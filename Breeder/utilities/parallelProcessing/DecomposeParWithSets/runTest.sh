#! /bin/sh

fluentMeshToFoam . setTest setTest/setTest.msh -writeSets
rm -rf setTest/processor*
decomposeParWithSets . setTest
