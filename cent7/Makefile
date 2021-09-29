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

SHELL := /bin/bash

.PHONY: cent7-base-image clean_install clean

all: cent7-base-image

cent7-base-image: Dockerfile
	@docker rmi cent7-base &>/dev/null || true
	docker build --rm -t cent7-base . \
	--build-arg user_uid=$$(id -u) \
	--build-arg user_gid=$$(id -g) \
	--build-arg user_name=$$(whoami)
	@touch $@

clean_install:
	rm -f cent7-base-image

clean:
	docker rmi cent7-base >&/dev/null || true
	rm -f cent7-base-image
