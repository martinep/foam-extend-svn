//  ICE Revision: $Id: ValueExpressionDriver.H 7567 2007-06-20 12:38:50Z bgschaid $ 

#ifndef VALUE_EXPRESSION_DRIVER_H
#define VALUE_EXPRESSION_DRIVER_H

#include <string.H>
#include <scalar.H>

#include <volFields.H>
#include <surfaceFields.H>

class ValueExpressionDriver;

#include "ValueExpressionParser.tab.hh"

namespace ve {
    class location;
    class ValueExpressionParser;
}

#define YY_DECL int velex(ve::ValueExpressionParser::semantic_type* yylval,ve::location* yylloc,ValueExpressionDriver &driver)

YY_DECL;

class ValueExpressionDriver {
public:
    enum ExpressionType{
        NO_TYPE,
        SCALAR_TYPE,
        VECTOR_TYPE,
        LOGICAL_TYPE
    };

private:
    Foam::string getTypeOfField(const Foam::string &name);
    Foam::string getTypeOfSet(const Foam::string &name);

    const Foam::string &time;
    const Foam::fvMesh &mesh;
    const Foam::Time& _runTime;

    Foam::volScalarField *result;
    Foam::volVectorField *vresult;

    ExpressionType typ;

public:
    ValueExpressionDriver(const Foam::string& time,const Foam::Time& runTime,const Foam::fvMesh &mesh);
    virtual ~ValueExpressionDriver();

    // Check the result type
    bool resultIsVector() { return typ==VECTOR_TYPE; }
    bool resultIsScalar() { return typ==SCALAR_TYPE; }
    bool resultIsLogical() { return typ==LOGICAL_TYPE; }

    // Setting the result
    void setScalarResult(Foam::volScalarField *);
    void setLogicalResult(Foam::volScalarField *);
    void setVectorResult(Foam::volVectorField *);

    // Getting the results
    Foam::volScalarField *getScalar() { return result; }
    Foam::volVectorField *getVector() { return vresult; }

    // Handling the scanner.
    void scan_begin ();
    void scan_end ();
    bool trace_scanning;

    // Handling the parser.
    void parse (const std::string& f);
    Foam::string content;
    bool trace_parsing;

    // Error handling.
    void error (const ve::location& l, const std::string& m);
    void error (const std::string& m);

    // checking for variables
    bool isFaceScalar(const Foam::string &name);
    bool isFaceVector(const Foam::string &name);
    bool isScalar(const Foam::string &name);
    bool isVector(const Foam::string &name);
    bool isCellSet(const Foam::string &name);
    bool isCellZone(const Foam::string &name);

    // returning fields
    Foam::surfaceScalarField *getFaceScalarField(const Foam::string &name);
    Foam::surfaceVectorField *getFaceVectorField(const Foam::string &name);
    Foam::volScalarField *getScalarField(const Foam::string &name);
    Foam::volVectorField *getVectorField(const Foam::string &name);

    // make constant fields
    Foam::volScalarField *makeScalarField(const Foam::scalar &val);
    Foam::volVectorField *makeVectorField(const Foam::vector &vec);
    Foam::volVectorField *makeVectorField(Foam::volScalarField *x,Foam::volScalarField *y,Foam::volScalarField *z);
    Foam::surfaceScalarField *makeSurfaceScalarField(const Foam::scalar &val);
    Foam::surfaceVectorField *makeSurfaceVectorField(const Foam::vector &vec);
    Foam::surfaceVectorField *makeSurfaceVectorField(Foam::surfaceScalarField *x,Foam::surfaceScalarField *y,Foam::surfaceScalarField *z);
    Foam::volScalarField *makeCellSetField(const Foam::string &name);
    Foam::volScalarField *makeCellZoneField(const Foam::string &name);

    // modulo operator
    Foam::volScalarField *makeModuloField(const Foam::volScalarField &a,const Foam::volScalarField &b);

    // make special fields
    Foam::surfaceVectorField *makeFacePositionField();
    Foam::surfaceVectorField *makeFaceProjectionField();
    Foam::surfaceVectorField *makeFaceField();
    Foam::surfaceScalarField *makeAreaField();
    Foam::volVectorField *makePositionField();
    Foam::volScalarField *makeDistanceField();
    Foam::volScalarField *makeRDistanceField(const Foam::volVectorField &r);
    Foam::volScalarField *makeVolumeField();
    Foam::volScalarField *makeRandomField();
    Foam::volScalarField *makeGaussRandomField();
    Foam::volScalarField *makeCellIdField();
    
    // return Time object
    const Foam::Time& runTime() const { return _runTime; }

    // Logical expressions
    template <class Field>
    Field *makeLogicalField(Foam::scalar v);

    template <class Op,class Field>
    Field *doCompare(Field *a,Op op,Field *b);

    template <class Op,class Field>
    Field *doLogicalOp(Field *a,Op op,Field *b);

    template <class Field>
    Field *doLogicalNot(Field *a);
    
    template <class T,class Field>
    T * doConditional(Field *l,T* yes,T* no,T* result);

    template<class T>
    void makeZeroGradientPatches(Foam::GeometricField<T,Foam::fvPatchField,Foam::volMesh> &field);

    template<class T>
    static void makePatches(Foam::GeometricField<T,Foam::fvPatchField,Foam::volMesh> &field,bool keepPatches,const Foam::wordList &fixedPatches);

    template<class T>
    static void setValuePatches(Foam::GeometricField<T,Foam::fvPatchField,Foam::volMesh> &field,bool keepPatches,const Foam::wordList &fixedPatches);

};

#endif
