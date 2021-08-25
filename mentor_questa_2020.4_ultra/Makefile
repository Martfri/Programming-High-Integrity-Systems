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

QUESTAINSTALLERZIP=questa_2020.4_linux.zip
QUESTAINSTALLER=install
QUESTAINSTALLERSCRIPT=scripts/batchInstall.sh

FILES=$(QUESTAINSTALLER) Dockerfile

SHELL := /bin/bash

.PHONY: questa2020.4-image clean

all: questa2020.4-image

${QUESTAINSTALLERZIP}:
	smbget -w ZHAW -u smb://cannes.zhaw.ch/ines/Software/Mentor_Siemens/questa_2020.4_linux.zip

${QUESTAINSTALLER}: ${QUESTAINSTALLERZIP}
	mkdir -p $@
	unzip -j -u -d $@ $^
	cp ${QUESTAINSTALLERSCRIPT} $@
	#rm -f $^
	@touch $@


questa2020.4-image: $(FILES)
	@docker rmi questa:2020.4 &>/dev/null || true
	docker build --rm -t questa:2020.4 .
	@touch $@


clean:
	docker rmi questa:2020.4 >&/dev/null || true
	rm -f questa2020.4-image
