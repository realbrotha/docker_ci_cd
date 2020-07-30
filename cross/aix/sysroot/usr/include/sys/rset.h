/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53H src/bos/kernel/sys/rset.h 1.33                                  */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2000,2006          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)25     1.33  src/bos/kernel/sys/rset.h, sysnuma, bos53H, h2006_09B5 2/23/06 14:21:49 */
/*
 * COMPONENT_NAME: (SYSNUMA) Non-Uniform Memory Access
 *
 * FUNCTIONS: NUMA API definitions and prototypes
 *
 * ORIGINS: 83
 */

#ifndef _H_RSET
#define _H_RSET

#include <sys/types.h>

typedef struct subrange subrange_t;

/* Type to identify a resource set handle: rsethandle_t */
typedef void * rsethandle_t;

/* Values to identify a work component or resource: rstype_t */
typedef int rstype_t;
#define R_NADA          0           /* Nothing - invalid specification */
#define R_PROCESS       1           /* Process */
#define R_RSET          2           /* Resource set */
#define R_SUBRANGE	3	    /* Memory range */
#define R_SHM           4 	    /* Shared Memory */
#define R_FILDES        5           /* File identified by an open file */
                                    /* descriptor */
#define R_THREAD        6           /* Thread */



/* Union to contain a work component or resource:  rsid_t */
typedef union {
	pid_t at_pid;           /* Process id (rstype_t R_PROCESS) */
	tid_t at_tid;           /* Kernel thread id (rstype_t R_THREAD) */
	int at_shmid;		/* Shared memory id (if R_SHM) */
	int at_fd;		/* File descriptor (if R_FILDES) */
	rsethandle_t at_rset;	/* Resource set handle (rstype R_RSET) */
        subrange_t *at_subrange;  /* Memory ranges (if R_SUBRANGE) */
	
#ifdef _KERNEL
	ulong_t at_raw_val;	/* raw value: used to avoid copy typecasting */
#endif
} rsid_t;

/* Structure to specify a set of memory subranges attachment: subrange_t */
struct subrange {
           off64_t su_offset;           /* Offset of the subrange (bytes) */
           size64_t su_length;          /* Length of the subrange (bytes) */
                                        /* 0 indicates an extent from
					 * the offset to the end of
					 * the object. */
           rstype_t su_rstype;          /* Type of resource the subrange */
                                        /* is being attached to  */
	   uint_t su_policy;            /* Memory allocation policy */
           rsid_t su_rsid;              /* Id of the resource the subrange */
                                        /* is being attached to  */
           off64_t su_rsoffset;         /* reserved for future use */
           size64_t su_rslength;        /* reserved for future use */
};

/* Structure to describe a resource attachment */
typedef struct attachinfo { 
           rstype_t at_rstype;		/* Type of resource */
           rsid_t at_rsid;		/* Id of the resource */
           uint_t at_policy;		/* Allocation policy */
           int pad0;			/* 64 bit padding */
           struct attachinfo *next_resource; /* Next involved resource */
} attachinfo_t; 

/*
 * Structure passed to ra_mmap: contains the mmap characterics
 * - code depends on this being ILP32/LP64 size-invariant
 */
typedef struct mmap_struct {
        uint64_t mm_addr;
        size64_t mm_len;
        off64_t  mm_pos;
        int      mm_prot;
        int      mm_flags;
        int      mm_fd;
} mmap_struct_t;


/* Values to identify memory and other policies */
#define P_DEFAULT       0               /* Default memory policy */
#define P_FIRST_TOUCH   1               /* First Access memory policy */
#define P_BALANCED      2               /* Balanced memory policy */

#define R_MEMP_MASK	0x000000ff	/* 256 possible memory policies */
#define R_ATTACH_STRSET 0x00000100	/* ST Rset scheduling policy */	

#define R_DETACH_ALLTHRDS 0x00000001	/* Detach all threads in a process */

#ifdef _KERNSYS
/* Kernel only, macros that operate on memory placement policies */
#define VALID_POLICY(p) ( p >= 0 && p <= P_BALANCED ) 
#define EQUAL_POLICY(p1, p2) (				\
	 p1 == p2 ||					\
	 ( (p1 == P_BALANCED || p1 == P_DEFAULT) &&	\
	   (p2 == P_BALANCED || p2 == P_DEFAULT) ) )		
#endif

/* Value to identify current execution object */
#define RS_MYSELF       (-1)

/* Bit layout for flags parameter */
#define R_TYPE_MASK     0x000000FF  /* bits 24-31 are types */
#define R_AVAIL_MASK    0x0000FF00  /* bits 16-23 are availability */

/* Values passed to rs_alloc: */
#define RS_EMPTY        0           /* Resource set with no resources */
#define RS_SYSTEM       1           /* Resource set with system resources */
#define RS_ALL          2           /* Resource set with all resources */
#define RS_PARTITION    3           /* Resource set with calling process's */
                                    /* partition rset resources */

/* Values to identify type of information requested: rsinfo_t */
typedef int rsinfo_t;
#define R_NUMPROCS      0           /* Number of processors */
#define R_NUMMEMPS      1           /* Number of memory pools */
#define R_MEMSIZE       2           /* Memory size (in MBytes) */
#define R_MAXSDL        3           /* Maximum system detail level */
#define R_SMPSDL        4           /* SMP system detail level */
#define R_MCMSDL        5           /* MCM system detail level */
#define R_MAXPROCS      6           /* Maximum number of processors in rset */
#define R_MAXMEMPS      7           /* Maximum number of memory pools in rset */
#define R_LGPGFREE      8           /* Number of free large pages in rset */
#define R_LGPGDEF       9           /* Number of defined large pages in rset */
#define R_SHMATTCAP	10          /* Support for ra_shmget(v) interfaces */
#define R_L2CSDL	11	    /* L2 cache system detail level */
#define R_PCORESDL	12	    /* Processor Core system detail level */


/* Values to identify a physical resource type for rs_op() and others */
#define R_PROCS         1           /* Processors */
#define R_MEMPS         2           /* Memory pools */
#define R_ALL_RESOURCES (R_MEMPS | R_PROCS)

/*
 * Commands for rs_op():
 * RS_UNION and RS_EXCLUSION may be also used for rs_getrad flags.
 */
#define RS_UNION        1           /* Union */
#define RS_INTERSECTION 2           /* Intersection */
#define RS_EXCLUSION    3           /* Exclusion */
#define RS_COPY         4           /* Resource set to resource set copy */
#define RS_FIRST        5           /* First resource of a given type */
#define RS_NEXT         6           /* Resource following a specified one */
#define RS_NEXT_WRAP    7           /* Resource following a specified one */
                                    /* in a resource set, with wrapping */
                                    /* for the last resource */
#define RS_ISEMPTY      8           /* Emptiness */
#define RS_ISEQUAL      9           /* Equality */
#define RS_ISCONTAINED  10          /* Inclusion */

#define RS_TESTRESOURCE 11          /* Test if resource in rset */
#define RS_ADDRESOURCE  12          /* Add resource to rset */
#define RS_DELRESOURCE  13          /* Delete resource from rset */
#define RS_STSET  	14          /* Get ST rset */

/*
 * Flags for rs_op():
 */
#define RS_NON_EXCLUSIVE    0x00000001

/*
 * Attached rset types
 */
#define RS_EFFECTIVE_RSET             2       /* process effective rset */
#define RS_PARTITION_RSET             3       /* process partition rset */
#define RS_DEFAULT_RSET               4       /* Default rset           */
#define RS_THREAD_RSET                5       /* Thread effective rset  */
#define RS_THREAD_PARTITION_RSET      6       /* Thread partition rset  */

/* Value to specify default rset to rs_setpartition() */
#define RS_DEFAULT	((rsethandle_t)RS_DEFAULT_RSET)

/* Maximum length of a RAD name */
#define RAD_NAME_SIZE   32

/* Maximum length of a registered Rset name or namespace */
#define RSET_NAME_SIZE  255

/* Commands passed to rs_registername: */
#define RS_DEFINE       0           /* The name's registration is not */
                                    /* modified if it already exists */
#define RS_REDEFINE     1           /* The name's registration is */
                                    /* modified if it already exists */

/* structure for rs_getnameattr and rs_setnameattr */
typedef struct rs_attributes {
        uid_t owner; gid_t group; uint_t mode;
} rs_attributes_t;

/* Commands passed to rs_setnameattr: */
#define RS_OWNER        1           /* Set owner attribute */
#define RS_GROUP        2           /* Set group attribute */
#define RS_PERM         4           /* Set permission attribute */

/* Values to identify the resource sets types */
#define RS_PERMMASK     0000666     /* to extract permission from mode */
#define RS_TYPMASK      0003000     /* to extract type from mode */
#define RS_APPDEF       0000000     /* Application-defined Rset */
#define RS_SYSADM       0001000     /* System-Admin. defined Rset */
#define RS_SYSRAD       0002000     /* System RAD */

/* Values to identify the resource sets names access rights */
#define RS_IRUSR        0000400     /* read permission: owner */
#define RS_IWUSR        0000200     /* write permission: owner */
#define RS_IRGRP        0000040     /* read permission: group */
#define RS_IWGRP        0000020     /* write permission: group */
#define RS_IROTH        0000004     /* read permission: other */
#define RS_IWOTH        0000002     /* write permission: other */

#ifdef _NO_PROTO

extern int rs_numrads();
extern int rs_getrad();
extern int rs_getinfo();
extern int rs_alloc();
extern void rs_free();
extern int rs_init();
extern int rs_op();

extern int rs_registername();
extern int rs_getnameattr();
extern int rs_setnameattr();
extern int rs_discardname();
extern int rs_getnamedrset();

extern pid_t ra_fork();
extern int ra_execl();
extern int ra_execle();
extern int ra_execlp();
extern int ra_execv();
extern int ra_execve();
extern int ra_execvp();
extern int ra_exect();

extern int ra_attachrset();
extern int ra_detachrset();
extern int ra_getrset();

extern int ra_shmget();
extern int ra_shmgetv();

extern void *ra_mmap();
extern void *ra_mmapv();

extern int rs_getpartition();
extern int rs_setpartition();

extern int rs_getassociativity();
extern attachinfo_t *ra_get_attachinfo();
extern int ra_free_attachinfo();

#else /* _NO_PROTO */

/* rset services */
extern int rs_numrads(rsethandle_t rseth,
                    uint_t sdl,
                    uint_t flags);

extern int rs_getrad(rsethandle_t rseth_in,
                    rsethandle_t rseth_out,
                    uint_t sdl,
                    uint_t index,
                    uint_t flags);

extern int rs_getinfo(rsethandle_t rseth,
                    rsinfo_t info_type,
                    uint_t flags);

extern rsethandle_t rs_alloc(uint_t flags);

extern void rs_free(rsethandle_t rseth);

extern int rs_init(rsethandle_t rseth,
                    uint_t flags);

extern int rs_op(uint_t command,
                    rsethandle_t rseth1,
                    rsethandle_t rseth2,
                    uint_t flags,
                    uint_t id);

/* registry services */
extern int rs_registername(rsethandle_t rseth,
                    char *name_space,
                    char *name,
                    uint_t mode,
                    uint_t command);

extern int rs_getnameattr(char *name_space,
                    char *name,
                    rs_attributes_t *attr);

extern int rs_setnameattr(char *name_space,
                    char *name,
                    uint_t command,
                    rs_attributes_t *attr);

extern int rs_discardname(char *name_space,
                    char *name);

extern int rs_getnamedrset(char *name_space,
                    char *name,
                    rsethandle_t rseth);

/* attachment services */
extern pid_t ra_fork(rstype_t rstype_resource,
                    rsid_t rsid_resource,
                    uint_t flags);

extern int ra_execl(rstype_t, rsid_t, uint_t, const char *, ...);
extern int ra_execle(rstype_t, rsid_t, uint_t, const char *, ...);
extern int ra_execlp(rstype_t, rsid_t, uint_t, const char *, const char *, ...);
extern int ra_execv(rstype_t, rsid_t, uint_t, const char *, char *const[]);
extern int ra_execve(rstype_t, rsid_t, uint_t, const char *, char *const[],
                     char *const[]);
extern int ra_execvp(rstype_t, rsid_t, uint_t, const char *, char *const[]);
extern int ra_exect(rstype_t, rsid_t, uint_t, char *, char *[], char *[]);

extern int ra_attachrset(rstype_t rstype_work_component,
                    rsid_t rsid_work_component,
                    rsethandle_t rseth,
                    uint_t flags);

extern int ra_detachrset(rstype_t rstype_work_component,
                    rsid_t rsid_work_component,
                    uint_t flags);

extern int ra_getrset(rstype_t rstype_work_component,
                    rsid_t rsid_work_component,
                    uint_t flags,
                    rsethandle_t rseth);

extern int ra_shmget(key_t key, size_t size, int shmflg, rstype_t rstype,
		     rsid_t rsid, uint_t policy);
extern int ra_shmgetv(key_t key, size_t size, int shmflg, int rangecnt,
		      subrange_t *user_subranges);

extern void * ra_mmap( void *addr, size_t len, int prot, int flags,
		       int fildes, off64_t off, rstype_t rstype,
		       rsid_t rsid, uint policy );
extern void * ra_mmapv( void *addr, size_t len, int prot, int flags,
		        int fildes, off64_t off, int rangecnt,
			subrange_t *user_subranges );


/* partition services */
extern int rs_getpartition(pid_t pid,
                    rsethandle_t rseth);

extern int rs_setpartition(pid_t pid,
                    rsethandle_t rseth,
                    uint_t flags);

extern int rs_getassociativity(uint_t type,
		    uint_t id,
		    uint_t *associativity_array,
		    uint_t associativity_array_size);

extern attachinfo_t *ra_get_attachinfo(rstype_t rstype,
                    rsid_t rsid,
                    off64_t offset,
                    size64_t length,
                    uint_t flags);    

extern int ra_free_attachinfo(attachinfo_t *info);
#endif /* _NO_PROTO */

#if defined(_KERNEL)

#if !defined(_H_PROCESSOR)
#include <sys/processor.h>
#endif

/* Define an anonymous alias for the system rset */
#define RS_SYSRSET      NULL

extern int krs_numrads(rsethandle_t rseth,
                    uint_t sdl,
                    uint_t flags);

extern int krs_getrad(rsethandle_t rseth,
                    uint_t sdl,
                    uint_t index,
                    uint_t flags);

extern int krs_getinfo(rsethandle_t rseth,
                    rsinfo_t info_type,
                    uint_t flags,
		    int *result);

extern int krs_alloc(rsethandle_t *rseth,
                    uint_t flags);

extern void krs_free(rsethandle_t rseth);

extern int krs_init(rsethandle_t rseth,
                    uint_t flags);

extern int krs_op(uint_t command,
                    rsethandle_t rseth1,
                    rsethandle_t rseth2,
                    uint_t flags,
                    uint_t id);

extern int kra_creatp(pid_t *pid,
                    rstype_t rstype_resource,
                    rsid_t rsid_resource,
                    uint_t flags);

extern int kra_attachrset(rstype_t rstype_work_component,
                    rsid_t rsid_work_component,
                    rsethandle_t rseth,
                    uint_t flags);

extern int kra_detachrset(rstype_t rstype_work_component,
                    rsid_t rsid_work_component,
                    uint_t flags);

extern int kra_getrset(rstype_t rstype_work_component,
                    rsid_t rsid_work_component,
                    uint_t flags,
                    rsethandle_t rseth,
                    uint_t *rset_type);

extern int krs_getpartition(pid_t pid,
                    uint_t flags,
                    rsethandle_t rseth,
                    uint_t *rset_type);

extern int krs_setpartition(pid_t pid,
                    rsethandle_t rseth,
                    uint_t flags);

extern int krs_getassociativity(uint_t type,
                    uint_t l_id,        
                    uint_t *assoc,              
                    uint_t len);  

extern uint_t krs_radid(uint_t sdl);

#endif          /* _KERNEL */

#endif /*_H_RSET*/


