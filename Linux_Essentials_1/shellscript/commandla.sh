#!/bin/bash

if [ $# -lt 1 ]
then
	echo "Enter atleast one argument!"
else
	echo "Number of Arguments = $#"
fi

i=1
for arg in $*
do
	echo "Argument $i : $arg"
	i=$((i+1))
done

echo "First Argument = $1"
