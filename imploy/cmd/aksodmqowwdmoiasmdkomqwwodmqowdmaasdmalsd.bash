#!/bin/bash

if [ "$1" = "c" ] 
then
	if [ "$2" = "cursor" ]
	then
		update-alternatives --config x-cursor-theme

	elif [ "$2" = "browser" ]
	then
		update-alternatives --config x-www-browser
	else
		update-alternatives --config $2
	fi
else
	update-alternatives $1 $2
fi
