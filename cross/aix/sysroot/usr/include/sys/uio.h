/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53N src/bos/kernel/sys/uio.h 1.43                                   */
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
/* @(#)63     1.43  src/bos/kernel/sys/uio.h, sysios, bos53N, n2007_38A8 9/5/07 16:48:31 */

/*
 * COMPONENT_NAME: (SYSIOS) User I/O services header file
 *
 * FUNCTIONS: none
 *
 * ORIGINS: 26, 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1995
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	(#)uio.h	7.1 (Berkeley) 6/4/86
 */

#ifndef _H_UIO_
#define _H_UIO_

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


#include <strict_stdtypes.h>

#ifndef _H_TYPES
#include <sys/types.h>
#endif

#include <end_strict_stdtypes.h>

#if _XOPEN_SOURCE_EXTENDED==1
struct iovec {
#ifdef _KERNEL
	caddr_t iov_base;	/* base memory address			*/
#else
	void *iov_base;	/* base memory address			*/
#endif /* _KERNEL */
	size_t	iov_len;	/* length of transfer for this area	*/
};

#ifdef _NO_PROTO
extern ssize_t	readv();
extern ssize_t	writev();
#else
extern ssize_t	readv(int, const struct iovec *, int);
extern ssize_t 	writev(int, const struct iovec *, int);
#endif /* _NO_PROTO */
#endif /* _XOPEN_SOURCE_EXTENDED */

#ifdef _ALL_SOURCE
#ifdef __64BIT__
#ifdef _NO_PROTO
extern ssize_t	readvx();
extern ssize_t	writevx();
extern ssize_t	preadv();
extern ssize_t	pwritev();
#else
extern ssize_t	readvx(int, const struct iovec *, int, long);
extern ssize_t 	writevx(int, const struct iovec *, int, long);
extern ssize_t	preadv(int, const struct iovec *, int, offset_t);
extern ssize_t 	pwritev(int, const struct iovec *, int, offset_t);
#endif /* _NO_PROTO */
#endif /* __64BIT__ */

#include <sys/xmem.h>
struct uio {
	struct	iovec *uio_iov;	/* ptr to array of iovec structs	*/
	struct	xmem  *uio_xmem;/* ptr to array of xmem structs		*/
	int32long64_t  uio_iovcnt;/* #iovec elements remaining to process */
	int32long64_t  uio_iovdcnt;/* #iovec elements already processed	*/
#ifdef _LONG_LONG
	offset_t uio_offset;	/* byte offset in file/dev to read/write*/
#else /* _LONG_LONG */
#ifdef __64BIT__
	off_t	uio_offset; 	/* off_t offset for ANSI-C mode      */
#else
	int	uio_rsvd;	/* ANSI-C does not support long long */
	off_t	uio_offset; 	/* off_t offset for ANSI-C mode      */
#endif /* __64BIT__ */
#endif  /* _LONG_LONG */
	int32long64_t uio_resid;	/* #bytes left in data area	*/
	short	uio_segflg;	/* see segment flag value defines below */
	long	uio_fmode;	/* copy of file modes from open file struct */
};
typedef struct uio uio_t;

#ifndef __64BIT_KERNEL
/*
 * Control structure used by pinu/unpinu.  Head of list in U.U_pinu_block.
 */
struct pinu_block {
	struct pinu_block *next;	/* pointer to next block in chain    */
	int		seg_num;	/* segment number for this descripter*/
	int		pincount;	/* number of pages pinned in segment */
	struct xmem	xd;		/* cross-memory descripter	     */
};
#endif /* ! __64BIT_KERNEL */

#ifdef	_SUN
/* SUN -> 4.3 BSD difference */
#define uio_seg uio_segflg
#endif	/* SUN */

enum	uio_rw { UIO_READ, UIO_WRITE, UIO_READ_NO_MOVE, UIO_WRITE_NO_MOVE,
		 UIO_PWRITE };

/*
 * Segment flag values 
 */
#define UIO_USERSPACE	USER_ADSPACE	/* user address space */
#define UIO_SYSSPACE	SYS_ADSPACE	/* system address space */
#define UIO_USERISPACE	USERI_ADSPACE	/* user instruction address space */
#define UIO_XMEM	3		/* using cross mem descriptors	*/
#ifndef IOV_MAX
					/* Also Defined in sys/limits.h	     */
#define IOV_MAX		16		/* Maximum num of iov's on readv()   */
					/* or writev()			     */
#endif /* IOV_MAX */
#ifndef _KERNEL
#endif /* _KERNEL */

#ifdef _KERNEL
#ifndef _NO_PROTO

extern int	ureadc(
	int		c,
	struct uio	*uio);
/* arguments:
 *	int		c;		character to give to user
 *	struct uio	*uio;		user area description
 */

extern int	uwritec(
	struct uio	*uio);
/* arguments:
 *	struct uio	*uio;		user area description
 */

extern int	uiomove(
	caddr_t		cp,
	int32long64_t	n,
	enum uio_rw	rw,
	struct uio	*uio);
/* arguments:
 *	caddr_t		cp;		address of kernel buffer
 *	int32long64_t	n;		#bytes to transfer
 *	enum uio_rw	rw;		direction of xfer (read/write)
 *	struct uio	*uio;		user area description
 */

#ifndef __64BIT_KERNEL

extern int	pinu(
	caddr_t		base,
	int		len,
	short		segflg);
/* arguments:
 *	caddr_t		base;		address of first byte to pin
 *	int		len;		#bytes to pin
 *	short		segflg;		flag that specifies where data is
 */

extern int	unpinu(
	caddr_t		base,
	int		len,
	short		segflg);
/* arguments:
 *	caddr_t		base;		address of first byte to unpin
 *	int		len;		#bytes to unpin
 *	short		segflg;		flag that specifies where data is
 */
#endif /* ! __64BIT_KERNEL */

extern int	xmempin(
	caddr_t		base,
	int32long64_t	len,
	struct xmem	*xd);
/* arguments:
 *	caddr_t		base;		address of first byte to pin
 *	int32long64_t	len;		#bytes to pin
 *	struct xmem	*xd;		cross memory descripter
 */

extern int	xmemunpin(
	caddr_t		base,
	int32long64_t	len,
	struct xmem	*xd);
/* arguments:
 *	caddr_t		base;		address of first byte to unpin
 *	int32long64_t	len;		#bytes to unpin
 *	struct xmem	*xd;		cross memory descripter
 */

#else

extern int	ureadc();
/* arguments:
 *	int		c;		character to give to user
 *	struct uio	*uio;		user area description
 */

extern int	uwritec();
/* arguments:
 *	struct uio	*uio;		user area description
 */

extern int	uiomove();
/* arguments:
 *	caddr_t		cp;		address of kernel buffer
 *	int32long64_t	n;		#bytes to transfer
 *	enum uio_rw	rw;		direction of xfer (read/write)
 *	struct uio	*uio;		user area description
 */

#ifndef __64BIT_KERNEL
extern int	pinu();
/* arguments:
 *	caddr_t		base;		address of first byte to pin
 *	int		len;		#bytes to pin
 *	short		segflg;		specifies where data to pin is
 */

extern int	unpinu();
/* arguments:
 *	caddr_t		base;		address of first byte to unpin
 *	int		len;		#bytes to unpin
 *	short		segflg;		specifies where data to unpin is
 */
#endif /* ! __64BIT_KERNEL */

extern int	xmempin();
/* arguments:
 *	caddr_t		base;		address of first byte to pin
 *	int32long64_t	len;		#bytes to pin
 *	struct xmem	*xd;		cross memory descripter
 */

extern int	xmemunpin();
/* arguments:
 *	caddr_t		base;		address of first byte to unpin
 *	int32long64_t	len;		#bytes to unpin
 *	struct xmem	*xd;		cross memory descripter
 */

#endif /* not _NO_PROTO */

#ifndef __64BIT_KERNEL
/* 64bit prototypes
 */
int copyin64(unsigned long long src, char *  target, int nbytes);
int copyout64(char * src, unsigned long long target, int nbytes);
int copyinstr64(unsigned long long from, caddr_t to, uint max, uint *actual);
int fubyte64(unsigned long long addr64);
int fuword64(unsigned long long addr64);
int subyte64(unsigned long long addr64, uchar val);
int suword64(unsigned long long addr64, int val);
#else
#define copyin64(_a,_b,_c) copyin(_a,_b,_c)
#define copyout64(_a,_b,_c) copyout(_a,_b,_c)
#define copyinstr64(_a,_b,_c,_d) copyinstr(_a,_b,_c,_d)
#define fubyte64(_a) fubyte(_a)
#define fuword64(_a) fuword(_a)
#define subyte64(_a,_b) subyte(_a,_b)
#define suword64(_a,_b) suword(_a,_b)
#endif /* ! __64BIT_KERNEL */

#ifdef _KERNSYS
int uiomove_xproc(pid_t, ptr64, int32long64_t, enum uio_rw, struct uio *);
int kbufmove_xproc(pid_t, ptr64, int32long64_t, enum uio_rw, void *);
#endif

#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)

int uiomove_chksum(             /* move data plus TCP checksum */
        caddr_t        cp,      /* address of kernel buffer */
        int32long64_t  n,       /* #bytes to transfer */
        enum uio_rw    rw,      /* direction of xfer */
        struct uio     *uio,    /* user area description */
        uint           *sum);   /* pointer to checksum */

int uphysio(                    /* perform raw I/O for block DD */
         struct uio *uio,       /* description of buffer        */
         int    rw,             /* access mode:  read or write  */
         uint32long64_t   buf_cnt, /* degree of concurrency        */
         dev_t  dev,            /* device to read from/write to */
         int    (*strat)(),     /* ptr to I/O strategy routine  */
         int    (*mincnt)(),    /* device request check routine */
         void   *minparms);     /* parameters for mincnt        */

int fubyte(void  *);
int fuword(void *);
int subyte(void *, char);
int suword(void *, int);

#ifndef __64BIT_KERNEL
int copyin(void *, void *, uint);
int copyout(void *, void *, uint);
int copyinstr(void *, void *, uint, uint *);
#else
int copyin(void *, void *, size_t);
int copyout(void *, void *, size_t);
int copyinstr(void *, void *, size_t, size_t *);
#endif /* !__64BIT_KERNEL */

#endif /* (__64BIT_KERNEL) || (__FULL_PROTO) */

#endif /* _KERNEL */

#endif /* _ALL_SOURCE */

#ifdef __cplusplus
}
#endif

#endif /* _H_UIO_ */
