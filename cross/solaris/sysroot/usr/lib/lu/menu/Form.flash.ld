#
#ident	"@(#)Form.flash.ld	5.1	01/04/04 SMI"
#
# Copyright (c) 2001 Sun Microsystems, Inc.  All Rights Reserved.
#
#############################################################################
#	Module Name:  Form.flash.ld
#       Arguments:    $ARG1 - The next archive_id to use when adding archive.
#############################################################################
# This form asks for the required information for retrieving flash archives
# through a generic device.
#############################################################################

# Form-wide infomation.

form=`gettext "Local Device Retrieval"`
help=OPEN TEXT $OBJ_DIR/Sub1Help.ld
altslks=true

# File used to gather output from pfinstall
`set -l VERIFYOUT="/tmp/pfinstall.flash.verify.${VPID}`

# We don't want this file to stick around
close=`rm -f ${VERIFYOUT}`

############################################################################
# This block is run when the user attempts to accept what they
# have entered.  Here, we go run pfinstall and pass the line
# that would normally end up in a pfinstall profile.  If pfinstall
# is able to verify the archive, we add it to the list and
# close this form.  Otherwise, we pop up a message and refuse
# to leave.
############################################################################
done=`
	message -w;
	set -l LOCSPEC="archive_location local_device ${F1} ${F2} ${F3}";
	set -e LD_LIBRARY_PATH="$MRPATH/usr/snadm/lib";
	$MRPATH/usr/sbin/install.d/pfinstall -F ${LOCSPEC} > ${VERIFYOUT} 2> ${VERIFYOUT} ;
	if [ "${RET}" != 0 ] ;
	then
		set -l CMD="open text $OBJ_DIR/Text.flash.invalid ${VERIFYOUT}";
	else
		set -l SPEC="${ARG1}|Local Device|${F1}:${F2}:${F3}|${LOCSPEC}";
		echo $SPEC >> ${ARCHIVELIST};
		set -l CMD="close";
	fi;`$CMD

############################################################################
# Field: Device
# Format: "Device:  _________"
# Validation: Must be a valid file
############################################################################
# i18n: should be 15 characters or less
name=`gettext "Device"`":"
nrow=1
ncol=2
frow=1
fcol=18
rows=1
columns=50
scroll=true

# default value, not localized
value="/dev/dsk/c0t6d0s0"

# check to see if it's a real device
valid=`if [ -r "${F1}" ] ; then
		echo TRUE;
	else
		echo FALSE;
	fi;`

invalidmsg=`gettext "ERROR: Device ${F1} cannot be accessed"`

############################################################################
# Field: Path
# Format: "Path:  _________"
# Validation: none
############################################################################
name=`gettext "Path"`":"
nrow=2
ncol=2
frow=2
fcol=15
rows=1
columns=50
scroll=true

# default value
value=`gettext '/path/to/archive.flar'`

############################################################################
# Field: Filesystem type
# Format: "Filesystem type:  _________"
# Validation: Must be a valid fs type on this system
############################################################################
name="`gettext "Filesystem Type"`:"
nrow=3
ncol=2
frow=3
fcol=20
rows=1
columns=40
scroll=true
# we don't translate hsfs
value="hsfs"

#Here the validations should include:
# local filesystem type should be accessible and mountable
valid=`if [ -z "${F3}" -o -x "/usr/lib/fs/${F3}/mount" ] ; then
		echo TRUE;
	else
		echo FALSE;
	fi;`

invalidmsg=`gettext "ERROR: No support for ${F3} in /usr/lib/fs/${F3}/mount"`


############################################################################
# SLK Buttons.  Only save, cancel, and help do stuff.
############################################################################
name= 
button=9
action=nop

name=
button=10
action=nop

name=`gettext "SAVE"`
button=11
action=done

NAME=
button=12
action=nop

name=
button=13
action=nop

name=`gettext "CANCEL"`
button=14
action=cancel

name=
button=15
action=help

name=`gettext "HELP"`
button=16
action=help
