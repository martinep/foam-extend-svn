//  OF-extend Revision: $Id: volumeAverageFunctionObject.C 592 2008-04-21 08:06:44Z bgschaid $ 
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

\*---------------------------------------------------------------------------*/

#include "volumeAverageFunctionObject.H"
#include "addToRunTimeSelectionTable.H"

#include "volFields.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(volumeAverageFunctionObject, 0);

    addToRunTimeSelectionTable
    (
        functionObject,
        volumeAverageFunctionObject,
        dictionary
    );



// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

volumeAverageFunctionObject::volumeAverageFunctionObject
(
    const Time& t,
    const dictionary& dict
)
:
    volumeFieldFunctionObject(t,dict)
{
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

word volumeAverageFunctionObject::dirName()
{
    return typeName;
}

scalarField volumeAverageFunctionObject::process(const word& fieldName,scalar preset)
{
    return average(fieldName,preset);
}

Field<vector> volumeAverageFunctionObject::process(const word& fieldName,vector preset)
{
    return average(fieldName,preset);
}

Field<sphericalTensor> volumeAverageFunctionObject::process(const word& fieldName,sphericalTensor preset)
{
    return average(fieldName,preset);
}

Field<symmTensor> volumeAverageFunctionObject::process(const word& fieldName,symmTensor preset)
{
    return average(fieldName,preset);
}

Field<tensor> volumeAverageFunctionObject::process(const word& fieldName,tensor preset)
{
    return average(fieldName,preset);
}

string volumeAverageFunctionObject::firstLine()
{
    return " average";
}

} // namespace Foam

// ************************************************************************* //
