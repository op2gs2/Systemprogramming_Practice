#!/bin/bash

while [ 1 ]; do
	$status = ps -ef | grep hello
	if [ "$status" == "hello" ]; then
		echo '[shell] Restarting ./hello!'
		./hello
	fi
done