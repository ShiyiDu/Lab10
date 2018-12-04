#!/bin/bash

gpio mode 0 out
gpio mode 1 out
gpio mode 2 out

gpio write 0 0
gpio write 1 0
gpio write 2 0

start=`./tempread`
echo "initail temperature $start"

while(true)
do
	current=`./tempread`
	echo "current $current"
	let "diff=current-start"
	
	if(($diff>=1000 && $diff<2000)); then
		gpio write 0 1
		gpio write 1 0
		gpio write 2 0
	elif(($diff>=2000 && $diff<3000)); then
		gpio write 0 1
		gpio write 1 1
		gpio write 2 0
	elif(($diff>=3000)); then
		gpio write 0 1
		gpio write 1 1
		gpio write 2 1
	else
		gpio write 0 0
		gpio write 1 0
		gpio write 2 0
	fi
	
done
