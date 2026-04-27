#!/bin/bash

if [ $# -ne 2 ]
then
	echo "Número de parámetros incorrecto, se esperaban 2"
	exit 11
elif [ ! -d $1 ] || [ ! -d $2 ]
then
	echo "Los parámetros deben ser directorios válidos"
	exit 21
else
	echo "Introduzca un carácter"
	read C
	N=0
	for f in $(find $1 -name "$C*" -type f)
	do
		echo "$f"
		tail -3 $f
		echo "Quiere mover el archivo?"
		read P
		case $P in
			's')mv $f $2; N=$((N+1));;
			*);;
		esac
	done
	echo "Se han movido  $N ficheros"
fi
