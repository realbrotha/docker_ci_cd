/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/kernel/sys/capabilities.h 1.11                          */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2000,2006          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

#ifndef _H_SYS_CAP
#define	_H_SYS_CAP

#include <sys/types.h>

/*
 * cap_flag_t
 *
 * Flag for selecting which capabilities set is requested.
 */

#define	CAP_EFFECTIVE	1
#define	CAP_INHERITABLE	2
#define	CAP_PERMITTED	3
typedef unsigned int cap_flag_t;

/*
 * cap_t
 *
 * cap_t is an opaque data type.  The format used within the
 * library and kernel is represented by (struct __cap_t).
 */

struct __cap_t {
	uint64_t cap_effective;
	uint64_t cap_inheritable;
	uint64_t cap_permitted;
};
typedef void * cap_t;
cap_t cap_init();

/*
 * cap_flag_value_t
 *
 * A flag to indicate if a capability should be or is set or cleared.
 */

#define CAP_CLEAR	0
#define	CAP_SET		1
typedef unsigned int cap_flag_value_t;

/*
 * cap_value_t
 *
 * The symbolic constants used to represent capabilities.
 */

typedef int cap_value_t;

#define	CAP_PROPAGATE	   1		/* inherit without file capabilities */
#define	CAP_PROPOGATE	   1		/* deprecated spelling */
#define	CAP_NUMA_ATTACH	   2		/* NUMA attachment capability */
#define CAP_BYPASS_RAC_VMM 3	        /* large page use capability */
#define	CAP_EWLM_AGENT	   4		/* eWLM Agent capability */
#define	CAP_ARM_APPLICATION 5		/* ARM Application capability */
#define	CAP_AACCT	   6		/* Advanced Accounting capability */
#define	CAP_CREDENTIALS	   7		/* Per-thread credentials */

#define CAP_MAXIMUM CAP_CREDENTIALS	/* Highest valued capability */

/*
 * Kernel functions and exported services
 */

#ifdef _KERNEL
struct ucred;
int kcap_get_proc (struct __cap_t *, int);
int kcap_set_proc (struct __cap_t *, int);
int kcap_is_set_cr (int, struct ucred *);
int kcap_is_set (int);

#if defined(__64BIT_KERNEL)
int kcap_is_null_set (cap_flag_t, struct __cap_t *);
int kcap_is_subset (cap_flag_t, struct __cap_t *, struct __cap_t *);
void kcap_exec (struct __cap_t *);
#else
int kcap_is_null_set (cap_flag_t, short *);
int kcap_is_subset (cap_flag_t, short *, short *);
void kcap_exec (short *);
#endif	/* defined(__64BIT_KERNEL) */

#endif	/* _KERNEL */

#endif	/* _H_SYS_CAP */
