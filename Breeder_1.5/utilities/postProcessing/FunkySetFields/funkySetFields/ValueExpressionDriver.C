//  ICE Revision: $Id: ValueExpressionDriver.C 7567 2007-06-20 12:38:50Z bgschaid $ 

#include "ValueExpressionDriver.H"
#include <Random.H>
#include <wallDist.H>
#include <dimensionedVector.H>
#include "zeroGradientFvPatchFields.H"
#include "fixedValueFvPatchFields.H"
#include "wallFvPatch.H"
#include "cellSet.H"

ValueExpressionDriver::ValueExpressionDriver (const Foam::string& time,const Foam::Time& runTime,const Foam::fvMesh &mesh)
    : time(time),
      mesh(mesh),
      _runTime(runTime),
      result(NULL),
      vresult(NULL),
      typ(NO_TYPE),
      trace_scanning (false),
      trace_parsing (false)
{
}

ValueExpressionDriver::~ValueExpressionDriver ()
{
    if(result) {
        delete result;
    }
    if(vresult) {
        delete vresult;
    }
}

void ValueExpressionDriver::setScalarResult(Foam::volScalarField *r) {
    result=r;
    typ=SCALAR_TYPE;
}

void ValueExpressionDriver::setLogicalResult(Foam::volScalarField *r) {
    result=r;
    typ=LOGICAL_TYPE;
}

void ValueExpressionDriver::setVectorResult(Foam::volVectorField *r) {
    vresult=r;
    typ=VECTOR_TYPE;
}

void ValueExpressionDriver::parse (const std::string &f)
{
    content = f;
    scan_begin ();
    ve::ValueExpressionParser parser (*this);
    parser.set_debug_level (trace_parsing);
    parser.parse ();
    scan_end ();
}

void ValueExpressionDriver::error (const ve::location& l, const std::string& m)
{
    std::ostringstream buff;
    buff << l;
    std::string place="";
    for(unsigned int i=0;i<l.begin.column;i++) {
        place+=" ";
    }
    for(unsigned int i=l.begin.column;i<l.end.column;i++) {
        place+="^";
    }
    for(unsigned int i=l.end.column;i<content.size();i++) {
        place+=" ";
    }

    Foam::FatalErrorIn("parsingValue")
        //        << Foam::args.executable()
        << " Parser Error at " << buff.str() << " :"  << m << Foam::endl
            << content << Foam::endl << place
            << Foam::exit(Foam::FatalError);
    //    Foam::Info << buff.str() << ": " << m << Foam::endl;
}

void ValueExpressionDriver::error (const std::string& m)
{
    Foam::FatalErrorIn("parsingValue")
        //        << Foam::args.executable()
            << " Parser Error: " << m
            << Foam::exit(Foam::FatalError);
}

bool ValueExpressionDriver::isFaceScalar(const Foam::string &name)
{
    if(getTypeOfField(name)=="surfaceScalarField") {
        return true;
    } else {
        return false;
    }
}

bool ValueExpressionDriver::isFaceVector(const Foam::string &name)
{
    if(getTypeOfField(name)=="surfaceVectorField") {
        return true;
    } else {
        return false;
    }
}

bool ValueExpressionDriver::isScalar(const Foam::string &name)
{
    if(getTypeOfField(name)=="volScalarField") {
        return true;
    } else {
        return false;
    }
}

bool ValueExpressionDriver::isVector(const Foam::string &name)
{
    if(getTypeOfField(name)=="volVectorField") {
        return true;
    } else {
        return false;
    }
}

bool ValueExpressionDriver::isCellSet(const Foam::string &name)
{
    if(getTypeOfSet(name)=="cellSet") {
        return true;
    } else {
        return false;
    }
}

bool ValueExpressionDriver::isCellZone(const Foam::string &name)
{
    if(mesh.cellZones().findZoneID(name)>=0) {
        return true;
    } else {
        return false;
    }
}

Foam::string ValueExpressionDriver::getTypeOfField(const Foam::string &name)
{
    Foam::IOobject f 
        (
            name,
            time,
            mesh,
            Foam::IOobject::MUST_READ,
            Foam::IOobject::NO_WRITE
        );
    f.headerOk();

    return f.headerClassName();
}

Foam::string ValueExpressionDriver::getTypeOfSet(const Foam::string &name)
{
    Foam::IOobject f 
        (
            name,
            time,
            Foam::polyMesh::meshSubDir/"sets",
	    mesh,
            Foam::IOobject::MUST_READ,
            Foam::IOobject::NO_WRITE
        );
    
    if(f.headerOk()) {;
        return f.headerClassName();
    } else {
        Foam::Info << "No set " << name << " at t=" << time << " falling back to 'constant'" << Foam::endl;
        f=Foam::IOobject 
        (
            name,
            "constant",
            Foam::polyMesh::meshSubDir/"sets",
	    mesh,
            Foam::IOobject::MUST_READ,
            Foam::IOobject::NO_WRITE
        );
        f.headerOk();
        return f.headerClassName();
    }
}

Foam::volScalarField *ValueExpressionDriver::getScalarField(const Foam::string &name)
{
    Foam::dimensionSet nullDim(0,0,0,0,0);

    Foam::volScalarField *f=new Foam::volScalarField(
        Foam::IOobject
        (
            name,
            time,
            mesh,
            Foam::IOobject::MUST_READ,
            Foam::IOobject::NO_WRITE
        ),
        mesh
    );
    f->dimensions().reset(nullDim);

    return f;
}

Foam::surfaceScalarField *ValueExpressionDriver::getFaceScalarField(const Foam::string &name)
{
    Foam::dimensionSet nullDim(0,0,0,0,0);

    Foam::surfaceScalarField *f=new Foam::surfaceScalarField(
        Foam::IOobject
        (
            name,
            time,
            mesh,
            Foam::IOobject::MUST_READ,
            Foam::IOobject::NO_WRITE
        ),
        mesh
    );
    f->dimensions().reset(nullDim);

    return f;
}

Foam::surfaceVectorField *ValueExpressionDriver::getFaceVectorField(const Foam::string &name)
{
    Foam::dimensionSet nullDim(0,0,0,0,0);

    Foam::surfaceVectorField *f=new Foam::surfaceVectorField(
        Foam::IOobject
        (
            name,
            time,
            mesh,
            Foam::IOobject::MUST_READ,
            Foam::IOobject::NO_WRITE
        ),
        mesh
    );
    f->dimensions().reset(nullDim);

    return f;
}

Foam::volScalarField *ValueExpressionDriver::makeModuloField(
    const Foam::volScalarField &a,
    const Foam::volScalarField &b)
{
    Foam::volScalarField *result=makeScalarField(0.);

    forAll(*result,cellI) {
        Foam::scalar val=fmod(a[cellI],b[cellI]);

        if(fabs(val)>(b[cellI]/2)) {
            if(val>0) {
                val-=b[cellI];
            } else {
                val+=b[cellI];
            }
        }

        (*result)[cellI]=val;
    }

    return result;
}

Foam::volScalarField *ValueExpressionDriver::makeRandomField()
{
    Foam::volScalarField *f=makeScalarField(0.);
    Foam::Random rand(65);

    forAll(*f,cellI) {
        (*f)[cellI]=rand.scalar01();
    }

    return f;
}

Foam::volScalarField *ValueExpressionDriver::makeCellIdField()
{
    Foam::volScalarField *f=makeScalarField(0.);

    forAll(*f,cellI) {
        (*f)[cellI]=Foam::scalar(cellI);
    }

    return f;
}

Foam::volScalarField *ValueExpressionDriver::makeGaussRandomField()
{
    Foam::volScalarField *f=makeScalarField(0.);
    Foam::Random rand(65);

    forAll(*f,cellI) {
        (*f)[cellI]=rand.GaussNormal();
    }

    return f;
}

Foam::volVectorField *ValueExpressionDriver::makePositionField()
{
    Foam::dimensionSet nullDim(0,0,0,0,0);
    Foam::volVectorField *f=new Foam::volVectorField(
        Foam::IOobject
        (
            "pos",
            time,
            mesh,
            Foam::IOobject::NO_READ,
            Foam::IOobject::NO_WRITE
        ),
        mesh,
        Foam::vector(0,0,0)
    );
    f->dimensions().reset(mesh.C().dimensions());
    *f=mesh.C();
    f->dimensions().reset(nullDim);
    return f;
}

Foam::surfaceVectorField *ValueExpressionDriver::makeFacePositionField()
{
    Foam::dimensionSet nullDim(0,0,0,0,0);
    Foam::surfaceVectorField *f=new Foam::surfaceVectorField(
        Foam::IOobject
        (
            "fpos",
            time,
            mesh,
            Foam::IOobject::NO_READ,
            Foam::IOobject::NO_WRITE
        ),
        mesh,
        Foam::vector(0,0,0)
    );
    f->dimensions().reset(mesh.Cf().dimensions());
    *f=mesh.Cf();
    f->dimensions().reset(nullDim);
    return f;
}

Foam::surfaceVectorField *ValueExpressionDriver::makeFaceProjectionField()
{

    Foam::dimensionSet nullDim(0,0,0,0,0);
    Foam::surfaceVectorField *f=new Foam::surfaceVectorField(
        Foam::IOobject
        (
            "fproj",
            time,
            mesh,
            Foam::IOobject::NO_READ,
            Foam::IOobject::NO_WRITE
        ),
        mesh,
        Foam::vector(0,0,0)
    );
    f->dimensions().reset(mesh.Cf().dimensions());

    Foam::vector fmin(0,0,0);
    Foam::vector fmax(0,0,0);
    
    forAll(*f,faceI)
    {
        const Foam::face &fProp = mesh.faces()[faceI];
        fmin = mesh.points()[fProp[0]];
        fmax = fmin;
        forAll(fProp,pointI)
        {
            forAll(mesh.points()[0],compI)
            {
                if(mesh.points()[fProp[pointI]].component(compI) < fmin.component(compI))
                    fmin.component(compI) = mesh.points()[fProp[pointI]].component(compI);
                if(mesh.points()[fProp[pointI]].component(compI) > fmax.component(compI))
                    fmax.component(compI) = mesh.points()[fProp[pointI]].component(compI);
            }
        }
        (*f)[faceI] = fmax - fmin;
    }
    forAll(mesh.boundaryMesh(),patchI)
    {
        Foam::labelList cNumbers = mesh.boundaryMesh()[patchI].faceCells();
        Foam::fvsPatchVectorField & fFace = f->boundaryField()[patchI];
        
        forAll(fFace,faceI)
        {
            const Foam::cell & cProp(mesh.cells()[cNumbers[faceI]]);

            forAll(cProp,cJ)
            {
                const Foam::label patchID = mesh.boundaryMesh().whichPatch(cProp[cJ]);

                if (patchID == patchI)
                {
                    const Foam::face & fProp = mesh.faces()[cProp[cJ]];

                    fmin = mesh.points()[fProp[0]];
                    fmax = fmin;

                    forAll(fProp,pointI)
                    {
                        forAll(mesh.points()[0],compI)
                        {
                            if(mesh.points()[fProp[pointI]].component(compI) < fmin.component(compI))
                                fmin.component(compI) = mesh.points()[fProp[pointI]].component(compI);
                            if(mesh.points()[fProp[pointI]].component(compI) > fmax.component(compI))
                                fmax.component(compI) = mesh.points()[fProp[pointI]].component(compI);
                        }
                    }
                    fFace[faceI] = fmax - fmin;
                }
            }
        }
    }

    f->dimensions().reset(nullDim);
    return f;
}

Foam::surfaceVectorField *ValueExpressionDriver::makeFaceField()
{
    Foam::dimensionSet nullDim(0,0,0,0,0);
    Foam::surfaceVectorField *f=new Foam::surfaceVectorField(
        Foam::IOobject
        (
            "face",
            time,
            mesh,
            Foam::IOobject::NO_READ,
            Foam::IOobject::NO_WRITE
        ),
        mesh,
        Foam::vector(0,0,0)
    );
    f->dimensions().reset(mesh.Sf().dimensions());
    *f=mesh.Sf();
    f->dimensions().reset(nullDim);
    return f;
}

Foam::surfaceScalarField *ValueExpressionDriver::makeAreaField()
{
    Foam::dimensionSet nullDim(0,0,0,0,0);
    Foam::surfaceScalarField *f=new Foam::surfaceScalarField(
        Foam::IOobject
        (
            "face",
            time,
            mesh,
            Foam::IOobject::NO_READ,
            Foam::IOobject::NO_WRITE
        ),
        mesh,
        0
    );
    f->dimensions().reset(mesh.magSf().dimensions());
    *f=mesh.magSf();
    f->dimensions().reset(nullDim);
    return f;
}

Foam::volScalarField *ValueExpressionDriver::makeVolumeField()
{
    Foam::volScalarField *f=new Foam::volScalarField(
        Foam::IOobject
        (
            "vol",
            time,
            mesh,
            Foam::IOobject::NO_READ,
            Foam::IOobject::NO_WRITE
        ),
        mesh,
        0
    );
    const Foam::scalarField &V=mesh.V();

    forAll(*f,cellI) {
        (*f)[cellI]=V[cellI];
    }

    return f;
}

Foam::volScalarField *ValueExpressionDriver::makeDistanceField()
{
    Foam::dimensionSet nullDim(0,0,0,0,0);
    Foam::volScalarField *f=new Foam::volScalarField(
        Foam::IOobject
        (
            "dist",
            time,
            mesh,
            Foam::IOobject::NO_READ,
            Foam::IOobject::NO_WRITE
        ),
        mesh,
        0
    );
    f->dimensions().reset(mesh.C().dimensions());
    Foam::wallDist dist(mesh);
    *f=dist;
    f->dimensions().reset(nullDim);
    return f;

}

Foam::volScalarField *ValueExpressionDriver::makeRDistanceField(const Foam::volVectorField& r)
{
    Foam::dimensionSet nullDim(0,0,0,0,0);
    Foam::volScalarField *f=new Foam::volScalarField(
        Foam::IOobject
        (
            "rdist",
            time,
            mesh,
            Foam::IOobject::NO_READ,
            Foam::IOobject::NO_WRITE
        ),
        mesh,
        0
    );

    forAll(*f,cellI) {
        (*f)[cellI]=mag(mesh.C()[cellI] - r[cellI]);
    }

    return f;
}

Foam::volVectorField *ValueExpressionDriver::getVectorField(const Foam::string &name)
{
    Foam::dimensionSet nullDim(0,0,0,0,0);
    Foam::volVectorField *f=new Foam::volVectorField(
        Foam::IOobject
        (
            name,
            time,
            mesh,
            Foam::IOobject::MUST_READ,
            Foam::IOobject::NO_WRITE
        ),
        mesh
    );

    f->dimensions().reset(nullDim);
    return f;
}

template<class T>
void ValueExpressionDriver::makeZeroGradientPatches(Foam::GeometricField<T,Foam::fvPatchField,Foam::volMesh> &field) 
{
  typename Foam::GeometricField<T,Foam::fvPatchField,Foam::volMesh>::GeometricBoundaryField &bf=field.boundaryField();
  Foam::List<Foam::fvPatchField<T> *>bfNew(bf.size());

  forAll(bf,patchI) {
    const Foam::fvPatch &patch=bf[patchI].patch();

    if(typeid(patch)==typeid(Foam::wallFvPatch) || typeid(patch)==typeid(Foam::fvPatch)) {
        bfNew[patchI]=new Foam::zeroGradientFvPatchField<T>(patch,field);      
    } else {
        bfNew[patchI]=bf[patchI].clone().ptr();
    }
  }

  bf.clear();
  bf.setSize(bfNew.size());
  forAll(bf,i) {
      bf.set(i,bfNew[i]);
  }

  // Fix for SIGFPE crash dividing (/) a scalarField with a non-zero
  // scalarField
  bf.evaluate();
}

Foam::volScalarField *ValueExpressionDriver::makeScalarField(const Foam::scalar &val)
{
    std::ostringstream buff;
    buff << "constantScalar" << val;

    Foam::volScalarField *f=new Foam::volScalarField(
        Foam::IOobject
        (
            buff.str(),
            time,
            mesh,
            Foam::IOobject::NO_READ,
            Foam::IOobject::NO_WRITE
        ),
        mesh,
        val,
        "zeroGradient"
    );

    //    makeZeroGradientPatches(*f);

    return f;
}

Foam::surfaceScalarField *ValueExpressionDriver::makeSurfaceScalarField(const Foam::scalar &val)
{
    std::ostringstream buff;
    buff << "constantScalar" << val;

    Foam::surfaceScalarField *f=new Foam::surfaceScalarField(
        Foam::IOobject
        (
            buff.str(),
            time,
            mesh,
            Foam::IOobject::NO_READ,
            Foam::IOobject::NO_WRITE
        ),
        mesh,
        val,
        "fixedValue"
    );
    //    makeZeroGradientPatches(*f);

    //    Foam::Info << *f << Foam::endl;
    return f;
}

Foam::volScalarField *ValueExpressionDriver::makeCellSetField(const Foam::string &name)
{
  Foam::volScalarField *f=makeScalarField(0);

  Foam::IOobject head 
      (
          name,
          time,
          Foam::polyMesh::meshSubDir/"sets",
          mesh,
          Foam::IOobject::MUST_READ,
          Foam::IOobject::NO_WRITE
      );
  
  if(!head.headerOk()) {;
      head=Foam::IOobject 
          (
              name,
              "constant",
              Foam::polyMesh::meshSubDir/"sets",
              mesh,
              Foam::IOobject::MUST_READ,
              Foam::IOobject::NO_WRITE
          );
      head.headerOk();
  }

  Foam::cellSet cs(head);
  Foam::labelList cells(cs.toc());

  forAll(cells,cellI) {
    (*f)[cells[cellI]]=1.;
  }

  return f;
}

Foam::volScalarField *ValueExpressionDriver::makeCellZoneField(const Foam::string &name)
{
  Foam::volScalarField *f=makeScalarField(0);
  Foam::label zoneID=mesh.cellZones().findZoneID(name);

  const Foam::cellZone &zone=mesh.cellZones()[zoneID];

  forAll(zone,ind) {
      Foam::label cellI=zone[ind];
      (*f)[cellI]=1.;
  }

  return f;
}

Foam::volVectorField *ValueExpressionDriver::makeVectorField(const Foam::vector &vec)
{
    std::ostringstream buff;
    buff << "constantVector" << vec.x() << "_" << vec.y() << "_" << vec.z() ;

    Foam::volVectorField *f=new Foam::volVectorField(
        Foam::IOobject
        (
            buff.str(),
            time,
            mesh,
            Foam::IOobject::NO_READ,
            Foam::IOobject::NO_WRITE
        ),
        mesh,
        vec
    );

    makeZeroGradientPatches(*f);

    return f;
}

Foam::volVectorField *ValueExpressionDriver::makeVectorField(Foam::volScalarField *x,Foam::volScalarField *y,Foam::volScalarField *z)
{
    Foam::volVectorField *f=makeVectorField(Foam::vector(0,0,0));

    forAll(*f,cellI) {
        (*f)[cellI]=Foam::vector((*x)[cellI],(*y)[cellI],(*z)[cellI]);
    }

    return f;
}

Foam::surfaceVectorField *ValueExpressionDriver::makeSurfaceVectorField(const Foam::vector &vec)
{
    std::ostringstream buff;
    buff << "constantVector" << vec.x() << "_" << vec.y() << "_" << vec.z() ;

    Foam::surfaceVectorField *f=new Foam::surfaceVectorField(
        Foam::IOobject
        (
            buff.str(),
            time,
            mesh,
            Foam::IOobject::NO_READ,
            Foam::IOobject::NO_WRITE
        ),
        mesh,
        vec,
        "fixedValue"
    );

    //    makeZeroGradientPatches(*f);

    return f;
}

Foam::surfaceVectorField *ValueExpressionDriver::makeSurfaceVectorField(Foam::surfaceScalarField *x,Foam::surfaceScalarField *y,Foam::surfaceScalarField *z)
{
    Foam::surfaceVectorField *f=makeSurfaceVectorField(Foam::vector(0,0,0));

    forAll(*f,faceI) {
        (*f)[faceI]=Foam::vector((*x)[faceI],(*y)[faceI],(*z)[faceI]);
    }

    return f;
}

template<class T>
void ValueExpressionDriver::makePatches(Foam::GeometricField<T,Foam::fvPatchField,Foam::volMesh> &field,bool keepPatches,const Foam::wordList &fixedPatches) 
{
  typename Foam::GeometricField<T,Foam::fvPatchField,Foam::volMesh>::GeometricBoundaryField &bf=field.boundaryField();
  Foam::List<Foam::fvPatchField<T> *>bfNew(bf.size());

  forAll(bf,patchI) {
    const Foam::fvPatch &patch=bf[patchI].patch();

    bool isValuePatch=false;
    forAll(fixedPatches,i) {
      if(fixedPatches[i]==patch.name()) {
	isValuePatch=true;
      }
    }

    if((!keepPatches || isValuePatch) && (typeid(patch)==typeid(Foam::wallFvPatch) || typeid(patch)==typeid(Foam::fvPatch))) {
        if(isValuePatch){
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
void ValueExpressionDriver::setValuePatches(Foam::GeometricField<T,Foam::fvPatchField,Foam::volMesh> &field,bool keepPatches,const Foam::wordList &fixedPatches) 
{
  typename Foam::GeometricField<T,Foam::fvPatchField,Foam::volMesh>::GeometricBoundaryField &bf=field.boundaryField();
  Foam::List<Foam::fvPatchField<T> *>bfNew(bf.size());

  forAll(bf,patchI) {
    const Foam::fvPatch &patch=bf[patchI].patch();

    bool isValuePatch=false;
    forAll(fixedPatches,i) {
      if(fixedPatches[i]==patch.name()) {
	isValuePatch=true;
      }
    }

    if((!keepPatches || isValuePatch) && (typeid(patch)==typeid(Foam::wallFvPatch) || typeid(patch)==typeid(Foam::fvPatch))) {
        if(typeid(field.boundaryField()[patchI])==typeid(Foam::fixedValueFvPatchField<T>)) {
            Foam::fvPatchField<T> &pf=field.boundaryField()[patchI];
            
            pf==pf.patchInternalField();
        }
    }
  }
}

// Force the compiler to generate the code, there'S a better way but I'm too stupid
void dummyS(Foam::GeometricField<Foam::scalar,Foam::fvPatchField,Foam::volMesh>  &f,bool keepPatches,const Foam::wordList &fixedPatches) {
    ValueExpressionDriver::makePatches(f,keepPatches,fixedPatches);
    ValueExpressionDriver::setValuePatches(f,keepPatches,fixedPatches);
}

void dummyV(Foam::GeometricField<Foam::vector,Foam::fvPatchField,Foam::volMesh>  &f,bool keepPatches,const Foam::wordList &fixedPatches) {
    ValueExpressionDriver::makePatches(f,keepPatches,fixedPatches);
    ValueExpressionDriver::setValuePatches(f,keepPatches,fixedPatches);
}
