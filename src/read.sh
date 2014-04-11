#!/bin/bash
while true
do
	RET=$(gpio read 1)
	echo $RET
	if [ $RET -eq 1 ] 
	then
		echo "1"
	else
		echo "$RET"
	fi
done
