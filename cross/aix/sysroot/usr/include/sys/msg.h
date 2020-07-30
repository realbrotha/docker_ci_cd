/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/msg.h 1.20.1.22                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1987,2003          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)97       1.20.1.22  src/bos/kernel/sys/msg.h, sysipc, bos530 5/20/03 08:05:16 */
/*
 * COMPONENT_NAME: (SYSIPC) IPC Message Facility
 *
 * FUNCTIONS:
 *
 * ORIGINS: 3,27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1987, 1996
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 */

#ifndef _H_MSG
#define _H_MSG

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#ifndef _H_IPC
#include <sys/ipc.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _XOPEN_SOURCE

#ifndef _H_TYPES
#include <sys/types.h>
#endif
/*
 * The maximum message size is 4Mb.
 * The maximum number of bytes on a queue is 4Mb.
 * 
 */
typedef unsigned int    msgqnum_t;
typedef __ulong64_t     msglen_t;
typedef unsigned int    msglen32_t; /* size invariant 32-bit message length */
#if defined(__64BIT__) || defined(_LONG_LONG)
typedef uint64_t        msglen64_t; /* size invariant 64-bit message length */
#endif

/*
 *	Message Operation Flags.
 */

#define	MSG_NOERROR	010000	/* no error if big message */

#endif /* _XOPEN_SOURCE */

/*
 *	Structure Definitions
 */

#ifdef	_ALL_SOURCE
/*
 *	ipc_perm Mode Definitions.
 */
#define	MSG_R		IPC_R	/* read permission */
#define	MSG_W		IPC_W	/* write permission */
#define	MSG_RWAIT	01000	/* a reader is waiting for a message */
#define	MSG_WWAIT	02000	/* a writer is waiting to send */

/*
 *	Message header information
 */

#define	MSGX	time_t	mtime;		/* time message was sent */	\
		uid_t	muid;		/* author's effective uid */	\
		gid_t	mgid;		/* author's effective gid */	\
		pid_t	mpid;		/* author's process id */

struct msg_hdr	{ 
		 MSGX
		 mtyp_t	mtype;		/* message type */
};

/*
 *	There is one msg structure for each message that may be in the system.
 */

struct msg {
	struct msg     *msg_next;	/* ptr to next message on q */
	struct msg_hdr 	msg_attr;	/* message attributes */
	unsigned int	msg_ts; 	/* message text size */
	char		*msg_spot;	/* pointer to message text */
};

/*
 *	User message buffer template for msgsnd and msgrcv system calls.
 */

struct msgbuf {
	mtyp_t	mtype;		/* message type */
	char	mtext[1];	/* message text */
};

/*
 *	User message buffer template for msgxrcv system call.
 */

struct msgxbuf {
		MSGX
		mtyp_t	mtype;	  /* Message type */
		char	mtext[1]; /* Message text */
};

/* We need to know the length of everything but mtext[1] and padding. */
#define MSGXBUFSIZE (int)(((struct msgxbuf *)NULL)->mtext)

/* rmsgsnd() and rmsgrcv() "flags" parameter definitions */
#define MSG_SYSSPACE	0x01
#define XMSG 		0x02
#define MSG_INDIRECT    0x04    /* indirect access to message text */
/* flag specifying sytem V subroutines are called on behalf of
 * rt ipc routines
 * MUST not overlap with flags above
 */
#define MSG_RTIPC       0x08


/*
 *	Message information structure.
 */

struct msginfo {
	int	msgmax,	/* max message size			*/
		msgmnb,	/* max # bytes on queue 		*/
		msgmni,	/* # of message queue identifiers	*/
		msgmnm;	/* max # messages per queue identifier	*/
};

#endif	/* _ALL_SOURCE */

#ifdef _XOPEN_SOURCE
/*
 *	There is one msg queue id data structure for each q in the system.
 */

struct msqid_ds {
	struct ipc_perm	msg_perm;	/* operation permission struct */

#ifdef _ALL_SOURCE
#ifdef __64BIT__
	__ptr32		msg_first;	/* 32bit kernel ptr 1st msg on q */
	__ptr32		msg_last;	/* 32bit kernel ptr last msg on q */
#else
	struct msg	*msg_first;	/* ptr to first message on q */
	struct msg	*msg_last;	/* ptr to last message on q */
#endif /* __64BIT__ */
	unsigned int	msg_cbytes;	/* current # bytes on q */
#else
#ifdef __64BIT__
	__ptr32		__msg_first;	/* 32bit kernel ptr 1st msg on q */
	__ptr32		__msg_last;	/* 32bit kernel ptr last msg on q */
#else
	void 		*__msg_first;	/* ptr to first message on q */
	void 		*__msg_last;	/* ptr to last message on q */
#endif /* __64BIT__ */
	unsigned int 	__msg_cbytes;	/* current # bytes on q */
#endif /* _ALL_SOURCE */
	msgqnum_t	msg_qnum;	/* # of messages on q */
	msglen_t	msg_qbytes;	/* max # of bytes on q */
	pid_t		msg_lspid;	/* pid of last msgsnd */
	pid_t		msg_lrpid;	/* pid of last msgrcv */
	time_t		msg_stime;	/* last msgsnd time */
	time_t		msg_rtime;	/* last msgrcv time */
	time_t		msg_ctime;	/* last change time */

#ifdef _ALL_SOURCE
	/* event list of messages for this queue */
	int		msg_rwait;       /* wait list for message receive */
	int		msg_wwait;       /* wait list for message send */
	/* The following member is for msgselect() */
	unsigned short	msg_reqevents;   /* select/poll requested events */
#else
	/* event list of messages for this queue */
	int		__msg_rwait;     /* wait list for message receive */
	int		__msg_wwait;     /* wait list for message send */
	/* The following member is for msgselect() */
	unsigned short	__msg_reqevents; /* select/poll requested events */
#endif /* _ALL_SOURCE */
};


#ifdef _NO_PROTO
extern int msgctl();
extern int msgget();
extern int msgrcv();
extern int msgsnd();
#else
extern int msgget(key_t, int);
#if ((_XOPEN_SOURCE >= 500) || defined (__64BIT__))
ssize_t msgrcv(int, void *, size_t, long, int);
#else
extern int msgrcv(int, void *, size_t, long, int);
#endif
extern int msgsnd(int, const void *, size_t, int);
extern int msgctl(int, int, struct msqid_ds *);
#endif /* _NO_PROTO */

#endif /* _XOPEN_SOURCE */

#ifdef _ALL_SOURCE
/*
 * Number of bytes to copy for IPC_STAT_OLD command
 */
#define MSG_STAT_OLD  (int)&(((struct msqid_ds_OLD *)NULL)->msg_rwait)
/*
 * Number of bytes to copy for IPC_STAT command
 */

#define MSG_STAT  (int)&(((struct msqid_ds *)NULL)->msg_rwait)

		  
#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)
/*
 * Full prototypes for kernel interfaces.
 */
extern int kmsgctl(int, int, struct msqid_ds *);
extern int kmsgget(key_t, int, int *);
extern int kmsgrcv(int, struct msgxbuf *, size_t, mtyp_t, int, int, ssize_t *);
extern int kmsgsnd(int, struct msgbuf *, size_t, int);
#endif /* __64BIT_KERNEL || __FULL_PROTO */

extern ssize_t msgxrcv(int, struct msgxbuf*, size_t, long, int);

#endif /* _ALL_SOURCE */

#ifdef __cplusplus
}
#endif
#endif	/* _H_MSG */

