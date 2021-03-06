//  ICE Revision: $Id: ValueExpressionDriverI.H 1846 2010-10-26 19:53:12Z bgschaid $

#ifndef VALUE_EXPRESSION_DRIVER_I_H
#define VALUE_EXPRESSION_DRIVER_I_H

#include "wallFvPatch.H"
#include "fixedValueFvPatchFields.H"
#include "zeroGradientFvPatchFields.H"

template<class T>
T *ValueExpressionDriver::getField(const Foam::string &name)
{
    if(debug) {
        Foam::Info << "ValueExpressionDriver::getField. Name: " << name
        << " Type: " << T::typeName << Foam::endl;
    }

    Foam::dimensionSet nullDim(0,0,0,0,0);

    T *f=NULL;

    if(
        searchInMemory_
        &&
        mesh_.foundObject<T>(name)
        ) {
        if(debug) {
            Foam::Info << "Getting " << name << " from memory" << Foam::endl;
        }

        f=new T(
            mesh_.lookupObject<T>(name)
            );
    } else if(
        searchOnDisc_
        ) {
        if(debug) {
            Foam::Info << "Reading " << name << " from disc" << Foam::endl;
        }
        f=new T(
            Foam::IOobject
            (
                name,
                time_,
                mesh_,
                Foam::IOobject::MUST_READ,
                Foam::IOobject::NO_WRITE
            ),
            mesh_
            );
        if(cacheReadFields_) {
            if(debug) {
                Foam::Info << "Registering a copy of " << name <<
                " with mesh" << Foam::endl;
            }
            T* toCache=new T(*f);
            toCache->store();
        }
    }

    if(f==NULL) {
        Foam::FatalErrorIn(
            "ValueExpressionDriver::getField(const Foam::string &name)")
        << "Could not find the field " << name
        << " in memory or on disc" << Foam::endl
        << abort(Foam::FatalError);
    }

    f->dimensions().reset(nullDim);

    return f;
}

template<class T>
bool ValueExpressionDriver::ValueExpressionDriver::isThere(
    const Foam::string &name)
{
    if(debug) {
        Foam::Info << "ValueExpressionDriver::isThere. Name: " << name
        << " Type: " << T::typeName << Foam::endl;
    }
    if(searchInMemory_) {
        if(mesh_.foundObject<T>(name)) {
            if(debug) {
                Foam::Info << "Found " << name << " in memory" << Foam::endl;
            }
            return true;
        }
    }

    if(
        searchOnDisc_
        &&
        getTypeOfField(name)==T::typeName
        ) {
        if(debug) {
            Foam::Info << "Found " << name << " on disc" << Foam::endl;
        }
        return true;
    } else {
        if(debug) {
            Foam::Info << name << " not found" << Foam::endl;
        }
        return false;
    }
}

template<class T>
void ValueExpressionDriver::makePatches
(
    Foam::GeometricField<T,Foam::fvPatchField,Foam::volMesh> &field,
    bool keepPatches,
    const Foam::wordList &fixedPatches
) {
    typename Foam::GeometricField<T,Foam::fvPatchField,
                                  Foam::volMesh>::GeometricBoundaryField &bf=
        field.boundaryField();
    Foam::List<Foam::fvPatchField<T> *>bfNew(bf.size());

    forAll(bf,patchI) {
        const Foam::fvPatch &patch=bf[patchI].patch();

        bool isValuePatch=false;
        forAll(fixedPatches,i) {
            if(fixedPatches[i]==patch.name()) {
                isValuePatch=true;
            }
        }

        if(
            (
                !keepPatches
                ||
                isValuePatch
            )
            &&
            (
                typeid(patch)==typeid(Foam::wallFvPatch)
                ||
                typeid(patch)==typeid(Foam::fvPatch
                                      )
            )
            ) {
            if(isValuePatch) {
                bfNew[patchI]=new Foam::fixedValueFvPatchField<T>(patch,field);
            } else {
                bfNew[patchI]=new Foam::zeroGradientFvPatchField<T>(patch,field);
            }
        } else {
            bfNew[patchI]=bf[patchI].clone().ptr();
        }
    }

    bf.clear();
    bf.setSize(bfNew.size());
    forAll(bf,i) {
        bf.set(i,bfNew[i]);
    }
}

template<class T>
void ValueExpressionDriver::setValuePatches
(
    Foam::GeometricField<T,Foam::fvPatchField,Foam::volMesh> &field,
    bool keepPatches,
    const Foam::wordList &fixedPatches
) {
    typename Foam::GeometricField<T,Foam::fvPatchField,
                                  Foam::volMesh>::GeometricBoundaryField &bf=
        field.boundaryField();
    Foam::List<Foam::fvPatchField<T> *>bfNew(bf.size());

    forAll(bf,patchI) {
        const Foam::fvPatch &patch=bf[patchI].patch();

        bool isValuePatch=false;
        forAll(fixedPatches,i) {
            if(fixedPatches[i]==patch.name()) {
                isValuePatch=true;
            }
        }

        if(
            (
                !keepPatches
                ||
                isValuePatch
            )
            &&
            (
                typeid(patch)==typeid(Foam::wallFvPatch)
                ||
                typeid(patch)==typeid(Foam::fvPatch
                                      )
            )
            ) {
            if(typeid(field.boundaryField()[patchI])==
               typeid(Foam::fixedValueFvPatchField<T>)) {
                Foam::fvPatchField<T> &pf=field.boundaryField()[patchI];

                pf==pf.patchInternalField();
            }
        }
    }
}

#endif
