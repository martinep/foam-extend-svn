/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright Hydro-Quebec - IREQ, 2008
     \\/     M anipulation  |
-------------------------------------------------------------------------------
  License
  This file is part of OpenFOAM.

  OpenFOAM is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
  for more details.

  You should have received a copy of the GNU General Public License
  along with OpenFOAM; if not, write to the Free Software Foundation,
  Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

  Description
  Conversion of CGNS files into Foam's mesh and fields

Authors 
  Martin Beaudoin, Hydro-Quebec - IREQ, 2005
  Robert Magnan,   Hydro-Quebec - IREQ, 2007

\*---------------------------------------------------------------------------*/

// open foam includes
#include "argList.H"
#include "error.H"
#include "Time.H"
#include "IFstream.H"
#include "ISstream.H"
#include "volFields.H"
#include "fvMesh.H"
#include "pointFields.H"
#include "pointVolInterpolation.H"
#include "IOdictionary.H"

// cgns interface library
#include "libcgnsoo3/cgnsoo.H"
#include "libcgnsoo3/file.H"

// includes specific to this application
#include "CGNSBoundaryConditions.H"
#include "CGNSQuantity.H"
#include "CGNSElementType.H"
#include "CGNSQuantityConverter.H"
#include "ConnectivityMapper.H"
#include "SolutionConverter.H"
#include "FoamReplaceChar.H"
#include "FoamQuantities.H"

// standard C++ library
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <cstring>

using std::string;
using std::vector;
using std::list;
using std::map;
using std::set;

using Foam::Info;
using Foam::Warning;
using Foam::FatalError;
using Foam::exit;
using Foam::endl;

using namespace CGNSOO;



// Taking care of rho
// Check if rho if it was specified as a command line argument
Foam::scalar getRhoValue( const Foam::argList& args, Foam::IOobject& ioobj )
{
	Foam::scalar rho = 1.0;  // Default value;

	// get rho from the command line
	if( args.options().found("rho") )
	{
		rho = Foam::readScalar(Foam::IStringStream(args.options()["rho"])());
		Info << "User specified value for rho = " << rho << endl;
	}
	//Info << "Value for rho = " << rho << endl;
	return rho;
}

//------------------------------------------------------------------------------
// Subroutine to extract a list of word pairs from a list of region names
// This is used to parse the command line argument defining matching cyclic BC
// Returns true on error
//------------------------------------------------------------------------------
static bool parseMatchingCyclicBcNames( const string& args, 
					list< pair<string,string> >& namepairs )
{
    // works on a modifiable c-string copy
    char* str = new char[args.length()+1];
    std::strcpy( str, args.c_str() );
    string tokens[2];
    int itok = 0;
    const char separators[] = { ':', ',', '\0' };
    char* psep = std::strtok( str, separators );
    while (psep != NULL)
    {
	tokens[itok++] = psep;
	if ( itok==2 )
	{
		itok = 0; // reset
		//Info << "parseMatchingCyclicBcNames: new BC pair: " << tokens[0] << " - " << tokens[1] << endl;
		namepairs.push_back( pair<string,string>(tokens[0],tokens[1]) );
	}
        psep = std::strtok( NULL, separators );
    }
    delete str;
    return (itok != 0); // error if odd number of tokens
}

//------------------------------------------------------------------------------
// Main program
//------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    using Foam::argList;
    
    argList::noParallel();
    argList::validArgs.append("CGNS file");
    argList::validOptions.insert("zone", "zoneList");
    argList::validOptions.insert("dryrun", "");
    argList::validOptions.insert("novalidationMesh", "");
    argList::validOptions.insert("saveSolutions", "");
    argList::validOptions.insert("separatePatches", "");
    argList::validOptions.insert("cfxCompatibility", "");    
    argList::validOptions.insert("use2DElementsAsPatches", "");
    argList::validOptions.insert("matchCyclicBC", "bc1:bc2");
    argList::validOptions.insert("cyclicRotX", "angle_nn_degree");
    argList::validOptions.insert("cyclicRotY", "angle_in_degree");
    argList::validOptions.insert("cyclicRotZ", "angle_in_degree");
    argList::validOptions.insert("mergeTolerance", "tolerance for matching identical nodes: fraction of smallest edge. Default value=0.1");
    argList::validOptions.insert("cyclicMatchFaceTolFactor", "tolerance for matching cyclic faces: fraction of the smallest edge. Default value= 0.1");
    argList::validOptions.insert("rho", "Volumic_density. Default value=1.0");
    argList::validOptions.insert("debug", "");
    argList::validOptions.insert("mapUnknown", "");

    argList::validOptions.insert("help", "");

    argList args(argc, argv);

    // validate arguments
    if (!args.check())
    {
        Foam::FatalError.exit();
    }

    bool separatePatches = false;
    if ( args.options().found("separatePatches") )
    {
    	separatePatches = true;
    }
    
    bool cfxCompatibilityMode = false;
    if ( args.options().found("cfxCompatibility") )
    {
    	cfxCompatibilityMode = true;
    }
    
    bool use2DElementsAsPatches = false;
    if ( args.options().found("use2DElementsAsPatches") )
    {
    	use2DElementsAsPatches = true;
    }
    
    bool debug = false;
    if ( args.options().found("debug") )
    {
    	debug = true;
    }
    
    bool mapUnknown = false;
    if ( args.options().found("mapUnknown") )
    {
    	mapUnknown = true;
    }
    
    bool dryRun = false;
    if (args.options().found("dryrun"))
    {
        Warning << "Option -dryrun was used: data will not be saved" << endl;
	dryRun = true;
    }
   
    Foam::scalar mergeTolerance = 0.1;
    if ( args.options().found("mergeTolerance") )
    {
    	mergeTolerance = Foam::readScalar(Foam::IStringStream(args.options()["mergeTolerance"])());;
	Info << "MergeTolerance set to " << mergeTolerance << endl;
    }
    
    if( args.options().found("rho") && !args.options().found("saveSolutions") )
    {
	Warning << "Option -rho is useless since no solution will be saved (no -saveSolutions option)" 
		<< endl;
    }

    if( args.options().found("help") )
    {
        args.printUsage();

        Info << endl;
        Info << "  Note: to specify a rotation angle like 1/13 of 360 degree," << endl;
        Info << "        you can use the Unix command bc to compute the value with full precision, eg:" << endl;
        Info << "            -cyclicRotZ `echo \"360/13\" | bc -l`" << endl;
        Info << endl;
        exit(0);
    }

#   include "createTime.H"
#if 0
    CgnsToFoamDictionary optionsDict(
		IOobject( "CgnsToFoamDict", 
			  mesh.time().constant(), 
			  mesh,
			  IOobject::READ_IF_PRESENT, 
			  IOobject::NO_WRITE )
    );
    if ( optionsDict.headerOk() )
    {
		Info << "CgnsToFoamOptions: " << endl;
		Info << "\tSplitting multiple cell into different zones : " << optionsDict.splitMixed() << endl;
		Info << "\tConversion Path is " << optionsDict.conversionDirectory() << endl;
    }
#endif
    //--------------------------------------------------
    
    string cgnsFilename(args.args()[3]);
    if ( debug )
    	Info << "Conversion of file " << cgnsFilename << endl;
    CGNSOO::file cgnsFile( cgnsFilename, CGNSOO::file::READONLY );
    
    int nbases = cgnsFile.getNbBase();
    if ( nbases == 0 )
    {
        FatalError << "No Base node were found in the CGNS file" 
		   << exit( FatalError );
    }
    else if ( nbases > 1 )
    {
        Warning << "More than one CGNS Base were found in the file." << endl
		<< "Only the first one will be treated." << endl;
    }
    
    string baseName;
    int physicalDim, cellDim;
    Base_t base = cgnsFile.readBase( 0, baseName, physicalDim, cellDim );
    int nbZones = base.getNbZone();
    if ( debug )
    	Info << "Mesh: total number of zones: " << nbZones << endl;
    
    //--------------------------------------------------------------------------
    // Load family definitions into a map indexed by family name
    // We are only interested in family with BCs to resolve
    // boundary conditions of type FamilySpecified.
    //--------------------------------------------------------------------------
    int nfamilies = base.getNbFamily();
    map<string,BCType_t> fammap;
    for ( int ifam=0 ; ifam<nfamilies ; ifam++ )
    {
    	string famname;
	int ngeoref; // unused
	bool hasfbc;
    	Family_t fam = base.readFamily( ifam, famname, hasfbc, ngeoref );
	if ( hasfbc )
	{
		string fambcname; // not useful
		BCType_t bctype;
		fam.readFamilyBC( fambcname, bctype );
		fammap[famname] = bctype;
	}
    }
    
    //--------------------------------------------------------------------------
    // Build a local to global node map table
    // Extract node coordinates
    //--------------------------------------------------------------------------
    ConnectivityMapper mapper;
        
    for( int indexZone=0 ; indexZone<nbZones ; indexZone++ )
    {
        // Zone
	string zonename;
	vector<int> nodesize, cellsize, bndrysize;
	ZoneType_t zonetype;
	Zone_t zone = base.readZone( indexZone, 
					zonename, 
					nodesize, cellsize, bndrysize, 
					zonetype );
						
        // Read the mesh nodes
        vector<double> xCoordinates;
        vector<double> yCoordinates;
        vector<double> zCoordinates;

	int nbgrids = zone.getNbGridCoordinates();
	if ( nbgrids != 1 )
	{
		Warning << "CGNS file with more than one GridCoordinates"
			<< " - only the first grid will be read"
			<< endl;
	}
	
	// What type of coordinate system do we have?
	string coordName;
	GridCoordinates_t gridcoo = zone.readGridCoordinates( 0, coordName );
	int nbcoords = gridcoo.getNbCoordinatesData();
	
	std::map<string,int> coomap;
	for ( int icoo=0 ; icoo<nbcoords ; icoo++ )
	{
		string     cooname;
		DataType_t cootype;
		gridcoo.getCoordinatesDataInfo( icoo, cooname, cootype );
		coomap[cooname] = icoo;
	}
	if ( nbcoords==3 &&
	     coomap.find("CoordinateX") != coomap.end() &&
	     coomap.find("CoordinateY") != coomap.end() &&
	     coomap.find("CoordinateZ") != coomap.end() )
	{
		// Cartesian coordinate system
		DataArray_t datax = gridcoo.readCoordinatesData( "CoordinateX", xCoordinates );
		DataArray_t datay = gridcoo.readCoordinatesData( "CoordinateY", yCoordinates );
		DataArray_t dataz = gridcoo.readCoordinatesData( "CoordinateZ", zCoordinates );
	}
	else if ( nbcoords==3 &&
	     coomap.find("CoordinateR") != coomap.end() &&
	     coomap.find("CoordinateZ") != coomap.end() &&
	     coomap.find("CoordinateTheta") != coomap.end() )
	{
		// lire en r,t,z et convertir en x,y,z
		vector<double> rCoo, tCoo;
		DataArray_t datar = gridcoo.readCoordinatesData( "CoordinateR", rCoo );
		DataArray_t datat = gridcoo.readCoordinatesData( "CoordinateTheta", tCoo );
		DataArray_t dataz = gridcoo.readCoordinatesData( "CoordinateZ", zCoordinates );
		int ndata = rCoo.size();
		for ( int i=0 ; i<ndata ; i++ )
		{
			xCoordinates.push_back( rCoo[i]*cos(tCoo[i]) );
			yCoordinates.push_back( rCoo[i]*sin(tCoo[i]) );
		}
	}
	else
	{
		FatalError << "Unknown coordinate system ";
		for ( std::map<string,int>::const_iterator i  = coomap.begin() ; 
		                                           i != coomap.end() ; 
							   i++ )
			FatalError << " : " << (*i).first;
		FatalError << endl << exit(FatalError);
	}

	// Convert the 3 vectors of doubles into a list of points
	list<Foam::point> plist;
	int nnodes = xCoordinates.size();
        for( int i=0 ; i<nnodes ; i++)
        {
		Foam::point pt( xCoordinates[i],
		 		yCoordinates[i],
		 		zCoordinates[i] );
		plist.push_back( pt );
        }

	// Read the connectivity information
	// and let the merger handle all this mess!!
	switch ( zonetype )
	{
	case CGNSOO::Structured:
		// Connectivity is implicit ... it will be constructured internally
		mapper.addStructuredZone( nodesize[0],nodesize[1],nodesize[2],plist );
		break;
	case CGNSOO::Unstructured:
		{
		// get all the element sections
		int nbesections = zone.getNbElements();
		vector< string        > sectionnames(nbesections);
		vector< vector<int>   > connectivities(nbesections);
		vector< ElementType_t > etypes(nbesections);
		for ( int ies=0 ; ies<nbesections ; ies++ )
		{
			//string sectionname;
			int    start, end, nbndry;
			bool   hasparent;
			Elements_t esection = zone.readElements( 
				ies, sectionnames[ies], etypes[ies], start, end, nbndry, hasparent );
			DataArray_t connecda = esection.readConnectivity( connectivities[ies] );
		}
		mapper.addUnstructuredZone( nodesize[0], cellsize[0], plist,
					    sectionnames, etypes, connectivities );
		}
		break;
	default:
		FatalError << "Unrecognized zone type"
			   << " - only Structured and Unstructured are accepted"
			   << exit(FatalError);
		break;
	}
    }    
    
    // Merge identical points at the interfaces
    // Normally, for an unstructured mesh, there should not be any change
    // For a structured one, the points at the boundary must be merged.
    if ( debug )
    	Info << "Mesh: total number of nodes before merge: " << mapper.getTotalNodes() << endl;
    mapper.merge( mergeTolerance );
    
    // Validation
    int nCreatedCells = mapper.getTotalCells();
    if ( debug )
    {
	    Info << "Mesh: total number of nodes after merge: " << mapper.getTotalNodes() << endl;
	    Info << "Mesh: total number of cells after merge: " << nCreatedCells << endl;
    }
    
    //--------------------------------------------------------------------------
    // Read-in the boundary conditions
    //--------------------------------------------------------------------------

    CGNSBoundaryConditions bc_merger( mapper, fammap, debug );
    if ( use2DElementsAsPatches )
    {
    	bc_merger.addPatchesFromElements( CGNSOO::BCTypeNull  );
    }
    else
    {
	for( int indexZone=0 ; indexZone<nbZones ; indexZone++ )
	{
		string zonename;
		vector<int> nodesize, cellsize, bndrysize;
		ZoneType_t zonetype;
		Zone_t    zone = base.readZone( indexZone, 
						zonename, 
						nodesize, cellsize, bndrysize, 
						zonetype );
		ZoneBC_t zonebc = zone.readZoneBC();
		int nbBoco = zonebc.getNbBoundaryConditions();
		
		for( int indexBC=0 ; indexBC < nbBoco ; indexBC++ )
		{
			string         bcname;
			BCType_t       bctype;
			PointSetType_t psettype;
			BC_t bc = zonebc.readBC( indexBC, bcname, bctype, psettype );
	
			bc_merger.addBoundaryPatch( base, indexZone, zonetype, bc, bcname, bctype, psettype );
		}
	}
    }
    bc_merger.buildPatches( separatePatches );
    
    // Lets deal with cyclic BC ....
    if (args.options().found("matchCyclicBC"))
    {
        Foam::scalar cyclicRotX = 0;
        Foam::scalar cyclicRotY = 0;
        Foam::scalar cyclicRotZ = 0;
        Foam::scalar cyclicMatchFaceTolFactor = 0.1;  // Default value... one tenth of the smallest edge found in the mesh

        if ( debug )
           Info << "Processing cyclic boundary conditions" << endl;
	
	// Divide the argument to matchCyclicBC into pairs of names to
	// be matched one to another
	string argCyclicBC = args.options()["matchCyclicBC"];
	//string s_argCyclicBC = FoamReplaceChar( argCyclicBC, ' ', '_' );
	string s_argCyclicBC = argCyclicBC;
        list< pair<string,string> > l_matchingCyclicBcNames;
	if ( parseMatchingCyclicBcNames(s_argCyclicBC,l_matchingCyclicBcNames) )
	{
	    FatalError  << "Unmatched bcname for cyclic boundaries"
	    		<< " - number of names must be even."
	    		<< exit(FatalError);
	}

        if( l_matchingCyclicBcNames.size() > 0 )
        {
	    Foam::vector rotAxis(0,0,1);
	    Foam::scalar rotAngle = 0;
            if( args.options().found("cyclicRotX") )
	    {
                cyclicRotX = Foam::readScalar(Foam::IStringStream(args.options()["cyclicRotX"])());
		rotAxis = Foam::vector(1,0,0);
		rotAngle = cyclicRotX;
	    }
            if( args.options().found("cyclicRotY") )
	    {
                cyclicRotY = Foam::readScalar(Foam::IStringStream(args.options()["cyclicRotY"])());
		rotAxis = Foam::vector(0,1,0);
		rotAngle = cyclicRotY;
	    }
            if( args.options().found("cyclicRotZ") )
	    {
                cyclicRotZ = Foam::readScalar(Foam::IStringStream(args.options()["cyclicRotZ"])());
		rotAxis = Foam::vector(0,0,1);
		rotAngle = cyclicRotZ;
	    }
            if( args.options().found("cyclicMatchFaceTolFactor") )
                cyclicMatchFaceTolFactor = Foam::readScalar(Foam::IStringStream(args.options()["cyclicMatchFaceTolFactor"])());

            // Validation
            if( cyclicRotX == 0 && cyclicRotY == 0 && cyclicRotZ == 0 )
            {
                FatalError << "Option -cyclicRot[XYZ] is missing. "
			   << "Please specify a rotation angle for the periodic cyclic BC." 
			   << exit(FatalError);
            }


            for ( list< pair<string,string> >::iterator p  = l_matchingCyclicBcNames.begin() ;
						        p != l_matchingCyclicBcNames.end() ;
						        p++ )
            {
	    	const string& firstPatchName  = p->first;
		const string& secondPatchName = p->second;
		
		int retcode = bc_merger.computeCyclicBC( firstPatchName, secondPatchName, rotAxis, rotAngle, cyclicMatchFaceTolFactor );
		if ( retcode < 0 )
		{
			switch( retcode )
			{
			case -1:
				FatalError << "Option -matchCyclicBC: Unknown BC name: "
					   << firstPatchName << endl;
				break;
			case -2:
				FatalError << "Option -matchCyclicBC: Unknown BC name: "  
					   << secondPatchName << endl;
				break;
			}
			FatalError.exit(1);
		}
	    }
        }
    }

    //--------------------------------------------------------------------------
    // Output in the OpenFOAM format
    //--------------------------------------------------------------------------
    if ( debug )
	Info << "Creation of Foam poly mesh" << endl;
	
    Foam::polyMesh* pShapeMesh = bc_merger.buildFoamMesh( runTime );

    if (args.options().found("noMeshValidation"))
    {
        if ( debug )
	   Info << "Option -noMeshValidation used: mesh will not be validated" << endl;
    }
    else
    {
        if ( debug )
    	   Info << "Validation of the mesh" << endl;
	pShapeMesh->checkMesh();
    }
    
    if (!dryRun)
    {
    	Info << "Output of mesh and boundary conditions" << endl;
	Foam::IOstream::defaultPrecision(10); // Set the precision of the points data to 10
	pShapeMesh->write();
    }
   
    // Save CGNS solutions as initial solution? 
    if ( args.options().found("saveSolutions") )
    {
        Foam::fvMesh cell_mesh(*pShapeMesh);
	
        Foam::scalar rho = getRhoValue( args, runTime );
	
	CGNSQuantityConverter* qConverter = (cfxCompatibilityMode) 
		? new CGNSQuantityConverter_CFXcompatibility()
		: new CGNSQuantityConverter();
	SolutionConverter solConverter( *pShapeMesh, base, *qConverter );
	solConverter.buildAndWriteFoamFields( mapper, base, rho, runTime, mapUnknown, dryRun );
	delete qConverter;
    }
    
    if ( debug )
        Info << "Please validate Boundary Conditions by running FoamX." << endl;
    
    return 0;
}

#ifdef MISSING_POINTVOLINTERPOLATION
# include "pointVolInterpolation.C"
#endif
