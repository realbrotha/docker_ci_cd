/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* gos530 src/gos/2d/XTOP/include/fonts/font.h 1.2                        */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1997,1996          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)79	1.2  src/gos/2d/XTOP/include/fonts/font.h, xfont, gos530 6/21/96 13:54:40 */
/* $XConsortium: font.h,v 1.13 94/04/17 20:11:07 gildea Exp $ */
/***********************************************************
Copyright 1987 by Digital Equipment Corporation, Maynard, Massachusetts.

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
/* $NCDId: @(#)font.h,v 1.7 1991/06/24 17:00:23 lemke Exp $ */

#ifndef FONT_H
#define FONT_H

#ifndef BitmapFormatByteOrderMask
#include	"fsmasks.h"
#endif

/* data structures */
#ifndef _XTYPEDEF_FONTPTR
typedef struct _Font *FontPtr;
#define _XTYPEDEF_FONTPTR
#endif

typedef struct _FontInfo *FontInfoPtr;
typedef struct _FontProp *FontPropPtr;
typedef struct _ExtentInfo *ExtentInfoPtr;
typedef struct _FontPathElement *FontPathElementPtr;

#ifndef _XTYPEDEF_CHARINFOPTR
typedef struct _CharInfo *CharInfoPtr;
#define _XTYPEDEF_CHARINFOPTR
#endif

typedef struct _FontNames *FontNamesPtr;
typedef struct _FontResolution *FontResolutionPtr;

#define NullCharInfo	((CharInfoPtr) 0)
#define NullFont	((FontPtr) 0)
#define NullFontInfo	((FontInfoPtr) 0)

 /* draw direction */
#define LeftToRight 0
#define RightToLeft 1
#define BottomToTop 2
#define TopToBottom 3
typedef int DrawDirection;

#define NO_SUCH_CHAR	-1


#define	FontAliasType	0x1000

#define	AllocError	80
#define	StillWorking	81
#define	FontNameAlias	82
#define	BadFontName	83
#define	Suspended	84
#define	Successful	85
#define	BadFontPath	86
#define	BadCharRange	87
#define	BadFontFormat	88
#define	FPEResetFailed	89	/* for when an FPE reset won't work */

/* OpenFont flags */
#define FontLoadInfo	0x0001
#define FontLoadProps	0x0002
#define FontLoadMetrics	0x0004
#define FontLoadBitmaps	0x0008
#define FontLoadAll	0x000f
#define	FontOpenSync	0x0010
#define FontReopen	0x0020

/* Query flags */
#define	LoadAll		0x1
#define	FinishRamge	0x2
#define       EightBitFont    0x4
#define       SixteenBitFont  0x8

/* Glyph Caching Modes */
#define CACHING_OFF 0
#define CACHE_16_BIT_GLYPHS 1
#define CACHE_ALL_GLYPHS 2
#define DEFAULT_GLYPH_CACHING_MODE CACHING_OFF
extern int glyphCachingMode;

extern int StartListFontsWithInfo(
#if NeedFunctionPrototypes
    ClientPtr /*client*/,
    int /*length*/,
    unsigned char */*pattern*/,
    int /*max_names*/
#endif
);

extern FontNamesPtr MakeFontNamesRecord( /* size */ );
extern void FreeFontNames();
extern int  AddFontNamesName();

extern int  FontToFSError();

extern FontResolutionPtr GetClientResolution();

typedef struct _FontPatternCache    *FontPatternCachePtr;

extern FontPatternCachePtr  MakeFontPatternCache ();
extern void		    FreeFontPatternCache ();
extern void		    EmtpyFontPatternCache ();
extern void		    CacheFontPattern ();
extern FontPtr		    FindCachedFontPattern ();
extern void		    RemoveCachedFontPattern ();

typedef enum {
    Linear8Bit, TwoD8Bit, Linear16Bit, TwoD16Bit
}           FontEncoding;

#endif				/* FONT_H */