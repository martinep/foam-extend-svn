#! /usr/bin/env bash

rm -rf externalStuff
mkdir externalStuff

SAMPLE_SURFACE=$FOAM_UTILITIES/postProcessing/miscellaneous/sampleSurface

for sub in  surfaces surfaceWriters ; do
    echo "Preparing "$sub
    cp -r $SAMPLE_SURFACE/$sub externalStuff/$sub
done

find externalStuff -name .svn -exec rm -rf {} \; -prune
cd externalStuff
rmdepall
