/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/kernel/sys/ras.h 1.21.1.4                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 2004,2008              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

/* @(#)12       1.21.1.4  src/bos/kernel/sys/ras.h, sysras, bos53Q, q2008_07C1 2/7/08 18:04:56 */

/*
 * COMPONENT_NAME: (sysras) RAS Component Infrastructure
 *
 * FUNCTIONS: 
 *
 * ORIGINS: 27
 */

#ifndef _H_SYSRAS
#define _H_SYSRAS

#include <sys/ras_base.h>
#include <sys/eyec.h>
#include <sys/types.h>
#include <sys/limits.h>
#include <stddef.h>

/* RAS_FILE_ASSERT is meant for sanity checks of basic structures.  If
 * there's a problem, the compiler will complain about a negative
 * array size on the line with the failing assert.
 */
#define RAS_FILE_ASSERT(id,test)				\
	struct CoMpIlE_aSsErT__##id { char v[(test) ? 1 : -1]; }

#ifdef __64BIT__
#define RAS_FIELD_CHECK(__struct, __field, __pos32, __pos64) \
	RAS_FILE_ASSERT(__field, offsetof(__struct, __field) \
					== __pos64)
#else
#define RAS_FIELD_CHECK(__struct, __field, __pos32, __pos64) \
	RAS_FILE_ASSERT(__field, offsetof(__struct, __field) \
					== __pos32)
#endif


/* Eye Catcher Data Types: */

/* 
 * Types for various sizes (1,2,4,8 bytes) of eye-catchers. It is recommended
 * that eye-catchers are declared as the first field in a data structure. Each 
 * component is free to choose the size and contents of the eye-catcher
 * but the recommended size is 8 bytes (for 64-bit kernel). The size of
 * the eye-catcher can be smaller when adding one to an existing data 
 * structure in order not to break binary compatibility.
 */
typedef unsigned char		eye_catch1b_t;
typedef unsigned short		eye_catch2b_t;
typedef unsigned int		eye_catch4b_t;
typedef unsigned long long	eye_catch8b_t;
/* 
 * size variant eye catcher - 4 bytes in 32-bit and 8 bytes in 64-bit 
 */
typedef unsigned long		eye_catch_t;



/* Error Code Data Type: */

/*
 * All kernel functions should return unique and meaningful return codes.
 * Error codes must conform to the global kernel error code guideline.
 * For more details on the format of error codes refer to <sys/kerrno.h>.
 */
typedef long	kerrno_t;

/* ras_block_t is the only thing anyone outside of RAS should really
 * care about.
 */
typedef void *ras_block_t;

/*
 * All kernel structures or fields added in this following structure
 * must be visible under the _RAS_INTERNAL flag.
 * It may break the compilation of some binaries (trcdead, ...) otherwise.
 */

#if (defined _RAS_INTERNAL) || (defined _KERNEL)
/* rasr_block_t is not meant to be used directly. If you need to
 * access one of these fields, use one of the read-only macros below.
 * It is a bug for any code outside of this .h to use the rasr_block_t
 * type.
 *
 * Any additions to the rasr_block_t should be at the end. This
 * structure must maintain binary compatibility, so care should be
 * taken if a field is no longer going to be used (like putting in a
 * dummy default value).
 *
 * Additions to this structure should also be made to RAS_BLOCK_NULL.
 */
struct rasr_block
{
	eye_catch_t	rrb_eyec;
	long		rrb_private;

        /* 
	 * Component Trace Domain properties
	 *  
	 * WARNING: Do not change this structure without updating 
	 *	    ml/POWER/ras_trace.m4.
	 */
			/* Encoded pointer to private trace block */
	long            rrb_trace_private;
			/* The current level of trace for private buffer */
	short	rrb_trace_privlevel;
			/* The current level of trace for system trace mode */
	short     rrb_trace_syslevel;            
			/* = max(rrb_trace_memlevel, rrb_trace_syslevel) */
	short     rrb_trace_level_summary;       
			/* The current level of trace for memory trace mode */
	short     rrb_trace_memlevel;            
					   
	/* 
	 * Error checking domain properties 
	 */
	short	rrb_errchecklevel;
	short	rrb_errlowsev_disp;
	short	rrb_errmedsev_disp;
	short	rrb_pad2;
#ifdef __64BIT__
	long		rrb_reserved[7];
#else
	long		rrb_reserved[6];
#endif
};

typedef struct rasr_block rasr_block_t;

/* Macros to retrieve rasr_block_t values, and compiler asserts to keep the
 * fields in the same place, for binary compatibility.
 */

RAS_FIELD_CHECK(rasr_block_t, rrb_eyec, 0, 0);
#define rasrb_eyec(__rasb) \
	(((const rasr_block_t *)(__rasb))->rrb_eyec)

RAS_FIELD_CHECK(rasr_block_t, rrb_private, 4, 8);
/* Note: the private field is intrinsically private, so no field
 * access macro is defined for it here. The field check should stay
 * here for consistency (so all the field checks are in the same
 * place)
 */
#endif	/* _RAS_INTERNAL || _KERNEL */

/* Constants: */

/* Limits: */
#define	RAS_NAME_MAX	64
#define RAS_DESC_MAX	256
#define RAS_PATH_MAX	1024

/* Domains: */

/* Define the "domains" that interact with the RAS infrastructure.
 * RASD_FIRST <= domain < RASD_LAST
 *
 * Any field or code using a domain should assume this enum goes to
 * 0xF (RASD_LIMIT defined below), in case more domains are added
 * later.
 */
#define RASD_FIRST 	1

enum ras_domain
{
	RASD_TRACE=RASD_FIRST,
	RASD_ERROR,
	RASD_DUMP,
	RASD_LAST
};

#define RASD_LIMIT	0x10

typedef enum ras_domain ras_domain_t;

RAS_FILE_ASSERT( toomanydomains, RASD_LAST < RASD_LIMIT );

/* Anyone using RASD_TO_RASD_FLAG should reserve 2 bytes (16 bits) for
 * domain flags, for extensibility. This gives room to add several
 * more domains.
 */
#define RASD_TO_INDEX(__domain)		( (__domain) - RASD_FIRST )
#define RASD_TO_RASD_FLAG(__domain)	( 1 << RASD_TO_INDEX(__domain) )
#define RASD_FLAG_MASK			0xFFFF

#define RASD_DOMAINS			(RASD_LAST - RASD_FIRST)


/* rascntl / ras_control / ras_callback command structure.
 *
 * The ras_control command has a low byte specifying the domain and a
 * high byte specifying an eye catcher. Macros are provided to extract
 * these.
 */
#define	NOCALLBACK	0x10000ULL		/* avoid calling callback */

/* #define RAS_...	0x00200000ULL */	/* RESERVED for kernel */

typedef unsigned long long ras_cmd_t;

#define RASC_HIGHBYTE_SHIFT	\
	( (sizeof(ras_cmd_t)-1) * 8 )

#define RASC_LOWBYTE_MASK	\
	( (ras_cmd_t)0xFF )

#define RASC_HIGHBYTE_MASK	\
	( RASC_LOWBYTE_MASK << RASC_HIGHBYTE_SHIFT )

#define RASC_GET_DOMAIN(__cmd)	\
	( (ras_cmd_t)(__cmd) & RASC_LOWBYTE_MASK )

#define RASC_GET_COMMAND(__cmd)	\
	( ((ras_cmd_t)(__cmd) & ~(RASC_HIGHBYTE_MASK)) >> 8 )

#define RASC_GET_EYEC(__cmd)	\
	( (ras_cmd_t)(__cmd) & RASC_HIGHBYTE_MASK )

#define RASC_EYEC		\
	( (ras_cmd_t)0x52 << RASC_HIGHBYTE_SHIFT )

/* A macro to help define commands. Note: If __cmd or __dom are too
 * large, this macro will result in a -1L, which won't pass the eye
 * catcher checks in ras_control. This is intentional, since it's a
 * bad command.
 */
#define RASC_COMMAND_BADARGS(__dom, __cmd)	\
	( (((__cmd) << 8) & RASC_HIGHBYTE_MASK)	\
	  || ((__cmd) == 0) 			\
	  || ((__dom) & ~RASC_LOWBYTE_MASK) )

#define RASC_COMMAND(__dom, __cmd)					\
	( (RASC_EYEC							\
	   | ((ras_cmd_t)(__cmd) << 8)					\
	   | ((ras_cmd_t)(__dom)) )					\
	  | ( RASC_COMMAND_BADARGS((ras_cmd_t)(__dom),			\
				   (ras_cmd_t)(__cmd)) ? -1LL : 0) )

RAS_FILE_ASSERT( baddomain, RASC_COMMAND(0x100, 0x1) == -1LL );
RAS_FILE_ASSERT( badcmd,    RASC_COMMAND(0x1,   -1)  == -1LL );

/* Infrastructure ras_control/rascntl commands/domains: */

#define RASC_DOMAIN_GENERAL	0x10
#define RASC_DOMAIN_PATH	0x20	/* Understood by rascntl
					 * or ras_path_control only */

/* RAS_COMMAND_CHECK verifies that __cmd is a valid command
 * and has value __val. The main purpose for this is to be defensive
 * and ensure binary compatability, but this also means that one can
 * search for the hex version of the command in /usr/include/sys and
 * find it.
 */
#define RAS_COMMAND_CHECK(__cmd, __val) \
	RAS_FILE_ASSERT( RAS_COMMAND_ ## __cmd, __cmd == __val )

/* Commands understood by the infrastructure: */

/* General domain, works on both ras_block_t's and paths */
#define RASC_LOGICAL_ALIAS	RASC_COMMAND(RASC_DOMAIN_GENERAL, 0x1)
RAS_COMMAND_CHECK(RASC_LOGICAL_ALIAS,		0x5200000000000110ull);
		  
#define RASC_BLOCK_TO_FULL_PATH	RASC_COMMAND(RASC_DOMAIN_GENERAL, 0x2)
RAS_COMMAND_CHECK(RASC_BLOCK_TO_FULL_PATH,	0x5200000000000210ull);

#define RASC_STAT_COMPONENT	RASC_COMMAND(RASC_DOMAIN_GENERAL, 0x3)
RAS_COMMAND_CHECK(RASC_STAT_COMPONENT, 		0x5200000000000310ull);

/* Path domain, works ony for rascntl / ras_path_control */
#define RASC_ALIAS_TO_FULL_PATH	RASC_COMMAND(RASC_DOMAIN_PATH, 0x1)
RAS_COMMAND_CHECK(RASC_ALIAS_TO_FULL_PATH, 	0x5200000000000120ull);

#define RASC_LIST_COMPONENTS	RASC_COMMAND(RASC_DOMAIN_PATH, 0x2)
RAS_COMMAND_CHECK(RASC_LIST_COMPONENTS,		0x5200000000000220ull);

#define RASC_LIST_ALIASES	RASC_COMMAND(RASC_DOMAIN_PATH, 0x3)
RAS_COMMAND_CHECK(RASC_LIST_ALIASES,		0x5200000000000320ull);

/* RASC_STAT_COMPONENT structure: */

/* Each domain is given 128 bytes in the stat structure as an opaque
 * section of memory for the domain to do with what it wishes. The
 * RASC_STAT_DOMAIN macro below should be used to access the domain
 * specific section in a typed manner.
 */
typedef int ras_stat_domain_t[32];

struct ras_stat
{
	int rstat_eyec;
	int rstat_flags;
	
	char rstat_name[RAS_NAME_MAX];
	char rstat_desc[RAS_DESC_MAX];

	ras_type_t rstat_typesubtype;
	
	int rstat_reserved[8];

	ras_stat_domain_t rstat_domain[RASD_DOMAINS];
};

typedef struct ras_stat ras_stat_t; 

/* ras_register / RASC_STAT_COMPONENT / RASC_LIST_COMPONENTS flags:
 */

#define RASF_TRACE_AWARE		RASD_TO_RASD_FLAG(RASD_TRACE)
#define RASF_ERROR_AWARE		RASD_TO_RASD_FLAG(RASD_ERROR)
#define RASF_DUMP_AWARE			RASD_TO_RASD_FLAG(RASD_DUMP)

/* RASF_REGISTER_FLAGS - Valid ras_register flags: */
#define RASF_REGISTER_FLAGS		((long)0		\
					 | RASF_TRACE_AWARE	\
					 | RASF_ERROR_AWARE	\
					 | RASF_DUMP_AWARE	\
					)

/* STAT / LIST only: */
#define RASF_ISALIAS			0x10000
#define RASF_HASCHILD			0x20000

/* RASC_STAT_DOMAIN: Get domain specific info from ras_stat_t buffer.
 *
 * Example: RASC_STAT_DOMAIN(statbuf, RASD_TRACE, rstat_trace_t *)
 */

#define RASC_STAT_DOMAIN(__rs, __dom, __type) \
	((__type)&((__rs)->rstat_domain[RASD_TO_INDEX(__dom)]))

/* RASC_LIST_COMPONENTS structure: */
struct ras_pathent
{
	int rpent_eyec; /* eyec must stay first */
	int rpent_flags;
	ras_type_t rpent_typesubtype;
	int rpent_reserved[7];
	char rpent_name[RAS_NAME_MAX];
	char rpent_desc[RAS_DESC_MAX];
};

typedef struct ras_pathent ras_pathent_t;

/* The code relies on rpent_eyec being in position 0, so make sure. */
RAS_FIELD_CHECK(ras_pathent_t, rpent_eyec, 0, 0);


/*
 * Definition of an arg parameter of type that may be passed to ras_callback()
 * (component callback) function for certain RAS commands. This structure is
 * size invariant between 32-bit and 64-bit user and kernel space.
 */
struct ras_arg
{
	eye_catch8b_t		arg_eyec;	/* eye catcher for this data */
	unsigned long long	argptr;		/* pointer to arg data	*/
	long long		argsize;	/* size of arg data	*/

};

typedef struct ras_arg ras_arg_t;

/* Prototypes: */

#if (defined _RAS_INTERNAL) || (defined _KERNEL)

typedef kerrno_t (*ras_callback_t)(
	ras_block_t,
	ras_cmd_t,
	void *,
	void *);

#endif /* _RAS_INTERNAL || _KERNEL*/

#ifdef _KERNEL
kerrno_t ras_register(
	ras_block_t *rasbp,
	char *name,
	ras_block_t parent,
	ras_type_t typesubtype,
	char *desc,
	long flags,
	ras_callback_t ras_callback,
	void *callback_data);

kerrno_t ras_control(
	ras_block_t rasb,
	ras_cmd_t cmd,
	void *arg,
	long argsize);

kerrno_t ras_path_control(
	char *path,
	ras_cmd_t cmd,
	void *arg,
	long argsize);

kerrno_t ras_customize(
	ras_block_t rasb);

kerrno_t ras_unregister(
	ras_block_t rasb);

kerrno_t ras_null_callback(
	ras_block_t,
	ras_cmd_t,
	void *,
	void *);

#ifndef __INFREQUENT

#if __IBMC__ >= 900 && __C99_PRAGMA_OPERATOR
#define __INFREQUENT    _Pragma("execution_frequency(very_low)")
#else
#define __INFREQUENT
#endif /* __IBMC__ >= 900 */

#endif /* ! __INFREQUENT */

#endif /* _KERNEL */

/* RAS utility services: */

#if (defined _RAS_INTERNAL) || (defined _KERNEL)

/*
 * This macro is common to both runtime and KDB execution environments.
 * The checker code can call this RASCHK_RT_ONLY that will have the desired
 * code in runtime environment and will be void in KDB environment. 
 */
#ifdef  __RT_RASCHK
#define	RASCHK_RT_ONLY(__statement)	do { __statement; } while(0)
#define	RASCHK_KDB_ONLY(__statement)	do { ; } while(0)
#endif

#ifdef  __KDB_RASCHK
#define	RASCHK_RT_ONLY(__statement)	do { ; } while(0)
#define	RASCHK_KDB_ONLY(__statement)	do { __statement; } while(0)
#endif

/* 
 * void *ENCODE_KPTR(void *ptr, short key) 
 */
#ifdef __64BIT_KERNEL
#define ENCODE_KPTR(__p, __key)	((void *)((ulong)(__p)^((0x8ULL<<60) | \
				   ( ((0x0000FFFFULL)&(__key)) << 44))))
#else
#define ENCODE_KPTR(__p, __key)	((void *)(__p))
#endif

/* 
 * void *DECODE_KPTR(void *ptr, short key) 
 */
#define DECODE_KPTR(__p, __key)	ENCODE_KPTR(__p, __key)

/* 
 * void *INVALID_PTR(int key) 
 */
#ifdef __64BIT_KERNEL
#define INVALID_PTR(__key)	((void *)((0x700DFEEDUL << 32) | (__key)))
#else
#define INVALID_PTR(__key)	((void *)((unsigned long) \
					(0 | ((__key)%0x40))))

#endif /* __64BIT_KERNEL */

#define RAS_BLOCK_INVALID	INVALID_PTR(0x7262)	/* "rb" */

extern const ras_block_t RAS_BLOCK_NULL;

#endif /* _RAS_INTERNAL || _KERNEL */

int rascntl(
	char *path,
	ras_cmd_t cmd,
	void *arg,
	int argsize);

#endif /* _H_SYSRAS */
