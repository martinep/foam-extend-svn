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
    \\  /    A nd           | Copyright (C) 1991-2004 OpenCFD Ltd.
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
    Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

Application
    Sets the velocity on patches according to a rotation vector

Description

    Revision: $Id: /local/openfoam/InitialConditions/setRadialBC/setRadialBC.C 1991 2007-09-14T12:08:34.864129Z bgschaid  $ 
\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "OSspecific.H"
#include "fixedValueFvPatchFields.H"
#include "movingWallVelocityFvPatchVectorField.H"

#include <fstream>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{

#   include "setRootCase.H"

#   include "createTime.H"
#   include "createMesh.H"
#   include "createFields.H"

  // Read control dictionary
  IOdictionary radialBCDict
    (
     IOobject
     (
      "rotationDict",
      runTime.system(),
      mesh,
      IOobject::MUST_READ,
      IOobject::NO_WRITE
      )
     );

  wordList bcs=radialBCDict.lookup("boundaries");
  scalar revs=readScalar(radialBCDict.lookup("revsPerMinute"));
  vector rotation=radialBCDict.lookup("rotationVector");
  vector origin=radialBCDict.lookup("originVector");
  bool removeNormal=true;

  if(radialBCDict.found("removeNormalComponent")) {
    removeNormal=readBool(radialBCDict.lookup("removeNormalComponent"));
  }

  rotation /= mag(rotation);

  Info << " Setting Boundaries " << bcs << " to " << revs << " revs with rotation " << rotation << endl;


  
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

  volVectorField::GeometricBoundaryField& Upatches = U.boundaryField();

  int patched=0;

  forAll(bcs,bcI)
    {
      word bcName=bcs[bcI];

      forAll(Upatches, patchI)
	{
	  if
              ((
                (typeid(Upatches[patchI]) == typeid(fixedValueFvPatchVectorField)) ||
                (typeid(Upatches[patchI]) == typeid(movingWallVelocityFvPatchVectorField))
             )
	     &&
	     (mesh.boundaryMesh()[patchI].name() == bcName) 
	     )
	    {
	      Info << " Patching rotating wall " << bcName << "\n";
	      patched++;

	      fixedValueFvPatchVectorField& Upatch =
		refCast<fixedValueFvPatchVectorField>(Upatches[patchI]);
	      
	      const vectorField& faceCentres = 
		mesh.Cf().boundaryField()[patchI];

	      const vectorField& faceNormals = 
		mesh.Sf().boundaryField()[patchI];

	      forAll(faceCentres, facei)
		{
		  vector relative=faceCentres[facei]-origin;
		  scalar radius=mag(relative);
		  vector direction=relative/radius;
		  
		  scalar factor=radius*(revs/60)*2*3.1415;
		  
		  Upatch[facei] = factor*(rotation^direction);

		  if(removeNormal) {
		    vector normal=faceNormals[facei]/mag(faceNormals[facei]);
		    scalar component=Upatch[facei] & normal;

		    //		    Info << facei << "\t" << Upatch[facei] << "\t" << component << "\t";

		    Upatch[facei]-=component*normal;

		    //		    Info << Upatch[facei] << "\t" << (Upatch[facei] & normal) << endl;
		  }
		}
	    }
	  
	};
    };

  if(patched!=bcs.size()) {
    Info << "\n\n Patched " << patched << " walls, but " << bcs.size() << " were specified. Not writing U\n" << endl;
  } else {     
    Info<< "Writing modified field U\n" << endl;
    U.write();
  }

  Info<< "End\n" << endl;
  
  return(0);
}


// ************************************************************************* //
