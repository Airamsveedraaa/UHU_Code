#!/bin/bash

if [ ! -d $1 ]
then
	echo "El parámetro debe ser un directorio"
	exit 1
elif [ $# -eq 0 ]
then
	while true
	do
		ls ~
		sleep 1
	done
else 
	while true
	do
		ls $1
		sleep 1
	done
fi
