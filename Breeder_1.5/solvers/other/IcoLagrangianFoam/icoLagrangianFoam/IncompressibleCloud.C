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

namespace Foam
{
    defineTypeNameAndDebug(IncompressibleCloud, 0);
};

namespace Foam {

  // * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


  // * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //


  // Construct from components
  IncompressibleCloud::IncompressibleCloud(
					   const volPointInterpolation& vpi,
					   const volVectorField& U
					   )
    :
    Cloud<HardBallParticle>(U.mesh(),false),
    
    constProps_(
        IOdictionary(
            IOobject
            (
                "cloudProperties",
                U.time().constant(),
                U.db(),
                IOobject::MUST_READ,
                IOobject::NO_WRITE
            )
        )
    ),
    runTime_(U.time()),
    time0_(runTime_.value()),
    mesh_(U.mesh()),
    volPointInterpolation_(vpi),
    random_(666),
    U_(U),
    smoment_(mesh_.nCells(), vector::zero),
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
	HardBallParticle::readFields(*this);
  }



  // * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

  // * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

  IncompressibleCloud::~IncompressibleCloud()
  {}


  // * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //
  
  void IncompressibleCloud::evolve() {
    smoment_.setSize(U_.size());
    smoment_ = vector::zero;

    autoPtr<interpolation<vector> > UInt = interpolation<vector>::New
      (
          interpolationSchemes_,
          volPointInterpolation_,
          U_
      );
    
    HardBallParticle::trackData td(*this,UInt());

    label particles=size();

    this->move(td);
    this->inject(td);  

    td.reportCounters(particles);
  }

  void IncompressibleCloud::move(HardBallParticle::trackData &td) {
    smoment_ = vector::zero;

    Cloud<HardBallParticle>::move(td);
  }

  void IncompressibleCloud::inject(HardBallParticle::trackData &td) {
      if(runTime_.time().value()<td.constProps().tStart_ || runTime_.time().value()>td.constProps().tEnd_) {
          return;
      }

      scalar prop=random().scalar01();

      if(prop<td.constProps().thres_) {
          vector tmp=(random().vector01()-vector(0.5,0.5,0.5))*2;
          vector pos=td.constProps().center_+tmp*td.constProps().r0_;
          
          tmp=vector(random().GaussNormal(),random().GaussNormal(),random().GaussNormal())/sqrt(3.);
          vector vel=tmp*td.constProps().vel0_+td.constProps().vel1_;
          
          scalar d=fabs(random().GaussNormal())*td.constProps().d1_+td.constProps().d0_;
          
          label cellI=mesh_.findCell(pos);
          
          if(cellI>=0) {
              HardBallParticle* ptr=new HardBallParticle(*this,pos,cellI,d,vel);
              
              ptr->stepFraction() = 1;
              
              addParticle(ptr);
              
              td.countInject();
          }
      }
  }

  // * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //


  // * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //


  // * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

} // namespace Foam

// ************************************************************************* //
