/*---------------------------------------------------------------------------*\
 ##   ####  ######     | 
 ##  ##     ##         | Copyright: ICE Stroemungsfoschungs GmbH
 ##  ##     ####       |
 ##  ##     ##         | http://www.ice-sf.at
 ##   ####  ######     |
-------------------------------------------------------------------------------
 =========                   |
 \\      /   F ield          | OpenFOAM: The Open Source CFD Toolbox
  \\    /    O peration      |
   \\  /     A nd            | Copyright (C) 1991-2005 OpenCFD Ltd.
    \\/      M anipulation   |
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
    meshQualityFields

Description
    Writes mesh-quality fields

    Revision: $Id: /local/openfoam/Utilities/PostProcessing/meshQualityFields/meshQualityFields.C 1151 2007-03-12T16:33:26.026427Z bgschaid  $ 
\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "argList.H"
#include "Time.H"
#include "fvMesh.H"
#include "cellQuality.H"
#include "nearWallDist.H"

using namespace Foam;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Main program:

int main(int argc, char *argv[])
{
#   include "addTimeOptionsNoConstant.H"
#   include "addRegionOption.H"

#   include "setRootCase.H"
#   include "createTime.H"

    instantList Times = runTime.times();

#   include "checkTimeOptionsNoConstant.H"

    runTime.setTime(Times[startTime], startTime);

#   include "createNamedMesh.H"

    for (label i=startTime; i<endTime; i++)
    {
        runTime.setTime(Times[i], i);

        Info<< "Time = " << runTime.timeName() << endl;

        polyMesh::readUpdateState state = mesh.readUpdate();

	cellQuality quality(mesh);

	Info << "Generating non-orthogonality" << endl;

	volScalarField nonOrth
        (
            IOobject
            (
                "nonOthogonal",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            mesh,
            dimensionedScalar("nonOrthogonal",dimless,0.)
        );
	nonOrth.transfer(quality.nonOrthogonality()());
	nonOrth.write();
	
	Info << "Generating skewness" << endl;

	volScalarField skewness
        (
            IOobject
            (
                "skewness",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            mesh,
            dimensionedScalar("skewness",dimless,0.)
        );
	skewness.transfer(quality.skewness()());
	skewness.write();

	Info << "Generating volume" << endl;

	volScalarField volume
        (
            IOobject
            (
                "cellVolume",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            mesh,
            dimensionedScalar("volume",dimensionSet(0,3,0,0,0,0,0),0.)
        );
	const scalarField &vol=mesh.V();
	forAll(vol,cellI) {
	  volume[cellI]=vol[cellI];
	}
	volume.write();
	
	Info << "Generating surface area" << endl;

	surfaceScalarField faceArea
        (
            IOobject
            (
                "faceArea",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            mesh,
            dimensionedScalar("area",dimensionSet(0,2,0,0,0,0,0),0.)
        );
        faceArea=mag(mesh.Sf());
	faceArea.write();
	
	Info << "Generating wall distance" << endl;

	volScalarField wallDist
        (
            IOobject
            (
                "wallDist",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            mesh,
            dimensionedScalar("dist",dimensionSet(0,1,0,0,0,0,0),0.)
        );

        nearWallDist dist(mesh);
        forAll(wallDist.boundaryField(),patchI) {
            wallDist.boundaryField()[patchI]=dist[patchI];
        }

	wallDist.write();
	
	Info << endl;
    }

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
