#!/bin/bash

read -p "Enter path : " path

cd $path

fileholder=$(ls *.txt)

for file in $fileholder
do
	mv "$file" "${file%.txt}.text"
done

cd -

echo "renamed succesfully"
