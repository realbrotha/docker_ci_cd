/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* gos530 src/gos/2d/XTOP/include/fonts/fontstruct.h 1.2                  */
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
/* @(#)80	1.2  src/gos/2d/XTOP/include/fonts/fontstruct.h, xfont, gos530 6/21/96 13:54:52 */
/* $XConsortium: fontstruct.h,v 1.16 94/04/17 20:11:08 gildea Exp $ */
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

#ifndef FONTSTR_H
#define FONTSTR_H

#include <X11/Xproto.h>
#include "font.h"
#include <X11/Xfuncproto.h>

/*
 * This version of the server font data strucutre is only for describing
 * the in memory data structure. The file structure is not necessarily a
 * copy of this. That is up to the compiler and the OS layer font loading
 * machinery.
 */

#define GLYPHPADOPTIONS 4	/* 1, 2, 4, or 8 */

typedef struct _FontProp {
    long        name;
    long        value;		/* assumes ATOM is not larger than INT32 */
}           FontPropRec;

typedef struct _FontResolution {
    unsigned short x_resolution;
    unsigned short y_resolution;
    unsigned short point_size;
}           FontResolutionRec;

typedef struct _ExtentInfo {
    DrawDirection drawDirection;
    int         fontAscent;
    int         fontDescent;
    int         overallAscent;
    int         overallDescent;
    int         overallWidth;
    int         overallLeft;
    int         overallRight;
}           ExtentInfoRec;

typedef struct _CharInfo {
    xCharInfo   metrics;	/* info preformatted for Queries */
    char       *bits;		/* pointer to glyph image */
}           CharInfoRec;

/*
 * Font is created at font load time. It is specific to a single encoding.
 * e.g. not all of the glyphs in a font may be part of a single encoding.
 */

typedef struct _FontInfo {
    unsigned short firstCol;
    unsigned short lastCol;
    unsigned short firstRow;
    unsigned short lastRow;
    unsigned short defaultCh;
    unsigned int noOverlap:1;
    unsigned int terminalFont:1;
    unsigned int constantMetrics:1;
    unsigned int constantWidth:1;
    unsigned int inkInside:1;
    unsigned int inkMetrics:1;
    unsigned int allExist:1;
    unsigned int drawDirection:2;
    unsigned int cachable:1;
    unsigned int anamorphic:1;
    short       maxOverlap;
    short       pad;
    xCharInfo   maxbounds;
    xCharInfo   minbounds;
    xCharInfo   ink_maxbounds;
    xCharInfo   ink_minbounds;
    short       fontAscent;
    short       fontDescent;
    int         nprops;
    FontPropPtr props;
    char       *isStringProp;
}           FontInfoRec;

typedef struct _Font {
    int         refcnt;
    FontInfoRec info;
    char        bit;
    char        byte;
    char        glyph;
    char        scan;
    fsBitmapFormat format;
    int         (*get_glyphs) ( /* font, count, chars, encoding, count, glyphs */ );
    int         (*get_metrics) ( /* font, count, chars, encoding, count, glyphs */ );
    void        (*unload_font) ( /* font */ );
    void        (*unload_glyphs) ( /* font */ );
    FontPathElementPtr fpe;
    pointer     svrPrivate;
    pointer     fontPrivate;
    pointer     fpePrivate;
    int		maxPrivate;
    pointer	*devPrivates;
}           FontRec;

extern Bool	_FontSetNewPrivate (/* pFont, n, ptr */);
extern int	AllocateFontPrivateIndex ();

#define FontGetPrivate(pFont,n) ((n) > (pFont)->maxPrivate ? (pointer) 0 : \
			     (pFont)->devPrivates[n])

#define FontSetPrivate(pFont,n,ptr) ((n) > (pFont)->maxPrivate ? \
			_FontSetNewPrivate (pFont, n, ptr) : \
			((((pFont)->devPrivates[n] = (ptr)) != 0) || TRUE))

typedef struct _FontNames {
    int         nnames;
    int         size;
    int        *length;
    char      **names;
}           FontNamesRec;

/* External view of font paths */
typedef struct _FontPathElement {
    int         name_length;
    char       *name;
    int         type;
    int         refcount;
    pointer     private;
}           FontPathElementRec;

typedef struct _FPEFunctions {
    int         (*name_check) (
#if NeedFunctionPrototypes
			       char* /* name */
#endif
			       );
    int         (*init_fpe) (
#if NeedNestedPrototypes
			     FontPathElementPtr /* fpe */
#endif
			     );
    int         (*reset_fpe) (
#if NeedNestedPrototypes
			     FontPathElementPtr /* fpe */
#endif
			     );
    int         (*free_fpe) (
#if NeedNestedPrototypes
			     FontPathElementPtr /* fpe */
#endif
			     );
    int         (*open_font) (
#if NeedNestedPrototypes
			      pointer /* client */,
			      FontPathElementPtr /* fpe */,
			      int /* flags */,
			      char* /* name */,
			      int /* namelen */,
			      fsBitmapFormat /* format */,
			      fsBitmapFormatMask /* fmask */,
			      unsigned long /* id (type XID or FSID) */,
			      FontPtr* /* pFont */,
			      char** /* aliasName */,
			      FontPtr /* non_cachable_font */
#endif
			      );

    int         (*close_font) (
#if NeedNestedPrototypes
			       FontPathElementPtr /* fpe */,
			       FontPtr /* pFont */
#endif
			       );
    int         (*list_fonts) (
#if NeedNestedPrototypes
			       pointer /* client */,
			       FontPathElementPtr /* fpe */,
			       char* /* pat */,
			       int /* len */,
			       int /* max */,
			       FontNamesPtr /* names */
#endif
			       );
    int         (*start_list_fonts_and_aliases) (
#if NeedNestedPrototypes
						 pointer /* client */,
						 FontPathElementPtr /* fpe */,
						 char* /* pat */,
						 int /* len */,
						 int /* max */,
						 pointer* /* privatep */
#endif
						 );
    int         (*list_next_font_or_alias) (
#if NeedNestedPrototypes
					    pointer /* client */,
					    FontPathElementPtr /* fpe */,
					    char** /* namep */,
					    int* /* namelenp */,
					    char** /* resolvedp */,
					    int* /* resolvedlenp */,
					    pointer /* private */
#endif
					    );
    int         (*start_list_fonts_with_info) (
#if NeedNestedPrototypes
					       pointer /* client */,
					       FontPathElementPtr /* fpe */,
					       char* /* pat */,
					       int /* patlen */,
					       int /* maxnames */,
					       pointer* /* privatep */
#endif
					       );
    int         (*list_next_font_with_info) (	/* client, fpe, name, namelen,
					         info, num, data */
#if NeedNestedPrototypes
					     pointer /* client */,
					     FontPathElementPtr /* fpe */,
					     char** /* name */,
					     int* /* namelen */,
					     FontInfoPtr* /* info */,
					     int* /* numFonts */,
					     pointer /* private */
#endif
					     );
    int         (*wakeup_fpe) (
#if NeedNestedPrototypes
			       FontPathElementPtr /* fpe */,
			       unsigned long* /* LastSelectMask */
#endif
			       );
    int		(*client_died) (
#if NeedNestedPrototypes
				pointer /* client */,
				FontPathElementPtr /* fpe */
#endif
				);
		/* for load_glyphs, range_flag = 0 ->
			nchars = # of characters in data
			item_size = bytes/char
			data = list of characters
		   range_flag = 1 ->
			nchars = # of fsChar2b's in data
			item_size is ignored
			data = list of fsChar2b's */
    int		(*load_glyphs) (
#if NeedNestedPrototypes
				pointer /* client */,
				FontPtr /* pfont */,
				Bool /* range_flag */,
				unsigned int /* nchars */,
				int /* item_size */,
				unsigned char* /* data */
#endif
				);
    void	(*set_path_hook)(
#if NeedFunctionPrototypes
				 void
#endif
				 );
}           FPEFunctionsRec, FPEFunctions;

extern int  InitFPETypes();

/*
 * Various macros for computing values based on contents of
 * the above structures
 */

#define	GLYPHWIDTHPIXELS(pci) \
	((pci)->metrics.rightSideBearing - (pci)->metrics.leftSideBearing)

#define	GLYPHHEIGHTPIXELS(pci) \
 	((pci)->metrics.ascent + (pci)->metrics.descent)

#define	GLYPHWIDTHBYTES(pci)	(((GLYPHWIDTHPIXELS(pci))+7) >> 3)

#define GLYPHWIDTHPADDED(bc)	(((bc)+7) & ~0x7)

#define BYTES_PER_ROW(bits, nbytes) \
	((nbytes) == 1 ? (((bits)+7)>>3)	/* pad to 1 byte */ \
	:(nbytes) == 2 ? ((((bits)+15)>>3)&~1)	/* pad to 2 bytes */ \
	:(nbytes) == 4 ? ((((bits)+31)>>3)&~3)	/* pad to 4 bytes */ \
	:(nbytes) == 8 ? ((((bits)+63)>>3)&~7)	/* pad to 8 bytes */ \
	: 0)

#define BYTES_FOR_GLYPH(ci,pad)	(GLYPHHEIGHTPIXELS(ci) * \
				 BYTES_PER_ROW(GLYPHWIDTHPIXELS(ci),pad))
/*
 * Macros for computing different bounding boxes for fonts; from
 * the font protocol
 */

#define FONT_MAX_ASCENT(pi)	((pi)->fontAscent > (pi)->ink_maxbounds.ascent ? \
			    (pi)->fontAscent : (pi)->ink_maxbounds.ascent)
#define FONT_MAX_DESCENT(pi)	((pi)->fontDescent > (pi)->ink_maxbounds.descent ? \
			    (pi)->fontDescent : (pi)->ink_maxbounds.descent)
#define FONT_MAX_HEIGHT(pi)	(FONT_MAX_ASCENT(pi) + FONT_MAX_DESCENT(pi))
#define FONT_MIN_LEFT(pi)	((pi)->ink_minbounds.leftSideBearing < 0 ? \
			    (pi)->ink_minbounds.leftSideBearing : 0)
#define FONT_MAX_RIGHT(pi)	((pi)->ink_maxbounds.rightSideBearing > \
				(pi)->ink_maxbounds.characterWidth ? \
			    (pi)->ink_maxbounds.rightSideBearing : \
				(pi)->ink_maxbounds.characterWidth)
#define FONT_MAX_WIDTH(pi)	(FONT_MAX_RIGHT(pi) - FONT_MIN_LEFT(pi))

#endif				/* FONTSTR_H */
