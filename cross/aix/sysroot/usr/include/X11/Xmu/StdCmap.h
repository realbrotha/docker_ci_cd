/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* gos530 src/gos/2d/XTOP/lib/Xmu/StdCmap.h 1.1                           */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1996               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* SCCSID_BEGIN_TAG                                                    */
/* @(#)81  1.1  src/gos/2d/XTOP/lib/Xmu/StdCmap.h, xsample, gos530 7/12/96 11:27:31 */
/* SCCSID_END_TAG                                                      */
/* $XConsortium: StdCmap.h,v 1.4 94/04/17 20:16:15 converse Exp $ */

/*
 
Copyright (c) 1988  X Consortium

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the X Consortium shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from the X Consortium.

*/

/*
 * The interfaces described by this header file are for miscellaneous utilities
 * and are not part of the Xlib standard.
 */

#ifndef _XMU_STDCMAP_H_
#define _XMU_STDCMAP_H_

#include <X11/Xfuncproto.h>

_XFUNCPROTOBEGIN

Status XmuAllStandardColormaps(
#if NeedFunctionPrototypes
    Display*		/* dpy */
#endif
);

Status XmuCreateColormap(
#if NeedFunctionPrototypes
    Display*		/* dpy */,
    XStandardColormap*	/* colormap */
#endif
);

void   XmuDeleteStandardColormap(
#if NeedFunctionPrototypes
    Display*		/* dpy */,
    int			/* screen */,
    Atom		/* property */
#endif
);

Status XmuGetColormapAllocation(
#if NeedFunctionPrototypes
    XVisualInfo*	/* vinfo */,
    Atom		/* property */,
    unsigned long*	/* red_max_return */,
    unsigned long*	/* green_max_return */,
    unsigned long*	/* blue_max_return */
#endif
);

Status XmuLookupStandardColormap(
#if NeedFunctionPrototypes
    Display*		/* dpy */,
    int			/* screen */,
    VisualID		/* visualid */,
    unsigned int	/* depth */,
    Atom		/* property */,
    Bool		/* replace */,
    Bool		/* retain */
#endif
);

XStandardColormap *XmuStandardColormap(
#if NeedFunctionPrototypes
    Display*		/* dpy */,
    int			/* screen */,
    VisualID		/* visualid */,
    unsigned int	/* depth */,
    Atom		/* property */,
    Colormap		/* cmap */,
    unsigned long	/* red_max */,
    unsigned long	/* green_max */,
    unsigned long	/* blue_max */
#endif
);

Status XmuVisualStandardColormaps(
#if NeedFunctionPrototypes
    Display*		/* dpy */,
    int			/* screen */,
    VisualID		/* visualid */,
    unsigned int	/* depth */,
    Bool		/* replace */,
    Bool		/* retain */
#endif
);

_XFUNCPROTOEND

#endif /* _XMU_STDCMAP_H_ */
