/*
 * Copyright 2006 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _SYS_MODHASH_IMPL_H
#define	_SYS_MODHASH_IMPL_H

#pragma ident	"@(#)modhash_impl.h	1.1	06/05/03 SMI"

/*
 * Internal details for the kernel's generic hash implementation.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _KERNEL

#include <sys/ksynch.h>
#include <sys/modhash.h>

struct mod_hash_entry {
	mod_hash_key_t mhe_key;			/* stored hash key	*/
	mod_hash_val_t mhe_val;			/* stored hash value	*/
	struct mod_hash_entry *mhe_next;	/* next item in chain	*/
};

struct mod_hash_stat {
	ulong_t mhs_hit;	/* tried a 'find' and it succeeded */
	ulong_t mhs_miss;	/* tried a 'find' but it failed */
	ulong_t mhs_coll;	/* occur when insert fails because of dup's */
	ulong_t mhs_nelems;	/* total number of stored key/value pairs */
	ulong_t mhs_nomem;	/* number of times kmem_alloc failed */
};

struct mod_hash {
	krwlock_t	mh_contents;	/* lock protecting contents */
	char		*mh_name;	/* hash name */
	int		mh_sleep;	/* kmem_alloc flag */
	size_t		mh_nchains;	/* # of elements in mh_entries */

	/* key and val destructor */
	void    (*mh_kdtor)(mod_hash_key_t);
	void    (*mh_vdtor)(mod_hash_val_t);

	/* key comparator */
	int	(*mh_keycmp)(mod_hash_key_t, mod_hash_key_t);

	/* hash algorithm, and algorithm-private data */
	uint_t  (*mh_hashalg)(void *, mod_hash_key_t);
	void    *mh_hashalg_data;

	struct mod_hash	*mh_next;	/* next hash in list */

	struct mod_hash_stat mh_stat;

	struct mod_hash_entry *mh_entries[1];
};

/*
 * MH_SIZE()
 * 	Compute the size of a mod_hash_t, in bytes, given the number of
 * 	elements it contains.
 */
#define	MH_SIZE(n) \
	(sizeof (mod_hash_t) + ((n) - 1) * (sizeof (struct mod_hash_entry *)))

/*
 * Module initialization; called once.
 */
void mod_hash_init(void);

#endif /* _KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* _SYS_MODHASH_IMPL_H */