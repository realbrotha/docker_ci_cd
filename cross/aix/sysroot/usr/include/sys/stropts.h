/* @(#)41       1.23  src/bos/kernel/sys/stropts.h, sysxpse, bos530 12/17/03 16:39:18 */
/*
 * COMPONENT_NAME: SYSXPSE - STREAMS framework
 * 
 * ORIGINS: 63, 71, 83
 * 
 */
/*
 * LEVEL 1, 5 Years Bull Confidential Information
 */
/*
 * (c) Copyright 1990, 1991, 1992 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */
/*
 * OSF/1 1.1
 */
/*
 *   Copyright (c) 1990, 1991  Mentat Inc.
 */

#ifndef	_STROPTS_
#define	_STROPTS_

#include <standards.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _ALL_SOURCE
#include <sys/ioctl.h>
#endif

#ifndef _IO
/* 
 * Important note:
 *	We can't include ioctl.h here because of SPEC1170 requirements.
 *	So, define all IO related macros here same as ioctl.h.  If the
 *	ioctl.h changes for IO related macros, then make sure and 
 *	incorporate same changes here.  
*/
/*
 * Ioctl's have the command encoded in the lower word,
 * and the size of any in or out parameters in the upper
 * word.  The high 2 bits of the upper word are used
 * to encode the in/out status of the parameter; for now
 * we restrict parameters to at most 128 bytes.
 */
#define _IOCPARM_MASK    0x7f            /* parameters must be < 128 bytes */
#define _IOC_VOID        0x20000000      /* no parameters */
#define _IOC_OUT         0x40000000      /* copy out parameters */
#define _IOC_IN          0x80000000      /* copy in parameters */
#define _IOC_INOUT       (_IOC_IN|_IOC_OUT)
/* the 0x20000000 is so we can distinguish new ioctl's from old */
#define _IO(x,y)        (_IOC_VOID|(x<<8)|y)
#define _IOR(x,y,t)     (_IOC_OUT|((sizeof(t)&_IOCPARM_MASK)<<16)|(x<<8)|y)
#define _IOW(x,y,t)     (_IOC_IN|((sizeof(t)&_IOCPARM_MASK)<<16)|(x<<8)|y)
/* this should be _IORW, but stdio got there first */
#define _IOWR(x,y,t)    (_IOC_INOUT|((sizeof(t)&_IOCPARM_MASK)<<16)|(x<<8)|y)

#ifdef _ALL_SOURCE
#define IOCPARM_MASK	_IOCPARM_MASK
#define IOC_VOID	_IOC_VOID
#define IOC_OUT		_IOC_OUT
#define IOC_IN		_IOC_IN
#define IOC_INOUT	_IOC_INOUT
#endif /* _ALL_SOURCE */

#endif /* _IO */

#ifndef _T_SCALAR_DEF
#ifdef __64BIT__
typedef signed int      t_scalar_t;
typedef unsigned int    t_uscalar_t;
#else
typedef signed long     t_scalar_t;
typedef unsigned long   t_uscalar_t;
#endif /* __64BIT__ */
#define _T_SCALAR_DEF
#endif

# if _XOPEN_SOURCE_EXTENDED==1

/* ioctl command values */

#define	I_NREAD		_IO('S',1)	/* get the number of bytes in 1st msg */
#define	I_PUSH		_IO('S',2)	/* push module just below stream head */
#define	I_POP		_IO('S',3)	/* pop module below stream head */
#define	I_LOOK		_IO('S',4)	/* get name of first stream module */
#define	I_FLUSH		_IO('S',5)	/* flush all input and/or output q's */
#define	I_SRDOPT	_IO('S',6)	/* set the read mode */
#define	I_GRDOPT	_IO('S',7)	/* get the current read mode */
#define	I_STR		_IO('S',8)	/* create an internal ioctl message */
#define	I_SETSIG	_IO('S',9)	/* request SIGPOLL signal on events */
#define	I_GETSIG	_IO('S',10)	/* query the registered events */
#define	I_FIND		_IO('S',11)	/* check for module in stream */
#define	I_LINK		_IO('S',12)	/* connect stream under mux fd */
#define	I_UNLINK	_IO('S',13)	/* disconnect two streams */
#define I_ISASTREAM     _IO('S',14)	/* identifies as stream/pipe/fifo */
#define	I_PEEK		_IO('S',15)	/* peek at data on read queue */
#define	I_FDINSERT	_IO('S',16)	/* create a msg and send downstream */
#define	I_SENDFD	_IO('S',17)	/* send fd to a connected pipe stream */
#define	I_RECVFD	_IO('S',18)	/* retrieve a file descriptor */
#define	I_FLUSHBAND	_IO('S',19)	/* flush an input and/or output band */
#define	I_SWROPT	_IO('S',20)	/* set the write mode */
#define	I_GWROPT	_IO('S',21)	/* get the current write mode */
#define	I_LIST		_IO('S',22)	/* get list of all modules on stream */
#define	I_ATMARK	_IO('S',23)	/* is next message "marked" */
#define	I_CKBAND	_IO('S',24)	/* check for a message on a band */
#define	I_GETBAND	_IO('S',25)	/* get band of next msg to be read */
#define	I_CANPUT	_IO('S',26)	/* can message be passed on a stream */
#define	I_SETCLTIME	_IO('S',27)	/* set the close timeout wait */
#define	I_GETCLTIME	_IO('S',28)	/* get the current close timeout wait */
#define	I_PLINK		_IO('S',29)	/* connect a permanent link */
#define	I_PUNLINK	_IO('S',30)	/* disconnect a permanent link */

/* priority message request on putmsg() or strpeek */
#define	RS_HIPRI	0x1

/* flags for getpmsg and putpmsg */
#define	MSG_HIPRI	RS_HIPRI
#define	MSG_BAND	0x2		/* get message from a particular band */
#define	MSG_ANY		0x4		/* get message from any band */

/* return values from getmsg(), 0 indicates all ok */
#define	MORECTL		0x1	/* more control info available */
#define	MOREDATA	0x2	/* more data available */

#ifndef FMNAMESZ
#define FMNAMESZ	8	/* maximum length of a module or device name */
#endif

/* flush requests */
#define	FLUSHR		0x1		/* Flush the read queue */
#define	FLUSHW		0x2		/* Flush the write queue */
#define	FLUSHRW		(FLUSHW|FLUSHR)	/* Flush both */
#define	FLUSHLOW	0x8		/* Flush only low priority messages */
#define	FLUSHBAND	0x40		/* Flush a particular band */

/* signal event masks */
#define	S_INPUT		0x1	/* A non-M_PCPROTO message has arrived */
#define	S_HIPRI		0x2	/* A M_PCPROTO message is available */
#define	S_OUTPUT	0x4	/* The write queue is no longer full */
#define	S_MSG		0x8	/* A signal message at front of read queue */
#define	S_RDNORM	0x10	/* A non-priority message is available */
#define	S_RDBAND	0x20	/* A banded messsage is available */
#define	S_WRNORM	0x40	/* Same as S_OUTPUT */
#define	S_WRBAND	0x80	/* A priority band exists and is writable */
#define	S_ERROR		0x100	/* Error message has arrived */
#define	S_HANGUP	0x200	/* Hangup message has arrived */
#define	S_BANDURG	0x400	/* Use SIGURG vs SIGPOLL on S_RDBAND signals */

/* flags for I_ATMARK */
#define	ANYMARK		0x1		/* Check if message is marked */
#define	LASTMARK	0x2		/* is this the only message marked */


/* read mode bits for I_S|GRDOPT; choose one of the following */
#define	RNORM		0x01	/* byte-stream mode, default */
#define	RMSGD		0x02	/* message-discard mode */
#define	RMSGN		0x04	/* message-nondiscard mode */

/* More read modes, these are bitwise or'ed with the modes above */
#define	RPROTNORM	0x10	/* Normal handling of M_(PC)PROTO messages */
#define	RPROTDIS	0x20	/* Discard M_(PC)PROTO message blocks */
#define	RPROTDAT	0x40	/* Convert M_(PC)PROTO mblks into M_DATA */

/* write modes for I_S|GWROPT */
#define	SNDZERO		0x1	/* Allow zero-length message for 0 byte write */

#define	MUXID_ALL	-1	/* all lower streams for I_UNLINK/I_PUNLINK */

/* I_FLUSHBAND */
struct bandinfo {
	unsigned char	bi_pri;		/* Band to flush */
	int		bi_flag;	/* One of the above flush requests */
};

struct	strbuf {
	int	maxlen;		/* max buffer length */
	int	len;		/* length of data */
	char	* buf;		/* pointer to buffer */
};

/* structure of ioctl data on I_FDINSERT */
struct	strfdinsert {
	struct strbuf	ctlbuf;
	struct strbuf	databuf;
#if _XOPEN_SOURCE>=500
	t_uscalar_t	flags;	/* type of message, 0 or RS_HIPRI */
#else
	t_scalar_t	flags;	/* type of message, 0 or RS_HIPRI */
#endif
	int		fildes;	/* fd of other stream */
	int		offset;	/* where to put other stream read qp */
};

/* I_LIST structures */
struct str_mlist {
#undef	l_name		/* XXX puke: user.h indirectly #includes loader.h */
	char	l_name[FMNAMESZ + 1];
};

struct str_list {
	int	sl_nmods;		/* # of modules in sl_modlist array */
	struct str_mlist * sl_modlist;
};

/* I_PEEK structure */
struct	strpeek {
	struct strbuf	ctlbuf;
	struct strbuf	databuf;
#if _XOPEN_SOURCE>=500
	t_uscalar_t	flags;	/* if RS_HIPRI, get priority messages only */
#else
	t_scalar_t	flags;	/* if RS_HIPRI, get priority messages only */
#endif
};

/* structure of ioctl data on I_RECVFD */
struct	strrecvfd {
	int		fd;	/* new file descriptor */
	ushort_t	__uid;
	ushort_t	__gid;
	uid_t		uid;	/* user id of sending stream */
	gid_t		gid;
};

/* structure of ioctl data on I_STR */
struct	strioctl {
	int	ic_cmd;		/* downstream command */
	int	ic_timout;	/* ACK/NAK timeout */
	int	ic_len;		/* length of data arg */
	char	* ic_dp;	/* ptr to data arg */
};

#ifdef _NO_PROTO
int	isastream();
int	getmsg();
int	getpmsg();
int	ioctl();
int	putmsg();
int	putpmsg();
int	fattach();
int	fdetach();      
#else /* _NO_PROTO */
int	isastream(int);
int	getmsg(int, struct strbuf *, struct strbuf *, int *);
int	getpmsg(int, struct strbuf *, struct strbuf *, int *, int *);
int	ioctl(int, int, ...);
int	putmsg(int, const struct strbuf *, const struct strbuf *, int);
int	putpmsg(int, const struct strbuf *, const struct strbuf *, int, int);
int	fattach(int, const char *);
int	fdetach(const char *);      
#endif /* _NO_PROTO */

#endif /*_XOPEN_EXTENDED_SOURCE */

#ifdef	_ALL_SOURCE

#define	RFILL		0x08	/* fill read buffer mode (PSE private) */
#define RPROTCOMPRESS   0x80    /* Compress M_DATA if messages allow */

#ifndef SIGPOLL
#define	SIGPOLL	SIGIO			/* another type of I/O event */
#endif /* SIGPOLL */

/* ioctl values needed on non-SYS V systems */
/* XXX functionality unused - remove from system */
#define	I_GETMSG	_IO('S',40)	/* getmsg() system call */
#define	I_PUTMSG	_IO('S',41)	/* putmsg() system call */
#define	I_POLL		_IO('S',42)	/* poll() system call */
#define	I_SETDELAY	_IO('S',43)	/* set blocking status */
#define	I_GETDELAY	_IO('S',44)	/* get blocking status */
#define	I_RUN_QUEUES	_IO('S',45)	/* sacrifice for the greater good */
#define	I_GETPMSG	_IO('S',46)	/* getpmsg() system call */
#define	I_PUTPMSG	_IO('S',47)	/* putpmsg() system call */
#define	I_AUTOPUSH	_IO('S',48)	/* for systems that cannot do the autopush in open */
#define	I_PIPE		_IO('S',49)	/* pipe() system call - not implemented */
#define I_FIFO          _IO('S',50)	/* convert a stream into a FIFO */

#define I_STR_ATTR      _IO('S',60) /* SEC_BASE attribute versions of above. */
#define I_PEEK_ATTR     _IO('S',61) /* ... */
#define I_FDINSERT_ATTR _IO('S',62)
#define I_SENDFD_ATTR   _IO('S',63)
#define I_RECVFD_ATTR   _IO('S',64)
#define I_GETMSG_ATTR   _IO('S',65)
#define I_PUTMSG_ATTR   _IO('S',66)
#define I_GETPMSG_ATTR  _IO('S',67)
#define I_PUTPMSG_ATTR  _IO('S',68)

/* structure for getpmsg and putpmsg */
struct	strpmsg {
	struct strbuf	ctlbuf;
	struct strbuf	databuf;
	int		band;
	t_scalar_t	flags;
};

#ifdef SEC_BASE

/* structure of ioctl data for I_FDINSERT_ATTR */
struct strfdinsert_attr {
        struct strbuf   ctlbuf;
        struct strbuf   databuf;
        t_uscalar_t	flags;  /* type of message, 0 or RS_HIPRI */
        int             fildes; /* fd of other stream */
        int             offset; /* where to put other stream read qp */
        struct strbuf   attrbuf;
};

/* structure of ioctl data for I_PEEK_ATTR */
struct strpeek_attr {
        struct strbuf   ctlbuf;
        struct strbuf   databuf;
        t_uscalar_t     flags;  /* if RS_HIPRI, get priority messages only */
        struct strbuf   attrbuf;
};

/* structure for getpmsg_attr and putpmsg_attr */
struct  strpmsg_attr {
        struct strbuf   ctlbuf;
        struct strbuf   databuf;
        int             band;
        t_scalar_t      flags;
        struct strbuf   attrbuf;
};

/* structure of ioctl data for I_RECVFD_ATTR */
struct strrecvfd_attr {
        int             fd;     /* new file descriptor */
        uid_t           uid;    /* user id of sending stream */
        gid_t           gid;
        struct strbuf   attrbuf;
};

/* structure of ioctl data for I_SENDFD_ATTR */
struct strsendfd_attr {
        int             fd;     /* file descriptor to be passed */
        struct strbuf   attrbuf;
};

/* structure of ioctl data for I_STR_ATTR */
struct strioctl_attr {
        int     ic_cmd;         /* downstream command */
        int     ic_timout;      /* ACK/NAK timeout */
        int     ic_len;         /* length of data arg */
        char *  ic_dp;          /* ptr to data arg */
        struct strbuf   attrbuf;
};

#endif /* SEC_BASE */

/* destined for the junk pile - do not use */
#define	stream_open	open
#define	stream_close	close
#define	stream_read	read
#define	stream_write	write
#define	stream_ioctl	ioctl

#endif  /* _ALL_SOURCE */ 

#ifdef __cplusplus
}
#endif

#endif	/*_STROPTS_*/
