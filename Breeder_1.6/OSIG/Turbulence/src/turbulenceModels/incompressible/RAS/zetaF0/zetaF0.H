/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2004-2011 OpenCFD Ltd.
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

Class
    Foam::incompressible::RASModels::zetaF0

Description
    Incompressible k-eps-zeta-f0 turbulence model with elliptic relaxation.

    Model described in the paper:
    \verbatim
        "OpenFOAM Implementation of an Incompressible Eddy Viscosity Turbulence Model
        with Zero Wall Boundary Condition Elliptic Relaxation Function"

        Mirza Popovac

        7th OpenFOAM Workshop, 25-28 June 2012, Darmstadt, Germany.
    \endverbatim

    The default model coefficients correspond to the following:
    \verbatim
        zetaF0Coeffs
        {
            Cmu        0.22;
            sigmaK     1.0;
            sigmaEps   1.3;
            sigmaZeta  1.2;
            Ceps10     1.4;
            Ceps11     0.012;
            Ceps2      1.9;
            Cf1        1.4;
            Cf2        0.65;
            Ceta       85.0;
            CL         0.36;
            Ctau       6.0;
            CT         0.6;
        }
    \endverbatim

SourceFiles
    zetaF0.C

\*---------------------------------------------------------------------------*/

#ifndef zetaF0_H
#define zetaF0_H

#include "RASModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace incompressible
{
namespace RASModels
{

/*---------------------------------------------------------------------------*\
                           Class zetaF0 Declaration
\*---------------------------------------------------------------------------*/

class zetaF0
:
    public RASModel
{

protected:

    // Protected data

        // Model coefficients

        dimensionedScalar Cmu_;
        dimensionedScalar sigmaK_;
        dimensionedScalar sigmaEps_;
        dimensionedScalar sigmaZeta_;
        dimensionedScalar Ceps10_;
        dimensionedScalar Ceps11_;
        dimensionedScalar Ceps2_;
        dimensionedScalar Cf1_;
        dimensionedScalar Cf2_;
        dimensionedScalar Ceta_;
        dimensionedScalar CL_;
        dimensionedScalar Ctau_;
        dimensionedScalar CT_;

        // Fields

            volScalarField k_;
            volScalarField epsilon_;
            volScalarField zeta_;
            volScalarField f0_;

            // Local limiters
            dimensionedScalar zetaMin_;
            dimensionedScalar f0Min_;
	    dimensionedScalar TinvMin_;
            dimensionedScalar TscMin_;
            dimensionedScalar LscMin_;

            volScalarField nut_;

    // Protected Member Functions

        tmp<volScalarField> TimeScale() const;
        tmp<volScalarField> LengthScale() const;


public:

    //- Runtime type information
    TypeName("zetaF0");

    // Constructors

        //- Construct from components
        zetaF0
        (
            const volVectorField& U,
            const surfaceScalarField& phi,
            transportModel& transport
        );


    //- Destructor
    virtual ~zetaF0()
    {}


    // Member Functions

        //- Return the turbulence viscosity
        virtual tmp<volScalarField> nut() const
        {
            return nut_;
        }

        //- Return the effective diffusivity for k
        tmp<volScalarField> DkEff() const
        {
            return tmp<volScalarField>
            (
                new volScalarField("DkEff", nut_/sigmaK_ + nu())
            );
        }

        //- Return the effective diffusivity for epsilon
        tmp<volScalarField> DepsilonEff() const
        {
            return tmp<volScalarField>
            (
                new volScalarField("DepsilonEff", nut_/sigmaEps_ + nu())
            );
        }

        //- Return the effective diffusivity for zeta
        tmp<volScalarField> DzetaEff() const
        {
            return tmp<volScalarField>
            (
                new volScalarField("DzetaEff", nut_/sigmaZeta_ + nu())
            );
        }

        //- Return the turbulence kinetic energy
        virtual tmp<volScalarField> k() const
        {
            return k_;
        }

        //- Return the turbulence kinetic energy dissipation rate
        virtual tmp<volScalarField> epsilon() const
        {
            return epsilon_;
        }

        //- Return the normalized turbulent fluctuations
        virtual tmp<volScalarField> zeta() const
        {
            return zeta_;
        }

        //- Return the elliptic relaxation function
        virtual tmp<volScalarField> f0() const
        {
            return f0_;
        }

        //- Return the Reynolds stress tensor
        virtual tmp<volSymmTensorField> R() const;

        //- Return the effective stress tensor including the laminar stress
        virtual tmp<volSymmTensorField> devReff() const;

        //- Return the source term for the momentum equation
        virtual tmp<fvVectorMatrix> divDevReff(volVectorField& U) const;

        //- Solve the turbulence equations and correct the turbulence viscosity
        virtual void correct();

        //- Read RASProperties dictionary
        virtual bool read();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace RASModels
} // End namespace incompressible
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
