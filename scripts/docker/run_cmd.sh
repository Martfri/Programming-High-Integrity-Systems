#!/bin/bash

# variables
TOOL=$1
shift
MOUNT_PATH=$1
shift
MKFILE_PATH=$1
shift
GENERIC_CMD=$1
shift
GENERIC_ARG="$@"

# configuration
BASEDIR=$(dirname $(realpath "$0"))
RUN_DOCKER=$BASEDIR/run_docker.sh
RUN_CMD="/home/common/scripts/docker/run_cmd.sh"

# Run Docker start script
source $RUN_DOCKER $TOOL $MOUNT_PATH $RUN_CMD
