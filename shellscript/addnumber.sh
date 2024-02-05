#!/bin/bash

read -p "Enter numbers to add : " num

sum=0

for (( i=1;i<=$num;i++ ))
do
	read -p "Enter no. : " add
	sum=$((sum+add))
done

echo "Sum is : $sum"
