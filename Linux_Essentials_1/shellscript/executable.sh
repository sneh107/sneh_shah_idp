#!/bin/bash

read -p "Enter location of dir : " loc

fileholder=$(find $loc -maxdepth 1 -type f -executable ! -name "executable.sh")

for file in $fileholder
do
	echo "Executing $file"
	starttime=$(date +%s)
	$file
	finishtime=$(date +%s)
	timetaken=$((finishtime-starttime))
	echo "Time take $timetaken seconds."
done
