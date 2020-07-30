/*
 * Copyright 2006 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_SYS_EXACCT_IMPL_H
#define	_SYS_EXACCT_IMPL_H

#pragma ident	"@(#)exacct_impl.h	1.8	06/06/02 SMI"

#ifdef	__cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/zone.h>

/*
 * Setting the exacct error code.  libexacct provides more detailed codes for
 * identifying causes of operational failure; the kernel doesn't use this
 * facility, since the kernel operations can't fail.  (KM_SLEEP allocations,
 * for instance.)
 */
#ifdef _KERNEL
#define	EXACCT_SET_ERR(x)
#else /* _KERNEL */
extern void exacct_seterr(int);
#define	EXACCT_SET_ERR(x)   exacct_seterr(x)
#endif /* _KERNEL */

typedef struct task_usage {
	hrtime_t tu_utime;	/* user time */
	hrtime_t tu_stime;	/* system time */

	uint64_t tu_minflt;	/* minor faults */
	uint64_t tu_majflt;	/* major faults */
	uint64_t tu_sndmsg;	/* messages sent */
	uint64_t tu_rcvmsg;	/* messages received */
	uint64_t tu_ioch;	/* characters read and written */
	uint64_t tu_iblk;	/* input blocks */
	uint64_t tu_oblk;	/* output blocks */
	uint64_t tu_vcsw;	/* voluntary context switches */
	uint64_t tu_icsw;	/* involuntary context switches */
	uint64_t tu_nsig;	/* signals received */
	uint64_t tu_nswp;	/* swaps */
	uint64_t tu_nscl;	/* system calls */
	uint64_t tu_startsec;	/* start time (seconds) */
	uint64_t tu_startnsec;	/* start time (nanoseconds) */
	uint64_t tu_finishsec;	/* finish time (seconds) */
	uint64_t tu_finishnsec;	/* finish time (nanoseconds) */
	taskid_t tu_anctaskid;	/* ancestor task's ID */
} task_usage_t;

typedef struct proc_usage {
	uint64_t pu_minflt;	/* minor faults */
	uint64_t pu_majflt;	/* major faults */
	uint64_t pu_sndmsg;	/* messages sent */
	uint64_t pu_rcvmsg;	/* messages received */
	uint64_t pu_ioch;	/* characters read and written */
	uint64_t pu_iblk;	/* input blocks */
	uint64_t pu_oblk;	/* output blocks */
	uint64_t pu_vcsw;	/* voluntary context switches */
	uint64_t pu_icsw;	/* involuntary context switches */
	uint64_t pu_nsig;	/* signals received */
	uint64_t pu_nswp;	/* swaps */
	uint64_t pu_nscl;	/* system calls */
	uint64_t pu_utimesec;	/* user time (seconds) */
	uint64_t pu_utimensec;	/* user time (nanoseconds) */
	uint64_t pu_stimesec;	/* system time (seconds) */
	uint64_t pu_stimensec;	/* system time (nanoseconds) */
	uint64_t pu_startsec;	/* start time (seconds) */
	uint64_t pu_startnsec;	/* start time (nanoseconds) */
	uint64_t pu_finishsec;	/* finish time (seconds) */
	uint64_t pu_finishnsec;	/* finish time (nanoseconds) */
	uint64_t pu_mem_rss_avg;	/* average RSS (K) */
	uint64_t pu_mem_rss_max;	/* peak RSS (K) */

	pid_t pu_pid;		/* process ID */
	uid_t pu_ruid;		/* user ID */
	gid_t pu_rgid;		/* group ID */
	projid_t pu_projid;	/* project ID */
	taskid_t pu_taskid;	/* task ID */
	uint32_t pu_acflag;	/* accounting flags */
	char *pu_command;	/* command string */
	uint32_t pu_major;	/* major number of controlling tty */
	uint32_t pu_minor;	/* minor number of controlling tty */
	int pu_wstat;		/* wait() status */
	pid_t pu_ancpid;	/* ancestor process's ID */
	char pu_zonename[ZONENAME_MAX];	/* Zone name */
	char pu_nodename[_SYS_NMLN];
} proc_usage_t;

typedef struct flow_usage {
	uint32_t fu_saddr[4];	/* source address */
	uint32_t fu_daddr[4];	/* remote address */
	uint8_t fu_protocol;	/* protocol type */
	uint16_t fu_sport;	/* source port */
	uint16_t fu_dport;	/* remote port */
	uint8_t fu_dsfield;	/* DS field */
	uint32_t fu_nbytes;	/* number of bytes (incl. IP header) */
	uint32_t fu_npackets;	/* number of packets */
	uint64_t fu_ctime;	/* creation time for this item */
	uint64_t fu_lseen;	/* when the last item of this desc. was seen */
	projid_t fu_projid;	/* project ID */
	uid_t fu_userid;		/* user ID */
	boolean_t fu_isv4;	/* to extract the correct l/r-addr */
	char *fu_aname;		/* action instance name */
} flow_usage_t;

extern void exacct_order16(uint16_t *);
extern void exacct_order32(uint32_t *);
extern void exacct_order64(uint64_t *);

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_EXACCT_IMPL_H */
