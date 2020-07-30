/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/kernel/sys/aacct.h 1.37.2.1                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2003,2006          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)75       1.37.2.1  src/bos/kernel/sys/aacct.h, sysproc, bos53L, l2006_41A1 10/5/06 18:13:59 */
#ifndef _H_AACCT
#define _H_AACCT

#include <sys/types.h>
#include <sys/proc.h>		/* struct proc_counts */

/*
 * The projid_t has three components: a type, an origin field, and an id.
 * The type is the upper nibble and is read-only.  The origin is the next
 * nibble and is also read-only.  The id is the lower 24 bits, resulting
 * in valid project ids in the range 0x0 - 0x00FFFFFF.  Actually, project
 * id 0 is the default System Project, so the first user defined project 
 * ID that can be assigned is 1. 
 *
 * The design allows projects to be defined and used from multiple sources.
 * Locally defined projects may be used in conjunction with projects stored
 * in LDAP.  Application defined projects may also be used.  It is assumed
 * that projects are unique and that the origin does not need to be specified
 * when making an assignment.  It is sufficient to specify the project by
 * name or number.  When performing a lookup, the system uses the first
 * project definition that matches. 
 */
#define PROJIDMASK	0x00FFFFFF
#define PROJORIGMASK	0x0F000000
#define PROJORIGLOCAL	0x00000000
#define PROJORIGAPI	0x01000000
#define PROJORIGLDAP	0x02000000
#define PROJTYPEMASK	0xF0000000
#define PROJIDUIDREL	0x10000000
#define PROJIDGIDREL	0x20000000

#define PROJTYPESHIFT   28
#define PROJORIGSHIFT  	24

#define PROJID(id)      ((id) & PROJIDMASK)
#define PROJORIG(id)    (((id) & PROJORIGMASK) >> PROJORIGSHIFT)
#define PROJTYPE(id)    (((id) & PROJTYPEMASK) >> PROJTYPESHIFT)

/* Project origins */
#define ORIGIN_PDF	0
#define ORIGIN_API	1
#define ORIGIN_LDAP	2

/* Default project */
#define SYSPROJNAME 	"System"
#define SYSPROJNAMELEN 	7
#define SYSPROJID	0

/* Project identifier ranges */
#define PROJIDMAX	PROJIDMASK	
#define PROJIDMINU	1		/* Minimum User Defined Project */
#define PROJIDMIN	0 
 
/*
 * Project related definitions
 */
#define PROJNAMELEN     32
typedef int projid_t;

/* 
 * Project flag values
 */
#define PROJFLAGS_AGGR	0x1
#define PROJFLAGS_API	0x2
#define PROJFLAGS_LDAP	0x4
#define PROJFLAGS_PDF	0x8
#define PROJFLAGS_ALL  	(PROJFLAGS_AGGR | PROJFLAGS_LDAP | \
 			 PROJFLAGS_API  | PROJFLAGS_PDF)

/* 
 * Project flag macros 
 */
#define PROJISAPI(flags)        ((flags) & PROJFLAGS_API)
#define PROJISLDAP(flags)       ((flags) & PROJFLAGS_LDAP)
#define PROJISPDF(flags)        (!PROJISAPI((flags)) && !PROJISLDAP((flags)))
#define PROJISAGGR(flags)       ((flags) & PROJFLAGS_AGGR)

struct project {
        char     name[PROJNAMELEN];
        projid_t id;
        int      flags;
};

/*
 * These APIs updated the specified project repository and the kernel, 
 * if necessary.  The kernel is updated, if the project repository 
 * has been loaded into the kernel.
 */
int projdballoc(void **handle);
int projdbfree(void *handle);
int projdbsinit(void **handle, int *n_handles, int mode);
int projdbtype(void *handle);
int projdbfinit(void *handle, char *file, int mode);
int addprojdb(void *handle, struct project *proj, char *comment);
int rmprojdb(void *handle, struct project *proj, int flag);
int getfirstprojdb(void *handle, struct project *proj, char *comm);
int getnextprojdb(void *handle, struct project *proj, char *comm);
int getprojdb(void *handle, struct project *proj, int flag);
int getprojdbs(void **handles, int *no_handles, struct project *proj, int flag);
int chprojattrdb(void *handle, struct project *proj, int cmd);

/* flag parameter values for rmproj(), getproj(), rmprojdb() and getprojdb() */
#define PROJ_NAME	1
#define PROJ_NUM	2

/* cmd parameter values for chprojattrdb() and chprojattr() */
#define PROJ_ENABLE_AGGR	1
#define PROJ_DISABLE_AGGR	0

/* return codes for projdbtype */
#define PROJ_ISLDAP	1
#define PROJ_ISPDF	2

/*
 * These APIs are intended for high level job schedulers that wish to
 * assign their own project codes.  These APIs do not update the project 
 * repository.  They are designed to interface directly with the kernel, 
 * so project assignments may be performed without having to explicitly 
 * load the project repository.  Since these APIs bypass the registry, 
 * applications that post process accounting data and which rely on the 
 * registry to associate project names with project numbers may not 
 * function properly.  However, they should be able to display the 
 * project number. 
 */
int addproj(struct project *proj);
int chprojattr(struct project *proj, int cmd);
int rmproj(struct project *proj, int flag);
int getproj(struct project *proj, int flag);
int getprojs(struct project *proj, int * nelems);
int proj_execve(char *path, char *const arg[], 
		char *const env[], projid_t proj, int force);
int getsubproj(unsigned long long *subproj);
int setsubproj(unsigned long long *subproj);
projid_t getmyproj(void);
int setmyproj(projid_t id);

/*
 * The tusage structure is for use by ARM transactions, and contains the
 * usage statistics these transactions can report.  It can optionally be
 * passed to acct_put for inclusion in an accounting transaction record.
 */
struct tusage {
	unsigned long long tu_cpu;	/* cpu used, in u-secs */
	unsigned long long tu_res1;
};

#define TUSAGE_ZERO(TU) {			\
		(TU).tu_cpu  = 0;		\
		(TU).tu_res1 = 0; }

#define TUSAGE_ADD(TU1, TU2) {			\
		(TU1).tu_cpu  += (TU2).tu_cpu;	\
		(TU1).tu_res1 += (TU2).tu_res1; }

#define TUSAGE_SUB(TU1, TU2) {			\
		(TU1).tu_cpu  -= (TU2).tu_cpu;	\
		(TU1).tu_res1 -= (TU2).tu_res1; }

#ifdef _KERNEL

/* get cpu usage of current thread. */
u_longlong_t acct_get_usage(struct tusage *);	

/*
 * The kernel exports aacct_flags to indicate if accounting
 * is enabled overall.
 *
 * Knowledge of which individual transactions are enabled is passed
 * to registered interval callout routines.
 *
 * Note that the value of aacct_flags is returned by the ACC_QUERY_STATE
 * option of acctctl, so the flag definitions are made visible outside the
 * kernel even though the flag word itself is not.
 */

extern int aacct_flags;
#endif


/*
 * These flags identify global accounting state
 */ 
#define AACCT_ON	0x00000001	/* accounting enabled */
#define AACCT_LOADED	0x00000002	/* kernel extension loaded */
#define AACCT_SYS_INT	0x00000004	/* system interval is active */
#define AACCT_PROC_INT	0x00000008	/* process interval is active */
#define AACCT_AGGR_PROC	0x00000010	/* process aggregation is enabled */
#define AACCT_AGGR_KE	0x00000020	/* kernext aggregation is enabled */
#define AACCT_AGGR_ARM	0x00000040	/* ARM aggregation is enabled */

#ifdef _KERNEL

#define ACCT_ENABLED	(aacct_flags & AACCT_ON)

/*
 * The acct_put routine is exported from the kernel, so it can always be
 * called whether advanced accounting is active or loaded or not.
 *
 * This service builds the common header from its parameters and values
 * in curproc, appends the specific transaction data to create an accounting
 * transaction record, and schedules it to be written to an accounting file.
 *
 * The projid may be	specified directly if known,
 *			set to PROJID_SYSTEM for system interval transactions
 *			set to PROJID_UNKNOWN to request curproc's project ID
 *
 * If tusage is non-NULL, a common subheader will be generated.
 *
 * The possible flag #defines are below.
 */
void acct_put(	int trid,		/* transaction ID */
		int flags,		/* flags, eg aggregation */
		int projid,		/* project ID */
		struct tusage * usage,	/* transaction usage values */
		void *trdata,		/* transaction-specific data */
		int tr_len);		/* size of trdata */

#define	PROJID_SYSTEM	0	/* projid value for system interval trans's */
#define PROJID_NOACCT	-1	/* projid value for no accounting */
#define PROJID_UNKNOWN	-2	/* get projid value from curproc */

/*
 * The follow flag value(s) are for the public interface to acct_put,
 * and must all be defined in the right half of the integer.
 * The left half of the integer is reserved for internal use.
 */
#define	ACCT_PUT_DIRECT	0x00000001	/* bypass aggregation */

/*
 * Kernel services to register/unregister handlers for interval accounting.
 *
 * Only up to 15 characters will be kept from the transname parameter.
 */
int acct_interval_register(	int transid,
				int cmds,
				int (*handler)(int transid, int cmd, void *arg),
				void *arg,
				unsigned long *h_token,
				char *transname);

/*
 * These are the possible "cmds" that will trigger callout to the registered
 * handler.  If new cmds need to be implemented, be sure to
 *
 * 1. include them in ACCT_CMD_ALL
 * 2. assign consecutive bits from the right (low order).
 *
 * The upper half of the cmds integer is reserved for internal system use.
 */
#define ACCT_CMD_ENABLE		1
#define ACCT_CMD_DISABLE	2
#define ACCT_CMD_INTERVAL	4
#define ACCT_CMD_FSWITCH	8

#define ACCT_CMD_ALL	(ACCT_CMD_ENABLE | ACCT_CMD_DISABLE | \
		       ACCT_CMD_INTERVAL | ACCT_CMD_FSWITCH)

int acct_interval_unregister(unsigned long h_token);

/*
 * Special atomic increment and clear services are provided to allow
 * machine independent updating of unsigned long long values.
 * However, only 63 bit values are guaranteed.
 *
 * 64bit kernel - can use ldarx/stdcx in the natural way, providing a
 *		very efficient 64bit service.
 *
 * 32bit kernel on 64bit hardware - can use ldarx/stdcx in a disabled
 *		section to prevent interrupts, providing a moderately
 *		efficient 64bit service.
 *
 * 32bit kernel on 32bit hardware - must use the high-order bit of the
 *		doubleword as an interlock with sync and isync, providing
 *		a pretty inefficient 63bit service.
 *
 * All services return the previous value of the unsigned long long.
 * Or as many bits as we can depending on the platform involved.
 * The increment services will only perform an incrment if accounting
 * is enabled, since this is a potentially expensive operation.
 *
 * The acct_add_LL and acct_zero_LL services are intended for kernel
 * extensions maintaining their own system data whose addresses they know.
 */
unsigned long long acct_add_LL(unsigned long long *, unsigned int);
unsigned long long acct_zero_LL(unsigned long long *);

/*
 * The acct_add_proc service is intended for kernel extension extensions
 * that need to update the non-sysproc process-based counters in the
 * proc structure (which they are not allowed to address directly).
 * The indices to use are #defined below with the tran_proc structure.
 * For example, to update the local I/O count, use the TRP_LOCAL_IO index.
 */
unsigned long long acct_add_proc(unsigned int counter_index, unsigned int incr);

/* Get calling process' project id */
projid_t acct_get_projid(void);

/* Get project id for the given attributes */
projid_t acct_classify(char *appname, uid_t uid, gid_t gid);

#endif	/* _KERNEL */

/*
 * Kernel transaction IDs are defined here, and implicitly mapped to
 * their purpose by choosing a meaningful name for the #define value.
 * This name should be of the form TRID_purpose, where "purpose" is
 * chosen to identify the type of transaction.
 *
 * Also add the "purpose" as an array assignment in the ACCT_NAME macro.
 *
 * When a transaction ID is defined here, the corresponding structure
 * mapping that transaction's specific data must also be defined in the
 * next section of this header file.  The structure name should be
 * tran_purpose, where "purpose" would be identical to the corresponding
 * "purpose" in the transaction ID name.
 */
#define	TRID_pad	0	/* reserved for file padding */
#define	TRID_proc	1	/* process (non-aggregated) transaction */
#define TRID_agg_proc	2	/* aggregated process transaction */
#define TRID_agg_app	3	/* agregated application use */
#define TRID_cpumem	4	/* system configuration and activity */
#define	TRID_policy	5	/* policy change */
#define	TRID_file	6	/* file system activity */
#define TRID_netif	7	/* network interface activity */
#define TRID_disk	8	/* physical disk volume activity */
#define TRID_lostdata	9	/* cpu lost data record */
#define TRID_vscsi_target 10    /* virtual scsi target adapter */
#define TRID_vscsi_client 11    /* virtual scsi client adapter */
#define	TRID_agg_ke	  12	/* 3rd party common aggregation record */
#define	TRID_arm_applenv  13	/* ARM application instance record */
#define	TRID_arm_trenv	  14	/* ARM transaction definition record */
#define	TRID_arm_tran	  15	/* ARM transaction instance record */
#define	TRID_agg_arm      16	/* ARM aggregate transaction record */
#define TRID_project	  17	/* project definitions */

#define TRID_KERN_MAX	127	/* highest number for base kernel trans */
#define TRID_MAX	255	/* highest allowed transaction ID */

/*
 * Each accounting file will contain a simple header in the first page
 * of the file, with nothing else in this page.  Normal accounting records 
 * will start in the second page.  The header is simply:
 */
struct acct_file_header {
	unsigned int afh_version;		/* just in case... */
	unsigned int afh_flags;			/* ... */
	unsigned long long afh_offset;		/* current file pointer */
	unsigned long long afh_file_size;	/* amount of space in file */
	unsigned int afh_state;			/* for debugging only */
	unsigned int afh_id;			/* for debugging only */
	unsigned long long afh_time_first;	/* open date, in seconds */
	unsigned long long afh_time_last;	/* close date, maybe */
	char afh_system_id[32];			/* uname -u */
	char afh_system_model[32];		/* uname -M */
	char afh_host_name[32];			/* uname -n */
	char afh_partition_name[256];		/* uname -L - Name */
	char afh_partition_number[4];		/* uname -L,  -1 if not LPAR */
	char afh_recover_turbo_cputime;		/* =1 if turbo chg recovered */
	char afh_PAD[3];
	unsigned long long afh_reserved[461];	/* pad to full page */
};

/*
 * Values for afh_recover_turbo_cputime:
 *
 */
				/* if turbo_acct (SMIT option) is ON,
				 * then excess accounting charges 
				 * accumulated when CPU was in turbo mode
				 * are recovered.
				 */
#define AACCT_CPU_CHARGES_RECOVERED	0x01

/*
 * General format of an accounting transaction record.
 *
 * Variable length data specific to the record begins at tran_data,
 * which may optionally include a subheader.  The first integer of
 * this subheader will contain the subheader's total size.
 * The size of the transaction-specific data at tran_data (not
 * including any subheader) is implied by the tran_id.
 *
 * Note - the size of this structure may be misleading!
 * Use TRAN_HDR_SIZE, defined below.
 */
struct aacct_tran_header {
	unsigned int		tran_size;	/* size of entire record */
	unsigned int		tran_id;	/* transaction ID */
	unsigned char		tran_flags;	/* transaction flags (below) */
	unsigned char		tran_pad1[3];
	int			tran_project;	/* project ID */
	unsigned long long	tran_subproj;	/* subproject ID (for LL) */
	unsigned long long	tran_time;	/* time record built, usecs */
	char			tran_data[4];	/* variable length data */
};

/*
 * Flags defined in tran_flags
 */
#define	TRAN_KERNEL	0x01	/* kernel transaction gen'd by acct_put */
#define TRAN_SUBHEADER	0x02	/* tran_data starts off with a subheader */
#define TRAN_PROJ_RUSER	0x04	/* proj ID generated relative to UID */
#define TRAN_PROJ_RGRP	0x08	/* proj ID generated relative to GID */

/*
 * Size of the common header == offset to the variable transaction data.
 */
#define TRAN_HDR_SIZE	(long)&(((struct aacct_tran_header *)0)->tran_data)

/*
 * Version control is provided by detecting changes in the size of the
 * accounting data.  New fields are always added to the end of the structure
 * and fields are never removed, so the size of the accounting record will
 * only increase from one version to the next. The following defines may be
 * used to determine the version of the accounting data, which also serves
 * to document that changes that have been made.
 *
 * For example, the field elapsed was added to the tran_cpumem structure.
 */
#define TRsize_cpumem_V1 ((int)(&((struct tran_cpumem *)0)->elapsed) + \
				   TRAN_HDR_SIZE)

#define TRAN_cpumem_V1(hdr)       ((hdr)->tran_size == TRsize_cpumem_V1)

/******** The structures here map transaction specific data *************/

/*
 * There are a lot of doubleword counters that exist identically in
 * the proc structure (collecting data) and in the process record
 * (reporting it).  The trp_counts array in struct proc_counts allows us
 * to add counters in one place, and have them appear in both the proc and
 * process accounting record structures (discrete and aggregated) identically.
 * The array organization lets the data be copied by exit and interval
 * accounting without knowing the names of the individual fields.
 * The #defines let you reference the fields as if they were simple
 * long longs, as opposed to via explicit subscripting, to increment them.
 * To add a new accounting field, all you have to do is add two #defines,
 * (uppercase for the new data's index, lowercase for its scalar name)
 * increment TRP_NUM_COUNTS in proc.h, increment TRP_MAX and possibly
 * TRP_MAX_PROC below, and add the actual subsystem code to increment it.
 * Everything else will be taken care of automatically.
 *
 * The first TRP_MAX_PROC+1 elements are protected by the pv_lock_d,
 * and updated in process_proc_table, at interval end, or in exit.
 * The first TRP_LAST_TB+1 elements are collected in timebase units in
 * the proc structure, but converted to microseconds when moved to the
 * accounting transaction.
 *
 * The remaining elements are updated atomically outside sysproc,
 * and are copied/cleared atomically by interval accounting.
 * The code that increments them must use acct_add_LL, or, from a kernel
 * extension, acct_add_proc using the index number defined here.
 *
 * WARNING WARNING WARNING - New fields may be added compatibly only at
 * the end of the process record.  In effect, this means that TRP_LAST_TB
 * and TRP_MAX_PROC should never be changed.
 * TRP_MAX is the only value that may be compatibly increased.
 * This means that it is easy to add non-sysproc counters.  Adding a new
 * sysproc counter at the end will require source code in acct_proc()
 * to copy it while the pv_lock_d is still held.
 *
 * See the immediately following array reference definitions for comments
 * on the individual counters.
 */
#define TRP_ELAPSED	0
#define TRP_THREADTIME	1
#define TRP_CPUTIME	2
#define TRP_LAST_TB		2	/* highest timebase value */

#define TRP_DPAGE_SEC	3
#define TRP_RPAGE_SEC	4
#define TRP_VPAGE_SEC	5
#define TRP_MAX_PROC		5	/* highest index for sysproc data */

#define TRP_LOCAL_IO	6
#define TRP_OTHER_IO	7
#define TRP_LSOCK_IO	8
#define TRP_RSOCK_IO	9
#define TRP_MAX			9	/* highest index for all this data */

/*
 * Note: while the first three time statistics are reported to the user
 * via accounting transactions in usecs, the values are maintained in TB
 * units in the proc structure for efficiency reasons.
 */
#define	trp_elapsed	trp_count[0]	/* proc elapsed u-secs */
#define	trp_threadtime	trp_count[1]	/* combined threads elapsed u-secs */
#define	trp_cputime	trp_count[2]	/* proc (combined threads) cpu u-secs */
#define	trp_dpage_sec	trp_count[3]	/* page secs of disk pages */
#define	trp_rpage_sec	trp_count[4]	/* page secs of real pages */
#define	trp_vpage_sec	trp_count[5]	/* page secs of virt mem */
#define	trp_local_io	trp_count[6]	/* bytes file i/o to jfs, j2, etc. */
#define	trp_other_io	trp_count[7]	/* bytes file i/o to nfs, dfs, etc. */
#define	trp_lsock_io	trp_count[8]	/* bytes unix-domain/loopback sockets */
#define	trp_rsock_io	trp_count[9]	/* bytes over remote sockets */

/*
 * The proc_counts structure is actually defined in proc.h, but shown
 * here to indicate its nature.  The structure is used not only in the
 * proc structure, where data is collected, but in the various process
 * level accounting transactions as well.
 *
 *	struct proc_counts {
 *		unsigned long long	trp_count[TRP_NUM_COUNTS];
 *	} p_acct;	
 *
 * Both headers must be consistent, as checked below.
 */
struct trp_max_check {
	char	a[TRP_MAX < TRP_NUM_COUNTS ? 1 : -1];
};

struct tran_proc {
	int			trp_version;
	uid_t			trp_uid;	/* user id */
	gid_t			trp_gid;	/* group id */
	pid32_t			trp_pid;	/* process id */
	int			trp_service_cl;	/* eWLM service class */
	int			trp_flags;	/* flags, see below */
	char			trp_comm[12];	/* base command name */
	int			trp_pad[3];
	dev64_t			trp_tty;	/* controlling terminal */
						/* time 0 is the epoch below */
	unsigned long long	trp_start;	/* proc start time in secs */
	unsigned long long	trp_wlmkey;	/* WLM class key */
	struct proc_counts	trp_counts;	/* incrementing statistics */
};

#define TRP_FINAL	0x01	/* This is the final exit for the process */
#define TRP_CORE	0x02	/* process created a core file */
#define TRP_KILLED	0x04	/* process was killed by a signal */
#define TRP_KPROC	0x08	/* kernel process */
#define TRP_CHKPNT	0x10	/* terminated because of checkpoint */

/**********************************************************************/

struct tran_agg_proc {
	int			trp_version;
	int			trp_pad;
	unsigned long long	trp_start;	/* start time in seconds */
	uid_t			trp_uid;	/* user id */
	unsigned int		trp_procs;	/* number of procs aggregated */
	struct proc_counts	trp_counts;	/* incrementing statistics */
};

struct tran_agg_app {
	int			trp_version;
	int			trp_pad;
	unsigned long long	trp_start;	/* start time in seconds */
	uid_t			trp_uid;	/* user id */
	unsigned int		trp_commands;	/* invocations aggregated */
	dev64_t			trp_dev;	/* devno for command */
	ino64_t			trp_ino;	/* inode for command */
	struct proc_counts	trp_counts;	/* incrementing statistics */
};

struct tran_agg_ke {
	int			trp_version;
	int			trp_pad;
	unsigned long long	trp_start;	/* start time in seconds */
	unsigned int		trp_trid;	/* transaction id */
	unsigned int		trp_count;	/* # transactions aggregated */
	char			trp_comm[12];	/* KE name from U_comm */
	struct tusage		trp_usage;	/* resource utilization */
};

/**********************************************************************/


struct tran_cpumem {
        unsigned int rec_type;

#define ACCT_CPU_ADD_PRE        0
#define ACCT_CPU_ADD_POST       1
#define ACCT_CPU_REMOVE_PRE     2
#define ACCT_CPU_REMOVE_POST    3
#define ACCT_MEM_ADD_PRE        4
#define ACCT_MEM_ADD_POST       5
#define ACCT_MEM_REMOVE_PRE     6
#define ACCT_MEM_REMOVE_POST    7
#define ACCT_ENTCAP_ADD_PRE     8
#define ACCT_ENTCAP_ADD_POST    9
#define ACCT_ENTCAP_REMOVE_PRE  10
#define ACCT_ENTCAP_REMOVE_POST 11
#define ACCT_SYSTEM_INTERVAL    12
#define ACCT_SYSTEM_INT_ENABLE  13
#define ACCT_SYSTEM_INT_DISABLE 14
#define ACCT_LGPG_POOL_INCREASE 15
#define ACCT_LGPG_POOL_DECREASE 16
#define ACCT_PMIG_PRE		17
#define ACCT_PMIG_POST		18

        unsigned int ncpus;
        unsigned int entitled_cap;
        unsigned int pad;
        unsigned long long idle_time;		/* idle (msecs) */
        unsigned long long iowait_time;		/* iowait (msecs) */
        unsigned long long sprocess_time;	/* kprocess (msecs) */
        unsigned long long uprocess_time;	/* uprocess (msecs) */
        unsigned long long interrupt_time;	/* interrupt (msecs) */
        unsigned long long memory_size;
        unsigned long long lgpg_total;
        unsigned long long lgpg_inuse;
        unsigned int pgsp_ins;
        unsigned int pgsp_outs;
        unsigned int num_ios;
        unsigned int page_steals;
	unsigned long long elapsed;		/* interval (msecs) */
}; 

/*
 * Project definition record.  Written when projects are loaded.
 *
 * The project record is variable length and consists of a header
 * (tran_project), followed by an array of projects (proj_rec),
 * followed by a block of strings containing the project names.
 * Each proj_rec contains an offset to the associated project name,
 * relative to the start of the proj_rec array.
 */
struct proj_rec {
    unsigned	projid;
    ushort_t	origin;
    ushort_t	offset;
};

#define ACCT_ORIGIN_LOCAL	1

struct tran_project {
    int	resvd[2];
    unsigned nproj;
    unsigned size;
};

struct tran_proj {
    struct tran_project	proj_header;
    struct proj_rec	*proj;
};

/*
 * Policy record.  Written when a policy is loaded or unloaded.
 */
struct tran_policy {
    int		resvd[2];
    unsigned	type;
    unsigned	event;
}; 

/* policy types */
#define ACCT_POL_ADM	1
#define ACCT_POL_USR	2
#define ACCT_POL_GRP	3

/* policy events */
#define ACCT_EVNT_LOAD		1
#define ACCT_EVNT_UNLOAD	2

/**********************************************************************/

/* advanced accounting file system data for system level statistic
 *
 * Note: The following struct tran_filesystem contains
 *       the top portion of a file system transaction record,
 *       which is the main portion of the record and has fixed size.
 *
 *       the rest of the portion contains two elements which were not
 *       defined here to avoid duplication:
 *
 *       1) the device name of the logical volume which is holding the
 *          file system. 
 *
 *       2) the mount point of the file system. 
 *
 *       Since these two elements are variable length, so a file system
 *       transaction record will be also variable length.
 *
 *       The maximum length for device name or mount point is PATH_MAX.
 *       They are null terminated strings.
 */

struct tran_filesystem {
   	unsigned long long DbytesTrans; /* total bytes for read and write */
   	unsigned long long DnumRdWrs;  	/* total number of reads and writes */
   	unsigned long long DnumOpens;  	/* total number of opens */
   	unsigned long long DnumCreates; /* total number of creates */
   	unsigned long long DnumLocks;  	/* total number of locks */

   	uint Dfstype;    	/* fs type, also in vfs.vfs_mdata->vmt_gfstype 
                     		 *    its value is defined in <sys/vmount.h>
                     		 */
	short devname_len; 		/* device name length */
	short mntptr_len;   		/* mount point length */ 
};

/**********************************************************************/
/*
 * Network interface activity structure for acct record. (TRID_netif)
 */
#define TNETIF_NAMSIZ 	16
typedef struct tran_netif
{
	char		netif_name[TNETIF_NAMSIZ];
	long long	nios;
	long long	nbytes;
} tran_netif_t;

/**********************************************************************/

struct tran_disk {
        unsigned long long      total_xfers;    /* total disk transfers */
        unsigned long long      total_rblks;    /* total reads from disk */
        unsigned long long      total_wblks;    /* total writes to disk */
        unsigned int            blk_size;       /* blk size of disk transfer */
        char                    diskname[38];   /* name of disk */
};

/**********************************************************************/

struct tran_lostdata {
	int			trl_lost_recs;	/* number of lost transactions*/
	long long		trl_lost_cpu;	/* usecs lost process cputime */
	long long		trl_lost_start;	/* time data loss began, usecs*/
	long long		trl_lost_KEcpu;	/* usecs lost kernext cputime */
};

/**********************************************************************/

struct tran_vscsi_client {
        uint32_t                partition_num;  /* srvr partition number  */
        unsigned long long      unit_id;        /* srvr unit id           */
        unsigned long long      lun_id;         /* device logical unit id */
        unsigned long long      bytes_in;       /* bytes read             */
        unsigned long long      bytes_out;      /* bytes written          */
};

/**********************************************************************/

struct tran_vscsi_target {
        uint32_t                client_partition_num;  /* client number   */
        unsigned long long      unit_id;        /* srvr unit id           */
        unsigned long long      lun_id;        	/* device logical unit id */
        unsigned long long      bytes_in;      	/* bytes read             */
        unsigned long long      bytes_out;     	/* bytes written          */
};

/**********************************************************************/

/*
 * Character set mappings for ARM data.
 */
#define ACCT_ARM_ASCII		3	/* ARM_CHARSET_ASCII 		*/
#define ACCT_ARM_UTF8		106	/* ARM_CHARSET_UTF8 		*/
#define ACCT_ARM_UTF16BE	1013	/* ARM_CHARSET_UTF16BE 		*/
#define ACCT_ARM_UTF16LE	1014	/* ARM_CHARSET_UTF16LE 		*/
#define ACCT_ARM_UTF16		1015	/* ARM_CHARSET_UTF16 		*/
#define ACCT_ARM_IBM037		2028	/* ARM_CHARSET_IBM037 		*/
#define ACCT_ARM_IBM1047	2102	/* ARM_CHARSET_IBM1047 		*/

/*
 * Version numbers for data structures.
 */
#define ACCT_ARM_APPL_V1	1	/* tran_arm_applenv 		*/
#define ACCT_ARM_TRENV_V1	1	/* tran_arm_trenv 		*/
#define ACCT_ARM_TRAN_V1	1	/* tran_arm_tran 		*/
#define ACCT_ARM_AGG_V1		1	/* tran_agg_arm 		*/

/*
 * This record is produced for each unique registered application at the
 * system level.  The aeid parameter is used to refer to this unique 
 * combination of appl_name, group name, and properties.
 *
 * All offsets are calculated relative to the structure that contains them.
 * For example, ap_name is calculated relative to the start of the struct
 * tran_arm_applenv, tr_name to tran_arm_trenv, noffset to 
 * tran_arm_properties, ag_uid to tran_agg_arm, ... 
 */ 
struct tran_arm_applenv { 
	unsigned int 	   ap_version;	/* just in case			*/
	unsigned int 	   ap_charset;	/* character set for strings   	*/
	unsigned long long ap_id;	/* application environment id  	*/
	unsigned short	   ap_name;	/* offset to appl name    	*/
	unsigned short	   ap_group;	/* offset to appl group   	*/
	unsigned short	   ap_iprop;	/* offset to identity properties*/
	unsigned short	   ap_cprop;	/* offset to context properties */
	unsigned short	   ap_pad[2];
};
	
/*
 * This record is produced for each unique registered transaction at 
 * the system level.  The teid is used to refer to this unique combination
 * of transaction name and properties.  The cproperties contains only names.
 * The corresponding cproperty value fields are not provided. 
 */ 
struct tran_arm_trenv {
	unsigned int 	   tr_version;	/* just in case			*/
	unsigned int 	   tr_charset;	/* character set for strings 	*/
	unsigned long long tr_id;	/* transaction environment id	*/
	unsigned short	   tr_name;	/* offset to transaction name 	*/
	unsigned short	   tr_iprop;	/* offset to identity properties*/
	unsigned short	   tr_cprop;	/* offset to context properties */
	unsigned short	   tr_pad[3];
};

/* 
 * Arm IDs, if provided, are not unix user ids.  The content of this
 * field is defined by the application.   
 */
struct tran_arm_id {
	union {
		char	   c[16];
		int	   i[4];
		long long  l[2];
	} id_u;
};

/* 
 * Completion status for ARM transactions
 */ 
#define ACCT_ARM_STATUS_DISCARD	   -1	/* arm_discard_transaction() called */
#define ACCT_ARM_STATUS_GOOD	    0
#define ACCT_ARM_STATUS_ABORTED	    1
#define ACCT_ARM_STATUS_FAILED	    2
#define ACCT_ARM_STATUS_UNKNOWN	    3

/*
 * This record is produced for each transaction.
 */
struct tran_arm_tran {
	unsigned int 	   tri_version; /* just in case			*/
	unsigned int 	   tri_rc;	/* completion status 		*/
	unsigned long long tri_aeid;	/* application environment id  	*/
	unsigned long long tri_teid;	/* transaction environment id	*/
	unsigned short	   tri_uid;	/* offset to user identifier    */
	unsigned short	   tri_uname;	/* offset to user name 		*/
	unsigned short	   tri_acct;	/* offset to "EWLM:AIX:Account Class" */
	unsigned short	   tri_pad2;
	unsigned int	   tri_response;/* response time (milliseconds) */
	unsigned int	   tri_queued;	/* queued time   (milliseconds)	*/
	struct tusage	   tri_util;	/* resource util (microseconds) */
};

/*
 * Context and identity properties are stored as name value pairs.  Names
 * and strings are stored as struct tran_arm_string objects.
 */
struct tran_arm_prop {
	unsigned short	   noffset;	/* name offset 			*/
	unsigned short	   voffset;	/* value offset			*/
};

#define ACCT_MAX_PROPERTIES	20	/* ARM_PROPERTY_MAX_COUNT 	*/

struct tran_arm_properties {
	unsigned short	   tp_pad;
	unsigned short	   tp_cnt;	/* number of name-value pairs */

	struct tran_arm_prop tp_nv[ACCT_MAX_PROPERTIES*2];
};

/* 
 * All ARM string data has the following format.  The character set is
 * is defined in the parent structure.
 */
struct tran_arm_string {
	unsigned short 	ts_len;		/* number of bytes in string[] */
	char		ts_string[512];	/* the actual string data */
};

/*
 * The following structure is the aggregated ARM transaction.
 */
struct tran_agg_arm {
	unsigned int 	   ag_version;	/* just in case			*/
	unsigned int	   ag_rc;	/* completion status		*/
	unsigned long long ag_start;	/* start time in seconds 	*/
	unsigned long long ag_aeid;	/* application environment id  	*/
	unsigned long long ag_teid;	/* transaction environment id	*/
	unsigned short 	   ag_uid;	/* offset to user identifier 	*/
	unsigned short	   ag_uname;	/* offset to user name 		*/
	unsigned short	   ag_acct;	/* offset to account class 	*/
	unsigned short 	   ag_pad2;

	/* statistics that are incremented */
	unsigned int	   ag_pad3;
	unsigned int 	   ag_response;	/* response time (milliseconds) */
	unsigned int 	   ag_queued;	/* queued time   (milliseconds) */
	unsigned int 	   ag_count;	/* number of records aggregated */
	struct tusage 	   ag_util;	/* resource util (microseconds)	*/
};

/**********************************************************************
 *
 * The ACCT_NAME macro below generates a code segment to be run during
 * kernel initialization.  This pre-defines certain transactions that
 * are always present in the kernel.
 *
 * This data is for kernel use only.
 */
#define TRSS	15		/* transaction string size for below */
#ifdef _KERNSYS
#define aacct_name acct_sys_data.tr_name
#endif /* _KERNSYS */
#define ACCT_NAME							\
	strncpy (aacct_name[TRID_proc],		"proc",		TRSS);	\
	strncpy (aacct_name[TRID_agg_proc],	"agg_proc",	TRSS);	\
	strncpy (aacct_name[TRID_agg_app],	"agg_app",	TRSS);	\
	strncpy (aacct_name[TRID_cpumem],	"system",	TRSS);	\
	strncpy (aacct_name[TRID_project],	"project",	TRSS);	\
	strncpy (aacct_name[TRID_policy],	"policy",	TRSS);	\
	strncpy (aacct_name[TRID_file],		"file",		TRSS);	\
	strncpy (aacct_name[TRID_netif],	"netif",	TRSS);	\
	strncpy (aacct_name[TRID_disk],		"disk",		TRSS);	\
	strncpy (aacct_name[TRID_lostdata],	"lostdata",	TRSS);	\
	strncpy (aacct_name[TRID_agg_ke],	"agg_KE",	TRSS);	\
	strncpy (aacct_name[TRID_vscsi_client],	"vscsi_client",	TRSS);	\
	strncpy (aacct_name[TRID_vscsi_target],	"vscsi_target",	TRSS);	\
	strncpy (aacct_name[TRID_arm_applenv],	"arm_applenv",	TRSS);	\
	strncpy (aacct_name[TRID_arm_trenv],	"arm_trenv",	TRSS);	\
	strncpy (aacct_name[TRID_arm_tran],	"arm_tran",	TRSS);	\
	strncpy (aacct_name[TRID_agg_arm],	"agg_arm",	TRSS);	\
	strncpy (aacct_name[TRID_pad],		"pad",		TRSS);	\
/* ACCT_NAME */

/**********************************************************************/

/*********************************************************************
 *
 * DATA HARVESTING APIS
 *
 * The section has to do with the extraction and mainipulation
 * of accounting data. These interfaces are provided by libaacct.a.
 *
 **********************************************************************/

#define TRAN_STRSIZE		 512

enum crit  { CRIT_NONE,  CRIT_PROJ,  CRIT_UID,  CRIT_GID,  CRIT_CMD};

struct aacct_tran_rec
{
	struct aacct_tran_rec	*next;
	struct aacct_tran_rec	*prev;

	unsigned int tran_id;			/* transaction ID */
	unsigned char tran_flags;		/* transaction flags */
	int tran_project;			/* project ID */
	unsigned long long tran_subproj;	/* subproject ID */
	unsigned long long tran_time;		/* time record built */
	union {
		struct tran_proc *tr_proc;		  /* TRID_proc */
		struct tran_agg_proc *tr_agg_proc;	  /* TRID_agg_proc */
		struct tran_agg_app *tr_agg_app;	  /* TRID_agg_app */
		struct tran_cpumem *tr_cpumem;		  /* TRID_cpumem */
		struct tran_filesystem_v2 *tr_file;	  /* TRID_file */
		struct tran_netif *tr_netif;		  /* TRID_netif */
		struct tran_disk *tr_disk;		  /* TRID_disk */
		struct tran_vscsi_target *tr_vscsi_target;/* TRID_vscsi_target*/
		struct tran_vscsi_client *tr_vscsi_client;/* TRID_vscsi_client*/
		struct tran_arm_applenv_v2 *tr_applenv;	  /* TRID_arm_applenv */
		struct tran_arm_trenv_v2 *tr_trenv;	  /* TRID_arm_trenv */
		struct tran_arm_tran_v2 *tr_arm;	  /* TRID_arm_tran */
		struct tran_agg_arm_v2 *tr_agg_arm;	  /* TRID_agg_arm */
		struct tran_lostdata *tr_lost;		  /* TRID_lostdata */
		struct tran_proj *tr_project;		  /* TRID_project */
		struct tran_policy *tr_policy;		  /* TRID_policy */

		/*
		 * The following field is used for internal use only.  A dummy
		 * record is allocated to expedite building and sorting the
		 * list.  The TRID of the dummy record is -1 to indicate that
		 * the record does not hold accounting data.
		 */
		struct aacct_tran_rec *last_rec;	  /* internal use only. */
	} tran_data;

	unsigned long pad[2];
};

/*
 * aacct_tran_rec short cut for struct tran_proc
 */
#define tr_p_vers		tran_data.tr_proc->trp_version
#define tr_p_uid		tran_data.tr_proc->trp_uid
#define tr_p_gid		tran_data.tr_proc->trp_gid
#define tr_p_pid		tran_data.tr_proc->trp_pid
#define tr_p_service_cl		tran_data.tr_proc->trp_service_cl
#define tr_p_flags		tran_data.tr_proc->trp_flags
#define tr_p_cmd		tran_data.tr_proc->trp_comm
#define tr_p_tty		tran_data.tr_proc->trp_tty
#define tr_p_start		tran_data.tr_proc->trp_start
#define tr_p_wlmkey		tran_data.tr_proc->trp_wlmkey
#define tr_p_stats		tran_data.tr_proc->trp_counts

/*
 * aacct_tran_rec short cut for struct tran_agg_proc
 */
#define tr_ap_vers		tran_data.tr_agg_proc->trp_version
#define tr_ap_start		tran_data.tr_agg_proc->trp_start
#define tr_ap_procs		tran_data.tr_agg_proc->trp_procs
#define tr_ap_uid		tran_data.tr_agg_proc->trp_uid
#define tr_ap_stats		tran_data.tr_agg_proc->trp_counts

/*
 * aacct_tran_rec short cut for struct tran_agg_app
 */
#define tr_aa_vers		tran_data.tr_agg_app->trp_version
#define tr_aa_start		tran_data.tr_agg_app->trp_start
#define tr_aa_uid		tran_data.tr_agg_app->trp_uid
#define tr_aa_ncmds		tran_data.tr_agg_app->trp_commands
#define tr_aa_dev		tran_data.tr_agg_app->trp_dev
#define tr_aa_ino		tran_data.tr_agg_app->trp_ino
#define tr_aa_stats		tran_data.tr_agg_app->trp_stat

/*
 * aacct_tran_rec short cut for struct tran_cpumem
 */
#define tr_s_type		tran_data.tr_cpumem->rec_type
#define tr_s_ncpus		tran_data.tr_cpumem->ncpus
#define tr_s_ec			tran_data.tr_cpumem->entitled_cap
#define tr_s_idle		tran_data.tr_cpumem->idle_time
#define tr_s_iowait		tran_data.tr_cpumem->iowait_time
#define tr_s_kprocs		tran_data.tr_cpumem->sprocess_time
#define tr_s_uprocs		tran_data.tr_cpumem->uprocess_time
#define tr_s_int		tran_data.tr_cpumem->interrupt_time
#define tr_s_memsize		tran_data.tr_cpumem->memory_size
#define tr_s_lpg_total		tran_data.tr_cpumem->lgpg_total
#define tr_s_lpg_inuse		tran_data.tr_cpumem->lgpg_inuse
#define tr_s_pgins		tran_data.tr_cpumem->pgsp_ins
#define tr_s_pgouts		tran_data.tr_cpumem->pgsp_outs
#define tr_s_pgstls		tran_data.tr_cpumem->page_steals
#define tr_s_nios		tran_data.tr_cpumem->num_ios
#define tr_s_elapsed		tran_data.tr_cpumem->elapsed

/*
 * aacct_tran_rec short cut for struct tran_netif
 */
#define tr_n_netifname		tran_data.tr_netif->netif_name
#define tr_n_nios		tran_data.tr_netif->nios
#define tr_n_nbytes		tran_data.tr_netif->nbytes

/*
 * aacct_tran_rec short cut for struct tran_disk
 */
#define tr_d_xfers		tran_data.tr_disk->total_xfers
#define tr_d_rblks		tran_data.tr_disk->total_rblks
#define tr_d_wblks		tran_data.tr_disk->total_wblks
#define tr_d_blksize		tran_data.tr_disk->blk_size
#define tr_d_diskname		tran_data.tr_disk->diskname

/*
 * aacct_tran_rec short cut for struct tran_lostdata
 */
#define tr_l_recs		tran_data.tr_lost->trl_lost_recs
#define tr_l_cpu		tran_data.tr_lost->trl_lost_cpu
#define tr_l_start		tran_data.tr_lost->trl_lost_start
#define tr_l_KEcpu		tran_data.tr_lost->trl_lost_KEcpu

/*
 * aacct_tran_rec short cut for struct tran_vscsi_client
 */
#define tr_vc_tlpid		tran_data.tr_vscsi_client->partition_num
#define tr_vc_unid		tran_data.tr_vscsi_client->unit_id
#define tr_vc_lun		tran_data.tr_vscsi_client->lun_id
#define tr_vc_bytesin		tran_data.tr_vscsi_client->bytes_in
#define tr_vc_bytesout		tran_data.tr_vscsi_client->bytes_out

/*
 * aacct_tran_rec short cut for struct tran_vscsi_target
 */
#define tr_vt_clpid		tran_data.tr_vscsi_target->client_partition_num
#define tr_vt_unid		tran_data.tr_vscsi_target->unit_id
#define tr_vt_lun		tran_data.tr_vscsi_target->lun_id
#define tr_vt_bytesin		tran_data.tr_vscsi_target->bytes_in
#define tr_vt_bytesout		tran_data.tr_vscsi_target->bytes_out

/*
 * aacct_tran_rec short cut for struct tran_policy
 */
#define tr_po_type		tran_data.tr_policy->type
#define tr_po_event		tran_data.tr_policy->event

/*
 * aacct_tran_rec short cut for struct tran_project
 */
#define tr_pr_nproj		tran_data.tr_project->proj_header.nproj
#define tr_pr_size		tran_data.tr_project->proj_header.size
#define tr_pr_projid(i)		tran_data.tr_project->proj[i].projid
#define tr_pr_projorig(i)	tran_data.tr_project->proj[i].origin
#define tr_pr_projname(i)	tran_data.tr_project->proj[i].offset

/*
 * aacct_tran_rec short cut for struct tran_filesystem_v2
 */
#define tr_f_total		tran_data.tr_file->DbytesTrans
#define tr_f_nrdwr		tran_data.tr_file->DnumRdWrs
#define tr_f_nopens		tran_data.tr_file->DnumOpens
#define tr_f_ncreat		tran_data.tr_file->DnumCreates
#define tr_f_nlocks		tran_data.tr_file->DnumLocks
#define tr_f_type		tran_data.tr_file->Dfstype
#define tr_f_dev		tran_data.tr_file->devname
#define tr_f_mnt		tran_data.tr_file->mountpt

struct tran_filesystem_v2
{
	unsigned long long	DbytesTrans;	/* total bytes for rdwr */
	unsigned long long 	DnumRdWrs;	/* total number of rdwrs */
	unsigned long long 	DnumOpens;	/* total number of opens */
	unsigned long long 	DnumCreates;	/* total number of creates */
	unsigned long long 	DnumLocks;	/* total number of locks */
	unsigned int		Dfstype;	/* fs type */
	char			devname[PATH_MAX];/* device name */
	char			mountpt[PATH_MAX];/* mount point */
};

struct tran_arm_properties_v2 {
	unsigned short		tp_cnt;		/* number of name=value pairs */
	struct tran_arm_string	tp_name[ACCT_MAX_PROPERTIES];
	struct tran_arm_string	tp_value[ACCT_MAX_PROPERTIES];
};

/*
 * aacct_tran_rec short cut for struct tran_arm_applenv_v2
 */
#define tr_a_vers		tran_data.tr_applenv->ap_version
#define tr_a_charset		tran_data.tr_applenv->ap_charset
#define tr_a_id			tran_data.tr_applenv->ap_id
#define tr_a_name		tran_data.tr_applenv->ap_name
#define tr_a_group		tran_data.tr_applenv->ap_group
#define tr_a_iprop_cnt		tran_data.tr_applenv->ap_iprop.tp_cnt
#define tr_a_iprop_name		tran_data.tr_applenv->ap_iprop.tp_name
#define tr_a_iprop_val		tran_data.tr_applenv->ap_iprop.tp_value
#define tr_a_cprop_cnt		tran_data.tr_applenv->ap_cprop.tp_cnt
#define tr_a_cprop_name		tran_data.tr_applenv->ap_cprop.tp_name
#define tr_a_cprop_val		tran_data.tr_applenv->ap_cprop.tp_value

struct tran_arm_applenv_v2 {
	unsigned int		ap_version;
	unsigned int		ap_charset;	  /* char set for strings */
	unsigned long long	ap_id;		  /* appl environment id */
	char			ap_name[TRAN_STRSIZE]; /* application name */
	char			ap_group[TRAN_STRSIZE];/* application group name */
	struct tran_arm_properties_v2 ap_iprop;	  /* identity properties */
	struct tran_arm_properties_v2 ap_cprop;	  /* context properties */
};

/*
 * aacct_tran_rec short cut for struct tran_arm_trenv_v2
 */
#define tr_e_vers		tran_data.tr_trenv->tr_version
#define tr_e_charset		tran_data.tr_trenv->tr_charset
#define tr_e_id			tran_data.tr_trenv->tr_id
#define tr_e_name		tran_data.tr_trenv->tr_name
#define tr_e_iprop_cnt		tran_data.tr_trenv->tr_iprop.tp_cnt
#define tr_e_iprop_name		tran_data.tr_trenv->tr_iprop.tp_name
#define tr_e_iprop_val		tran_data.tr_trenv->tr_iprop.tp_value
#define tr_e_cprop_cnt		tran_data.tr_trenv->tr_cprop.tp_cnt
#define tr_e_cprop_name		tran_data.tr_trenv->tr_cprop.tp_name
#define tr_e_cprop_val		tran_data.tr_trenv->tr_cprop.tp_value

struct tran_arm_trenv_v2 {
	unsigned int		tr_version;
	unsigned int		tr_charset;	  /* char set for strings */
	unsigned long long	tr_id;		  /* trans environment id */
	char			tr_name[TRAN_STRSIZE]; /* transaction name */
	struct tran_arm_properties_v2 tr_iprop;	  /* identity properties */
	struct tran_arm_properties_v2 tr_cprop;	  /* context properties */
};

/*
 * aacct_tran_rec short cut for struct tran_arm_tran_v2
 */
#define tr_i_vers		tran_data.tr_arm->tri_version
#define tr_i_rc			tran_data.tr_arm->tri_rc
#define tr_i_aeid		tran_data.tr_arm->tri_aeid
#define tr_i_teid		tran_data.tr_arm->tri_teid
#define tr_i_uid		tran_data.tr_arm->tri_uid
#define tr_i_uname		tran_data.tr_arm->tri_uname
#define tr_i_acct		tran_data.tr_arm->tri_acct
#define tr_i_resp		tran_data.tr_arm->tri_response
#define tr_i_queued		tran_data.tr_arm->tri_queued
#define tr_i_cpu		tran_data.tr_arm->tri_util.tu_cpu
#define tr_i_res1		tran_data.tr_arm->tri_util.tu_res1

struct tran_arm_tran_v2 {
	unsigned int		tri_version;
	unsigned int		tri_rc;		  /* completion status */
	unsigned long long	tri_aeid;	  /* appl environment id */
	unsigned long long	tri_teid;	  /* trans environment id */
	struct tran_arm_id	tri_uid;	  /* user identifier */
	char			tri_uname[TRAN_STRSIZE];/* user name */
	char			tri_acct[TRAN_STRSIZE]; /* account class name */
	unsigned int		tri_response;	   /* milliseconds */
	unsigned int		tri_queued;	   /* milliseconds */
	struct tusage		tri_util;	   /* cpu microseconds */
	unsigned long long	spare[5];
};

/*
 * aacct_tran_rec short cut for struct tran_agg_arm_v2
 */
#define tr_g_vers		tran_data.tr_agg_arm->ag_version
#define tr_g_rc			tran_data.tr_agg_arm->ag_rc
#define tr_g_start		tran_data.tr_agg_arm->ag_start
#define tr_g_aeid		tran_data.tr_agg_arm->ag_aeid
#define tr_g_teid		tran_data.tr_agg_arm->ag_teid
#define tr_g_uid		tran_data.tr_agg_arm->ag_uid
#define tr_g_uname		tran_data.tr_agg_arm->ag_uname
#define tr_g_acct		tran_data.tr_agg_arm->ag_acct
#define tr_g_resp		tran_data.tr_agg_arm->ag_response
#define tr_g_queued		tran_data.tr_agg_arm->ag_queued
#define tr_g_count		tran_data.tr_agg_arm->ag_count
#define tr_g_cpu		tran_data.tr_agg_arm->ag_util.tu_cpu
#define tr_g_res1		tran_data.tr_agg_arm->ag_util.tu_res1

struct tran_agg_arm_v2 {
	unsigned int		ag_version;
	unsigned int		ag_rc;		   /* completion status */
	unsigned long long	ag_start;	   /* start time in seconds */
	unsigned long long	ag_aeid;	   /* appl environment id */
	unsigned long long	ag_teid;	   /* trans environment id */
	struct tran_arm_id	ag_uid;		   /* user identifier */
	char			ag_uname[TRAN_STRSIZE]; /* user name */
	char			ag_acct[TRAN_STRSIZE];  /* account class name */
	unsigned int		ag_response;	   /* milliseconds */
	unsigned int		ag_queued;	   /* milliseconds */
	unsigned int		ag_count;	   /* num of records aggr */
	struct tusage		ag_util;	   /* cpu microseconds */
};

/*
 * proc_crit is the common structure to be used for collecting the
 * process transaction records based on the parameter passed
 * (based on UID, GID, PROJID or CMD parameters).  The selection
 * criteria is CRIT_NONE, CRIT_UID, ...
 */
union proc_crit
{
	uid_t *uidlist;			/* list of UIDs */
	gid_t *gidlist;			/* list of GIDs */
	projid_t *projlist;		/* list of Project IDs */
	char **cmdlist;			/* list of commands */
};

struct agg_proc_stat
{
	struct agg_proc_stat	*next;
	projid_t		proj_id;		/* project ID */
	uid_t			uid;			/* user ID */
	gid_t			gid;			/* group ID */
	char			command[12];		/* base command name */
	dev64_t			devno;			/* devno for command */
	ino64_t			inode;			/* inode for command */
	unsigned long long	count;			/* cnt of recs aggr */
	unsigned long long	total_elapsed_time;	/* proc (usecs)*/
	unsigned long long	thread_elapsed_time;    /* threads (usecs)*/
	unsigned long long	cpu_time;		/* cpu (usecs) */
	unsigned long long	local_file_io;		/* bytes jfs, etc. */
	unsigned long long	other_file_io;		/* bytes nfs, etc. */
	unsigned long long	disk_page_secs;		/* disk cost */
	unsigned long long	real_page_secs;		/* real mem cost */
	unsigned long long	virtual_page_secs;	/* virt mem cost */
	unsigned long long	local_socket_io;	/* bytes unix-domain */
	unsigned long long	remote_socket_io;	/* bytes r sockets */
	unsigned long long	spare[5];
};

/*
 * These are LPAR selection types for agg_lpar_stat()
 */
#define AGG_CPUMEM	0
#define AGG_FILESYS	1
#define AGG_NETIF	2
#define AGG_DISK	3
#define AGG_VTARGET	4
#define AGG_VCLIENT	5

union agg_lpar_rec
{
	struct agg_cpumem_stat **cpumem_list;
	struct agg_fs_stat **fs_list;
	struct agg_netif_stat **netif_list;
	struct agg_disk_stat **disk_list;
	struct agg_vtarget_stat **vtarget_list;
	struct agg_vclient_stat **vclient_list;
};

/*
 * Note: The CPU times like idle, wait time are in milliseconds. 
 *
 */
struct agg_cpumem_stat
{
	struct agg_cpumem_stat	*next;
	projid_t		proj_id;		/* project ID */
	unsigned long long	count;			/* cnt of rec aggr */
	unsigned long long	idle_time;		/* CPU Idle time */
	unsigned long long	iowait_time;		/* CPU IOWait time */
	unsigned long long	sprocess_time;		/* System Process time */
	unsigned long long	uprocess_time;		/* User Process time */
	unsigned long long	interrupt_time; 	/* Interrupt time */		 
	unsigned long long	num_ios;		/* number of I/Os */
	unsigned long long	pgsp_ins;		/* page swap ins */
	unsigned long long	pgsp_outs;		/* page swap outs */
	unsigned long long	lgpg_total;		/* large page pool */
	unsigned long long	lgpg_inuse;		/* large pages in use */
	unsigned long long	page_steals;		/* num of page steals */
	unsigned long long	elapsed_time;		/* milliseconds */
	unsigned long long	spare[5];
};

struct agg_fs_stat
{
	struct agg_fs_stat	*next;
	projid_t		proj_id;		/* project ID */
	unsigned long long	count;			/* cnt of recs aggr */
	char			devname[PATH_MAX];	/* device name */
	char			mountpt[PATH_MAX];	/* mount point of fs */
	unsigned int		Dfstype;		/* file system type */
	unsigned long long	DbytesTrans;		/* total bytes rdwr */
	unsigned long long	DnumRdWrs;		/* total num rdwr */
	unsigned long long	DnumOpens;		/* total num of opens */
	unsigned long long	DnumCreates;		/* total num of creates */
	unsigned long long	DnumLocks;		/* total num of locks */
	unsigned long long	spare[5];
};

struct agg_netif_stat
{
	struct agg_netif_stat	*next;
	projid_t		proj_id;		/* project ID */
	unsigned long long	count;			/* cnt of recs aggr */
	char			netif_name[TNETIF_NAMSIZ];/* netif name */
	unsigned long long	num_ios;		/* number of i/o */
	unsigned long long	num_bytes;		/* total bytes xfer*/
	unsigned long long	spare[5];
};

struct agg_disk_stat
{
	struct agg_disk_stat	*next;
	projid_t		proj_id;	/* project ID */
	unsigned long long	count;		/* cnt of recs aggrd */
	unsigned int		blk_size;	/* blk size of disk transfer */
	char			diskname[38];	/* name of disk */
	unsigned long long	total_xfers;	/* total disk transfers */
	unsigned long long	total_rblks;	/* total reads from the disk */
	unsigned long long	total_wblks;	/* total writes to the disk */
	unsigned long long	spare[5];
};

struct agg_vtarget_stat
{
	struct agg_vtarget_stat	*next;
	projid_t		proj_id;	/* project ID */
	unsigned long long	count;		/* cnt of records aggr */
	uint32_t		client_partition_num;/* client LPAR number */
	unsigned long long	unit_id;	/* server unit ID */
	unsigned long long	lun_id;		/* device logical unit ID */
	unsigned long long	bytes_in;	/* bytes read */
	unsigned long long	bytes_out;	/* bytes written */
	unsigned long long	spare[5];
};

struct agg_vclient_stat
{
	struct agg_vclient_stat	*next;
	projid_t		proj_id;	/* project ID */
	unsigned long long	count;		/* cnt of recs aggr */
	uint32_t		partition_num;	/* server LPAR number */
	unsigned long long	unit_id;	/* server unit ID */
	unsigned long long	lun_id;		/* device logical unit id */
	unsigned long long	bytes_in;	/* bytes read */
	unsigned long long	bytes_out;	/* bytes written */
	unsigned long long	spare[5];
};

struct agg_arm_stat
{
	struct agg_arm_stat	*next;
	projid_t		proj_id;	    /* project ID */
	unsigned long long	count;		    /* cnt of recs aggr */
	unsigned long long	aeid;		    /* Appl environment ID */
	unsigned long long	teid;		    /* Trans environment ID */
	char			appl_group[TRAN_STRSIZE];/* Appl Group Name */
	char			appl_name[TRAN_STRSIZE]; /* Appl Name */
	char			tr_name[TRAN_STRSIZE];   /* Transaction Name */
	char			acct_class[TRAN_STRSIZE];/* Account Class Name */
	char			user_name[TRAN_STRSIZE]; /* User Name */
	unsigned long long	response_time;	    /* Response Time */
	unsigned long long	queued_time;	    /* Queued Time */
	struct tusage		res_util;	    /* Resource Utilization */
	unsigned long long	spare[5];
};

int getfilehdr(char *filename, struct acct_file_header *hdrinfo);

int buildtranlist(char *filename, unsigned int trid[], 
		  unsigned int ntrids, long long begin_time, 
		  long long end_time, struct aacct_tran_rec **tran_list);

int getproclist(char *filename, long long begin_time, 
		long long end_time, struct aacct_tran_rec **p_list);

int getlparlist(char *filename, long long begin_time, 
		long long end_time, struct aacct_tran_rec **l_list);

int getarmlist(char *filename, long long begin_time, 
	       long long end_time, struct aacct_tran_rec **t_list);

int freetranlist(struct aacct_tran_rec *tran_list);

int buildproclist(int crit, union proc_crit *crit_list, 
		  int n_crit, struct aacct_tran_rec *p_list,
		  struct aacct_tran_rec **sublist);

int agg_arm_stat(struct aacct_tran_rec *tran_list, 
	 	 struct agg_arm_stat **arm_list);

int agg_proc_stat(int sortcrit1, int sortcrit2, int sortcrit3, 
		  int sortcrit4, struct aacct_tran_rec *tran_list, 
		  struct agg_proc_stat **proc_list);

int agg_lpar_stat(int l_type, struct aacct_tran_rec *tran_list, 
		  union agg_lpar_rec *l_list);

void free_agg_list(void *list);

int getprojdbcnt(void);

#endif		 /* _H_AACCT */
