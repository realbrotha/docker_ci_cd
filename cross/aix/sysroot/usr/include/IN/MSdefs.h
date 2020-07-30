/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/IN/MSdefs.h 1.8                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1989          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)35	1.8  src/bos/usr/include/IN/MSdefs.h, libIN, bos530 6/16/90 00:17:17 */
/*
 * COMPONENT_NAME: LIBIN
 *
 * FUNCTIONS:
 *
 * ORIGINS: 9,27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 */

/*
 * Segmented memory stack allocator definitions
 */

#ifndef _H_MSdefined
#define _H_MSdefined

#include <IN/LSdefs.h>

typedef struct MSstag {struct MSstag *next; char blk[1];} MSsegment;
typedef struct {
        List1 segs;		/* list of MSsegment's */
	unsigned short size;    /* size of chunks in this stack */
	unsigned short align;   /* alignment boundary for objects */
        char *nextbyte;		/* points to next available byte */
        char *(*alloc)();	/* address of alloc routine */
        void (*free)();		/* address of free routine */
        void (*error)();}	/* address of error routine */
    MSheader;
typedef struct {MSheader *ms; MSsegment *seg; char *byte;} MSpointer;

extern void MSinit(/* MSheader *ms; unsigned size,align;
			char *(*alloc)(); void (*free)(),(*errmsg)() */);
extern void MSterm(/* MSheader *ms */);
extern MSpointer MSsavetop(/* MSheader *ms */);
extern void MSrestoretop(/* MSpointer *msp */);
extern char *MSgetblock(/* MSheader *ms; int sz */);

#endif
