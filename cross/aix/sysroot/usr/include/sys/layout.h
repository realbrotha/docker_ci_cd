/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/sys/layout.h 1.1                            */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* OBJECT CODE ONLY SOURCE MATERIALS                                      */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1995,1997          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* The source code for this program is not published or otherwise         */
/* divested of its trade secrets, irrespective of what has been           */
/* deposited with the U.S. Copyright Office.                              */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)38	1.1  src/bos/usr/include/sys/layout.h, libi18n, bos530 8/6/97 21:00:47 */
/*
 *      (c) Copyright 1995 Sun Microsystems, Inc. 
 *	All rights reserved. 
 *	See LEGAL NOTICE file for terms of the license.
 */
 
/*
 *  This is the public header file for layout services.
 */
 
#ifndef _LAYOUT_H_
#define _LAYOUT_H_


/* <sys/layout.h> */

/* ----------------------- Public declaration --------------------------- */


#define AllTextDescriptors      0x0000007f

#define Orientation		1L
#define Context			(1L<<1)
#define TypeOfText		(1L<<2)
#define ImplicitAlg		(1L<<3)
#define Swapping		(1L<<4)
#define Numerals		(1L<<5)
#define TextShaping		(1L<<6)

#define ActiveDirectional	(1L<<16)
#define ActiveShapeEditing	(1L<<17)
#define ShapeCharset		(1L<<18)
#define ShapeCharsetSize	(1L<<19)
#define ShapeContextSize	(1L<<20)
#define InOutTextDescrMask	(1L<<21)
#define InOnlyTextDescr		(1L<<22)
#define OutOnlyTextDescr	(1L<<23)
#define CheckMode		(1L<<24)
#define QueryValueSize		(1L<<25)

/* Possible values for Orientation */
#define ORIENTATION_LTR         0x00000001
#define ORIENTATION_RTL         0x00000002
#define ORIENTATION_TTBRL	0x00000003
#define ORIENTATION_TTBLR	0x00000004
#define ORIENTATION_CONTEXTUAL	0x00000005

/* Possible values for Context */
#define CONTEXT_LTR	        0x00000010
#define CONTEXT_RTL         	0x00000020

/* Possible values for TypeOfText */
#define TEXT_IMPLICIT		0x00000100
#define TEXT_EXPLICIT		0x00000200
#define TEXT_VISUAL         	0x00000300

/* Possible values for ImplicitAlg */
#define ALGOR_BASIC	        0x00001000
#define ALGOR_IMPLICIT         	0x00002000

/* Possible values for Swapping */
#define SWAPPING_NO         	0x00010000
#define SWAPPING_YES	        0x00020000

/* Possible values for Numerals */
#define NUMERALS_NOMINAL        0x00100000
#define NUMERALS_NATIONAL	0x00200000
#define NUMERALS_CONTEXTUAL	0x00300000

/* Possible values for TextShaping */
#define TEXT_SHAPED		0x01000000
#define TEXT_NOMINAL		0x02000000
#define TEXT_SHFORM1		0x03000000
#define TEXT_SHFORM2		0x04000000
#define TEXT_SHFORM3		0x05000000
#define TEXT_SHFORM4		0x06000000

/* Possible values for CheckMode */
#define MODE_STREAM		0x00000001
#define MODE_EDIT		0x00000002


#define MaskAllTextDescriptors	0x0fffffff
#define MaskOrientation		0x0000000f
#define MaskContext		0x000000f0
#define MaskTypeOfText		0x00000f00
#define MaskImplicitAlg		0x0000f000
#define MaskSwapping		0x000f0000
#define MaskNumerals		0x00f00000
#define MaskTextShaping		0x0f000000

/* Mask for the Property parament of m_*transform() */
#define NESTLEVEL_MASK		0x0f
#define DISPLAYCELL_MASK	0x10
	


typedef int	LayoutId;
typedef int	BooleanValue;
typedef void	*LayoutValue;

typedef struct {
    LayoutId		name;
    LayoutValue		value;
} LayoutValueRec, *LayoutValues;

typedef int	LayoutDesc;
typedef struct {
    LayoutDesc		inp;
    LayoutDesc		out;
} LayoutTextDescriptorRec, *LayoutTextDescriptor;


typedef struct {
    int		front;
    int		back;
} LayoutEditSizeRec, *LayoutEditSize;

typedef struct _LayoutObject *LayoutObject;	/* Public name */

extern LayoutObject m_create_layout(
#if NeedFunctionPrototypes
    const void*			/* attrobj */,
    const char*			/* modifier */
#endif
);

extern int m_destroy_layout(
#if NeedFunctionPrototypes
    const LayoutObject		/* layoutobject */
#endif
);

extern int m_getvalues_layout(
#if NeedFunctionPrototypes
    const LayoutObject		/* layoutobject */,
    LayoutValues		/* values */,
    int*			/* index_returned */
#endif
);

extern int m_setvalues_layout(
#if NeedFunctionPrototypes
    const LayoutObject		/* layoutobject */,
    LayoutValues		/* values */,
    int*			/* index_returned */
#endif
);

extern int m_transform_layout(
#if NeedFunctionPrototypes
    LayoutObject		/* layoutobject */,
    const char*			/* InpBuf */,
    const size_t		/* InpSize */,
    void*			/* OutBuf */,
    size_t*			/* OutSize */,
    size_t*			/* InpToOut */,
    size_t*			/* OutToInp */,	
    unsigned char *		/* Property */,
    size_t*			/* InpBufIndex */		
#endif
);

extern int m_wtransform_layout(
#if NeedFunctionPrototypes
    LayoutObject		/* layoutobject */,
    const wchar_t*		/* InpBuf */,
    const size_t		/* InpSize */,
    void*			/* OutBuf */,
    size_t*			/* OutSize */,
    size_t*			/* InpToOut */,
    size_t*			/* OutToInp */,	
    unsigned char *		/* Property */,
    size_t*			/* InpBufIndex */		
#endif
);









/* ----------------------- Private declaration --------------------------- */


#endif /* _LAYOUT_H_ */
