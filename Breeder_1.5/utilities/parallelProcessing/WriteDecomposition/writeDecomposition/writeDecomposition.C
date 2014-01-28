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
    writeDecomposition

Description
    Writes the decomposition

    Revision: $Id: /local/openfoam/Utilities/PostProcessing/writeDecomposition/writeDecomposition.C 1280 2007-04-27T13:55:25.796383Z bgschaid  $ 
\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "argList.H"
#include "Time.H"
#include "polyMesh.H"

using namespace Foam;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Main program:

int main(int argc, char *argv[])
{
#   include "addTimeOptionsNoConstant.H"

#   include "setRootCase.H"
#   include "createTime.H"

    instantList Times = runTime.times();

#   include "checkTimeOptionsNoConstant.H"

    if(!Pstream::parRun()) {
        FatalErrorIn(
            "writeDecomposition::main"
        ) << " this utility only makes sense on a decomposed grid " << endl
            << exit(FatalError);


    }

    runTime.setTime(Times[startTime], startTime);

#   include "createMesh.H"

    for (label i=startTime; i<endTime; i++)
    {
        runTime.setTime(Times[i], i);

        Info<< "Time = " << runTime.timeName() << endl;

	Info << "Decomposition field" << endl;

	volScalarField decomposition
        (
            IOobject
            (
                "decomposition",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            mesh,
            dimensionedScalar("decomposition",dimless,0.)
        );

        decomposition=Pstream::myProcNo();
	decomposition.write();
		
	Info << endl;
    }

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
