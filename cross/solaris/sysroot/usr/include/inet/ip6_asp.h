/*
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_INET_IP6_ASP_H
#define	_INET_IP6_ASP_H

#pragma ident	"@(#)ip6_asp.h	1.3	04/09/28 SMI"

#ifdef	__cplusplus
extern "C" {
#endif

#include <netinet/in.h>
#include <sys/types.h>
#include <inet/ip6.h>

/*
 * The maximum size of the label, including NULL bytes following the
 * label string.  The implementation assumes that this value is 16.
 */
#define	IP6_ASP_MAXLABELSIZE	16

typedef struct ip6_asp {
	in6_addr_t	ip6_asp_prefix;
	in6_addr_t	ip6_asp_mask;
	/*
	 * ip6_asp_label must be on an 8 byte boundary because we cast
	 * them as (int64_t *) in order to compare them as two 64 bit
	 * integers rather than sixteen characters.
	 */
	union {
		char	iau_label_c[IP6_ASP_MAXLABELSIZE];
		int64_t	iau_label_i[IP6_ASP_MAXLABELSIZE / sizeof (int64_t)];
	} ip6_asp_u;
	uint32_t	ip6_asp_precedence;
} ip6_asp_t;
#define	ip6_asp_label	ip6_asp_u.iau_label_c

#if defined(_SYSCALL32) && _LONG_LONG_ALIGNMENT_32 == 4

/*
 * The ip6_asp structure as seen by a 64-bit kernel looking
 * at a 32-bit process, where the 32-bit process uses 32-bit
 * alignment for 64-bit quantities.  Like i386 does :-)
 */
typedef struct ip6_asp32 {
	in6_addr_t	ip6_asp_prefix;
	in6_addr_t	ip6_asp_mask;
	union {
		char	iau_label_c[IP6_ASP_MAXLABELSIZE];
		int32_t	iau_label_i[IP6_ASP_MAXLABELSIZE / sizeof (int32_t)];
	} ip6_asp_u;
	uint32_t	ip6_asp_precedence;
} ip6_asp32_t;

#endif	/* _SYSCALL32 && _LONG_LONG_ALIGNMENT_32 == 4 */

#define	IP6_ASP_TABLE_REFHOLD() {			\
	ip6_asp_refcnt++;				\
	ASSERT(ip6_asp_refcnt != 0);			\
}

#define	IP6_ASP_TABLE_REFRELE()	{			\
	mutex_enter(&ip6_asp_lock);			\
	ASSERT(ip6_asp_refcnt != 0);			\
	if (--ip6_asp_refcnt == 0) {			\
		mutex_exit(&ip6_asp_lock);		\
		ip6_asp_check_for_updates();		\
	} else {					\
		mutex_exit(&ip6_asp_lock);		\
	}						\
}

/*
 * Structure used in the SIOCGDSTINFO request.
 * Used to retrieve information about the given destination
 * address, to be used by the caller to sort a list of
 * potential destination addresses.
 */
struct dstinforeq {
	in6_addr_t	dir_daddr;		/* destination address */
	in6_addr_t	dir_saddr;		/* source address for daddr */
	in6addr_scope_t	dir_dscope;		/* destination scope */
	in6addr_scope_t	dir_sscope;		/* source scope */
	t_uscalar_t	dir_dmactype;		/* dl_mac_type of output inf */
	uint32_t	dir_precedence;		/* destination precedence */
	uint8_t		dir_dreachable : 1,	/* is destination reachable? */
			dir_sdeprecated : 1,	/* is source deprecated? */
			dir_labelmatch: 1,	/* src and dst labels match? */
			dir_padbits : 5;
};

#ifdef _KERNEL

typedef void (*aspfunc_t)(ipsq_t *, queue_t *, mblk_t *, void *);

extern void	ip6_asp_free(void);
extern void	ip6_asp_init(void);
extern boolean_t	ip6_asp_can_lookup();
extern void	ip6_asp_table_refrele();
extern char	*ip6_asp_lookup(const in6_addr_t *, uint32_t *);
extern void	ip6_asp_replace(mblk_t *mp,
    ip6_asp_t *, size_t, boolean_t, model_t);
extern int	ip6_asp_get(ip6_asp_t *, size_t);
extern boolean_t	ip6_asp_labelcmp(const char *, const char *);
extern void	ip6_asp_pending_op(queue_t *, mblk_t *, aspfunc_t);

#endif /* _KERNEL */

#ifdef	__cplusplus
}
#endif

#endif	/* _INET_IP6_ASP_H */
