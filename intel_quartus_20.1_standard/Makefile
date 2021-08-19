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

QUARTUSCOMPLETEINSTALLER=Quartus-20.1.1.720-linux-complete.tar
QUARTUSCOMPLETECHECKSUM=2C480C1BDE5C73DDC0FB20DB69F74A07

HLSINSTALLER=HLSProSetup-21.2.0.72-linux.run
HLSCHECKSUM=DE0AACFDB8C4381AE5D45256733F0B25

FILES=$(HLSINSTALLER) $(QUARTUSCOMPLETEINSTALLER) Dockerfile

SHELL := /bin/bash

.PHONY: quartus20-image clean

all: quartus-20-1-1-image

${QUARTUSCOMPLETEINSTALLER}:
	curl -O https://download.altera.com/akdlm/software/acdsinst/20.1std.1/720/ib_tar/Quartus-20.1.1.720-linux-complete.tar
	@SUM=$$(md5sum $(QUARTUSCOMPLETEINSTALLER) | awk '{print toupper($$1)}'); \
		if [ "$$SUM" != "$(QUARTUSCOMPLETECHECKSUM)" ]; then echo "Checksum for Quartus Installer doesn't match."; exit 1; fi

${HLSINSTALLER}:
	curl -O https://download.altera.com/akdlm/software/acdsinst/21.2/72/ib_installers/HLSProSetup-21.2.0.72-linux.run
	@SUM=$$(md5sum $(HLSINSTALLER) | awk '{print toupper($$1)}'); \
		if [ "$$SUM" != "$(HLSCHECKSUM)" ]; then echo "Checksum for HLS Installer doesn't match."; exit 1; fi


quartus-20-1-1-image: $(FILES)
	@docker rmi quartus:20.1.1 &>/dev/null || true
	docker build --rm -t quartus:20.1.1 .
	@touch $@


clean:
	docker rmi quartus:20.1.1 >&/dev/null || true
	rm -f quartus-20-1-1-image
