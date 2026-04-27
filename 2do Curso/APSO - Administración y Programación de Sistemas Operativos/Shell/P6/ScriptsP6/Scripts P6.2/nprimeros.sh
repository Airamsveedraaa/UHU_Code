#!/bin/bash

if [ ! -d $1 ]
then
	echo "El primer parámetro debe ser un directorio"
	exit 1
else
	i=0
	for f in $(find $1 -type f)
	do
		if [ $i -lt $2 ]
		then
			echo "El nombre del fichero $i es $f"
			i=$((i+1))
		fi
	done
fi
