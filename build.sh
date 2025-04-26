#!/bin/bash

SRC="./src/"
BUILD="./build/"
INCLUDE="./include/"
LIB="./lib/"
CC="~/opt/android/ndk/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android23-clang"

gcc -o ${BUILD}main ${SRC}main.c -I${INCLUDE} -L${LIB} -lraylib -lm

PROJECT_NAME=opoker
PROJECT_BUILD_ID=android
PROJECT_BUILD_PATH=${PROJECT_BUILD_ID}.${PROJECT_NAME}

~/opt/android/ndk/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android23-clang -o ${PROJECT_NAME}.o -c ${SRC}/main.c -I${INCLUDE}

# cleaning up build info because for some reason it's stalling building process

rm -r ${PROJECT_BUILD_PATH}
mkdir -p ${PROJECT_BUILD_PATH}/obj
cp ${PROJECT_NAME}.o ${PROJECT_BUILD_PATH}/obj
make
