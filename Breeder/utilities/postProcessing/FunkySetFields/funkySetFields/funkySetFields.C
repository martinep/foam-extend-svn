/*---------------------------------------------------------------------------*\
 ##   ####  ######     | 
 ##  ##     ##         | Copyright: ICE Stroemungsfoschungs GmbH
 ##  ##     ####       |
 ##  ##     ##         | http://www.ice-sf.at
 ##   ####  ######     |
-------------------------------------------------------------------------------
 =========                   |
 \\      /   F ield          | OpenFOAM: The Open Source CFD Toolbox
  \\    /    O peration      |
   \\  /     A nd            | Copyright (C) 1991-2005 OpenCFD Ltd.
    \\/      M anipulation   |
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

Application
    funkySetFields

Description

 ICE Revision: $Id: funkySetFields.C 7567 2007-06-20 12:38:50Z bgschaid $ 
\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

#include "ValueExpressionDriver.H"

template<class T>
void setField(const string &name,const fvMesh &mesh,const string &time,T *result,volScalarField *cond,bool create,const dimensionSet &dim,bool keepPatches,const wordList &valuePatches)
{
    dimensioned<typename T::value_type> init("nix",dim,typename T::value_type());

    T *tmp;
    if(create) {
      tmp=new T
        (
            IOobject  
            (
                name,
                time,
                mesh,
		IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            mesh,
            init
        );
    } else {
      tmp=new T
        (
            IOobject  
            (
                name,
                time,
                mesh,
		IOobject::MUST_READ,
                IOobject::NO_WRITE
            ),
            mesh
        );
    }

    ValueExpressionDriver::makePatches(*tmp,keepPatches,valuePatches);

    label setCells=0;

    forAll(*tmp,cellI) {
        if((*cond)[cellI]!=0) {
	  (*tmp)[cellI]=(*result)[cellI];
            setCells++;
        }
    }

    ValueExpressionDriver::setValuePatches(*tmp,keepPatches,valuePatches);

    Info << " Setting " << setCells << " of " << tmp->size() << " cells" << endl;

    Info << " Writing to " << name << endl;

    tmp->write();

    delete tmp;
}

void doAnExpression(const fvMesh &mesh,const word &field,const string &expression,const string &condition,const Time& runTime,bool doDebug,bool create,const dimensionSet &dim,bool keepPatches,const wordList &valuePatches)
{
    const string &time = runTime.timeName();
    bool isScalar=false;

    if(!create) {
        IOobject f 
            (
                field,
                time,
                mesh,
                IOobject::MUST_READ,
                IOobject::NO_WRITE
            );
        f.headerOk();
        
        word classN=f.headerClassName();
        if(classN=="volScalarField") {
            isScalar=true;
        } else if (classN!="volVectorField") {
            FatalErrorIn("doAnExpression()")
                //            << args.executable()
                << " unsupported type " << classN << " of field " << field << " or not existing at time " << time
                    << exit(FatalError);
        }
    } else {
        Info << " Creating field " << field << "\n" << endl;
    }

    Info << " Putting " << expression << " into field " << field << " at t = " << time << " if condition " << condition << " is true" << endl;
    if(keepPatches) {
        Info << " Keeping patches unaltered" << endl;
    } else {
        if(valuePatches.size()>0) {
            Info << " Setting the patches " << valuePatches << " to fixed value" << endl;
        }
    }

    Info << endl;

    ValueExpressionDriver driver(time,runTime,mesh);
    ValueExpressionDriver ldriver(time,runTime,mesh);

    if (doDebug) {
        Info << "Parsing expression: " << expression << "\nand condition " << condition << "\n" << endl; 
        driver.trace_parsing=true;
        driver.trace_scanning=true;
    }

    ldriver.parse(condition);
    if(!ldriver.resultIsLogical()) {
        FatalErrorIn("doAnExpression()")
            //            << args.executable()
                << " condition: " << condition << " does not evaluate to a logical expression" 
            << exit(FatalError);
    }

    driver.parse(expression);

    if(create) {
        if(driver.resultIsVector()) {
            isScalar=false;
        } else if(driver.resultIsScalar()) {
            isScalar=true;
        } else {
            FatalErrorIn("doAnExpression()")
                << " result is neither scalar nor vector" 
            << exit(FatalError);
        }
    }

    if(driver.resultIsVector()==isScalar) {
        FatalErrorIn("doAnExpression()")
            //            << args.executable()
                << " inconsistent types: " << field << " is  " << (isScalar ? "scalar" : "vector" ) << " while the expression evaluates to a " << (!driver.resultIsVector() ? "scalar" : "vector" )
            << exit(FatalError);
    } else {
        if(isScalar) {
            setField(field,mesh,time,driver.getScalar(),ldriver.getScalar(),create,dim,keepPatches,valuePatches);
        } else {
	  setField(field,mesh,time,driver.getVector(),ldriver.getScalar(),create,dim,keepPatches,valuePatches);
        }
    }
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Main program:

int main(int argc, char *argv[])
{

#   include "addTimeOptionsNoConstant.H"

    argList::validOptions.insert("field","<field to overwrite>");
    argList::validOptions.insert("expression","<expression to write>");
    argList::validOptions.insert("condition","<logical condition>");
    argList::validOptions.insert("dimension","<dimension of created field>");
    argList::validOptions.insert("debugParser","");
    argList::validOptions.insert("create","");
    argList::validOptions.insert("keepPatches","");
    argList::validOptions.insert("valuePatches","<list of patches that get a fixed value>");

#   include "setRootCase.H"

    // make sure the program never fails due to dimension "problems"
    dimensionSet::debug=false;
    
    if (!args.options().found("time") && !args.options().found("latestTime")) {
        FatalErrorIn("main()")
            << args.executable()
                << ": time/latestTime option is required" << endl
            << exit(FatalError);
    }

#   include "createTime.H"
    instantList Times = runTime.times();
#   include "checkTimeOptions.H"
    if(startTime < 0) {
        FatalErrorIn("funkySetFields")
            << "Could not find a valid time (time directory not existing)" << endl
                << "startTime: " << startTime << " endTime: " << endTime << endl
                << endl
                << abort(FatalError);
    }
    runTime.setTime(Times[startTime],startTime);
#   include "createMesh.H"

    if(args.options().found("field")) {
        Info << " Using command-line options\n" << endl;

        word field=args.options()["field"];
        
        string expression=args.options()["expression"];

        string condition="true";
        if (args.options().found("condition")) {
            condition=args.options()["condition"];
        }

	string dimString="[0 0 0 0 0]";
	
	if (args.options().found("dimension")) {
	  dimString=args.options()["dimension"];
	}
	IStringStream dimStream(dimString);
	dimensionSet dim(dimStream);

        bool create=false;
        if (args.options().found("create")) {
            create=true;
        }

        bool keepPatches=false;
        if (args.options().found("keepPatches")) {
            keepPatches=true;
            if(keepPatches && create) {
                FatalErrorIn("main()")
                    << args.executable()
                        << ": the options <keepPatches> and <create> contradict"
                        << exit(FatalError);
            }
        }

        string valuePatchesString="";
        if (args.options().found("valuePatches")) {
            valuePatchesString=args.options()["valuePatches"];
        }
        IStringStream valuePatchesStream("("+valuePatchesString+")"); 
        wordList valuePatches(valuePatchesStream);

        doAnExpression(mesh,field,expression,condition,runTime,args.options().found("debugParser"),create,dim,keepPatches,valuePatches);
    } else {
        Info << " Using funkySetFieldsDict \n" << endl;
        
        if(args.options().found("keepPatches") || args.options().found("valuePatches") ||
           args.options().found("create") || args.options().found("dimension") ||
           args.options().found("condition") || args.options().found("expression")) {
            FatalErrorIn("main()")
                << args.executable()
                    << ": No other options than -time valid when using funkySetFieldsDict"
                    << exit(FatalError);
        }

        IOdictionary funkyDict
            (
                IOobject
                (
                    "funkySetFieldsDict",
                    runTime.system(),
                    mesh,
                    IOobject::MUST_READ,
                    IOobject::NO_WRITE
                )
            );

        PtrList<entry> parts=funkyDict.lookup("expressions");

        forAll(parts,partI) {
            const dictionary &part=parts[partI].dict();

            Info << "\n\nPart: " << parts[partI].keyword() << endl;

            word field=part["field"];

            string expression=part["expression"];

            string condition="true";

            if (part.found("condition")) {
                condition=part["condition"];
            }

	    dimensionSet dim(0,0,0,0,0);

            if (part.found("dimension")) {
                dim=dimensionSet(part.lookup("dimension"));
            }

            bool create=false;
            if (part.found("create")) {
                create=readBool(part["create"]);
            }

            bool keepPatches=false;
            if (part.found("keepPatches")) {
                keepPatches=readBool(part["keepPatches"]);
                if(keepPatches && create) {
                    FatalErrorIn("main()")
                        << args.executable()
                            << ": the options <keepPatches> and <create> contradict"
                            << exit(FatalError);
                }
            }

            wordList valuePatches;
            if (part.found("valuePatches")) {
                valuePatches=wordList(part.lookup("valuePatches"));
            }

            doAnExpression(mesh,field,expression,condition,runTime,args.options().found("debugParser"),create,dim,keepPatches,valuePatches);
        }
    }
    
    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
