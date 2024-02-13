#!/bin/bash

read -p "Enter Location where you want to replace : " loc

cd $loc

fileholder=$(ls *.txt)

for file in $fileholder
do
	mv "$file" "${file%.txt}.text"
done

cd -

echo "Renamed Successfully!"
