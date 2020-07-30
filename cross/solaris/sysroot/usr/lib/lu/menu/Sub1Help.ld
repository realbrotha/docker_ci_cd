#
#ident	"@(#)Sub1Help.ld	5.1	01/04/04 SMI"
#
# Copyright (c) 2001 Sun Microsystems, Inc.  All Rights Reserved.
#
title=`gettext "Local Device Retrieval Method"`

close=nop
wrap=true
altslks=true

begrow=any
begcol=any
rows=7
columns=73

`gettext "Strike the CANCEL function key to return to main menu." | message`

text="\n"`gettext "The Local Device Retrieval method allows you to retrieve an archive from an arbitrary block device.  You can specify the following options:"`"\n"\
`gettext "Device:\tThis is the full device path used to retrieve the archive.  For example, /dev/dsk/c0t6d0s0.  If the path does not start with \'/\', it is assumed to be relative to /dev/dsk."`"\n"\
`gettext "Path:\tThis is the filesystem path on the device, which will be used to retrieve the archive.  For example, /home/archive.flar.  The path must start with \'/\'."`"\n"\
`gettext "Filesystem Type:\tThis is the type of filesystem that exists on the device.  For example, hsfs.  The filesystem type will be used when mounting the filesystem from the specified device."`"\n"\

`indicator -w`

name= 
button=9
action=nop

name=
button=10
action=nop

name=
button=11
action=nop

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

name=
button=16
action=help
