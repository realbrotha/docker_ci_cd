/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/kernel/sys/aio.h 1.21.1.10                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1991,2008              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
 /* @(#)55       1.21.1.10  src/bos/kernel/sys/aio.h, sysxaio, bos53Q, q2008_13B1 2/29/08 18:14:22 */
/*
 * COMPONENT_NAME: (SYSXAIO) Asynchronous I/O
 *
 * FUNCTIONS: aio.h
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1991
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
#ifndef _H_AIO
#define _H_AIO

#include <standards.h>
#include <sys/signal.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

#if _XOPEN_SOURCE>=500

#ifdef _ALL_SOURCE
#include <sys/errno.h>
#define EINPROG EINPROGRESS
#endif /* _ALL_SOURCE */

#ifdef _LARGE_FILES
typedef struct aiocb64 *aio_handle_t;
#else
typedef struct aiocb *aio_handle_t;
#endif /* _LARGE_FILES */

#ifdef _AIO_AIX_SOURCE
struct aiocb
{
	int		aio_whence;	/* lseek whence argument       */
	off_t		aio_offset;	/* lseek offset argument       */
	char	       *aio_buf;	/* Pointer to R/W buffer       */
	ssize_t		aio_return;	/* return code of i/o          */
	int		aio_errno;	/* Error number, or EINPROG    */
	size_t		aio_nbytes;	/* Number of bytes to r/w      */
	union {
		int	reqprio;	/* Not used		       */
		struct {		/* extended aiocb	       */
			int	version:8;	/* version number      */
			int	priority:8;	/* per io priority     */
			int	cache_hint:16;	/* cache hint	       */
		} ext;
	} aio_u1;
	struct osigevent aio_event;	/* Not used		       */
	int		aio_flag;	/* Checked for AIO_SIGNAL only */
	int		aio_iocpfd;	/* IOCP file descriptor        */
	aio_handle_t	aio_handle;	/* Pointer back to self	       */
#ifdef _KERNEL
	offset_t	aio_lloffset;
#else
#ifdef __64BIT__
	uint_t		aio_reserved[2];  /* Implementation reserved field */
#else
	uint_t		aio_reserved[3];  /* Implementation reserved field */
#endif /* __64BIT__ */
#endif /* _KERNEL */
	int		aio_pad[2]; 	 /* Implementation reserved field */
};
/* For source compat, formerly "File fp, used internally" but never used. */
#define aio_fp aio_iocpfd
#else /* !_AIO_AIX_SOURCE */
struct aiocb
{
	int		aio_lio_opcode; /* opcode for lio_listio (posix) */
	int		aio_fildes;     /* file descriptor (posix)     */
	int		aio_word1;      /* Implementation reserved field */ 	
	off_t		aio_offset;	/* lseek offset argument       */
	volatile void   *aio_buf;       /* Pointer to R/W buffer(posix)*/
	ssize_t		aio_return;	/* return code of i/o          */
	int		aio_errno;	/* Error number, or EINPROG    */
	size_t		aio_nbytes;	/* Number of bytes to r/w      */
	int		aio_reqprio;	/* Request priority 	       */
	struct sigevent aio_sigevent; 	/* signal number and value     */
	int		aio_word2;      /* Implementation reserved field */ 	
	int		aio_fp;		/* File fp, used internally    */
	aio_handle_t	aio_handle;	/* Pointer back to self	       */
#ifdef _KERNEL
	offset_t	aio_lloffset;
#else
#ifdef __64BIT__
	uint_t		aio_reserved[2];  /* Implementation reserved field */
#else
	uint_t		aio_reserved[3];  /* Implementation reserved field */
#endif /* __64BIT__ */
#endif /* _KERNEL */
#ifdef __64BIT__
	tid_t		aio_sigev_tid;	/* used internally for real time */
#else					/* thread generation             */
	tid_t		aio_sigev_tid;
	int		aio_pad;	/* implementation reserved field */
#endif	/* __64BIT__ */
};
#endif /* _AIO_AIX_SOURCE */

#if defined(_LARGE_FILES) || defined(_LARGE_FILE_API)
#ifdef _AIO_AIX_SOURCE
struct aiocb64
{
	int		aio_whence;	/* lseek whence argument       */
	long		aio_reserved1;  /* Implementation reserved field */
	char	        *aio_buf;	/* Pointer to R/W buffer       */
	ssize_t		aio_return;	/* return code of i/o          */
	int		aio_errno;	/* Error number, or EINPROG    */
	size_t		aio_nbytes;	/* Number of bytes to r/w      */
	union {
		int	reqprio;	/* Not used		       */
		struct {		/* extended aiocb	       */
			int	version:8;	/* version number      */
			int	priority:8;	/* per io priority     */
			int	cache_hint:16;	/* cache hint	       */
		} ext;
	} aio_u1;
	struct osigevent aio_event;	/* Not used		       */
	int		aio_flag;	/* Checked for AIO_SIGNAL only */
	int		aio_iocpfd;     /* IOCP file descriptor	       */
	aio_handle_t	aio_handle;	/* Pointer back to self	       */
#ifdef _LARGE_FILES
	off_t		aio_offset;	/* 64 bit offset		*/
#else
	off64_t		aio_offset;
#endif
	int		aio_pad[2];	/* Implementation reserved field */
};
#else /* ! _AIO_AIX_SOURCE */
struct aiocb64
{
	int		aio_lio_opcode; /* opcode for lio_listio (posix) */
	int		aio_fildes;     /* file descriptor (posix)     */
	int		aio_word1;	/* Implementation reserved field  */
	long		aio_reserved1;  /* Implementation reserved field */
	volatile void	*aio_buf;       /* Pointer to R/W buffer (posix)*/
	ssize_t		aio_return;	/* return code of i/o          */
	int		aio_errno;	/* Error number, or EINPROG    */
	size_t		aio_nbytes;	/* Number of bytes to r/w      */
	int		aio_reqprio;	/* Request priority            */
	struct sigevent aio_sigevent; 	/* signal number and value     */
	int		aio_word2;	/* Implementation reserved field */
	int	   	aio_fp;		/* File fp, used internally    */
	aio_handle_t	aio_handle;	/* Pointer back to self	       */
#ifdef _LARGE_FILES
	off_t		aio_offset;	/* 64 bit offset		*/
#else
	off64_t		aio_offset;
#endif
#ifdef __64BIT__
	tid_t		aio_sigev_tid;	/* used internally for real time */
#else					/* thread generation             */
	tid_t		aio_sigev_tid;
	int		aio_pad;	/* implementation reserved field */
#endif /* __64BIT__ */
};
#endif /* _AIO_AIX_SOURCE */
#endif /* _LARGE_FILES || _LARGE_FILE_API */ 

/*
 * bits in aio_flag field of aiocb struct
 */

#define AIO_EVENT	0x001		/* Event notification not implemented  */
#define AIO_SIGNAL	0x002

#ifdef _AIO_AIX_SOURCE
#define AIO_EXTENDED	0x004		/* extended aiocb structure	       */
#endif /* _AIO_AIX_SOURCE */

/*
 * return values from aio_cancel()
 */
#define AIO_CANCELED	0	/* all i/o requested was cancelled */
#define AIO_NOTCANCELED	1	/* some i/o could not be cancelled */
#define AIO_ALLDONE	2	/* all i/o was already completed   */

/*
 * Values for the cmd paramter to lio_listio.
 */
#define LIO_NOWAIT	0
#define LIO_WAIT	1
#define LIO_ASYNC	2  /* LIO Event notification not implemented */
#define LIO_ASIG	3  /* temporary replacement until Event notification */
#define	LIO_NOWAIT_AIOWAIT	4
/*
 * The LIO_NOWAIT_GMCS aix-only command specifies a performance
 * optimization for use only with i/o completion ports and the
 * GetMultipleCompletionStatus function.
 * This cmd inhibits asynchronous updating of the aiocb in user space,
 * requiring the caller to use the aio_return (byte count) and aio_errno
 * values provided after waiting with GetMultipleCompletionStatus.
 */
#ifdef _AIO_AIX_SOURCE
#define	LIO_NOWAIT_GMCS	5
#endif

/*
 * Values for lio_opcode
 */
#define LIO_NOP	 	0
#define	LIO_READ	1
#define	LIO_WRITE	2

#ifdef _AIO_AIX_SOURCE

/* Extended aiocb, aiocb64, liocb, and liocb64.  The aio_reqprio field
 * is not supported under _AIO_AIX_SOURCE, and has been overloaded to
 * contain extra fields.  The aio_priority and aio_cache_hint fields 
 * are only used if VALID_AIOCBX is true.  
 */
#define aio_reqprio	aio_u1.reqprio
#define aio_version	aio_u1.ext.version
#define aio_priority	aio_u1.ext.priority
#define aio_cache_hint	aio_u1.ext.cache_hint

#define AIOCBX_VERS1	1
#define AIOCBX_VERS2	2
#define AIOCBX_VERSION	AIOCBX_VERS2

#define VALID_AIOCBX(x)		(((x)->aio_flag & AIO_EXTENDED) && \
				 ((x)->aio_version > 0) && \
				 ((x)->aio_version <= AIOCBX_VERSION))

#else /* _AIO_AIX_SOURCE */

static ssize_t  aio_return(struct aiocb *__aiocbp)
{
	extern ssize_t _posix_aio_return(struct aiocb *);
	return _posix_aio_return(__aiocbp);
}
static int      aio_error(const struct aiocb *__aiocbp)
{
	extern int     _posix_aio_error(const struct aiocb *);
	return _posix_aio_error(__aiocbp);
}

#ifdef _LARGE_FILE_API
static ssize_t  aio_return64(struct aiocb64 *__aiocbp)
{
	extern ssize_t _posix_aio_return64(struct aiocb64 *);
	return _posix_aio_return64(__aiocbp);
}
static int      aio_error64(const struct aiocb64 *__aiocbp)
{
	extern int     _posix_aio_error64(const struct aiocb64 *);
	return _posix_aio_error64(__aiocbp);
}
#endif /* _LARGE_FILE_API */
#endif /* ! _AIO_AIX_SOURCE */

/* subroutine declarations
 */
#ifdef _NO_PROTO

int aio_read();
int aio_write();
int lio_listio();
int aio_cancel();
int aio_suspend();
#ifndef _AIO_AIX_SOURCE
int aio_fsync();
#endif

#else

#ifndef _AIO_AIX_SOURCE
static int      aio_read(struct aiocb *__aiocbp)
{
	extern int _posix_aio_read(struct aiocb *);
	return  _posix_aio_read(__aiocbp);
}

static int      aio_write(struct aiocb *__aiocbp)
{
        extern int _posix_aio_write(struct aiocb *);
        return _posix_aio_write(__aiocbp);
}

static int      lio_listio(int __mode, 
			  struct aiocb *__restrict__ const __list[__restrict__],
                          int __nent, struct sigevent *__restrict__ __sig)
{
	extern int      _posix_lio_listio(int ,
			  struct aiocb *__restrict__ const __list[__restrict__],
					   int,  struct sigevent *__restrict__);
	return _posix_lio_listio(__mode , __list, __nent, __sig);
}

static int      aio_cancel(int __fildes, struct aiocb *__aiocbp)
{
        extern int _posix_aio_cancel(int, struct aiocb *);
        return _posix_aio_cancel(__fildes,__aiocbp);
}

static	int	aio_suspend(const struct aiocb *const __list[],int __nent,
					const struct timespec *__timeout)
{
	extern int _posix_aio_suspend(const struct aiocb *const[],int,
                                                const struct timespec *);
	return _posix_aio_suspend(__list,__nent,__timeout);
}

static	int	aio_nwait(int __cnt, int __nwait,
				struct aiocb **__uaiocbpa)
{
	extern int _posix_aio_nwait(int, int, struct aiocb **);
	return _posix_aio_nwait(__cnt, __nwait, __uaiocbpa);
}

static  int     aio_nwait_timeout(int __cnt, int __nwait,
                                struct aiocb **__uaiocbpa, int __timeout)
{
        extern int _posix_aio_nwait_timeout(int, int, struct aiocb **, int);
        return _posix_aio_nwait_timeout(__cnt, __nwait, __uaiocbpa, __timeout);
}

static int aio_fsync(int __op , struct aiocb *__aiocbp)
{
	extern int _posix_aio_fsync(int, struct aiocb *);
	return _posix_aio_fsync(__op,__aiocbp);
}

#ifdef _LARGE_FILE_API

static	int	aio_read64(struct aiocb64 *__aiocbp)
{
	extern int _posix_aio_read64(struct aiocb64 *);
	return _posix_aio_read64(__aiocbp);
}

static	int	aio_write64(struct aiocb64 *__aiocbp)
{
	extern int _posix_aio_write64(struct aiocb64 *);
	return _posix_aio_write64(__aiocbp);
}

static	int	lio_listio64(int __mode, 
			struct aiocb64 *__restrict__ const __list[__restrict__],
				int __nent, struct sigevent *__restrict__ __sig)
{
	extern int   _posix_lio_listio64(int , 
		   	struct aiocb64 *__restrict__ const __list[__restrict__],
					    int, struct sigevent *__restrict__);
	return _posix_lio_listio64(__mode , __list, __nent, __sig);
}

static	int	aio_cancel64(int __fildes, struct aiocb64 *__aiocbp)
{
	extern int _posix_aio_cancel64(int, struct aiocb64 *);
	return _posix_aio_cancel64(__fildes,__aiocbp);
}

static  int     aio_suspend64(const struct aiocb64 *const __list[],int __nent,
					const struct timespec *__timeout)
{
	extern int _posix_aio_suspend64(const struct aiocb64 *const[],int,
						const struct timespec *);
	return _posix_aio_suspend64(__list,__nent,__timeout);
}

static	int	aio_nwait64(int __cnt, int __nwait,
				struct aiocb64 **__uaiocbpa)
{
	extern int _posix_aio_nwait64(int, int, struct aiocb64 **);
	return _posix_aio_nwait64(__cnt, __nwait, __uaiocbpa);
}

static  int     aio_nwait_timeout64(int __cnt, int __nwait,
                                struct aiocb64 **__uaiocbpa, int __timeout)
{
        extern int _posix_aio_nwait_timeout64(int, int, struct aiocb64 **, int);
        return _posix_aio_nwait_timeout64(__cnt,__nwait,__uaiocbpa,__timeout);
}

static	int aio_fsync64(int __op , struct aiocb64 *__aiocbp)
{
	extern int _posix_aio_fsync64(int, struct aiocb64 *);
	return _posix_aio_fsync64(__op,__aiocbp);
}

#endif  /*  _LARGE_FILE_API */
#endif /* ! _AIO_AIX_SOURCE */

#endif /* _NO_PROTO */
#endif /* _XOPEN_SOURCE>=500 */

#ifdef _ALL_SOURCE
#ifdef _AIO_AIX_SOURCE

struct liocb
{
	int		lio_opcode;	/* list member opcode	       */
	int		lio_fildes;	/* file descriptor	       */
	struct aiocb	lio_aiocb;	/* aiocb for request	       */
};


#if defined(_LARGE_FILES) || defined(_LARGE_FILE_API)
struct liocb64
{
	int		lio_opcode;	/* list member opcode	       */
	int		lio_fildes;	/* file descriptor	       */
	struct aiocb64	lio_aiocb;	/* aiocb for request	       */
};
#endif /* _LARGE_FILES || _LARGE_FILE_API */ 

int 	aio_read(int, struct aiocb *);
int 	aio_write(int, struct aiocb *);
int 	lio_listio(int, struct liocb *[], int, void *);
int 	aio_cancel(int, struct aiocb *);
int 	aio_suspend(int, struct aiocb *[]);
int	aio_nwait(int, int, struct aiocb **);
int     aio_nwait_timeout(int, int, struct aiocb **, int);
ssize_t	aio_return(struct aiocb *);
int 	aio_error(struct aiocb *);

#ifdef _LARGE_FILE_API
int 	aio_read64(int, struct aiocb64 *);
int 	aio_write64(int, struct aiocb64 *);
int 	lio_listio64(int, struct liocb64 *[], int, void *);
int 	aio_cancel64(int, struct aiocb64 *);
int 	aio_suspend64(int, struct aiocb64 *[]);
int	aio_nwait64(int, int, struct aiocb64 **);
int	aio_nwait_timeout64(int, int, struct aiocb64 **, int);
ssize_t	aio_return64(struct aiocb64 *);
int 	aio_error64(struct aiocb64 *);
#endif  /*  _LARGE_FILE_API */

#ifdef _LARGE_FILES
#define	liocb		liocb64
#endif

#endif /* _AIO_AIX_SOURCE */

#ifdef _LARGE_FILES
#define	aiocb			aiocb64
#define	aio_read		aio_read64
#define	aio_write		aio_write64
#define	aio_suspend		aio_suspend64
#define	aio_cancel		aio_cancel64
#define	lio_listio		lio_listio64
#define	aio_nwait		aio_nwait64
#define	aio_nwait_timeout	aio_nwait_timeout64
#ifndef _AIO_AIX_SOURCE
#define aio_fsync       	aio_fsync64
#define aio_return(h)   	aio_return64(h)
#define aio_error       	aio_error64
#endif /* ! _AIO_AIX_SOURCE */
#endif /* _LARGE_FILES */

#endif /* _ALL_SOURCE */
#ifdef __cplusplus
}
#endif
#endif /* _H_AIO */
