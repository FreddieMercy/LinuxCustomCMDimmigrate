#!/bin/bash

if [ $# == 2 ]
	then
		var=${PWD}
		echo $#
		cp $1 $2
		cd $2
		ls -l
		cd $var

elif [ $# == 3 ]
	then
		var=${PWD}
		echo $#
		cp $1 $2 $3
		cd $3
		cd ..
		ls -l
		cd $var

elif [ $# == 0 ]
	then
		echo "Not copying anything"

else
	echo "FUCK UP!"
		

fi
