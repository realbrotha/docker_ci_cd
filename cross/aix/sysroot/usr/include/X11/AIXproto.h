/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* gos530 src/gos/2d/XTOP/include/extensions/AIXproto.h 1.10.1.5          */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1987,2000          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)18	1.10.1.5  src/gos/2d/XTOP/include/extensions/AIXproto.h, xext, gos530 7/7/00 14:20:03 */
/*
 * COMPONENT_NAME: X11
 *
 * FUNCTIONS: none
 *
 * ORIGINS: 27 
 *
 * (C) COPYRIGHT International Business Machines Corp. 1987,1995
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 */

#ifndef _AIXPROTO_H
#define _AIXPROTO_H

#include "Xmd.h"

/* aixCursorExtension protocol request and reply size */
#define sz_xQueryCrossHairReq           4    
#define sz_xQueryCrossHairReply         32  
#define sz_xCreateCrossHairReq		24
#define sz_xCreateMultiColorCurReq	20
#define sz_xRecolorMultiColorCurReq	8
#define sz_xCursorQueryVersionReq        8       
#define sz_xCursorQueryVersionReply      32   
#define sz_xGetCrossHairCursorInfoReq    8    
#define sz_xGetCrossHairCursorInfoReply  32  
#define sz_xRecolorCrossHairCursorReq    20   
#define sz_xGetMultiColorCursorInfoReq   8   
#define sz_xGetMultiColorCursorInfoReply 32   

#define sz_xExtBlinkReq			24

#define sz_xGenExtReq			4
#define sz_xGetDPYInfoReq		sz_xGenExtReq
#define sz_xExtChangeModeReq		8
#define sz_xExtQueryModeReq		8
#define sz_xManageOverlayReq            12
#define sz_xQueryMemoryUsageReq		8


#define sz_xDirectAdapterAccessReq	16
#define sz_xDirectWindowAccessReq	12
#define sz_xDirectFontAccessReq		12
#ifdef GL_X_PERF
#define sz_xDirectInputAccessReq        8
#endif
#define sz_xFastResUpdateReq                   12
#define sz_xFastResUpdateReply                 32
#define sz_xHardwareSyncReq                    16
#define sz_xDirectAccessQueryVersionReq        8
#define sz_xDirectAccessQueryVersionReply      32

/*  WRITE TO BOTH BUFFERS DEFINES             */
#define sz_xDAEQueryCapabilitiesReq           8      
#define sz_xDAEQueryCapabilitiesRep          32      
#define sz_xDAEWriteToBothBuffersReq         12 
#define sz_xDrawPolyMarkerReq           16
#define sz_xSetPolyMarkerReq            16
#define sz_xDrawPolyMarkersReq          16

#define sz_xFullScreenReq               12
#define sz_xNewXFontReq			20



/* For the purpose of the structure definitions in this file,
we must redefine the following types in terms of Xmd.h's types, which may
include bit fields.  All of these are #undef'd at the end of this file,
restoring the definitions in X.h.  */

#define Window CARD32
#define Drawable CARD32
#define Font CARD32
#define Pixmap CARD32
#define Cursor CARD32
#define Colormap CARD32
#define GContext CARD32

typedef struct {
    CARD8 reqType;
    BYTE mcode;
    CARD16 length B16;
    Colormap cmap B32;
    CARD8 pixel;
    BYTE pad;
    CARD16 colorlength B16;
} xChangeColorsReq;    


typedef struct {
    CARD8 reqType;
    BYTE mcode ;
    CARD16 length B16;
} xGenExtReq ;


typedef struct {
    BYTE type; 
    BYTE pad1;
    CARD16 sequenceNumber B16;
    CARD32 length B32;  /* 0 */
    CARD32 kbdid B32;
    CARD32 dpsid B32;
    CARD32 displayid B32;
    CARD32 pad2 B32;
    CARD32 pad3 B32;
    CARD32 pad4 B32;
    } xGetDPYInfoReply;

/** 
*** aixDirectAccessExtension PROTOCOL STRUCTURE Definition
**/
typedef struct {
    CARD8  reqType;             /* always DirectAccessReqCode        */
    CARD8  directaccessReqType; /* always X_DirectAccessQueryVersion */
    CARD16 length;           /* sz_xDirectAccessQueryVersionReq/4=2  */
    CARD16 majorVersion  B16;
    CARD16 minorVersion  B16;
} xDirectAccessQueryVersionReq;

typedef struct {
    BYTE   type;               /* always X_Reply = 1       */
    CARD8  pad1;
    CARD16 sequenceNumber B16;
    CARD32 length         B32; /* =(sz_xDirectAccessQueryVersionReply-32)/4=0 */
    CARD16 majorVersion   B16; /* =aixDIRECTACCESS_MAJOR_VERSION              */
    CARD16 minorVersion   B16; /* =aixDIRECTACCESS_MINOR_VERSION              */
    CARD32 pad2           B32;
    CARD32 pad3           B32;
    CARD32 pad4           B32;
    CARD32 pad5           B32;
    CARD32 pad6           B32;
} xDirectAccessQueryVersionReply;

/* define FastResUpdate protocol request/reply structure */
typedef struct
{
    CARD8   reqType;              /* always DirectAccessReqCode */
    CARD8   directaccessReqType;  /* always X_FastResUpdate     */
    CARD16  length;               /* sz_xFastResUpdateReq/4=3   */
    Window  wid   B32;            /*                            */
    INT32   nid   B32;            /* machine/cpu id             */
} xFastResUpdateReq;

typedef struct
{
    BYTE    type;                 /* always X_Reply = 1         */
    BYTE    access;               /* direct access - local machine? */
    CARD16  sequenceNumber B16;
    CARD32  length B32;           /* (sz_xFastResUpdateReply-32)/4=0      */
    CARD32  shmID;                /* key of shared memory segment         */
    CARD32  shm_offset;           /* offset to shmFastResUpdateRec Entry  */
    CARD32  pad1;                                                        
    CARD32  pad2;
    CARD32  pad3;
    CARD32  pad4;
} xFastResUpdateReply;

/* define HardwareSync protocol request structure */
typedef struct
{
    CARD8   reqType;              /* always DirectAccessReqCode */
    CARD8   directaccessReqType;  /* always X_HardwareSync      */
    CARD16  length;               /* sz_xHardwareSyncReq/4=4    */
    CARD32  level B32;            /* synchronization level      */
    INT32   nid   B32;            /* machine/cpu id             */
    Drawable  drawable;           /* drawable for the screen    */
} xHardwareSyncReq;

typedef struct {
	CARD8	reqType ; 	/* DirectAccessReqCode */
	BYTE	mcode   ; 	/* X_DirectFontAccess  */
	CARD16	length B16 ;
	INT32	nid B32 ;	/* cpu id  */
	Window	fid B32 ;	/* font id */
} xDirectFontAccessReq ;

typedef struct {
    BYTE type; 
    BYTE access;
    CARD16 sequenceNumber B16;
    CARD32 length B32;
     CARD32 shmID B32;		/* if 0 then no shm offsets sent */
    CARD32 pad3 B32;
    CARD32 pad4 B32;
    CARD32 pad5 B32;
    CARD32 pad6 B32;
    CARD32 pad7 B32;
    } xDirectFontAccessReply;

#ifdef GL_X_PERF
typedef struct {
    CARD8 reqType;              /* DirectAccessReq Code */
    BYTE mcode;                 /* X_DirectInputAccess */
    CARD16 length B16;
    INT32 nid B32;               /* CPU id */
} xDirectInputAccessReq;

typedef struct {
    BYTE type;
    BYTE access;
    CARD16 sequenceNumber B16;
    CARD32 length;
    CARD32 shmID;
    CARD32 offset;
    CARD32 pad4 B32;
    CARD32 pad5 B32;
    CARD32 pad6 B32;
    CARD32 pad7 B32;
} xDirectInputAccessReply;
#endif

typedef struct {
    CARD8     reqType;           /* DirectAccessReq Code */
    CARD8     mcode;             /* X_DirectBufferAccess */
    CARD16    length B16;        /* length of the request */
    INT32     nid B32;           /* cpu id  */
    CARD32    num B32;           /* number of CARD32s */
} xDirectBufferAccessReq;        /* Followed by a list of CARD32 */
#define sz_xDirectBufferAccessReq    12

typedef struct {
    CARD32    mask B32;
} xDirectAlphaBufferInfo;

typedef struct {
    CARD32    mask B32;
} xDirectStencilBufferInfo;

typedef struct {
    CARD64    redMask;
    CARD64    greenMask;
    CARD64    blueMask;
    CARD64    alphaMask;
    CARD8     redSize;
    CARD8     greenSize;
    CARD8     blueSize;
    CARD8     alphaSize;
} xDirectAccumBufferInfo;

typedef struct {
    CARD32    mask B32;
    INT32     minValue B32;
    INT32     maxValue B32;
} xDirectDepthBufferInfo;

typedef struct {
    CARD32    mask B32;
} xDirectMaskBufferInfo;

typedef struct {
    CARD8     redSize;
    CARD8     greenSize;
    CARD8     blueSize;
    CARD8     alphaSize;
    CARD32    redMask B32;
    CARD32    greenMask B32;
    CARD32    blueMask B32;
    CARD32    alphaMask B32;
} xDirectAuxilBufferInfo;

typedef struct {
    CARD32    mask B32;
} xDirectFrameBufferInfo;

typedef struct {
    CARD32    mask B32;
} xDirectMultiBufferInfo;

typedef struct {
    CARD32    mask B32;
} xDirectStereoBufferInfo;

typedef struct {
    CARD32    mask B32;
} xDirectMultisampleBufferInfo;

typedef struct {
    CARD32    mask B32;
    CARD8     redSize;
    CARD8     greenSize;
    CARD8     blueSize;
    CARD8     pad;
} xDirectExtendedcolorBufferInfo;


typedef struct {
    BYTE      type;               /* X_Reply */
    CARD8     access;
    CARD16    sequenceNumber B16;
    CARD32    length B32;
    CARD32    more B32;           /* True/False */
    CARD32    buf_id B32;         /* buffer resource id */
    CARD32    buf_type B32;       /* buffer type */
    CARD8     depth;              /* plane depth */
    CARD8     bits_per_pixel;     /* number of bits until next scan line */
    BOOL      isHardware;         /* Is this a hareware buffer? */
    CARD8     instance;
    union {
	struct {
    CARD32    key B32;            /* Key and offset are used by shared memory */
    CARD32    offset B32;
	      } bufAccSharedMem;
    CARD32    baseAddr B32;
	  }   bufferAccess;
    union {
     xDirectAlphaBufferInfo    alphaInfo;
     xDirectStencilBufferInfo  stencilInfo;
     xDirectAccumBufferInfo    accumInfo;
     xDirectDepthBufferInfo    depthInfo;
     xDirectMaskBufferInfo     maskInfo;
     xDirectAuxilBufferInfo    auxilInfo;
     xDirectFrameBufferInfo    frameInfo;
     xDirectMultiBufferInfo    mbuffInfo;
     xDirectStereoBufferInfo   stereoInfo;
     xDirectMultisampleBufferInfo    multisampleInfo;
     xDirectExtendedcolorBufferInfo  extendedcolorInfo;
          }   bufferInfo;       
} xDirectBufferAccessReply;
#define sz_xDirectBufferAccessReply    72

typedef struct {
    CARD8  reqType;        /* DirectAccessReqCode   */
    BYTE   mcode;          /* X_DirectAdapterAccess */
    CARD16 length B16;
    INT32  scrnNum B32;
    INT32  pid B32;
    INT32  nid B32;
} xDirectAdapterAccessReq;

typedef struct {
    BYTE   type;
    BYTE   access;
    CARD16 sequenceNumber B16;
    CARD32 length B32;
    CARD32 aid B32;
    CARD32 gsc_handle B32;
    CARD32 pad4 B32;
    CARD32 pad5 B32;
    CARD32 pad6 B32;
    CARD32 pad7 B32;
} xDirectAdapterAccessReply;

typedef struct {
	CARD8	reqType ; 	/* NewFontReqCode */
	BYTE	mcode   ; 	/* X_NewFont */
	CARD16	length B16 ;
	Font	fid;		/* font id */
	CARD32  shmID;		/* key of shared segment */
	CARD32  shm_off;	/* offset into shared segment */
	CARD32	font_len;	/* length of font */
} xNewXFontReq;

typedef struct {
    CARD8 reqType ; 
    CARD8 mcode ; 
    CARD16 length  ;
    INT32  nid B32 ;	/* cpu id  */
    Window wid B32 ;
} xDirectWindowAccessReq;

typedef struct {
    BYTE   type;
    BYTE   access;
    CARD16 sequenceNumber B16;
    CARD32 length B32;
    CARD64 wg_handle;
    CARD32 pad4 B32;
    CARD32 pad5 B32;
    CARD32 pad6 B32;
    CARD32 pad7 B32;
} xDirectWindowAccessReply;

typedef struct {
    CARD8 reqType ; 
    CARD8 mcode ; 
    CARD16 length  ;
    Window wid B32 ;
    INT32  on  B32 ;
} xFullScreenReq;

typedef struct {
    BYTE   type;
    BYTE   access;
    CARD16 sequenceNumber B16;
    CARD32 length B32;
    CARD32 pad2 B32;
    CARD32 pad3 B32;
    CARD32 pad4 B32;
    CARD32 pad5 B32;
    CARD32 pad6 B32;
    CARD32 pad7 B32;
} xFullScreenReply;

typedef struct {
    CARD8 reqType ;
    CARD8 mcode ;
    CARD16 length  ;
    Window wid B32 ;
    INT32  on  B32 ;
} xManageOverlayReq;

typedef struct {
    BYTE   type;
    BYTE   access;
    CARD16 sequenceNumber B16;
    CARD32 length B32;
    CARD32 pad2 B32;
    CARD32 pad3 B32;
    CARD32 pad4 B32;
    CARD32 pad5 B32;
    CARD32 pad6 B32;
    CARD32 pad7 B32;
} xManageOverlayReply;

typedef struct {
    CARD8 reqType;
    CARD8 mcode;
    CARD16 length;
    CARD32 time;
} xQueryMemoryUsageReq;

typedef struct {
    BYTE   type;
    BYTE   access;
    CARD16 sequenceNumber B16;
    CARD32 length B32;
    CARD32 pad2 B32;
    CARD32 pad3 B32;
    CARD32 pad4 B32;
    CARD32 pad5 B32;
    CARD32 pad6 B32;
    CARD32 pad7 B32;
} xQueryMemoryUsageReply;

typedef struct {
      CARD8 reqType ;
      CARD8  directaccessReqType;
      CARD16 length  ;
      Drawable drawable B32 ;
  } xDAEQueryCapabilitiesReq;
  
typedef struct {
      BYTE   type;
      BYTE   pad;
      CARD16 sequenceNumber B16;
      CARD32 length B32;
      CARD32 capabilities;
      CARD32 pad1;
      CARD32 pad2;
      CARD32 pad3;
      CARD32 pad4;
      CARD32 pad5;
} xDAEQueryCapabilitiesRep;

typedef struct {
      CARD8 reqType ;
      CARD8  directaccessReqType;
      CARD16 length  ;
      Window wid B32 ;
      BOOL   state; 
      CARD8  pad1;
      CARD8  pad2;
      CARD8  pad3;
} xDAEWriteToBothBuffersReq;

typedef struct _DAEChangeDisplayResolution {
    CARD8       reqType;
    CARD8       directaccessReqType;
    CARD16      length;
    Window      wid;
    CARD32      resolution;
    CARD32      reserved;
} xDAEChangeDisplayResolutionReq;

#define sz_xDAEChangeDisplayResolutionReq 16



/**                                                       
*** aixCursorExtensionl PROTOCOL STRUCTURE DEFINITION      
**/                                                  
typedef struct {
    CARD8  reqType;         /* always CursorReqCode           */
    CARD8  cursorReqType;   /* always X_CursorQueryVersion    */
    CARD16 length;          /* sz_xCursorQueryVersionReq/4=2  */
    CARD16 majorVersion  B16;
    CARD16 minorVersion  B16;
} xCursorQueryVersionReq;

typedef struct {
    BYTE   type;                 /* always X_Reply = 1       */
    CARD8  pad1;
    CARD16 sequenceNumber B16;
    CARD32 length         B32;   /* =(sz_xCursorQueryVersionReply-32)/4=0 */
    CARD16 majorVersion   B16;   /* =aixCURSOR_MAJOR_VERSION              */
    CARD16 minorVersion   B16;   /* =aixCURSOR_MINOR_VERSION              */
    CARD32 pad2           B32;
    CARD32 pad3           B32;
    CARD32 pad4           B32;
    CARD32 pad5           B32;
    CARD32 pad6           B32;
} xCursorQueryVersionReply;

typedef struct {
    CARD8     reqType;        /* always CursorReqCode               */
    CARD8     cursorReqType;  /* always X_GetCrossHairCursorInfo    */
    CARD16    length;         /* sz_xGetCrossHairCursorInfoReq/4=2  */
    Drawable  drawable;
} xGetCrossHairCursorInfoReq;

typedef struct {
    BYTE   type;                 /* always X_Reply = 1             */
    CARD8  pad1;
    CARD16 sequenceNumber B16;
    CARD32 length         B32;   /* =(sz_xGetCrossHairCursorInfoReply-32)/4=0 */
    CARD16 max_width;
    CARD16 min_width;
    CARD16 best_width;
    CARD16 best_base;
    CARD32 pad2           B16;
    CARD32 pad3           B32;
    CARD32 pad4           B32;
    CARD32 pad5           B32;
} xGetCrossHairCursorInfoReply;

typedef struct {
    CARD8  reqType;               /* always CursorReqCode              */
    CARD8  cursorReqType;         /* always X_RecolorCrossHairCursor   */
    CARD16 length;                /* sz_xRecolorCrossHairCursorReq/4=5 */
    Cursor cid  B32;              /* cursor id to be recolored         */
    xColorItem  xcolor;
} xRecolorCrossHairCursorReq;

typedef struct {
    CARD8     reqType;            /* always CursorReqCode               */
    CARD8     cursorReqType;      /* always X_GetMultiColorCursorInof   */
    CARD16    length;             /* sz_xGetMultiColorCursorInfoReq/4=2 */
    Drawable  drawable;
} xGetMultiColorCursorInfoReq;

typedef struct {
    BYTE   type;                 /* always X_Reply */
    CARD8  pad1;
    CARD16 sequenceNumber B16;
    CARD32 length         B32;   /* sz(Reply+DATA-32)/4 */
    CARD16 cursor_planes;
    CARD16 pad2;
    INT32  transparent_pixel;
    CARD16 width;
    CARD16 height;
    CARD32 pad3           B32;
    CARD32 pad4           B32;
    CARD32 pad5           B32;
} xGetMultiColorCursorInfoReply;

typedef struct {
    CARD8 reqType;
    CARD8 mcode ;
    CARD16 length ;
    Cursor cid  B32;
    INT16 width ;
    INT16 base ;
    xColorItem xcolor ;
} xCreateCrossHairReq;


typedef struct {
    CARD8 reqType;
    CARD8 mcode ;
    CARD16 length ;
} xQueryCrossHairReq;

typedef struct {
    BYTE type;
    CARD8  pad;
    CARD16 sequenceNumber B16;
    CARD32 length B32;
    CARD16 max_wid B16;
    CARD16 min_wid B16;
    CARD16 best_wid B16;
    CARD16 base B16;
    CARD32 colors B32;
    CARD32 pad1 B32;
    CARD32 pad2 B32;
    CARD32 pad3 B32;
} xQueryCrossHairReply;

typedef struct {
    CARD8 reqType;
    CARD8 mcode ;
    CARD16 length ;
    Cursor cid  B32 ;
    Pixmap pmid  B32 ;
    INT32 x B32 ;
    INT32 y B32 ;
} xCreateMultiColorCurReq;


typedef struct {
    CARD8 reqType;
    CARD8 mcode ;
    CARD16 length ;
    Cursor cid  B32;
} xRecolorMultiColorCurReq;

typedef struct {
    CARD8 reqType;
    CARD8 mcode ;
    CARD16 length B16 ;
    Colormap cmid  B32;
    CARD16 duration B16 ;
    BYTE pad1, pad2 ;
    xColorItem  xcolor ;
} xExtBlinkReq;


typedef struct {
    CARD8 reqType;
    CARD8 mcode ;
    CARD16 length  B16;
    Colormap cmap  B32;
} xExtStoreAnyColorsReq;

typedef struct {
    CARD8 reqType;
    CARD8 mcode ;
    CARD16 length;
    Drawable drawable;
    GContext gc;
    INT16 xoff,yoff;
} xDrawPolyMarkerReq;

typedef struct {
    CARD8 reqType;
    CARD8 mcode ;
    CARD16 length;
    Drawable drawable;
    GContext gc;
    BYTE coordMode;
    BYTE pad1,pad2,pad3;
} xDrawPolyMarkersReq;

typedef struct {
    CARD8 reqType;
    CARD8 mcode ;
    CARD16 length;
    GContext gc;
    Pixmap  marker;
    INT16 xhot,yhot;
} xSetPolyMarkerReq;


typedef union {
    xGenericReply generic;
    xGetDPYInfoReply getDPYInfo;
    xError error;
} xExtReply;


/* restore these definitions back to the typedefs in X.h */
#undef Window
#undef Drawable
#undef Font
#undef Pixmap
#undef Cursor
#undef Colormap
#undef GContext

#endif /* _AIXPROTO_H */
