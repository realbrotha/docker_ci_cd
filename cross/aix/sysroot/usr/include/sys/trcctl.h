/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53S src/bos/kernel/sys/trcctl.h 1.40.1.1                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1988,1989              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)87    1.40.1.1  src/bos/kernel/sys/trcctl.h, systrace, bos53S, s2008_37D7 9/10/08 13:48:10 */
/*
 * @BULL_COPYRIGHT@
 */

/*
 * COMPONENT_NAME:            include/sys/trcctl.h
 *
 * FUNCTIONS:  header file for ioctl's to /dev/systrace and /dev/systrctl
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_TRCCTL
#define _H_TRCCTL
#include <sys/types.h>
#include <sys/systemcfg.h>
#include <sys/trchdr.h>
#include <limits.h>

#define	TRCIOC ('C'<<8)

#define CFGMTRL (TRCIOC|0x1)
#define CFGMTRA (TRCIOC|0x2)
#define CFGMTRF (TRCIOC|0x3)
#define CFGBTR  (TRCIOC|0x4)

#define TRCSYNC (TRCIOC|0x7)
#define TRCON   (TRCIOC|0x8)
#define TRCOFF  (TRCIOC|0x9)
#define TRCSTOP (TRCIOC|0xA)
#define TRCSTAT (TRCIOC|0xB)
#define TRC_LOADER    (TRCIOC|0xC)	/* Only used for _IA64. */
#define TRCIOC_LOGCFG (TRCIOC|0xE)
#define TRCIOC_LOGIO  (TRCIOC|0xF)
#define TRCIOC_THTSTART (TRCIOC|0x10)
#define TRCIOC_CFGPROC (TRCIOC|0x11)
#define TRCIACTIVE	(TRCIOC|0x20)
#define TRCDHK  (TRCIOC|0x30)           /* Force demon pid into trace buffer */

#define MDEV_SYSTRACE  0
#define MDEV_SYSTRCTL  1
#define MDEV_SYSMEM    2
#define MDEV_SYSUTIL   3
#define MDEV_SYSNULL   4
#define MDEV_SYSTRACE1 5
#define MDEV_SYSTRACE2 6
#define MDEV_SYSTRACE3 7
#define MDEV_SYSTRCTL1 8
#define MDEV_SYSTRCTL2 9
#define MDEV_SYSTRCTL3 10
#define MDEV_SYSTRACE4 11
#define MDEV_SYSTRACE5 12
#define MDEV_SYSTRACE6 13
#define MDEV_SYSTRACE7 14
#define MDEV_SYSTRCTL4 15
#define MDEV_SYSTRCTL5 16
#define MDEV_SYSTRCTL6 17
#define MDEV_SYSTRCTL7 18

struct tr_stat {
	int trst_mode;
	int trst_cmd;
	int trst_ovfcount;
	int trst_iactive;
	int trst_alloc;			/* buffer allocation scheme */
        unsigned char trst_events[__TRC_EVENTMAP_BYTES];
};

/* # cpus on this system. */
#define __TRC_SYSCPUS _system_configuration.ncpus
/* Minimum allowed buffer size. */
#define __TRCBUF_MINSIZE 8192
/* Maximum allowed buffer size. */
#define __TRCBUF_MAXSIZE 268435184

/* Parameter passed to the driver at config time. */
struct tr_struct {
	uint tr_tbufsize;		/* trace data buffer size in bytes */
	int tr_alloc;				/* buffer allocation type, trchdr.h */
	int tr_nbufs;				/* no. buffer sets */
	int tr_cpus_traced;		/* # cpus being traced. */
	unsigned char tr_events[__TRC_EVENTMAP_BYTES];	/* events to trace */
	unsigned char tr_cpus[__TRC_CPUBYTES];	/* CPUs to trace */
	uint tr_nrmax;			/* Non-Root max Buffer size */
	char tr_fn[PATH_MAX+1];		/* log file name */
};

/* tr_alloc and trc_alloc bit values, see also trchdr.h. */
#define TAL_ALLOC_HEAP 0x1		/* on for trace -b */
#define TAL_ALLOC_SEG  0x2		/* on if trace -B */
#define TAL_ALLOC_MULTICPU 0x4		/* on for trace -C */
#define TAL_INSERT_CPUID 0x8		/* on for trace -p */
#define TAL_ALLOC_ALLCPU 0x10		/* -Call, implies TAL_ALLOC_MULTICPU */

/* tr_cpus field handling macros.
 * This bit map contains bits for each cpu traced.
 * The bit numbering is left to right.
 */
#ifndef __ia64
#define CPUS_ID(n) ((n)/8)
#define CPUS_BIT(n) (0x80 >> ((n)%8))
#define ISCPU(map, n) (map[CPUS_ID(n)] & CPUS_BIT(n))
#define SETCPU(map, n) map[CPUS_ID(n)] |= CPUS_BIT(n)
#define RESETCPU(map, n) map[CPUS_ID(n)] &= ~CPUS_BIT(n)
#else
/***************
_iA64_
Creating a problem with the trcwakechan bit selection.
See trcdd.h (here word based setting is being done).
***************/
#define CPUS_ID(n) ((n)/32)
#define CPUS_BIT(n) (0x80000000 >> ((n)%32))
#define ISCPU(map, n) (((unsigned int *)map)[CPUS_ID(n)] & CPUS_BIT(n))
#define SETCPU(map, n) ((unsigned int *)map)[CPUS_ID(n)] |= CPUS_BIT(n)
#define RESETCPU(map, n) ((unsigned int *)map)[CPUS_ID(n)] &= ~CPUS_BIT(n)
#endif

/*
 * TRCSYNC parameter.
 * This consists of two bit maps, one identifying the original cpus to be
 * traced, and the other containing the cpus actually traced
 */
struct trcsync_parm {
	unsigned char tsy_cpus_in[__TRC_CPUBYTES]; /* CPUs specified */
	unsigned char tsy_cpus_out[__TRC_CPUBYTES]; /* CPUs that were traced */
	char tsy_fn[PATH_MAX+1];	/* log file name */
};

/*
 * Used to pass thread-based trace config information to the TRCIOC_THTSTART
 * ioctl.  thts_list contains pids first, then tids.
 */
struct thtstart {
	int thts_thtf;			/* flags */
	int thts_npid;			/* number of pids */
	int thts_ntid;			/* number of tids */
	u_longlong_t thts_list[1];	/* list of pids and tids. */
};
#define THTS_SIZE(s) (sizeof(*(s))+((s)->thts_npid+(s)->thts_ntid-1)*sizeof((s)->thts_list[0]))
/* thts_thtf flag values.  Also used for trc_thtf in the trchdr. */
#define TRC_THTF_PCPROP 0x1		/* Propagate across process creation. */
#define TRC_THTF_TCPROP 0x2		/* Propagate across thread creation. */
#define TRC_THTF_NONTHRD 0x4		/* Include non-thread events. */
#define TRC_THTF_THRD 0x8		/* Trace selected threads. */
#define TRC_THTF_THRDALL 0x10		/* Trace all threads. */
/* Mask for the propagation flags. */
#define TRC_THTF_PROPMASK (TRC_THTF_PCPROP|TRC_THTF_TCPROP)

/* Parameter used by the TRCIOC_CFGPROC ioctl. */
typedef struct {
	int procid;			/* Processor's type */
	int nv;				/* # of initial values. */
	struct {
		int regid;		/* register id of this initial value */
		uint64_t ival;		/* register's initial value */
	} iv[3];			/* one per potential MMCR */
	int n;				/* # of input registers */
	struct {
		int regid;		/* Register's index */
		int flags;		/* TRCRGF_PRESENT is set if register is valid. */
	} r[TRC_MAXREGS];
} cfgproc_t;

/* Only used for _IA64. */
struct trc_lv {						/* loader values for TRC_LOADER */
	unsigned long long lv_start;
	unsigned long long lv_size;
	char  lv_name[16];
};

/* add bull - Only used for _IA64. */
struct wtrc_lv {
        unsigned long long lv_start;
        unsigned long long lv_size;
        char  lv_name[16];
        char  lv_fullname[125];
/* _iA64_ structure size problems at user-32 and kernel-64 levels
        unsigned int  lv_flags; 
*/
        unsigned long long  lv_flags;
};
/* end bull */

#define TRC_NLV 100					/* max number of trc_lvs returned */

#define TRC_TBUFUMAX (1024 * 1024)	/* max size of trace buffer for user */

#endif /* _H_TRCCTL */

