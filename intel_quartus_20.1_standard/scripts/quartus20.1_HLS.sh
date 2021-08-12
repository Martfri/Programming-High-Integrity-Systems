# quartus
INSTALL_DIR=/opt/intel/intelFPGA/20.1
QUARTUS_64BIT=1
# quartus root directory
QUARTUS_ROOTDIR=$INSTALL_DIR/quartus
HLS_ROOTDIR=$INSTALL_DIR/hls
# ARM EDS

#license
LM_LICENSE_FILE=$LM_LICENSE_FILE:26010@aberdeen.zhaw.ch

# path
PATH=$PATH:$QUARTUS_ROOTDIR/bin:$INSTALL_DIR/nios2eds/bin:$QUARTUS_ROOTDIR/linux64:$QUARTUS_ROOTDIR/sopc_builder/bin:$INSTALL_DIR/nios2eds/sdk2/bin:$INSTALL_DIR/nios2eds/bin/gnu/H-x86_64-pc-linux-gnu/bin

export PATH QUARTUS_ROOTDIR QUARTUS_64BIT LM_LICENSE_FILE

source $HLS_ROOTDIR/init_hls.sh
