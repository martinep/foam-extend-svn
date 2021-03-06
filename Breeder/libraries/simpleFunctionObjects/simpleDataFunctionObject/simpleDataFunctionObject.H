//  OF-extend Revision: $Id: simpleDataFunctionObject.H 600 2008-04-28 13:34:56Z bgschaid $ 
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
    simpleFunctionObject

Description
    Basis for the other function objects here. Creates the directory and the files

SourceFiles
    simpleFunctionObject.C

\*---------------------------------------------------------------------------*/

#ifndef simpleDataFunctionObject_H
#define simpleDataFunctionObject_H

#include "simpleFunctionObject.H"
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class simpleDataFunctionObject Declaration
\*---------------------------------------------------------------------------*/

class simpleDataFunctionObject
:
    public simpleFunctionObject
{
    // Private Member Functions

    //- Disallow default bitwise copy construct
    simpleDataFunctionObject(const simpleDataFunctionObject&);
    
    //- Disallow default bitwise assignment
    void operator=(const simpleDataFunctionObject&);

protected:

    //- Get the path to the data directory
    fileName dataDir();

    //- Get the path to the base directory
    fileName baseDir();

    //- Name of the sub-dictionary of the case
    virtual word dirName()=0;

public:

    //- Runtime type information
    TypeName("simpleDataFunctionObject");


    // Constructors

    //- Construct from components
    simpleDataFunctionObject
    (
        const Time&,
        const dictionary&
    );

    bool start();

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
