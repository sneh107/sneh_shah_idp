#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Enter Argument"
fi


processname="$1"

pids=$(pgrep "$processname")

if [ -n "$pids" ]
then
	echo "$pids"
else
	echo "No process named "$processname""
fi
