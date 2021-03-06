/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2008 Franz Blaim All rights reserved
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

Authors
    Franz Blaim

\*---------------------------------------------------------------------------*/ 

#include "domainScalingFvPatchField.H"
#include "fvPatchField.H"



// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

template<class Type> 
void domainScalingFvPatchField<Type>::operator=(const UList<Type>& ul) 
{
//    if(bzeroGradient) 
        fvPatchField<Type>::operator=(ul ); 
}

template<class Type> 
void domainScalingFvPatchField<Type>::operator=(const fvPatchField<Type>& ptf) 
{
//    if(bzeroGradient) 
        fvPatchField<Type>::operator=( ptf ); 
}

template<class Type>
void  domainScalingFvPatchField<Type>::operator+=(const fvPatchField<Type>& ptf) 
{
    if(bzeroGradient)
        fvPatchField<Type>::operator+=(ptf);
}

template<class Type>
void  domainScalingFvPatchField<Type>::operator-=(const fvPatchField<Type>& ptf)
{
//    if(bzeroGradient)
        fvPatchField<Type>::operator-=(ptf);
}

template<class Type>
void  domainScalingFvPatchField<Type>::operator*=(const fvPatchField<scalar>& ptf) 
{
    if(bzeroGradient)
        fvPatchField<Type>::operator*=(ptf);
    
}

template<class Type>
void  domainScalingFvPatchField<Type>::operator/=(const fvPatchField<scalar>& ptf) 
{
    if(bzeroGradient)
        fvPatchField<Type>::operator/=(ptf);
}

template<class Type>
void  domainScalingFvPatchField<Type>::operator+=(const Field<Type>& tf) 
{
    if(bzeroGradient)
        fvPatchField<Type>::operator+=(tf);
}

template<class Type>
void  domainScalingFvPatchField<Type>::operator-=(const Field<Type>& tf) 
{
    if(bzeroGradient)
        fvPatchField<Type>::operator-=(tf);
    
}

template<class Type>
void  domainScalingFvPatchField<Type>::operator*=(const Field<scalar>& tf ) 
{
    if(bzeroGradient)
        fvPatchField<Type>::operator*=(tf);
}

template<class Type>
void  domainScalingFvPatchField<Type>::operator/=(const Field<scalar>& tf) 
{
    if(bzeroGradient)
        fvPatchField<Type>::operator/=(tf);
}

template<class Type>
void  domainScalingFvPatchField<Type>::operator=(const Type& t) 
{
    if(bzeroGradient)
        fvPatchField<Type>::operator=(t);
}

template<class Type>
void  domainScalingFvPatchField<Type>::operator+=(const Type& t) 
{
    if(bzeroGradient)
        fvPatchField<Type>::operator+=(t);
}

template<class Type>
void  domainScalingFvPatchField<Type>::operator-=(const Type& t) 
{
    if(bzeroGradient)
        fvPatchField<Type>::operator-=(t);
}

template<class Type>
void  domainScalingFvPatchField<Type>::operator*=(const scalar s) 
{
    if(bzeroGradient)
        fvPatchField<Type>::operator*=(s);
}

template<class Type>
void  domainScalingFvPatchField<Type>::operator/=(const scalar s) 
{
  if(bzeroGradient)   
      fvPatchField<Type>::operator/=(s);
}
        
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //   
