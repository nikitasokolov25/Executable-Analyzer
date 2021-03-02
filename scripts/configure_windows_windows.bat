@echo off
cls

cd ..
mkdir build
DEL /F/Q/S build\*.*

cd build
cmake ..

pause