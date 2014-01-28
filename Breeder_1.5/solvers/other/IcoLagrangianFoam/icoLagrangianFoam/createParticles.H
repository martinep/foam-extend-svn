//  ICE Revision: $Id: createParticles.H 7092 2007-01-25 21:38:27Z bgschaid $ 
Info << "Constructing Particles" << endl;

pointMesh pMesh(mesh);
volPointInterpolation vpi(mesh, pMesh);

IncompressibleCloud cloud(vpi,U);
