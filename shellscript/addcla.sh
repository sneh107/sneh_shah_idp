#!/bin/bash

if [ $# -eq 0 ]
then
    echo "Add Arguments"
fi

sum=0

for arg in $*
do
    sum=$((sum + arg))
done

echo "Sum of the numbers is: $sum"
