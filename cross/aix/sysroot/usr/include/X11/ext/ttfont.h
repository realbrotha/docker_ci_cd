/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* gos530 src/gos/2d/XTOP/lib/font/TrueType/ttfont.h 1.1                  */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1997               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/*   @(#)96       1.1  src/jkit/ttxfs/lib/font/TrueType/ttfont.h, JK_ttxfs, jkit110, GOLD 8/26/96 18:26:47
 *
 *   COMPONENT_NAME: ttxfs
 *
 *   FUNCTIONS: None
 *
 *   ORIGINS: 27
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1996
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_TTFONT
#define _H_TTFONT

/*
 * TrueType 
 */
#define TTFHandle	char *

typedef struct _TTFFormat {
	short		ttf_no;		/* TTF number */
	short		cmap_no;	/* CMAP number */
	char		bit;		/* for bitmap alignment */
	char		byte;		/* for bitmap alignment */
	char		glyph;		/* for bitmap alignment */
	char		scan;		/* for bitmap alignment */
} TTFFormat;

typedef struct _TTFScale {
	int	point;			/* point size */
	int	x_resolution;		/* x resolution */
	int	y_resolution;		/* y resolution */
	double	point_matrix[4];	/* matrix for rotation */
} TTFScale;

typedef struct _TTFFontInfo {
	int	direction;		/* font direction */
	int	ascent;			/* ascent */
	int	descent;		/* descent */
	int	width;			/* max width */
	int	line_gap;		/* line gap */
} TTFFontInfo;

/* platform id */
#define TTF_APPLE_UNICODE	0	/* unicode: no specific encoding */
#define TTF_MACINTOSH		1	/* Script manager code */
#define TTF_ISO			2	/* ISO encoding */
#define TTF_MICROSOFT		3	/* Microsoft encoding */
/* Macintosh platform-specific encoding id */
#define TTF_MAC_ROMAN		0
#define TTF_MAC_JAPANESE	1
#define TTF_MAC_CHINESE		2
#define TTF_MAC_KOREAN		3
#define TTF_MAC_ARABIC		4
#define TTF_MAC_HEBREW		5
#define TTF_MAC_GREEK		6
#define TTF_MAC_RUSSIAN		7
#define TTF_MAC_RSYMBOL		8
#define TTF_MAC_DEVANAGARI	9
#define TTF_MAC_GURMUKHI	10
#define TTF_MAC_GUJARATI	11
#define TTF_MAC_ORIYA		12
#define TTF_MAC_BENGALI		13
#define TTF_MAC_TAMIL		14
#define TTF_MAC_TELUGU		15
#define TTF_MAC_KANNADA		16
#define TTF_MAC_MALAYALAM	17
#define TTF_MAC_SINHALESE	18
#define TTF_MAC_BURMESE		19
#define TTF_MAC_KHMER		20
#define TTF_MAC_THAI		21
#define TTF_MAC_LAOTIAN		22
#define TTF_MAC_GEORGIAN	23
#define TTF_MAC_ARMENIAN	24
#define TTF_MAC_MALDIVIAN	25
#define TTF_MAC_TIBETAN		26
#define TTF_MAC_MONGOLIAN	27
#define TTF_MAC_GEEZ		28
#define TTF_MAC_SLAVIC		29
#define TTF_MAC_VIETNAMESE	30
#define TTF_MAC_SINDHI		31
#define TTF_MAC_UNINTERP	32
/* ISO specific encoding id */
#define TTF_ISO_ASCII		0	/* 7 bit ASCII */
#define TTF_ISO_10646		1	/* ISO 10646 */
#define TTF_ISO_8859_1		2	/* ISO 8859-1 */
/* Microsoft platform-specific encoding id */
#define TTF_MS_SYMBOL		0	/* Symbol */
#define TTF_MS_UNICODE		1	/* Unicode */
#define TTF_MS_SJIS		2	/* Shift JIS */
#define TTF_MS_BIG5		3	/* Big 5 */
#define TTF_MS_RPC		4	/* RPC */
#define TTF_MS_WANSUNG		5	/* Wansung */
#define TTF_MS_JOHAB		6	/* Johab */

typedef struct _TTFString {
	char	*str;			/* string (NOT terminated with null) */
	int	len;			/* string length in bytes */
} TTFString;

typedef struct _TTFCmap {
	int		first;		/* first character code in the cmap */
	int		last;		/* last character code in the cmap */
	unsigned short	format;		/* format: 0, 2, 4, or 6 */
	unsigned short	platform;	/* platform id */
	unsigned short	encoding;	/* platform specific encoding id */
	unsigned short	active;		/* 1: in use now. 0: not in use. */
} TTFCmap;

typedef struct _TTFName {
	TTFString	Copyright;	/* copyright string */
	TTFString	FamilyName;	/* font family name string */
	TTFString	SubfamilyName;	/* font subfamily name string */
	TTFString	FontIdentifier;	/* font unique identifier string */
	TTFString	FontName;	/* full font name string */ 
	TTFString	Version;	/* version string */
	TTFString	PSName;		/* PostScript name of the font */
	TTFString	Trademark;	/* trademark string */
} TTFName;

typedef struct _TTFInfo {
	int		lowestRecPPEM;	/* smallest readable size in pixels */
	int		num_of_cmaps;	/* the number of cmaps */
	TTFCmap		*cmaps;
	TTFName		name;
} TTFInfo;

typedef struct _TTCInfo {
	int		num_of_ttfs;	/* the number of TTFs in the TTC file */
	TTFInfo		*ttfi;		/* information of each TTF */
} TTCInfo;

/* TTF rasterizer error code */
#define TTF_SUCCESS			0
#define TTF_MALLOC_ERROR		-1
#define TTF_FILL_ERROR			-2
#define TTF_FILL_CONFUSION		-3
#define TTF_INVALID_INSTRUCTION		-4
#define TTF_INVALID_DATA		-5
#define TTF_TOO_SMALL_POINTS		-6
#define TTF_INVALID_CODE		-7
#define TTF_BAD_FILE			-8
#define TTF_NO_GLYPH			-9

/* TTF function prototype */
#ifdef _NO_PROTO

extern TTFHandle 	TTFOpen();
extern TTCInfo	*	TTFGetInfo();
extern void		TTFFreeTTCInfo();
extern int		TTFSetFormat();
extern int		TTFSetScale();
extern int		TTFRasterize();
extern void		TTFClose();

#else /* _NO_PROTO */

extern TTFHandle 	TTFOpen(char *, int);
extern TTCInfo	*	TTFGetInfo(TTFHandle);
extern void		TTFFreeTTCInfo(TTCInfo *ttci);
extern int		TTFSetFormat(TTFHandle, TTFFormat *);
extern int		TTFSetScale(TTFHandle, TTFScale *,
					CharInfoRec *, TTFFontInfo *);
extern int		TTFRasterize(TTFHandle, int, CharInfoRec *);
extern void		TTFClose(TTFHandle);

#endif /* _NO_PROTO */

#endif /* _H_TTFONT */
