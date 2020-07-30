/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/kernel/sys/trchdr.h 1.47.1.2                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1994          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)98    1.47.1.2  src/bos/kernel/sys/trchdr.h, systrace, bos53Q, q2007_50B0 11/30/07 14:56:53 */

/*
 * COMPONENT_NAME:            include/sys/trchdr.h
 *
 * FUNCTIONS: header file for system trace control block and macros
 *
 * ORIGINS: 27 83
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1994
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 *  LEVEL 1, 5 Years Bull Confidential Information
 */

/*
 * FUNCTION: definition of trchdr trace buffer header.
 *           Also contains state bit definitions and macros.
 *           To be used only inside the kernel.
 */  

#ifndef _H_TRCHDR
#define _H_TRCHDR

#include <sys/lock_def.h>
#include <sys/systemcfg.h>
#include <limits.h>

/* Some definitions to prevent forward references. */
struct trcbufs;
struct trc_log;
struct trc_log_64;
struct file;

#ifndef TRC_NCHANNELS
#define TRC_NCHANNELS 8
#endif

/* Maximum CPUs supported, must be a multiple of 32 (an int's worth) */
#define __TRC_MAXCPUS 1024		/* Must be a multiple of 32 */
#define __TRC_CPUBYTES (__TRC_MAXCPUS/8)

#define __TRC_NHOOKIDS	4096

/* Number of chars required to hold the hook ID bit map array */
#define __TRC_EVENTMAP_BYTES	(__TRC_NHOOKIDS/8)

/* See if SPLPAR is active. */
#ifdef TRC_SPLPAR_TEST
#define __trc_issplpar() (1)
#else
#define __trc_issplpar() __SPLPAR()
#endif

/*
 * Definitions for Trconflag bytes.
 * Trconflag is a one byte per channel array specifying trace mode
 * and control information.  It is in low kernel memory.
 */
extern char Trconflag[TRC_NCHANNELS];
/* thread-based tracing flags. */
#define TRC_OFL_INT 0x80		/* Interrupt tracing. */
#define TRC_OFL_ALLTHRDS 0x40		/* Tracing all threads. */
#define TRC_OFL_ALL (TRC_OFL_INT|TRC_OFL_ALLTHRDS)
#define TRC_OFL_SOMETHRDS 0x20		/* Tracing some threads. */
/* Trace modes, off, hook-based or all hooks. */
#define TRC_OFL_OFF 0			/* Tracing is off, must be 0 */
#define TRC_OFL_MODEMASK 0x7		/* Mask for mode bits. */
#define TRC_OFL_MODENOCOND 0x1		/* Trace regardless of the hook. */
#define TRC_OFL_MODECOND 0x2		/* Trace depending upon the hook. */

/*
 * Number of bytes that 'inptr' can grow beyond 'end'.
 * The generic trace doesn't go past the end.
 * We allow space for at least 3 fullsized, 64-bit, nongeneric hooks.
 * a fullsized hook takes up to 9, 64-bit, words, 72 bytes.
 * So we need to allow at least 216 bytes of overflow.
 * The maximum buffer size is 268435184 bytes, so we'll use
 * 256*1024*1024-x = 268435184, x = 272 bytes.
 * We use the same overflow size regardless of the kernel to avoid
 * confusion since the overflow size determines the maximum buffer size.
 */
#define TRC_OVB 272
#define GENBUFSIZE 4096			/* max size of trcgen() buffer */
/*
 * GENBUFSIZE64_32 is used to hold a 64-bit trace entry with a
 * 32-bit trace.  Since it must hold a 64-bit generic entry, it must
 * be longer than just GENBUFSIZE.
 * It must be able to hold the 8-byte data word plus 4 bytes of the
 * hookword.  The top 4 bytes of the hookword are in the data word.
 */
#define GENBUFSIZE64_32 (GENBUFSIZE+4+8)

#if defined(_KERNSYS) || defined (_TRACE_KEXT)
/*
 * trace channel buffer pointers.
 * This is only valid for use by the kernel and extensions.
 * Note that for now, the traced data is 32 bits regardless
 * of which kernel is active.
 */
struct trc_q {
#ifndef __64BIT__
	vmid_t q_sid;				/* Seg id, only needed when destroying segment */
	vmhandle_t q_sreg;			/* segment used */
#endif
	ulong_t *q_start;				/* base of the buffer */
	ulong_t *q_end;					/* end of the buffer - TRC_OVB */
	ulong_t *q_inptr;				/* trchk() will write here */
	size_t  q_size;				/* allocated size in bytes of this q */
};

struct trchdr {
	long trc_lockword;		/* serialize */
	tid_t trc_tid;			/* thread id of trclogio thread */
	struct trcbufs *trc_bufs;	/* channel's buffering structure ptr. */
	uint trc_nbufs;			/* number of buffer sets. */
	uint trc_bufs_finished;		/* # buffer sets finished. */
	int trc_state;			/* state bits defined below (ST_) */
	int trc_ioerr;			/* error if any. */
	short trc_mode;			/* modes defined below (MD_) */
	short trc_channel;		/* channel, used by dump */
	ushort trc_trconcount;		/* number of trcon calls */
	ushort trc_fileflags;		/* flags defined below (FF_) */
	int trc_trconflag;		/* Value for Trconflag */
	uint trc_tbufsize;		/* trace data buffer size in bytes */
	int trc_alloc;			/* buf allocation, see TAL_, trcctl.h */
#ifdef __64BIT__
	char *trc_regfunc;		/* addr of register collector, 0 if none. */
	int trc_nregs;			/* # regs being collectedd */
#endif
	unsigned char trc_events[__TRC_EVENTMAP_BYTES]; /* cond. event bit map */
	unsigned char trc_cpus_in[__TRC_CPUBYTES]; /* CPUs specified */
	unsigned char trc_cpus_out[__TRC_CPUBYTES]; /* CPUs that were traced */
	char trc_fn[PATH_MAX+1];	/* log file name */
};

/*
 * We need a save area per cpu.
 * Each save area consists of a C stack plus a save area for the frontend.
 */
#define TRC_STACKWORDS 1024		/* 4 or 8 k */
#define TRC_SAVEWORDS 16		/* up to 16 regs. */
/* n is the number of cpus. */
#define TRC_SAVESIZE(n) (n*(TRC_STACKWORDS+TRC_SAVEWORDS)*sizeof(long))
/*
 * buffering vector.
 * There may be one or more for a channel.
 * trc_bufs above points to an array of these.
 *
 * If changing this, also see trchdr.m4.
 */
struct trcbufs {
	struct trchdr *tbuf_hdrp;	/* pointer to the header */
	tid_t tbuf_tid;			/* i/o handler's tid */
	tid_t tbuf_sleepword;		/* wakeup to do i/o */
	long tbuf_hkmask;		/* mask to apply to hookword. */
	int tbuf_buflock;		/* spin lock for serialization */
	ushort tbuf_fsm;	/* states defined below (FSM_) */
	ushort tbuf_ctl;		/* control (CTL_) */
	uint tbuf_wrapcount;		/* trace buffer wraparound count */
	uint tbuf_ovfcount;		/* overflow due to wrapping */
	struct trc_q tbuf_currq;		/* used by hook routines */
	struct trc_q    tbuf_Aq;
	struct trc_q    tbuf_Bq;
	ulong_t *tbuf_lastinptr;	/* Used when dumping */
#ifdef __64BIT__
	struct trc_log_64 *tbuf_lp;	/* trace logfile structure */
#else
	struct trc_log *tbuf_lp;		/* trace logfile structure */
#endif
	int tbuf_cpuid;			/* cpuid for this buffer set */
};

#ifndef __64BIT__
#define tbuf_sreg    tbuf_currq.q_sreg
#define tbuf_sid     tbuf_currq.q_sid
#endif
#define tbuf_start   tbuf_currq.q_start
#define tbuf_end     tbuf_currq.q_end
#define tbuf_inptr   tbuf_currq.q_inptr
#define tbuf_size    tbuf_currq.q_size

#ifndef __64BIT__
#define tbuf_sregA   tbuf_Aq.q_sreg
#define tbuf_sidA    tbuf_Aq.q_sid
#endif
#define tbuf_startA  tbuf_Aq.q_start
#define tbuf_endA    tbuf_Aq.q_end
#define tbuf_inptrA  tbuf_Aq.q_inptr
#define tbuf_sizeA   tbuf_Aq.q_size

#ifndef __64BIT__
#define tbuf_sregB   tbuf_Bq.q_sreg
#define tbuf_sidB    tbuf_Bq.q_sid
#endif
#define tbuf_startB  tbuf_Bq.q_start
#define tbuf_endB    tbuf_Bq.q_end
#define tbuf_inptrB  tbuf_Bq.q_inptr
#define tbuf_sizeB   tbuf_Bq.q_size

/* et_wait/et_post wait bits used by i/o proc and threads. */
#define EVENT_TRACE 0x80000000		/* i/o thread done. */
#define EVENT_TRCSTOP 0x40000000	/* TRCSTOP, posted to i/o process */
#define EVENT_TRCUNLOCK 0x80000000	/* ok to release channel lock. */
#define EVENT_TRCPROC 0x40000000	/* i/o process done. */
#define EVENT_ALLOC 0x20000000		/* tell i/o proc to create a thread */
					/* also posted (returned) if thread created */
#define EVENT_ALLOCERR 0x10000000	/* trclogio thread creation error. */

/*
 * Parameter structure passed to the trclogio process.
 */
struct trc_parent {
	struct trchdr *tp;
	tid_t tid;			/* The parent's tid. */
};

/*
 * State machine (fsm) states
 * State names have the format FSM_<write-state>_<read-state>.
 * The write-state refers to the tracing state.
 * The read state tells us whether the buffer can be written out,
 * i.e. read by trclogio().
 * Also, the spill states must have their high-order bit set.
 * This is how the collectors know we're spilling, the trconflags aren't used
 * for this any more.
 */
#define FSM_A_B               1		/* tracing to A, reading B */
#define FSM_A_BLOCK           2		/* tracing to A, don't read B */
#define FSM_B_A               3		/* tracing to B, reading A */
#define FSM_B_BLOCK           4		/* tracing to B, don't read A */
#define FSM_SPILL_MASK 	      0x8000	/* Set if we're spilling. */
#define FSM_SPILL_A           0x8001	/* Spilling, waiting for A */
#define FSM_SPILL_A_OFF       0x8002	/* we're done when A written */
#define FSM_SPILL_A_OFF2      0x8003	/* We'll be done when B written */
#define FSM_SPILL_B           0x8004	/* Spilling, waiting for B */
#define FSM_SPILL_B_OFF       0x8005	/* We'll be done when A written */
#define FSM_SPILL_B_OFF2      0x8006	/* we're done when B written */
#define FSM_SPILL_BLOCK       0x8007	/* no tracing, nothing to read */
#define FSM_SPILL_EOF         0x8008	/* We're done */

/*
 * Values for tbuf_ctl.
 * These are used to control the serialization in the collectors.
 */
#define CTL_MPSER 0x01		/* MP serialization */
#define CTL_UPSER 0x02		/* UP serialization */
#define CTL_CRIT 0x4		/* critical section needed */

extern struct trchdr trchdr[];

/* trc_state definitions. */
#define ST_ISOPEN      0x01		/* exclusivity */
#define ST_TRCON       0x02		/* tracing is active (buffer can SPILL) */
#define ST_WRAP        0x04		/* stop-on-wrap-mode, wrap */
#define ST_TRCSTOP     0x10		/* TRCSTOP ioctl, cause EOF */
#define ST_COND        0x20		/* conditional mode, for trcgen */
#define ST_BUS         0x40		/* bus mode, for trcgen */
#define ST_TSYNC       0x80		/* wait for close of /dev/systrace */
#define ST_IACTIVE	0x100		/* interactive trace is being run */
#define ST_SEPSEG	0x200		/* separate segment trace, 32-bit */

/*
 * trace mode codes. Internal to driver.
 */
#define MD_OFF            0		/* could become MD_DEBUG */
#define MD_CIRCULAR       1
#define MD_CIRCULAR_COND  2
#define MD_ALTERNATE      3
#define MD_ALTERNATE_COND 4
#define MD_SINGLE         5
#define MD_SINGLE_COND    6
#define MD_BUS            7
#define MD_BUS_COND       8

/*
 * File flags bits.
 */
#define FF_STOPONWRAP 0x01		/* Stop when file wraps, trace -s */
#define FF_SEPCPU 0x02			/* separate cpu, trace -C */

#define HKTOEVENT(hookword) (((unsigned long)(hookword) >> 20) & 0xfff)

#define ISEVENT(tp,n) \
((tp)->trc_events[HKTOEVENT(n)/8] & (1 << HKTOEVENT(n)%8))

/* Use for dynamic buffer allocation. */
struct trc_dba {
	tid_t dba_tid;			/* DR thread to post to. */
	struct trcbufs *dba_bp;		/* trcbufs ptr for the new thread. */
};

#ifdef _IBMRT
#define INT_OFF()  j_disable()
#define INT_ON()   j_enable(0)
#define INT_ONX(s) j_enable(s)
#else
#define INT_OFF()  i_disable(INTMAX)
#define INT_ON()   i_enable(INTBASE)
#define INT_ONX(s) i_enable(s)
#endif

extern char jsnapflg;

#ifdef DEBUG
#define trc_debug  (jsnapflg == 0) ? 0 : jsnap
#define trc_debug2 (jsnapflg <  2) ? 0 : jsnap
#else
#define trc_debug
#define trc_debug2
#endif

#define TIMESTAMP trc_timestamp()
#endif /* _KERNSYS || _TRACE_KEXT */

struct trc_log_entry {
	int le_offset;
	unsigned le_size;
};
/* for 64-bit access by 32-bit apps. */
struct trc_log_entry_64 {
	unsigned long long le_offset;
	unsigned long long le_size;
};

struct trc_log_hdr {
	int lh_magic;				/* magic number */
	int lh_nentries;			/* number of log_entries */
	int lh_currentry;			/* current entry */
	int lh_mode;				/* wrap mode */
	int lh_wrapcount;			/* wrap mode */
	int lh_fd;					/* logfile file descriptor */
#ifndef __64BIT__
	struct file *lh_fp;			/* logfile file structure */
#else
	unsigned lh_fp;			/* Just a 32-bit place holder here. */
#endif
	struct trc_log_entry lh_ic;	/* initial conditions from trace command */
};
/* For 32-bit app accessing 64-bit trace */
struct trc_log_hdr_64 {
	int lh_magic;				/* magic number */
	int lh_nentries;			/* number of log_entries */
	int lh_currentry;			/* current entry */
	int lh_mode;				/* wrap mode */
	int lh_wrapcount;			/* wrap mode */
	int lh_fd;					/* logfile file descriptor */
	long long lh_fp;			/* logfile file structure */
	struct trc_log_entry_64 lh_ic;	/* initial conditions fro trace command */
};

struct trc_log {
	struct trc_log_hdr   l_h;
	struct trc_log_entry l_data[1];	/* trace buffers */
};
/* For 32-bit apps using 64-bit trace. */
struct trc_log_64 {
	struct trc_log_hdr_64 l_h;
	struct trc_log_entry_64 l_data[1];	/* trace buffers */
};
#define l_magic     l_h.lh_magic
#define l_nentries  l_h.lh_nentries
#define l_currentry l_h.lh_currentry
#define l_mode      l_h.lh_mode
#define l_wrapcount l_h.lh_wrapcount
#define l_fd        l_h.lh_fd
#define l_fp        l_h.lh_fp
#define l_ic        l_h.lh_ic

#define MDL_NOWRAP     0x01
#define MDL_STOPONWRAP 0x02
#define MDL_MULTICPU 0x04
#define MDL_CPUFILE 0x08


#define TRC_LMAGIC 0xEFDF1111
/* 4.1 trace magic */
#define TRC_NEW_LMAGIC 0xEFDF1112
/* 64-bit magics */
#define TRC_64_LMAGIC 0xEFDF1113
#define TRC_64_LSTREAM 0xEFDF1114
#define VALID_TRCMAGIC(m) (((m) == TRC_LMAGIC) || \
	((m) == TRC_NEW_LMAGIC) || ((m) == TRC_64_LMAGIC) || \
	((m) == TRC_64_LSTREAM))

#ifdef __64BIT__
#define TRC_LHSIZE sizeof(struct trc_log_hdr_64)
#define TRC_LESIZE sizeof(struct trc_log_entry_64)
#else /* !__64BIT__ */
#define TRC_LHSIZE sizeof(struct trc_log_hdr)
#define TRC_LESIZE sizeof(struct trc_log_entry)
#endif /* __64BIT__ */
#define TRC_LSIZE(hp) \
	( TRC_LHSIZE + (hp)->lh_nentries * TRC_LESIZE )

/*
 * Trace dump table information.
 * This is 32/64 bit invarient.
 * It also provides the time conversion values.
 */
struct trctyp {
	uint magic;			/* unique identifier */
	u_longlong_t typ;		/* type flags */
	u_longlong_t xint;		/* Xint for time conversion */
	u_longlong_t xfrac;		/* Xfrac for time conversion */
	u_longlong_t rtc_type;		/* clock type */
};
/* typ values */
#define TRC_TYPMAGIC 0x54595001		/* TYP1 */
#define TRC_DMP_32 32
#define TRC_DMP_64 64

#ifdef __64BIT_KERNEL
#define KDB_TRCBUF_MINSIZE 8192*2
#else
#define KDB_TRCBUF_MINSIZE 8192
#endif

#define TRCSYS 1
#define TRCKDB 2

#ifdef _KERNEL
/* 
 * Critical section flags
 * This is a two-dimentional array, cpu and channel.
 */
extern char trc_critflags[][TRC_NCHANNELS];
#define TRC_CF_SAVING 0x1		/* saving data */

/* trchk0 flags */
#define	TRCHK0_PREEMPT 0x1		/* preemption data to be saved */
#define TRCHK0_HOOK 0x2			/* trace this hook */
#endif /* _KERNEL */

/*
 * Register id mapping for registers specified with "trace -r reglist".
 * ATTENTION! trc_registers must be kept in sync with the register defines
 * found in libtrace.h.
 */
#define TRCREG_NAMELEN 16
#define TRC_MAXREGS 13
#define TRC_REGISTERS_MAX 8		/* MAX register specs allowed */
/* Flags values. */
#define TRCRGF_PRESENT 1		/* Register is present */
#define TRCRGF_IVAL 2			/* Initial value of MMCRs required */

#define TRC_FIRST_MMCR 1		/* Index of first MMCR */
#define TRC_NUM_MMCR 3			/* # of MMCRs */
#ifndef _KERNEL
typedef struct {
	int n;				/* # specified regs */
	uint64_t *datap;		/* start of reg area (libtrace.a) */
	struct {
		char name[TRCREG_NAMELEN];
		int regid;		/* register's id */
		int flags;		/* see definitions above */
		int pos;		/* position in trace data */
	} r[TRC_MAXREGS];
} trc_registers_t;
/* Initialization */
#define TRC_REGISTERS_INIT {\
	0, 0,\
	{\
	{"PURR", TRC_PURR_ID, 0,-1},\
	{"MMCR0", TRC_MMCR0_ID, TRCRGF_IVAL,-1},\
	{"MMCR1", TRC_MMCR1_ID, TRCRGF_IVAL,-1},\
	{"MMCRA", TRC_MMCRA_ID, TRCRGF_IVAL,-1},\
	{"PMC1", TRC_PMC1_ID, TRCRGF_IVAL,-1},\
	{"PMC2", TRC_PMC2_ID, TRCRGF_IVAL,-1},\
	{"PMC3", TRC_PMC3_ID, TRCRGF_IVAL,-1},\
	{"PMC4", TRC_PMC4_ID, TRCRGF_IVAL,-1},\
	{"PMC5", TRC_PMC5_ID, TRCRGF_IVAL,-1},\
	{"PMC6", TRC_PMC6_ID, TRCRGF_IVAL,-1},\
	{"PMC7", TRC_PMC7_ID, TRCRGF_IVAL,-1},\
	{"PMC8", TRC_PMC8_ID, TRCRGF_IVAL,-1},\
	{"SPURR", TRC_SPURR_ID, TRCRGF_IVAL,-1}}}
#endif /* !_KERNEL */

/*
 * Processor id values.
 * These values are passed with HKWD_TRACE_UTIL, subhook HKUT_REGS.
 */
#define TRC_PROC_604 0
#define TRC_PROC_604E 1
#define TRC_PROC_RS64_II 2
#define TRC_PROC_POWER3 3
#define TRC_PROC_RS64_III 4
#define TRC_PROC_POWER3_II 5
#define TRC_PROC_POWER4 6
#define TRC_PROC_MPC7450 7
#define TRC_PROC_POWER4_II 8
#define TRC_PROC_POWER5 9
#define TRC_PROC_970 10
#define TRC_PROC_970MP 11
#define TRC_PROC_POWER6 12
#define TRC_PROC_MAX (TRC_PROC_POWER6+1)

#ifdef __64BIT_KERNEL
/*
 * Function used by the trace data collectors to get the regs.
 * It returns the updated buffer ptr.
 */
char *trc_getregs(char *buf, char *funcaddr);
#pragma mc_func trc_getregs { \
	"7c8903a6"			/* mtctr r4, funcaddr */ \
	"4e800421"  			/* bctrl call it */ \
}
#pragma reg_killed_by trc_getregs gr3-gr4,lr,ctr
#endif

#ifdef _KERNEL
extern int trc_setup_preempt_buffers(int cmd, int flags);
extern int trc_alloc_preempt(int cpu, int flags);
/* trc_setup_preempt_buffers parameters */
#define TSPB_INIT 1			/* cmd, init */
#define TSPB_TERM 0			/* cmd, terminate */
#define TSPB_ALLOC 0x1			/* flag, allocate */
#define TSPB_REG 0x2			/* flag, register */
#define TSPB_KDB 0x4			/* flag, called from kdb */
#endif

#ifndef __64BIT_KERNEL
/*
 * Trace system timer period.
 * This is the number of nanoseconds, times .85, needed to wrap the timer,
 */
#define TRC_GTIME_PERIOD(xint, xfrac) (u_longlong_t)\
	(17*(((xint)*0x100000000LL/(xfrac))/20))
#endif

#endif /* _H_TRCHDR */
