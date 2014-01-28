#! /bin/sh

CASE=axialCavity

blockMesh . $CASE
pyFoamMeshUtilityRunner.py makeAxialMesh . $CASE
setRadialBC . $CASE