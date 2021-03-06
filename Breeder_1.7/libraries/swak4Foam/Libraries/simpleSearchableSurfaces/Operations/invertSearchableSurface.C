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
    \\  /    A nd           | Copyright held by original author
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

Contributors/Copyright:
    2009, 2013 Bernhard F.W. Gschaider <bgschaid@ice-sf.at>

 SWAK Revision: $Id:  $
\*---------------------------------------------------------------------------*/

#include "invertSearchableSurface.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{

    defineTypeNameAndDebug(invertSearchableSurface, 0);
    addToRunTimeSelectionTable(searchableSurface, invertSearchableSurface, dict);

}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::invertSearchableSurface::invertSearchableSurface
(
    const IOobject& io,
    const dictionary& dict
)
:
    wrapperSearchableSurface(io,dict)
{
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::invertSearchableSurface::~invertSearchableSurface()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //



void Foam::invertSearchableSurface::getVolumeType
(
    const pointField& points,
    List<volumeType>& volType
) const
{
    delegate().getVolumeType
        (
            points,
            volType
        );

    forAll(volType,i) {
        if(volType[i]==INSIDE) {
            volType[i]=OUTSIDE;
        } else if(volType[i]==OUTSIDE) {
            volType[i]=INSIDE;
        }
    }
}

void Foam::invertSearchableSurface::getNormal
(
    const List<pointIndexHit>& hits,
    vectorField& normal
) const
{
    delegate().getNormal(
        hits,
        normal
    );

    forAll(normal,i) {
        normal[i]=-normal[i];
    }
}

// ************************************************************************* //
