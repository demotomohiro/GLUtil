# GLUtil
Classes and functions often used in my OpenGL projects

## Required libraries:
* GLEW

## Optional libraries:
* Boost(wave)
Required by cStdShader.

## Required tools:
CMake
### On Linux
gcc
### On Windows
Visual Studio 2015

## How to build and install
```console
git clone https://github.com/demotomohiro/GLUtil.git
mkdir build
cd build
```
On Windows
```console
cmake -G "Visual Studio 14 2015 Win64" ../GLUtil
msbuild INSTALL.vcxproj
```
You can also open batchRIshader.sln with Visual Studio and build it. 

On Linux
```console
cmake ../GLUtil
make
make install
```
### cmake options:
* -DCMAKE_BUILD_TYPE=[Debug|Release|RelWithDebInfo|MinSizeRel]
Specifies the build type. This options is ignored when used with Visual Studio.
* -DCMAKE_INSTALL_PREFIX="/path/to/install"
GLUtil will be insalled under the specified directory.
* -DBoost_USE_STATIC_LIBS=[on|off]
Set to ON to force the use of static Boost libraries. Default is OFF. 
* -DBUILD_SHARED_LIBS=[on|off]
Set to ON to build shared libraries.

This software is released under the MIT License, see LICENSE.
