/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
  \\    /   O peration     |
  \\  /    A nd           | Copyright (C) 1991-2005 OpenCFD Ltd.
  \\/     M anipulation  |
  -------------------------------------------------------------------------------
  License
  This file is part of OpenFOAM.

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
  IncompressibleCloud

  Description

  SourceFiles
  IncompressibleCloudI.H
  IncompressibleCloud.C
  IncompressibleCloudIO.C

  \*---------------------------------------------------------------------------*/

#ifndef IncompressibleCloud_H
#define IncompressibleCloud_H

#include "Cloud.H"


#include "HardBallParticle.H"
#include "volPointInterpolation.H"
#include "interpolation.H"
#include "Random.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{


  /*---------------------------------------------------------------------------*\
    Class IncompressibleCloud Declaration
    \*---------------------------------------------------------------------------*/

  class IncompressibleCloud
    :
    public Cloud<HardBallParticle>
  {
    // Private data
    HardBallParticle::constantProperties constProps_;

    // References to the database and meshes

    const Time& runTime_;
    scalar time0_;
    const fvMesh& mesh_;
    const volPointInterpolation& volPointInterpolation_;

      Random random_;

    // References to the physical fields

    const volVectorField& U_;

    vectorField smoment_;

    IOdictionary cloudProperties_;

    dictionary interpolationSchemes_;

    // Private Member Functions

    //- Disallow default bitwise copy construct
    IncompressibleCloud(const IncompressibleCloud&);

    //- Disallow default bitwise assignment
    void operator=(const IncompressibleCloud&);


  public:

    TypeName("IncompressibleCloud");

    // Constructors

    //- Construct null
    IncompressibleCloud(            
			const volPointInterpolation& vpi,
			const volVectorField& U
			);


    // Destructor

    ~IncompressibleCloud();


    // Member Functions

    //- Evolve the spray (move, inject and breakup)
    void evolve();

    //- Move the spray parcels
    void move(HardBallParticle::trackData &td);

    //- Inject more parcels
    void inject(HardBallParticle::trackData &td);

    // Access
    const Time &runTime() const {return runTime_; }
    vectorField &smoment() { return smoment_; }
    Random &random() { return random_; }

    const HardBallParticle::constantProperties &constProps() const { return constProps_; }

    inline tmp<volVectorField> momentumSource() const;

      void writeFields() const;
  };


  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "IncompressibleCloudI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
