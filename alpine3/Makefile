# --------------------------------------------------------------------
#   _____       ______  _____
#  |_   _|     |  ____|/ ____|
#    | |  _ __ | |__  | (___    Institute of Embedded Systems
#    | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur
#   _| |_| | | | |____ ____) |  (University of Applied Sciences)
#  |_____|_| |_|______|_____/   8401 Winterthur, Switzerland
# --------------------------------------------------------------------
#  @file Makefile
#  @author scdv, leiu
# --------------------------------------------------------------------

include ./shvars.mk


.PHONY: $(IMG_NAME) clean_install clean


all: $(IMG_NAME)


$(IMG_NAME): $(DKRFIL)
	@$(DKR) rmi $(DKR_TAG) 1> $(NIL) 2> $(NIL) || true
	$(DKR) build --rm -t $(DKR_TAG) . \
    --build-arg user_uid=$$(id -u)    \
    --build-arg user_gid=$$(id -g)    \
    --build-arg user_name=$$(whoami)
	@touch $@


clean_install:
	-rm -f $(IMG_NAME)


clean:
	$(DKR) rmi $(DKR_TAG) 1> $(NIL) 2> $(NIL) || true
	-rm -f $(IMG_NAME)

