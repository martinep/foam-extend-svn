/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2004-2010 OpenCFD Ltd.
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "zetaF0.H"
#include "addToRunTimeSelectionTable.H"

#include "backwardsCompatibilityWallFunctions.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace incompressible
{
namespace RASModels
{

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(zetaF0, 0);
addToRunTimeSelectionTable(RASModel, zetaF0, dictionary);

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

tmp<volScalarField> zetaF0::TimeScale() const
{
    return max(min(k_/(epsilon_ + epsilonSmall_),
                   CT_/(sqrt(6*2*magSqr(dev(symm(fvc::grad(U_)))))*Cmu_*zeta_+TinvMin_)),
                   Ctau_*sqrt(nu()/(epsilon_ + epsilonSmall_)));
}

tmp<volScalarField> zetaF0::LengthScale() const
{
    return CL_*max(min(pow(k_,1.5)/(epsilon_ + epsilonSmall_),
                       sqrt(k_)/(sqrt(6*2*magSqr(dev(symm(fvc::grad(U_)))))*Cmu_*zeta_+TinvMin_)),
                       Ceta_*pow(pow(nu(),3.0)/(epsilon_ + epsilonSmall_),0.25));
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

zetaF0::zetaF0
(
    const volVectorField& U,
    const surfaceScalarField& phi,
    transportModel& lamTransportModel
)
:
    RASModel(typeName, U, phi, lamTransportModel),

    Cmu_
    (
        dimensioned<scalar>::lookupOrAddToDict
        (
            "Cmu",
            coeffDict_,
            0.22
        )
    ),
    sigmaK_
    (
        dimensioned<scalar>::lookupOrAddToDict
        (
            "sigmaK",
            coeffDict_,
            1.0
        )
    ),
    sigmaEps_
    (
        dimensioned<scalar>::lookupOrAddToDict
        (
            "sigmaEps",
            coeffDict_,
            1.3
        )
    ),
    sigmaZeta_
    (
        dimensioned<scalar>::lookupOrAddToDict
        (
            "sigmaZeta",
            coeffDict_,
            1.2
        )
    ),
    Ceps10_
    (
        dimensioned<scalar>::lookupOrAddToDict
        (
            "Ceps10",
            coeffDict_,
            1.4
        )
    ),
    Ceps11_
    (
        dimensioned<scalar>::lookupOrAddToDict
        (
            "Ceps11",
            coeffDict_,
            0.012
        )
    ),
    Ceps2_
    (
        dimensioned<scalar>::lookupOrAddToDict
        (
            "Ceps2",
            coeffDict_,
            1.9
        )
    ),
    Cf1_
    (
        dimensioned<scalar>::lookupOrAddToDict
        (
            "Cf1",
            coeffDict_,
            1.4
        )
    ),
    Cf2_
    (
        dimensioned<scalar>::lookupOrAddToDict
        (
            "Cf2",
            coeffDict_,
            0.65
        )
    ),
    Ceta_
    (
        dimensioned<scalar>::lookupOrAddToDict
        (
            "Ceta",
            coeffDict_,
            85.0
        )
    ),
    CL_
    (
        dimensioned<scalar>::lookupOrAddToDict
        (
            "CL",
            coeffDict_,
            0.36
        )
    ),
    Ctau_
    (
        dimensioned<scalar>::lookupOrAddToDict
        (
            "Ctau",
            coeffDict_,
            6.0
        )
    ),
    CT_
    (
        dimensioned<scalar>::lookupOrAddToDict
        (
            "CT",
            coeffDict_,
            0.6
        )
    ),

    k_
    (
        IOobject
        (
            "k",
            runTime_.timeName(),
            mesh_,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        autoCreateK("k", mesh_)
    ),
    epsilon_
    (
        IOobject
        (
            "epsilon",
            runTime_.timeName(),
            mesh_,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        autoCreateEpsilon("epsilon", mesh_)
    ),
    zeta_
    (
        IOobject
        (
            "zeta",
            runTime_.timeName(),
            mesh_,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh_
    ),

    f0_
    (
        IOobject
        (
            "f0",
            runTime_.timeName(),
            mesh_,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh_
    ),

    zetaMin_("zetaMin", dimless, SMALL),
    f0Min_("f0Min", dimless/dimTime, SMALL),
    TinvMin_("TinvMin", dimless/dimTime, SMALL),
    TscMin_("TscMin", dimTime, SMALL),
    LscMin_("LscMin", dimLength, SMALL),

    nut_
    (
        IOobject
        (
            "nut",
            runTime_.timeName(),
            mesh_,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        autoCreateNut("nut", mesh_)
    )
{
    bound(k_, k0_);
    bound(epsilon_, epsilon0_);
    bound(zeta_, zetaMin_);
    bound(f0_, f0Min_);

    nut_ = Cmu_*k_*zeta_*TimeScale();
    nut_.correctBoundaryConditions();

    printCoeffs();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tmp<volSymmTensorField> zetaF0::R() const
{
    return tmp<volSymmTensorField>
    (
        new volSymmTensorField
        (
            IOobject
            (
                "R",
                runTime_.timeName(),
                mesh_,
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            ((2.0/3.0)*I)*k_ - nut_*twoSymm(fvc::grad(U_)),
            k_.boundaryField().types()
        )
    );
}


tmp<volSymmTensorField> zetaF0::devReff() const
{
    return tmp<volSymmTensorField>
    (
        new volSymmTensorField
        (
            IOobject
            (
                "devRhoReff",
                runTime_.timeName(),
                mesh_,
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
           -nuEff()*dev(twoSymm(fvc::grad(U_)))
        )
    );
}


tmp<fvVectorMatrix> zetaF0::divDevReff(volVectorField& U) const
{
    return
    (
      - fvm::laplacian(nuEff(), U)
//    - fvc::div(nuEff()*dev(T(fvc::grad(U))))
      - fvc::div(nuEff()*dev(fvc::grad(U)().T()))
    );
}


bool zetaF0::read()
{
    if (RASModel::read())
    {
        Cmu_.readIfPresent(coeffDict());
        sigmaK_.readIfPresent(coeffDict());
        sigmaEps_.readIfPresent(coeffDict());
        sigmaZeta_.readIfPresent(coeffDict());
        Ceps10_.readIfPresent(coeffDict());
        Ceps11_.readIfPresent(coeffDict());
        Ceps2_.readIfPresent(coeffDict());
        Cf1_.readIfPresent(coeffDict());
        Cf2_.readIfPresent(coeffDict());
        Ceta_.readIfPresent(coeffDict());
        CL_.readIfPresent(coeffDict());
        Ctau_.readIfPresent(coeffDict());
        CT_.readIfPresent(coeffDict());

        return true;
    }
    else
    {
        return false;
    }
}


void zetaF0::correct()
{
    Info << "Solving zetaF0 elliptic relaxation model" << endl;

    RASModel::correct();

    if (!turbulence_)
    {
        return;
    }

    const volTensorField gradU(fvc::grad(U_));
    const volScalarField S2(2*magSqr(dev(symm(gradU))));
//    const volScalarField magS(sqrt(S2));

    volScalarField TimeScale_ = (TimeScale() + TscMin_);
    volScalarField LengthScale_ = (LengthScale() + LscMin_);

    volScalarField G("RASModel::G", nut_*S2);

    // Update epsilon and G at the wall
    epsilon_.boundaryField().updateCoeffs();


    // Dissipation equation
    tmp<fvScalarMatrix> epsEqn
    (
        fvm::ddt(epsilon_)
      + fvm::div(phi_, epsilon_)
      - fvm::Sp(fvc::div(phi_), epsilon_)
      - fvm::laplacian(DepsilonEff(), epsilon_)
     ==
        Ceps10_*(scalar(1.0)+Ceps11_/(zeta_+zetaMin_))*G/TimeScale_
      - fvm::Sp
        (
            Ceps2_/TimeScale_,
            epsilon_
        )
    );

    epsEqn().relax();

    epsEqn().boundaryManipulate(epsilon_.boundaryField());

    solve(epsEqn);
    bound(epsilon_, epsilon0_);


    // Turbulent kinetic energy equation
    tmp<fvScalarMatrix> kEqn
    (
        fvm::ddt(k_)
      + fvm::div(phi_, k_)
      - fvm::Sp(fvc::div(phi_), k_)
      - fvm::laplacian(DkEff(), k_)
     ==
        G
//    - fvm::Sp(epsilon_/k_, k_)
      - fvm::Sp
        (
            1.0/TimeScale_,
            k_
        )
    );

    kEqn().relax();
    solve(kEqn);
    bound(k_, k0_);


    // f0 equation
    tmp<fvScalarMatrix> f0Eqn
    (
      - fvm::laplacian(f0_)
     ==
      - fvm::Sp
        (
            scalar(1.0)/sqr(LengthScale_),
            f0_
        )
      -
        (
            (
                Cf1_-scalar(1.0)+
                Cf2_*G/(epsilon_+epsilonSmall_)
            )*(zeta_-scalar(2.0/3.0))+zeta_
        )/(sqr(LengthScale_)*TimeScale_)
      
    );

    f0Eqn().relax();
    solve(f0Eqn);
    bound(f0_, f0Min_);


    // Zeta equation
    tmp<fvScalarMatrix> zetaEqn
    (
        fvm::ddt(zeta_)
      + fvm::div(phi_, zeta_)
      - fvm::Sp(fvc::div(phi_), zeta_)
      - fvm::laplacian(DzetaEff(), zeta_)
     ==
        f0_ 
      - fvm::Sp
        (
            (G+epsilon_)/k_,
            zeta_
        )
    );

    zetaEqn().relax();
    solve(zetaEqn);
    bound(zeta_, zetaMin_);


    // Re-calculate viscosity
    nut_ = Cmu_*k_*zeta_*TimeScale_;
    nut_.correctBoundaryConditions();


    Info << "Solved zetaF0 elliptic relaxation model" << endl;

}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace RASModels
} // End namespace incompressible
} // End namespace Foam

// ************************************************************************* //
