/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/atomic_op.h 1.7.1.7                          */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1993,2002          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)85       1.7.1.7  src/bos/kernel/sys/atomic_op.h, sysproc, bos530 8/6/02 15:40:28 */
/*
 *   COMPONENT_NAME: SYSPROC
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 27, 83
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1993
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 * LEVEL 1,  5 Years Bull Confidential Information
 */

#ifndef _H_ATOMIC_OP
#define _H_ATOMIC_OP

#include <sys/types.h>

typedef int	*atomic_p;
typedef ushort	*atomic_h;
typedef long	*atomic_l;

#ifdef _NO_PROTO

int  fetch_and_add();
uint fetch_and_and();
uint fetch_and_or();
boolean_t compare_and_swap();
long  fetch_and_addlp();
ulong fetch_and_andlp();
ulong fetch_and_orlp();
boolean_t compare_and_swaplp();
ushort fetch_and_add_h();

#ifdef _KERNEL
boolean_t test_and_set();
int fetch_and_nop();
#endif

#else /* _NO_PROTO */

#ifdef _KERNSYS
#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)
boolean_t test_and_setlp(atomic_l, unsigned long);
boolean_t test_and_setsp(atomic_h, short);
#endif
#endif

int  fetch_and_add(atomic_p,int);
uint fetch_and_and(atomic_p,uint);
uint fetch_and_or(atomic_p,uint);
boolean_t compare_and_swap(atomic_p,int *,int);
long  fetch_and_addlp(atomic_l,long);
ulong fetch_and_andlp(atomic_l,ulong);
ulong fetch_and_orlp(atomic_l,ulong);
boolean_t compare_and_swaplp(atomic_l, long *, long);
ushort fetch_and_add_h(atomic_h,int);

#ifdef _KERNEL
boolean_t test_and_set(atomic_p, int);
int fetch_and_nop(atomic_p);
void * get_from_list(void *,long);
void * get_all_from_list(void *,long);
void   put_onto_list(void *,void *,long);
void   put_chain_onto_list(void *,void *,void *,long);
#endif

#endif /* _NO_PROTO */

/* Atomic Locking primitives--User mode routines */

#ifndef _KERNEL
#ifdef _NO_PROTO

boolean_t _check_lock();
void _clear_lock();
void _clear_lock_mem();
/* _safe_fetch is an obsolete function and should not be used */
int _safe_fetch();

#else /* _NO_PROTO */

boolean_t _check_lock(atomic_p, int, int);
void _clear_lock(atomic_p, int);
void _clear_lock_mem(atomic_p, int);
/* _safe_fetch is an obsolete function and should not be used */
int _safe_fetch(atomic_p);

#endif /* _NO_PROTO */

#ifndef __ia64
/* Atomic Locking primitive pragmas */

#pragma mc_func _clear_lock { \
 "48003403" /* bla    ._clear_lock */ \
}
#pragma mc_func _clear_lock_mem { \
 "48003413" /* bla    ._clear_lock_mem */ \
}
#pragma mc_func _check_lock { \
 "48003423" /* bla    ._check_lock */ \
}
#pragma mc_func _safe_fetch {          \
 "80630000" /* l      r3,0(r3)      */ \
 "5463003F" /* rlinm. r3, r3, 0, -1 */ \
 "41820004" /* beq    $+4           */ \
}
#pragma reg_killed_by _safe_fetch cr0,gr3
#endif /* ! __ia64 */

#endif /* !_KERNEL */

#endif /* _H_ATOMIC_OP */
