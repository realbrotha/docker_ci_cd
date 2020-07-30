/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53S src/bos/kernel/sys/sysinfo.h 1.31.1.2                           */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1988,1994              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)28     1.31.1.2  src/bos/kernel/sys/sysinfo.h, sysios, bos53S, s2008_35B7 8/21/08 16:32:25 */
/* sysinfo.h	5.2 87/01/09 18:25:51 */
#ifndef _H_SYSINFO
#define _H_SYSINFO
/*
 * COMPONENT_NAME: (SYSIOS) IO subsystems
 *
 * ORIGINS: 3, 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1994
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*  NOTE:  An assembly-language version of these structures exists
 *            in "sysinfo.m4".  BE SURE to update that file whenever
 *            <sys/sysinfo.h> is changed!!!
 *	      Also must keep sysinfo and sysinfo64 compatible !!
 */

#include <sys/types.h>
#include <sys/iostat.h>
#ifdef _KERNSYS
#include <sys/ppda.h>
#endif

struct sysinfo {
#define	CPU_NTIMES	4 	/* number of cpu times */
	long	cpu[CPU_NTIMES];   /* this array is updated every clock tick,
			     and keys off the state of the current running
			     process */
#define	CPU_IDLE	0 /* slot incremented whenever the 'wait' process
			     is the current running process */
#define	CPU_USER	1 /* slot incremented whenever the current running
			     process is executing in user mode */
#define CPU_KERNEL	2 /* slot incremented whenever the current running 
			     process is executing in kernel mode */
#define	CPU_WAIT	3 /* This slot is incremented whenever the current 
			     running process is waiting for a block i/o 
			     request to complete. Currently, whenever a 
			     process becomes blocked, it is put to sleep 
			     and a new process is made the current running 
			     process (i.e. processes no longer maintain 
			     control of the cpu when they become blocked). */
#define	sysfirst	bread	/* first sysinfo variable
			  	   sysfirst define should be maintained as 
				   first non-array sysinfo variable */
	long	bread;
	long	bwrite;
	long	lread;
	long	lwrite;
	long	phread;
	long	phwrite;
	long	pswitch;  /* field is incremented whenever 'curproc' (i.e.
			     current running process) changes. It is possible
			     that this field can wrap. */
	long	syscall;
	long	sysread;
	long	syswrite;
	long	sysfork;  /* field is incremented by one whenever a 'fork'
			     is done */
	long	sysexec;  /* field is incremented by one whenever a 'exec'
			     is done */
	long	runque;   /* every second the process table is scanned to
			     determine the number of processes that are
			     ready to run. If that count is > 0 the
			     current number of ready processes is added 
			     to 'runque' (i.e. 'runque' is a cummulative
			     total of ready processes at second intervals). */
	long	runocc;   /* whenever 'runque' is updated, 'runocc'
			     is incremented by 1 (can be used to compute
			     the simple average of ready processes). */
	long	swpque;   /* every second the process table is scanned to 
			     determine the number of processes that are
			     inactive because they are waiting to be paged
			     in. If that count is > 0 then the current number
			     of processes waiting to be paged in is added
			     to 'swpque' (i.e. 'swpque' is a cummulative
			     total of processes waiting to be swapped in
			     at second intervals). */
	long	swpocc;   /* whenever 'swpque' is updated, 'swpocc' is 
			     incremented by one (can be used to compute
			     the simple average of processes waiting to be 
			     paged in).*/
	long	iget;
	long	namei;
	long	dirblk;
	long	readch;
	long	writech;
	long	rcvint;
	long	xmtint;
	long	mdmint;
	struct	ttystat ttystat;
#define	rawch	ttystat.rawinch
#define	canch	ttystat.caninch
#define	outch	ttystat.rawoutch
	long	msg;
	long	sema;
	long    ksched;   /* field is incremented by one whenever a kernel
                             process is created */
	long    koverf;   /* field is incremented by one whenever an  attempt
			     is made to create a kernel process and:
				- the user has forked to their maximum limit
					       - OR -
				- the configuration limit of processes has been
				  reached */
	long    kexit;    /* field is incremented by one immediately after the
			     kernel process becomes a zombie */
	long    rbread;         /** remote read requests       **/
	long    rcread;         /** reads from remote cache    **/
	long    rbwrt;          /** remote writes              **/
	long    rcwrt;          /** cached remote writes       **/
	long	devintrs;	/* device interrupts */
	long	softintrs;	/* software interrupts */
	long	traps;		/* traps */
#define	syslast		traps	/* last sysinfo variable
				   syslast define should be maintained as 
				   last non-array sysinfo variable */
};

extern struct sysinfo sysinfo;

#ifdef _LONG_LONG

/* these fields have the same meaning as the corresponding fields
 * in sysinfo, but are size-invariant (64-bits long)
 */

struct sysinfo64 {
	long long	cpu[CPU_NTIMES];
	long long	bread;
	long long	bwrite;
	long long	lread;
	long long	lwrite;
	long long	phread;
	long long	phwrite;
	long long	pswitch; 
	long long	syscall;
	long long	sysread;
	long long	syswrite;
	long long	sysfork;
	long long	sysexec;
	long long	runque;
	long long	runocc;
	long long	swpque;
	long long	swpocc;
	long long	iget;
	long long	namei;
	long long	dirblk;
	long long	readch;
	long long	writech;
	long long	rcvint;
	long long	xmtint;
	long long	mdmint;
	struct	ttystat64 ttystat;
	long long	msg;
	long long	sema;
	long long	ksched;
	long long	koverf;
	long long	kexit;
	long long	rbread;
	long long	rcread;
	long long	rbwrt;
	long long	rcwrt;
	long long	devintrs;
	long long	softintrs;
	long long	traps;
};

extern struct sysinfo64 sysinfo64;

#endif

struct syswait {
	short	iowait;
	short	physio;
};

extern struct syswait syswait;

struct syserr {
	long	inodeovf;
	long	fileovf;
	long	textovf;
	long	procovf;
	long	sbi[5];
#define	SBI_SILOC	0
#define	SBI_CRDRDS	1
#define	SBI_ALERT	2
#define	SBI_FAULT	3
#define	SBI_TIMEO	4
};

extern struct syserr syserr;

struct cpuinfo {
	long	cpu[CPU_NTIMES];
	long	pswitch;
	long	syscall;
	long	sysread;
	long	syswrite;
	long	sysfork;
	long	sysexec;
	long	readch;
	long	writech;
	long	iget;
	long	namei;
	long	dirblk;
	long	msg;
	long	sema;
	long	bread;
	long	bwrite;
	long	lread;
	long	lwrite;
	long	phread;
	long	phwrite;

/* CPUINFO_SIZE is the size of the cpuinfo structure without the padding */
#define	CPUINFO_SIZE ((CPU_NTIMES + 19) * sizeof(long))

#ifdef __64BIT__
	char	fill[256-CPUINFO_SIZE];
#else
	char	fill[128-CPUINFO_SIZE];
#endif
};

#ifdef _KERNSYS
extern struct cpuinfo cpuinfo[MAXCPU];
#endif

/* 
 * The waitinfo structure is slightly different than the 
 * cpuinfo structure in that fields in the waitinfo structure
 * must be updated atomically, while the cpuinfo fields have
 * no such requirement.
 */

#ifdef _KERNEL
extern struct waitinfo *waitinfo;
struct waitinfo {
	long	uphyswait;
	long	iowait;
	long	wait;
	long	cpu_state[CPU_NTIMES];
	/* Following 3 'oncpu' fields must remain contiguous and
	 * in same order as the 'base' fields defined above. 
	 * The 'base' and 'oncpu' fields must be added together 
	 * to determine the wait state for a processor */ 
	long    uphyswait_oncpu;
	long    iowait_oncpu;
	long	wait_oncpu;
	char	fill[128-((CPU_NTIMES+6)*sizeof(long))];
};

struct cpustats {
        unsigned long long pcpu[4];		/* PURR cpu buckets */
        unsigned long long cswitches;		/* Context switches */
        unsigned long long cedes;		/* Cedes	    */
        unsigned long long confers;		/* Confers	    */
        unsigned long long tb_last; 		/* Last TimeBase read */
        unsigned long long purr_last; 		/* Last PURR read   */
        unsigned long long intr_purr;		/* PURR spent in interrupts */
        unsigned long long tot_disptime;	/* Partition dispatch time */ 
        unsigned long long idle_time;		/* True idle time    */
        unsigned long long iowait_time;         /* True iowait time  */
        /* the following process times do not contain interrupt time */
        unsigned long long uprocess_system_time; /* system time of user procs */
        unsigned long long uprocess_time;       /* process time of user procs */
        unsigned long long sprocess_time;       /* process time of kernel proc*/

	/* per-cpu redispatch counters... */
	unsigned long long redisp_s0;		/* redispatches on same lcpu */
	unsigned long long redisp_s1;		/* on same physical cpu(CORE) */
	unsigned long long redisp_s2;		/* same chipset,but not pcpu */
	unsigned long long redisp_s3;		/* same MCM,but not on chipset*/
	unsigned long long redisp_s4;		/* other MCMs on our CEC/Plane*/
	unsigned long long redisp_s5;		/* outside our CEC/Plane */

        int 		   missed_ticks;	/* Missed Ticks	     */ 

	/* per-cpu migration counters... */
	unsigned int	   mig_push_count;	/* due to starv load balance */
						/* dispatches from GRQ, 
						 * outside our MCM */
	unsigned long long mig_s4_grq_count;
						/* migrations due to idle steal
						 * outside our MCM */
	unsigned long long mig_s4_pull_count;

	unsigned long long nivcsws;		/* involuntary AIX cswitches */
	unsigned long long nvcsws;		/* voluntary AIX cswitches */

	unsigned int	   stealable;		/* unbound threads on this cpu*/
	unsigned int	   unstealable;		/* bound threads on this cpu */
	
	unsigned long long memfault_count;	/* number of Virtual Partition 
						   Page Faults */
	unsigned long long memfault_accum;	/* Time to resolv those Faults*/


        unsigned long long idle_stolen_purr;    /* ticks while idle(waitproc) */
        unsigned long long idle_stolen_spurr;   
        unsigned long long busy_stolen_purr;    /* ticks while busy           */
        unsigned long long busy_stolen_spurr;   

        unsigned long long idle_donated_purr;   /* donated in H_CEDE          */
        unsigned long long idle_donated_spurr;  
        unsigned long long busy_donated_purr;   /* due hypervisor event        */
        unsigned long long busy_donated_spurr;
        unsigned long long idle_purr;		/* Idle PURR    */

	u_longlong_t spurrcpu[4];		/* SPURR cpu buckets */
	u_longlong_t spurr_last;		/* Last SPURR read   */
	u_longlong_t intr_spurr;		/* SPURR spent in interrupts */
	u_longlong_t tot_spurr_disptime;	/* Partition dispatch time in 
						   SPURR tics */
	u_longlong_t spurr_idle_time;		/* True idle time in SPURR   */
	u_longlong_t spurr_iowait_time;		/* True iowait time in SPURR */
	/* 
	 * The following process times do not contain interrupt time and all
	 * these accumulated charges are SPURR based. 
	 */
	u_longlong_t spurr_uprocess_system_time; /* system time of user procs */
	u_longlong_t spurr_uprocess_time; /* process time of user procs */
	u_longlong_t spurr_sprocess_time; /* process time of kernel procs */
	/*
	 * Acculmuation of "chopped off" ticks per category in CAPPURR mode when
	 * turbo accounting option is disabled. 
	 */
	u_longlong_t spurr_turbo_boosted_time[4];
	char	     spurr_version;	  /* 0 if CPU does not have SPURR */

	char  filler[71];                       /* 128b cache aligned */
};

int kget_cpustats(short cpuid, struct cpustats *stats);

#ifdef _KERNSYS
extern struct cpustats *cpustats;
#endif


#endif

#endif /* _H_SYSINFO */
