/*
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_SYS_CPC_IMPL_H
#define	_SYS_CPC_IMPL_H

#pragma ident	"@(#)cpc_impl.h	1.11	04/09/28 SMI"

#include <sys/types.h>
#include <sys/time.h>
#include <sys/rwlock.h>

#if defined(_KERNEL) && defined(_MULTI_DATAMODEL)
#include <sys/types32.h>
#endif

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct {
	char		*ca_name;
	uint64_t	ca_val;
} cpc_attr_t;

/*
 * Flag arguments to cpc_bind_event and cpc_ctx_bind_event
 */
#define	CPC_BIND_LWP_INHERIT	(0x1)
#define	CPC_BIND_EMT_OVF	(0x2)

#define	CPC_MAX_IMPL_NAME	512	/* Max len of PCBE's description str */
#define	CPC_MAX_CPUREF		1024	/* Max len of PCBE's CPU ref string */

#define	CPC_OVF_NOTIFY_EMT	0x1
#define	CPC_COUNT_USER		0x2
#define	CPC_COUNT_SYSTEM	0x4

#define	KCPC_REQ_ALL_FLAGS	0x7
#define	KCPC_REQ_VALID_FLAGS(flags) \
		(((flags) | KCPC_REQ_ALL_FLAGS) == KCPC_REQ_ALL_FLAGS)

/*
 * CPC Capabilities
 */
#define	CPC_CAP_OVERFLOW_INTERRUPT	0x1
#define	CPC_CAP_OVERFLOW_PRECISE	0x2

/*
 * The only valid per-set flag is CPC_BIND_LWP_INHERIT, which must remain in
 * cpc_event.h for backwards compatibility.
 */
#define	CPC_SET_ALL_FLAGS	0x1
#define	CPC_SET_VALID_FLAGS(flags) \
		(((flags) | CPC_SET_ALL_FLAGS) == CPC_SET_ALL_FLAGS)

/*
 * These system call subcodes and ioctls allow the implementation of the
 * libcpc library to store and retrieve performance counter data.  Subject
 * to arbitrary change without notice at any time.  Do not invoke them
 * directly!
 */
#define	CPC_BIND		0
#define	CPC_SAMPLE		1
#define	CPC_INVALIDATE		2
#define	CPC_RELE		3
#define	CPC_EVLIST_SIZE		4
#define	CPC_LIST_EVENTS		5
#define	CPC_ATTRLIST_SIZE	6
#define	CPC_LIST_ATTRS		7
#define	CPC_IMPL_NAME		8
#define	CPC_CPUREF		9
#define	CPC_USR_EVENTS		10
#define	CPC_SYS_EVENTS		11
#define	CPC_NPIC		12
#define	CPC_CAPS		13
#define	CPC_ENABLE		14
#define	CPC_DISABLE		15
#define	CPC_PRESET		16
#define	CPC_RESTART		17

#define	_CPCIO_IOC	((((('c'<<8)|'p')<<8)|'c')<<8)

#define	CPCIO_BIND			(_CPCIO_IOC | 0x1)
#define	CPCIO_SAMPLE			(_CPCIO_IOC | 0x2)
#define	CPCIO_RELE			(_CPCIO_IOC | 0x3)

/*
 * Forward declarations.
 */
struct _kthread;
struct _kcpc_set;

#define	CPC_MAX_EVENT_LEN	512
#define	CPC_MAX_ATTR_LEN	32

typedef struct _kcpc_attr {
	char		ka_name[CPC_MAX_ATTR_LEN];
	uint64_t	ka_val;
} kcpc_attr_t;

typedef struct _kcpc_pic {
	uint_t			kp_flags;
	struct _kcpc_request	*kp_req;   /* request this PIC counts for */
} kcpc_pic_t;

typedef struct _kcpc_ctx kcpc_ctx_t;

struct _kcpc_ctx {
	struct _kcpc_set *kc_set;	/* linked list of all bound sets */
	uint32_t	kc_flags;
	kcpc_pic_t	*kc_pics;	/* pointer to array of per-pic data */
	hrtime_t	kc_hrtime;	/* gethrtime() at last sample */
	uint64_t	kc_vtick;	/* virtualized %tick */
	uint64_t	kc_rawtick;	/* last snapshot of tick/tsc */
	struct _kthread	*kc_thread;	/* thread this context is measuring */
	int		kc_cpuid;	/* CPU this context is measuring */
	kcpc_ctx_t	*kc_next;	/* Global list of all contexts */
};

typedef struct __cpc_args {
	void *udata1;
	void *udata2;
	void *udata3;
} __cpc_args_t;

#ifdef _KERNEL

#ifdef _MULTI_DATAMODEL
typedef struct __cpc_args32 {
	caddr32_t udata1;
	caddr32_t udata2;
	caddr32_t udata3;
} __cpc_args32_t;
#endif /* _MULTI_DATAMODEL */

#define	KCPC_LOG2_HASH_BUCKETS	6	/* => 64 buckets for now */
#define	CPC_HASH_BUCKETS		(1l << KCPC_LOG2_HASH_BUCKETS)
#define	CPC_HASH_CTX(ctx)		((((long)(ctx)) >> 7) &		       \
						(CPC_HASH_BUCKETS - 1))

/*
 * Context flags.
 */
#define	KCPC_CTX_FREEZE		0x1	/* => no sampling */
#define	KCPC_CTX_SIGOVF		0x2	/* => send signal on overflow */
#define	KCPC_CTX_NONPRIV	0x4	/* => non-priv access to counters */
#define	KCPC_CTX_LWPINHERIT	0x8	/* => lwp_create inherits ctx */
#define	KCPC_CTX_INVALID	0x100	/* => context stolen; discard */
#define	KCPC_CTX_INVALID_STOPPED 0x200	/* => invalid ctx has been stopped */

/*
 * PIC flags.
 */
#define	KCPC_PIC_OVERFLOWED	0x1	/* pic overflowed & requested notify */

#ifdef __sparc
extern uint64_t ultra_gettick(void);
#define	KCPC_GET_TICK ultra_gettick
#else
extern hrtime_t tsc_read(void);
#define	KCPC_GET_TICK tsc_read
#endif /* __sparc */

#define	PCBE_NAMELEN 30 /* Enough room for "pcbe." plus full PCBE name spec */

struct cpu;

extern uint_t cpc_ncounters;
extern kmutex_t	kcpc_ctx_llock[];	/* protects ctx_list */
extern kcpc_ctx_t *kcpc_ctx_list[];	/* head of list */
extern krwlock_t kcpc_cpuctx_lock;	/* lock for 'kcpc_cpuctx' below */
extern int	kcpc_cpuctx;		/* number of cpu-specific contexts */

extern void kcpc_invalidate_all(void);

extern void kcpc_passivate(void);
extern void kcpc_remote_stop(struct cpu *cp);
extern int kcpc_pcbe_tryload(const char *, uint_t, uint_t, uint_t);

#endif /* _KERNEL */

/*
 * Error subcodes.
 */
#define	CPC_INVALID_EVENT		1	/* Unknown event */
#define	CPC_INVALID_PICNUM		2	/* Requested PIC out of range */
#define	CPC_INVALID_ATTRIBUTE		3	/* Unknown attribute */
#define	CPC_ATTRIBUTE_OUT_OF_RANGE	4	/* Attribute val out of range */
#define	CPC_RESOURCE_UNAVAIL		5	/* Can't get needed resource */
#define	CPC_PIC_NOT_CAPABLE		6	/* PIC can't count this event */
#define	CPC_REQ_INVALID_FLAGS		7	/* Invalid flags in req(s) */
#define	CPC_CONFLICTING_REQS		8	/* Reqs in the set conflict */
#define	CPC_ATTR_REQUIRES_PRIVILEGE	9	/* Insufficient privs for atr */
#define	CPC_PBIND_FAILED		10	/* Couldn't bind to processor */

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_CPC_IMPL_H */