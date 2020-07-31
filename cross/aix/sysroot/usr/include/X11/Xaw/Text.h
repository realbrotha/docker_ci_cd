/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* gos530 src/gos/2d/XTOP/lib/Xaw/Text.h 1.1                              */
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
/* @(#)90  1.1  src/gos/2d/XTOP/lib/Xaw/Text.h, xsample, gos530 7/12/96 13:09:13 */
/* SCCSID_END_TAG                                                      */
/* $XConsortium: Text.h,v 1.45 94/04/17 20:13:05 kaleb Exp $ */

/***********************************************************

Copyright (c) 1987, 1988, 1994  X Consortium

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

#ifndef _XawText_h
#define _XawText_h

#include <X11/Xaw/Simple.h>

/*
 Text widget

 Class: 	textWidgetClass
 Class Name:	Text
 Superclass:	Simple

 Resources added by the Text widget:

 Name		     Class	     RepType		Default Value
 ----		     -----	     -------		-------------
 autoFill	    AutoFill	     Boolean		False
 bottomMargin	    Margin	     Position		2
 displayPosition    TextPosition     XawTextPosition	0
 insertPosition	    TextPosition     XawTextPosition	0
 leftMargin	    Margin	     Position		2
 resize		    Resize	     XawTextResizeMode	XawTextResizeNever
 rightMargin	    Margin	     Position		4
 scrollHorizontal   Scroll	     XawTextScrollMode	XawtextScrollNever
 scrollVertical     Scroll	     XawTextScrollMode  XawtextScrollNever
 selectTypes        SelectTypes      Pointer            see documentation
 textSink	    TextSink	     Widget		NULL
 textSource	    TextSource	     Widget		NULL
 topMargin	    Margin	     Position		2
 unrealizeCallback  Callback	     Callback		NULL
 wrap		    Wrap	     XawTextWrapMode	XawTextWrapNever

*/

typedef long XawTextPosition;

typedef enum { XawtextScrollNever,
	       XawtextScrollWhenNeeded, XawtextScrollAlways} XawTextScrollMode;

typedef enum { XawtextWrapNever, 
	       XawtextWrapLine, XawtextWrapWord} XawTextWrapMode;

typedef enum { XawtextResizeNever, XawtextResizeWidth,
	       XawtextResizeHeight, XawtextResizeBoth} XawTextResizeMode;

typedef enum {XawsdLeft, XawsdRight} XawTextScanDirection;
typedef enum {XawtextRead, XawtextAppend, XawtextEdit} XawTextEditType;
typedef enum {XawselectNull, XawselectPosition, XawselectChar, XawselectWord,
    XawselectLine, XawselectParagraph, XawselectAll} XawTextSelectType;

typedef struct {
    int  firstPos;
    int  length;
    char *ptr;
    unsigned long format;
    } XawTextBlock, *XawTextBlockPtr; 

#include <X11/Xaw/TextSink.h>
#include <X11/Xaw/TextSrc.h>

#define XtEtextScrollNever "never"
#define XtEtextScrollWhenNeeded "whenneeded"
#define XtEtextScrollAlways "always"

#define XtEtextWrapNever "never"
#define XtEtextWrapLine "line"
#define XtEtextWrapWord "word"

#define XtEtextResizeNever "never"
#define XtEtextResizeWidth "width"
#define XtEtextResizeHeight "height"
#define XtEtextResizeBoth "both"

#define XtNautoFill "autoFill"
#define XtNbottomMargin "bottomMargin"
#define XtNdialogHOffset "dialogHOffset"
#define XtNdialogVOffset "dialogVOffset"
#define XtNdisplayCaret "displayCaret"
#define XtNdisplayPosition "displayPosition"
#define XtNleftMargin "leftMargin"
#define XtNrightMargin "rightMargin"
#define XtNscrollVertical "scrollVertical"
#define XtNscrollHorizontal "scrollHorizontal"
#define XtNselectTypes "selectTypes"
#define XtNtopMargin "topMargin"
#define XtNwrap "wrap"

#define XtCAutoFill "AutoFill"
#define XtCScroll "Scroll"
#define XtCSelectTypes "SelectTypes"
#define XtCWrap "Wrap"

#ifndef _XtStringDefs_h_
#define XtNinsertPosition "insertPosition"
#define XtNresize "resize"
#define XtNselection "selection"
#define XtCResize "Resize"
#endif

/* Return Error code for XawTextSearch */

#define XawTextSearchError      (-12345L)

/* Return codes from XawTextReplace */

#define XawReplaceError	       -1
#define XawEditDone		0
#define XawEditError		1
#define XawPositionError	2

extern unsigned long FMT8BIT;
extern unsigned long XawFmt8Bit;
extern unsigned long XawFmtWide;

/* Class record constants */

extern WidgetClass textWidgetClass;

typedef struct _TextClassRec *TextWidgetClass;
typedef struct _TextRec      *TextWidget;

_XFUNCPROTOBEGIN

extern XrmQuark _XawTextFormat(
#if NeedFunctionPrototypes
    TextWidget		/* tw */
#endif
);

extern void XawTextDisplay(
#if NeedFunctionPrototypes
    Widget		/* w */
#endif
); 

extern void XawTextEnableRedisplay(
#if NeedFunctionPrototypes
    Widget		/* w */
#endif
);

extern void XawTextDisableRedisplay(
#if NeedFunctionPrototypes
    Widget		/* w */
#endif
);

extern void XawTextSetSelectionArray(
#if NeedFunctionPrototypes
    Widget		/* w */,
    XawTextSelectType*	/* sarray */
#endif
);

extern void XawTextGetSelectionPos(
#if NeedFunctionPrototypes
    Widget		/* w */,
    XawTextPosition*	/* begin_return */,
    XawTextPosition*	/* end_return */
#endif
);

extern void XawTextSetSource(
#if NeedFunctionPrototypes
    Widget		/* w */,
    Widget		/* source */,
    XawTextPosition	/* position */
#endif
);

extern int XawTextReplace(
#if NeedFunctionPrototypes
    Widget		/* w */,
    XawTextPosition	/* start */,
    XawTextPosition	/* end */,
    XawTextBlock*	/* text */
#endif
);

extern XawTextPosition XawTextTopPosition(
#if NeedFunctionPrototypes
    Widget		/* w */
#endif
);

extern void XawTextSetInsertionPoint(
#if NeedFunctionPrototypes
    Widget		/* w */,
    XawTextPosition	/* position */
#endif
);

extern XawTextPosition XawTextGetInsertionPoint(
#if NeedFunctionPrototypes
    Widget		/* w */
#endif
);

extern void XawTextUnsetSelection(
#if NeedFunctionPrototypes
    Widget		/* w */
#endif
);

extern void XawTextSetSelection(
#if NeedFunctionPrototypes
    Widget		/* w */,
    XawTextPosition	/* left */,
    XawTextPosition	/* right */
#endif
);

extern void XawTextInvalidate(
#if NeedFunctionPrototypes
    Widget		/* w */,
    XawTextPosition	/* from */,
    XawTextPosition	/* to */
#endif
);

extern Widget XawTextGetSource(
#if NeedFunctionPrototypes
    Widget		/* w */
#endif
);

extern XawTextPosition XawTextSearch(
#if NeedFunctionPrototypes
    Widget			/* w */,
#if NeedWidePrototypes
    /* XawTextScanDirection */ int /* dir */,
#else
    XawTextScanDirection	/* dir */,
#endif
    XawTextBlock*		/* text */
#endif
);

extern void XawTextDisplayCaret(
#if NeedFunctionPrototypes
    Widget		/* w */,
#if NeedWidePrototypes
    /* Boolean */ int	/* visible */
#else
    Boolean		/* visible */
#endif
#endif
);

_XFUNCPROTOEND

/*
 * For R3 compatability only. 
 */

#include <X11/Xaw/AsciiSrc.h>
#include <X11/Xaw/AsciiSink.h>

#endif /* _XawText_h */
/* DON'T ADD STUFF AFTER THIS #endif */