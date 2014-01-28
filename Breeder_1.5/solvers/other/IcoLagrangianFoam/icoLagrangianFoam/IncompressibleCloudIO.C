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

  void IncompressibleCloud::writeFields() const
  {
      HardBallParticle::writeFields(*this);
  }
} //namespace Foam

// ************************************************************************* //
