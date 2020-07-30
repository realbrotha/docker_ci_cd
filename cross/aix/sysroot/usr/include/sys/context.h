/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53V src/bos/kernel/sys/POWER/context.h 1.13.4.1                     */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1988,1995              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)71       1.13.4.1  src/bos/kernel/sys/POWER/context.h, sysproc, bos53V, v2009_13A8 3/25/09 16:33:11 */
/*
 *   COMPONENT_NAME: SYSPROC
 *
 *   FUNCTIONS: 
 *
 *   ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1995
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */


#ifndef	_H_CONTEXT
#define	_H_CONTEXT

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#include <sys/m_param.h>
#include <sys/mstsave.h>
#ifdef __cplusplus
extern "C" {
#endif

/* define return values for exception handlers */
#define _EXCONTINUE	0
#define	_EXRETURN	1
#define	_EXRESUME	2

/* define exception type values; negative values are user defined */
#define	_EXPGIO		0
#define _EXTRAP		1
#define	_EXIO		2
#define _EXDLOK		3
#define _EXSIG		4

/*
 * User and kernel declaration for stack_t structure
 * 64bit kernel need to use the "32bit size" for 32bit process.
 * For 64bit process, the kernel (in the 2 modes) use stack64_t.
 * stack_t structure used in sigaltstack() system call.
 */
typedef struct {
#ifdef __64BIT_KERNEL
	__ptr32 ss_sp;		/* stack base or pointer */
	uint_t ss_size;		/* stack size */
#else /* __64BIT_KERNEL */
	void  *ss_sp;		/* stack base or pointer */
	size_t ss_size;		/* stack size */
#endif /* __64BIT_KERNEL */

	int    ss_flags;	/* yup, flags go here */

	int    __pad[4];	/* rfu */

} stack_t;

#ifdef _ALL_SOURCE 
#if defined(_KERNSYS) || defined(_LONG_LONG)
/*
 * Kernel declaration for stack_t for 64-bit process. this assumes
 * int is 4-bytes. 32-bit and 64-bit API both use the sigstack above.
 */
typedef struct {
        unsigned long long ss_sp;       /* stack base or pointer */
        unsigned long long ss_size;     /* stack size */
        int                ss_flags;    /* yup, flags go here */
        int                __pad[4];    /* rfu */
} stack64_t;
#endif /* _KERNSYS or _LONG_LONG */

/*
 * 32-bit size invariant stack_t structure for use by 64-bit debuggers
 */
typedef struct {
	__ptr32 ss_sp;		/* stack base or pointer */
	uint_t ss_size;		/* stack size */
	int    ss_flags;	/* yup, flags go here */

	int    __pad[4];	/* rfu */

} stack32_t;
#endif /* _ALL_SOURCE */

/*
 * XPG4.2 requires structures and structure elements to be defined such 
 * that they do not pollute the namespace.  _ALL_SOURCE contains the 
 * kernel version, while not _ALL_SOURCE contains the sanitized versions.
 */

#ifdef _ALL_SOURCE /* { */

#define EXCONTINUE	_EXCONTINUE
#define	EXRETURN	_EXRETURN
#define	EXRESUME	_EXRESUME
#define	EXPGIO		_EXPGIO
#define EXTRAP		_EXTRAP
#define	EXIO		_EXIO
#define EXDLOK		_EXDLOK
#define EXSIG		_EXSIG

#define jmpbuf          __jmpbuf
#define context64       __context64

/* 
 * Machine status for 64-bit process.
 * Note that this structure mimics the layout of mstsave64 up thru
 * the "except" field, and bcopy is used to initialize this much at once.
 * (The fpscr and fpscrx words correspond to the asr doubleword in mstsave64).
 */
#if defined(_LONG_LONG)
struct __context64 {
	unsigned long long	gpr[_NGPRS]; 	/* 64-bit gprs */
	unsigned long long	msr;		/* msr */
	unsigned long long	iar;		/* iar */
	unsigned long long	lr;		/* LR */
	unsigned long long	ctr;		/* CTR */
	unsigned int		cr;		/* CR */
	unsigned int		xer;		/* XER */
	unsigned int		fpscr;		/* floating pt status reg */
	unsigned int		fpscrx;		/* software ext to fpscr */
        unsigned long long      except[1];      /* exception address    */
	double  		fpr[_NFPRS];	/* floating pt regs 	*/
	char			fpeu;		/* floating pt ever used */
	char			fpinfo;		/* floating pt info	*/
	char			fpscr24_31;	/* bits 24-31 of 64-bit FPSCR */
        char                    pad[1];
        int                     excp_type;      /* exception type       */
};


#else /* _LONG_LONG */

#ifdef __64BIT__
struct __context64 {
	unsigned long		gpr[_NGPRS]; 	/* 64-bit gprs */
	unsigned long		msr;		/* msr */
	unsigned long		iar;		/* iar */
	unsigned long		lr;		/* LR */
	unsigned long		ctr;		/* CTR */
	unsigned int		cr;		/* CR */
	unsigned int		xer;		/* XER */
	unsigned int		fpscr;		/* floating pt status reg */
	unsigned int		fpscrx;		/* software ext to fpscr */
        unsigned long		except[1];      /* exception address    */
	double  		fpr[_NFPRS];	/* floating pt regs 	*/
	char			fpeu;		/* floating pt ever used */
	char			fpinfo;		/* floating pt info	*/
	char			fpscr24_31;	/* bits 24-31 of 64-bit FPSCR */
        char                    pad[1];
        int                     excp_type;      /* exception type       */
};
#endif /* __64BIT__ */


#endif /* _LONG_LONG */


#if defined(_LONG_LONG) || defined(__64BIT__)
/* 
 * Kernel declaration of sigcontext for 64-bit process. this assumes 
 * int is 4-bytes. 32-bit and 64-bit API both use the sigcontext above.
 * with sigset_t for 64-bits defined as two ints.
 */
struct sigcontext64 {
	int  		   sc_onstack;	/* sigstack state to restore */
	sigset64_t	sc_mask;	/* signal mask to restore */
	int 		   sc_uerror;	/* u_error to restore */
	struct __context64 sc_context;	/* 64-bit state 	*/
};

/* Offsets of some fields  in sigcontext64 */
#define OFF_FPSCR   ((uint) &((struct sigcontext64 *)0)->sc_context.fpscr)
#define OFF_FPSCRX  ((uint) &((struct sigcontext64 *)0)->sc_context.fpscrx)
#define OFF_FPR     ((uint) &((struct sigcontext64 *)0)->sc_context.fpr[0])
#define OFF_FPINFO  ((uint) &((struct sigcontext64 *)0)->sc_context.fpinfo)

/* offset to struct context64 from beginning of sigcontext
 */
#define OFF_CONT64 ((uint) &((struct sigcontext64 *)0)->sc_context)
#define OFF_CONT   ((uint) &((struct sigcontext *)0)->sc_jmpbuf)

#endif /* _LONG_LONG || __64BIT__*/

#else /* !_ALL_SOURCE  } { */
 
/*
 * Machine status for 64-bit process.
 * Note that this structure mimics the layout of mstsave64 up thru
 * the "except" field, and bcopy is used to initialize this much at once.
 * (The fpscr and fpscrx words correspond to the asr doubleword in mstsave64).
 *
 * For standards compliance, we are not allowed to use the long long data
 * type.  Since this structure is only meant to correctly define the size
 * and alignment of a context structure within jmpbuf within sigcontext,
 * we can satisfy the typical 64 bit environment by defining gpr, msr, iar,
 * lr, ctr, and except[] with unsigned long instead.  We won't generate the
 * structure at all in 32-bit compilation mode, since there is no way to
 * guarantee doubleword alignment without long long.  Therefore, anyone
 * who needs this structure in 32-bit mode MUST compile with _ALL_SOURCE.
 * Note that ordinary applications pick up __mstsave instead of __context64
 * in 32-bit mode.
 */
#ifdef __64BIT__
struct __context64 {
        unsigned long           __gpr[_NGPRS];    /* 64-bit gprs */
        unsigned long           __msr;            /* msr */
        unsigned long           __iar;            /* iar */
        unsigned long           __lr;             /* LR */
        unsigned long           __ctr;            /* CTR */
        unsigned int            __cr;             /* CR */
        unsigned int            __xer;            /* XER */
        unsigned int            __fpscr;          /* floating pt status reg */
        unsigned int            __fpscrx;         /* software ext to fpscr */
        unsigned long           __except[1];      /* exception address    */
        double                  __fpr[_NFPRS];    /* floating pt regs     */
        char                    __fpeu;           /* floating pt ever used */
        char                    __fpinfo;         /* floating pt info     */
	char			__fpscr24_31;	  /* 24-31 of 64-bit FPSCR */
        char                    __pad[1];
        int                     __excp_type;      /* exception type       */
};

/*
 * Kernel declaration of sigcontext for 64-bit process. this assumes
 * int is 4-bytes. 32-bit and 64-bit API both use the sigcontext above.
 * with sigset_t for 64-bits defined as two ints.
 */
struct __sigcontext64 {
	int		   __sc_onstack;  /* sigstack state to restore */
	sigset64_t	__sc_mask;	/* signal mask to restore */
	int		   __sc_uerror;   /* u_error to restore */
	struct __context64 __sc_context;  /* 64-bit state	 */
};
#endif /* __64BIT__ */

#endif /* _ALL_SOURCE  } */


/*
 * VMX machine state.  Care must be taken to align this state on 
 * 16-byte boundaries if used for direct load/store with vector registers
 * Single declaration below works for 32-bit or 64-bit, _ALL_SOURCE or not
 */
typedef struct {
	unsigned int __v[4];
} __vmxreg_t;

typedef struct __vmx_context {
	__vmxreg_t 	__vr[32];	/* vector registers               */
	unsigned int	__pad1[3];	/* reserved, must be set to 0     */
	unsigned int	__vscr;		/* vector status and control reg  */
	unsigned int	__vrsave;	/* vrsave special purpose reg     */
	unsigned int	__pad2[3];	/* reserved, must be set to 0     */	
} __vmx_context_t;

/*
 * Extended context structure.  This is used by extended context
 * APIs.  If the legacy context (mstsave for 32-bit, __context64 for 64-bit)
 * "msr" field has the __EXTCTX bit set, then there is an associated
 * extended context structure for that context.
 * Single declaration below works for 32-bit or 64-bit, _ALL_SOURCE or not
 */

#define __EXTCTX	0x2000000	/* if this bit is set in the        */
					/* legacy context "msr" field,      */
					/* then there is an associated      */
					/* extended context available 	    */
					/* this bit coincides with          */
					/* the MSR:VMX bit (38) by design   */
#define __EXTCTX_MAGIC	0x45435458	/* extended context valid marker    */

/*
 * Extended context flags.  Can be used to control redefinitions of reserved
 * space, future extensions, and validity of content.
 */
#define __EXTCTX_VMX	0x00000001	/* extctx contains VMX state        */
#define __EXTCTX_UKEYS	0x00000002	/* extctx contains user-key state   */

/* Size of extended context reserved space.  Entire 
 * extended context is 4K
 */
#define __EXTCTX_RSV	(4096 - sizeof(__vmx_context_t) - (7 * sizeof(int)))

typedef struct __extctx {
	unsigned int	__flags;	/* extended context flags           */
	unsigned int	__rsvd1[3];	/* maintain 16-byte alignment       */
	union {
	    __vmx_context_t	__vmx;	/* VMX machine state                */
	} __u1;

	unsigned int	__ukeys[2];	/* Active user-key-set		    */
					/* Must be 8-byte aligned 	    */

	char	__reserved[__EXTCTX_RSV];/* reserved for future use         */
					 /* must be set to 0, and be        */
					 /* included in structure copies    */
	int		__extctx_magic;  /* marker to ensure integrity      */
					 /* of extended context             */
					 /* Set to __EXTCTX_MAGIC           */
	/* Total size of extended context is 4K */
} __extctx_t;

#define __vmx	__u1.__vmx


/* 
 * struct jmpbuf is part of the sigcontext structure. a different
 * structure is needed for 32 and 64 bit programs.
 */
#ifndef __64BIT__
struct	__jmpbuf {
#ifdef _ALL_SOURCE
	struct	mstsave jmp_context;
#else /* _ALL_SOURCE */
	struct	__mstsave __jmp_context;
#endif /* _ALL_SOURCE */
}; 

#else
struct	__jmpbuf {
#ifdef _ALL_SOURCE

#if defined(__64BIT_KERNEL) && defined(_KERNEL)
	/*
	 * __64BIT_KERNEL is used here to compile v_power_64.c with 
	 * -D_32KER_64VMM in 64bit kernel, jmpbuf is always relative 
	 * to a 32 bit process. 
	 */
	struct	mstsave32 jmp_context;
#else 
	struct	__context64 jmp_context;
#endif /* __64BIT_KERNEL */

#else /* _ALL_SOURCE */
	struct	__context64 __jmp_context;
#endif /* _ALL_SOURCE */
}; 
#endif  /* __64BIT__ */

#ifdef _ALL_SOURCE
/* 
 *   * 32-bit size invariant __jmpbuf structure for use by 64-bit debuggers
 */
struct	__jmpbuf32 {
	struct	mstsave32 jmp_context;
}; 
#endif

/* 
 * 'sigcontext' is not allowed in the SPEC1170 namespace, but
 * its size is needed for MINSIGSTKSZ.  This template is defined
 * for use where 'sigcontext' may be needed.
 */
struct	__sigcontext {
#ifdef _ALL_SOURCE
	int		sc_onstack;	/* sigstack state to restore */
#ifdef __64BIT_KERNEL
	sigset32_t	sc_mask;	/* signal mask to restore */
#else
	sigset_t	sc_mask;	/* signal mask to restore */
#endif
	int		sc_uerror;	/* u_error to restore */
	struct __jmpbuf sc_jmpbuf;	/* process context to restore */
#else /* _ALL_SOURCE */
	int		__sc_onstack;	/* sigstack state to restore */
#ifdef __64BIT_KERNEL
	sigset32_t	__sc_mask;	/* signal mask to restore */
#else
	sigset_t	__sc_mask;	/* signal mask to restore */
#endif
	int		__sc_uerror;	/* u_error to restore */
	struct __jmpbuf __sc_jmpbuf;	/* process context to restore */
#endif /* _ALL_SOURCE */
};


/* 
 * User context structure
 * The user context structure has the same layout as a
 * sigcontext structure until the uc_link structure, which
 * follows the sigcontext structure. 
 */
typedef struct __jmpbuf   mcontext_t;

typedef struct ucontext_t {
	int	    __sc_onstack; /* sigstack state to restore */
#ifdef __64BIT_KERNEL
        sigset32_t    uc_sigmask;   /* the set of signals that are blocked when
				     * this context is active */
#else
        sigset_t    uc_sigmask;   /* the set of signals that are blocked when
				   * this context is active */
#endif
        int	    __sc_uerror;  /* u_error to restore */
	mcontext_t  uc_mcontext;  /* machine-specific image of saved context */
#ifdef __64BIT_KERNEL
	__ptr32  uc_link;	  /* keep the same size in 64bit kernel */
#else /* __64BIT_KERNEL */
	struct ucontext_t *uc_link;/* context resumed after this one returns */
#endif /* __64BIT_KERNEL */

	stack_t     uc_stack;     /* stack used by context */
#ifdef __64BIT_KERNEL
	__ptr32	    __extctx;	  /* address of extended context (32-bit view)*/
#else /* __64BIT_KERNEL */
	__extctx_t  *__extctx;	  /* address of extended context */
#endif /* __64BIT_KERNEL */

	int	__extctx_magic;   /* marker to ensure integrity of    
				   * extended context pointer. Set to 
				   * __EXTCTX_MAGIC if extctx present */
#ifdef __64BIT__
	int	    __pad[1];	  /* rfu */
#else /* __64BIT__ */
	int	    __pad[2];	  /* rfu */
#endif /* __64BIT__ */
#if defined(__EXTABI__) || defined(__AIXEXTABI)
	__extctx_t   __x;         /* reserve space for extended ABI context */
				  /* always reference through __extctx ptr */	
				  /* since the extended context isn't      */
				  /* always embedded with in the ucontext  */
#endif /* __EXTABI__ || __AIXEXTABI */
} ucontext_t;

#ifdef _ALL_SOURCE
/* 32-bit size-invariant structure for 64-bit userspace */
typedef struct __jmpbuf32   mcontext32_t;

typedef struct ucontext32_t {
	int	    __sc_onstack; /* sigstack state to restore */
        sigset32_t    uc_sigmask;   /* the set of signals that are blocked when
				     * this context is active */
        int	    __sc_uerror;  /* u_error to restore */
	mcontext32_t uc_mcontext; /* machine-specific image of saved context */
	__ptr32  uc_link;	  /* keep the same size in 64bit kernel */

	stack32_t     uc_stack;   /* stack used by context */
	__ptr32	    __extctx;	  /* address of extended context (32-bit view)*/

	int	__extctx_magic;   /* marker to ensure integrity of    
				   * extended context pointer. Set to 
				   * __EXTCTX_MAGIC if extctx present */
	int	    __pad[2];	  /* rfu */
#if defined(__EXTABI__) || defined(__AIXEXTABI)
	__extctx_t   __x;         /* reserve space for extended ABI context */
				  /* always reference through __extctx ptr */	
				  /* since the extended context isn't      */
				  /* always embedded with in the ucontext  */
#endif /* __EXTABI__ || __AIXEXTABI */
} ucontext32_t;
#endif /* _ALL_SOURCE */

#ifdef __cplusplus
}
#endif

#endif /* _H_CONTEXT */
