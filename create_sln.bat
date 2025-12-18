rem Use this batch file to build rt-engine for Visual Studio
rmdir /s /q build
mkdir build
cd build
cmake ..
