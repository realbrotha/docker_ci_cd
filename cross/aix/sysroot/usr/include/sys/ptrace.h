/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/kernel/sys/ptrace.h 1.12.3.17                           */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,1995          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)27       1.12.3.17  src/bos/kernel/sys/ptrace.h, sysproc, bos53L, l2007_14A0 3/31/07 19:59:20 */
/*
 *   COMPONENT_NAME: SYSPROC
 *
 *   FUNCTIONS: 
 *
 *   ORIGINS: 3, 27, 83
 *
 */

#ifndef _H_PTRACE
#define _H_PTRACE

#include <sys/thread.h>

/*
 * Request parameters for the ptrace() system call.  The child process must
 * issue the PT_TRACE_ME ptrace request to set the child's trace flag that
 * causes the child to be left in a stopped state upon receipt of a signal.
 * The parent process can examine and modify the child process's memory
 * image using the ptrace() call when the child is in the stopped state.
 * Also, the parent process can cause the child process to either terminate
 * or continue, with the possibility of ignoring the signal that caused it
 * to stop.
 */

#define	PT_TRACE_ME	0	/* used ONLY by child process to be traced */
#define	PT_READ_I	1	/* read child instruction address space */
#define	PT_READ_D	2	/* read child data address space */
#define	PT_WRITE_I	4	/* write child instruction address space */
#define	PT_WRITE_D	5	/* write child data address space */
#define	PT_CONTINUE	7	/* continue execution */
#define	PT_KILL		8	/* terminate execution */
#define	PT_STEP		9	/* execute one or more instructions */	

#define	PT_READ_GPR	11	/* read general purpose register */
#define	PT_READ_FPR	12	/* read floating point register */

#define	PT_WRITE_GPR	14	/* write general purpose register */
#define	PT_WRITE_FPR	15	/* write floating point register */

#define PT_READ_BLOCK	17	/* read block of data ptrace(17) */
#define PT_WRITE_BLOCK	19	/* write block of data ptrace(19) */

#define PT_ATTACH	30	/* attach to a process */
#define PT_DETACH 	31	/* detach a proc to let it keep running */
#define PT_REGSET 	32	/* return entire register set to caller */
#define PT_REATT  	33	/* reattach debugger to proc */
#define PT_LDINFO   	34	/* return loaded program file descriptor/info */
#define PT_MULTI  	35	/* set/clear multi-processing */
#define PT_NEXT		36	/* step over instruction, not implemented in */
			 	/* AIX ptrace (only for kdbx kernel debugger) */
#define PT_SET		37	/* Set a ptrace flag or attribute */
#define PT_CLEAR	38	/* Clear a ptrace flag or attribute */
#define PT_LDXINFO	39	/* return loaded program file descriptor/info */
				/* in an extended ldinfo structure */

#define PT_QUERY	40	/* return info about ptrace capabilities */
#define PT_WATCH	41	/* set/clear watchpoints */

#define PTT_CONTINUE	50	/* continue execution of one or more threads */
#define PTT_STEP	51	/* execute one or more instr. for a thread */
#define PTT_READ_SPRS	52	/* read thread's special purpose registers */
#define PTT_WRITE_SPRS	53	/* write thread's special purpose registers */
#define PTT_READ_GPRS	54	/* read thread's general purpose registers */
#define PTT_WRITE_GPRS	55	/* write thread's general purpose registers */
#define PTT_READ_FPRS	56	/* read thread's floating point registers */
#define PTT_WRITE_FPRS	57	/* write thread's floating point registers */
#define PTT_READ_VEC	58	/* read thread's vector registers */
#define PTT_WRITE_VEC	59	/* write thread's vector registers */
#define PTT_WATCH	60	/* thread watchpoint */
#define PTT_SET_TRAP	61	/* set thread breakpoint */
#define PTT_CLEAR_TRAP	62	/* clear thread breakpoint */
#define PTT_READ_UKEYSET 63	/* read thread's active user-key set */
#define PT_GET_UKEY	64	/* get the user-key assigned to an address */
#define PTT_READ_FPSCR_HI 65	/* read thread's upper 32-bits of FPSCR */
#define PTT_WRITE_FPSCR_HI 66	/* write thread's upper 32-bits of FPSCR */

#define PT_COMMAND_MAX 66

/* maximum bytes transferred with read/write via the ptrace() system call */
#define	IPCDATA		1024

/* Flags that can be set with PT_SET or cleared with PT_CLEAR */
#define PTFLAG_FAST_TRAP	0x00000001 /* Enable fast trap capability. */
#define PTFLAG_FAST_WATCH	0x00000002 /* Enable fast watch capability. */
#define PTFLAG_FAST_MASK	(PTFLAG_FAST_TRAP|PTFLAG_FAST_WATCH)

/* Macros for handling "Fast Trap" instructions */
#define _FASTTRAP_OP      0x0DDF8000
#define _FASTTRAP_OP_MASK 0xFFFF8000
#define _FASTTRAP_NUM     0x00007FFF

/*
 * ptracex service for debugging 64-bit programs.  
 *
 *	Neither the ptrace or ptracex system calls are callable from
 *	a 64-bit process.  The debugger must be 32-bit. 
 *
 *      If the debuggee is a 32-bit process, the options which refer
 *      to GPRs or SPRs fail with errno = EIO, and the options which
 *      specify addresses in the debuggee's address space which are
 *      larger than 2**32 - 1 fail with errno set to EIO.
 *
 *      Also, the options PT_READ_U and PT_WRITE_U are not supported
 *      if the debuggee is a 64-bit program, nor are they supported
 *	in the 64-bit kernel (errno = ENOTSUP).
 */

#ifdef _NO_PROTO
int ptrace();
int ptracex();
int ptrace64();
#else /* _NO_PROTO */
int ptrace(int request, int32long64_t id, int *address, int data, int *buffer);
int ptracex(int request, int32long64_t id, long long addr, int data, int *buff);
int ptrace64(int request, long long id, long long addr, int data, int *buff);
#endif /* _NO_PROTO */

/* SPRs for 32-bit process. 
 */
struct ptsprs {
        unsigned int    pt_iar;         /* instruction address register */
        unsigned int    pt_msr;         /* machine state register       */
        unsigned int    pt_cr;          /* condition register           */
        unsigned int    pt_lr;          /* link register                */
        unsigned int    pt_ctr;         /* count register               */
        unsigned int    pt_xer;         /* fixed point exception        */
        unsigned int    pt_mq;          /* multiply/quotient register   */
        unsigned int    pt_reserved_0;  /* reserved                     */
        unsigned int    pt_fpscr;       /* floating point status reg    */
        char            pt_reserved_1;  /* reserved                     */
        char            pt_reserved_2;  /* reserved                     */
        char            pt_reserved_3[2];/* reserved                    */
        unsigned int    pt_reserved_4[5];/* reserved                    */
        unsigned int    pt_reserved_5;  /* reserved                     */
        unsigned int    pt_reserved_6;  /* reserved                     */
        unsigned int    pt_reserved_7;  /* reserved                     */
        unsigned int    pt_reserved_8;  /* reserved                     */
        unsigned int    pt_reserved_9;  /* reserved                     */
        unsigned int    pt_fpscrx;      /* software extension to fpscr  */
};

/* SPRs for 64-bit process. Note that this declare assumes programs
 * which need this structure (e.g debuggers) are 32-bit programs.
 */
struct ptxsprs {
        unsigned long long      pt_msr;  /* machine state register    	*/
        unsigned long long      pt_iar;  /* instruction addr register 	*/
        unsigned long long      pt_lr;   /* link register             	*/
        unsigned long long      pt_ctr;  /* count register              */
        unsigned int            pt_cr;   /* condition register        	*/
        unsigned int            pt_xer;  /* fixed point exception 	*/
        unsigned int            pt_fpscr; /* floating point status reg 	*/
        unsigned int            pt_fpscrx; /* software extension to fpscr */
};

struct ptthreads 
{
	tid32_t	th[32767];
};

struct ptthreads64
{
	tid64_t	th[32767];
};

typedef struct _ptrace_info {
	unsigned int	ptrace_info_size;    /* size of _ptrace_info struct   */
	unsigned int	total_info_size;     /* buf size to return all info   */
	offset_t	watchpoints_hdr_off; /* offset to _pt_watchpoints_hdr */
} _ptrace_info;

typedef struct _pt_watchpoints_hdr {
	offset_t	pt_watchpoints_offset;	/* offset to _pt_watchpoint's */
	unsigned int	pt_watchpoints_count;	/* number of pt_watchpoint's  */
	unsigned int	pt_watchpoint_size;	/* _pt_watchpoint struct size */
	unsigned int	pt_validate:1;	/* PT_WATCH only, validate wp's       */
	unsigned int	pt_wp_write:1;	/* PT_QUERY only, write wp supported  */
	unsigned int	pt_wp_read:1;	/* PT_QUERY only, read wp supported   */
	unsigned int	pt_wp_thread:1;	/* PT_QUERY only, thread-based wp sup */
	unsigned int	pt_wp_value:1;	/* PT_QUERY only, value-based wp sup  */
	unsigned int	pt_wp_shmem:1;	/* PT_QUERY only, shared mem wp sup   */
	unsigned int	pt_wp_mapped:1;	/* PT_QUERY only, mapped file wp sup  */
	unsigned int	:25;
	unsigned int	reserved;
} _pt_watchpoints_hdr;

typedef struct _pt_watchpoint {
	unsigned long long		wp_start; /* address of watchpoint    */
	unsigned long long		wp_size;  /* size of watched range    */
	union {
		unsigned long long	wp_tid;   /* th id, 0 for proc-based  */
		struct {
			unsigned int	wp_minsize; /* minimum size of wp     */
			unsigned short	wp_count;   /* number of wp of type   */
			unsigned short	wp_align;   /* required wp alignment  */
		} pt_watchpoint_info;		    /* PT_QUERY only          */
	} pt_wp_u;
#ifndef __64BIT__
	unsigned int			reserved;
#endif
	void				*wp_value;    /* ptr to value to watch for */
	unsigned int			wp_ignore:1;  /* wp is ignored        */
	unsigned int			wp_invalid:1; /* wp is invalid        */
	unsigned int			wp_filter:1;  /* s/w filter implemented */
	unsigned int			wp_thread:1;  /* thread-based wp sup  */
	unsigned int			wp_shmem:1;   /* shared memory wp sup */
	unsigned int			wp_mapped:1;  /* mapped file wp sup   */
	unsigned int			wp_read:1;    /* read watchpoint      */
	unsigned int			wp_write:1;   /* write watchpoint     */
	unsigned char			wp_style;     /* style of watchpoint  */
} _pt_watchpoint;

/* wp_style flag */
#define _WP_STYLE_ANY		1
#define _WP_STYLE_HARDWARE	2
#define _WP_STYLE_HARDWARE1	3
#define _WP_STYLE_HARDWARE_LAST	127
#define _WP_STYLE_SOFTWARE	128
#define _WP_STYLE_SOFTWARE1	129
#define _WP_STYLE_SOFTWARE_LAST	255

#ifdef _KERNEL

#define OLD_MAXTHREADS 512

#define	IPCBSZ		(sizeof (double))

/* 
 * Allocate space in kernel buffers for MAXTHREADS + primary tid +
 * trailing NULL_TID.  Expanded tids are used.  
 */
#define LARGEBLKSIZE	((MAXTHREADS+2)*sizeof(tid64_t))
#define SMALLBLKSIZE	((OLD_MAXTHREADS+2)*sizeof(tid64_t))

#ifdef __64BIT_KERNEL
#define MAXLDINFO       (8*128*1024)
#else
#define MAXLDINFO       (128*1024)
#endif

struct ptipc {
	int		 ip_flag;	/* flags defined below */
	struct pvproc	*ip_dbpv;	/* debugger process */
        tid_t		 ip_tid;        /* debugger thread */
	tid_t		 ip_event;	/* event used for ptrace/procxmt IPC */
	tid_t		 ip_id;		/* ptrace(2) id parmameter */
	int		 ip_req;	/* ptrace(2) request parameter */
#ifndef __64BIT_KERNEL
	int		 ip_addr64;	/* high order 32-bits of ip_addr */
#endif
	int		*ip_addr;	/* ptrace(2) address parameter */
	int		 ip_data;	/* ptrace(2) data parameter */
	char		*ip_blkdata;	/* pointer to IPCDATA sized block or */
	char		 ip_buf[IPCBSZ];/* ... here if !(ip_flag & IPCBLKDATA)*/
};

/* ip_flag */
#define	IPCBUSY		0x00000001
#define	IPCWANTED	0x00000002
#define	IPCPTRACE	0x00000004
#define	IPCBLKDATA	0x00000008
#define IPCBLKLARGE	0x00000010
#endif /* _KERNEL */

/*
 * Linux compatibility section.
 * Define the Linux __ptrace_request enum.  This is not
 * ifdef'd because the library wrapper needs to see the enum
 * without the _LINUX_SOURCE_COMPAT redefines of the PT_* values.
 */
enum __ptrace_request {
	PTRACE_TRACEME,
	PTRACE_PEEKTEXT,
	PTRACE_PEEKDATA,
	PTRACE_PEEKUSER,
	PTRACE_POKETEXT,
	PTRACE_POKEDATA,
	PTRACE_POKEUSER,
	PTRACE_CONT,
	PTRACE_KILL,
	PTRACE_SINGLESTEP,
	PTRACE_GETREGS,
	PTRACE_SETREGS,
	PTRACE_GETFPREGS,
	PTRACE_SETFPREGS,
	PTRACE_ATTACH,
	PTRACE_DETACH,
	PTRACE_SYSCALL
};

#ifdef _LINUX_SOURCE_COMPAT

/*
 * Define/redefine the PT_* command values as Linux sees them.
 */
#undef  PT_TRACE_ME
#define PT_TRACE_ME	PTRACE_TRACEME
#undef  PT_READ_I
#define PT_READ_I	PTRACE_PEEKTEXT
#undef  PT_READ_D
#define PT_READ_D	PTRACE_PEEKDATA
#define PT_READ_U	PTRACE_PEEKUSER
#undef  PT_WRITE_I
#define PT_WRITE_I	PTRACE_POKETEXT
#undef  PT_WRITE_D
#define PT_WRITE_D	PTRACE_POKEDATA
#define PT_WRITE_U	PTRACE_POKEUSER
#undef  PT_CONTINUE
#define PT_CONTINUE	PTRACE_CONT
#undef  PT_KILL
#define PT_KILL		PTRACE_KILL
#undef  PT_STEP
#define PT_STEP		PTRACE_SINGLESTEP
#define PT_GETREGS	PTRACE_GETREGS
#define PT_SETREGS	PTRACE_SETREGS
#define PT_GETFPREGS	PTRACE_GETFPREGS
#define PT_SETFPREGS	PTRACE_SETFPREGS
#undef  PT_ATTACH
#define PT_ATTACH	PTRACE_ATTACH
#undef  PT_DETACH
#define PT_DETACH	PTRACE_DETACH

/*
 * Prototype.
 */
extern long __linux_ptrace(enum __ptrace_request, pid_t, void *, void *);
#define ptrace(a, b, c, d) __linux_ptrace((a), (b), (c), (d))

#endif	/* _LINUX_SOURCE_COMPAT */

/*
 * End of Linux compatibility section.
 */

#endif /* _H_PTRACE */
