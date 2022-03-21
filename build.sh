#!/bin/bash

# run AVD with kernel supporting module by:
# `android-sdk-linux/tools/emulator -avd <avdName> -kernel kernel/goldfish/arch/arm/boot/zImage -show-kernel`

# build ptree syscall and push onto adb (problem 1)
cd problem1
make
adb push ptree.ko /data/misc/ptree.ko
make clean
cd ..

# build test for ptree syscall and push onto adb (problem 2)
cd problem2/jni
ndk-build && adb push ../libs/armeabi/ptreeTestARM /data/misc/ptreeTestARM
rm -rf ../libs ../obj
cd ../..

# build genProcess and push onto adb (problem 3)
cd problem3/jni
ndk-build && adb push ../libs/armeabi/genProcessARM /data/misc/genProcessARM
rm -rf ../libs ../obj
cd ../..

# build server & client and push onto adb (problem 4)
cd problem4/jni
ndk-build && adb push ../libs/armeabi/server /data/misc/server && adb push ../libs/armeabi/client /data/misc/client
rm -rf ../libs ../obj
cd ../..
