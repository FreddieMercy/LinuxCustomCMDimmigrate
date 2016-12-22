#!/bin/bash

echo "running..."
echo "cleaning the outdated boot files (i.e: sudo apt-get purge linux-image-x.x.x-xx-generic)"

max=0

#sudo apt-get purge linux-image-x.x.x-xx-generic

for min in $(
	#find all versions
	for OUTPUT in $(ls /boot/initrd.img-[0-9]*.[0-9]*.[0-9]*-[0-9]*-generic)
	do
		#example: /boot/initrd.img-4.4.0-45-generic
		ONE=$(echo $OUTPUT | cut -d '-' -f 2)	#4.4.0
		TWO=$(echo $OUTPUT | cut -d '-' -f 3)	#45
		SAN=$(echo $ONE | cut -d '.' -f 1)	#4.x.x
		SI=$(echo $ONE | cut -d '.' -f 2)	#x.4.x
		WU=$(echo $ONE | cut -d '.' -f 3)	#x.x.0
		LIU="$SAN$SI$WU$TWO"	#44045	for comparison
		#echo linux-image-$ONE-$TWO-generic
	
		echo $LIU
	done)
do

if [ $min -gt $max ] 
	then
		tmp=$max
		max=$min
		min=$tmp

		#echo $min
fi

if [ $min -gt "0" ]
	then
		for OUTPUT in $(ls /boot/initrd.img-[0-9]*.[0-9]*.[0-9]*-[0-9]*-generic)
		do
			#example: /boot/initrd.img-4.4.0-45-generic
			ONE=$(echo $OUTPUT | cut -d '-' -f 2)	#4.4.0
			TWO=$(echo $OUTPUT | cut -d '-' -f 3)	#45
			SAN=$(echo $ONE | cut -d '.' -f 1)	#4.x.x
			SI=$(echo $ONE | cut -d '.' -f 2)	#x.4.x
			WU=$(echo $ONE | cut -d '.' -f 3)	#x.x.0
			LIU="$SAN$SI$WU$TWO"	#44045	for comparison
			#echo linux-image-$ONE-$TWO-generic
	
			if [ $min -eq $LIU ]
				then

					sudo apt-get purge linux-image-$ONE-$TWO-generic
					break
			fi
		done

		
fi

done

apt-get clean
apt-get update
apt-get upgrade
apt-get -f install
apt-get update
apt-get dist-upgrade
apt-get autoremove
