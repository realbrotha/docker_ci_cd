/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/usr/include/procinfo.h 1.58.1.2                         */
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
/* @(#)19       1.58.1.2  src/bos/usr/include/procinfo.h, sysproc, bos53Q, q2008_19D0 4/29/08 14:49:40 */
/*
 *   COMPONENT_NAME: SYSPROC
 *
 *   FUNCTIONS: 
 *
 *   ORIGINS: 27, 83
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1994
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 * LEVEL 1,  5 Years Bull Confidential Information
 */

#ifndef	_H_PROCINFO
#define	_H_PROCINFO

/*
 * You really can't use a header like this one without specifying
 * _ALL_SOURCE.  If you didn't, we try to let you get away with it,
 * but there are no guarantees!
 */
#ifndef _ALL_SOURCE
#define _ALL_SOURCE	/* to get rlimit64, rusage64 defs from resource.h */
#define _ALL_SOURCE_DEFINED
#endif

#include <sys/resource.h>
#include <sys/proc.h>
#include <sys/user.h>
#include <sys/wlm.h>

#ifdef _ALL_SOURCE_DEFINED
#undef _ALL_SOURCE
#endif

/*
 * Warning: the procinfo, userinfo, and uicredinfo structures represent
 * obsolete interfaces.  These would not compile correctly in 64-bit mode.
 */

#ifndef __64BIT__
struct	procinfo
{
	/* identification/authentication */
	unsigned long	pi_pid;		/* process ID */
	unsigned long	pi_ppid;	/* parent process ID */
	unsigned long	pi_sid;		/* session identifier */
	unsigned long	pi_pgrp;	/* process group */
	unsigned long	pi_uid;		/* real user ID	*/
	unsigned long	pi_suid;	/* saved user ID */

	/* scheduler information */
	unsigned long	pi_pri;		/* priority, 0 high, 31 low */
	unsigned long	pi_nice;	/* nice for priority, 0 to 39 */
	unsigned long	pi_cpu;		/* processor usage, 0 to 80 */

	/* process states are defined in <sys/proc.h>: */
	unsigned long	pi_stat;	/* process state */

	/* process flags are defined in <sys/proc.h>: */
	unsigned long	pi_flag;

	/* dispatcher fields */
	char		*pi_wchan;	/* wait channel */
	unsigned long	pi_wtype;	/* the wait type */

	/* miscellaneous */
	unsigned long	pi_adspace;	/* process address space */
	unsigned long	pi_majflt;	/* i/o page faults	 */
	unsigned long	pi_minflt;	/* non i/o page faults   */

	/* valid when the process is a zombie only */
	unsigned long	pi_utime;	/* this process user time */
	unsigned long	pi_stime;	/* this process system time */

	/* process statistics */
	unsigned long	pi_size;	/* size of image (pages) */
};

struct	userinfo
{
	/* credentials information */
	unsigned long	ui_luid;	/* login user id */
	unsigned long	ui_uid;		/* effective user identifier */
	unsigned long	ui_gid;		/* effective group identifier */

	/* accounting and profiling data */
	unsigned long	ui_start;	/* time at which process began */
	struct rusage	ui_ru;		/* this process' rusage info */
	struct rusage	ui_cru;		/* children's rusage info */

	/* resource limits info */
	struct rlimit	ui_rlimit[RLIM_NLIMITS];	/* resource limits */

	/* size of text */
	unsigned long	ui_tsize;	/* size of text */

	/* controlling tty info */
	unsigned long	ui_ttyp;	/* has a controlling terminal */
	unsigned long	ui_ttyd;	/* controlling terminal */
	unsigned long	ui_ttympx;	/*     "          "     channel */
	char	ui_comm[ MAXCOMLEN+1 ];		/* (truncated) program name */

	/* memory usage info */
	unsigned long	ui_drss;	/* data resident set size */
	unsigned long	ui_trss;	/* text resident set size */
	unsigned long	ui_dvm;		/* data virtual memory size */
	unsigned long	ui_prm;		/* percent real memory usage */
};

struct uicredinfo
{
	struct userinfo  uici_ui;	/* userinfo structure */
	struct ucred     uici_cred;	/* cred structure */
};
#endif /* __64BIT__ */


#define SSLEEP		1
#define SRUN		3

#define SNOWAIT		0
#define SWEVENT		1
#define SWLOCK		2
#define SWTIMER		3
#define SWCPU		4
#define SWPGIN		5
#define SWPGOUT		6
#define SWPLOCK		7
#define SWFREEF		8
#define SWMEM		9

/*
 * 		****	procsinfo structures	****
 *
 * The procsinfo structure in the kernel will match the 32-bit user mode one,
 * which is retained from AIX 4.2 for compatibility purposes.
 *
 * The new procsinfo64 structure in both kernel and user mode, as well as the
 * procsinfo structure in user 64-bit mode, is a new, expanded definition.
 *
 * Note that the rlimit and rusage embedded structures are affected by
 * compilation mode because of their use of 'long' declarations.
 * In the kernel, both generate equivalent to their 32-bit user counterparts.
 * All other expanded definition procsinfo fields carefully use data types that
 * are invariant over compilation mode.
 *
 * The procentry64 structure in both user and kernel mode is the new 64-bit
 * definition. The procsinfo and procsinfo64 strucures will still be supported
 * in 32-bit compilation mode, but not 64-bit mode. The getprocs() interface
 * will still be supported for 32-bit applications using the old structures,
 * but will not be exported as a system call for 64-bit applications.
 * All new applications wanting the new 64-bit process information must use
 * the new getprocs64() interface and the procentry64 structure.
 *
 */

#ifdef __64BIT__
/*
 * In 64-bit user mode, procsinfo is the 64-bit version.
 * The procsinfo64 structure must be kept in synch with it.
 */
struct procsinfo
{
	/* identification/authentication */
	pid_t 		pi_pid;		/* process ID */
	pid_t		pi_ppid;	/* parent process ID */
	pid_t 		pi_sid;		/* session identifier */
	pid_t 		pi_pgrp;	/* process group */
	uid_t 		pi_uid;		/* real user ID */
	uid_t 		pi_suid;	/* saved user ID */

	/* controlling tty info */
	pid_t 		pi_ttyp;	/* has a controlling terminal */
	dev32_t		pi_ttyd;	/* controlling terminal */
	uint 		pi_ttympx;	/*      "         "     channel */

	/* scheduler information */
	uint 		pi_nice;	/* nice for priority */
	uint 		pi_state;	/* process state -- from proc.h */
	uint 		pi_flags;	/* process flags -- from proc.h */
	uint 		pi_flags2;	/* process flags ext -- from proc.h */
	uint 		pi_thcount;	/* thread count */
	uint		pi_cpu;		/* first thread's tick count */
	uint		pi_pri;		/* first thread's priority */

	/* memory */
	uint		pi_adspace;	/* process address space */
	long long 	pi_majflt;	/* i/o page faults */
	long long 	pi_minflt;	/* non i/o page faults */
	long long 	pi_repage;	/* repaging count */
	long long 	pi_size;	/* size of image (pages) */

	/* valid when the process is a zombie only */
	uint		pi_r1;		/* reserved field */
	uint 		pi_utime;	/* this process user time */
	uint		pi_r2;		/* reserved field */
	uint		pi_stime;	/* this process system time */

	/* credentials information */
	struct ucred	pi_cred;

	/* accounting and profiling data */
	struct rusage64	pi_ru;		/* this process' rusage info */
	struct rusage64	pi_cru;		/* children's rusage info */
	long long	pi_ioch;	/* I/O character count  */
	long long 	pi_irss;	/* accumulator for memory integral */
	long long 	pi_start;	/* time at which process began */

	/* resource limits info */
	struct rlimit   pi_rlimit[RLIM_NLIMITS];	/* resource limits */

	/* file management */
	short		pi_cmask;	/* mask for file creation */
	unsigned int	pi_cdir;	/* current directory of process */
	unsigned int	pi_rdir;	/* root directory of process */
	unsigned int	pi_maxofile;	/* maximum u_ofile index in use */

	/* program name */
	char		pi_comm[MAXCOMLEN+1];	/* (truncated) program name */

	/* memory usage info */
	unsigned long long pi_drss;	/* data resident set size */
	unsigned long long pi_trss;	/* text resident set size */
	unsigned long long pi_dvm;	/* data virtual memory size */
	unsigned long long pi_prm;	/* percent real memory usage */
	unsigned long long pi_tsize;	/* size of text */
	unsigned long long pi_dsize;	/* current break value */
	unsigned long long pi_sdsize;	/* data size from shared library*/

	/* signal management */
	unsigned long long pi_signal[NSIG32];	/* disposition of sigs */
	char		   pi_sigflags[NSIG32];	/* sig action flags */
	sigset32_t	   pi_sig;	/* pending sigs */
	/* WLM information. 34+31=65 bytes, padded to 72 */
	char               pi_classname[2*(WLM_CLASSNAME_LENGTH+1)];
	char               pi_tag[WLM_TAG_LENGTH+1];

        /* pagesize information */
        char            pi_data_l2psize;     /* log2 of a proc's data pg sz */
        char            pi_text_l2psize;     /* log2 of a proc's text pg sz */
        char            pi_stack_l2psize;    /* log2 of a proc's stack pg sz */

	char            pi_pad4[4]; 

	/* other scheduler information */
	uint               pi_policy;           /* process policy */
	uint               pi_ppri;             /* process priority */

	/* project information */
	unsigned long long pi_subproj;
	int		   pi_projid;
	short		   pi_acctflags;
	/* struct size rounded to 1.5 K */
	char 		   pi_resvd[10];	/* reserve space for future use */
};

#else /* __64BIT__ */
/*
 * This procsinfo is for compatibility requests.
 * It's what you get in 32-bit user mode, and in kernel mode.
 *
 * Changing this structure should be avoided if at all possible;
 * otherwise you'll need to add another compatibility interface to getprocs and getuser.
 */
struct procsinfo
{
	/* identification/authentication */
	unsigned long	pi_pid;		/* process ID */
	unsigned long	pi_ppid;	/* parent process ID */
	unsigned long	pi_sid;		/* session identifier */
	unsigned long	pi_pgrp;	/* process group */
	unsigned long	pi_uid;		/* real user ID */
	unsigned long	pi_suid;	/* saved user ID */

	/* scheduler information */
	unsigned long	pi_nice;	/* nice for priority */
	unsigned long	pi_state;	/* process state -- from proc.h */
	unsigned long	pi_flags;	/* process flags -- from proc.h */
	unsigned long	pi_thcount;	/* thread count */

	/* memory */
	unsigned long	pi_adspace;	/* process address space */
	unsigned long	pi_majflt;	/* i/o page faults */
	unsigned long	pi_minflt;	/* non i/o page faults */
	unsigned long	pi_repage;	/* repaging count */
	unsigned long	pi_size;	/* size of image (pages) */

	/* valid when the process is a zombie only */
	unsigned long	pi_utime;	/* this process user time */
	unsigned long	pi_stime;	/* this process system time */

	/* credentials information */
	struct ucred	pi_cred;

	/* accounting and profiling data */
	unsigned long	pi_start;	/* time at which process began */
	struct rusage	pi_ru;		/* this process' rusage info */
	struct rusage	pi_cru;		/* children's rusage info */

	/* resource limits info */
	struct rlimit	pi_rlimit[RLIM_NLIMITS]; /* resource limits */

	/* size of text */
	unsigned long	pi_tsize;	/* size of text */

	/* controlling tty info */
	unsigned long	pi_ttyp;	/* has a controlling terminal */
	unsigned long	pi_ttyd;	/* controlling terminal */
	unsigned long	pi_ttympx;	/*	"	  "	channel */
        unsigned long   pi_dsize;       /* current break value */
        unsigned long   pi_sdsize;      /* data size from shared library */
	char		pi_comm[MAXCOMLEN+1]; /* (truncated) program name */

	/* memory usage info */
	unsigned long	pi_drss;	/* data resident set size */
	unsigned long	pi_trss;	/* text resident set size */
	unsigned long	pi_dvm;		/* data virtual memory size */
	unsigned long	pi_prm;		/* percent real memory usage */

	/* signal management */
	unsigned long	pi_signal[NSIG];/* disposition of sigs */
	char		pi_sigflags[NSIG];/* sig action flags */
	sigset_t	pi_sig;		/* pending sigs */

	/* file management */
        unsigned long   pi_cdir;        /* current directory of process */
        unsigned long   pi_rdir;        /* root directory of process */
	unsigned long	pi_maxofile;	/* maximum u_ofile index in use */

	long		pi_ioch;	/* I/O character count	*/

	/* project information */
	unsigned long long pi_subproj;
	int		   pi_projid;
	short		   pi_acctflags;
	short		   pi_pad5;
};
#endif /* __64BIT__ */

/*
 * procsinfo64 describes the 64-bit layout for all modes.
 * It's just like the 64-bit user mode procsinfo above,
 * but with explicit declaration of the rlimit and rusage fields
 * using rlimit64 and rusage64 structures.
 * Remember to keep procsinfo64 in synch with the 64-bit user mode procsinfo.
 */
struct procsinfo64
{
	/* identification/authentication */
	pid_t 		pi_pid;		/* process ID */
	pid_t		pi_ppid;	/* parent process ID */
	pid_t 		pi_sid;		/* session identifier */
	pid_t 		pi_pgrp;	/* process group */
	uid_t 		pi_uid;		/* real user ID */
	uid_t 		pi_suid;	/* saved user ID */

	/* controlling tty info */
	pid_t 		pi_ttyp;	/* has a controlling terminal */
#ifdef __64BIT__
	dev32_t		pi_ttyd;	/* controlling terminal */
#else
	dev_t		pi_ttyd;	/* controlling terminal */
#endif
	uint 		pi_ttympx;	/*      "         "     channel */

	/* scheduler information */
	uint 		pi_nice;	/* nice for priority */
	uint 		pi_state;	/* process state -- from proc.h */
	uint 		pi_flags;	/* process flags -- from proc.h */
	uint 		pi_flags2;	/* process flags ext -- from proc.h */
	uint 		pi_thcount;	/* thread count */
	uint		pi_cpu;		/* first thread's tick count */
	uint		pi_pri;		/* first thread's priority */

	/* memory */
	uint		pi_adspace;	/* process address space */
	__INTPAD(pi_pad1)               /* padding if required */
	long long 	pi_majflt;	/* i/o page faults */
	long long 	pi_minflt;	/* non i/o page faults */
	long long 	pi_repage;	/* repaging count */
	long long 	pi_size;	/* size of image (pages) */

	/* valid when the process is a zombie only */
	uint		pi_r1;		/* reserved field */
	uint 		pi_utime;	/* this process user time */
	uint		pi_r2;		/* reserved field */
	uint		pi_stime;	/* this process system time */

	/* credentials information */
	struct ucred	pi_cred;
	__INTPAD(pi_pad2)               /* padding if required */

	/* accounting and profiling data */
	struct rusage64	pi_ru;		/* this process' rusage info */
	struct rusage64	pi_cru;		/* children's rusage info */
	long long	pi_ioch;	/* I/O character count  */
	long long 	pi_irss;	/* accumulator for memory integral */
	long long 	pi_start;	/* time at which process began */

	/* resource limits info */
	struct rlimit64 pi_rlimit[RLIM_NLIMITS];	/* resource limits */

	/* file management */
	short		pi_cmask;	/* mask for file creation */
	unsigned int	pi_cdir;	/* current directory of process */
	unsigned int	pi_rdir;	/* root directory of process */
	unsigned int	pi_maxofile;	/* maximum u_ofile index in use */

	/* program name */
	char		pi_comm[MAXCOMLEN+1];	/* (truncated) program name */
	__INTPAD(pi_pad3)               /* padding if required */

	/* memory usage info */
	unsigned long long pi_drss;	/* data resident set size */
	unsigned long long pi_trss;	/* text resident set size */
	unsigned long long pi_dvm;	/* data virtual memory size */
	unsigned long long pi_prm;	/* percent real memory usage */
	unsigned long long pi_tsize;	/* size of text */
	unsigned long long pi_dsize;	/* current break value */
	unsigned long long pi_sdsize;	/* data size from shared library*/

	/* signal management */
#ifdef __64BIT__
	unsigned long long pi_signal[NSIG32];	/* disposition of sigs */
	char		   pi_sigflags[NSIG32];	/* sig action flags */
	sigset32_t	   pi_sig;	/* pending sigs */
#else
	unsigned long long pi_signal[NSIG];	/* disposition of sigs */
	char		   pi_sigflags[NSIG];	/* sig action flags */
	sigset_t	   pi_sig;	/* pending sigs */
#endif
	/* WLM information. 34+31=65 bytes, padded to 72 */
	char               pi_classname[2*(WLM_CLASSNAME_LENGTH+1)];
	char               pi_tag[WLM_TAG_LENGTH+1];

        /* pagesize information */
        char            pi_data_l2psize;     /* log2 of a proc's data pg sz */
        char            pi_text_l2psize;     /* log2 of a proc's text pg sz */
        char            pi_stack_l2psize;    /* log2 of a proc's stack pg sz */

	char            pi_pad4[4]; 

	/* other scheduler information */
	uint               pi_policy;           /* process policy */
	uint               pi_ppri;             /* process priority */

	/* project information */
	unsigned long long pi_subproj;
	int		   pi_projid;
	short		   pi_acctflags;
	
	/* struct size rounded to 1.5 K */
	char 		   pi_resvd[10];	/* reserve space for future use */
};


#define IS_PROC64(x)	((x)->pi_flags2 & S64BIT)
/*
 * The size of the fdsinfox section in core file can be obtained by
 * either  1] FD_HW_MARK(&(c_u.U_proc)) * sizeof(fdsinfox)
 * or      2] c_loader - c_fdsinfox
 * NOTE: c_xxxx fields are in core_dumpx structure in core.h.
 */
#define FD_HW_MARK(x)	((x)->pi_maxofile)

/*
 * For backward compatibility purpose, define OPEN_SHRT_MAX to have the 
 * same value of the old OPEN_MAX.
 * This allows the existing applications that use struct fdsinfo/fdsinfo64
 * continue to work in AIX 520 or later releases as long as the number of 
 * open file descriptors per process does not > SHRT_MAX.
 */ 
#define OPEN_SHRT_MAX   SHRT_MAX 


/* Struct fdsinfo_100K and fdsinfo64_100K are to allow information of more
 * than 32K file descriptors returned. 
 *
 * Define OPEN_100K_MAX to OPEN_MAX in the AIX 520 release.
 */
#define OPEN_100K_MAX   OPEN_MAX

struct fdsinfox
{
#ifdef __64BIT__
	unsigned int    fp;
#else
	struct file     *fp;
#endif
	unsigned short  flags;
	unsigned short  count;
};

struct fdsinfo
{
	struct fdsinfox pi_ufd[OPEN_SHRT_MAX];
};

/*
 * The fdsinfo_100K structure is identical to the fdsinfo structure above,
 * except that the number of possible file descriptor entries can grow up
 * to the new value of OPEN_MAX (>32K) in AIX 520.
 */
struct fdsinfo_100K
{
        struct fdsinfox pi_ufd[OPEN_100K_MAX];
};

/*
 * The fdsinfo_2000 structure is identical to the fdsinfo structure above,
 * except that the number of possible file descriptor entries is hard coded
 * to 2000 to match the limit from earlier releases of AIX.
 * This structure may be used when recompiling a getprocs() application
 * that requests fdsinfo output to avoid the costs of the much, much larger
 * new fdsinfo structure above.
 * Note that getprocs will fail (errno EMFILE) should it be compiled this
 * way and looking at a process with any file descriptors numbered 2000 or
 * above.
 */
struct fdsinfo_2000
{
	struct fdsinfox pi_ufd[2000];
};
/*
 * procentry64 provides size-invariant 64-bit process information.
 * This structure is to be used with getprocs64() interface available
 * to both 32 and 64 bit applications on AIX 4.4.
 */
struct procentry64
{
	/* identification/authentication */
	pid32_t		pi_pid;		/* process ID */
	pid32_t		pi_ppid;	/* parent process ID */
	pid32_t		pi_sid;		/* session identifier */
	pid32_t		pi_pgrp;	/* process group */
	uid_t 		pi_uid;		/* real user ID */
	uid_t 		pi_suid;	/* saved user ID */

	/* controlling tty info */
	pid32_t		pi_ttyp;	/* has a controlling terminal */
	uint		pi_pad0;	/* alignment padding */
	dev64_t		pi_ttyd;	/* controlling terminal */
	longlong_t	pi_ttympx;	/*      "         "     channel */

	/* scheduler information */
	uint 		pi_nice;	/* nice for priority */
	uint 		pi_state;	/* process state -- from proc.h */
	uint 		pi_flags;	/* process flags -- from proc.h */
	uint 		pi_flags2;	/* process flags ext -- from proc.h */
	uint 		pi_thcount;	/* thread count */
	uint		pi_cpu;		/* first thread's tick count */
	uint		pi_pri;		/* first thread's priority */

	/* file management */
	uint		pi_maxofile;	/* maximum u_ofile index in use */
	u_longlong_t	pi_cdir;	/* current directory of process */
	u_longlong_t	pi_rdir;	/* root directory of process */
	short		pi_cmask;	/* mask for file creation */
	short		pi_pad1;	/* alignment padding */

	/* program name */
	char		pi_comm[MAXCOMLEN+1];	/* (truncated) program name */

	/* memory */
	u_longlong_t 	pi_adspace;	/* process address space */
	longlong_t 	pi_majflt;	/* i/o page faults */
	longlong_t 	pi_minflt;	/* non i/o page faults */
	longlong_t 	pi_repage;	/* repaging count */
	longlong_t 	pi_size;	/* size of image (pages) */

	/* valid when the process is a zombie only */
	time64_t	pi_utime;	/* this process user time */
	time64_t	pi_stime;	/* this process system time */

	/* credentials information */
	cred_ext_t 	pi_cred;

	/* accounting and profiling data */
	struct trusage64 pi_ru;		/* this process' rusage info */
	struct trusage64 pi_cru;	/* children's rusage info */
	longlong_t	pi_ioch;	/* I/O character count  */
	longlong_t 	pi_irss;	/* accumulator for memory integral */
	time64_t 	pi_start;	/* time at which process began */

	/* resource limits info */
	struct rlimit64 pi_rlimit[RLIM_NLIMITS];	/* resource limits */

	/* memory usage info */
	u_longlong_t 	pi_drss;	/* data resident set size */
	u_longlong_t 	pi_trss;	/* text resident set size */
	u_longlong_t 	pi_dvm;		/* data virtual memory size */
	u_longlong_t 	pi_prm;		/* percent real memory usage */
	u_longlong_t 	pi_tsize;	/* size of text */
	u_longlong_t 	pi_dsize;	/* current break value */
	u_longlong_t 	pi_sdsize;	/* data size from shared library*/

	/* signal management */
	u_longlong_t 	pi_signal[NSIG64];/* disposition of sigs */
	uint		pi_sigflags[NSIG64];/* sig action flags */
	sigset64_t	pi_sig;		/* pending sigs */


	/* WLM information. 34+31=65 bytes, padded to 72 */
	char            pi_classname[2*(WLM_CLASSNAME_LENGTH+1)];
	char            pi_tag[WLM_TAG_LENGTH+1];        

        /* pagesize information */
        char            pi_data_l2psize;     /* log2 of a proc's data pg sz */
        char            pi_text_l2psize;     /* log2 of a proc's text pg sz */
        char            pi_stack_l2psize;    /* log2 of a proc's stack pg sz */

	char            pi_pad4[4]; 
                                    
	suseconds_t	pi_chk_utime;	/* user time at checkpoint  */
	suseconds_t	pi_chk_ctime;	/* child time at checkpoint  */

	/* other scheduler information */
	uint            pi_policy;           /* process policy */
	uint            pi_ppri;             /* process priority */

	/* loader segment for 64bit process */
	u_longlong_t    pi_adspace_ldr;
};

/*
 * fdsinfo64 describes the 64-bit layout in 64bit kernel.
 * This structure is to be used with getprocs64() interface available
 * to both 32 and 64bit applications running mainly with 64bit kernel.
 * This structure is 64bit size invariant and reflects the 64bit
 * kernel view of fdsinfo structure.
 */
struct fdsinfox64
{
	u_longlong_t	fp;		/* pointer to struct file	*/
	unsigned short  flags;		/* user fd table flags		*/
	unsigned short  count;		/* user fd reference count	*/
	unsigned int	pad;		/* reserved 			*/
};

struct fdsinfo64
{
	struct fdsinfox64 pi_ufd[OPEN_SHRT_MAX];
};

/*
 * The fdsinfo64_100K structure is identical to the fdsinfo64 structure above,
 * except that the number of possible file descriptor entries can grow up to
 * the new value of OPEN_MAX (>32K) in AIX 520.
 */
struct fdsinfo64_100K
{
        struct fdsinfox64 pi_ufd[OPEN_100K_MAX];
};


/* 
 * The thrdsinfo structure below adds and extends the sizes of fields
 * to better support 64-bit processes.  The same arrangement of thrdsinfo
 * structures (thrdsinfo, thrdsinfo64) is used as was used above for procsinfo.
 *
 * The 64-bit thrdsinfo can describe either a 32- or a 64-bit thread,
 * although one must look at the struct procsinfo to determine which.
 */

/*
 * This is the 32-bit compatibility structure for use with compatibility requests.
 *
 * Changing this structure should be avoided if at all possible;
 * otherwise you'll need to add another compatibility interface to getthrds.
 */
struct thrdsinfo
{
	/* identification */
	unsigned long	ti_tid;		/* thread ID */
	unsigned long	ti_pid;		/* process ID */

	/* scheduler information */
	unsigned long	ti_policy;	/* scheduling policy */
	unsigned long	ti_pri;		/* priority */
	unsigned long	ti_state;	/* thread state -- from thread.h */
	unsigned long	ti_flag;	/* thread flags -- from thread.h */
	unsigned long	ti_scount;	/* suspend count */
	unsigned long	ti_wtype;	/* type of thread wait */
	unsigned long	ti_wchan;	/* wait channel */
	unsigned long	ti_cpu;		/* processor usage */
	unsigned long	ti_cpuid;	/* processor on which I'm bound */

	/* signal management */
	sigset_t	ti_sigmask;	/* sigs to be blocked */
	sigset_t	ti_sig;		/* pending sigs */
	unsigned long	ti_code;	/* iar of exception */
	struct sigcontext *ti_scp;	/* sigctx location in user space */
	char		ti_cursig;	/* current/last signal taken */
	char		ti_pad1[3];	/* pad to word boundary */

	/* miscellaneous */
	unsigned long	ti_ticks;	/* # of ticks since dispatched */
	unsigned long	ti_dispct;	/* number of dispatches */
	unsigned long	ti_fpuct;	/* number of FP unavail ints. */
	unsigned long	ti_ustk;	/* user stack pointer */
	unsigned long	ti_resvd[5];	/* reserve space for future use */
};

/*
 * thrdsinfo64 describes the 64-bit layout for all modes.
 * Remember to keep thrdsinfo64 in synch with the 64-bit user thrdsinfo structure.
 */
struct thrdsinfo64 {
	/* identification */
#ifdef __64BIT__
	tid32_t		   ti_tid;	/* thread identifier */
#else
	tid_t		   ti_tid;	/* thread identifier */
#endif
	pid_t		   ti_pid;	/* process identifier */

	/* scheduler information */
	uint		   ti_pri;	/* current effective priority */
	uint		   ti_policy;	/* scheduling policy */
	uint		   ti_state;	/* thread state -- from thread.h */
	uint 		   ti_flag;	/* thread flags -- from thread.h */
	uint 		   ti_scount;	/* suspend count */
	uint 		   ti_wtype;	/* type of thread wait */
	unsigned long long ti_wchan;	/* wait channel */
	uint 		   ti_cpu;	/* processor usage */
	cpu_t 		   ti_cpuid;	/* processor on which I'm bound */
	cpu_t 		   ti_affinity;	/* processor on which I last ran */

	/* signal management */
#ifdef __64BIT__
	sigset32_t 	   ti_sigmask;	/* thread signal mask */
	sigset32_t 	   ti_sig;	/* pending signals */
#else
	sigset_t 	   ti_sigmask;	/* thread signal mask */
	sigset_t 	   ti_sig;	/* pending signals */
#endif
	unsigned long long ti_code;	/* iar of exception */
	unsigned long long ti_scp;	/* sigctx location in user space */
	char		   ti_cursig;	/* current/last signal taken */
	char		   ti_pad[7];	/* spare fields */
#ifdef __64BIT__
	sigset32_t	   ti_oldmask;	/* mask from before sigpause */
#else
	sigset_t	   ti_oldmask;	/* mask from before sigpause */
#endif
	unsigned long long ti_stkb;	/* current execution stack base */
	unsigned long long ti_ucontext;	/* current ucontext ptr */
	unsigned long long ti_sigsp;	/* special signal stack */
	unsigned long long ti_sigssz;	/* size of alternate signal stack */

	/* User thread management */
	unsigned long long ti_userdata;	/* user-owned data */
	unsigned long long ti_errnopp;	/* address of pointer to errno */
	unsigned long long ti_ustk;	/* user stack pointer from last sc */

	/* miscellaneous */
	uint 		   ti_ticks;	/* # of ticks since dispatched */
	uint		   ti_dispct;	/* number of dispatches */
	uint		   ti_fpuct;	/* number of FP unavail ints. */
	uint		   ti_watch;	/* ptrace watchpoint information */

	/* other scheduler information */
	uint               ti_nice;     /* thread nice value */

	uint 		   ti_resvd[6];	/* reserve space for future use */
	__INTPAD(ti_pad1)               /* padding if required */
};

/*
 * thrdentry64 provides size-invariant 64-bit thread information.
 * This structure is to be used with getthrds64() interface available
 * to both 32 and 64-bit applications on AIX 4.4.
 */
struct thrdentry64 {
	/* identification */
	tid64_t		   ti_tid;	/* thread identifier */
	pid32_t		   ti_pid;	/* process identifier */

	/* scheduler information */
	uint		   ti_pri;	/* current effective priority */
	uint		   ti_policy;	/* scheduling policy */
	uint		   ti_state;	/* thread state -- from thread.h */
	uint 		   ti_flag;	/* thread flags -- from thread.h */
	uint 		   ti_scount;	/* suspend count */
	uint 		   ti_wtype;	/* type of thread wait */
	uint 		   ti_cpu;	/* processor usage */
	cpu_t 		   ti_cpuid;	/* processor on which I'm bound */
	cpu_t 		   ti_affinity;	/* processor on which I last ran */
	uint		   ti_pad0;	/* alignment padding */
	unsigned long long ti_wchan;	/* wait channel */

	/* signal management */
	sigset64_t 	   ti_sigmask;	/* thread signal mask */
	sigset64_t 	   ti_sig;	/* pending signals */
	unsigned long long ti_code;	/* iar of exception */
	unsigned long long ti_scp;	/* sigctx location in user space */
	char		   ti_cursig;	/* current/last signal taken */
	char		   ti_pad[3];	/* spare fields */
	uint		   ti_flag2;	/* more flags */
	sigset64_t	   ti_oldmask;	/* mask from before sigpause */
	unsigned long long ti_stkb;	/* current execution stack base */
	unsigned long long ti_ucontext;	/* current ucontext ptr */
	unsigned long long ti_sigsp;	/* special signal stack */
	unsigned long long ti_sigssz;	/* size of alternate signal stack */

	/* User thread management */
	unsigned long long ti_userdata;	/* user-owned data */
	unsigned long long ti_errnopp;	/* address of pointer to errno */
	unsigned long long ti_ustk;	/* user stack pointer from last sc */

	/* miscellaneous */
	uint 		   ti_ticks;	/* # of ticks since dispatched */
	uint		   ti_dispct;	/* number of dispatches */
	uint		   ti_fpuct;	/* number of FP unavail ints. */
	uint		   ti_watch;	/* ptrace watchpoint information */

        /* accounting data */
        struct trusage64   ti_ru;       /* this thread's rusage info */

	/* other scheduler information */
	uint               ti_nice;     /* thread nice value */
        uint               ti_pad1;     /* alignment padding */
	struct timestruc64_t ti_start;  /* thread start time */
	uint 		   ti_resvd[2];	/* reserve space for future use */
};
/*
 * ti_watch flags
 */
#define T_WP			0x1
#define T_WP_SVC		0x2
#define T_WP_FAST		0x4

#endif	/* _H_PROCINFO */
