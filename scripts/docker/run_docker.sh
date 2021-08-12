#!/bin/bash

# variables
TOOL=$1
shift
MOUNT_PATH=$1
shift
CMD="$@"
shift

# variables
BASEDIR=$(realpath $(dirname $(realpath "$0"))/../../)
CFGDIR=$HOME/.tools4docker

mkdir -p $CFGDIR

if [[ "$DISPLAY" == "" ]]; then
	echo "DISPLAY environment variable is not set. An X display is required to run."
	exit 1
fi

DISPLAY=$($BASEDIR/cent7/xauth $TOOL-$(whoami) $CFGDIR/.Xauthority)

if [[ "$DISPLAY" == :* ]]; then
	x11flags="--ipc=host -v /tmp/.X11-unix:/tmp/.X11-unix"
else
	x11flags="-e QT_X11_NO_MITSHM=1 -e _X11_NO_MITSHM=1 -e _MITSHM=0"
fi

docker run --rm -it \
-u $(id -u):$(id -g) \
-e DISPLAY $x11flags $ethernet \
-h $TOOL-$(whoami) \
-v $MOUNT_PATH:/home/$(whoami)/data \
-e TOOL4DOCKER_MK_PATH=$MKFILE_PATH \
-e TOOL4DOCKER_MK_NAME=$MKFILE_NAME \
-e TOOL4DOCKER_MK_TARGET=$MAKE_TARGET \
$TOOL $CMD
