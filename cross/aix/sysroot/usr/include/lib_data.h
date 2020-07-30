/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/lib_data.h 1.6                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1992,1993          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)04	1.6  src/bos/usr/include/lib_data.h, libcthrd, bos530 7/22/02 12:39:18 */
/*
 *   COMPONENT_NAME: LIBCTHRD
 *
 *   FUNCTIONS: LIB_DATA_FUNCTION
 *		lib_data_hdl
 *		lib_data_ref
 *
 *   ORIGINS: 27,71
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1992,1993
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 */
/*
 * (c) Copyright 1990, 1991, 1992 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */

/* lib_data.h,v $ $Revision: 1.2 $ (OSF) */

#ifndef _H_LIB_DATA
#define _H_LIB_DATA
/*
 * Library macros/ types for "thread" data access
 */

typedef struct lib_data_functions {
	int	(*data_hdl)(void **);
	void	*(*data_ref)(void *);
	void	*(*data_errno_addr)(void);
} lib_data_functions_t;


#define	LIB_DATA_FUNCTION(datastruct, operation, arg) \
	((datastruct).operation ? (*(datastruct).operation)(arg) : 0)

#define	lib_data_hdl(datastruct, hdl) \
	LIB_DATA_FUNCTION(datastruct, data_hdl, hdl)

#define	lib_data_ref(datastruct, hdl) \
	LIB_DATA_FUNCTION(datastruct, data_ref, hdl)

#define	lib_errno_addr(datastruct) \
        ((datastruct).data_errno_addr ? (*(datastruct).data_errno_addr)() : 0)

/* 
 * specific data callback queues and synchronization primitive queues
 * are doubly linked lists. 
 */

typedef struct __clbk_queue {
    struct __clbk_queue *next;
    struct __clbk_queue *prev;
} __clbk_queue;

typedef void (*__clbk_fnc)(void);

typedef struct __clbk_node {
    __clbk_queue    queue;	    /* queue */
    __clbk_fnc	    callback_func;  /* callback function */
    int		    pri;	    /* prioriry order  */
    long	    reserved[10];   /* reserved */
} __clbk_node;

/*
 * Queue priorities are as follows:
 *    0 -   99	Specifies highest priority order
 *  100 -  799	Default order in FIFO order
 *  800 -  999	reserved for internal AIX callbacks.
 *
 *	   900	is reserved for libs.a since it needs to 
 *		initialized last.
 *
 */
#define CALLBACK_MAX_PRI	1000
#define CALLBACK_DEFAULT_PRI	100
#define LIB_S_PRI		900			/* called last */

/*
 * callback queue
 */
extern __clbk_queue __clbk_q;

extern int  _libc_callback_register( __clbk_node *, __clbk_fnc, int );
extern void _libc_callback_remove( __clbk_node *);

#endif /* _H_LIB_DATA */
