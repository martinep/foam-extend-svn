//  OF-extend Revision: $Id: patchForceFunctionObject.H 592 2008-04-21 08:06:44Z bgschaid $ 
/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright  held by original author
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

Class
    patchForceFunctionObject

Description
    Calculates the forces on the patches

SourceFiles
    patchForceFunctionObject.C

\*---------------------------------------------------------------------------*/

#ifndef patchForceFunctionObject_H
#define patchForceFunctionObject_H

#include "patchFunctionObject.H"

#include "SolverInfo.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class patchForceFunctionObject Declaration
\*---------------------------------------------------------------------------*/

class patchForceFunctionObject
:
    public patchFunctionObject
{

    // Private Member Functions

    //- Disallow default bitwise copy construct
    patchForceFunctionObject(const patchForceFunctionObject&);
    
    //- Disallow default bitwise assignment
    void operator=(const patchForceFunctionObject&);

    SolverInfo solver_;
protected:

    //- Names of the files
    virtual wordList fileNames();

    word dirName();

public:

    //- Runtime type information
    TypeName("patchForce");


    // Constructors

    //- Construct from components
    patchForceFunctionObject
    (
        const Time&,
        const dictionary&
    );


    // Member Functions

    //- Sample and write
    void write();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
