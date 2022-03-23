# CS307 OS Project 1

## Problem 1: Implement `ptree` syscall, printing the process tree in Android

The source file of this problem is `problem1/ptree.c`, and the corresponding makefile is `problem1/Makefile`, using `make`.
Execute `cd problem1 && make`, then the target module file `ptree.ko` is generated under `problem1/`.

## Problem 2: Test the `ptree` syscall

The source file of this problem is `problem2/jni/ptreeTest.c`, and the corresponding makefile is `problem2/jni/Android.mk`, using `ndk-build`.
Execute `cd problem2/jni && ndk-build`, then the target file is `problem2/libs/armeabi/ptreeTestARM`.

## Problem 3: Generate a process, and execute `ptreeTestARM` in its subprocess

The source file of this problem is `problem3/jni/genProcess.c`, and the corresponding makefile is `problem3/jni/Android.mk`, using `ndk-build`.
Execute `cd problem3/jni && ndk-build`, then the target file is `problem3/libs/armeabi/genProcessARM`.

## Problem 4: Implement a Caesar Encryption Server using Concurrent Programming

The source file of this problem is `problem4/jni/server.c` and `problem4/jni/client.c`, and the corresponding makefile is `problem4/jni/Android.mk`, using `ndk-build`.
Execute `cd problem4/jni && ndk-build`, then the target files are `problem4/libs/armeabi/server` and `problem4/libs/armeabi/client`.
