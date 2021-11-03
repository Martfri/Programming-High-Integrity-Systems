
# --------------------------------------------------------------------
#   _____       ______  _____
#  |_   _|     |  ____|/ ____|
#    | |  _ __ | |__  | (___    Institute of Embedded Systems
#    | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur
#   _| |_| | | | |____ ____) |  (University of Applied Sciences)
#  |_____|_| |_|______|_____/   8401 Winterthur, Switzerland
# --------------------------------------------------------------------
#  @file shvars.mk
#  @author scdv, leiu
# --------------------------------------------------------------------

SHELL := /bin/bash
NIL   := /dev/null

DKR    := docker
DKRFIL := Dockerfile

OS_MAJOR := alpine3
OS_MINOR := pedantic
OS_APDX  := image

IMG_NAME := $(OS_MAJOR)-$(OS_MINOR)-$(OS_APDX)
DKR_TAG  := $(OS_MAJOR)-$(OS_MINOR)

