//  OF-extend Revision: $Id: writeAdditionalFieldsFunctionObject.H 1354 2009-07-28 15:34:09Z bgschaid $ 
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
    writeAdditionalFieldsFunctionObject

Description
    Lets the user specify an additional set of fields that is to be written with the other
    fields the are written by AUTO_WRITE

Example usage: writes Enthalpy and viscosity after t=15

functions 
(
    writeEnthalpy {
        functionObjectLibs ("libsimpleFunctionObjects.so");
        type writeAdditionalFields;
        fieldNames ( h mu );
        after 15;
    }
);

SourceFiles
    writeAdditionalFieldsFunctionObject.C

\*---------------------------------------------------------------------------*/

#ifndef writeAdditionalFieldsFunctionObject_H
#define writeAdditionalFieldsFunctionObject_H

#include "writeFieldsGeneralFunctionObject.H"
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class writeAdditionalFieldsFunctionObject Declaration
\*---------------------------------------------------------------------------*/

class writeAdditionalFieldsFunctionObject
:
    public writeFieldsGeneralFunctionObject
{
    // Private Member Functions

    //- Disallow default bitwise copy construct
    writeAdditionalFieldsFunctionObject(const writeAdditionalFieldsFunctionObject&);
    
    //- Disallow default bitwise assignment
    void operator=(const writeAdditionalFieldsFunctionObject&);

protected:

    //- Overwrite the default output time
    virtual bool outputTime();
public:

    //- Runtime type information
    TypeName("writeAdditionalFields");


    // Constructors

    //- Construct from components
    writeAdditionalFieldsFunctionObject
    (
        const word&,
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
