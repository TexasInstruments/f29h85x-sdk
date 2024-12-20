#!/bin/bash

#####################################################################################
# Build script for invoking a cmake build, PROFILE could be either Release or Debug
#####################################################################################
PROFILE="Release"

mkdir build
pushd build
cmake -DCMAKE_BUILD_TYPE=$PROFILE ..
cmake --build .
popd

echo "If build is successful, the generated executable will be build/uart_flash_programmer"