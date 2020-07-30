/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53D src/bos/kernel/sys/cred.h 1.9.1.29                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1989          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)22     1.9.1.29  src/bos/kernel/sys/cred.h, syssauth, bos53D, d2005_13C0 3/28/05 11:17:05 */
/*
 *   COMPONENT_NAME: SYSSAUTH
 *
 *   FUNCTIONS: crhold
 *
 *
 *   ORIGINS: 3,9,24,26,27,83
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,2000
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 *   Copyright (c) 1988 by Sun Microsystems, Inc.
 */
/*
 *   LEVEL 1,  5 Years Bull Confidential Information
 */

#ifndef _H_CRED
#define _H_CRED

#ifdef __cplusplus
extern "C" {
#endif



#include <sys/limits.h>
#include <sys/types.h>
#include <sys/priv.h>
#include <sys/lockl.h>
#include <sys/capabilities.h>

#define	SHORT_NGROUPS	NGROUPS_MAX
#define	PAG_GROUPS	8

/*
 * groupset_t --
 *
 * This structure defines group sets.  The credentials structure only
 * has room for GROUPS_PER_SET groups.  When the cred has more than
 * GROUPS_PER_SET groups, a new groupset_t structure is appended.
 *
 * The macro __NGROUPS_GROUPSET_MAX is used for backwards compatibility.  It
 * defines the number of groups which are used by the 32-bit kernel.  It
 * must not be defined.  GROUPS_PER_SET is defined in terms of
 * __NGROUPS_GROUPSET_MAX and its definition must always be such that groupset_t
 * occupies no more space than the size of __NGROUPS_GROUPSET_MAX gid values.
 */

#define	__NGROUPS_GROUPSET_MAX 32

#define	GROUPS_PER_SET \
	((__NGROUPS_GROUPSET_MAX * sizeof (gid_t) - sizeof (void *)) \
		/ sizeof (gid_t))

typedef struct groupset {
	union {
		struct {
			gid_t	un_groups[GROUPS_PER_SET];
			struct groupset *un_next;
		} un_struct;
		gid_t	un_groups[__NGROUPS_GROUPSET_MAX];
	} gs_union;
} groupset_t;

/*
 * These macros provide access to the groupset structure members,
 * but only to kernel code.
 */

#ifdef _KERNEL
#define	gs_groups	gs_union.un_struct.un_groups
#define	gs_next		gs_union.un_struct.un_next
#endif

/*
 * PAG related macros
 */

/*
 * PAG_GROUPSET_PADDING caculates the number of groupset padding
 * entries required to ensure that PAG values are properly aligned and
 * are located at the beginning of their own groupset structure.
 */

#define PAG_GROUPSET_PADDING_WITH_GROUPS(ngrps) \
	((((ngrps) % GROUPS_PER_SET) == 0) ? 0 : \
	 GROUPS_PER_SET - ((ngrps) % GROUPS_PER_SET))

#define PAG_GROUPSET_PADDING(ngrps) \
	(((ngrps) == 0) ? GROUPS_PER_SET : \
	PAG_GROUPSET_PADDING_WITH_GROUPS((ngrps)))

/*
 * PAG_GROUPS_EFFECTIVE caculates the total number of groupset entries
 * required to hold all PAG values.  This includes the actual 64-bit
 * PAG values and any initial padding.
 */

#define PAG_GROUPS_EFFECTIVE(ngrps) \
	(PAG_GROUPSET_PADDING(ngrps) + ((PAG_GROUPS) * 2))

#ifndef MAX_PAG_ENTRIES
#define	MAX_PAG_ENTRIES		16
#endif

/*
 * cred_t
 *
 * Internal process credentials structure.  This structure is not
 * to be referenced by other than security kernel functions and
 * services.  The layout of this data structure is subject to
 * change.  Use cred_ext_t and the crexport() kernel function.
 */

struct ucred {
	int	cr_ref;			/* reference count */
	/* user ID's - managed by {gs}etuidx() */
	uid_t   cr_ruid;		/* real user id */
	uid_t   cr_uid;			/* effective user id */
	uid_t   cr_suid;		/* saved user id */
	uid_t   cr_luid;		/* login user id */
	uid_t   cr_acctid;		/* accounting id */
	/* group ID's - managed by {gs}etgidx() */
	gid_t   cr_gid;			/* effective group id */
	gid_t   cr_rgid;		/* real group id */
	gid_t   cr_sgid;		/* saved group id */
	/* concurrent group set - managed by {gs}etgroups() */
	short	cr_ngrps;		/* how many groups in list */
	/* capabilities -- managed by kcap_{gs}et_proc */
#if !defined(__64BIT_KERNEL)
	short	cr_caps;		/* capabilities sets 32-bit, non-LDT */
#else
	struct	__cap_t cr_caps;	/* capabilities sets 64-bit and LDT */
#endif
	groupset_t cr_groupset;		/* every cred gets one free set */

	/*
	 * max privileges
	 * at exec(), this is: old effective + old bequeathed
	 */
	priv_t	cr_mpriv;

	/*
	 * inherited privileges
	 * at exec(), this is: old bequeathed
	 */
	priv_t	cr_ipriv;

	/*
	 * current privileges
	 * at exec(), this is: old bequeathed + program's
	 */
	priv_t	cr_epriv;

	/*
	 * bequeathed privileges
	 * at exec(), this is: old bequeathed + program's
	 */
	priv_t	cr_bpriv;

	int    cr_pag;                 /* DCE process authentication group */
};

typedef struct ucred    cred_t;

/*
 * cred_43_t
 *
 * This structure is provided for binary compatibility.
 */

struct ucred_43 {
	int	ocr_ref;		/* Reference count */
	uid_t   ocr_ruid;		/* Real user ID */
	uid_t   ocr_uid;		/* Effective user ID */
	uid_t   ocr_suid;		/* Saved user ID */
	uid_t   ocr_luid;		/* Login user ID */
	uid_t   ocr_acctid;		/* Accounting user ID (unused) */
	gid_t   ocr_gid;		/* Effective group ID */
	gid_t   ocr_rgid;		/* Real group ID */
	gid_t   ocr_sgid;		/* Saved user ID */
	short	ocr_ngrps;		/* Number of concurrent groups */
	gid_t	ocr_groups[__NGROUPS_GROUPSET_MAX]; /* Concurrent groups */
	priv_t	ocr_mpriv;		/* Maximum privilege set */
	priv_t	ocr_ipriv;		/* Inherited privilege set */
	priv_t	ocr_epriv;		/* Effective privilege set */
	priv_t	ocr_bpriv;		/* Bequeathed privilege set */
	int	ocr_pag;		/* DCE PAG */
};
typedef struct ucred_43 cred_43_t;

/*
 * cred_ext_t
 *
 * This is the exportable user credentials structure.  It is the same
 * size and shape on 32 and 64 bit kernels and for 32 and 64 bit
 * processes, and all combinations thereof.  It is heavily padded
 * for future extensions.  This structure must be used wherever
 * a credentials structure is to be externalized because the other
 * credentials structure is subject to change without notice.
 *
 * This structure contains a mixture of 64-bit and 32-bit objects.
 * To avoid implicit padding, words should be inserted before any
 * double-word object when the structure offset is not a multiple
 * of 8.
 *
 * For 64 bit PAGs, the value is stored in two consecutive elements of
 * the crx_pags array.  The low word will correspond to the crx_pagids
 * element with the correct pag type.  The high word will correspond to
 * the crx_pagids element with the CRX_PAGID_64BIT bit set and with the
 * correct pag type set in the CRX_PAGID_MASK bits.
 */

#define CRX_PAGID_64BIT	0x80
#define CRX_PAGID_MASK	0x7f

#define CRX_MAX_GROUPS	128

typedef struct ucred_ext {

	/*
	 * User ID values
	 */

	uid_t   crx_ruid;		/* real user id */
	uid_t   crx_uid;		/* effective user id */
	uid_t   crx_suid;		/* saved user id */
	uid_t   crx_luid;		/* login user id */
	uid_t   crx_acctid;		/* accounting id */

	/*
	 * Group ID values
	 */

	gid_t   crx_gid;		/* effective group id */
	gid_t   crx_rgid;		/* real group id */
	gid_t   crx_sgid;		/* saved group id */

	/* 
	 * Concurrent group set.  Allows for up to CRX_MAX_GROUPS concurrent
	 * groups.  cr_ngroups lists the actual number of valid
	 * entries.
	 */

	int	crx_ngrps;		/* how many groups in list */
	gid_t   crx_groups[CRX_MAX_GROUPS]; /* short list of groups */

	/*
	 * Padding -- reserved word needed for alignment.
	 */

	int	crx_reserved_1;

	/*
	 * Capabilities
	 */

	struct	__cap_t crx_caps;	/* capabilities sets */ 

	/*
	 * Privileges
	 */

	priv_t	crx_mpriv;		/* Maximum privileges */
	priv_t	crx_ipriv;		/* Inherited privileges */
	priv_t	crx_epriv;		/* Effecive privileges */
	priv_t	crx_bpriv;		/* Bequeath privileges */

	/*
	 * PAGs
	 */

	int	crx_npags;		/* Number of PAG entries below */
	char	crx_pagids[MAX_PAG_ENTRIES]; /* PAG id number */
	int	crx_pags[MAX_PAG_ENTRIES]; /* PAG values */

	/*
	 * Pad to 256 words (1K bytes)
	 */

	int	crx_pad[256-173];	/* Padding for future extensions */
} cred_ext_t;

#ifdef	_KERNSYS

/*
 * The following code fragment enforces the 1KB size requirement for
 * (cred_ext_t).  If this code results in a compilation error the
 * size of crx_pad is incorrect and must be adjusted.
 */

struct ucred_ext_validitycheck {
	char	a[(sizeof (cred_ext_t) == 1024) ? 1:-1];
};
#endif


/*
 * Credentials services
 */

void crlock(void);
void crunlock(void);
void credlock(void);
void credunlock(void);
void crfree(struct ucred *);
struct ucred *crref(void);
struct ucred *crxref(struct ucred * volatile *);
struct ucred *crget(void);
struct ucred *crcopy(struct ucred *);
struct ucred *crdup(struct ucred *);
void crset(struct ucred *);
void crhold(struct ucred *);
void crexport(struct ucred *, struct ucred_ext *);
struct ucred *crimport(int, void *);

/*
 * Credentials macros
 */

#define	CRED_GETREF(cr) ((cr)->cr_ref)

#define CRED_GETRUID(cr) ((cr)->cr_ruid)
#define CRED_GETEUID(cr) ((cr)->cr_uid)
#define CRED_GETSUID(cr) ((cr)->cr_suid)
#define CRED_GETLUID(cr) ((cr)->cr_luid)
#define CRED_GETACCTID(cr) ((cr)->cr_acctid)

#define CRED_GETEGID(cr) ((cr)->cr_gid)
#define CRED_GETRGID(cr) ((cr)->cr_rgid)
#define CRED_GETSGID(cr) ((cr)->cr_sgid)

#define CRED_GETNGRPS(cr) ((cr)->cr_ngrps)

/* Get per-thread credentials or process credentials as appropriate */
#ifdef _KERNSYS
#define CRED_GETCREDP()	    (curthread->t_credp ? curthread->t_credp : U.U_cred)
#define CRED_TGETCREDP(t)   ((t)->t_credp ? (t)->t_credp : U.U_cred)
#endif

/*
 * Credentials constructing functions
 */

int kcred_getgroups (struct ucred *, int, gid_t *);
int kcred_setgroups (struct ucred *, int, gid_t *);
int kcred_getpriv (struct ucred *, int, priv_t *);
int kcred_setpriv (struct ucred *, int, priv_t *);
void kcred_getcap (struct ucred *, struct __cap_t *);
void kcred_setcap (struct ucred *, struct __cap_t *);
int kcred_getpag (struct ucred *, int, int *);
int kcred_getpag64 (struct ucred *, int, uint64_t *);
int kcred_setpag (struct ucred *, int, int);
int kcred_setpag64 (struct ucred *, int, uint64_t);
int kcred_genpagvalue (struct ucred *, int, uint64_t *, int);

/*
 * Groupset checking functions
 */

int groupmember (gid_t);
int groupmember_cr (gid_t, struct ucred *);

/*
 * Kernel services to manage pags.
 */

/* which parameter values */
#define PAG_DFS         0
#define PAG_AFS         1

int get_pag(int which, int *pag);
int get_pag64(int which, uint64_t *pag);
int set_pag(int which, int pag);
int set_pag64(int which, uint64_t pag);

struct pag_list {
	int pag;
	int active;
	int spare[2];
};

int validate_pag(int which, struct pag_list pag[], int npag);

struct pag_list64 {
	uint64_t pag;
	int active;
	int spare[2];
};

int validate_pag64(int which, struct pag_list64 pag[], int npag);

#define U_ROOT_UID          0 
#define G_SYSTEM_GRP        0 
#define G_SECURITY_GRP      7

#ifdef __cplusplus
}
#endif

#endif /* _H_CRED */
