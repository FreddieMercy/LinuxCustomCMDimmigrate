#!/bin/bash

if [ $# != 0 ]
	then
		echo $#
		rm $1 $2
		ls -l


elif [ $# == 0 ]
	then
		echo "Not removing anything"

else
	echo "FUCK UP!"
		

fi
