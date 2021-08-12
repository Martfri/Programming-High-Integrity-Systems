#!/bin/bash
CMD="$1"
shift
ARGUMENTS="$@"
shift
CMDSTR=$(printf "%s %s" $CMD $ARGUMENTS)

# startup scripts
source /home/common/scripts/mentor/questa2020.4.sh
source /home/common/scripts/intel/quartus20.1_HLS.sh

# run command
exec /bin/bash -login -c -m "$CMDSTR"
