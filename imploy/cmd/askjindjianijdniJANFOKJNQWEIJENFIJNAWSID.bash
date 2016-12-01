#!/bin/bash

if [ $# != 0 ]
	then
		echo $#
		cd "$1"
		ls -l
elif [ $# == 0 ]
	then
		echo "Not going anywhere"

else
	echo "No Dir"
		

fi
