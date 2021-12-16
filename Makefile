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

# Tool selection
TOOLS += mentor_questa_2020.4_ultra
TOOLS += intel_quartus_20.1_standard

INSTALL = cent7 $(TOOLS)


.PHONY: cent7 $(TOOLS) clean_install clean

all: $(INSTALL)

# Make Tools
$(TOOLS): cent7
	@make -C $@
	docker image prune -f

# Make Cent7
cent7:
	@make -C $@
	docker image prune -f

clean_install:
	$(foreach TOOL, $(INSTALL), $(MAKE) -C $(TOOL) clean_install;)

clean:
	$(foreach TOOL, $(INSTALL), $(MAKE) -C $(TOOL) clean;)
	docker image prune -f
