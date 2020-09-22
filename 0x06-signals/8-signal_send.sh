#!/bin/sh
# send a sigquit signal to a process
if [ $# -ne 1 ]
then
	echo "Usage: $0 <pid>"
	exit 1
fi

kill -s 3 $1
