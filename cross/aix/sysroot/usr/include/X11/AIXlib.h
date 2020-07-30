/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* gos530 src/gos/2d/XTOP/include/extensions/AIXlib.h 1.5                 */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1992,1994          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)98       1.5  src/gos/2d/XTOP/include/extensions/AIXlib.h, xext, gos530 2/10/94 14:53:25 */
/********************************************************************/
/*
 *   COMPONENT_NAME: X11
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 16,27,40,42,27
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1992
 *   All Rights Reserved
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/********************************************************************/

#ifndef _AIXLIB_H
#define _AIXLIB_H

#include "AIX.h"
#include "Xlib.h"



_XFUNCPROTOBEGIN

/**
***   aixCursorExtension XLIB interface function prototypes
**/
extern Bool XCursorQueryExtension();

extern Status XCursorQueryVersion();

extern Status XGetCrossHairCursorInfo();

extern Status XGetMultiColorCursorInfo();

extern Status XRecolorCrossHairCursor();

extern Cursor XCreateCrossHairCursor();

extern Status XQueryCrossHairCursor();

extern Cursor XCreateMultiColorCursor();

extern Status XRecolorMultiColorCursor();


/**
***   aixDirectAccessExtension XLIB interface function prototypes
**/

extern Bool   XDirectAccessQueryExtension();
extern Status XDirectAccessQueryVersion();   

_XFUNCPROTOEND



#endif /* _AIXLIB_H */
