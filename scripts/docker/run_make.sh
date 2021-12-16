#!/bin/bash

# variables
TOOL=$1
shift
MOUNT_PATH=$1
shift
MKFILE_PATH=$1
shift
MKFILE_NAME=$1
shift
MAKE_TARGET="$@"

# configuration
BASEDIR=$(dirname $(realpath "$0"))
RUN_DOCKER=$BASEDIR/run_docker.sh
RUN_MAKE="/home/common/scripts/docker/run_make_user_data.sh"

# Run Docker start script
source $RUN_DOCKER $TOOL $MOUNT_PATH $RUN_MAKE
