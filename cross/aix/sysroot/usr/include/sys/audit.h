/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/sys/audit.h 1.18.5.4                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1989,2010              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)60       1.18.5.4  src/bos/kernel/sys/audit.h, syssaud, bos53X, x2010_31A9 3/1/10 02:58:16 */
/*
 * COMPONENT_NAME: (SYSAUDIT) Audit Management
 *
 * FUNCTIONS: audit.h support for system auditing
 *
 * ORIGINS: 27 83
 *
 * (C) COPYRIGHT International Business Machines Corp. 1989,1996
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */                                                                   
/*
 *   LEVEL 1,  5 Years Bull Confidential Information
 */

#ifndef _H_AUDIT
#define _H_AUDIT

#include <sys/types.h>
#include <sys/user.h>
#include <sys/tcb.h>
/*
 * this file provides definitions for the
 * audit system call interfaces
 */

/*
 * commands for audit() system call
 */
#define	AUDIT_OFF	0
#define	AUDIT_ON	1
#define	AUDIT_QUERY	2
#define	AUDIT_RESET	4
#define AUDIT_NO_PANIC	8
#define AUDIT_PANIC	16
#define	AUDIT_EVENT_THRESHOLD	32
#define	AUDIT_BYTE_THRESHOLD	64
#define AUDIT_FULLPATH	128

#define audit_fp_flag	((audit_flag & AUDIT_FULLPATH) ? 1 : 0)

/*
 * commands for auditbin() system call
 */
#define AUDIT_WAIT	0x01
#define AUDIT_EXCL	0x02

/*
 * commands for auditproc() system call
 */
#define AUDIT_QEVENTS	1
#define AUDIT_EVENTS	2
#define AUDIT_QSTATUS	3
#define	AUDIT_STATUS	4
#define AUDIT_RESUME	0
#define AUDIT_SUSPEND	1
#define AUDIT_KLIST_EVENTS 5
/*
 * comands for auditevents() system call
 */
#define AUDIT_GET	0
#define AUDIT_SET	1
#define AUDIT_LOCK	3

/*
 * structure for auditevents() system call
 */
struct	audit_class
{
	char	*ae_name;	/* name of this administrative event */
	char	*ae_list;	/* ptr to list of null terminated base */
				/* event names, terminated by null string */
	int	ae_len;		/* length of names in ae_list (including */
				/* all nulls) */
};

/*
 * an audit trail consists of a sequence of bins.
 * each bin starts with a bin head, and must be terminated by
 * a bin tail before other bins can be appended to the trail
 */
struct aud_bin
{
	ushort_t bin_magic;
#define	AUDIT_MAGIC	0xf0f0
	u_char	 bin_version;
#define	VERSION_AUDIT_MERGED	3
#define	VERSION_AUDIT_64BIT	4
#define	VERSION_AUDIT_IS64BIT	0200
#define	AUDIT_VERSION	VERSION_AUDIT_64BIT
	u_char	 bin_tail;
#define	AUDIT_HEAD	0
#define	AUDIT_BIN_END	1
#define	AUDIT_TRAIL	2
 	unsigned int	 bin_len;/* unpacked length of bin's records, if this */
				/* is non-zero, the bin has a tail record */
	unsigned int	 bin_plen;/* current length of bin's records (may be */
				/* packed) */
	time_t bin_time;	/* timestamp at which head/tail was written */
	char	 bin_cpuid[8];
};

struct __aud_bin32 {
	ushort_t bin_magic;
	u_char   bin_version;
	u_char   bin_tail;
	unsigned int     bin_len;
	unsigned int     bin_plen;
	time32_t bin_time;
	char     bin_cpuid[8];
};

struct __aud_bin64 {
	ushort_t bin_magic;
	u_char   bin_version;
	u_char   bin_tail;
	unsigned int     bin_len;
	unsigned int     bin_plen;
	time64_t bin_time;
	char     bin_cpuid[8];
};

struct aud_rec_cb {
	ushort_t	arb_magic;/* magic value new format = AUD_REC_MAGIC */
	uchar_t		arb_pad;	/* unused at present */
	uchar_t		arb_auditstatus;/* audit status of process */
	int		arb_fd;		/* this stream's fd # in the process */
	uint_t		arb_auditmask;	/* process audit mask */
	uid_t		arb_uid;	/* effective user id */
	gid_t		arb_gid;	/* effective group id */
	uint_t		arb_result;	/* status - see auditlog for values */
	uid_t		arb_ruid;	/* real user id */
	uid_t		arb_luid;	/* login user id */
	char		arb_name[MAXCOMLEN];/* null terminated program name */
	pid32_t		arb_pid;	/* process id */
	pid32_t		arb_ppid;	/* process id of parent */
	tid32_t		arb_tid;	/* thread id */
	time32_t	arb_time;	/* time in secs */
	time32_t	arb_ntime;	/* nanosecs offset from ah_time */
/* arb_status values */
#define AUDIT_SUSPENDED 0x01	/* auditing suspended for this process */
};


/* auditobj parameters */

struct o_event
{
	int	o_type;		/* type of object (AUDIT_FILE,..) */
#define AUDIT_FILE 	0x01
	char	*o_name;	/* object to be audited */

#ifdef O_EVENT_RENAME
	char    *o_event_array[16];
#else
	char	*o_event[16];   /* event names indexed by access */
#endif

#define AUDIT_READ 	0
#define AUDIT_WRITE 	1
#define AUDIT_EXEC 	2
}; 

/* auditpack parameters */
#define AUDIT_PACK	0
#define AUDIT_UNPACK	1

/* audit device ioctl */
#define AIO_EVENTS	0x1

/* 
 * aud_rec ah_status values 
 */
#define AUDIT_OK		0
#define AUDIT_TCB_MOD		0x99
#define AUDIT_FAIL		0x01
#define AUDIT_FAIL_AUTH		0x03
#define AUDIT_FAIL_PRIV		0x05
#define AUDIT_FAIL_ACCESS	0x09
#define AUDIT_FAIL_DAC		0x19

/*
 * List of modifications to the audit record extension data
 */

#define	AUDIT_RECORD_VERSION_MERGED	2
#define	AUDIT_RECORD_VERSION_64BIT	3
#define	AUDIT_RECORD_VERSION_IS64BIT	0200
#define	AUDIT_RECORD_VERSION AUDIT_RECORD_VERSION_64BIT

struct aud_rec_base {
	ushort_t arb_magic;	/* magic value new format = AUD_REC_MAGIC */
#define	AUDIT_HDR0	0
#define	AUDIT_HDR1	1
#define AUDIT_HDR2	( (sizeof(struct aud_rec_ext) << 8) | AUDIT_RECORD_VERSION )
#define AUDIT_HDR3	AUDIT_HDR2 | AUDIT_RECORD_VERSION_IS64BIT

#ifndef __64BIT_KERNEL
#define AUDIT_HDR	AUDIT_HDR2 
#else
#define	AUDIT_HDR	AUDIT_HDR3
#endif

	ushort_t arb_length;	/* length of tail of this record */ 
	char	arb_event[16];	/* event name with null terminator */ 
	unsigned int arb_result;/* the audit status - see auditlog for values */
	uid_t	arb_ruid;	/* real user id */
	uid_t	arb_luid;	/* login user id */
	char	arb_name[MAXCOMLEN];	/* program name with null terminator */
	pid32_t	arb_pid;		/* process id */
	pid32_t	arb_ppid;	/* process id of parent */
	tid32_t arb_tid;         /* thread id */
	time32_t	arb_time;	/* time in secs */
	time32_t	arb_ntime;	/* nanosecs offset from ah_time */
};

/*
 * This structure must be maintained so that there is no padding
 * between the base and the extension.  Each field in this extension
 * requires a macro in order to be accessed as the definitions which
 * are used to preserve the "no padding" rule may not be the native
 * machine type.
 */

struct aud_rec_ext {
#define AUD_HDR_EXT_CPUID_LEN		8
	char are_cpuid[AUD_HDR_EXT_CPUID_LEN];
	unsigned int	are_time64[2];
};

struct aud_rec { 
	struct aud_rec_base ah_base;
#define ah_magic ah_base.arb_magic
#define ah_length ah_base.arb_length
#define ah_event ah_base.arb_event
#define ah_result ah_base.arb_result
#define ah_ruid ah_base.arb_ruid
#define ah_luid ah_base.arb_luid
#define ah_name ah_base.arb_name
#define ah_pid ah_base.arb_pid
#define ah_ppid ah_base.arb_ppid
#define ah_tid ah_base.arb_tid
#define ah_time ah_base.arb_time
#define ah_ntime ah_base.arb_ntime

	struct aud_rec_ext ah_ext;
#define ah_cpuid ah_ext.are_cpuid
#define ah_time64 ah_ext.are_time64
	/* record tail follows */
};

#define REC_HDR_SIZ (sizeof (struct aud_rec))

#define	AUDIT_CPU_ID(rec) \
	((AUDIT_HDR_VERSION(rec) >= AUDIT_RECORD_VERSION_MERGED) ? \
		(((struct aud_rec *)(rec))->ah_cpuid) : NULL)
#define	AUDIT_HDR_VERSION(rec) \
	((((struct aud_rec *) (rec))->ah_magic) & 0x007f)
#define	AUDIT_HDR_EXT_SIZE(rec) \
	(((((struct aud_rec *) (rec))->ah_magic) >> 8) & 0xff)
#define	AUDIT_REC_SIZE(rec) \
	(sizeof (struct aud_rec_base) + AUDIT_HDR_EXT_SIZE(rec))
#define	AUD_REC_TAIL(rec) \
	(((char *) rec) + (int) AUDIT_REC_SIZE(rec))
#define	AUDIT_TIME_64(rec) \
	(AUDIT_HDR_VERSION(rec) >= AUDIT_RECORD_VERSION_64BIT && \
		AUDIT_64BIT_TAIL(rec) ? \
		((((time64_t) (rec)->ah_time64[0]) << 32) | \
			((time64_t)(rec)->ah_time64[1])) : \
			((time64_t) (rec)->ah_time ))
#define	AUDIT_64BIT_TAIL(rec) \
	((((struct aud_rec *)(rec))->ah_magic) & \
	 AUDIT_RECORD_VERSION_IS64BIT)
#define AUDIT_BIN_IS64BIT(bh) \
	((((struct aud_bin *)(bh))->bin_version) & \
	VERSION_AUDIT_IS64BIT)
#define	AUDIT_BIN_CPUID(bh) \
	(AUDIT_BIN_IS64BIT(bh) ? (((struct __aud_bin64 *)(bh))->bin_cpuid) : \
	  (((struct __aud_bin32 *)(bh))->bin_cpuid))
		
struct auddata {		/* audit relevant data */
	ushort	svcnum;		/* name index from audit_klookup */
	ushort	argcnt;		/* number of arguments stored */
	int	args[10];	/* Parameters for this call */
	char	*audbuf;	/* buffer for misc audit record */
	int	bufsiz;		/* allocated size of pathname buffer */
	int	buflen;		/* actual length of pathname(s) */
	int	bufsrt;		/* event starts using audbuf from this point */
	ushort	bufcnt;		/* number of pathnames stored */
	unsigned int status;	/* audit status bitmap */
	char	*save[2];
};

/*
 * This structure is passed as the extension to a call to openx()
 * to open /dev/audit.
 */

struct auditext {
	char	*ax_classes;
	int	ax_len;
};

#ifdef _KERNEL
struct	auditext_32 {
	__cptr32 ax_classes;
	int	ax_len;
};

struct	auditext_64 {
	__cptr64 ax_classes;
	int	ax_len;
};
#endif


extern int auditlog(char *, int, char *, int);
extern char *auditpack(int, char *);

#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)

extern int audit(int, int);
extern int auditbin(int, int, int, int);
extern int auditevents(int, struct audit_class *, int);
extern int auditobj(int, struct o_event *, int);
extern int auditproc(pid_t, int, char *, int);
extern int audit_svcstart(const char *, int *, int, ...); 
extern int audit_svcbcopy(char *, uint32long64_t);
extern int audit_svcfinis(void);
extern int aud_vn_create(struct vnode *, struct vnode **, int32long64_t,
						caddr_t, int32long64_t, caddr_t *,struct ucred *);
extern int aud_vn_rdwr(struct vnode *, enum uio_rw, int32long64_t, 
						struct uio *, int32long64_t, caddr_t,struct ucred *);
extern int aud_vn_open(struct vnode *, int32long64_t, int);
extern int refreshdata(uid_t usr, char *classes, int len);

#endif /* __64BIT_KERNEL || __FULL_PROTO */



#endif /* _H_AUDIT */

