/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53S src/bos/kernel/sys/ukeys.h 1.4                                  */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 2005,2008              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)31     1.4  src/bos/kernel/sys/ukeys.h, sysras, bos53S, s2008_33C3 7/29/08 06:05:10 */
/*
 *   COMPONENT_NAME: SYSRAS (Storage Keys infrastructure)
 *
 *   FUNCTIONS:
 *
 *   ORIGINS: 27
 *
 */

#ifndef _H_UKEYS
#define _H_UKEYS

#include <sys/types.h>

/* User-key type defines and structures */
typedef unsigned int ukey_t;
typedef unsigned long long ukeyset_t;

#ifndef _KERNEL
/* User-key APIs and related defines */

int ukey_enable(void);
int ukey_getkey(void *, ukey_t *);
int ukey_protect(void *, size_t, ukey_t);

int ukeyset_init(ukeyset_t *nset, unsigned int flags);

int ukeyset_add_key(ukeyset_t *set, ukey_t key, unsigned int flags);
int ukeyset_remove_key(ukeyset_t *set, ukey_t key, unsigned int flags);
int ukeyset_ismember(ukeyset_t set, ukey_t key, unsigned int flags);
int ukeyset_add_set(ukeyset_t *set, ukeyset_t aset);
int ukeyset_remove_set(ukeyset_t *set, ukeyset_t rset);
int ukey_reserve(unsigned int flags, ukey_t *ukey);
int ukey_release(unsigned int flags, ukey_t ukey);

ukeyset_t ukeyset_activate(ukeyset_t set, int command);

#pragma mc_func ukeyset_activate \
{\
	"48008003"		/* bla 0x8000 */	\
}

#endif		/* ndef _KERNEL */

/* ukeyset_init() flag values */
#define UK_INIT_ADD_PRIVATE		0x00000001   /* Add private keys also */

/* ukeyset_add_key() and ukeyset_remove_key() flags */
#define UK_READ			0x00000001	      /* Read access key bit */
					
#define UK_WRITE		0x00000002	      /* Write access key bit */
#define UK_RW			(UK_READ | UK_WRITE)  /* Both R/W key bits */

/* ukeyset_activate() command values */

#define UKA_REPLACE_KEYS	1	/* replace kset with specified kset */
#define UKA_ADD_KEYS	 	2	/* add specified kset to current kset */
#define UKA_REMOVE_KEYS	 	3	/* remove given kset from active kset */
#define UKA_GET_KEYS	 	4	/* return current keyset */

/* Error return value from ukeyset_activate() */
#define UKSET_INVALID 		-1ULL

/*
 * As there are 32 user keys, this 32 bit mask value is used for reserving/
 * releasing user keys.
 */
#define UKEY_RESERVE_MASK	0x80000000
#define UKEY_RESERVE_INIT	0x00000000

/*
 * User Key values 
 *
 *	The UKEY_PUBLIC is numbered zero.
 *	The private user keys are numbered from 1 to 31.
 *	The UKEY_SYSTEM is a special key and cannot be assigned directly to
 *		any user memory. It is the value is returned by ukey_getkey()
 *		when the user-key for non-application memory (such as the
 *		kernel address space) is queried. 
 */
enum ukeys {
	UKEY_PUBLIC = 0,
	UKEY_PRIVATE1,
	UKEY_PRIVATE2,
	UKEY_PRIVATE3,
	UKEY_PRIVATE4,
	UKEY_PRIVATE5,
	UKEY_PRIVATE6,
	UKEY_PRIVATE7,
	UKEY_PRIVATE8,
	UKEY_PRIVATE9,
	UKEY_PRIVATE10,
	UKEY_PRIVATE11,
	UKEY_PRIVATE12,
	UKEY_PRIVATE13,
	UKEY_PRIVATE14,
	UKEY_PRIVATE15,
	UKEY_PRIVATE16,
	UKEY_PRIVATE17,
	UKEY_PRIVATE18,
	UKEY_PRIVATE19,
	UKEY_PRIVATE20,
	UKEY_PRIVATE21,
	UKEY_PRIVATE22,
	UKEY_PRIVATE23,
	UKEY_PRIVATE24,
	UKEY_PRIVATE25,
	UKEY_PRIVATE26,
	UKEY_PRIVATE27,
	UKEY_PRIVATE28,
	UKEY_PRIVATE29,
	UKEY_PRIVATE30,
	UKEY_PRIVATE31,
	UKEY_MAXIMUM = UKEY_PRIVATE31,

	UKEY_SYSTEM = 256
};

#define NUM_USERKEYS	UKEY_MAXIMUM+1  /* max. number of user keys supported */

extern int __n_userkeys;
extern int __validate_ukset(ukeyset_t *set);
extern void __get_ukeys(ukeyset_t set, char *buf);
extern void __get_ukey_name(ukey_t key, char *keyname);

#endif /* _H_UKEYS */
