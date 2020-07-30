#
# Copyright (c) 1998 by Sun Microsystems, Inc.
# All rights reserved.
#
#ident	"@(#)mp.conf.ko	1.3 98/03/30 SMI"
#
# Korean(EUC) font preferred version.
#

FontNameAlias	iso88591R	PCF  /usr/openwin/lib/X11/fonts/75dpi/courR18.pcf.Z
FontGroup	iso88591	PCF iso88591R

FontNameAlias	johap92R_WC	PCF  /usr/openwin/lib/locale/ko/X11/fonts/75dpi/gothic20.pcf.Z
FontGroup	johap92_WC	PCF johap92R_WC


#
#
#
MapCode2Font		0x0000 0x00FF			iso88591
MapCode2Font 		0x30000020 0x3000ffff  		johap92_WC

#
#
#
CnvCode2Font iso88591R _xuiso88591 /usr/lib/lp/locale/en_US.UTF-8/mp/xuiso88591.so
CnvCode2Font johap92R_WC  _xwc2euc /usr/lib/lp/locale/en_US.UTF-8/mp/xwceuc.so
