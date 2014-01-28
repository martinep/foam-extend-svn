/*---------------------------------------------------------------------------*\
 ##   ####  ######     | 
 ##  ##     ##         | Copyright: ICE Stroemungsfoschungs GmbH
 ##  ##     ####       |
 ##  ##     ##         | http://www.ice-sf.at
 ##   ####  ######     |
-------------------------------------------------------------------------------
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 1991-2005 OpenCFD Ltd.
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is based on OpenFOAM.

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

 ICE Revision: $Id: IncompressibleCloudIO.C 7092 2007-01-25 21:38:27Z bgschaid $ 
\*---------------------------------------------------------------------------*/

#include "IncompressibleCloud.H"
#include "IOstreams.H"

namespace Foam {
  // * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

  // construct from Istream


  // * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

  void HardBallParticle::writeFields(const IncompressibleCloud &c)
  {
    Particle<HardBallParticle>::writeFields(c);

    label np = c.size();

    IOField<scalar> d(c.fieldIOobject("d"),np);
    IOField<scalar> m(c.fieldIOobject("m"),np);
    IOField<vector> U(c.fieldIOobject("U"),np);

    label i = 0;

    forAllConstIter(IncompressibleCloud,c,iter)
      {
        const HardBallParticle& p = iter();

        d[i] = p.d_;
        m[i] = p.mass_;
        U[i] = p.U_;

        i++;
      }

    d.write();
    m.write();
    U.write();
  }

  void HardBallParticle::readFields(IncompressibleCloud &c) 
  {
    if(!c.size()) {
        return;
    }

    IOField<scalar> d(c.fieldIOobject("d"));
    IOField<scalar> m(c.fieldIOobject("m"));
    IOField<vector> U(c.fieldIOobject("U"));

    label i = 0;
    forAllIter(IncompressibleCloud,c,iter)
      {
        HardBallParticle& p = iter();

	p.d_ = d[i];
	p.mass_ = m[i];
	p.U_ = U[i];

//         p.calculateDerived(c.constProps().density_);  // should not be necessary because the mass is alread read
	i++;
      }
  }

} //namespace Foam

// ************************************************************************* //
