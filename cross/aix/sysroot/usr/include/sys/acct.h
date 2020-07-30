/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/acct.h 1.17                                  */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1993          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)39	1.17  src/bos/kernel/sys/acct.h, sysproc, bos530 4/11/04 16:55:57 */
/*
 *   COMPONENT_NAME: SYSPROC
 *
 *   FUNCTIONS: 
 *
 *   ORIGINS: 27,3
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1993
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */


#ifndef _H_ACCT
#define _H_ACCT

#include <sys/types.h>
#include <sys/param.h>

/*
 * Accounting structures
 * these use a comp_t type which is a 3 bit base 8 
 * exponent, 13 bit fraction "floating point" number.
 * Units are 1/AHZ seconds.
 */

typedef	ushort comp_t;		/* "floating point" */
		/* 13-bit fraction, 3-bit exponent  */

struct	acct
{
	char	ac_flag;		/* Accounting flag */
	char	ac_stat;		/* Exit status */
	char	ac_version;		/* File version */		
	char	ac_len;			/* Length of structure */
	uid_t	ac_uid;			/* Accounting user ID */
	gid_t	ac_gid;			/* Accounting group ID */
#ifdef __64BIT__
	dev32_t	ac_tty;			/* control typewriter */
	dev_t	ac_tty64;		/* 64-bit control typewriter */
#else
	dev_t	ac_tty;			/* control typewriter */
#if defined(_LONG_LONG)
	dev64_t	ac_tty64;		/* 64-bit control typewriter */
#else
        /* For 32-bit applications that do not define _LONG_LONG, this
         * will keep the size and offsets of the structure the same. However,
         * it will not work properly. However, since 32-bit apps should not
         * care about 64-bit devices, it will not make a difference. */
	quad ac_tty64;
#endif
#endif /* __64_BIT__ */
#if defined(_LONG_LONG)
        uint64_t ac_wlmkey;             /* WLM class identification */
#else
        quad     ac_wlmkey;		/* WLM class identification */
#endif

#if !defined __64BIT__ && (BYTE_ORDER == BIG_ENDIAN)
	uint	ac_btime_pad;		/* Beginning time (high word) */
#endif
	time_t	ac_btime;		/* Beginning time */
#if !defined __64BIT__ && (BYTE_ORDER == LITTLE_ENDIAN)
	uint	ac_btime_pad;		/* Beginning time (low word) */
#endif
	
	comp_t	ac_utime;		/* acctng user time in seconds */
	comp_t	ac_stime;		/* acctng system time in seconds */
	comp_t	ac_etime;		/* acctng elapsed time in seconds */
	comp_t	ac_mem;			/* memory usage */
	comp_t	ac_io;			/* chars transferred */
	comp_t	ac_rw;			/* blocks read or written */
	char	ac_comm[12];		/* command name */

#if defined(_LONG_LONG) || defined(__64BIT__)
	uint64_t ac_ctime;		/* reserved for usecs */
#else
	quad	ac_ctime;
#endif

	int 	reserved[6];
};	

#define	AFORK	0001		/* has executed fork, but no exec */
#define	ASU	0002		/* used super-user privileges */
#define	ACOMPAT	0004		/* used compatibilty mode */
#define	ACORE	0010		/* dumped core */
#define	AXSIG	0020		/* killed by signal */
#define	ACHKPNT	0040		/* killed by checkpoint */
#define	ACCTF	0300		/* record type: 00 = acct */

/*
 * 1/AHZ is the granularity of the data encoded in the various
 * comp_t fields. This is not necessarily equal to hz.
 */

#define AHZ 64
#endif	/* _H_ACCT */
