/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53D src/bos/kernel/sys/encap.h 1.22                                 */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1993,2005          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)28	1.22  src/bos/kernel/sys/encap.h, sysproc, bos53D, d2005_08A1 2/10/05 18:45:39 */
/*
 *   COMPONENT_NAME: SYSPROC
 * 
 *   FUNCTIONS:
 *
 *   ORIGINS: 27, 83
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1993
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 * LEVEL 1,  5 Years Bull Confidential Information
 */


#ifndef _H_ENCAP
#define _H_ENCAP

/*
 * This macro is not intended for kernel extensions.
 */
#ifdef _KERNSYS
#define IS_MASTERCPU()	(CPUID == master_CPU)
#endif

#ifdef _KERNEL

#include <sys/types.h>
#include <sys/sysinfo.h>

/*
 * Logical cpu id of the master is internal to kernel
 * and kernel extensions. It is not exported to the world.
 */
extern	cpu_t	master_CPU;
extern	cpu_t	high_cpuid;	/* highest logical cpuid ever online */
extern	cpu_t	b2lcpu(cpu_t);	/* from bindid to logical cpuid */
extern	cpu_t	l2bcpu(cpu_t);	/* from logical cpuid to bindid */
extern	cpu_t	my_lcpu(void);	/* provide callers logical cpuid */

/* Structure used by getctty/setctty routines */
struct ttyinfo
{
        pid_t          *ti_ttysid;      /* pid of session leader */
        pid_t          *ti_ttyp;        /* pid of process group leader */
        dev_t           ti_ttyd;        /* controlling tty device */
        off_t           ti_ttympx;      /* mpx value for controlling tty */
        unsigned        *ti_ttys;       /* ptr to t_state in tty struct */
        int32long64_t	ti_ttyid;       /* tty id */
        int             (*ti_ttyf)();   /* tty query function pointer */
};

/* flags for rusage_incr function */
#define RUSAGE_MSGSENT	1
#define RUSAGE_MSGSND	1
#define RUSAGE_MSGRCV	2
#define RUSAGE_INBLOCK	3
#define RUSAGE_OUTBLOCK	4
#define RUSAGE_NSIGNALS	5
#define RUSAGE_NVCSW	6
#define RUSAGE_NIVCSW	7

/* encapsulations routines */
#ifdef _NO_PROTO
void	  getctty();
pid_t	  getsid();
boolean_t is_blocked();
boolean_t is_caught();
boolean_t is_ignored();
int	  is_orphan();
boolean_t is_pgrp();
boolean_t is_pgrpl();
boolean_t is_sessl();
int	  kpidstate();
void	  limit_sigs();
void	  sigsetmask();
void	  rusage_incr();
void	  setctty();
int	  query_proc_info();
void	  getsi64();
void * 	  get_tgraphics();
void *	  get_asynchio_p();
void *	  get_asynchio_t();
int	  pidsig_qx();
struct ksiginfo *ks_alloc();
void	  ks_free();
int       kgetpname();
#else /* _NO_PROTO */
void	  getctty(struct ttyinfo *);
pid_t	  getsid(pid_t);
boolean_t is_blocked(int);
boolean_t is_caught(int);
boolean_t is_ignored(int);
int	  is_orphan(pid_t);
boolean_t is_pgrp(pid_t);
boolean_t is_pgrpl(pid_t);
boolean_t is_sessl(pid_t);
int	  kpidstate(pid_t);
void	  limit_sigs(sigset_t *, sigset_t *);
void	  sigsetmask(sigset_t *);
void	  rusage_incr(int, unsigned);
void	  setctty(struct ttyinfo *);
int	  query_proc_info(int);
void	  getsi64(struct sysinfo64 *);
void * 	  get_tgraphics(void);
void *	  get_asynchio_p(pid_t id);
void *	  get_asynchio_t(tid_t id, int ptr);
int	  pidsig_qx(pid_t, struct ksiginfo *);
struct ksiginfo *ks_alloc(int signo, int code, unsigned long long value,
				int flags);
void	  ks_free(struct ksiginfo *);
int       kgetpname(char *, size_t *);
#endif /* _NO_PROTO */

/* type values for query_proc_info() */
#define QPI_XPG_SUS_ENV		0	/* returns TRUE if calling process
					 * has SPEC 1170 environment active
					 */
#define QTI_FUNNELLED		1     	/* returns TRUE if calling thread
					 * is funnelled 
					 */
/* Return values of kpidstate function, depending on p_stat */
#define	KP_NOTFOUND	1		/* SNONE is set in p_stat */
#define	KP_INITING	2		/* SIDL  is set in p_stat */
#define	KP_EXITING	3		/* SZOMB is set in p_stat */
#define	KP_STOPPED	4		/* SSTOP is set in p_stat */
#define	KP_ALIVE	0		/* process is alive */

#endif

#endif /* _H_ENCAP */
