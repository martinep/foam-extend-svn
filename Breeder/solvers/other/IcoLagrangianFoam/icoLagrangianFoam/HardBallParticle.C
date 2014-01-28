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

  defineParticleTypeNameAndDebug(HardBallParticle, 0);

  // * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

  scalar HardBallParticle::density=1.;;


  // * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


  // * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //


  // Construct from components
  HardBallParticle::HardBallParticle(const Cloud<HardBallParticle>& cloud,
				     const vector& position,
				     const label celli,
				     const scalar& d,
				     const vector &U
				     )
    :
    particle<HardBallParticle>(cloud,position,celli),
    d_(d),
    mass_(0.),
    U_(U)
  {
    calculateDerived();
  }

  void HardBallParticle::calculateDerived() {
    mass_=density*4./3.*3.1415*d_*d_*d_/8.;
  }

  HardBallParticle::HardBallParticle
  (
   const Cloud<HardBallParticle>& cloud,
   Istream& is,
   bool readFields
   )
    :
      particle<HardBallParticle>(cloud, is)
  {
    if (readFields)
      {
        if (is.format() == IOstream::ASCII)
	  {
            d_ = readScalar(is);
            mass_ = readScalar(is);
            is >> U_;
	  }
        else
	  {
              is.read(reinterpret_cast<char*>(&d_),sizeof(d_));
              is.read(reinterpret_cast<char*>(&mass_),sizeof(mass_));
              is.read(reinterpret_cast<char*>(&U_),sizeof(U_));
	  }

        calculateDerived(); // should not be necessary because the mass is alread read
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
					  IncompressibleCloud &data,
					  const label cellI,
					  const label faceI
					  ) {
    vector Upos=data.UInterpolator().interpolate(position(),cellI,faceI);

    scalar relax=1/(data.dragCoefficient()*(d_*d_)/mass_);
    scalar coeff=dt/relax;
#ifdef DEBUG_MOVE
    Info << "Gas velocity: " << Upos << "( " << relax << " , " << coeff << ")" << endl;
    vector Uold=U();
#endif

    U()=( U() + coeff*Upos + data.g()*dt)/(1. + coeff);
#ifdef DEBUG_MOVE
    Info << Uold << " - > " << U() << endl;
#endif
  }

  bool HardBallParticle::move(IncompressibleCloud &data) {
#ifdef DEBUG_MOVE
    Info << "=======" << endl;
#endif

    bool keepParticle=true;
    scalar deltaT=data.runTime().deltaT().value();
    const polyMesh &mesh=cloud().pMesh();
    const polyBoundaryMesh &pbMesh=mesh.boundaryMesh();

 // set the end-time for the track
    scalar tEnd = (1.0 - stepFraction())*deltaT;

    scalar dtMax=max(tEnd/data.subCycles(),tEnd*1.e-4);

#ifdef DEBUG_MOVE
    Info << "Before: " << position() << " \t " << U() << endl;
    Info << "Time: " << tEnd << "\t" << deltaT << "\t" << dtMax  << endl;
#endif

    bool switchProcessor = false;  //added
    vector planeNormal = vector::zero; //added

    label nIter=0;

    while(keepParticle && (tEnd>SMALL) && (!switchProcessor)) {
      scalar dt=min(dtMax,tEnd);
      label cellI=cell();

      if(keepParticle){

      vector toPos=position()+U()*dt;

      dt *= trackToFace(toPos,data);
      tEnd -= dt;

      // Set the current time-step fraction.
      stepFraction() = 1.0 - tEnd/deltaT;
      
#ifdef DEBUG_MOVE
      Info << "Tracked: (" << deltaT << ")\t" << position() << "\t" << stepFraction()  << endl;
#endif

      if(onBoundary()) {
#ifdef DEBUG_MOVE
	Info << "Particle hit boundary patch " << patch(face()) << endl;
#endif
	if (isType<wallPolyPatch>(pbMesh[patch(face())])) {
#ifdef DEBUG_MOVE
	  Info << "Particle hits wall ";
#endif

	  data.countWall();

	  if(data.wallReflect()) {
#ifdef DEBUG_MOVE
	    Info << " is reflected from " << U();
#endif
	    vector Sf = mesh.faceAreas()[face()];
	    Sf /= mag(Sf);
	    scalar Un = U() & Sf;
            
	    if (Un > 0){
	      U() -= (1.0 + data.wallElasticity())*Un*Sf;
	    }
#ifdef DEBUG_MOVE
	    Info << "(" << Sf << " -> " << Un << ") to " << U() << endl;
#endif
	    keepParticle=true;	  
	  } else {
#ifdef DEBUG_MOVE
	    Info << " and dies " << endl;
#endif
	    keepParticle=false;
	  }
	} else if(isType<polyPatch>(pbMesh[patch(face())])) {
#ifdef DEBUG_MOVE
	  Info << "Particle removed (in/outlet) " <<  endl;
#endif

	  data.countLeaving();

	  keepParticle = false;
	}
      }
    
      nIter++;

      }
    
      vector oMom=U()*m();

      updateProperties(deltaT,data,cellI,face());

      vector nMom=U()*m();

      data.smoment()[cellI] += oMom-nMom;

      if(onBoundary() && keepParticle)
        {
          if(face() > -1)
	    {
                if(typeid(pbMesh[patch(face())]) == typeid(processorPolyPatch))
	        {
                    data.countChangedProzessor();
                    switchProcessor = true;
                }
	    }
        }
    }

#ifdef DEBUG_MOVE
    Info << "Time: " << tEnd << endl;
    Info << "After: " << position() << " \t " << U() << endl;
    Info << "Keeping: " << keepParticle << endl;
    Info << "Switching: " << switchProcessor << endl;
#endif
    return keepParticle;
  }

  Ostream& operator<<(Ostream& os, const HardBallParticle& p)
  {

    if (os.format() == IOstream::ASCII)
      {
	os << static_cast<const particle<HardBallParticle>&>(p)
	   << token::SPACE << p.d_
           << token::SPACE << p.mass_
	   << token::SPACE << p.U_;

      } else {
	os << static_cast<const particle<HardBallParticle>&>(p);
        os.write(reinterpret_cast<const char*>(&p.d_),sizeof(p.d_));
        os.write(reinterpret_cast<const char*>(&p.mass_),sizeof(p.mass_));
        os.write(reinterpret_cast<const char*>(&p.U_),sizeof(p.U_));
    }

    // Check state of Ostream
    os.check("operator<<(Ostream& os, const HardBallParticle& p)");

    return os;
  }

  // * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //


  // * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //


  // * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //


} // namespace Foam

// ************************************************************************* //
