#!/bin/bash

echo "Proceso padre (inicio) ..."
export V1=10
echo "V1=$V1"
ps -u
./hijo.sh
echo "V1=$V1"
echo "Proceso padre (fin)..."
