//  OF-extend Revision: $Id: patchFunctionObject.C 640 2008-05-26 19:07:08Z bgschaid $ 
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

#include "patchFunctionObject.H"
#include "addToRunTimeSelectionTable.H"

#include "volFields.H"
#include "OStringStream.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(patchFunctionObject, 0);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

patchFunctionObject::patchFunctionObject
(
    const Time& t,
    const dictionary& dict
)
:
    timelineFunctionObject(t,dict),
    patchNames_(0),
    patchIndizes_(0)
{
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool patchFunctionObject::start()
{
    patchNames_ = wordList(dict_.lookup("patches"));

    timelineFunctionObject::start();

    patchIndizes_.setSize(patchNames_.size());

    const fvMesh &mesh=refCast<const fvMesh>(obr_);
    forAll(patchNames_,i) {
        const word &name=patchNames_[i];
        patchIndizes_[i]=mesh.boundaryMesh().findPatchID(name);
        if(patchIndizes_[i]<0) {
            WarningIn("patchFunctionObject::start()") 
                << " Patch " << name << " does not exist in patches: " 
                    << mesh.boundaryMesh().names() << endl;
        }
    }

    if (Pstream::master())
    {
        if (debug)
        {
            Pout<< "Probing patches:" << patchNames_ << nl
                << endl;
        }
    }

    return true;
}

string patchFunctionObject::firstLine()
{
    OStringStream o;

    forAll(patchNames_,patchI) {
        o << token::SPACE << patchNames_[patchI];
    }

    return o.str();
}

} // namespace Foam

// ************************************************************************* //
