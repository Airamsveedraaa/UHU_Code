#!/bin/bash

echo "Al script $0 se le han pasado $# parámetros"
echo "Los parámetros son: $1, $2"


N=$(find $1 -name "*$2*" -type f | wc -l)
echo "En el directorio $1 hay $N ficheros que contienen la cadena $2"
echo '"Fin del script"'

