/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* gos530 src/gos/2d/XTOP/lib/Xt/CompositeP.h 1.1                         */
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
/* @(#)79  1.1  src/gos/2d/XTOP/lib/Xt/CompositeP.h, xtoolkit, gos530 7/11/96 18:01:35 */
/* SCCSID_END_TAG                                                      */
/* $XConsortium: CompositeP.h,v 1.17 94/04/17 20:13:43 converse Exp $ */

/***********************************************************

Copyright (c) 1987, 1988  X Consortium

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


Copyright 1987, 1988 by Digital Equipment Corporation, Maynard, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of Digital not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

#ifndef _XtCompositeP_h
#define _XtCompositeP_h

#include <X11/Composite.h>

/************************************************************************
 *
 * Additional instance fields for widgets of (sub)class 'Composite' 
 *
 ************************************************************************/

typedef struct _CompositePart {
    WidgetList  children;	     /* array of ALL widget children	     */
    Cardinal    num_children;	     /* total number of widget children	     */
    Cardinal    num_slots;           /* number of slots in children array    */
    XtOrderProc insert_position;     /* compute position of new child	     */
} CompositePart,*CompositePtr;

typedef struct _CompositeRec {
    CorePart      core;
    CompositePart composite;
} CompositeRec;

/*********************************************************************
 *
 *  Additional class fields for widgets of (sub)class 'Composite'
 *
 ********************************************************************/

typedef struct _CompositeClassPart {
    XtGeometryHandler geometry_manager;	  /* geometry manager for children   */
    XtWidgetProc      change_managed;	  /* change managed state of child   */
    XtWidgetProc      insert_child;	  /* physically add child to parent  */
    XtWidgetProc      delete_child;	  /* physically remove child	     */
    XtPointer	      extension;	  /* pointer to extension record     */
} CompositeClassPart,*CompositePartPtr;

typedef struct {
    XtPointer next_extension;	/* 1st 4 mandated for all extension records */
    XrmQuark record_type;	/* NULLQUARK; on CompositeClassPart */
    long version;		/* must be XtCompositeExtensionVersion */
    Cardinal record_size;	/* sizeof(CompositeClassExtensionRec) */
    Boolean accepts_objects;
    Boolean allows_change_managed_set;
} CompositeClassExtensionRec, *CompositeClassExtension;


typedef struct _CompositeClassRec {
     CoreClassPart      core_class;
     CompositeClassPart composite_class;
} CompositeClassRec;

externalref CompositeClassRec compositeClassRec;

#define XtCompositeExtensionVersion 2L
#define XtInheritGeometryManager ((XtGeometryHandler) _XtInherit)
#define XtInheritChangeManaged ((XtWidgetProc) _XtInherit)
#define XtInheritInsertChild ((XtWidgetProc) _XtInherit)
#define XtInheritDeleteChild ((XtWidgetProc) _XtInherit)

#endif /* _XtCompositeP_h */
/* DON'T ADD STUFF AFTER THIS #endif */
