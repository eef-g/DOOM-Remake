#!/bin/bash

sourceDir="src"
destDir="bin"

# Create the destination directory
mkdir -p $destDir

# Recursively create directories in destination directory
# mirroring the structure of the source directory
find $sourceDir -type d | while read dir; do
    newDir=${dir/$sourceDir/$destDir}
    mkdir -p "$newDir"
done