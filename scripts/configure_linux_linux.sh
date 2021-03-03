#!/bin/bash
cd ..
mkdir build > /dev/null 2>&1
rm -rf ./build/*

cd build
cmake ..

