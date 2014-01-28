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
    IncompressibleCloud

Description

 ICE Revision: $Id: IncompressibleCloudIO.C 7092 2007-01-25 21:38:27Z bgschaid $ 
\*---------------------------------------------------------------------------*/

#include "IncompressibleCloud.H"
#include "IOstreams.H"

namespace Foam {
  // * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

  // construct from Istream


  // * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

  Istream& operator>>(Istream& is, IncompressibleCloud&)
  {
    // Check state of Istream
    is.check
      (
       "Istream& operator>>(Istream&, IncompressibleCloud&)"
       );

    return is;
  }


  Ostream& operator<<(Ostream& os, const IncompressibleCloud&)
  {
    // Check state of Ostream
    os.check
      (
       "Ostream& operator<<(Ostream&, "
       "const IncompressibleCloud&)"
       );

    return os;
  }

  template<>
  void Cloud<HardBallParticle>::writeFields() const
  {
    label np = size();

    IOField<scalar> d(fieldIOobject("d"),np);
    IOField<scalar> m(fieldIOobject("m"),np);
    IOField<vector> U(fieldIOobject("U"),np);

    label i = 0;
    for
      (
       Cloud<HardBallParticle>::const_iterator iter = begin();
       iter != end();
       ++iter, ++i
       )
      {
        const HardBallParticle& p = iter();

        d[i] = p.d_;
        m[i] = p.mass_;
        U[i] = p.U_;
      }

    d.write();
    m.write();
    U.write();
  }

  template<>
  void Cloud<HardBallParticle>::readFields() 
  {
    IOField<scalar> d(fieldIOobject("d"));
    IOField<scalar> m(fieldIOobject("m"));
    IOField<vector> U(fieldIOobject("U"));

    label i = 0;
    for
      (
       Cloud<HardBallParticle>::iterator iter = begin();
       iter != end();
       ++iter, ++i
       )
      {
        HardBallParticle& p = iter();

	p.d_ = d[i];
	p.mass_ = m[i];
	p.U_ = U[i];

        p.calculateDerived();  // should not be necessary because the mass is alread read
      }

  }
} //namespace Foam

// ************************************************************************* //
