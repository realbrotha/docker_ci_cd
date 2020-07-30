/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* gos530 src/gos/2d/XTOP/lib/Xaw/Repeater.h 1.1                          */
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
/* @(#)71  1.1  src/gos/2d/XTOP/lib/Xaw/Repeater.h, xsample, gos530 7/12/96 13:07:25 */
/* SCCSID_END_TAG                                                      */
/*
 * $XConsortium: Repeater.h,v 1.4 94/04/17 20:12:38 jim Exp $
 *
Copyright (c) 1989  X Consortium

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
 *
 * Author:  Jim Fulton, MIT X Consortium
 */

#ifndef _XawRepeater_h
#define _XawRepeater_h

#include <X11/Xaw/Command.h>

/*****************************************************************************
 * 
 * Repeater Widget (subclass of Command)
 * 
 * This widget is a push button that repeatedly fires when held down.
 * 
 * Parameters:
 * 
 *  Name		Class		Type		Default
 *  ----		-----		----		-------
 * 
 *  decay		Decay		int		5 milliseconds
 *  flash		Boolean		Boolean		FALSE
 *  initialDelay	Delay		int		200 milliseconds
 *  minimumDelay	MinimumDelay	int		10 milliseconds
 *  repeatDelay		Delay		int		50 milliseconds
 *  startCallback	StartCallback	XtCallbackList	NULL
 *  stopCallback	StopCallback	XtCallbackList	NULL
 * 
 *****************************************************************************/

					/* new instance and class names */
#define XtNdecay "decay"
#define XtCDecay "Decay"
#define XtNinitialDelay "initialDelay"
#define XtCDelay "Delay"
#define XtNminimumDelay "minimumDelay"
#define XtCMinimumDelay "MinimumDelay"
#define XtNrepeatDelay "repeatDelay"
#define XtNflash "flash"
#define XtNstartCallback "startCallback"
#define XtCStartCallback "StartCallback"
#define XtNstopCallback "stopCallback"
#define XtCStopCallback "StopCallback"


					/* external declarations */
extern WidgetClass repeaterWidgetClass;

typedef struct _RepeaterClassRec *RepeaterWidgetClass;
typedef struct _RepeaterRec      *RepeaterWidget;

#endif /* _XawRepeater_h */
