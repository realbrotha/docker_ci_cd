/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/flock.h 1.38                                 */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,1989          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)15	1.38  src/bos/kernel/sys/flock.h, syslfs, bos530 7/25/02 19:22:48 */
/*
 * COMPONENT_NAME: SYSLFS - Logical File System
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27, 3
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1995
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
#ifndef _H_FLOCK
#define _H_FLOCK

#include <standards.h>
#include <sys/types.h>

/* POSIX does not define flock.h, however, the flock struct is required to
 * be included within fcntl.h when _POSIX_SOURCE is defined.  Therefore,
 * it is confined within POSIX ifdefs.
 */
#ifdef _POSIX_SOURCE
 
#ifndef _KERNEL
struct	flock	{
	short	l_type;
	short	l_whence;
#ifndef _LARGE_FILES
#ifndef __64BIT__
	off_t	l_start;
	off_t	l_len;		/* len = 0 means until end of file */
#endif
#endif
	unsigned int	l_sysid;
#ifdef	_NONSTD_TYPES
	ushort	l_pid_ext;
	ushort	l_pid;
#else
	pid_t	l_pid;
#endif
	int	l_vfs;
#if defined(_LARGE_FILES) || defined(__64BIT__)
	/* If LARGE FILES or 64 BIT then off_t is 64 bits and struct flock
	 * must be laid out as struct flock64
	 */
	off_t	l_start;
	off_t	l_len;
#endif
};
#endif /* _KERNEL */
typedef struct flock flock_t;

/* file segment locking types */
#define	F_RDLCK	01	/* Read lock */
#define	F_WRLCK	02	/* Write lock */
#define	F_UNLCK	03	/* Remove lock(s) */

#ifdef _LARGE_FILE_API
struct	flock64	{
	short		l_type;
	short		l_whence;
	unsigned int	l_sysid;
	pid_t		l_pid;
	int		l_vfs;
	off64_t		l_start;
	off64_t		l_len;
};
#endif /* _LARGE_FILE_API */

#endif /* _POSIX_SOURCE */

#ifdef _ALL_SOURCE
#ifdef _KERNEL
/* internal versions of 32 bit and 64 bit flock structures */

struct	flock	{
	short	l_type;
	short	l_whence;
	soff_t	l_start;
	soff_t	l_len;
	uint	l_sysid;
	pid_t	l_pid;
	int	l_vfs;
};

struct	eflock	{
	short		l_type;
	short		l_whence;
	unsigned int	l_sysid;
	pid_t		l_pid;
	int		l_vfs;
	offset_t	l_start;
	offset_t	l_len;
};
typedef struct eflock eflock_t;

/*
 * Function prototype for common_reclock()
 * This prototype allows the compiler to automatically promote the
 * size and offset parameters to their appropriate sizes without
 * having to use a type cast at the call site.
 */

struct gnode;

int
common_reclock(
	struct gnode *	gp,
	offset_t	size,
	offset_t	offset,
	struct eflock *	lckdat,
	int		cmd,
	int (*		retry_fcn)(),
	ulong	       *retry_id,
	int (*		lock_fcn)(),
	int (*		rele_fcn)());

#define INOFLCK		1	/* Inode is locked when reclock() is called. */
#define SETFLCK		2	/* Set a file lock. */
#define SLPFLCK		4	/* Wait if blocked. */

/* lock status
 *	used to coordinate with sleeping locks
 * 	WASBLOCK is only used for debugging
 */
#define LCK_UNBLOCK	0
#define	LCK_BLOCKER	1
#define	LCK_BLOCKED	2
#define	LCK_WASBLOCK	4

/* file locking structure (connected to gnode) 
 */
#define l_end 		l_len
#define MAXEND  	LONGLONG_MAX

struct	filock {
	struct	eflock	set;	/* contains type, start, and end (len) */
	short		state;	/* current state, see defines above */

	/* information about the blocking lock, if any */
	short		vfs;
	unsigned int	sysid;
	pid_t		pid;
	struct filock *	filockp;
	int (*		retry_fcn)();
	union {
		struct filock *	fl_prev;
		struct filock * fl_qmnext;	/* pointer to next quick */
						/* move chunk on free list */
	} _flp;
	struct filock *	fl_next;
	tid_t		event;	/* event list anchor */
	struct gnode *sl_gnode; /* gnode pointer for the object to be locked */
};
typedef struct filock filock_t;

#define fl_prev		_flp.fl_prev
#define fl_qmnext	_flp.fl_qmnext

/* file and record locking configuration structure */
/* record use total may overflow */
struct flckinfo {
	long recs;	/* number of records configured on system */
	long reccnt;	/* number of records currently in use */
	long recovf;	/* number of times system ran out of record locks. */
	long rectot;	/* number of records used since system boot */
};

#define RMTLOCK 1

#define ENF_LOCK(mode)	(((mode) & (ISGID | IEXEC | (IEXEC >> 3) | (IEXEC >> 6))) == ISGID)

#ifndef __64BIT_KERNEL
extern struct flckinfo	flckinfo;
extern struct filock	flox[];
#endif /* !__64BIT_KERNEL */
#endif /* _KERNEL */
#endif /* _ALL_SOURCE */
#endif /* _H_FLOCK */
