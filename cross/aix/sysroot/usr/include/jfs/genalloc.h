/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/jfs/genalloc.h 1.5                          */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,2001          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)43	1.5  src/bos/usr/include/jfs/genalloc.h, syspfs, bos530 6/11/01 15:29:16 */
/*
 * COMPONENT_NAME: (SYSPFS) Physical File System
 *
 * FUNCTIONS: genalloc.h
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_JFS_GENALLOC
#define _H_JFS_GENALLOC

#include <sys/types.h>

/* Common table management for large tables, genalloc structure should 
 * be kept to # of words that will divide evenly into PAGESIZE.
 */
struct genalloc
{	char	a_handle[8];		/* Object id			*/
	caddr_t	a_head;			/* Head of the free list	*/
	caddr_t	a_hiwater;		/* Current high water mark	*/
	caddr_t	a_table;		/* Static table			*/
	caddr_t	a_end;			/* Last+1 table element		*/
	int	a_osz;			/* Object size in bytes		*/
	int32long64_t	a_froff;	/* Saved offset of free pointer */
};

typedef	struct genalloc genalloc_t;

#define objsize(x)      ((x)->a_osz)
#define freeobj(x)      ((x)->a_head)
#define eotbl(x)      	((x)->a_end)

int geninit(int, int, int, off_t, caddr_t, genalloc_t **, caddr_t);
void *genalloc(genalloc_t *);
int genfree(genalloc_t *, void *);
void gentouch(genalloc_t *);

#endif /* _H_JFS_GENALLOC */
