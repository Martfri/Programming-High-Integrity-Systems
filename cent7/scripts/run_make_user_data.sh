#!/bin/bash
printf "COMMAND received: %s\n" "$@"

WORKPATH=${HOME}/data/$TOOL4DOCKER_MK_PATH

cd $WORKPATH
make -f ./$TOOL4DOCKER_MK_NAME $TOOL4DOCKER_MK_TARGET
