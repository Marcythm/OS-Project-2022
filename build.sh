#!/bin/bash

# build ptree syscall and push onto adb (problem 1)
cd problem1
make
adb push ptree.ko /data/misc/ptree.ko
make clean
cd ..

# build test for ptree syscall and push onto adb (problem 2)
cd problem2/jni
ndk-build && adb push ../libs/armeabi/ptreeTestARM /data/misc/ptreeTestARM
rm -rf ../libs
cd ../..

# build genProcess and push onto adb (problem 3)
cd problem3/jni
ndk-build && adb push ../libs/armeabi/genProcessARM /data/misc/genProcessARM
rm -rf ../libs
cd ../..
