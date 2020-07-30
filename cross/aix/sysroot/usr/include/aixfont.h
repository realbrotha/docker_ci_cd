/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* gos530 src/gos/include/aixfont.h 1.5                                   */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,1997          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)92	1.5  src/gos/include/aixfont.h, resmgr, gos530 6/9/97 15:48:09 */

#ifndef __aixFONT__
#define __aixFONT__

/*
 * This file describes the AIX Font format for X11R6
 *
 * Each font file contains the following data structures.  There is no
 * padding between these data structures.
 *
 *      1)  The FontInfo structure
 *              maxbounds.byteoffset is the total number of bytes in the
 *                      glpyh array
 *
 *      2)  The CharInfo array
 *              character bounds (metrics)
 *              offsets to glyphs
 *              indexed directly with character codes
 *
 *      3)  Character glyphs
 *              most significant bit/byte first
 *              end of glyphs padded to 32-bit boundary.
 *              raster format:
 *                  each scanline padded to a byte boundary
 *              stroke format:
 *                  2 byte number of x,y coordinates
 *                  2 byte pairs of x,y coordinates
 *                      sxxxxxx1syyyyyyf
 *                  where
 *                      s - sign bit
 *                      x - relative x coordinate
 *                      y - relative y coordinate
 *                      f - flag: 0 = draw, 1 = move
 *
 *      4)  Properties (optional)
 *              named properties
 *              property is a value or null-terminated strings
 *              character encodings are stored as properties
 *
 *      5)  Ink metrics (optional)
 *              character "ink" metrics
 *                  minimum bounds followed by
 *                  maximum bounds followed by
 *                  per character bounds
 *              indexed directly with character codes
 *
 *
 * Note:  An X11 Release 6 FontInfo structure from fontstruct.h
 *        will map exactly onto an aixFontInfo structure, except
 *	  for the font properties at the end.
 *
 *        An X11 Release 6 CharInfo structure from fontstruct.h
 *        will map exactly onto an aixCharInfo structure, except
 *	  that CharInfo has pointers to glyphs while aixCharInfo
 *        contains glyph offsets from the glyph base.
 *
 */

#define FONT_FILE_VERSION       6

typedef struct _aixFontProp {
    unsigned int  name;              /* offset of string                      */
    int        value;             /* a number or a string offset           */
    char       *isStringProp;     /*                                      */
} aixFontProp, *aixFontPropPtr;

/*
    Must match xCharInfo from X11/Xproto.h
*/
typedef struct {
    short leftSideBearing,
          rightSideBearing,
          characterWidth,
          ascent,
          descent;
    unsigned short attributes;
} xxCharInfo;

/*
    First part must match xCharInfo from X11/Xproto.h
*/
typedef struct _aixCharInfo {
    short leftSideBearing,
          rightSideBearing,
          characterWidth,
          ascent,
          descent;
    unsigned short attributes;     /* must be zero                         */
    unsigned int byteOffset:24;	   /* byte offset of raster from pGlyphs   */
    unsigned int exists:1;         /* true iff glyph exists for this char  */
    unsigned int pad:7;            /* reserved - must be zero              */
} aixCharInfo, *aixCharInfoPtr;

typedef struct _aixFontInfo {
    unsigned short firstCol;       /*                                      */
    unsigned short lastCol;        /*                                      */
    unsigned short firstRow;       /*                                      */
    unsigned short lastRow;        /*                                      */
    unsigned short defaultCh;      /* default character                    */
    unsigned int noOverlap:1;      /* see note (1)                         */
    unsigned int terminalFont:1;   /* see note (2)                         */
    unsigned int constantMetrics:1;/*                                      */
    unsigned int constantWidth:1;  /* see note (3)                         */
    unsigned int inkInside:1;      /* see note (4)                         */
    unsigned int inkMetrics:1;     /* see note (5)                         */
    unsigned int allExist:1;       /*                                      */
    unsigned int drawDirection:2;  /*                                      */
    unsigned int cachable:1;       /*                                      */
    unsigned int anamorphic:1;     /*                                      */
    short        maxOverlap;       /*                                      */
    short        pad;       	   /*                                      */
    xxCharInfo	 maxbounds;        /* MAX of glyph metrics over all chars  */
    xxCharInfo	 minbounds;        /* MIN of glyph metrics over all chars  */
    xxCharInfo	 ink_maxbounds;    /* MAX of ink metrics over all chars    */
    xxCharInfo	 ink_minbounds;    /* MIN of ink metrics over all chars    */
    short        fontAscent;       /* minimum for quality typography       */
    short        fontDescent;      /* minimum for quality typography       */
    int          nprops;           /*                                      */
    int          props;            /* really FontPropPtr                   */
    int          isStringProp;     /* really char *                        */
} aixFontInfo, *aixFontInfoPtr;

/********************
* for compatibility 
********************/
#define chDefault defaultCh
#define nProps nprops

/*
 *  note (1)   noOverlap      true if max(rightSideBearing-characterWidth)
 *                               <= minbounds->metrics.leftSideBearing
 *
 *  note (2)   terminalFont   Should be deprecated!  true if:
 *                            constant metrics && leftSideBearing == 0 &&
 *                            rightSideBearing == characterWidth &&
 *                            ascent == fontAscent && descent == fontDescent
 *
 *  note (3)   constantWidth  true if minbounds->metrics.characterWidth
 *                                 == maxbounds->metrics.characterWidth
 *
 *  note (4)   inkInside      true if for all defined glyphs:
 *                            leftSideBearing >= 0 &&
 *                            rightSideBearing <= characterWidth &&
 *                            -fontDescent <= ascent <= fontAscent &&
 *                            -fontAscent <= descent <= fontDescent
 *
 *  note (5)   inkMetrics     ink metrics != bitmap metrics used with
 *                            terminalFont.  See font's pInk{CI,Min,Max}
 *
 *  note (6)   glyphSets      used for sub-pixel positioning
 */

typedef unsigned char          *aixGlyphPtr;

#define NUMCHARS(pfi)          (((pfi)->lastCol - (pfi)->firstCol + 1) * \
                                ((pfi)->lastRow - (pfi)->firstRow + 1))
#define BYTESOFFONTINFO(pfi)   (sizeof(aixFontInfo))
#define BYTESOFCHARINFO(pfi)   (sizeof(aixCharInfo) * NUMCHARS(pfi))
#define BYTESOFPROPINFO(pfi)   (sizeof(aixFontProp) * (pfi)->nProps)
#define BYTESOFSTRINGINFO(pfi) ((pfi)->lenStrings)
#define BYTESOFGLYPHINFO(pfi)  (((pfi)->maxbounds.byteOffset+3) & ~0x3)
#define BYTESOFINKINFO(pfi)    (sizeof(aixCharInfo) * (2 + NUMCHARS(pfi)))

#endif /* __aixFONT__ */
