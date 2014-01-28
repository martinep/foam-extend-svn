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

  \*----------------------------------------------------------------------------*/

#include "IncompressibleCloud.H"
#include "processorPolyPatch.H"

namespace Foam {

  // * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


  // * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //


  // Construct from components
  IncompressibleCloud::IncompressibleCloud(
					   const volPointInterpolation& vpi,
					   const volVectorField& U
					   )
    :
    Cloud<HardBallParticle>(U.mesh()),
    runTime_(U.time()),
    time0_(runTime_.value()),
    mesh_(U.mesh()),
    volPointInterpolation_(vpi),
    U_(U),
    smoment_(mesh_.nCells(), vector::zero),
    random(666),
    cloudProperties_
    (
     IOobject
     (
      "cloudProperties",
      U.time().constant(),
      U.db(),
      IOobject::MUST_READ,
      IOobject::NO_WRITE
      )
     ),
    interpolationSchemes_(cloudProperties_.subDict("interpolationSchemes"))
  {
    g_=cloudProperties_.lookup("g");
    HardBallParticle::density=readScalar(cloudProperties_.lookup("density"));
    dragCoefficient_=readScalar(cloudProperties_.lookup("drag"));
    subCycles_=readScalar(cloudProperties_.lookup("subCycles"));
    useSourceMoment=readBool(cloudProperties_.lookup("useMomentumSource"));

    dictionary injection(cloudProperties_.subDict("injection"));
    thres=readScalar(injection.lookup("thres"));
    center=injection.lookup("center");
    r0=readScalar(injection.lookup("r0"));
    vel0=readScalar(injection.lookup("vel0"));
    vel1=injection.lookup("vel1");
    d0=readScalar(injection.lookup("d0"));
    d1=readScalar(injection.lookup("d1"));
    tStart=readScalar(injection.lookup("tStart"));
    tEnd=readScalar(injection.lookup("tEnd"));

    dictionary wall(cloudProperties_.subDict("wall"));
    wallReflect_=readBool(wall.lookup("reflect"));
    if(wallReflect_) {
      wallElasticity_=readScalar(wall.lookup("elasticity"));
    }
  }



  // * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

  // * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

  IncompressibleCloud::~IncompressibleCloud()
  {}


  // * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //
  
  void IncompressibleCloud::evolve() {
    smoment_.setSize(U_.size());

    resetCounters();
    label particles=size();

    UInterpolator_ = interpolation<vector>::New
      (
       interpolationSchemes_,
       volPointInterpolation_,
       U_
       );

    move();
    inject();  

    UInterpolator_.clear();

    reduce(particles, sumOp<label>());
    reduce(wallCollisions_, sumOp<label>());
    reduce(leavingModel_, sumOp<label>());
    reduce(injectedInModel_, sumOp<label>());
    reduce(changedProzessor_, sumOp<label>());

    Info << particles << " Particles moved. " << wallCollisions_ << " walls hit. " << leavingModel_ << " particles left the model. " ;
    if(injectedInModel_) {
        Info << injectedInModel_ << " particles injected. ";
    }
    if(changedProzessor_) {
        Info << changedProzessor_ << " particles changed the processor. ";
    }
    Info << endl;
  }

  void IncompressibleCloud::move() {
    smoment_ = vector::zero;

    Cloud<HardBallParticle>::move(*this);
  }

  void IncompressibleCloud::inject() {
    if(runTime_.time().value()<tStart || runTime_.time().value()>tEnd) {
      return;
    }

    scalar prop=random.scalar01();

    if(prop<thres) {
      vector tmp=(random.vector01()-vector(0.5,0.5,0.5))*2;
      vector pos=center+tmp*r0;

      tmp=vector(random.GaussNormal(),random.GaussNormal(),random.GaussNormal())/sqrt(3.);
      vector vel=tmp*vel0+vel1;

      scalar d=fabs(random.GaussNormal())*d1+d0;

      label cellI=mesh_.findCell(pos);

      if(cellI>=0) {
	HardBallParticle* ptr=new HardBallParticle(*this,pos,cellI,d,vel);
        
        ptr->stepFraction() = 1;

	addParticle(ptr);
        
        injectedInModel_++;
      }
    }
  }

  // * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //


  // * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //


  // * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

} // namespace Foam

#include "IncompressibleCloudIO.C"

// ************************************************************************* //
