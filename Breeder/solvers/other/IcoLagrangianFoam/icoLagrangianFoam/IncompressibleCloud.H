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
#include "Random.H"


#include "HardBallParticle.H"
#include "volPointInterpolation.H"
#include "interpolation.H"

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

    // References to the database and meshes

    const Time& runTime_;
    scalar time0_;
    const fvMesh& mesh_;
    const volPointInterpolation& volPointInterpolation_;


    // References to the physical fields

    const volVectorField& U_;

    vectorField smoment_;
    bool useSourceMoment;

    //- Acceleration due to gravity
    vector g_;

    scalar subCycles_;

    Random random;

    // Injection stuff
    scalar thres;
    vector center;
    scalar r0;
    scalar vel0;
    vector vel1;
    scalar d0;
    scalar d1;
    scalar tStart;
    scalar tEnd;

    // ReflectionStuff
    bool wallReflect_;
    scalar wallElasticity_;

    // counters for the statistics
    label wallCollisions_;
    label leavingModel_;
    label injectedInModel_;
    label changedProzessor_;
    
    void resetCounters() {
      wallCollisions_=0;
      leavingModel_=0;
      injectedInModel_=0;
      changedProzessor_=0;
    }

    // Other stuff
    scalar dragCoefficient_;

    IOdictionary cloudProperties_;

    dictionary interpolationSchemes_;

    autoPtr<interpolation<vector> > UInterpolator_;
  
    // Private Member Functions

    //- Disallow default bitwise copy construct
    IncompressibleCloud(const IncompressibleCloud&);

    //- Disallow default bitwise assignment
    void operator=(const IncompressibleCloud&);


  public:


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
    void move();

    //- Inject more parcels
    void inject();

    // Access
    const interpolation<vector>& UInterpolator() const {return UInterpolator_; }
    const Time &runTime() const {return runTime_; }
    const vector &g() const { return g_; }
    const scalar &dragCoefficient() const { return dragCoefficient_; }
    const scalar &subCycles() const { return subCycles_; }
    const scalar &wallElasticity() const { return wallElasticity_; }
    const bool &wallReflect() const { return wallReflect_; }
    vectorField &smoment() { return smoment_; }

    void countChangedProzessor() {changedProzessor_++;}
    void countLeaving() { leavingModel_++; }
    void countWall() { wallCollisions_++; }

    inline tmp<volVectorField> momentumSource() const;

    // Check

    // Edit

    // Write

    // Member Operators

    // Friend Functions

    // Friend Operators

    // IOstream Operators

  };


  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "IncompressibleCloudI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
