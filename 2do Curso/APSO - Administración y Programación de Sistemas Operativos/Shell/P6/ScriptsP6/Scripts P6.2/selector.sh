#!/bin/bash 

for p in $@
do
	if [ -f ~/$p ]
	then
		case $p in 
			???????*) cp $p /home/luisairam.saavedra/ModuloI/Practica6/largos/;;
			*) cp $p /home/luisairam.saavedra/ModuloI/Practica6/cortos/;;
		esac
	fi
done
