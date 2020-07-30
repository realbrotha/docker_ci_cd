#!/bin/csh
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# gos530 src/gos/2d/XTOP/aixclients/xdm/config/Xsession.csh 1.1 
#  
# Licensed Materials - Property of IBM 
#  
# (C) COPYRIGHT International Business Machines Corp. 1994 
# All Rights Reserved 
#  
# US Government Users Restricted Rights - Use, duplication or 
# disclosure restricted by GSA ADP Schedule Contract with IBM Corp. 
#  
# IBM_PROLOG_END_TAG 
# @(#)88        1.1  src/gos/2d/XTOP/aixclients/xdm/config/Xsession.csh, xdmcp, gos530 2/28/94 13:35:34
#
# COMPONENT_NAME: XDMCP
#
# FUNCTIONS: Xsession
#
# ORIGINS: 27
#
# (C) COPYRIGHT International Business Machines Corp. 1994
# All Rights Reserved
# Licensed Materials - Property of IBM
#
# US Government Users Restricted Rights - Use, duplication or
# disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#

#
# This script is called from /usr/lib/X11/xdm/Xsession when
# setting up the customized environment for a csh user.
# Note: The system administrator must uncomment the code in
#       /usr/lib/X11/xdm/Xsession that calls this file.
#

#
# set up the users custom environment
#
if (-r $HOME/.login) then
    source $HOME/.login
endif

#
# Start the users X session
#
set startup=$HOME/.xsession
set resources=$HOME/.Xresources

if ( -f /usr/bin/X11/startx ) then
        exec /usr/bin/X11/startx -t -wait
else if ( -f $startup ) then
        exec $startup
else
        if ( -f $resources ) then
                xrdb -retain $resources
        endif

        if ( -f "/usr/lib/X11/$LANG/xinitrc" ) then
                /bin/ksh /usr/lib/X11/$LANG/xinitrc
        else if ( -f "/usr/lpp/X11/defaults/$LANG/xinitrc" ) then
                /bin/ksh /usr/lpp/X11/defaults/$LANG/xinitrc
        else if ( -f "/usr/lpp/X11/defaults/xinitrc" ) then
                /bin/ksh /usr/lpp/X11/defaults/xinitrc
        else
                (mwm &)
                exec aixterm -geometry 80x35+0-0 -ls
        endif
endif


