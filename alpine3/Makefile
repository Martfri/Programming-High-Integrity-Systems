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

DL     := wget
TAR    := tar
EXT    := http://jupiter-win.zhaw.ch/mariana-trench/docker/from_scratch
FOLDER := alpine_linux_3-14
BUNDLE := $(FOLDER).tar.gz

.PHONY: $(IMG_NAME) clean_install clean purge


all: $(IMG_NAME)


$(BUNDLE):
	$(DL) $(EXT)/$@ -O ./$@
	$(TAR) xvf $@


$(IMG_NAME): $(DKRFIL) $(BUNDLE)
	@$(DKR) rmi $(DKR_TAG) 1> $(NIL) 2> $(NIL) || true
	$(DKR) build --rm -t $(DKR_TAG) . \
    --build-arg user_uid=$$(id -u)    \
    --build-arg user_gid=$$(id -g)    \
    --build-arg user_name=$$(whoami)  \
	--build-arg PKGS_LST="$(shell cd scripts && bash echo_pkgs_build_arg.bash)"
	@touch $@


clean_install:
	-rm -f $(IMG_NAME)


clean:
	-rm -rf $(BUNDLE) $(FOLDER)


purge:
	$(DKR) rmi $(DKR_TAG) 1> $(NIL) 2> $(NIL) || true
	-rm -rf $(IMG_NAME) $(BUNDLE) $(FOLDER)

