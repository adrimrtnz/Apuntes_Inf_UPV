#!/bin/bash
# arguments
echo El numero de argumentos es: $#
echo La orden completa tecleada es: $0 $@
echo La orden tecleada es: $0

N=1

for i in $@
do
    echo El argumento \"$N\" es: $i
    N=$((N+1))
done
