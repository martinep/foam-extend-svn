/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author
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

Class
    sampleSurfaceFunctionObject

Description

SourceFiles
    sampleSurfaceFunctionObject.C

\*---------------------------------------------------------------------------*/

#ifndef sampleSurfaceFunctionObject_H
#define sampleSurfaceFunctionObject_H

#include "simpleDataFunctionObject.H"
#include "dictionary.H"
#include "Switch.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class probes;

/*---------------------------------------------------------------------------*\
                     Class sampleSurfaceFunctionObject Declaration
\*---------------------------------------------------------------------------*/

class sampleSurfaceFunctionObject
:
    public simpleDataFunctionObject
{

    Switch deleteDir_;


    // Private Member Functions

        //- Disallow default bitwise copy construct
        sampleSurfaceFunctionObject(const sampleSurfaceFunctionObject&);

        //- Disallow default bitwise assignment
        void operator=(const sampleSurfaceFunctionObject&);

protected:
    virtual word dirName();
public:

    //- Runtime type information
    TypeName("sampleSurface");


    // Constructors

        //- Construct from components
        sampleSurfaceFunctionObject
        (
            const Time&,
            const dictionary&
        );


    // Member Functions

    //- start is called at the start of the time-loop
    virtual bool start();

    //- execute is called at each ++ or += of the time-loop
    virtual void write();

    //- Read and set the function object if its data has changed
    virtual bool read(const dictionary& dict);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
