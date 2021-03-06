//  OF-extend Revision: $Id: writeAdditionalFieldsFunctionObject.C 1354 2009-07-28 15:34:09Z bgschaid $ 
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

#include "writeAdditionalFieldsFunctionObject.H"
#include "addToRunTimeSelectionTable.H"

#include "polyMesh.H"
#include "IOmanip.H"
#include "Time.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(writeAdditionalFieldsFunctionObject, 0);

    addToRunTimeSelectionTable
    (
        functionObject,
        writeAdditionalFieldsFunctionObject,
        dictionary
    );

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

writeAdditionalFieldsFunctionObject::writeAdditionalFieldsFunctionObject
(
    const word &name,
    const Time& t,
    const dictionary& dict
)
:
    writeFieldsGeneralFunctionObject(name,t,dict)
{
}

bool writeAdditionalFieldsFunctionObject::start()
{
    writeFieldsGeneralFunctionObject::start();

    Info << "Additional fields " << fieldNames() << " will be written" << endl;

    return true;
}

bool writeAdditionalFieldsFunctionObject::outputTime()
{
    return (
        time().outputTime()
        &&
        time().time().value()>=after());
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

} // namespace Foam

// ************************************************************************* //
