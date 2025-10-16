#!/bin/bash

#####################################################################################
# Build script for invoking a cmake build, PROFILE could be either Release or Debug
#####################################################################################
PROFILE="Release"   # Release or Debug

mkdir -p build

cmake -S . -B build -DCMAKE_BUILD_TYPE=$PROFILE

pushd build > /dev/null

if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" ]]; then
    cmake --build . --config $PROFILE -j"$NUMBER_OF_PROCESSORS"
elif [[ "$(uname)" == "Linux" ]]; then
    cmake --build . -j$(nproc)
else
    cmake --build .
fi

if [[ $? -eq 0 ]]; then 
    echo "Build successful, the generated executable is outputted to $(pwd)/uart_flash_programmer"
else
    echo "Build failed!"
fi

popd > /dev/null