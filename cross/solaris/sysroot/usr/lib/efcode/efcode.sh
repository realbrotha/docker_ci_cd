#!/sbin/sh
#
# Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#
# ident	"@(#)efcode.sh	1.2	04/10/11 SMI"

#
# The open /dev/fcode file descriptor is passed by efdaemon in file
# descriptor 0, so redirecting stdin in this script is strongly discouraged.
#
/usr/lib/efcode/sparcv9/interpreter
