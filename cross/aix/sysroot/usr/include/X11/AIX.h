/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* gos530 src/gos/2d/XTOP/programs/Xserver/ddx/AIX/AIX.h 1.16             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1996          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)63     1.16  src/gos/2d/XTOP/programs/Xserver/ddx/AIX/AIX.h, xext, gos530 12/17/96 08:04:54  */
/*
 *   COMPONENT_NAME: X11
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 16,27,40,42
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _AIX_H
#define _AIX_H

#define AIX_GLYPHS_PER_KEY   2
#define AIX_MIN_KEY       0x08
#define AIX_MAX_KEY       0xf7+AIX_MIN_KEY

#define XDEV_IBM_K101		  0	/* American keyboard (101 keys)  */
#define XDEV_IBM_K102		  1	/* European keyboard (102 keys)  */
#define XDEV_IBM_K106		  2	/* Japanese keyboard (106 keys)  */

#define XDEV_IBM_APA8		6153
#define XDEV_IBM_APA8C		6154
#define XDEV_IBM_APA16		6155
#define XDEV_IBM_MPEL		5081
#define XDEV_IBM_EGA		5154
#define XDEV_IBM_8514A		8514
#define XDEV_IBM_GSL		4444

#define XDEV_IBM_GAI		9999
#define XDEV_IBM_SKYWAY		1111	
#define XDEV_IBM_SABINE		2222
#define XDEV_IBM_GEMINI		3333
#define XDEV_IBM_SKYMONO	5555
#define XDEV_IBM_PEDER		6666
#define XDEV_IBM_SGA		7777


#define AIXConnectionClosed   255

#define XAIXEXTENSIONNAME "XAixExtension" /* misc extensions */
#define AIXDIRECTRESOURCENAME "AixDirectResource" /* direct resource access */

#define AIXDIRECTNAME  "aixDirectAccessExtension"
#define DIRECTACCESSNAME "xDirectAccessExtension"
#define aixDIRECTACCESS_MAJOR_VERSION      1
#define aixDIRECTACCESS_MINOR_VERSION      6 
#define AIXCURSOREXTENSION "aixCursorExtension"	/* crosshair, 3colors, etc */
#define aixCURSOR_MAJOR_VERSION 1  /* aixCursorExtension Version Numbers */
#define aixCURSOR_MINOR_VERSION 0
#define COLORMAPEXTNAME "xColormapExtension"	/* blink, etc */

 
/* misc extensions */

#define X_DrawPolyMarker	1
#define X_SetPolyMarker		2
#define X_DrawPolyMarkers	3
#define X_AAAA			4	/* non support */
#define X_BBBB			5	/* non support */
#define X_DrawGeoText		6	/* non support */
#define X_SetGeoText		7	/* non support */
#define X_CCCC              	8       /* non support */

/* direct resource access */

#define X_DirectAdapterAccess		1
#define X_DirectWindowAccess		2
#define X_DirectFontAccess		3
#define X_QueryDirectResourceAccess	4
#define X_FullScreen			5
#define X_NewXFont			6
#define X_ManageOverlay                 7
#define X_QueryMemoryUsage		8
#ifdef GL_X_PERF
#define X_DirectInputAccess		9
#endif
#define X_DirectBufferAccess		10
#define X_FastResUpdate                 11
#define X_HardwareSync                  12
#define X_DirectAccessQueryVersion      13
#define X_ChangeCoreDeviceControl       14
#define X_GetCoreDeviceControl       	15
#define X_DAEQueryCapabilities          16
#define X_DAEWriteToBothBuffers         17
#define X_DAEChangeDisplayResolution    19



#define FLUSHTOFRAMEBUFFER              0
#define QUERY_ALL_ACTIVE_MEM		0
#define	QUERY_MEM_SINCE_LAST_QUERY	1

/* WRITE TO BOTH BUFFERS DEFINES		*/
#define	DAEWriteToBothBuffersOn		1
#define	DAEWriteToBothBuffersOff	0	

/* QUERY CAPABILITIES DEFINES			*/
#define DAEWriteToBothBuffersCapability		(1l<<0)

/* DEFINES FOR CHANGE RESOLUTION ON THE FLY	*/
#define DAEResolutionDefault                    (1L<<0)
#define DAEResolution640X480                    (1L<<1)

/* aixCursorExtension Protocol Minor Nubmer */
#define X_CreateCrossHair	1
#define X_QueryCrossHair	2
#define X_CreateMultiColorCur	3	/* for 3-colors cursor */
#define X_RecolorMultiColorCur	4
#define X_CursorQueryVersion      5
#define X_GetCrossHairCursorInfo  6
#define X_RecolorCrossHairCursor  7
#define X_GetMultiColorCursorInfo 8

#define PSEUDO_BASED_CROSSHAIR  4
#define SCREEN_BASED_CROSSHAIR  1
#define WINDOW_BASED_CROSSHAIR  2
#define NO_CROSSHAIR            0


#define X_ExtBlink		1	/* to support GL only */
#define X_ExtStoreAnyColors	2	/* to support GL only */
#define X_ExtRegisterGlcmap     3       /* to support GL only */


/* *********************************************************************** */
/* Shared memory structure for FastResourceUpdate Protocol in DWA Ext.     */
/* 4kByte = 1021*(sizeof(shmFastResUpdateRec))                             */
/*          + sizeof(shmFastResUpdateHeader)                               */
/* *********************************************************************** */

#define NUM_SHMFASTRESUPDATE_ENTRY 1021
typedef int     shmFastResUpdateRec;
typedef int    *shmFastResUpdateRecPtr;

typedef struct _shmFastResUpdateHeader *shmFastResUpdateHeaderPtr;
typedef struct _shmFastResUpdateHeader
{
     int                       numEntryAllocated;
     shmFastResUpdateRecPtr    disBufEntry;
     shmFastResUpdateHeaderPtr next;
} shmFastResUpdateHeader;

#define Cleanup_shmFastRes(header_p, index_p)	\
{									    \
     --(((shmFastResUpdateHeaderPtr)(header_p))->numEntryAllocated);	    \
     ((shmFastResUpdateHeaderPtr)(header_p))->disBufEntry[(index_p)] = -1;  \
}

#define GetDisplayedBuffer(ptr)          \
{                                        \
    *ptr;                                \
}
#endif /* _AIX_H */
