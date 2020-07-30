/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/POWER/execargs.h 1.15                       */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,1995          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)50	1.15  src/bos/usr/include/POWER/execargs.h, sysproc, bos530 11/17/98 14:42:16 */
/*
 * COMPONENT_NAME: (SYSPROC) Process Management 
 *
 * FUNCTIONS: 
 *
 * ORIGINS: 3, 6, 27
 *
 */

#ifndef _H_EXECARGS
#define _H_EXECARGS

/*
 * This include file permits ps to print the command line for
 * a process.  Given the address of the argument vector for
 * the command, the shell uses the newargs() macro to put the
 * address of the argument vector where ps can find it.
 */

#include <sys/param.h>
extern int _errno;

#if defined(__64BIT_KERNEL) && defined(_KERNEL)
typedef unsigned int	__cptrp32_64_t;
#else
typedef char **		__cptrp32_64_t;
#endif 

struct	top_of_stack {
	ulong32int64_t	main_reg[NGPRS];
	ulong32int64_t	lr;
	__cptrp32_64_t	environ;
	int	errno;
#if defined(__64BIT__) && !defined(_KERNEL) 
	uint			reserved1;
	ulong			reserved2;
	void *			usla_cblk;
	ulong			reserved3;
#endif
};

typedef struct top_of_stack TopOfStack;

#define TopOfBaseStack	((struct top_of_stack *)((long)&_errno	 \
					- sizeof(__cptrp32_64_t) \
					- sizeof(ulong32int64_t) \
					- sizeof(ulong32int64_t[NGPRS])))

#define ARGC_value	(&(TopOfBaseStack->main_reg[ARG1]))
#define ARGS_loc	(&(TopOfBaseStack->main_reg[ARG2]))
#define ENVS_loc	(&(TopOfBaseStack->main_reg[ARG3]))
#define newargs(argv)	(*(__cptrp32_64_t *)ARGS_loc = (argv))

#endif /* _H_EXECARGS */
