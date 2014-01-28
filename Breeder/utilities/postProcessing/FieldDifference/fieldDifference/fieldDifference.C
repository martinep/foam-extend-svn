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
    fieldDifference

Description
    Calculates the difference for a scalar field
    
    Revision: $Id: /local/openfoam/Utilities/PostProcessing/fieldDifference/fieldDifference.C 1871 2007-08-22T16:54:01.619148Z bgschaid  $ 
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
#   include "addRegionOption.H"

    Foam::argList::validArgs.append("scalarField");
    
#   include "setRootCase.H"
#   include "createTime.H"

    word fieldName(args.args()[3]);
   
    instantList Times = runTime.times();

#   include "checkTimeOptionsNoConstant.H"

    if(startTime==0) {
        startTime=1;
    }

    if(startTime>1) {
        // We need one timestep previous
        startTime--;
    }

    if(endTime<=2) {
        FatalErrorIn("fieldDifference")
            << " The first timestep " << Times[endTime-1] 
                << " has no previous value. Can't do anything\n!"
                << exit(FatalError);
    }

    runTime.setTime(Times[startTime], startTime);

#   include "createNamedMesh.H"

    bool firstTime=true;
    scalar prevTimeValue=-1;

    volScalarField oldField
        (
        IOobject
            (
                fieldName,
                runTime.timeName(),
                mesh,
                IOobject::MUST_READ,
                IOobject::NO_WRITE
            ),
            mesh
        );

    for (label i=startTime; i<endTime; i++)
    {
        runTime.setTime(Times[i], i);

        Info<< "Time = " << runTime.timeName() << endl;
	
        volScalarField theField
            (
                IOobject
                (
                    fieldName,
                    runTime.timeName(),
                    mesh,
                    IOobject::MUST_READ,
                    IOobject::NO_WRITE
                ),
                mesh
            );

        if(firstTime) {
            firstTime=false;

            Info << "This step has no previous. Skipping it" << endl;

        } else {
            volScalarField deltaField
                (
                    IOobject
                    (
                        "delta"+fieldName,
                        runTime.timeName(),
                        mesh,
                        IOobject::NO_READ,
                        IOobject::NO_WRITE
                    ),
                    mesh,
                    dimensionedScalar("delta"+fieldName,theField.dimensions()/runTime.dimensions(),0)                
            );

            dimensionedScalar deltaT("deltaT",runTime.dimensions(),runTime.value()-prevTimeValue);
            Info << " Time Difference: " << deltaT << endl;
            deltaField=(theField-oldField)/deltaT;

            Info << " Change Rate: [ " << min(deltaField) << " , " << max(deltaField) << "]" << endl;
            Info << " Change Absolute: [ " << min(deltaField)*deltaT << " , " << max(deltaField)*deltaT << "]" << endl;
            deltaField.write();
        }

        prevTimeValue=runTime.value();
        oldField=theField;

	Info << endl;
    }

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
