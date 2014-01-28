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

  \*----------------------------------------------------------------------------*/

#include "HardBallParticle.H"
#include "IOstreams.H"
#include "IncompressibleCloud.H"
#include "wallPolyPatch.H"
#include "processorPolyPatch.H"

namespace Foam {

  defineTypeNameAndDebug(HardBallParticle, 0);
  defineParticleTypeNameAndDebug(HardBallParticle, 0);
    //  defineParcelTypeNameAndDebug(HardBallParticle, 0);

  defineTemplateTypeNameAndDebug(Cloud<HardBallParticle>, 0);

  // * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //


  // * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


  // * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //


  // Construct from components
  HardBallParticle::HardBallParticle(const IncompressibleCloud& cloud,
				     const vector& position,
				     const label celli,
				     const scalar& d,
				     const vector &U
				     )
    :
    Particle<HardBallParticle>(cloud,position,celli),
    d_(d),
    mass_(0.),
    U_(U)
  {
      calculateDerived(cloud.constProps().density_);
  }
    
    HardBallParticle::constantProperties::constantProperties(const dictionary& dict)
        :     
        useSourceMoment_(readBool(dict.lookup("useMomentumSource"))),
        density_(readScalar(dict.lookup("density"))),
        g_(dict.lookup("g")),
        subCycles_(readScalar(dict.lookup("subCycles"))),
        thres_(readScalar(dict.subDict("injection").lookup("thres"))),
        center_(dict.subDict("injection").lookup("center")),
        r0_(readScalar(dict.subDict("injection").lookup("r0"))),
        vel0_(readScalar(dict.subDict("injection").lookup("vel0"))),
        vel1_(dict.subDict("injection").lookup("vel1")),
        d0_(readScalar(dict.subDict("injection").lookup("d0"))),
        d1_(readScalar(dict.subDict("injection").lookup("d1"))),
        tStart_(readScalar(dict.subDict("injection").lookup("tStart"))),
        tEnd_(readScalar(dict.subDict("injection").lookup("tEnd"))),
        wallReflect_(readBool(dict.subDict("wall").lookup("reflect"))),
        wallElasticity_(  
            wallReflect_ ? 
            readScalar(dict.subDict("wall").lookup("elasticity")) :
            0.
        ),
        dragCoefficient_(readScalar(dict.lookup("drag")))
    {
    }
    
    HardBallParticle::trackData::trackData(
        IncompressibleCloud &cloud,
        interpolation<vector> &Uint
    )
        :
        Particle<HardBallParticle>::trackData(cloud),
    cloud_(cloud),
    constProps_(cloud.constProps()),
    wallCollisions_(0),
    leavingModel_(0),
    injectedInModel_(0),
    changedProzessor_(0),
    UInterpolator_(Uint)
    {
    }

  void HardBallParticle::calculateDerived(const scalar density) {
      mass_=density*4./3.*3.1415*d_*d_*d_/8.;
  }

  HardBallParticle::HardBallParticle
  (
   const Cloud<HardBallParticle>& cloud,
   Istream& is,
   bool readFields
   )
    :
      Particle<HardBallParticle>(cloud, is)
  {
    if (readFields)
      {
        if (is.format() == IOstream::ASCII)
	  {
              is >> d_;
              is >> mass_;
              is >> U_;
	  }
        else
	  {
              is.read(reinterpret_cast<char*>(&d_),sizeof(d_));
              is.read(reinterpret_cast<char*>(&mass_),sizeof(mass_));
              is.read(reinterpret_cast<char*>(&U_),sizeof(U_));
	  }

      }

    is.check("HardBallParticle::HardBallParticle(IStream &");
  }


  // * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

  HardBallParticle::~HardBallParticle()
  {}

  // * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

    // #define DEBUG_MOVE

  void HardBallParticle::updateProperties(
					  const scalar dt,
					  const trackData &data,
					  const label cellI,
					  const label faceI
					  ) {
    vector Upos=data.UInterpolator().interpolate(position(),cellI,faceI);

    scalar relax=1/(data.constProps().dragCoefficient()*(d_*d_)/mass_);
    scalar coeff=dt/relax;
#ifdef DEBUG_MOVE
    Info << "Gas velocity: " << Upos << "( " << relax << " , " << coeff << ")" << endl;
    vector Uold=U();
#endif

    U()=( U() + coeff*Upos + data.constProps().g()*dt)/(1. + coeff);
#ifdef DEBUG_MOVE
    Info << Uold << " - > " << U() << endl;
#endif
  }

    bool HardBallParticle::move(HardBallParticle::trackData &data) {
#ifdef DEBUG_MOVE
    Info << "=======" << endl;
#endif
    scalar deltaT=data.cloud().pMesh().time().deltaT().value();

 // set the end-time for the track
    scalar tEnd = (1.0 - stepFraction())*deltaT;

    scalar dtMax=max(tEnd/data.constProps().subCycles(),tEnd*1.e-4);

#ifdef DEBUG_MOVE
    Info << "Before: " << position() << " \t " << U() << endl;
    Info << "Time: " << tEnd << "\t" << deltaT << "\t" << dtMax  << endl;
#endif

    vector planeNormal = vector::zero; //added

    label nIter=0;

    data.switchProcessor = false;
    data.keepParticle = true;

    while(data.keepParticle && (tEnd>SMALL) && (!data.switchProcessor)) {
      scalar dt=min(dtMax,tEnd);
      label cellI=cell();

      vector toPos=position()+U()*dt;
      
      dt *= trackToFace(toPos,data);
      tEnd -= dt;
      
      // Set the current time-step fraction.
      stepFraction() = 1.0 - tEnd/deltaT;
          
      nIter++;
    
      vector oMom=U()*m();
      
      updateProperties(deltaT,data,cellI,face());

      vector nMom=U()*m();

      data.cloud().smoment()[cellI] += oMom-nMom;
    }

#ifdef DEBUG_MOVE
    Info << "Time: " << tEnd << endl;
    Info << "After: " << position() << " \t " << U() << endl;
    Info << "Keeping: " << keepParticle << endl;
    Info << "Switching: " << switchProcessor << endl;
#endif
    return data.keepParticle;
  }

  Ostream& operator<<(Ostream& os, const HardBallParticle& p)
  {

    if (os.format() == IOstream::ASCII)
      {
	os << static_cast<const Particle<HardBallParticle>&>(p)
	   << token::SPACE << p.d_
           << token::SPACE << p.mass_
	   << token::SPACE << p.U_;

      } else {
	os << static_cast<const Particle<HardBallParticle>&>(p);
        os.write(reinterpret_cast<const char*>(&p.d_),sizeof(p.d_));
        os.write(reinterpret_cast<const char*>(&p.mass_),sizeof(p.mass_));
        os.write(reinterpret_cast<const char*>(&p.U_),sizeof(p.U_));
    }

    // Check state of Ostream
    os.check("operator<<(Ostream& os, const HardBallParticle& p)");

    return os;
  }

    void HardBallParticle::trackData::reportCounters(label particles) {
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

    void HardBallParticle::hitWallPatch
    (
        const wallPolyPatch&,
        trackData& td
    )
    {
        td.countWall();

        if(td.constProps().wallReflect()) {
	    vector Sf = cloud().pMesh().faceAreas()[face()];
	    Sf /= mag(Sf);
	    scalar Un = U() & Sf;
            
	    if (Un > 0){
                U() -= (1.0 + td.constProps().wallElasticity())*Un*Sf;
	    }
	    td.keepParticle=true;	  
	  } else {
	    td.keepParticle=false;
	  }
    } 

    void HardBallParticle::hitWallPatch
    (
        const wallPolyPatch&,
        int& 
    )
    {
    }

    void HardBallParticle::hitPatch
    (
        const polyPatch&,
        trackData& td
    )
    {
        td.keepParticle=false;
        td.countLeaving();
    } 

    void HardBallParticle::hitPatch
    (
        const polyPatch&,
        int& 
    )
    {
    }

    void HardBallParticle::hitProcessorPatch
    (
        const processorPolyPatch&,
        trackData& td
    )
    {
        td.switchProcessor=false;
        td.countChangedProzessor();
    } 

    void HardBallParticle::hitProcessorPatch
    (
        const processorPolyPatch&,
        int& 
    )
    {
    }

    
  // * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //


  // * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //


  // * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //


} // namespace Foam

// ************************************************************************* //
