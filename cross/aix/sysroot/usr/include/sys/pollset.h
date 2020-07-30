/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53D src/bos/kernel/sys/pollset.h 1.3                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2005               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)70	1.3  src/bos/kernel/sys/pollset.h, sysios, bos53D, d2005_16B5 4/13/05 13:21:12 */
#ifndef _H_POLLSET
#define _H_POLLSET
#ifndef _H_POLL
#include <sys/poll.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define PS_ADD		0x0
#define PS_MOD		0x1
#define PS_DELETE	0x2

typedef int pollset_t;

struct pollingset {
	struct pollfd	*ps_fds;
	int		array_length;
	int		timeout;
};
typedef struct pollingset pollingset_t;

struct poll_ctl {
	short cmd;
	short events;
	int fd;
};

extern pollset_t pollset_create(int maxfd);
extern int pollset_destroy(pollset_t ps);
extern int pollset_query(pollset_t ps, struct pollfd *pollfd_query);
extern int pollset_ctl(pollset_t ps, struct poll_ctl *pollctl_array,
		       int array_length);
extern int pollset_poll(pollset_t ps, struct pollfd *polldata_array,
			int array_length, int timeout);

#ifdef __cplusplus
}
#endif

#ifdef _KERNSYS

typedef struct pollingset64 {
	int		ps_fds_hi;
	int		ps_fds_lo;
	int		array_length;
	int		timeout;
}pollingset64_t;

#endif
#endif	/* _H_POLLSET */
