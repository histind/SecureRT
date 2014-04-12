#!/bin/bash
while true
do
	RET=$(gpio read 1)
	echo $RET
	if [ $RET -eq 1 ] 
	then
		echo "1"
		gpio write 0 1
		gpio write 0 0
	else
		echo "$RET"
	fi
done
