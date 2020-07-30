/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53V src/bos/kernel/sys/dr.h 1.38                                    */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 2001,2009              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)40     1.38  src/bos/kernel/sys/dr.h, sysproc, bos53V, v2009_14A7 3/31/09 13:23:48 */

#ifndef _H_SYS_DR
#define _H_SYS_DR

#include <sys/types.h>
#include <sys/processor.h>

typedef struct dr_info {
	unsigned int        add : 1;	/* add operation		      */
	unsigned int        rem : 1; 	/* remove operation		      */
	unsigned int        cpu : 1;	/* target resource is a cpu	      */
	unsigned int        mem : 1;	/* target resource is memory	      */
	unsigned int      check : 1;	/* check phase in effect	      */
	unsigned int        pre : 1;	/* pre phase in effect		      */
	unsigned int       doit : 1;	/* doit phase in effect		      */
	unsigned int       post : 1;	/* post phase in effect		      */
	unsigned int  posterror : 1;	/* post error phase in effect	      */
	unsigned int      force : 1;	/* force option in effect	      */
	unsigned int   bindproc : 1;	/* process has bindprocess dependency */
	unsigned int   softpset : 1;	/* process has soft processor set
					   dependency                         */
	unsigned int   hardpset : 1;	/* process has hard processor set
					   dependency			      */
	unsigned int      plock : 1;	/* process has plock'ed/mlock'd memory*/
	unsigned int       pshm : 1;	/* process has pinned shared memory   */
	unsigned int	ent_cap	: 1;	/* target resource:entitled capacity  */
	unsigned int	var_wgt	: 1;	/* target resource:variable weight    */
	unsigned int splpar_capable : 1;/* 1/0 partition is/not splpar capable*/
	unsigned int splpar_shared  : 1;/* 1/0 partition shared/dedicated mode*/
	unsigned int splpar_capped  : 1;/* 1/0 partition capped/uncapped mode */
	unsigned int cap_constrained : 1;/* Set to 1 if requested capacity
					  * update is constrained by PHYP to 
					  * be within partition capacity bounds.
					  */
	unsigned int migrate : 1;
	unsigned int hibernate : 1;
	unsigned int partition : 1;

	/* The following fields are filled out for cpu based requests */

	int	lcpu;			/* logical id of target cpu 	      */
	int	bcpu;			/* bind-id of target cpu	      */

	uint	phase_gen;		/* Reserved for kernel use.           */

	/* The following fields are filled out for memory based requests */

        size64_t  req_memsz_change;	/* Request size in bytes              */
	size64_t  sys_memsz;		/* System Memory size		      */
        rpn64_t   sys_free_frames;	/* Number of free frames in the system*/
        rpn64_t   sys_pinnable_frames;	/* Number of pinnable frames in system*/
        rpn64_t   sys_total_frames;	/* Total number of frames in system   */

	/*
	 * SPLPAR parameters.
	 */
	uint64_t  capacity;		/* partition current entitled capacity
					 * if ent_cap bit is set, partition's
					 * current variable capacity weight 
					 * if var_wgt bit is set. 
					 */
	int	  delta_cap;		/* delta capacity added/removed to 
					 * current value depending on add/rem 
					 * bit flag value above 
					 */
	int  reserved[9];          
} dr_info_t;

int dr_reconfig(int flags, dr_info_t *info);

/* Valid flags for dr_reconfig are */
#define DR_QUERY            0x000000001
#define DR_EVENT_FAIL       0x000000002
#define DR_RECONFIG_DONE    0x000000004

/*
 * LPAR cpu info struct.  Used to pass back
 * load average and utilization average.
 */
typedef struct lpar_load{
        int     loadavg;                /* load average on lpars */
        int     utilavg;                /* utilization average on lpars */
	char	loadavgshift;		/* int -> float shift value */
	char	pad[3];
} lpar_load_t;

int getlparload(lpar_load_t *lp, size_t size);

#ifdef _KERNEL
/* 
 * DR Events that Kernel Extensions wants to be notified of 
 */ 
#define DR_CPU_ADD_CHECK		0x00000001ULL
#define DR_CPU_ADD_PRE			0x00000002ULL
#define DR_CPU_ADD_POST			0x00000004ULL
#define DR_CPU_ADD_POST_ERROR		0x00000008ULL
#define DR_CPU_REMOVE_CHECK		0x00000010ULL
#define DR_CPU_REMOVE_PRE		0x00000020ULL
#define DR_CPU_REMOVE_POST		0x00000040ULL
#define DR_CPU_REMOVE_POST_ERROR	0x00000080ULL
#define DR_MEM_ADD_CHECK		0x00000100ULL
#define DR_MEM_ADD_PRE			0x00000200ULL
#define DR_MEM_ADD_POST			0x00000400ULL
#define DR_MEM_ADD_POST_ERROR		0x00000800ULL
#define DR_MEM_REMOVE_CHECK		0x00001000ULL
#define DR_MEM_REMOVE_PRE		0x00002000ULL
#define DR_MEM_REMOVE_POST		0x00004000ULL
#define DR_MEM_REMOVE_POST_ERROR	0x00008000ULL
#define DR_MEM_ADD_RES			0x00010000ULL
#define DR_MEM_REMOVE_RES		0x00020000ULL

#define DR_CAP_ADD_CHECK		0x00040000ULL
#define DR_CAP_ADD_PRE			0x00080000ULL
#define DR_CAP_ADD_POST			0x00100000ULL
#define DR_CAP_ADD_POST_ERROR		0x00200000ULL
#define DR_CAP_REMOVE_CHECK		0x00400000ULL
#define DR_CAP_REMOVE_PRE		0x00800000ULL
#define DR_CAP_REMOVE_POST		0x01000000ULL
#define DR_CAP_REMOVE_POST_ERROR	0x02000000ULL

#define DR_MEM_REMOVE_OP_PRE            0x04000000ULL
#define DR_MEM_REMOVE_OP_POST           0x08000000ULL
#define DR_MEM_ADD_OP_POST              0x10000000ULL
#define DR_RESERVED1			0x20000000ULL
#define DR_RESERVED2			0x40000000ULL
#define DR_RESERVED3			0x80000000ULL

#define DR_PMIG_CHECK			0x100000000ULL
#define DR_PMIG_PRE			0x200000000ULL
#define DR_PMIG_POST			0x400000000ULL
#define DR_PMIG_POST_ERROR		0x800000000ULL
						/* Reserved for internal use  */
#define DR_PMIG_POST_INTERNAL		0x1000000000ULL 
/*
 * Events flag values grouped for ease.
 */
#define DR_CHECK_NOTIFY	(DR_MEM_REMOVE_CHECK | DR_CPU_REMOVE_CHECK | \
			 DR_CPU_ADD_CHECK | DR_MEM_ADD_CHECK | \
			 DR_CAP_ADD_CHECK | DR_CAP_REMOVE_CHECK | DR_PMIG_CHECK)

#define DR_PRE_NOTIFY	(DR_MEM_REMOVE_PRE | DR_CPU_REMOVE_PRE | \
			 DR_CPU_ADD_PRE | DR_MEM_ADD_PRE | \
			 DR_MEM_ADD_RES | DR_MEM_REMOVE_RES | \
			 DR_CAP_ADD_PRE | DR_CAP_REMOVE_PRE | DR_PMIG_PRE)

#define DR_POST_NOTIFY	(DR_MEM_REMOVE_POST | DR_CPU_REMOVE_POST | \
			 DR_CPU_ADD_POST | DR_MEM_ADD_POST | \
			 DR_CAP_ADD_POST | DR_CAP_REMOVE_POST | DR_PMIG_POST)

#define DR_POST_ERROR_NOTIFY	(DR_MEM_REMOVE_POST_ERROR | \
				 DR_CPU_REMOVE_POST_ERROR | \
				 DR_CPU_ADD_POST_ERROR    | \
				 DR_MEM_ADD_POST_ERROR	  | \
				 DR_CAP_ADD_POST_ERROR    | \
				 DR_CAP_REMOVE_POST_ERROR | \
				 DR_PMIG_POST_ERROR)

#define DR_CPU_NOTIFY 	(DR_CPU_ADD_CHECK    | DR_CPU_ADD_PRE        | \
			 DR_CPU_ADD_POST     | DR_CPU_ADD_POST_ERROR | \
			 DR_CPU_REMOVE_CHECK | DR_CPU_REMOVE_PRE     | \
			 DR_CPU_REMOVE_POST  | DR_CPU_REMOVE_POST_ERROR)

#define DR_MEM_NOTIFY 	(DR_MEM_ADD_CHECK    | DR_MEM_ADD_PRE        | \
			 DR_MEM_ADD_POST     | DR_MEM_ADD_POST_ERROR | \
			 DR_MEM_REMOVE_CHECK | DR_MEM_REMOVE_PRE     | \
			 DR_MEM_ADD_RES      | DR_MEM_REMOVE_RES     | \
			 DR_MEM_REMOVE_POST  | DR_MEM_REMOVE_POST_ERROR)

#define DR_CAP_NOTIFY 	(DR_CAP_ADD_CHECK    | DR_CAP_ADD_PRE        | \
			 DR_CAP_ADD_POST     | DR_CAP_ADD_POST_ERROR | \
			 DR_CAP_REMOVE_CHECK | DR_CAP_REMOVE_PRE     | \
			 DR_CAP_REMOVE_POST  | DR_CAP_REMOVE_POST_ERROR)

#define DR_PMIG_NOTIFY 	(DR_PMIG_CHECK	     | DR_PMIG_PRE	     | \
			 DR_PMIG_POST        | DR_PMIG_POST_ERROR)

#define DR_ALL_NOTIFY	(DR_CPU_NOTIFY | \
			 DR_MEM_NOTIFY | \
			 DR_CAP_NOTIFY | \
			 DR_PMIG_NOTIFY)

#define DR_ALL_OP_NOTIFY (DR_MEM_REMOVE_OP_PRE  | \
			  DR_MEM_REMOVE_OP_POST | \
			  DR_MEM_ADD_OP_POST)

/* 
 * DR handler return values: 
 */
#define DR_SUCCESS  0
#define DR_WAIT     1
#define DR_FAIL     2

/*
 * Output data structures to kernel extensions for cpu and memory
 * DR operations
 */

struct dri_cpu {
	cpu_t		lcpu;		/* Logical CPU Id of target CPU */
	cpu_t		bcpu;		/* Bind Id being removed	*/
};

struct dri_mem {
	size64_t	req_memsz_change;   /* requested mem size  */
	size64_t	sys_memsz;	    /* Original total mem size */
	size64_t	act_memsz_change;   /* mem added/removed so far */
	rpn64_t	        sys_free_frames;    /* Number of free frames */
	rpn64_t	        sys_pinnable_frames;/* Number of pinnable frames */
	rpn64_t	        sys_total_frames;   /* Total number of frames */
	unsigned long long lmb_addr;   	    /* start addr of LMB */
	size64_t	lmb_size;	    /* Size of LMB being added */
};

/*
 * SPLPAR parameters. Changes in variable weight is NOT notified to kextns.
 */
struct dri_cpu_capacity {
	uint64_t	ent_capacity;	/* partition current entitled capacity*/
	int		delta_ent_cap;	/* delta capacity added/removed*/
	int		status;		/* capacity update constrained or not */
};

/*
 * dri_cpu_capacity.status flags.
 */
#define	CAP_UPDATE_SUCCESS	0x0
#define	CAP_UPDATE_CONSTRAINED	0x1

/*
 * Info passed to the kernel extentions during partition migration operation.
 */
struct dri_pmig {
	int		version;	/* changes when new fields are added. */
	int		dest_lpid;
	long long	streamid;
	unsigned int	selfarp_secs;
	int		pad[3];
};

extern int	reconfig_register( int (*)(void *, void *, int, void *),
			   int, void * , ulong *, char *);  /* deprecated */
extern int	reconfig_register_ext( int (*)(void *, void *, 
						unsigned long long, void *),
			   unsigned long long, void * , ulong *, char *);
extern int	reconfig_unregister(ulong);
extern void	reconfig_complete(void *, int);
extern void	dr_mem_sync(void);


#endif /* _KERNEL */

/*
 * These commands specify what lpar info is to be retrieved.
 */
#define LPAR_INFO_FORMAT1	1 /* command for retrieving LPAR format1 info */
#define LPAR_INFO_FORMAT2	2 /* command for retrieving LPAR format2 info */

#define PROC_MODULE_INFO        4 /* command for retrieving processor module
                                   * format info */
#define NUM_PROC_MODULE_TYPES   5 /* command for retrieving the module count
                                   * prior to requesting processor module 
                                   * information */
/*
 * eWLM uses lpar_set_resources() call to modify the following SPLPAR
 * resource attributes (lpar_resource_id).
 */

#define __SPLPAR_ENT_CAPACITY	1	/* Entitled Processor Capacity	  */
#define __SPLPAR_VAR_WEIGHT	2	/* Variable Processor Capacity Wt */
#define __SPLPAR_CUR_INTER_CAP	3	/* OS/400: current interactive Cap*/
#define __SPLPAR_NUM_VCPUS	4	/* # of logical(virtual) CPUS available
					 * to this LPAR
					 */
#define __SPLPAR_PARTITION_MEM	5	/* MB of memory available to the OS*/

/* lpar_set_resources() return codes */

#define LPAR_SRES_PARAMINVALID	-1	/* Invalid parameters */
#define LPAR_SRES_CONFNOTSUP	-2	/* configuration constraint */
#define LPAR_SRES_HWERROR	-3	/* Hardware/Firmware error */
#define LPAR_SRES_NOPERM	-4	/* Insufficient authority */
#define LPAR_SRES_EXCEPTION	-5	/* failed due to an Exception */
#define LPAR_SRES_EXIST		-99	/* resource already exist */
#define LPAR_SRES_BUSY		-98	/* resource is busy */
#define LPAR_SRES_UNAVAIL	-97	/* resource temporarily unavailable */
#define LPAR_SRES_ALLOC		-96	/* resource allocation failed */
#define LPAR_SRES_INTERROR	-95	/* Internal errors */
#define LPAR_SRES_NOTREADY	-94	/* resource is not ready */
#define LPAR_SRES_NOTSUP	-93	/* Operation not supported */
#define LPAR_SRES_IOERROR	-92	/* operation failed due to I/O error */
#define LPAR_SRES_INPROGRESS	-91	/* operation in progress */
#define LPAR_SRES_NOTAVAIL	-90	/* resource not available */
#define LPAR_SRES_NOTINARANGE	-89	/* parameter is out of range */

/*
 * LPAR Information structures
 *   - used by lpar_get_info system call
 *   - used by klpar_get_info kernel service
 */

typedef struct lpar_info_format1_t {

	int	 version;		/* version for this structure */
	int	 pad0;
	uint64_t max_memory;            /* MB of max memory lpar can support*/
        uint64_t min_memory;            /* MB of min memory defined for lpar */
	uint64_t memory_region;		/* size in bytes of one LMB */
        uint64_t dispatch_wheel_time;   /* Time of dispatch wheel in nsecs */

        uint     lpar_number;            /* Assigned LPAR number */
        uint     lpar_flags;             /* Logical Partition Flags */
#define LPAR_INFO1_LPAR_CAPABLE	  0x001  /* LPAR Capable System */
#define LPAR_INFO1_LPAR_ENABLED	  0x002  /* LPAR System */
#define LPAR_INFO1_DR_CAPABLE  	  0x004  /* DLPAR Capable */
#define LPAR_INFO1_SMT_CAPABLE    0x008  /* SMT Capable */
#define LPAR_INFO1_SMTBOUND       0x010  /* SMT Threads bound */
#define LPAR_INFO1_SPLPAR_CAPABLE 0x020  /* SPLPAR Capable */
#define LPAR_INFO1_SHARED 	  0x040  /* Shared Partition */
#define LPAR_INFO1_PMIG_CAPABLE	  0x080  /* Partition is migration capable */
#define LPAR_INFO1_MSP_CAPABLE    0x100  /* Mover Service Partition */
#define LPAR_INFO1_DONATE_CAPABLE 0x200  /* LPAR Idle Cycle Donation capable */
#define LPAR_INFO1_DONATE_ENABLED 0x400  /* LPAR Idle Cycle Donation enabled */

        uint     max_pcpus_in_sys;      /* max# physCPUs possible in system 
					 * including unlicenced and potentially
					 * hot-pluggable CPUs
					 */
        uint     min_vcpus;             /* min # of virtual cpus in this 
					 * LPAR definition
					 */
        uint     max_vcpus;             /* max # of virtual cpus this 
					 * LPAR can support 
					 */

        uint     min_lcpus;             /* min # of logical cpus */
        uint     max_lcpus;             /* max # of logical cpus this LPAR 
					 * can support 
					 */

        uint     minimum_capacity;      /* Minimum Processor Capacity */
        uint     maximum_capacity;      /* Maximum Processor Capacity */
        uint     capacity_increment;    /* Processor Capacity change granule */

        ushort   smt_threads;           /* # of SMT threads per CPU*/
        char     pad1[6];           	/* added for 8-byte alignment */

#define LPAR_NAME_LEN1	256
        char     lpar_name[LPAR_NAME_LEN1]; /* LPAR name assigned at HMC */

	uint	 desired_capacity;	/* Partition capacity defined by HMC */
	uint	 desired_vcpus;		/* virtual processors defined by HMC */
	uint64_t desired_memory;	/* memory defined by HMC */
	uint	 desired_variable_capwt;/* variable cap weight defined by HMC */
        char     pad2[12];           	/* Reserved for future */

} lpar_info_format1_t;


typedef struct lpar_info_format2_t {

	int	 version;		/* version for this structure */
	int	 pad0;

        uint64_t online_memory;         /* MB of currently online memory */
        uint64_t tot_dispatch_time;     /* Total lpar dispatch time in nsecs */
        uint64_t pool_idle_time;        /* Idle time of shared CPU pool nsecs*/
        uint64_t dispatch_latency;      /* Max latency inbetween dispatches */
                                        /* of this LPAR on physCPUS in nsecs */
        uint     lpar_flags;       
#define LPAR_INFO2_CAPPED       0x01    /* Parition Capped */
#define LPAR_INFO2_AUTH_PIC     0x02    /* Authority granted for poolidle*/
#define LPAR_INFO2_SMT_ENABLED  0x04    /* SMT Enabled */
#define LPAR_INFO2_EXTENDED	0x10    /* Extended shared processor pool 
					 * information */

        uint     pcpus_in_sys;          /* # of active licensed physical CPUs 
					 * in system */
        uint     online_vcpus;          /* # of current online virtual CPUs */
        uint     online_lcpus;          /* # of current online logical CPUs */
        uint     pcpus_in_pool;         /* # physical CPUs in shared pool */
        uint     unalloc_capacity;      /* Unallocated Capacity available 
					 * in shared pool */
        uint     entitled_capacity;     /* Entitled Processor Capacity for this
 					 * partition */
        uint     variable_weight;       /* Variable Processor Capacity
					 * Weight */
        uint     unalloc_weight;        /* Unallocated Variable Weight
					 * available for this partition */
        uint     min_req_vcpu_capacity; /* OS minimum required virtual
					 * processor capacity. */

        ushort   group_id;              /* ID of a LPAR group/aggregation */
        ushort   pool_id;               /* ID of a shared pool */

	/* The following 9 fields are only valid if LPAR_INFO2_EXTENDED
	 * is set */
        uint     shcpus_in_sys;         /* # of physical processors allocated
					 * for shared processor use */
        uint     max_pool_capacity;     /* Maximum processor capacity of
					 * partition's pool */
        uint     entitled_pool_capacity;/* Entitled processor capacity of
					 * partition's pool */
        uint64_t pool_max_time;         /* Summation of maximum time that could
					 * be consumed by the pool, in 
					 * nanoseconds */
        uint64_t pool_busy_time;        /* Summation of busy time accumulated
					 * across all partitions in the pool,
					 * in nanoseconds */
        uint64_t pool_scaled_busy_time; /* Scaled summation of busy time
					 * accumulated across all partitions in
					 * the pool, in nanoseconds */
        uint64_t shcpu_tot_time;        /* Summation of total time across all
					 * physical processors allocated for
					 * shared processor use, in
					 * nanoseconds */
        uint64_t shcpu_busy_time;       /* Summation of busy time accumulated
					 * across all shared processor
					 * partitions, in nanoseconds */
        uint64_t shcpu_scaled_busy_time;/* Scaled summation of busy time
					 * accumulated across all shared
					 * processor partitions, in
					 * nanoseconds */
} lpar_info_format2_t;

typedef struct proc_module_info_t {

        uint nsockets; /* Number of sockets of this module type        */
        uint nchips;   /* Number of chips of this module type          */
        uint ncores;   /* Number of cores per chip in this module type */
} proc_module_info_t;

/* The following portion is not support until AIX 6.1.  It is being placed
 * in the pre 6.1 header file to support applications that need to be compiled
 * on pre 6.1 but support the WPAR query using lpar_get_info().
 */
#ifndef _CORRALID_H
typedef unsigned short cid_t;
typedef unsigned int ckey_t;
#define WPAR_INFO_FORMAT        3 /* command for retrieving WPAR format1 info */
#endif
typedef struct wpar_info_format_t {

        int   version;                  /* version for this structure */
        ckey_t   wpar_ckey;             /* WPAR static identifier */
        cid_t    wpar_cid;              /* WPAR dynamic identifier */
        uint     wpar_flags;
#define WPAR_INFO_CPU_RSET       0x01   /* WPAR restricted to CPU resource set */
#define WPAR_INFO_PROCESS        0x02   /* Denotes process runs inside WPAR */
#define WPAR_INFO_MOBILE         0x04   /* Denotes WPAR is              */
                                        /* checkpoint/restartable       */
#define WPAR_INFO_APP            0x08   /* Denotes WPAR is application WPAR */
#define WPAR_INFO_CPU_XRSET      0x10   /* WPAR restricted to Exclusive CPU Resource set */
        uint     partition_cpu_limit;   /* Number of logical CPUs in rset or 0 */
        int      percent_cpu_limit;     /* CPU limit in 100ths of % - 1..10000 */
        int      percent_mem_limit;     /* MEM limit in 100ths of % - 1..10000 */
        uint     partition_vcpu_limit;  /* Number of virtual CPUs in rset or 0 */
        char     pad1[32];              /* Reserved for future use */
} wpar_info_format_t;

#ifdef _KERNEL
int alloclmb(long long *, int);
int freelmb(long long);
int klpar_get_info(int command, void *lparinfo_buffer, size_t bufsize);	
#else
int lpar_get_info(int command, void *lparinfo_buffer, size_t bufsize);	
int lpar_set_resources(int lpar_resource_id, void *lpar_resource);	
#endif

#endif /* _H_SYS_DR */
