//  OF-extend Revision: $Id: patchForceFunctionObject.C 625 2008-05-14 23:37:48Z bgschaid $ 
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

#include "patchForceFunctionObject.H"
#include "addToRunTimeSelectionTable.H"

#include "volFields.H"
#include "surfaceFields.H"
#include "IOmanip.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(patchForceFunctionObject, 0);

    addToRunTimeSelectionTable
    (
        functionObject,
        patchForceFunctionObject,
        dictionary
    );



// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

patchForceFunctionObject::patchForceFunctionObject
(
    const Time& t,
    const dictionary& dict
)
:
    patchFunctionObject(t,dict),
    solver_(obr_,dict)
{
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void patchForceFunctionObject::write()
{
    vectorField vals(patchNames_.size(), VGREAT*vector::one);
   
    const fvMesh &mesh=refCast<const fvMesh>(obr_);

    const volScalarField &p=mesh.lookupObject<volScalarField>("p");
    const volVectorField &U=mesh.lookupObject<volVectorField>("U");

    if(solver_.compressible()) {
        const volScalarField &mu=obr_.lookupObject<volScalarField>("mu");

        forAll(patchIndizes_,i) {
            label patchI=patchIndizes_[i];
            
            if(patchI>=0) {
                vector pressureForce=gSum
                    (
                        p.boundaryField()[patchI]
                        *mesh.Sf().boundaryField()[patchI]
                    );
                
                vector viscousForce = gSum
                    (
                        - mu*U.boundaryField()[patchI].snGrad()*
                        mesh.magSf().boundaryField()[patchI]
                    );
                
                vals[i]=pressureForce+viscousForce;
            }
        }        
    } else {
        IOdictionary transportProperties
            (
                IOobject
                (
                    "transportProperties",
                    "constant",
                    mesh,
                    IOobject::MUST_READ,
                    IOobject::NO_WRITE
                )
            );

        dimensionedScalar nu
            (
                transportProperties.lookup("nu")
            );
        
        forAll(patchIndizes_,i) {
            label patchI=patchIndizes_[i];
            
            if(patchI>=0) {
                vector pressureForce=gSum
                    (
                        p.boundaryField()[patchI]
                        *mesh.Sf().boundaryField()[patchI]
                    );
                
                vector viscousForce = gSum
                    (
                        - nu.value()*U.boundaryField()[patchI].snGrad()*
                        mesh.magSf().boundaryField()[patchI]
                    );
                
                vals[i]=pressureForce+viscousForce;
            }
        }
    }    

    forAll(vals,i) {
        reduce(vals[i],sumOp<vector>());
        vals[i]*=factor();
    }

    if (Pstream::master())
    {
        unsigned int w = IOstream::defaultPrecision() + 7;

        OFstream& probeStream = *filePtrs_["force"];

        probeStream << setw(w) << p.time().value();

        forAll(vals, probeI)
        {
            probeStream << setw(w) << vals[probeI];
        }
        probeStream << nl;
    }

    if(verbose()) {
        Info << " Forces: ";

        forAll(patchNames_, patchI)
        {
            Info << "  " << patchNames_[patchI] << " = " 
                << vals[patchI];
        }

        Info << endl;
    }
    
}

    //- Names of the files
wordList patchForceFunctionObject::fileNames()
{
    return wordList(1,"force");
}

word patchForceFunctionObject::dirName()
{
    return word("patchForces");
}


} // namespace Foam

// ************************************************************************* //
