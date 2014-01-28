//  OF-extend Revision: $Id: SolverInfo.C 592 2008-04-21 08:06:44Z bgschaid $ 
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

#include "SolverInfo.H"

#include "objectRegistry.H"
#include "surfaceFields.H"

namespace Foam {

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

    SolverInfo::SolverInfo(const objectRegistry &obr,const dictionary& dict)
:
    phi_(
        dict.found("phi")
        ? word(dict.lookup("phi"))
        : word("phi")
    ),
    compressible_(false),
    turbulent_(false),
    les_(false)
{
    if(obr.foundObject<surfaceScalarField>(phi_)) {
        const surfaceScalarField &phi=obr.lookupObject<surfaceScalarField>(phi_);

        if(phi.dimensions()==dimensionSet(1,0,-1,0,0,0,0)) {
            compressible_=true;
        } else if(phi.dimensions()!=dimensionSet(0,3,-1,0,0,0,0)) {
        WarningIn("SolverInfo::SolverInfo(const dictionary& dict,const objectRegistry &obr)")
            << " Dimensions " << phi.dimensions() 
                << " of the phi-field with name " << phi_ 
                << "don't fit compressible or incompressible " << nl
                << "Assumin incompressible solver" << endl;            
        }
    } else {
        WarningIn("SolverInfo::SolverInfo(const dictionary& dict,const objectRegistry &obr)")
            << "Can't find phi-field with name " << phi_ << nl
                << "Assumin incompressible solver" << endl;
    }

    if (file(obr.time().constantPath()/"turbulenceProperties")) {
        turbulent_=true;

        IOdictionary turbProp(
            IOobject (
                "turbulenceProperties",
                obr.time().constant(),
                obr,
                IOobject::MUST_READ,
                IOobject::NO_WRITE
            )
        );

        bool ransFound=turbProp.found("turbulenceModel");
        bool lesFound=turbProp.found("LESmodel");

        if(ransFound && lesFound) {
            WarningIn("SolverInfo::SolverInfo(const dictionary& dict,const objectRegistry &obr)")
                << "LES and RANS found. Assuming RANS" << endl;
        } else if(lesFound) {
            les_=true;
        } else if(!ransFound && !lesFound) {
            WarningIn("SolverInfo::SolverInfo(const dictionary& dict,const objectRegistry &obr)")
                << "Neither LES nor RANS found. Assuming no turbulence" << endl;
            turbulent_=false;
        }
    }
    // printInfo();
}

void SolverInfo::printInfo()
{
    Info << "phi: " << phi_ << endl;
    Info << "Compressible: " << compressible_ << endl;
    Info << "Turbulent: " << turbulent_ << endl;
    Info << "LES: " << les_ << endl;
}

}

// ************************************************************************* //
