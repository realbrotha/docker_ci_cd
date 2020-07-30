/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53D src/bos/kernel/sys/POWER/ucontext.h 1.4.1.12                    */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1996,2005          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)04       1.4.1.12  src/bos/kernel/sys/POWER/ucontext.h, sysproc, bos53D, d2005_13A1 3/22/05 13:19:58 */
/*
 * COMPONENT_NAME: SYSPROC
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27 83
 *
 * (C) COPYRIGHT International Business Machines Corp. 1996
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_SYS_UCONTEXT
#define _H_SYS_UCONTEXT

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#if _XOPEN_SOURCE_EXTENDED==1

#include <strict_stdtypes.h>

#ifndef _H_TYPES
#include <sys/types.h>
#endif

#include <sys/context.h>

#include <end_strict_stdtypes.h>

#if defined(__EXTABI__) || defined(__AIXEXTABI)
#define	getcontext	__getcontextx
#define	swapcontext	__swapcontextx
#endif /* __EXTABI__ || __AIXEXTABI */


#ifdef _NO_PROTO

int getcontext();
int setcontext();
void makecontext();
int swapcontext();

#else /* _NO_PROTO */

int getcontext(ucontext_t *);
int setcontext(const ucontext_t *);
void makecontext(ucontext_t *, void (*)(), int, ...);
int swapcontext(ucontext_t *, const ucontext_t *);

#endif /* _NO_PROTO */

#endif /* _XOPEN_SOURCE_EXTENDED */

#ifdef _ALL_SOURCE

/* internal structure for kgetcontext() */
typedef struct __kcontext kcontext_t;

struct __kcontext {
#ifdef __64BIT_KERNEL
	sigset32_t	kc_sigmask;	/* signal mask */
#else
	sigset_t	kc_sigmask;	/* signal mask */
#endif
	stack_t		kc_stack;	/* signal stack */
#ifdef __64BIT_KERNEL
	__ptr32		kc_link;	/* previous context ptr */
#else /* __64BIT_KERNEL */
	ucontext_t	*kc_link;	/* previous context ptr */
#endif /* __64BIT_KERNEL */

	int	        pad[4];		/* rfu */
};


#if defined(_KERNSYS) || defined(_LONG_LONG)
/* 
 * kernel declaration for ucontext_t for 64-bit process. this assumes
 * int is 4-bytes. 32-bit and 64-bit API both use the ucontext_t above.
 */
typedef struct __context64 mcontext64_t;
typedef struct __ucontext64 ucontext64_t;

struct __ucontext64 {
        int                __sc_onstack;
	sigset64_t	uc_sigmask;	/* signal mask to restore */
        int                __sc_uerror;	   /* u_error to restore */
        mcontext64_t       uc_mcontext64;  /* machine image of saved context */
        unsigned long long uc_link64;	   /*context resumed after this one */
        stack64_t          uc_stack64; 	   /* stack used by context */
	unsigned long long __extctx;	   /* address of extended context */
	int		   __extctx_magic; /* if set to __EXTCTX_MAGIC, then */
					   /* extended context is present    */
        int                __pad[1];   	   /* rfu */
};
#endif /* _KERNSYS or _LONG_LONG */

#endif /* _ALL_SOURCE */

#ifdef _KERNSYS


/* kernel uses a union kctxt to cover both 32-bit and 64-bit processes. */
union uctxt {
	ucontext_t	uctx32;
	ucontext64_t	uctx64;
};

/* 
 * kernel declaration for kcontext_t for 64-bit process. this assumes
 * int is 4-bytes. 32-bit and 64-bit API both use the kcontext_t above.
 */
typedef struct __kcontext64 kcontext64_t;

struct __kcontext64 {
	sigset64_t	kc_mask;	/* signal mask		*/
	stack64_t	kc_stack;	/* signal stack         */
	unsigned long long kc_link;	/* previous context ptr */
	int	        pad[4];		/* rfu */
};

/* kernel uses a union kctxt to cover both 32-bit and 64-bit processes. */
union kctxt {
	kcontext_t	kc32;
	kcontext64_t	kc64;
};

#endif /* _KERNSYS */


#endif /* _H_SYS_UCONTEXT */
