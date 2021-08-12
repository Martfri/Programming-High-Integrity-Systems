#-------------------------------------------------------------------------------
#  _____       ______  _____
# |_   _|     |  ____|/ ____|
#   | |  _ __ | |__  | (___    Institute of Embedded Systems
#   | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur
#  _| |_| | | | |____ ____) |  (University of Applied Sciences)
# |_____|_| |_|______|_____/   8401 Winterthur, Switzerland
#-------------------------------------------------------------------------------
# @file
# @author scdv
#-------------------------------------------------------------------------------

# Build config
# Check docker images for installed tools
TOOL := quartus:20.1.1
# This path will be mounted as top directory on docker
# must be relative to this path (empty for this path)
BUILD_TOP_PATH := ./
#Name of the Makefile which is used
MAKEFILE := Makefile


# Docker config
# LOAD_PATH path to the docker start scripts
LOAD_PATH := ${HOME}/scripts/docker

# Variables
MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
MOUNT_PATH := $(abspath $(dir $(LOCAL_PATH)$(BUILD_TOP_PATH)))
LOCAL_PATH := $(subst $(MOUNT_PATH)/, , $(dir $(MKFILE_PATH)))


.PHONY: all show_var

# run Make in Docker
show_var:
	@printf "Tool:          %s\n" $(TOOL)
	@printf "Makefile Path: %s\n" $(LOCAL_PATH)
	@printf "Mount Path:    %s\n" $(MOUNT_PATH)

# it is possible to open programs in docker using this script
# the following is an example
#
# quartus:
# 	$(LOAD_PATH)/run_docker.sh $(TOOL) $(MOUNT_PATH) quartus

all:
%:
	$(LOAD_PATH)/run_make.sh $(TOOL) $(MOUNT_PATH) $(LOCAL_PATH) $(MAKEFILE) $@
