/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/cs.h 1.1                                     */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,1989          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)38	1.1  src/bos/kernel/sys/cs.h, sysproc, bos530 2/27/90 11:22:38 */
/*
 * COMPONENT_NAME: (SYSPROC) Kernel Process Management
 *
 * FUNCTIONS: 
 *	defines and prototype for the "cs" SVC, compare and swap.
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
#ifndef _h_CS
#define _h_CS

/* Return values. */
#define CS_SWAPPED 0
#define CS_NOT_SWAPPED  1

/*
 * cs prototype.
 *
 * input:
 *	Pointer to the word to test & set.
 *	compare value
 *	swap value placed into word if compares equal.
 *
 * output:
 *	CS_SWAPPED - returned if swap occurred (equal compare)
 *	CS_NOT_SWAPPED - returned if no swap (not equal)
 */
#ifdef _NO_PROTO
extern int cs();
#else /* _NO_PROTO */
extern int cs(int *,int,int);
#endif

#endif /* !_h_CS */
