/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/ndbm.h 1.3.1.11                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1992,1995          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)70  1.3.1.11  src/bos/usr/include/ndbm.h, libcndbm, bos530 8/5/03 09:27:07 */
#ifdef _POWER_PROLOG_
/*
 *   COMPONENT_NAME: LIBCNDBM
 *
 *   FUNCTIONS: dbm_clearerr, dbm_dirfno, dbm_error, dbm_pagfno, dbm_rdonly
 *		
 *   ORIGINS: 26,27,71
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1992,1995
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
#endif /* _POWER_PROLOG_ */

/*
 * (c) Copyright 1990, 1991, 1992 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */
/*
 *
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 */

#ifndef _H_NDBM
#define _H_NDBM

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if _XOPEN_SOURCE_EXTENDED==1

#include <strict_stdtypes.h>

#ifndef _H_TYPES
#include <sys/types.h>
#endif

#include <end_strict_stdtypes.h>

/*
 * 
 * FUNCTIONS: dbm_clearerr, dbm_dirfno, dbm_error, dbm_pagfno, dbm_rdonly 
 * Hashed key data base library.
 */
typedef struct {
	int	dbm_dirf;		/* open directory file */
	int	dbm_pagf;		/* open page file */
	int	dbm_flags;		/* flags, see below */
	int	dbm_maxbno;		/* last ``bit'' in dir file */
	int	dbm_bitno;		/* current bit number */
	int	dbm_hmask;		/* hash mask */
	int	dbm_blkptr;		/* current block for dbm_nextkey */
	int	dbm_keyptr;		/* current key for dbm_nextkey */
	int	dbm_blkno;		/* current page to read/write */
	int	dbm_pagbno;		/* current page in pagbuf */
	char	dbm_pagbuf[1024];	/* page file block buffer */
	int	dbm_dirbno;		/* current block in dirbuf */
	char	dbm_dirbuf[4096];	/* directory file block buffer */
#if (defined(_THREAD_SAFE) && defined(_ALL_SOURCE))
	void	*dbm_lock;		/* for inter-thread locking */
#endif
} DBM;

#define _DBM_RDONLY	0x1	/* data base open read-only */
#define _DBM_IOERR	0x2	/* data base I/O error */

typedef struct {
	void	*dptr;
	size_t	dsize;
} datum;

/*
 * flags to dbm_store()
 */
#define DBM_INSERT	0
#define DBM_REPLACE	1

#ifdef _NO_PROTO
int	dbm_clearerr(DBM *);
void	dbm_close();
int	dbm_delete();
int	dbm_error();
datum	dbm_fetch();
datum	dbm_firstkey();
datum	dbm_nextkey();
int	dbm_forder();
DBM	*dbm_open();
int	dbm_store();
#else
int	dbm_clearerr(DBM *);
void	dbm_close(DBM *);
int	dbm_delete(DBM *, datum);
int	dbm_error(DBM*);
datum	dbm_fetch(DBM *, datum);
datum	dbm_firstkey(DBM *);
datum	dbm_nextkey(DBM *);
int	dbm_forder(DBM *, datum);
DBM	*dbm_open(const char *, int, mode_t);
int	dbm_store(DBM *, datum, datum, int);
#endif /* _NO_PROTO */

#define dbm_rdonly(db)	((db)->dbm_flags & _DBM_RDONLY)

#define dbm_error(db)	((db)->dbm_flags & _DBM_IOERR)
	/* use this one at your own risk! */
#define dbm_clearerr(db)	((db)->dbm_flags &= ~_DBM_IOERR)

/* for flock(2) and fstat(2) */
#define dbm_dirfno(db)	((db)->dbm_dirf)
#define dbm_pagfno(db)	((db)->dbm_pagf)

#endif /* _XOPEN_SOURCE_EXTENDED */

#ifdef _ALL_SOURCE
#define PBLKSIZ 1024
#define DBLKSIZ 4096
#endif /* _ALL_SOURCE */

#ifdef __cplusplus
}
#endif
#endif /* _H_NDBM */
