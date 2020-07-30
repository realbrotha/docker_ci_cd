/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* gos530 src/gos/2d/graphics_tools/kaplib/kapture.h 1.4                  */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1996,1997          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */


/**********************************************
 *  Required Include Files                    
 **********************************************/
#define KINCS
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>


#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif
/**********************************************************************
* errors
**********************************************************************/
#define KFORMATERR     2    /* Unexpected format in xwd file             */
#define KMEMFAIL       4    /* returned when alloc fails                 */
#define KCOLORERR      8    /* number of colors exceeds color table size */
#define KCREATEXFAIL  16    /* call to xcreate image failed              */
#define KXERROR       32    /* error returned from x window function call*/
#define KREADERR      64    /* File read failed                          */
#define KUNSUPPORTED 128    /* unsupported visual type ( GTO only )      */


#define KRGB 0
#define KCMAP 1
#define K_DEF_CTAB_SIZE 4096
#define KTABENVNAME "KCTABSIZE"

/* output file formats */

#define K_PS4   0x01	/* Postscript 4 Bit greyscale		*/
#define K_PS8  	0x02	/* Postscript 8 Bit colormapped		*/
#define K_PS24 	0x04	/* Postscript 24 Bit RGB		*/
		
#define K_TIFF4  0x11	/* TIFF 4 Bit greyscale			*/	
#define K_TIFF8  0x12	/* TIFF 8 Bit colormapped		*/
#define K_TIFF24 0x14	/* TIFF 24 Bit RGB			*/

#define K_XWD    0x20   /*   x window dump format               */


/* input parameter data structure Subject to modification */
typedef struct {
          int image_type;
          int ctablesize;
} KDATA;


/***************************************************
*    
* kgetwindow
*        Return a 24 bit truecolor Ximage of a
*        window tree hierarchy given the 
*        XWindow ID of the parent  
*
***************************************************/

extern int
kgetwindow(
              Display *dpy,      /* IN: pointer to display          */
              Window window,     /* IN: window id of parent of tree */
              KDATA *kdata,      /* IN: ptr to aditional info       */
              XImage** ximage    /* OUT:  pointer to ximage pointer */
             );

/***************************************************
*
*  kgetregion
*        Return a 24 bit TrueColor Ximage of a
*        rectangular region of a display:screen given
*        corner points of the region. 
***************************************************/
extern int
kgetregion(     
         Display         *dpy,           /* IN: Display pointer          */ 
         int             xul,            /* IN: x upper left             */
         int             yul,            /* IN: y upper left             */
         int             xlr,            /* IN: x lower right            */
         int             ylr,            /* IN: y lower right            */
         KDATA           *kdata,         /* IN: ptr to aditional info    */
         XImage **       Ximage          /* OUT: ptr to Ximage structure */
          );
/***************************************************
*
*  kgetwindow_pseudo
*        Return an Ximage of a window tree hierarchy
*        given the Xwindow ID of teh parent window.
*        Image returned will
*        be 8 bit pseudo color if the number of colors is
*        less than or equal to 255, else it will be
*        24 bit pseudo color
***************************************************/


extern int kgetwindow_pseudo(
                Display  *dpy,          /* IN: pointer to display          */
                Window   window,        /* IN: window id of parent of tree */
                KDATA    *kdata,        /* IN: ptr to additional info      */
                XImage** ximage,        /* OUT:  pointer to ximage pointer */
                XColor** color_array,   /* OUT: array of colors used       */
                int*     numcolors,     /* OUT: ptr to area to write       */
                Colormap *colormap      /* OUT: ID of installed colormap if valid */
             );



/***************************************************
*
*  kgetregion_pseudo
*        Return an Ximage of a
*        rectangular region of a display:screen given
*        corner points of the region. Image returned will
*        be 8 bit pseudo color if the number of colors is
*        less than or equal to 255, else it will be
*        24 bit pseudo color
***************************************************/

extern int
kgetregion_pseudo(     
       Display         *dpy,           /* IN:  Display pointer 		*/
       int             xul,            /* IN:  x upper left       	*/
       int             yul,            /* IN:  y upper left 	 	*/
       int             xlr,            /* IN:  x lower right 		*/
       int             ylr,            /* IN:  y lower right 		*/
       KDATA           *kdata,         /* IN: ptr to aditional info       */
       XImage **       Ximage,         /* OUT: image structure 		*/
       XColor**        color_array,    /* OUT: array of colors used 	*/
       int*            numcolors,      /* OUT: ptr to area to write 
                                                       # of colors used */
       Colormap*       colormap      /* OUT: ID of installed colormap if valid */
              );

/***************************************************
*
This function will return an Ximage of a window tree hierarchy
given the Xwindow ID of the parent window.
Image returned will be 8 bit pseudo color if the number of colors is
less than or equal to 255, else it will be 24 bit true color. (eventually this
may be expanded to support 12 bit via a flag passed in the KDATA structure).
This function will be optimal for grabbing 8 bit window heirarchies that only
share a single color map. Additionally it will provide data in a format
that will offer the best performance for displaying on displays that
support both 8 and 24 bit visuals. 
This function will return accurate data for all visuals
on all servers regardless of server or
window depth or visual types and combinations of the same.
The return code will be non zero if an error occurs.
*****************************************************************/

extern int kgetwindow_bestdepth(
            Display *dpy,            /* IN: pointer to display          */
            Window window,           /* IN: window id of parent of tree */
            KDATA   *kdata,          /* IN: ptr to additional info      */
            XImage** ximage,         /* OUT:  pointer to ximage pointer */
            XColor** color_array,    /* OUT: array of colors used       */
            int* numcolorsr,           /* OUT: ptr to area to write
                                                       # of colors used */
            Colormap* colormap      /* OUT: ID of installed colormap if valid */
             );

/***************************************************************  
*
  This function will return an Ximage of a
  rectangular region of a display:screen given
  corner points of the region. Image returned will
  be 8 bit pseudo color if the number of colors is
  less than or equal to 255, else it will be
  24 bit true color.

  This function will be optimal for grabbing 8 
  bit window regions that only share a single color map. 
  Additionally it will provide data in a format
  that is optimal for conversion to color table oriented file formats.
  that will offer the best performance for displaying on displays that
  support both 8 and 24 bit visuals. 

  This function will return accurate data for all visuals
  on all servers regardless of server or
  window depth or visual types and combinations of the same.
  The return code will be non zero if an error occurs.
*
*******************************************************************/

extern int
kgetregion_bestdepth(
       Display         *dpy,           /* IN:  Display pointer          */
       int             xul,            /* IN:  x upper left             */
       int             yul,            /* IN:  y upper left             */
       int             xlr,            /* IN:  x lower right            */
       int             ylr,            /* IN:  y lower right            */
       KDATA           *kdata,         /* IN: ptr to additional info     */
       XImage **       Ximage,         /* OUT: image structure          */
       XColor**        color_array,    /* OUT: array of colors used     */
       int*            numcolors,      /* OUT: ptr to area to write
                                                       # of colors used */
       Colormap*       colormap        /* OUT: ID of installed colormap if valid */
              );

/**********************************************************
*
extern   kgetwindow_8

  This function will return an Ximage of a window tree 
  hierarchy given the Xwindow ID of the parent window. 
  Image returned will be 8 bit pseudo color. 
  If the number of colors is less than or equal to 
  255 this function will return accurate data. 
  Otherwise it will apply color reduction algorythm 
  specified in the KDATA structure to compress the 
  number of colors to 255. This function will be optimal 
  for producing images for display
  on devices that will not support greater 
  than 8 bits per pixel. 
  The return code will be non zero if an error occurs. 
*
*************************************************************/

int kgetwindow_8(
              Display *dpy,       /* IN: pointer to display          */
              Window window,      /* IN: window id of parent of tree */
              KDATA   *kdata,     /* IN: ptr to additional info       */
              XImage** ximage,    /* OUT:  pointer to ximage pointer */
              XColor** color_array,/* OUT: array of colors used     */
              int* numcolors,     /* OUT: ptr to area to write
                                                       # of colors used */
              Colormap* colormap  /* OUT: ID of installed colormap if valid */
             );

/*********************************************************************
*

  kgetregion_8

  This function will return an Ximage of a rectangular 
  region of a display:screen given corner points of the 
  region. Image returned will be 8 bit pseudo color. 
  If the number of colors is less than or equal to 255 
  this function will return accurate data. Otherwise it 
  will apply color reduction algorythm specified in the 
  KDATA structure to compress the number of colors to 255. 
  This function will be optimal for producing images
  for display on devices that will not support greater 
  than 8 bits per pixel. The return code will be 
  non zero if an error occurs. 
*
**********************************************************************/

extern int
kgetregion_8(
       Display         *dpy,           /* IN:  Display pointer          */
       int             xul,            /* IN:  x upper left             */
       int             yul,            /* IN:  y upper left             */
       int             xlr,            /* IN:  x lower right            */
       int             ylr,            /* IN:  y lower right            */
       KDATA           *kdata,         /* IN: ptr to additional info     */
       XImage **       Ximage,         /* OUT: image structure          */
       XColor**        color_array,    /* OUT: array of colors used     */
       int*            numcolors,      /* OUT: ptr to area to write
                                                       # of colors used */
       Colormap*       colormap  /* OUT: ID of installed colormap if valid */
              );

/*----------------------------------------------------------*/
/*----------------------------------------------------------*/
/* File IO Functions                                        */
/*----------------------------------------------------------*/
/*----------------------------------------------------------*/


/* **************************************************************
*  
   kwrite
 
   output  the Ximage to the open stream 
   indentified by the FileDescriptor parameter.
   Data formated according to the Kfiletype parameter. Numcolors and 
   colormap are ignored for direct color visuals. Xvisual type must
   be either pseudocolor or direct color. On a succesful call the number
   of bytes written will be returned. Negative 1 (0xFFFFFF)
   will be returned on error. 
*
********************************************************************/


extern int kwrite(
       int FileDescriptor,     /* IN: File discriptor to write to */
       XImage* ximage,         /* IN: Ptr to XImage structure     */
       int visualtype,         /* IN: Visual type from X.h        */
       int numcolors,          /* IN: Highest entry used in table */
       XColor* colormap,       /* IN: Array of Xcolors            */
       int Kfiletype           /* IN: Format of output file       */
      );

/********************************************************************
*
  kread

  read a xwd formmatted stream and return the contents as an 
  Ximage and array of Xcolors. If the visual type of the 
  xwd stream is DirectColor, the numcolors returned will be
  0 and there will be no memory allocated for the colormap.
  If the visual type is PseudoColor  storage for the colormap
  will be allocated. In all cases storage for the ximage will
  be allocated. If the visual type is not PseudoColor or 
  DirectColor an error will be returned. If the call is succesful,
  the number of bytes read will be returned on the stack.
  If an error occurs 0xFFFFFFFF (-1) will be returned and
  any storage allocated by the function will be freed. 
*
************************************************************************/
  

extern int kread(
       int FileDescriptor,     /* IN: File discriptor to read from  */
       XImage** ximage,        /* OUT: Ptr to XImage structure      */
       int *visualtype,        /* OUT: Visual type from X.h         */
       int *numcolors,         /* OUT: Highest entry used in table  */
       XColor** colormap        /* OUT: Array of Xcolors             */
      );



/*----------------------------------------------------------*/
/*----------------------------------------------------------*/
/* Utilitiy Functions                                       */
/*----------------------------------------------------------*/
/*----------------------------------------------------------*/
/*******************************************************************/
/* return a window id from a mouse click                           */
/*******************************************************************/
extern Window Select_Window( Display  *dpy );


/*******************************************************************/
/* return a rectangle selected by rubberbanding on the screen      */
/*******************************************************************/
void rubberband(
                Display * dpy,
                int  *          xul,            /* IN x upper left */
                int  *          yul,            /* IN y upper left */
                int  *          xlr,            /* IN x lower right */
                int  *          ylr            /* IN y lower right */
              );

/*******************************************************************/
/* open a 24 bit true color window on any display that supports it */
/*******************************************************************/
extern int
initTrueColor(Display * dpy,     /* ptr to display on which to open win */
              Window * window,   /* pointer to win id to be returned    */
              int w,             /* width of the window in pixels       */
              int h              /* height of the window in pixels      */
             );




extern int
initPseudoColor(Display *dpy,
                Window *swindow,
                int x,
                int y,
                int depth,
                int numcolors,
                XColor * color_array);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

