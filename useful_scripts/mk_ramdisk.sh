#!/bin/bash

#############################################################
#                                                           #
#Pack everyting in your specified dir into a ramdisk.img    #
#                                                           #
#############################################################

ROOT_DIR=$PWD
OUT_IMG=ramdisk.img

if [ -d $1 ];then
    ROOT_DIR=$1
fi

if [ $# == 2 ];then
    OUT_IMG=$2
fi

cd $ROOT_DIR
find . | cpio -o -H newc | gzip > $OUT_IMG
cd -
