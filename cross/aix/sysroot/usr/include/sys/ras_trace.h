/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/sys/ras_trace.h 1.15.1.5                         */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 2005,2009              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)71	1.15.1.5  src/bos/kernel/sys/ras_trace.h, sysras, bos53X, x2009_46B0 11/11/09 11:59:49 */

#ifndef _H_RAS_TRACE
#define _H_RAS_TRACE

#include <sys/ras.h>

#include <sys/types.h>
#include <sys/trcmacros.h>

#ifdef _KERNEL

/* Macros to retrieve rasr_block_t values, and compiler asserts to keep the
 * fields in the same place, for binary compatibility.
 */

RAS_FIELD_CHECK(rasr_block_t, rrb_trace_private, 8, 16);
#define rasrb_trace_private(__rasb) \
	(((const rasr_block_t *)(__rasb))->rrb_trace_private)

RAS_FIELD_CHECK(rasr_block_t, rrb_trace_privlevel, 12, 24);
#define rasrb_trace_memlevel(__rasb) \
	(((const rasr_block_t *)(__rasb))->rrb_trace_memlevel)

RAS_FIELD_CHECK(rasr_block_t, rrb_trace_syslevel, 14, 26);
#define rasrb_trace_syslevel(__rasb) \
	(((const rasr_block_t *)(__rasb))->rrb_trace_syslevel)

RAS_FIELD_CHECK(rasr_block_t, rrb_trace_level_summary, 16, 28);
#define rasrb_trace_level_summary(__rasb) \
	(((const rasr_block_t *)(__rasb))->rrb_trace_level_summary)

RAS_FIELD_CHECK(rasr_block_t, rrb_trace_memlevel, 18, 30);
#define rasrb_trace_privlevel(__rasb) \
	(((const rasr_block_t *)(__rasb))->rrb_trace_privlevel)
#endif	/* _KERNEL */

/* Available levels of trace for both system and memory mode */
enum {
    CT_LEVEL_0,
    CT_LEVEL_1,
    CT_LEVEL_2,
    CT_LEVEL_3,
    CT_LEVEL_4,
    CT_LEVEL_5,
    CT_LEVEL_6,
    CT_LEVEL_7,
    CT_LEVEL_8,
    CT_LEVEL_9
};

#define CT_LVL_MINIMAL CT_LEVEL_1
#define CT_LVL_NORMAL  CT_LEVEL_3
#define CT_LVL_DETAIL  CT_LEVEL_7
#define CT_LVL_MAXIMAL CT_LEVEL_9
/* Default memtrc level.  In AIX5.4 and beyond it will be CT_LVL_NORMAL. */
#define CT_LVL_DEFAULT CT_LVL_MINIMAL
/* Default systrc level. */
#define CT_SYSTRC_LVL_DEFAULT CT_LVL_NORMAL

/* Flags */
/* Some of them are only used by private kernel part */
/* But all are exported for simplicity */
#define CT_MEMTRC_SUSPEND     0x1   /* The memory trace mode is suspended */
#define CT_MEMTRC_TURNING_ON  0x2   /* The memory trace mode is being turned on */
#define CT_MEMTRC_TURNING_OFF 0x4   /* The memory trace mode is being turned off */
#define CT_MEMTRC_SAVE        0x8   /* The private memory buffer is being saved */
#define CT_MEMTRC_RESIZE      0x10  /* The private memory buffer is being resized*/
#define CT_SYSTRC_ON          0x20  /* The system trace mode is on */
#define CT_SERIALIZED         0x40  /* Component Trace must serialize trace
				       entries */
#define CT_CUSTOMIZED         0x80  /* The component has been customized */

#define CT_MEMTRC_RESUMING    0x200 /* SYNC state for RESUME in
				       rasp_trace_control() */

#define CT_MEMTRC_NOBUFFER    0x80000000 /* The component has no private buffer 
				       	    allocated (used only by 
					    rasp_trace_stat and ctctrl) */

/* This structure size must not exceed 128 bytes */
struct rstat_trace {
    unsigned long long rst_filltime; /* The estimated time to fill the buffer */
    short rst_memlvl;          /* The level of trace for memory trace mode */
    short rst_syslvl;          /* The level of trace for system trace mode */
    uint_t rst_flags;                /* Trace flags */
    uint_t rst_bufsize;              /* The current size of the memory buffer */

    int rstat_trace_reserved[27];
};

typedef struct rstat_trace rstat_trace_t;

RAS_FILE_ASSERT(rstat_trace_size,
                sizeof(rstat_trace_t) <= sizeof(ras_stat_domain_t));

/* Command basis */
enum {
	_CT_MEMTRC_ON = 1,
	_CT_MEMTRC_OFF,
	_CT_MEMTRC_SUSPEND,
	_CT_MEMTRC_RESUME,
	_CT_SYSTRC_ON,
	_CT_SYSTRC_OFF,
	_CT_MEMTRC_LVL,
	_CT_SYSTRC_LVL,
	_CT_MEMBUFSIZE,
	_CT_DR_MEM,
	_CT_PASS_THROUGH,
	_CT_SERIALIZED,
	_CT_GETBUFFER,
	_CT_ALLOC_BUFFER,
	_CT_FREE_BUFFER,
	_CT_MEMTRC_DISABLE,
	_CT_MEMTRC_ENABLE
};



/* Callback commands */
#define RASCT_MEMTRC_ON            RASC_COMMAND(RASD_TRACE, _CT_MEMTRC_ON)
RAS_COMMAND_CHECK(RASCT_MEMTRC_ON,		0x5200000000000101ull);
#define RASCT_MEMTRC_OFF           RASC_COMMAND(RASD_TRACE, _CT_MEMTRC_OFF)
RAS_COMMAND_CHECK(RASCT_MEMTRC_OFF,		0x5200000000000201ull);
#define RASCT_MEMTRC_SUSPEND       RASC_COMMAND(RASD_TRACE, _CT_MEMTRC_SUSPEND)
RAS_COMMAND_CHECK(RASCT_MEMTRC_SUSPEND,		0x5200000000000301ull);
#define RASCT_MEMTRC_RESUME        RASC_COMMAND(RASD_TRACE, _CT_MEMTRC_RESUME)
RAS_COMMAND_CHECK(RASCT_MEMTRC_RESUME,		0x5200000000000401ull);
#define RASCT_SYSTRC_ON            RASC_COMMAND(RASD_TRACE, _CT_SYSTRC_ON)
RAS_COMMAND_CHECK(RASCT_SYSTRC_ON,		0x5200000000000501ull);
#define RASCT_SYSTRC_OFF           RASC_COMMAND(RASD_TRACE, _CT_SYSTRC_OFF)
RAS_COMMAND_CHECK(RASCT_SYSTRC_OFF,		0x5200000000000601ull);
#define RASCT_MEMTRC_LVL           RASC_COMMAND(RASD_TRACE, _CT_MEMTRC_LVL)
RAS_COMMAND_CHECK(RASCT_MEMTRC_LVL,		0x5200000000000701ull);
#define RASCT_SYSTRC_LVL           RASC_COMMAND(RASD_TRACE, _CT_SYSTRC_LVL)
RAS_COMMAND_CHECK(RASCT_SYSTRC_LVL,		0x5200000000000801ull);
#define RASCT_MEMBUFSIZE           RASC_COMMAND(RASD_TRACE, _CT_MEMBUFSIZE)
RAS_COMMAND_CHECK(RASCT_MEMBUFSIZE,		0x5200000000000901ull);
#define RASCT_DR_MEM               RASC_COMMAND(RASD_TRACE, _CT_DR_MEM)
RAS_COMMAND_CHECK(RASCT_DR_MEM,		        0x5200000000000A01ull);
#define RASCT_PASS_THROUGH         RASC_COMMAND(RASD_TRACE, _CT_PASS_THROUGH)
RAS_COMMAND_CHECK(RASCT_PASS_THROUGH,		0x5200000000000B01ull);

/* 
 * persistence switches used only by the framework, invalid for the
 * component callbacks.
 */
#define RASCT_MEMTRC_DISABLE       RASC_COMMAND(RASD_TRACE, _CT_MEMTRC_DISABLE)
RAS_COMMAND_CHECK(RASCT_MEMTRC_DISABLE,		0x5200000000001001ull);
#define RASCT_MEMTRC_ENABLE        RASC_COMMAND(RASD_TRACE, _CT_MEMTRC_ENABLE)
RAS_COMMAND_CHECK(RASCT_MEMTRC_ENABLE,		0x5200000000001101ull);

#ifdef _KERNEL

#define RASCT_SET_MEMTRC_SUSPEND   \
        RASC_COMMAND(RASD_TRACE, _CT_MEMTRC_SUSPEND | NOCALLBACK)
RAS_COMMAND_CHECK(RASCT_SET_MEMTRC_SUSPEND,		0x5200000001000301ull);
#define RASCT_SET_MEMTRC_RESUME    \
        RASC_COMMAND(RASD_TRACE, _CT_MEMTRC_RESUME  | NOCALLBACK)
RAS_COMMAND_CHECK(RASCT_SET_MEMTRC_RESUME,		0x5200000001000401ull);
#define RASCT_SET_SYSTRC_ON        \
        RASC_COMMAND(RASD_TRACE, _CT_SYSTRC_ON      | NOCALLBACK)
RAS_COMMAND_CHECK(RASCT_SET_SYSTRC_ON,		        0x5200000001000501ull);
#define RASCT_SET_SYSTRC_OFF       \
        RASC_COMMAND(RASD_TRACE, _CT_SYSTRC_OFF     | NOCALLBACK)
RAS_COMMAND_CHECK(RASCT_SET_SYSTRC_OFF,		        0x5200000001000601ull);
#define RASCT_SET_MEMTRC_LVL       \
        RASC_COMMAND(RASD_TRACE, _CT_MEMTRC_LVL     | NOCALLBACK)
RAS_COMMAND_CHECK(RASCT_SET_MEMTRC_LVL,		        0x5200000001000701ull);
#define RASCT_SET_SYSTRC_LVL       \
        RASC_COMMAND(RASD_TRACE, _CT_SYSTRC_LVL     | NOCALLBACK)
RAS_COMMAND_CHECK(RASCT_SET_SYSTRC_LVL,		        0x5200000001000801ull);
#define RASCT_SET_MEMBUFSIZE       \
        RASC_COMMAND(RASD_TRACE, _CT_MEMBUFSIZE     | NOCALLBACK)
RAS_COMMAND_CHECK(RASCT_SET_MEMBUFSIZE,		        0x5200000001000901ull);
#define RASCT_SET_CT_SERIALIZED    \
        RASC_COMMAND(RASD_TRACE, _CT_SERIALIZED     | NOCALLBACK)
RAS_COMMAND_CHECK(RASCT_SET_CT_SERIALIZED,              0x5200000001000C01ull);

#endif /* _KERNEL */

/* This command is a private command and must not be called from the component*/
#define RASCT_GETBUFFER            \
        RASC_COMMAND(RASD_TRACE, _CT_GETBUFFER      | NOCALLBACK)
RAS_COMMAND_CHECK(RASCT_GETBUFFER,                      0x5200000001000D01ull);

#ifdef _KERNEL
#define RASCT_SET_ALLOC_BUFFER     \
        RASC_COMMAND(RASD_TRACE, _CT_ALLOC_BUFFER   | NOCALLBACK)
RAS_COMMAND_CHECK(RASCT_SET_ALLOC_BUFFER,               0x5200000001000E01ull);
#define RASCT_SET_FREE_BUFFER      \
        RASC_COMMAND(RASD_TRACE, _CT_FREE_BUFFER    | NOCALLBACK)
RAS_COMMAND_CHECK(RASCT_SET_FREE_BUFFER,                0x5200000001000F01ull);
#endif /* _KERNEL */

#ifdef _KERNEL

/* Memory destination flags */
/* The trace is stored in the rare buffer of Lightweight Memory Trace */
#define MT_RARE    0x1 
/* The trace is stored in the common buffer of Lightweight Memory Trace */
#define MT_COMMON  0x2
/* The trace is stored in private buffer of the component */
#define MT_PRIV    0x4
/* The trace may be stored in the system trace */
#define MT_SYSTEM  0x8

/* non-generic trace function prototypes */
void ct_hook0(ras_block_t cb, ulong_t hkwd);
void ct_hook1(ras_block_t cb, ulong_t hkwd, ulong_t d1);
void ct_hook2(ras_block_t cb, ulong_t hkwd, ulong_t d1, ulong_t d2);
void ct_hook3(ras_block_t cb, ulong_t hkwd, ulong_t d1, ulong_t d2, ulong_t d3);
void ct_hook4(ras_block_t cb, ulong_t hkwd, ulong_t d1, ulong_t d2, ulong_t d3, 
	      ulong_t d4);
void ct_hook5(ras_block_t cb, ulong_t hkwd, ulong_t d1, ulong_t d2, ulong_t d3, 
	      ulong_t d4, ulong_t d5);

#if __IBMC__
#pragma isolated_call(ct_hook0)
#pragma isolated_call(ct_hook1)
#pragma isolated_call(ct_hook2)
#pragma isolated_call(ct_hook3)
#pragma isolated_call(ct_hook4)
#pragma isolated_call(ct_hook5)
#endif

/* ctfunc_hookx trace function prototypes */
void ctfunc_hook0(ras_block_t cb, unsigned long long hwlvldest);
void ctfunc_hook1(ras_block_t cb, unsigned long long hwlvldest, ulong d1);
void ctfunc_hook2(ras_block_t cb, unsigned long long hwlvldest, ulong d1,
	ulong d2);
void ctfunc_hook3(ras_block_t cb, unsigned long long hwlvldest, ulong d1,
	ulong d2, ulong d3);
void ctfunc_hook4(ras_block_t cb, unsigned long long hwlvldest, ulong d1,
	ulong d2, ulong d3, ulong d4);
void ctfunc_hook5(ras_block_t cb, unsigned long long hwlvldest, ulong d1,
	ulong d2, ulong d3, ulong d4, ulong d5);

#if __IBMC__
#pragma isolated_call(ctfunc_hook0)
#pragma isolated_call(ctfunc_hook1)
#pragma isolated_call(ctfunc_hook2)
#pragma isolated_call(ctfunc_hook3)
#pragma isolated_call(ctfunc_hook4)
#pragma isolated_call(ctfunc_hook5)
#endif

/* trace a generic entry */
void rasp_trcgen(
	ras_block_t cb,
	ulong_t hkwd,
	ulong_t d1,
	uint len,
	char *buf);

/* CT_HOOKx - CT_GEN macros */
#ifdef __64BIT_KERNEL
#define CT_HOOK0(cb, level, mem_dest, hw)				\
    do {								\
        if (((mem_dest) & MT_RARE) &&					\
	    ((short)(level) <= rasrb_trace_memlevel((cb))))		\
           mtrchook0(HKWD64_EXPAND((hw),0) | HKWD64_TMASK, MTRC_RARE);	\
									\
        if (((mem_dest) & MT_COMMON)					\
	    && ((short)(level) <= rasrb_trace_memlevel((cb))))		\
           mtrchook0(HKWD64_EXPAND((hw),0) | HKWD64_TMASK, MTRC_COMMON);\
									\
        if (((mem_dest) & MT_PRIV) &&					\
	    ((short)(level) <= rasrb_trace_privlevel((cb))))		\
           ct_hook0((cb), HKWD64_EXPAND((hw),0)|HKWD64_TMASK);		\
									\
        if (((mem_dest) & MT_SYSTEM) &&					\
	    ((short)(level) <= rasrb_trace_syslevel((cb)))) {		\
	    __INFREQUENT;						\
            __TRCHOOK(HKWD64_EXPAND((hw),0) | HKWD64_TMASK);		\
	}								\
     } while (0)

#define CT_HOOK1(cb, level, mem_dest, hw, d1)				\
    do {								\
        if (((mem_dest) & MT_RARE) &&					\
	    ((short)(level) <= rasrb_trace_memlevel((cb))))		\
           mtrchook1(HKWD64_EXPAND((hw),8) | HKWD64_TMASK,		\
			(ulong_t) (d1), MTRC_RARE);			\
									\
        if (((mem_dest) & MT_COMMON) &&					\
	    ((short)(level) <= rasrb_trace_memlevel((cb))))		\
           mtrchook1(HKWD64_EXPAND((hw),8) | HKWD64_TMASK,		\
			(ulong_t) (d1), MTRC_COMMON);			\
									\
        if (((mem_dest) & MT_PRIV) &&					\
	    ((short)(level) <= rasrb_trace_privlevel((cb))))		\
           ct_hook1((cb), HKWD64_EXPAND((hw),8)|HKWD64_TMASK,		\
                       (ulong_t) (d1));					\
									\
        if (((mem_dest) & MT_SYSTEM) &&					\
	    ((short)(level) <= rasrb_trace_syslevel((cb)))) {		\
	    __INFREQUENT;						\
            __TRCHOOK(HKWD64_EXPAND((hw),8) | HKWD64_TMASK,		\
			(ulong_t) (d1));				\
	}								\
     } while (0)

#define CT_HOOK2(cb, level, mem_dest, hw, d1, d2)			\
  do {									\
        if (((mem_dest) & MT_RARE) &&					\
	    ((short)(level) <= rasrb_trace_memlevel((cb))))		\
           mtrchook2(HKWD64_EXPAND((hw),16) | HKWD64_TMASK,		\
		     (ulong_t) (d1), (ulong_t) (d2), MTRC_RARE);	\
									\
        if (((mem_dest) & MT_COMMON) &&					\
	    ((short)(level) <= rasrb_trace_memlevel((cb))))		\
           mtrchook2(HKWD64_EXPAND((hw),16) | HKWD64_TMASK,		\
		     (ulong_t) (d1), (ulong_t) (d2), MTRC_COMMON);	\
									\
        if (((mem_dest) & MT_PRIV) &&					\
	    ((short)(level) <= rasrb_trace_privlevel((cb))))		\
           ct_hook2((cb), HKWD64_EXPAND((hw),16)|HKWD64_TMASK,		\
		       (ulong_t) (d1), (ulong_t) (d2));			\
									\
        if (((mem_dest) & MT_SYSTEM) &&					\
	    ((short)(level) <= rasrb_trace_syslevel((cb)))) {		\
	    __INFREQUENT;						\
            __TRCHOOK(HKWD64_EXPAND((hw),16) | HKWD64_TMASK,		\
		      (ulong_t) (d1), (ulong_t) (d2));			\
	}								\
     } while (0)

#define CT_HOOK3(cb, level, mem_dest, hw, d1, d2, d3)			\
  do {									\
        if (((mem_dest) & MT_RARE) &&					\
	    ((short)(level) <= rasrb_trace_memlevel((cb))))		\
           mtrchook3(HKWD64_EXPAND((hw),24) | HKWD64_TMASK,		\
		     (ulong_t) (d1), (ulong_t) (d2), (ulong_t) (d3),	\
			MTRC_RARE);					\
									\
        if (((mem_dest) & MT_COMMON) &&					\
	    ((short)(level) <= rasrb_trace_memlevel((cb))))		\
           mtrchook3(HKWD64_EXPAND((hw),24) | HKWD64_TMASK,		\
		     (ulong_t) (d1), (ulong_t) (d2), (ulong_t) (d3),	\
			MTRC_COMMON);					\
									\
        if (((mem_dest) & MT_PRIV) &&					\
	    ((short)(level) <= rasrb_trace_privlevel((cb))))		\
           ct_hook3((cb), HKWD64_EXPAND((hw),24)|HKWD64_TMASK,		\
		       (ulong_t) (d1), (ulong_t) (d2), (ulong_t) (d3));	\
									\
        if (((mem_dest) & MT_SYSTEM) &&					\
	    ((short)(level) <= rasrb_trace_syslevel((cb)))) {		\
	    __INFREQUENT;						\
            __TRCHOOK(HKWD64_EXPAND((hw),24) | HKWD64_TMASK,		\
		     (ulong_t) (d1), (ulong_t) (d2), (ulong_t) (d3));	\
	}								\
     } while (0)

#define CT_HOOK4(cb, level, mem_dest, hw, d1, d2, d3, d4)		\
  do {									\
        if (((mem_dest) & MT_RARE) &&					\
	    ((short)(level) <= rasrb_trace_memlevel((cb))))		\
           mtrchook4(HKWD64_EXPAND((hw),32) | HKWD64_TMASK,		\
		     (ulong_t) (d1), (ulong_t) (d2), (ulong_t) (d3),	\
			(ulong_t) (d4), MTRC_RARE);			\
									\
        if (((mem_dest) & MT_COMMON) &&					\
	    ((short)(level) <= rasrb_trace_memlevel((cb))))		\
           mtrchook4(HKWD64_EXPAND((hw),32) | HKWD64_TMASK,		\
		     (ulong_t) (d1), (ulong_t) (d2), (ulong_t) (d3),	\
			(ulong_t) (d4), MTRC_COMMON);			\
									\
        if (((mem_dest) & MT_PRIV) &&					\
	    ((short)(level) <= rasrb_trace_privlevel((cb))))		\
           ct_hook4((cb), HKWD64_EXPAND((hw),32)|HKWD64_TMASK,		\
		       (ulong_t) (d1), (ulong_t) (d2), (ulong_t) (d3),	\
			(ulong_t) (d4));				\
									\
        if (((mem_dest) & MT_SYSTEM) &&					\
	    ((short)(level) <= rasrb_trace_syslevel((cb)))) {		\
	    __INFREQUENT;						\
            __TRCHOOK(HKWD64_EXPAND((hw),32) | HKWD64_TMASK,		\
		     (ulong_t) (d1), (ulong_t) (d2), (ulong_t) (d3),	\
			(ulong_t) (d4));				\
	}								\
     } while (0)

#define CT_HOOK5(cb, level, mem_dest, hw, d1, d2, d3, d4, d5)		\
  do {									\
        if (((mem_dest) & MT_RARE) &&					\
	    ((short)(level) <= rasrb_trace_memlevel((cb))))		\
           mtrchook5(HKWD64_EXPAND((hw),40) | HKWD64_TMASK,		\
		     (ulong_t) (d1), (ulong_t) (d2), (ulong_t) (d3),	\
			(ulong_t) (d4), (ulong_t) (d5), MTRC_RARE);	\
									\
        if (((mem_dest) & MT_COMMON) &&					\
	    ((short)(level) <= rasrb_trace_memlevel((cb))))		\
           mtrchook5(HKWD64_EXPAND((hw),40) | HKWD64_TMASK,		\
		     (ulong_t) (d1), (ulong_t) (d2), (ulong_t) (d3),	\
			(ulong_t) (d4), (ulong_t) (d5), MTRC_COMMON);	\
									\
        if (((mem_dest) & MT_PRIV) &&					\
	    ((short)(level) <= rasrb_trace_privlevel((cb))))		\
           ct_hook5((cb), HKWD64_EXPAND((hw),40)|HKWD64_TMASK,		\
		       (ulong_t) (d1), (ulong_t) (d2), (ulong_t) (d3),	\
			(ulong_t) (d4), (ulong_t) (d5));		\
									\
        if (((mem_dest) & MT_SYSTEM) &&					\
	    ((short)(level) <= rasrb_trace_syslevel((cb)))) {		\
	    __INFREQUENT;						\
            __TRCHOOK(HKWD64_EXPAND((hw),40) | HKWD64_TMASK,		\
		     (ulong_t) (d1), (ulong_t) (d2), (ulong_t) (d3),	\
			(ulong_t) (d4), (ulong_t) (d5));		\
	}								\
     } while (0)


#define CT_GEN(cb, level, hkwd, d1, len, buf)				\
  do {									\
        if ((short)(level) <= rasrb_trace_privlevel((cb)))		\
           rasp_trcgen((cb), HKWD64_EXPAND12((hkwd),(len))		\
		             |HKWD64_TMASK|HKWD64_GMASK|HKWD64_PMASK,	\
		       (ulong_t) (d1), (uint) (len), (void *) (buf));	\
        if ((short)(level) <= rasrb_trace_syslevel((cb)))		\
		trcgenkt(0, (hkwd), (ulong_t)(d1),			\
				(uint)(len), (void *)(buf));		\
     } while (0)

/* The following macros have no level checks. They are meant specifically
 * for performance sensitive areas.
 *
 */
#define CT_HOOK0_SYSTEM(hw)\
	__TRCHOOK(HKWD64_EXPAND((hw),0) | HKWD64_TMASK);
#define CT_HOOK1_SYSTEM(hw, d1)\
	__TRCHOOK(HKWD64_EXPAND((hw),8) | HKWD64_TMASK, (d1));
#define CT_HOOK2_SYSTEM(hw, d1, d2)\
	__TRCHOOK(HKWD64_EXPAND((hw),16) | HKWD64_TMASK, (d1), (d2));
#define CT_HOOK3_SYSTEM(hw, d1, d2, d3)\
	__TRCHOOK(HKWD64_EXPAND((hw),24) | HKWD64_TMASK, (d1), (d2), (d3));
#define CT_HOOK4_SYSTEM(hw, d1, d2, d3, d4)\
	__TRCHOOK(HKWD64_EXPAND((hw),32) | HKWD64_TMASK,\
			(d1), (d2), (d3), (d4));
#define CT_HOOK5_SYSTEM(hw, d1, d2, d3, d4, d5)\
	__TRCHOOK(HKWD64_EXPAND((hw),40) | HKWD64_TMASK,\
			(d1), (d2), (d3), (d4), (d5));

#else /* __64BIT_KERNEL */
#define CT_HOOK0(cb, level, mem_dest, hw)				\
  do {									\
        if (((mem_dest) & MT_RARE) &&					\
	    ((short)(level) <= rasrb_trace_memlevel((cb))))		\
           mtrchook0(_TRCTMASK((hw))|HKTY_ST, MTRC_RARE);		\
									\
        if (((mem_dest) & MT_COMMON) &&					\
	    ((short)(level) <= rasrb_trace_memlevel((cb))))		\
           mtrchook0(_TRCTMASK((hw))|HKTY_ST, MTRC_COMMON);		\
									\
        if (((mem_dest) & MT_PRIV) &&					\
	    ((short)(level) <= rasrb_trace_privlevel((cb))))		\
           ct_hook0((cb), _TRCTMASK((hw))|HKTY_ST);			\
									\
        if (((mem_dest) & MT_SYSTEM) &&					\
	    ((short)(level) <= rasrb_trace_syslevel((cb)))) {		\
	    __INFREQUENT;						\
            __TRCHOOK(_TRCTMASK((hw))|HKTY_ST);				\
	}								\
     } while (0)

#define CT_HOOK1(cb, level, mem_dest, hw, d1)				\
  do {									\
        if (((mem_dest) & MT_RARE) &&					\
	    ((short)(level) <= rasrb_trace_memlevel((cb))))		\
           mtrchook1(_TRCTMASK((hw))|HKTY_LT, (ulong_t) (d1),		\
			MTRC_RARE);					\
									\
        if (((mem_dest) & MT_COMMON) &&					\
	    ((short)(level) <= rasrb_trace_memlevel((cb))))		\
           mtrchook1(_TRCTMASK((hw))|HKTY_LT, (ulong_t) (d1),		\
		MTRC_COMMON);						\
									\
        if (((mem_dest) & MT_PRIV) &&					\
	    ((short)(level) <= rasrb_trace_privlevel((cb))))		\
           ct_hook1((cb), _TRCTMASK((hw))|HKTY_LT, (ulong_t) (d1));	\
									\
        if (((mem_dest) & MT_SYSTEM) &&					\
	    ((short)(level) <= rasrb_trace_syslevel((cb)))) {		\
	    __INFREQUENT;						\
            __TRCHOOK(_TRCTMASK((hw))|HKTY_LT, (ulong_t) (d1));		\
	}								\
     } while (0)

#define CT_HOOK5(cb, level, mem_dest, hw, d1, d2, d3, d4, d5)		\
  do {									\
        if (((mem_dest) & MT_RARE) &&					\
	    ((short)(level) <= rasrb_trace_memlevel((cb))))		\
           mtrchook5(_TRCTMASK((hw))|HKTY_GT,				\
		     (ulong_t) (d1), (ulong_t) (d2), (ulong_t) (d3),	\
			(ulong_t) (d4), (ulong_t) (d5), MTRC_RARE);	\
									\
        if (((mem_dest) & MT_COMMON) &&					\
	    ((short)(level) <= rasrb_trace_memlevel((cb))))		\
           mtrchook5(_TRCTMASK((hw))|HKTY_GT,				\
		     (ulong_t) (d1), (ulong_t) (d2), (ulong_t) (d3),	\
			(ulong_t) (d4), (ulong_t) (d5), MTRC_COMMON);	\
									\
        if (((mem_dest) & MT_PRIV) &&					\
	    ((short)(level) <= rasrb_trace_privlevel((cb))))		\
           ct_hook5((cb), _TRCTMASK((hw))|HKTY_GT,			\
		       (ulong_t) (d1), (ulong_t) (d2), (ulong_t) (d3),	\
			(ulong_t) (d4), (ulong_t) (d5));		\
									\
        if (((mem_dest) & MT_SYSTEM) &&					\
	    ((short)(level) <= rasrb_trace_syslevel((cb)))) {		\
	    __INFREQUENT;						\
            __TRCHOOK(_TRCTMASK((hw))|HKTY_GT, (ulong_t) (d1),		\
	    		(ulong_t) (d2),	(ulong_t) (d3), (ulong_t) (d4),	\
			(ulong_t) (d5));				\
	}								\
     } while (0)

#define CT_HOOK2(cb, level, mem_dest, hw, d1, d2)			\
          CT_HOOK5(cb, level, mem_dest, hw, d1, d2, 0, 0, 0)

#define CT_HOOK3(cb, level, mem_dest, hw, d1, d2, d3)			\
          CT_HOOK5(cb, level, mem_dest, hw, d1, d2, d3, 0, 0)

#define CT_HOOK4(cb, level, mem_dest, hw, d1, d2, d3, d4)		\
          CT_HOOK5(cb, level, mem_dest, hw, d1, d2, d3, d4, 0)


#define CT_GEN(cb, level, hkwd, d1, len, buf)				\
        do {								\
                if ((short)(level) <= rasrb_trace_privlevel((cb)))	\
	            rasp_trcgen((cb), (hkwd)|HKTY_VT|(len), 		\
		    	(ulong_t) (d1), (uint) (len), (void*) (buf));	\
                if ((short)(level) <= rasrb_trace_syslevel((cb)))	\
                    trcgenkt(0, (hkwd), (ulong_t)(d1),			\
			     (uint)(len), (void *)(buf));		\
	} while (0)

/* The following macros have no level checks. They are meant specifically
 * for performance sensitive areas.
 *
 */
#define CT_HOOK0_SYSTEM(hw)\
	__TRCHOOK(_TRCTMASK((hw))|HKTY_ST);
#define CT_HOOK1_SYSTEM(hw, d1)\
	__TRCHOOK(_TRCTMASK((hw))|HKTY_LT, (d1));
#define CT_HOOK2_SYSTEM(hw, d1, d2)\
	__TRCHOOK(_TRCTMASK((hw))|HKTY_GT, (d1), (d2));
#define CT_HOOK3_SYSTEM(hw, d1, d2, d3)\
	__TRCHOOK(_TRCTMASK((hw))|HKTY_GT, (d1), (d2), (d3));
#define CT_HOOK4_SYSTEM(hw, d1, d2, d3, d4)\
	__TRCHOOK(_TRCTMASK((hw))|HKTY_GT, (d1), (d2), (d3), (d4));
#define CT_HOOK5_SYSTEM(hw, d1, d2, d3, d4, d5)\
	__TRCHOOK(_TRCTMASK((hw))|HKTY_GT, (d1), (d2), (d3), (d4), (d5));
#endif /* __64BIT_KERNEL */



#define CT_TRCON(cb, level) ((short)(level) <= rasrb_trace_level_summary((cb)))

#define CTF_MD_SHIFT	32
#define CTF_LVL_SHIFT	40

#define CTF_COMBINE(lvl, md, hw)\
	(((unsigned long long)(lvl) << CTF_LVL_SHIFT) |	\
	 ((unsigned long long)(md)  << CTF_MD_SHIFT)  |	\
	  (hw))

#define CTFUNC_HOOK0(cb, lvl, mem_dest, hw)				\
	ctfunc_hook0(cb, CTF_COMBINE((lvl), (mem_dest), (hw)));
#define CTFUNC_HOOK1(cb, lvl, mem_dest, hw, d1)				\
	ctfunc_hook1(cb, CTF_COMBINE((lvl), (mem_dest), (hw)),		\
		(d1));
#define CTFUNC_HOOK2(cb, lvl, mem_dest, hw, d1, d2)			\
	ctfunc_hook2(cb, CTF_COMBINE((lvl), (mem_dest), (hw)),		\
		(d1), (d2));
#define CTFUNC_HOOK3(cb, lvl, mem_dest, hw, d1, d2, d3)			\
	ctfunc_hook3(cb, CTF_COMBINE((lvl), (mem_dest), (hw)),		\
		(d1), (d2), (d3));
#define CTFUNC_HOOK4(cb, lvl, mem_dest, hw, d1, d2, d3, d4)		\
	ctfunc_hook4(cb, CTF_COMBINE((lvl), (mem_dest), (hw)),		\
		(d1), (d2), (d3), (d4));
#define CTFUNC_HOOK5(cb, lvl, mem_dest, hw, d1, d2, d3, d4, d5)		\
	ctfunc_hook5(cb, CTF_COMBINE((lvl), (mem_dest), (hw)),		\
		(d1), (d2), (d3), (d4), (d5));
#endif /* _KERNEL */

#endif /* _H_RAS_TrACE */
