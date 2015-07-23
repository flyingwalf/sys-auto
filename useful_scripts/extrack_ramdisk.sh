#!/bin/bash

#############################################################
#                                                           #
#Extract everyting from a ramdisk.img into your current dir #
#                                                           #
#############################################################

RAMDISK=ramdisk.img

if [ $# == 1 ];then
    RAMDISK=$1
fi

gunzip -c $RAMDISK | cpio -i
