#!/bin/bash

SRC="./src/"
BUILD="./build/"
INCLUDE="./include/"
LIB="./lib/"

gcc -o ${BUILD}main ${SRC}main.c -I${INCLUDE} -L${LIB} -lraylib -lm
