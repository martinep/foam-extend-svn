//  OF-extend Revision: $Id: patchIntegrateFunctionObject.H 592 2008-04-21 08:06:44Z bgschaid $ 
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
    patchIntegrateFunctionObject

Description
    Integrates fields on the patches

SourceFiles
    patchIntegrateFunctionObject.C

\*---------------------------------------------------------------------------*/

#ifndef patchIntegrateFunctionObject_H
#define patchIntegrateFunctionObject_H

#include "patchFieldFunctionObject.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class patchIntegrateFunctionObject Declaration
\*---------------------------------------------------------------------------*/

class patchIntegrateFunctionObject
:
    public patchFieldFunctionObject
{
    // Private Member Functions

    //- Disallow default bitwise copy construct
    patchIntegrateFunctionObject(const patchIntegrateFunctionObject&);
    
    //- Disallow default bitwise assignment
    void operator=(const patchIntegrateFunctionObject&);

    //- integrate single field on all patches
    template <class T>
    Field<T> integrate(const word& fieldName,T preset) const;
    
protected:

    word dirName();

    virtual scalarField process(const word& fieldName,scalar preset);
    virtual Field<vector> process(const word& fieldName,vector preset);
    virtual Field<sphericalTensor> process(const word& fieldName,sphericalTensor preset);
    virtual Field<symmTensor> process(const word& fieldName,symmTensor preset);
    virtual Field<tensor> process(const word& fieldName,tensor preset);

public:

    //- Runtime type information
    TypeName("patchIntegrate");


    // Constructors

    //- Construct from components
    patchIntegrateFunctionObject
    (
        const Time&,
        const dictionary&
    );

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

#ifdef NoRepository
#   include "patchIntegrateFunctionObjectTemplates.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
