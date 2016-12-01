#!/bin/bash

if [ $1 == "qq" ]
        then
		qemu-system-i386 -hda /home/junhao/MTX

elif [ $1 == "gcc" ]
        then
		gcc $2
		./a.out
else
	echo "Command not found"
fi
