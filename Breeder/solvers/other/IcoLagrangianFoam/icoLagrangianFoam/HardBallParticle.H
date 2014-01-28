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
  HardBallParticle

  Description

  SourceFiles
  HardBallParticleI.H
  HardBallParticle.C
  HardBallParticleIO.C

  \*---------------------------------------------------------------------------*/

#ifndef HardBallParticle_H
#define HardBallParticle_H

#include "particle.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

  // Class forward declarations
  class IncompressibleCloud;

  /*---------------------------------------------------------------------------*\
    Class HardBallParticle Declaration
    \*---------------------------------------------------------------------------*/

  class HardBallParticle
    :
    public particle<HardBallParticle>
  {
    // Private data

    scalar d_;

    scalar mass_;

    vector U_;

    // Private Member Functions

    //         //- Disallow default bitwise copy construct
    //         HardBallParticle(const HardBallParticle&);

    //- Disallow default bitwise assignment
    void operator=(const HardBallParticle&);

    void calculateDerived();

    void updateProperties(
			  const scalar deltaT,
			  IncompressibleCloud &data,
			  const label cellI,
			  const label faceI
			  );

  public:

    friend class Cloud<HardBallParticle>;
    // Static data members

    //- Static data someStaticData
    static  scalar density;


    // Constructors

    //- Construct from components
    HardBallParticle( 
		     const Cloud<HardBallParticle>& cloud,
		     const vector& position,
		     const label celli,
		     const scalar& d,
		     const vector &U
		     );

    //- Construct from Istream reading field values if required
    HardBallParticle
    (
     const Cloud<HardBallParticle>& cloud,
     Istream& is,
     bool readFields = true
     );

    class iNew
    {
      const Cloud<HardBallParticle>& cloud_;

    public:

      iNew(const Cloud<HardBallParticle>& cloud)
	:
	cloud_(cloud)
      {}

      autoPtr<HardBallParticle> operator()(Istream& is) const
      {
	return autoPtr<HardBallParticle>(new HardBallParticle(cloud_, is));
      }
    };

    // Destructor

    ~HardBallParticle();


    // Member Functions

    bool move(IncompressibleCloud &data);

    // Access

    scalar& d()  {return d_;};
    scalar& m()  {return mass_;};
    vector& U()  {return U_;};

    // Check

    // Edit

    // Write


    // Member Operators

    //        void operator=(const HardBallParticle&);


    // Friend Functions

    // Friend Operators

    // IOstream Operators

    friend Ostream& operator<<(Ostream&, const HardBallParticle&);
  };


  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "HardBallParticleI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
