/*---------------------------------------------------------------------------*\
 ##   ####  ######     | 
 ##  ##     ##         | Copyright: ICE Stroemungsfoschungs GmbH
 ##  ##     ####       |
 ##  ##     ##         | http://www.ice-sf.at
 ##   ####  ######     |
-------------------------------------------------------------------------------
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 1991-2005 OpenCFD Ltd.
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is based on OpenFOAM.

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
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Application
    checkYPlusCompressible

Description
    Calculates and reports yPlus for all wall patches, for each time in a
    database. Writes a field yPlus with the values on the wall faces

 ICE Revision: $Id: checkYPlusCompressible.C 8084 2007-10-15 17:59:48Z bgschaid $ 
\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "basicThermo.H"
#include "compressible/turbulenceModel/turbulenceModel.H"
#include "wallFvPatch.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{

#   include "addTimeOptions.H"
#   include "addRegionOption.H"

    argList::validOptions.insert("write","");

#   include "setRootCase.H"

#   include "createTime.H"

    // Get times list
    instantList Times = runTime.times();

    bool doWrite=false;
    if (args.options().found("write")) {
      doWrite=true;    
    }

    // set startTime and endTime depending on -time and -latestTime options
#   include "checkTimeOptions.H"

    runTime.setTime(Times[startTime], startTime);

#   include "createNamedMesh.H"

    for (label i=startTime; i<endTime; i++)
    {
        runTime.setTime(Times[i], i);

        Info<< "Time = " << runTime.timeName() << endl;

        mesh.readUpdate();

        Info << "Reading field p\n" << endl;
        volScalarField p
        (
            IOobject
            (
                "p",
                runTime.timeName(),
                mesh,
                IOobject::MUST_READ,
                IOobject::NO_WRITE
            ),
            mesh
        );

        Info << "Reading field U\n" << endl;
        volVectorField U
        (
            IOobject
            (
                "U",
                runTime.timeName(),
                mesh,
                IOobject::MUST_READ,
                IOobject::NO_WRITE
            ),
            mesh
        );

#       include "createPhi.H"

	Info<< "Reading thermophysical properties\n" << endl;
	autoPtr<basicThermo> thermo
	  (
	   basicThermo::New(mesh)
	   );

	volScalarField rho
	  (
	   IOobject
	   (
            "rho",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
	    ),
	   thermo->rho()
	   );

	Info<< "Creating turbulence model\n" << endl;
	
	autoPtr<compressible::turbulenceModel> turbulence
	  (
	   compressible::turbulenceModel::New
	   (
	    rho,
	    U,
	    phi,
	    thermo()
	    )
	   );    

        Info << " Creating yPlus" << endl;

        volScalarField yPlus
	  (
	   IOobject
	   (
	    "yPlus",
	    runTime.timeName(),
	    mesh,
	    IOobject::NO_READ,
	    IOobject::NO_WRITE
            ),
	   mesh,
	   0
	   );

	{
	  volScalarField::GeometricBoundaryField &bf=yPlus.boundaryField();
	  List<fvPatchField<scalar> *>bfNew(bf.size());
	  
	  forAll(bf,patchI) {
	    const fvPatch &patch=bf[patchI].patch();
	    
	    if(typeid(patch)!=typeid(wallFvPatch)) {
	      bfNew[patchI]=bf[patchI].clone().ptr();
	    } else {
	      bfNew[patchI]=new fixedValueFvPatchField<scalar>(patch,yPlus);      
	    }
	  }
	

	  bf.clear();
	  bf.setSize(bfNew.size());
	  forAll(bf,i) {
              bf.set(i,bfNew[i]);
	  }
	}
	
        Info << " Setting boundaries" << endl;
        forAll (mesh.boundary(), patchI)
        {
             if (typeid(mesh.boundary()[patchI]) == typeid(wallFvPatch))
            {
                tmp<scalarField> tYp = turbulence->yPlus(patchI);
                scalarField& Yp = tYp();

		forAll(Yp,faceI) {
		  yPlus.boundaryField()[patchI][faceI]=Yp[faceI];
		}

                Info<< "Patch " << patchI
                    << " named " << mesh.boundary()[patchI].name()
                    << " y+ : min: " << min(Yp) << " max: " << max(Yp)
                    << " average: " << average(Yp) << nl << endl;
            }
        }

	if(doWrite) {
            Info << " Writing yPlus " << endl;
            yPlus.write();
	}
    }

    Info << "End" << endl;

    return(0);
}


// ************************************************************************* //
