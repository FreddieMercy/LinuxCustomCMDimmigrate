#!/bin/bash

if [ $# != 0 ]
	then
		var=${PWD}
		echo $#
		mv $1 $2
		cd $2
		ls -l
		cd $var

elif [ $# == 0 ]
	then
		echo "Not moving anything"

else
	echo "FUCK UP!"
		

fi
