# --------------------------------------------------------------------
#   _____       ______  _____
#  |_   _|     |  ____|/ ____|
#    | |  _ __ | |__  | (___    Institute of Embedded Systems
#    | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur
#   _| |_| | | | |____ ____) |  (University of Applied Sciences)
#  |_____|_| |_|______|_____/   8401 Winterthur, Switzerland
# --------------------------------------------------------------------
#  @file alpine3-pedantic.mk
#  @author scdv, leiu
# --------------------------------------------------------------------

include ./shvars.mk


.PHONY: $(DKR_TAG)


$(DKR_TAG):
	@docker image inspect $(DKR_TAG) &>/dev/null || \
     (echo "$(DKR_TAG) image does not exist"; exit 1 )

