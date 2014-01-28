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

#include "Particle.H"
#include "volPointInterpolation.H"
#include "interpolation.H"

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
    public Particle<HardBallParticle>
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

    void calculateDerived(const scalar density);

  public:

      friend class IncompressibleCloud;

      class constantProperties {
      public:
          // This isn't very elegant, but I couldn't be bothered to write accessor-methods
          bool useSourceMoment_;
          
          scalar density_;
          
          //- Acceleration due to gravity
          vector g_;
          
          scalar subCycles_;
          
          // Injection stuff
          scalar thres_;
          vector center_;
          scalar r0_;
          scalar vel0_;
          vector vel1_;
          scalar d0_;
          scalar d1_;
          scalar tStart_;
          scalar tEnd_;
          
          // ReflectionStuff
          bool wallReflect_;
          scalar wallElasticity_;
          
          // Other stuff
          scalar dragCoefficient_;

          constantProperties(const dictionary& dict);          

          const vector &g() const { return g_; }
          const scalar &dragCoefficient() const { return dragCoefficient_; }
          const scalar &subCycles() const { return subCycles_; }
          const scalar &wallElasticity() const { return wallElasticity_; }
          const bool &wallReflect() const { return wallReflect_; }
      };

      class trackData
      :
      public Particle<HardBallParticle>::trackData
      {
          IncompressibleCloud& cloud_;

          const constantProperties &constProps_;

          // counters for the statistics
          label wallCollisions_;
          label leavingModel_;
          label injectedInModel_;
          label changedProzessor_;
          
          interpolation<vector> &UInterpolator_;
   
      public:
          trackData(
              IncompressibleCloud &cloud,
              interpolation<vector> &Uint_
          );

          IncompressibleCloud &cloud() { return cloud_; }

          const constantProperties constProps() const 
              {
                  return constProps_;
              }

          void resetCounters() {
              wallCollisions_=0;
              leavingModel_=0;
              injectedInModel_=0;
              changedProzessor_=0;
          }

          void reportCounters(label particles);

          void countChangedProzessor() {changedProzessor_++;}
          void countLeaving() { leavingModel_++; }
          void countWall() { wallCollisions_++; }
          void countInject() { injectedInModel_++; }

          const interpolation<vector>& UInterpolator() const {return UInterpolator_; }
      };

    // Static data members

    //- Run-time type information
    TypeName("HardBallParticle");

    //- Static data someStaticData

    // Constructors

    //- Construct from components
    HardBallParticle( 
		     const IncompressibleCloud& cloud,
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

    // Destructor

    ~HardBallParticle();

     autoPtr<HardBallParticle> clone() const
        {
            return autoPtr<HardBallParticle>(new HardBallParticle(*this));
        }


    // Member Functions

    bool move(trackData &data);

    void updateProperties(
			  const scalar deltaT,
			  const trackData &data,
			  const label cellI,
			  const label faceI
			  );

    // Access

    scalar& d()  {return d_;};
    scalar& m()  {return mass_;};
    vector& U()  {return U_;};

    static void readFields(IncompressibleCloud &c);

    static void writeFields(const IncompressibleCloud &c);

    friend Ostream& operator<<(Ostream&, const HardBallParticle&);

    void hitWallPatch
    (
        const wallPolyPatch&,
        trackData& td
    );
    void hitWallPatch
    (
        const wallPolyPatch&,
        int& 
    );
    void hitPatch
    (
        const polyPatch&,
        trackData& td
    );
    void hitPatch
    (
        const polyPatch&,
        int& 
    );
    void hitProcessorPatch
    (
        const processorPolyPatch&,
        trackData& td
    );
    void hitProcessorPatch
    (
        const processorPolyPatch&,
        int& 
    );

  };

template<>
inline bool contiguous<HardBallParticle>()
{
    return false;
}


  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "HardBallParticleI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
