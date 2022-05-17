#!/bin/bash

usage () {
	echo 
	echo "Usage $0 <port> <dir>"
	echo 
	echo -e "\t <port> is the port number where artemis will listen."
	echo -e "\t        ASK Professor for a port number to use"
	echo 
	echo -e "\t <dir> is directory where to install artemis"
	echo 
	echo -e "\t example:"
	echo -e "\t     $0 9500 $HOME/DiscoW/csd/jms"

	exit 1
}


if [ $# -ne 2 ] ; then 
	usage
fi

PORT=$1
DIR=$2

# Check port is a number, greater than 1024
if [ -n "$PORT" ] && [ "$PORT" -eq "$PORT" ] && [ "$PORT" -gt 1024 ] 2>/dev/null; then
    true  # Nothing, just ok.
else
    usage
fi


# If directory already exists, don't continue
if [ -r $DIR ] ; then
	echo ERROR: directory \"$DIR\" already exits.
	echo Remove it before running this command again
	exit 1
fi

# If cannot create directory, don't continue
mkdir -p $DIR 2>/dev/null
if [ $? -ne 0 ] ; then
	echo ERROR: Cannot create directory \"$DIR\"
	echo Double check directory name, and check your permissions
	exit 1
fi

# Port for Web console
WPORT=$(($PORT+1))

# Let's go !
echo
echo " ==> Installing artemis in $DIR, using port $PORT and Web port $WPORT..."
echo " ==> Remember using same port when starting CsdMessengerServer/CsdMessengerClient"
echo


./artemis create \
	--default-port $PORT \
	--http-port $WPORT \
	--allow-anonymous \
	--user admin \
	--password admin \
	--queues csd:anycast \
	--no-autocreate \
	--relax-jolokia \
	--no-autotune \
	--no-amqp-acceptor \
	--no-hornetq-acceptor \
	--no-mqtt-acceptor \
    --no-stomp-acceptor	\
	$DIR 

