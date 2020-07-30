/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/dev.h 1.3                                    */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1991          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)38	1.3  src/bos/kernel/sys/dev.h, sysspecfs, bos530 4/29/91 11:55:11 */
/*
 * COMPONENT_NAME: (SYSSPECFS) Special File System
 *
 * FUNCTIONS: 
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

#ifndef _H_DEV
#define _H_DEV

/* Test for dd entry points */
# define	TDD_MPX(maj) 	(devsw[maj].d_mpx)
# define	TDD_STRAT(maj) 	(devsw[maj].d_strategy)
# define	TDD_TTY(maj) 	(devsw[maj].d_ttys)
# define	TDD_DUMP(maj) 	(devsw[maj].d_dump)
# define	TDD_SELECT(maj) (devsw[maj].d_select)
# define	TDD_READ(maj) 	(devsw[maj].d_read)
# define	TDD_WRITE(maj) 	(devsw[maj].d_write)

#endif /* _H_DEV */
