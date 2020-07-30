/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/usr/ccs/lib/libtrace/libtrace.h 1.19.1.1                */
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
#ifndef	_H_libtrace
#define	_H_libtrace
/* @(#)09        1.19.1.1  src/bos/usr/ccs/lib/libtrace/libtrace.h, cmdtrace, bos53L, l2006_43C2 10/20/06 11:00:21 */
/* Maximum number of trace hook	ids. */
#define	TRC_NHOOKIDS 4096
/* First non-reserved trace hook. */
#define	TRC_FIRSTUSER 0x010
/* Max value for a trace hook id. */
#define	TRC_MAXHOOK 0xfff

#include <sys/types.h>
#include <sys/utsname.h>

#ifdef __cplusplus
extern "C" {
#endif

/*****************************
 * Trace retrieval API definitions.
 *****************************/

/* Trace log file handle returned by trc_open. */
typedef	void * trc_loghandle_t;
typedef	void *trc_logpos_t;		/* log object position object. */

/* Log file types passed to trc_open. */
#define	TRC_LOGREAD 0x1			/* Open	for reading. */
#define	TRC_LOGWRITE 0x2		/* Open	for writing. (unsupported) */
#define	TRC_LOGRAW 0x100		/* Process in raw mode.	*/
#define	TRC_LOGPROC 0x200		/* processed mode. */
#define	TRC_LOGVERBATIM	0x10000		/* return the file data	verbatim */
#define	TRC_LIBDEBUG 0x20000		/* Output debug	info to	list file. */
#define	TRC_LOGLIVE 0x40000		/* Return live, not copied, data. */
#define TRC_RETAIN_HANDLE 0x80000	/* Don't free the handle after an open failure. */
#define TRC_NOTEMPLATES 0x100000	/* Ignore any template file. */
#define TRC_MULTI_MERGE	0x200000	/* Merging multiple files 	*/
#define TRC_REMOVE_DUPS	0x400000	/* Duplicate event detection	*/

typedef	unsigned short trc_hookid_t;
typedef	unsigned short trc_subhookid_t;
/*
 * Some	information is returned	in a fixed format for raw entries.
 * Also	a pointer to the raw data and the raw data's length is returned.
 * The raw data	is a raw trace event as	defined	in /etc/trcfmt.
 * Thus	it is different	for 32 and 64 bit events.
 */
typedef	struct trc_raw_d {
	trc_hookid_t	_hookid;	/* hook	id stored as 0x0hhh. */
	trc_subhookid_t	_subhookid;	/* subhook id. */
	unsigned	_cpuid;		/* cpuid if applicable.	*/
	uint64_t	_tid;		/* thread id. */
	uint64_t	_timestamp;	/* time	stamp in ticks. */
	uint64_t 	_rawofst;	/* Raw data's file offset. */
	int 		_rawlen;	/* raw data length. */
	char 		*_rawbuf;	/* Pointer to raw data.	*/
	char 		*_component;	/* Component name, if applicable. */
	char 		*_logfile;	/* Name of source logfile */
	int 		_dupcount;	/* number of duplicate events detected*/
} trc_raw_t;

/*
 * trace hook information data.
 * This	is returned by trc_read() if TRC_LOGPROC was specified on the open.
 *
 * trchi_ascii points to a string containing the hook-specific printible
 * data	for this hook.	This data is always presented by the template
 * in the same way, so this won't be effected by selected options.
 */
typedef	struct trc_hook_d {
	trc_hookid_t 	_hookid;	/* Hook	id stored as 0xhhh0. */
	trc_subhookid_t	_subhookid;	/* subhook id */
	uint64_t 	_elapsed_nseconds; /* elapsed time in nanoseconds. */
	uint64_t 	_tid;		/* thread id */
	uint64_t 	_pid;		/* process id */
	uint64_t 	_svc;		/* current system call address */
	uint64_t 	_rawofst;	/* Raw data's file offset. */
	time64_t 	_trcontime;	/* Time of the last trcon */
	time64_t 	_trcofftime;	/* Time of the last trcoff */
	int 		_cpu;		/* cpu number. */
	int 		_rcpu;		/* CPUs	remaining in this trace. */
	int 		_pri;		/* process priority. */
	int 		_intr_depth;	/* Interrupt depth. */
	int 		_indent;	/* Indentation level, no. of tabs + 1. */
	char 		*_svcname;	/* current svc name */
	char 		*_procname;	/* Process' name */
	char 		*_filename;	/* current file */
	char 		*_ascii;	/* ASCII data printed by the template. */
	char 		*_component;	/* Component name, if applicable. */
	char 		*_logfile;	/* event's trace log file */
	int		_dupcount;	/* number of duplicate events detected*/
} trc_hook_t;

/*
 * Data	returned by trc_read().
 */
typedef	struct trc_read_d {
	int 		trcr_magic;	/* structure magic number. */
	int 		trcr_flags;	/* shared between raw and cooked. */
	union {
		trc_raw_t _raw;		/* raw data info. */
		trc_hook_t _hook;	/* hook	info data */
	} _ru;
} trc_read_t;

/* Definitions for trcr_flags. */
#define	TRCRF_RAW 0x1			/* On if raw data read.	*/
#define	TRCRF_PROC 0x2			/* On if processed or cooked data. */
#define	TRCRF_64BIT 0x10		/* on for a 64-bit entry, off if 32-bit. */
#define	TRCRF_TIMESTAMPED 0x20		/* ** on for a time stamped entry. */
#define	TRCRF_CPUIDOK 0x40		/* ** *** On if the cpu id is known. */
#define	TRCRF_GENERIC 0x80		/* On for a generic entry. */
#define	TRCRF_64BITTRACE 0x100		/* On for all entries of a 64-bit kernel trace */
#define TRCRF_LIVEDATA 0x200		/* Data is live, TRC_LOGLIVE, don't free it. */
#define TRCRF_NOPRINT 0x400		/* Template specified $NOPRINT or $SKIP. */
#define TRCRF_REGS 0x800		/* programmable regs present */
#define TRCRF_REGSTRACE 0x1000		/* programmable regs in this trace */

/*
 * flag	Notes:
 * * Only valid	for a raw read.
 * ** The TRCRF_CPUIDOK	flag is	set if the cpu id can be determined from
 * the raw data.  This is true if either the -p	flag was specified on a
 * 64-bit trace, or the	trace is a multi-cpu trace with	multiple files,
 * one per cpu.
 * *** If the flag isn't set, the contents of the associated field are 
 * undefined.
 */
/* Raw field definitions. */
#define	trcri_hookid _ru._raw._hookid
#define	trcri_subhookid	_ru._raw._subhookid
#define	trcri_cpuid _ru._raw._cpuid
#define	trcri_tid _ru._raw._tid
#define	trcri_timestamp	_ru._raw._timestamp
#define	trcri_rawofst _ru._raw._rawofst
#define	trcri_rawlen _ru._raw._rawlen
#define	trcri_rawbuf _ru._raw._rawbuf
#define	trcri_component _ru._raw._component
#define	trcri_logfile _ru._raw._logfile
#define trcri_dupcount	_ru._raw._dupcount

/*
 * Macros to extract data from the raw data buffer.
 * "r" is of type struct trc_read_t *.
 */
/* word size, 4 or 8 bytes. */
#define TRC_WORDSIZE(r) (((r)->trcr_flags&TRCRF_64BIT)? 8:4)
#define __TRC_D1_32(r) (*(uint*)(&(r)->trcri_rawbuf[sizeof(uint)]))
#define __TRC_D1_64(r) (*(uint64_t*)(&(r)->trcri_rawbuf[sizeof(uint64_t)]))
#define __TRC_D2_32(r) (*(uint*)(&(r)->trcri_rawbuf[2*sizeof(uint)]))
#define __TRC_D2_64(r) (*(uint64_t*)(&(r)->trcri_rawbuf[2*sizeof(uint64_t)]))
#define __TRC_D3_32(r) (*(uint*)(&(r)->trcri_rawbuf[3*sizeof(uint)]))
#define __TRC_D3_64(r) (*(uint64_t*)(&(r)->trcri_rawbuf[3*sizeof(uint64_t)]))
#define __TRC_D4_32(r) (*(uint*)(&(r)->trcri_rawbuf[4*sizeof(uint)]))
#define __TRC_D4_64(r) (*(uint64_t*)(&(r)->trcri_rawbuf[4*sizeof(uint64_t)]))
#define __TRC_D5_32(r) (*(uint*)(&(r)->trcri_rawbuf[5*sizeof(uint)]))
#define __TRC_D5_64(r) (*(uint64_t*)(&(r)->trcri_rawbuf[5*sizeof(uint64_t)]))
#define __TRC_H32(r) (*(uint*)((r)->trcri_rawbuf))
#define __TRC_H64(r) (*(uint64_t*)((r)->trcri_rawbuf))
#define __TRC_DBYTES_32(r) (((r)->trcr_flags & TRCRF_GENERIC)?\
	  (HKWDTOBLEN(__TRC_H32(r))+8): (4*HKWDTOLEN(__TRC_H32(r))))
#define __TRC_DBYTES_64(r) (((r)->trcr_flags & TRCRF_GENERIC)?\
	  (HKWD64_TO_LEN(__TRC_H64(r))+16): (HKWD64_TO_LEN(__TRC_H64(r))+8))
#define __TRC_DBYTES(r) (((r)->trcr_flags & TRCRF_64BIT)?\
	  __TRC_DBYTES_64(r): __TRC_DBYTES_32(r))
#define __TRC_TIDOFF_32(r) (((r)->trcr_flags & TRCRF_64BITTRACE)?\
	  (8*((__TRC_DBYTES_32(r)+7)/8)): (4*((__TRC_DBYTES_32(r)+3)/4)))
#define __TRC_TIDOFF_64(r) (8*((__TRC_DBYTES_64(r)+7)/8))
#define __TRC_TIDOFF(r) (((r)->trcr_flags & TRCRF_64BIT)?\
	  __TRC_TIDOFF_64(r): __TRC_TIDOFF_32(r))
/*
 * The thread id and timestamp are only 4 bytes for a 32-bit hook in a
 * 32-bit trace, otherwise they're 8 bytes.
 */
#define TRC_TIDSIZE(r) \
	(((r)->trcr_flags & TRCRF_64BITTRACE)?8:TRC_WORDSIZE(r))
#define TRC_TIMESIZE(r) TRC_TIDSIZE(r)
#define __TRC_TS_32(r) (*(uint*)(&(r)->trcri_rawbuf[__TRC_TIDOFF_32(r)+TRC_TIDSIZE(r)]))
#define __TRC_TS_64(r) (*(uint64_t*)(&(r)->trcri_rawbuf[__TRC_TIDOFF_64(r)+TRC_TIDSIZE(r)]))
#define __TRC_RAWTIME(r) (((r)->trcr_flags & TRCRF_64BIT)?\
	  __TRC_TS_64(r): (uint64_t)__TRC_TS_32(r))
/* Number of data words (non-generic only). */
#define TRC_DWORDS(r) ((__TRC_DBYTES(r)-TRC_WORDSIZE(r))/TRC_WORDSIZE(r))
/* Data words 1 - 5 */
#define TRC_LONGD1(r) (((r)->trcr_flags & TRCRF_64BIT)?\
	  __TRC_D1_64(r): (uint64_t)__TRC_D1_32(r))
#define TRC_LONGD2(r) (((r)->trcr_flags & TRCRF_64BIT)?\
	  __TRC_D2_64(r): (uint64_t)__TRC_D2_32(r))
#define TRC_LONGD3(r) (((r)->trcr_flags & TRCRF_64BIT)?\
	  __TRC_D3_64(r): (uint64_t)__TRC_D3_32(r))
#define TRC_LONGD4(r) (((r)->trcr_flags & TRCRF_64BIT)?\
	  __TRC_D4_64(r): (uint64_t)__TRC_D4_32(r))
#define TRC_LONGD5(r) (((r)->trcr_flags & TRCRF_64BIT)?\
	  __TRC_D5_64(r): (uint64_t)__TRC_D5_32(r))
/* Raw ticks from the event, 0 if not timestamped */
#define TRC_RAWTICKS(r) (((r)->trcr_flags&TRCRF_TIMESTAMPED)?\
	  __TRC_RAWTIME(r): 0LL)
/* Offset to programmable registers. */
#define TRC_REGOFF(r) (((r)->trcr_flags & TRCRF_TIMESTAMPED)?\
	  (__TRC_TIDOFF(r)+TRC_TIDSIZE(r)+TRC_TIMESIZE(r)):\
	  (__TRC_TIDOFF(r)+TRC_TIDSIZE(r)))

/* processed data items. */
#define	trchi_hookid _ru._hook._hookid
#define	trchi_subhookid	_ru._hook._subhookid
#define	trchi_elapsed_nseconds _ru._hook._elapsed_nseconds
#define	trchi_tid _ru._hook._tid
#define	trchi_pid _ru._hook._pid
#define	trchi_svc _ru._hook._svc
#define	trchi_rawofst _ru._hook._rawofst
#define	trchi_trcontime _ru._hook._trcontime
#define	trchi_trcofftime _ru._hook._trcofftime
#define	trchi_cpuid _ru._hook._cpu
#define	trchi_rcpu _ru._hook._rcpu
#define	trchi_pri _ru._hook._pri
#define	trchi_intr_depth _ru._hook._intr_depth
#define	trchi_indent _ru._hook._indent
#define	trchi_svcname _ru._hook._svcname
#define	trchi_procname _ru._hook._procname
#define	trchi_filename _ru._hook._filename
#define	trchi_ascii _ru._hook._ascii
#define	trchi_component _ru._hook._component
#define	trchi_logfile	_ru._hook._logfile
#define trchi_dupcount	_ru._hook._dupcount

/* trc_read magic/version numbers. */
#define	TRCR_MAGIC_V1 0x54520101
#define	TRCR_MAGIC_V2 0x54520102
#define TRCR_MAGIC_V3 0x54520103
#define	TRCR_MAGIC TRCR_MAGIC_V3

/*
 * File	names array.
 * This	contains a base	file name plus one name	per cpu	file.
 */
typedef	char *trci_fname_t;

/* Trace hook set definitions. */
#define TRC_HKSETSIZE (TRC_NHOOKIDS/8)
typedef char trc_hookset_t[TRC_HKSETSIZE];

/*
 * Structure returned from trc_loginfo().
 */
typedef	struct trc_loginfo_d {
	int 		trci_magic;	/* structure magic number. */
	int 		trci_logmagic;	/* the trace log file magic number */
	time_t 		trci_time;	/* the time the	trace was taken	*/
	int 		trci_ipaddr;	/* The system's	IP address. */
	struct utsname	trci_uname;	/* uname info. */
	char 		*trci_cmd;	/* the command used to start the trace */
	trci_fname_t 	*trci_fnames;	/* Pointer to file names array.	*/
	int 		trci_mach_cpus;	/* the number of cpus in the machine */
	int 		trci_traced_cpus; /* the number of cpus traced */
	int 		trci_flags;	/* trace data stream flags. */
	int 		trci_obj_type;	/* the trace object type */
	trc_hookset_t 	trci_hookids;	/* hooks traced	(bitmap). */
} trc_loginfo_t;

#define	TRCI_MAGIC_V1 0x52434901
#define	TRCI_MAGIC_V2 0x52434902
#define	TRCI_MAGIC TRCI_MAGIC_V2

/*
 * trci_logmagic will be 0 for a 32-bit	raw trace.
 * There is no magic number for	that type of trace.
 */

/* Flag	bits for trci_flags. */
#define	TRCIF_MULTICPU 0x1		/* multi-cpu trace (trace -C) */
#define	TRCIF_64BIT 0x2			/* 32-bit if not set. */
#define	TRCIF_SEPSEG 0x10		/* separate segment buffering. */
#define	TRCIF_CONDTRACE	0x20		/* on if conditional trace (-jJkK) */
#define	TRCIF_CONDEXCL 0x40		/* set if exclusion (-kK) */
#define	TRCIF_COMPONENT 0x80            /* multi-component trace */

/*
 * This structure is used to pass search criteria to trc_find_first.
 *
 * To use it an operation is put in tls_op.  If it is a leaf operation,
 * the	trace data item	id is put in tls_field and the value to	compare
 * against is put in one of the tls_*field data items.
 * Boolean values are put in tls_intvalue.
 *
 * To connect operations, a unary or binary operator is put in	tls_op.
 * The	operation(s) to	apply the operator to are put in tls_left and,
 * if it's a binary operator, tls_right.
 */

typedef	struct trc_logsearch_d {
	unsigned int 	tls_op;		/* operation */
	union {				/* left side */
		struct trc_logsearch_d *_tls_left;
		unsigned int _tls_field;
	} tlsu1;
	union {				/* right side */
		struct trc_logsearch_d *_tls_right;
		int64_t _tls_longvalue;
		uint64_t _tls_ulongvalue;
		int 	_tls_intvalue;
		unsigned int _tls_uintvalue;
		short 	_tls_shortvalue;
		unsigned short _tls_ushortvalue;
		unsigned char *_tls_strvalue;
		char 	*_tls_hooksetvalue;/* trace hook set */
	} tlsu2;
} trc_logsearch_t;

#define	tls_left tlsu1._tls_left
#define	tls_field tlsu1._tls_field
#define	tls_right tlsu2._tls_right
#define	tls_longvalue tlsu2._tls_longvalue
#define	tls_ulongvalue tlsu2._tls_ulongvalue
#define	tls_intvalue tlsu2._tls_intvalue
#define	tls_uintvalue tlsu2._tls_uintvalue
#define	tls_shortvalue tlsu2._tls_shortvalue
#define	tls_ushortvalue tlsu2._tls_ushortvalue
#define	tls_strvalue tlsu2._tls_strvalue
#define	tls_hooksetvalue tlsu2._tls_hooksetvalue

/* Operators to	use in the match structures. */
#define	TLS_OP_EQUAL 0x01
#define	TLS_OP_NE 0x02
#define	TLS_OP_SUBSTR 0x03
#define	TLS_OP_LT 0x04
#define	TLS_OP_LE 0x05
#define	TLS_OP_GT 0x06
#define	TLS_OP_GE 0x07
#define	TLS_OP_FNMATCH 0x08
#define	TLS_OP_LEAF 0x100
#define	TLS_OP_NOT 0x101
#define	TLS_OP_AND 0x201
#define	TLS_OP_OR 0x202
#define	TLS_OP_XOR 0x203

/* Flags to combine with the field id to indicate the data type	of the field */
#define	TLS_TYPE 0xff00
#define	TLS_TYPE_STRING	0x0100
#define	TLS_TYPE_BOOLEAN 0x0200
#define	TLS_TYPE_LONG 0x1100
#define	TLS_TYPE_INT 0x1200
#define	TLS_TYPE_SHORT 0x1300
#define	TLS_TYPE_ULONG 0x2100
#define	TLS_TYPE_UINT 0x2200
#define	TLS_TYPE_USHORT	0x2300
#define TLS_TYPE_HOOKSET 0x3100

/* When may the argument be checked? */
#define TLS_CHECK_MASK 0xff0000
/* These items must be in numerical order. */
#define TLS_CHECK_NONE 0		/* No processing is necessary. */
#define TLS_AFTER_READ 0x100000		/* Check after it's read. */
#define TLS_AFTER_PROCESS 0x200000	/* Check after template processing. */
#define TLS_CHECK_ALL TLS_AFTER_PROCESS	/* Check after all processing is done. */

/* Flags to indicate which field to match in the find functions. */
#define	TLS_MATCH_FIELD	0xff
#define	TLS_MATCH_HOOKID (0x01|TLS_TYPE_USHORT|TLS_AFTER_READ)
#define	TLS_MATCH_HOOK_AND_SUBHOOK (0x02|TLS_TYPE_UINT|TLS_AFTER_READ)
#define	TLS_MATCH_HOOKSET (0x03|TLS_TYPE_HOOKSET|TLS_AFTER_READ)
#define	TLS_MATCH_TIME (0x04|TLS_TYPE_ULONG|TLS_AFTER_READ) /* time in nanoseconds from start of trace */
#define	TLS_MATCH_TID (0x05|TLS_TYPE_ULONG|TLS_AFTER_READ)
#define	TLS_MATCH_PID (0x06|TLS_TYPE_ULONG|TLS_AFTER_PROCESS)
#define	TLS_MATCH_RAWOFST (0x07|TLS_TYPE_ULONG|TLS_AFTER_READ)
#define	TLS_MATCH_CPUID (0x08|TLS_TYPE_UINT|TLS_AFTER_PROCESS)
#define	TLS_MATCH_RCPU (0x09|TLS_TYPE_UINT|TLS_AFTER_READ)
#define	TLS_MATCH_FLAGS	(0x0a|TLS_TYPE_UINT|TLS_AFTER_PROCESS) /* trcr_flags */
#define	TLS_MATCH_INTR_DEPTH (0x0b|TLS_TYPE_INT|TLS_AFTER_PROCESS)
#define	TLS_MATCH_PROCNAME (0x0c|TLS_TYPE_STRING|TLS_AFTER_PROCESS)
#define	TLS_MATCH_SVCNAME (0x0d|TLS_TYPE_STRING|TLS_AFTER_PROCESS)
#define	TLS_MATCH_PRI (0x0e|TLS_TYPE_INT|TLS_AFTER_PROCESS)
#define	TLS_MATCH_TICKS (0x0f|TLS_TYPE_ULONG|TLS_AFTER_READ) /* time in ticks from start of trace */
#define	TLS_MATCH_DATA (0x10|TLS_TYPE_STRING|TLS_AFTER_PROCESS) /* string must match the data. */
#define	TLS_MATCH_FILENAME (0x11|TLS_TYPE_STRING|TLS_AFTER_PROCESS)
#define	TLS_MATCH_TRCONTIME (0x12|TLS_TYPE_ULONG|TLS_AFTER_READ) /* time in nanoseconds from start of trace */
#define	TLS_MATCH_TRCOFFTIME (0x13|TLS_TYPE_ULONG|TLS_AFTER_READ) /* time in nanoseconds from start of trace */
#define	TLS_MATCH_COMPONENT (0x14|TLS_TYPE_STRING|TLS_AFTER_READ)

/* Array element type for hook ids and names. */
typedef struct trc_hooknm_d {
	trc_hookid_t 	hookid;
	char 		*hookname;
} trc_hooknm_t;

typedef struct trc_hookname_d {
	int 		trchn_magic;	/* Identifier for this version. */
	unsigned 	trchn_nhooks;	/* Number of hooks. */
	trc_hooknm_t 	*trchn_names;	/* Pointer to array of ids and names. */
} trc_hookname_t;
/* Magic numbers. */
#define TRCHN_MAGIC_V1 0x544e0101	/* version 1.1 */
#define TRCHN_MAGIC TRCHN_MAGIC_V1
/* TRC_HOOK_ALL as the second trc_hookname parameter returns all hooks. */
#define TRC_HOOK_ALL ((trc_hookid_t)0xffff)

/* Errors returned in addition to standard errno values. */
#define	TRCERR(rv) ((rv) < 0)
#define	TRCE_EOF -1			/* end-of-file or not found. */
#define	TRCE_BADFORMAT -2		/* data	format error. */
#define	TRCE_TOOMANY -3			/* a limit was exceeded. */
#define TRCE_TMPLTFORMAT -4		/* Template format error. */
#define	TRCE_WARN -10			/* Warning, the	function succeeded however. */

/* Functions supported by trc_libcntl(). */
#define TRC_CNTL_ADJLINENO 1		/* Adjust $LINENO. */
#define TRC_CNTL_NAMELIST 2		/* Set the namelist file. */
#define TRC_CNTL_TEXTOFFSET 3		/* offset returned text */
#define TRC_CNTL_TEXTOFFSET_SUBSEQUENT 4 /*   only on subsequent lines. */
#define TRC_CNTL_TEXTHEADER 5		/* header line */
#define TRC_CNTL_PAGESIZE 6		/* Page size */

/* Register values for the regid parameter to trc_reg(). */
#define TRC_PURR_ID 0			/* the PURR */
#define TRC_MMCR0_ID 1			/* MMCR0 */
#define TRC_MMCR1_ID 2			/* MMCR1 */
#define TRC_MMCRA_ID 3			/* MMCRA */
#define TRC_PMC1_ID 4			/* PMC1 */
#define TRC_PMC2_ID 5			/* PMC2 */
#define TRC_PMC3_ID 6			/* PMC3 */
#define TRC_PMC4_ID 7			/* PMC4 */
#define TRC_PMC5_ID 8			/* PMC5 */
#define TRC_PMC6_ID 9			/* PMC6 */
#define TRC_PMC7_ID 10			/* PMC7 */
#define TRC_PMC8_ID 11			/* PMC8 */
#define TRC_SPURR_ID 12			/* SPURR */

/*
 * The processor id values passed with utility hook 00A, subhook 0x14,
 * are found in /usr/include/sys/trchdr.h.
 */

/* Function Prototypes.	*/
#ifdef _NO_PROTO
extern int trc_open();
extern int trc_close();
extern int trc_read();
extern int trc_loginfo();
extern int trc_find_first();
extern int trc_find_next();
extern int trc_compare();
extern int trc_seek();
extern int trc_tell();
extern void trc_mapon();
extern void trc_mapoff();
extern int trc_libcntl();
extern int trc_free();
extern uint64_t trc_ticks2nanos();
extern char *trc_strerror();
extern void trc_perror();
extern void trc_hkemptyset();
extern void trc_hkfillset();
extern int trc_hkaddset();
extern int trc_hkdelset();
extern int trc_hkisset();
extern int trc_ishookset();
extern int trc_hookname();
extern int trc_copyread();
extern int trc_reg();
extern char *trc_logpath();
extern char *trc_ct_logpath();
extern char *trc_logmtrcdir();
#else
extern int trc_open(char *log_object_name, char	*template_file_name, int type,
	trc_loghandle_t	*handlep);
extern int trc_close(trc_loghandle_t handle);
extern int trc_read(trc_loghandle_t handle, trc_read_t *ret);
extern int trc_loginfo(char *log_object_name, trc_loginfo_t *infop);
extern int trc_find_first(trc_loghandle_t handle, trc_logsearch_t *argp,
	trc_read_t *ret);
extern int trc_find_next(trc_loghandle_t handle, trc_logsearch_t *argp,
	trc_read_t *ret);
extern int trc_compare(trc_loghandle_t handle, trc_logsearch_t *argp);
extern int trc_seek(trc_loghandle_t h, trc_logpos_t pos, trc_read_t *r);
extern int trc_tell(trc_loghandle_t h, trc_logpos_t *posp);
extern void trc_mapon();
extern void trc_mapoff();
extern int trc_libcntl(trc_loghandle_t h, int cmd, void *datap);
extern int trc_free(void *parmp);
extern uint64_t trc_ticks2nanos(trc_loghandle_t h, uint64_t ticks);
extern char *trc_strerror(void *h, int rv);
extern void trc_perror(void *h,	int rv,	char *str);
extern void trc_hkemptyset(trc_hookset_t hs);
extern void trc_hkfillset(trc_hookset_t hs);
extern int trc_hkaddset(trc_hookset_t hs, short hk);
extern int trc_hkdelset(trc_hookset_t hs, short hk);
extern int trc_hkisset(trc_hookset_t hs, short hk);
extern int trc_ishookset(int chan, char *hkst, size_t hkst_sz);
extern int trc_hookname(trc_loghandle_t handle, trc_hookid_t hook, trc_hookname_t *hooknamep);
extern int trc_copyread(trc_read_t *targ, trc_read_t *src);
extern int trc_reg(trc_loghandle_t handle, int regid, uint64_t *ret);
extern char *trc_logpath(void);
extern char *trc_ct_logpath(void);
extern char *trc_logmtrcdir (void);
#endif /* _NO_PROTO */

/*****************************
 * Trace group handling	API definitions.
 *****************************/

typedef	char *trcevgrp_db_t;
typedef	int trcevgrp_lock_t;
typedef	char *trcevgrp_grpname_t;
typedef	char *trcevgrp_type_t;
typedef	char *trcevgrp_members_t;
struct trcevgrp_group {
	trcevgrp_grpname_t trcevgrp_grpname;
	trcevgrp_type_t	trcevgrp_type;
	char 		*trcevgrp_description;
	trcevgrp_members_t trcevgrp_members;
};

/* Values for trcevgrp_type. */
#define	TRCEVGRP_RESERVED "reserved"

/* Possible delimiters for hooks and group names. */
#define	TRCHK_DELIMS	", \t\n"	/* Start literal at a tab stop */
/* Delimiter used by trcevgrp_read and in the database.	*/
#define	TRCHK_DELIMC ','
#define	TRCHK_DELIM ","
/* Master file name used for multi-component trace files */
#define COMP_TRACE_FILE "trc_ct.master"


/*
 * Group retrieval criteria. 
 * If the item is "*", this requests all groups. 
 */
typedef	trcevgrp_grpname_t trcevgrp_crit_t;

/* Data	returned by trcevgrp_read. */
struct trcevgrp_ret {
	int 		trcevret_nretrieved; /* Number retrieved. */
	struct trcevgrp_group *trcevret_grpp; /*	array of returned items. */
};

/* libtrace routines. */
#ifdef _NO_PROTO
extern int trcevgrp_read();
extern void trcevgrp_free();
extern int trcevgrp_update();
extern int trcevgrp_delete();
extern int trcevgrp_lock();
extern int trcevgrp_unlock();
#else /* !_NO_PROTO */
extern int trcevgrp_read(trcevgrp_crit_t criteria,
	struct trcevgrp_ret *ret);
extern void trcevgrp_free(struct trcevgrp_ret *ret);
extern int trcevgrp_update(struct trcevgrp_group *group);
extern int trcevgrp_delete(trcevgrp_crit_t criteria);
extern int trcevgrp_lock(trcevgrp_db_t db, trcevgrp_lock_t *lockhp);
extern int trcevgrp_unlock(trcevgrp_lock_t handle);
#endif /* _NO_PROTO */

#ifdef __cplusplus
}
#endif

#endif /* _H_libtrace */
