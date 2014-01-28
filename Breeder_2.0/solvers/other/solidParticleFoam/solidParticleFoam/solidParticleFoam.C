/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) Tutorial Author: Hakan Nilsson
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
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Application
    solidParticleFoam

Description
    Example of the use of the solidParticleCloud class

\*---------------------------------------------------------------------------*/

//Some features of the fvCFD class are needed:
#include "fvCFD.H"
//The class definitions of the solidParticleCloud class are needed:
#include "solidParticleCloud.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{

#   include "setRootCase.H"

#   include "createTime.H"
#   include "createMesh.H"
#   include "createFields.H"
//The gravitational acceleration is needed:
#   include "readGravitationalAcceleration.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nCreating particle cloud" << endl;
    solidParticleCloud particles(mesh);
    //The solidParticleCloud class constructor allows the specification
    //of the cloudName of the Cloud directory (default is defaultCloud):
    //solidParticleCloud particles(mesh, "myCloud");

    //The solidParticleCloud class has access member functions:
    Info<<"\nFrom constant/particleProperties:" << endl;
    Info<<"rhop = " << particles.rhop() << endl;
    Info<<"e = " << particles.e() << endl;
    Info<<"mu = " << particles.mu() << endl;

    Info<< "\nStarting time loop\n" << endl;

    for (runTime++; !runTime.end(); runTime++)
    {
        Info<< "Time = " << runTime.timeName() << nl << endl;

        Info<< "Moving particles." << nl << endl;
        particles.move(g);

        runTime.write();

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    //It is possible to explicitly write the lagrangian fields.
    //Here they will be placed in the endTime+deltaT time directory:
    //Info<<"\nWriting fields." << endl;
    //particles.writeFields();

    Info<< "End\n" << endl;

    return(0);
}


// ************************************************************************* //
