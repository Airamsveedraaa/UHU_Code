#!/bin/bash


if [ $# -eq 0 ]
then
	echo "Se debe pasar un parametro"
	exit 1
else
	RUTA="$1"
	i=1
	echo "Dame un numero"
	read N
	if [ $N -ge 10 ]
	then
		echo "El valor es mayor a 10, ejecutando script con el valor más alto posible"
		while [ $i -lt 9 ]	
		do
			RUTA=$RUTA/$1
			i=$((i+1))
		done
	elif [ $N -lt 2 ]
	then
		echo "El mínimo valor posible es 2, ejecutando script con el valor más bajo posible"
		while [ $i -lt 2 ]
		do
			RUTA=$RUTA/$1
			i=$((i+1))
		done
	else
		while [ $i -lt $N ]
		do
			RUTA=$RUTA/$1
			i=$((i+1))
		done
	fi
		mkdir -p $RUTA
fi
