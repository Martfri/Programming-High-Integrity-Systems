#!/bin/bash

# variables
LOCAL_SCRIPT_PATH=$1
DOCKER_SCRIPT_PATH=$(realpath $(dirname $(realpath "$0"))/../docker)

if [[ -d $LOCAL_SCRIPT_PATH ]]; then
    for script in $DOCKER_SCRIPT_PATH/*.sh ; do
        ln -s $script $LOCAL_SCRIPT_PATH/$(basename $script)
        echo "created symbolic link:" $LOCAL_SCRIPT_PATH/$(basename $script)
    done

else
    echo "This scripts creates symbolic links in the local script folder for the docker scripts"
    echo "It must be called with an existing Path as argument"
    exit 1
fi
