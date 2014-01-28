//  OF-extend Revision: $Id: simpleDataFunctionObject.C 600 2008-04-28 13:34:56Z bgschaid $ 
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

#include "simpleDataFunctionObject.H"
#include "addToRunTimeSelectionTable.H"

#include "polyMesh.H"
#include "IOmanip.H"
#include "Time.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(simpleDataFunctionObject, 0);

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

simpleDataFunctionObject::simpleDataFunctionObject
(
    const Time& t,
    const dictionary& dict
)
:
    simpleFunctionObject(t,dict)
{
}

fileName simpleDataFunctionObject::dataDir()
{
    return baseDir()/obr_.time().timeName();
}

fileName simpleDataFunctionObject::baseDir()
{
    fileName theDir;

    if (Pstream::parRun())
    {
        // Put in undecomposed case (Note: gives problems for
        // distributed data running)
        theDir =
            obr_.time().path()
            /".."
            /dirName();
    }
    else
    {
        theDir =
            obr_.time().path()
            /dirName();
    }

    return theDir;
}

bool simpleDataFunctionObject::start()
{
    simpleFunctionObject::start();

    mkDir(dataDir());

    return true;
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

} // namespace Foam

// ************************************************************************* //
