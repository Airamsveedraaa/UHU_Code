#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Se espera un parámetro"
	exit 1
else
	case $1 in
		"for") for ((i=1;i<10;i++))	
			do
				if [ $i -eq 6 ]
				then
					continue
				elif [ $i -eq 9 ]
				then
					break
				else
					echo "$i"
				fi
			done;;
		"while") i=1
			while [ $i -lt 10 ]
			do
				if [ $i -eq 6 ]
				then
					i=$((i+1))
					continue
				elif [ $i -eq 9 ]
				then
					break
				fi
				echo "$i"
				i=$((i+1))
			done;;
		"until") i=1
			until [ $i -eq 10 ]
			do
				if [ $i -eq 6 ]
				then
					i=$((i+1))
					continue
				elif [ $i -eq 9 ]
				then
					break
				fi
				echo "$i"
				i=$((i+1))
			done;;
		esac
fi
