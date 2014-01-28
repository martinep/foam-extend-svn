//  ICE Revision: $Id: /local/openfoam/InitialConditions/setRadialBC/createFields.H 941 2007-01-25T21:22:46.998732Z bgschaid  $ 
    Info<< "Vector field U\n" << endl;
    volVectorField U
    (
        IOobject
        (
            "U",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );
