#!/bin/bash

SRC="./src/"
BUILD="./build/"
INCLUDE="./include/"
LIB="./lib/"
CC="~/opt/android/ndk/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android23-clang"

gcc -o ${BUILD}main ${SRC}main.c -I${INCLUDE} -L${LIB} -lraylib -lm
