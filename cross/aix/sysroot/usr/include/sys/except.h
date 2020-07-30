/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/except.h 1.7                                 */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1993          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)03       1.7  src/bos/kernel/sys/except.h, sysproc, bos530 4/8/98 10:34:10 */
/*
 *   COMPONENT_NAME: SYSPROC
 *
 *   FUNCTIONS: 
 *
 *   ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1993
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */


#ifndef _H_EXCEPT
#define _H_EXCEPT

#include <sys/m_except.h>

/*
 * Structure for registering exception handlers
 */
struct	uexcepth {
	struct	uexcepth	*next;
	int 			(*handler)();
};
#define	EXCEPT_NOT_HANDLED   -1	/* The exception condition was not resolved */
#define	EXCEPT_HANDLED	     0	/* The exception was handled */

/* Programmed I/O Error Recovery Retry count */
#define	PIO_RETRY_COUNT	3		/* retry count of 3 */	

/* Programmed I/O recovery routine action values */
#define PIO_RETRY	0		/* Retry operation */
#define PIO_NO_RETRY	1		/* Do no attempt retry of I/O */

/*
 * Function prototypes for 64bit kernel only
 */
#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)
extern void	getexcept(struct except *);
extern void	uexadd(struct uexcepth *);
extern void	uexdel(struct uexcepth *);
extern void	uexblock(tid_t);
extern pid_t	uexpid(void);
extern void	uexclear(tid_t);
#endif /* __64BIT_KERNEL || __FULL_PROTO */

#endif /*_H_EXCEPT*/
