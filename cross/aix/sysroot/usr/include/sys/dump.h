/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53S src/bos/kernel/sys/dump.h 1.67.1.1                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1988,1995              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)02     1.67.1.1  src/bos/kernel/sys/dump.h, sysdump, bos53S, s2008_38C3 9/16/08 15:01:33 */

/*
 * FUNCTIONS:  header file for system dumpfile formats
 */

#ifndef	_H_DUMP
#define	_H_DUMP

#include <sys/types.h>
#include <sys/err_rec.h>

/* Defined to eliminate forward references. */
struct xmem;
struct mbuf;

/* For 64-bit, we need two general "cookies" to	use as segment values -	one
 * to indicate that this is part of the	general	kernel segment mapping,	and
 * another to indicate that this is actually a real address.  For 32-bit, we
 * already have	a flag to indicate real	addresses (D_REAL), but	we need	to
 * identify a dump area	as being part of the general kernel segment mapping,
 * since the kernel heap now spans segments, etc.  For binary compatibility,
 * the 32-bit "general"	segment	value will be 0.
 */
#define	DUMP_GEN_SEGVAL32	((uint)0)
#define	DUMP_GEN_SEGVAL64	((u_longlong_t)-1L)
#define	DUMP_REAL_SEGVAL32	(uint)0x007fffff
#define	DUMP_REAL_SEGVAL64	((u_longlong_t)-2L)
#ifdef _KERNEL
#ifdef __64BIT__
#define	DUMP_GEN_SEGVAL		((vmhandle_t)DUMP_GEN_SEGVAL64)
#define	DUMP_REAL_SEGVAL	((vmhandle_t)DUMP_REAL_SEGVAL64)
#else /* !__64BIT__ */
#define	DUMP_GEN_SEGVAL		((vmhandle_t)DUMP_GEN_SEGVAL32)
#define	DUMP_REAL_SEGVAL	((vmhandle_t)DUMP_REAL_SEGVAL32)
#endif
#else /* !_KERNEL */
#define	DUMP_GEN_SEGVAL		DUMP_GEN_SEGVAL32
/* DUMP_REAL_SEGVAL is DUMP_REAL_SEGVAL64 for backward compatibility. */
#define	DUMP_REAL_SEGVAL	DUMP_REAL_SEGVAL64
#endif /* _KERNEL */

#ifdef _KERNSYS
/*
 * System debug info can be gotten by setting the dump_debug global variable
 * to a non-zero value.
 * Bit 31: If set, enables debug printfs
 * Bit 30: enables certain printfs indicating we've hit key dump
 *        routines.
 * Bit 29: enables breakpoints in kdb for key dump routines.
 * Bit 28: shows dump stats at the end of dump.
 * Bit 27: shows dump queue activity, very verbose!
 * Bit 26: Disable dump timeouts used by parallel dump.  This is required
 *	  to interactively debug dumps.
 */
extern int dump_debug;
#define	__DDBG_PRT		0x1	/* debug prints */
#define __DDBG_KEY		0x2	/* key places in dump */
#define __DDBG_BRK		0x4	/* debug brk points */
#define __DDBG_STATS		0x8	/* show dump stats */
#define __DDBG_QUE		0x10	/* queue debug (much output!) */
#define	__DDBG_NO_TIMEOUT	0x20	/* disable dump timeouts */
#define __DDBG_SPIN_TRAP	0x40	/* trap in spin loops */

#define _DDBGPRT(s,a,b,c,d,e) \
        if (dump_debug & __DDBG_PRT)   printf(s,(a),(b),(c),(d),(e))
#define _DDBGPRT0(s) \
	if (dump_debug & __DDBG_PRT)   printf(s)
#define _DDBGPRT1(s,a) \
        if (dump_debug & __DDBG_PRT)   printf(s,(a))
#define _DDBGPRT2(s,a,b) \
        if (dump_debug & __DDBG_PRT)   printf(s,(a),(b))
#define _DDBGPRT3(s,a,b,c) \
        if (dump_debug & __DDBG_PRT)   printf(s,(a),(b),(c))
#define _DDBGPRT4(s,a,b,c,d) \
        if (dump_debug & __DDBG_PRT)   printf(s,(a),(b),(c),(d))
#define _DDBGPRT5 _DDBGPRT

#define _DDBGKEY0(s) \
        if (dump_debug & __DDBG_KEY)   printf(s)
#define _DDBGKEY1(s,a) \
        if (dump_debug & __DDBG_KEY)   printf(s,(a))
#define _DDBGKEY2(s,a,b) \
        if (dump_debug & __DDBG_KEY)   printf(s,(a),(b))
#define _DDBGKEY3(s,a,b,c) \
        if (dump_debug & __DDBG_KEY)   printf(s,(a),(b),(c))

#define _DDBGQUE2(s,a,b) \
        if (dump_debug & __DDBG_QUE)   printf(s,(a),(b))
#define _DDBGQUE3(s,a,b,c) \
        if (dump_debug & __DDBG_QUE)   printf(s,(a),(b),(c))

#define _DDBGBRK(a) \
	if (dump_debug & __DDBG_BRK)	brkpoint(a)

#endif /* _KERNSYS */

/*
 * XMEM	NOTE:
 * The xmem pointer is only used in the	unlimited dump table.
 * Thus	you must use the unlimited dump	table to dump a	discontiguous
 * multi-segment area.
 * You may dump	a contiguous, multi-segment, area in the 64-bit	environment
 * by simply specifying	the length, d_len, accordingly.
 */

/*
 * The following structures are	invariant dump entry definitions.
 */
struct cdt_entry64 {				/* component dump table	entry */
	char			d_name[16];	/* name	of data	area to	be dumped */
	unsigned long long	d_len;		/* length of data area to be dumped */
	__ptr64			d_ptr;		/* offset of data area to be dumped */
	unsigned long long	__d_segval;     /* segment value for d_ptr */
#ifdef __64BIT__
	struct xmem *		d_xmemp;	/* see "XMEM NOTE" above. */
#else /* !__64BIT__ */
	unsigned long long	d_xmemp;	/* see "XMEM NOTE" above. */
#endif
};

struct cdt_entry32 {			/* 32-bit component dump table entry */
	char		 d_name[8];	/* name	of data	area to	be dumped */
	__ulong32_t d_len;		/* length of data area to be dumped */
	__cptr32 d_ptr;			/* offset of data area to be dumped */
	union {
#ifdef __64BIT__
		vmhandle32_t _d_segval;	/* segment value for xmem operations */
		__ptr32	d_xmemp;	/* see "XMEM NOTE" above. */
#else /* !__64BIT__ */
		vmhandle_t _d_segval;	/* segment value for xmem operations */
		struct xmem *d_xmemp;	/* see "XMEM NOTE" above. */
#endif /* __64BIT__ */
	} _d;
};

/*
 * cdt_entry_vr	is for dumping real memory by virtual or real address.
 * It is only valid for	dump tables with the DMP_MAGIC_VR magic	number.
 * It is also only valid in a 32-bit dump.
 */
struct cdt_entry_vr {			/* dump	table entry for	v/r addresses*/
	char		 d_name[16];	/* name	of data	area to	be dumped */
	uint		 d_len;		/* length of data area to be dumped */
	int		 d_addrflags;	/* Address flags. */
	union {
		struct {
		    __cptr32 _d_ptr;	/* data	pointer	*/
#ifdef __64BIT__
		    union {
			vmhandle32_t _d_segval; /* segment id */
			vmid32_t _d_vmid;	/* segment id. */
		    } _ud;
#else /* !__64BIT__ */
		    union {
			vmhandle_t _d_segval; /* segment id	*/
			vmid_t _d_vmid;	/* segment id. */
		    } _ud;
#endif /* __64BIT__ */
		} _d;
		unsigned long long _d_realaddr;	/* real	address	*/
	} _u;
};

#define	d_realaddr _u._d_realaddr
#define	d_segval_v _u._d._ud._d_segval
#define	d_vmid_v _u._d._ud._d_vmid
#define	d_ptr_v	_u._d._d_ptr

/*
 * Flag	definitions for	d_addrflags.
 * All unused flag bits	must be	zero.
 */
#define	D_REAL 0x1		/* The address is a real address.
				 * if off, the address is virtual. */
#define D_VMID 0x2			/* The vmid is passed rather than the vmhandle. */

#ifdef __64BIT__
#define	cdt_entry cdt_entry64
#define d_segval __d_segval
#else /* !__64BIT__ */
#define	cdt_entry cdt_entry32		/* Base	dump table entry. */
#define	d_segval _d._d_segval
#define	d_xmemdp d_segval
#endif /* __64BIT__ */

struct cdt_head	{
	int  _cdt_magic;
	char _cdt_name[16];		/* component dump name */
	int  _cdt_len;			/* length of component dump table */
};

/*
 * We use a different magic number for each dump table.
 * Note	that cdt_entry_vr and associated structures is not
 * valid in 64-bit mode.
 * Note	also that all magic numbers are	available in either
 * mode	so a dump reader can at	least tell if it's a valid
 * dump.
 */
#define	DMP_MAGIC_32 0xEEEEEEEE
#define	DMP_MAGIC_VR 0xEEEEEEEF
#define	DMP_MAGIC_64 0xEEEEEEED
#define	DMP_MAGIC_U32 0xEEEEEEEC
#define	DMP_MAGIC_U64 0xEEEEEEEB
#define	DMP_MAGIC_UD32 0xEEEEEEEA
#define	DMP_MAGIC_UD64 0xEEEEEEE9
#define	DMP_MAGIC_END 0xEEEEEEE0	/* Magic no. at	the end	of the dump. */

#ifdef __64BIT__
#define	DMP_MAGIC DMP_MAGIC_64
#define	DMP_MAGIC_U DMP_MAGIC_U64
#define	DMP_MAGIC_UD DMP_MAGIC_UD64
#else /* !__64BIT__ */
#define	DMP_MAGIC  DMP_MAGIC_32
#define	DMP_MAGIC_U DMP_MAGIC_U32
#define	DMP_MAGIC_UD DMP_MAGIC_UD32
#endif /* __64BIT__ */

struct cdt0 {						/* component dump table	*/
	struct cdt_head	 _cdt_head;		/* minus the variable length table */
};

struct cdt {						/* component dump table	*/
	struct cdt_head	 _cdt_head;
	struct cdt_entry  cdt_entry[1];	/* component dump table	entries	*/
};

/*
 * Component dump table	which may contain real or virtual addresses.
 * This	is only	valid in 32-bit	dumps.
 */
struct cdt_vr {
	struct cdt_head	 _cdt_head;
	struct cdt_entry_vr cdt_entry[1];	/* component dump table	entries	*/
};

#define	cdt_magic _cdt_head._cdt_magic
#define	cdt_name  _cdt_head._cdt_name
#define	cdt_len	  _cdt_head._cdt_len

/*
 * Header for an unlimited size	dump table.
 * cdtu_magic must be DMP_MAGIC_U.
 * cdtu_nentries must be at least 1 when passed	to dump.
 * It will be 0	in the dump, indicating	an unlimited number of entries.
 * This	header is the same size	as cdt_head.
 * Note there are separate magic numbers for 32 or 64 bit dumps.
 */
struct cdt_head_u {
	int  cdtu_magic;		/* Set to DMP_MAGIC_U */
	char cdtu_name[16];		/* component dump name */
	int cdtu_nentries;		/* Number of entries. */
};

/* Unlimited dump table	data entry. */
struct cdt_entry_u {
	int du_magic;			/* Set to DMP_MAGIC_UD */
	char du_name[16];		/* name	of data	area to	be dumped */
	unsigned long long du_len;	/* length of data area to be dumped */
	__ptr64 du_ptr;			/* offset of data area to be dumped */
#ifdef _KERNEL
#ifdef __64BIT__
	vmhandle_t du_segval;		/* segment value for d_ptr */
	struct xmem * du_xmemp;   	/* Must be null if not used. */
#else /* !__64BIT__ (32-bit kernel) */
	uint du_fill1;			/* filler */
	vmhandle_t du_segval;		/* segment value for d_ptr */
	uint du_fill2;			/* filler */
	struct xmem * du_xmemp;   	/* Must be null if not used. */
#endif
#else /* !_KERNEL */
	unsigned long long du_segval;	/* 32/64 segment value for d_ptr */
	unsigned long long du_xmemp;   /* 32/64 xmem ptr. */
#endif
};

/* Test	for a real address in this unlimited table. */
#define	ISADDRREALU32(ceu) ((ceu)->du_segval ==	DUMP_REAL_SEGVAL32)
#define	ISADDRREALU64(ceu) ((ceu)->du_segval ==	DUMP_REAL_SEGVAL64)
#ifdef __64BIT__
#define	ISADDRREALU(ceu) ISADDRREALU64(ceu)
#else /* !__64BIT__ */
#define	ISADDRREALU(ceu) ISADDRREALU32(ceu)
#endif /* __64BIT__ */

/* A cdt_u dump	table must have	at least one entry. */
struct cdt_u {
	struct cdt_head_u cdtu_head;
	struct cdt_entry_u cdtu_entry[1];
};

/* See if this is an unlimited dump table. */
#define	ISDMPU32(cp) (((struct cdt_head_u *)(cp))->cdtu_magic == DMP_MAGIC_U32)
#define	ISDMPU64(cp) (((struct cdt_head_u *)(cp))->cdtu_magic == DMP_MAGIC_U64)
#define ISDMPU3264(cp) (ISDMPU32(cp) || ISDMPU64(cp))
/* See if this component data entry is from an unlimited table.	*/
#define	ISCEU32(cep) (((struct cdt_entry_u *)(cep))->du_magic == DMP_MAGIC_UD32)
#define	ISCEU64(cep) (((struct cdt_entry_u *)(cep))->du_magic == DMP_MAGIC_UD64)
#define ISCEU3264(cep) (ISCEU32(cep) || ISCEU64(cep))
#ifdef __64BIT__
#define	ISDMPU(cp) ISDMPU64(cp)
#define ISCEU(cep) ISCEU64(cep)
#else
#define	ISDMPU(cp) ISDMPU32(cp)
#define ISCEU(cep) ISCEU32(cep)
#endif

/* Validate the	magic number. */
#define	VALID_DMP_MAGIC_32_64(n) (((n) == DMP_MAGIC_32)	||\
				  ((n) == DMP_MAGIC_64)	||\
				  ((n) == DMP_MAGIC_VR)	||\
				  ((n) == DMP_MAGIC_U32) ||\
				  ((n) == DMP_MAGIC_U64))

#define	CDT_ENTRY_SIZE_32_64(comp_head)	\
	( ((comp_head)->cdt_magic==DMP_MAGIC_64) ?	\
		sizeof(struct cdt_entry64):	\
		( (((comp_head)->cdt_magic==DMP_MAGIC_U32) || \
		  ((comp_head)->cdt_magic==DMP_MAGIC_U64)) ? \
			sizeof(struct cdt_entry_u):	\
			( ((ISDMPVR(comp_head))	?	\
				sizeof(struct cdt_entry_vr) :\
				sizeof(struct cdt_entry32))) ) )

/* This	doesn't	include	the unlimited dump table. */
#define	NUM_ENTRIES_32_64(cp) \
	(((cp)->cdt_len	- sizeof(struct	cdt_head)) /\
	CDT_ENTRY_SIZE_32_64(cp) )

/* Address macros */
/* ISADDRREAL32, ADDR_VR32, and ISVMID must be used with a cdt_entry_vr. */
#define	ISADDRREAL32(cde) ((cde)->d_addrflags & D_REAL)
#define	ADDR_VR32(cde) (ISADDRREAL32(cde)) ? (cde)->d_realaddr :\
		      (unsigned	long long)(cde)->d_ptr_v
#define	ISVMID(cde) ((cde)->d_addrflags & D_VMID)
#define	ISADDRREAL64(cde) ((cde)->__d_segval == DUMP_REAL_SEGVAL64)
#define	ADDR_VR64(cde) (cde)->d_ptr

#ifdef __64BIT__
#define ADDR_VR ADDR_VR64
#else
#define ADDR_VR ADDR_VR32
#endif

/* ISADDRREAL works for unlimited dump tables also. */
#ifdef __64BIT__
#define	ISADDRREAL(cde)	\
	(ISCEU(cde)? ISADDRREALU((struct cdt_entry_u *)cde): ISADDRREAL64((struct cdt_entry *)cde))
#else
#define	ISADDRREAL(cde)	\
	(ISCEU(cde)? ISADDRREALU((struct cdt_entry_u *)cde): ISADDRREAL32((struct cdt_entry_vr *)cde))
#endif

#ifdef __64BIT__
#define	VALID_DMP_MAGIC(n) (((n) == DMP_MAGIC) || ((n) == DMP_MAGIC_U))
#else /* !__64BIT__ */
#define	VALID_DMP_MAGIC(n) (((n) == DMP_MAGIC) ||\
			    ((n) == DMP_MAGIC_U) ||\
			    ((n) == DMP_MAGIC_VR))
#endif /* __64BIT__ */

#define	VALID_CDT_MAGIC(cp) VALID_DMP_MAGIC((cp)->cdt_magic)
#define	VALID_CDT_MAGIC_32_64(cp) VALID_DMP_MAGIC_32_64((cp)->cdt_magic)

#define	ISDMPVR(cp) ((cp)->cdt_magic ==	DMP_MAGIC_VR)

/* See if it's a 32 or 64 bit dump. */
#define ISDMP32(cp) (ISDMPU32(cp) || ISDMPVR(cp) || \
	((cp)_cdt_magic == DMP_MAGIC_32))
#define ISDMP64(cp) (ISDMPU64(cp) || ((cp)->cdt_magic == DMP_MAGIC_64))

/* cdt_entry size for this table */
#define	CDT_ENTRY_SIZE(cp) (ISDMPVR(cp)	? sizeof(struct	cdt_entry_vr) :\
		(ISDMPU(cp)? sizeof(struct cdt_entry_u): \
			sizeof(struct cdt_entry)))

#define	NUM_ENTRIES_OLD(cp)	\
	(((cp)->cdt_len	- sizeof(struct	cdt_head)) /\
	CDT_ENTRY_SIZE(cp) )

/*
 * Get the number of entries regardless	of the table type.
 * Note	that for the unlimited dump table this value will not be valid
 * if the data has just	been read, since the cdtu_nentries is 0	in the dump.
 */
#define	NUM_ENTRIES(cp)	\
	(ISDMPU(cp)? ((struct cdt_head_u *)(cp))->cdtu_nentries: \
	  NUM_ENTRIES_OLD((struct cdt *)(cp)))

/*
 * Copy	data from an old format, cdt_entry, to the new cdt_entry_vr
 * structure.  Since there's not much data to move, we use this
 * method rather than using bcopy().
 *
 * This	is only	valid for a cdt_entry32.
 *
 * Input:
 *   oldp = pointer to a struct	cdt_entry32.
 *   newp = pointer to a struct	cdt_entry_vr.
 */
#define	CDT_OLD2NEW(oldp, newp)	{\
		int *iold = (int *)(oldp), *inew = (int	*)(newp);\
		/* d_name[0-3] */ *inew++ = *iold++; \
		/* d_name[4-7] */ *inew++ = *iold++; \
		/* d_name[8-11]	*/ *inew++ = 0;	\
		/* d_name[12-15] */ *inew++ = 0; \
		/* d_len */ *inew++ = *iold++; \
		/* set d_addrflags off */ *inew++ = 0; \
		/* d_ptr */ *inew++ = *iold++; \
		/* d_segval */ *inew = *iold;\
	}

/*
 * these definitions are mainly	for formatting the raw dump data
 */

#ifndef	_UW7_
typedef	unsigned char bitmap_t;
#endif

#define	DMP_MAXSEGS32 1
#define	DMP_MAXSEGS64 4*1024*1024	/* Allow for 10**15 bytes. */
#define	DMP_MAXPAGES32 ((size_t)((ulong)((ulong)DMP_MAXSEGS32 *	256 * 1024 * 1024) / PAGESIZE))
#define	DMP_MAXPAGES64 ((size_t)((u_longlong_t)DMP_MAXSEGS64 * (256*1024*1024/PAGESIZE)))

#ifdef __64BIT__
#define	DMP_MAXSEGS DMP_MAXSEGS64
#define	DMP_MAXPAGES DMP_MAXPAGES64
#else
#define	DMP_MAXSEGS DMP_MAXSEGS32
#define	DMP_MAXPAGES DMP_MAXPAGES32
#endif

/* BITS_BM is the number of bits per bitmap.  DMP_BMBITS is the	max number of
 * bits	that can be written to a dump file per write operation (i.e. the
 * chunksize" of the bitmap).  DMP_BMMASK is used on loop indices to change the
 * index to identify the bit within the	current	chunk, rather than the bit
 * within the whole bitmap.
 */
#define	BITS_BM		(8 * sizeof(bitmap_t))	/* must	be a power of 2	*/
#define	DMP_BMBITS	(512 * BITS_BM)		/* must	be a power of 2	*/
#define	DMP_BMMASK	(512 * BITS_BM - 1)	/* so that this	works	*/

#define	ISBITMAP(bm,bit) \
	( bm[(bit)/BITS_BM] &  (1 << ((bit) % BITS_BM))	)

#define	SETBITMAP(bm,bit) \
	( bm[(bit)/BITS_BM] |= (1 << ((bit) % BITS_BM))	)

#define	BTOP32(addr) (((uint)(addr) & 0x0FFFFFFF) / PAGESIZE)
#define	BTOPR(addr) ((u_longlong_t)(addr) / PAGESIZE)
#define	BTOP_VR(f,addr)	((f) ? BTOPR(addr) : BTOP32(addr))
#define	BTOP64(addr) (((u_longlong_t)(addr) & (SEGSIZE-1)) / PAGESIZE)

#ifdef __64BIT__
#define	BTOP(addr) BTOP64(addr)
#else
#define	BTOP(addr) BTOP32(addr)
#endif /* __64BIT__ */

#define	DMPSEG32(x) ((uint)(x) & 0xF0000000)
#define	DMPSEG64(x) ((u_longlong_t)(x) & 0xFFFFFFFFF0000000LL)
#define	DMPLIM32(ptr,len) \
	(uint)( DMPSEG32((ptr)+(len)-1)	== DMPSEG32(ptr) ? \
		((uint)(ptr)+(len)-1) :	0x0FFFFFFF )
#define	DMPLIMR(ptr,len) (u_longlong_t)((u_longlong_t)(ptr)+(len)-1)
#define	DMPLIM_VR(f,addr,len) \
	((f) ? (u_longlong_t)DMPLIMR(addr,len) : \
	  (u_longlong_t)DMPLIM32(addr,len))
#define	DMPLIM64(ptr,len) (u_longlong_t)((u_longlong_t)(ptr)+(len)-1)

#ifdef __64BIT__
#define	DMPSEG(x) DMPSEG64(x)
#define	DMPLIM(ptr,len)	DMPLIM64(ptr,len)
#else /* !__64BIT__ */
#define	DMPSEG(x) DMPSEG32(x)
#define	DMPLIM(ptr,len)	DMPLIM32(ptr,len)
#endif	/* __64BIT__ */

#define	NPAGES32(ptr,len) \
	( (len)	== 0 ? 0 : BTOP32(DMPLIM32(ptr,len)) - BTOP32(ptr) + 1 )
#define	NPAGES_VR(f,ptr,len) \
	( (len)	== 0 ? 0 : \
	  (uint)(BTOP_VR(f,DMPLIM_VR(f,ptr,len)) - \
	    BTOP_VR(f,ptr) + 1)	)
/* NPAGES_CDE32 must be used with a cdt_entry_vr structure
 * which can represent both real and virtual addresses
 */
#define	NPAGES_CDE32(cep) \
	NPAGES_VR(ISADDRREAL(cep), \
		  ADDR_VR32(cep), (cep)->d_len)
/* A 64-bit dump data area can span segments. */
#define	NPAGES64(ptr,len) \
	((len) == 0 ? 0	: \
	  ((u_longlong_t)(((uint)(ptr) & (PAGESIZE-1)) + (len) + PAGESIZE - 1) / PAGESIZE))
#define	NPAGES_CDE64(cep) \
	NPAGES64((cep)->d_ptr, (cep)->d_len)
#define	NPAGES_U(cep) \
	NPAGES64((cep)->du_ptr,	(cep)->du_len)
#ifdef __64BIT__
#define	NPAGES(ptr,len)	NPAGES64(ptr,len)
#define	NPAGES_CDE(cep)	(ISCEU(cep)? NPAGES_U((struct cdt_entry_u *)cep): \
		NPAGES_CDE64((struct cdt_entry *)cep))
#else /* !__64BIT__ */
#define	NPAGES(ptr,len)	NPAGES32(ptr,len)
/* NPAGES_CDE (32-bit) must be used with either a cdt_entry_vr or cdt_entry_u. */
#define	NPAGES_CDE(cep)	(ISCEU(cep)? NPAGES_U((struct cdt_entry_u *)cep): \
		NPAGES_CDE32((struct cdt_entry_vr *)cep))
#endif /* __64BIT__ */

/*
 * # of	pages:	# of bitmap_t elements (bytes)
 *	0		 0
 *	1		 1
 *	8		 1
 *	9		 2
 *	16		 2
 *	17		 3
 */
#define	BITMAPSIZE64(ptr,len) \
	( (NPAGES64(ptr,len) + BITS_BM - 1) / BITS_BM )
#define	BITMAPSIZE_CDE64(cep) \
	BITMAPSIZE64((cep)->d_ptr, (cep)->d_len)
#define	BITMAPSIZE_U(cep) \
	BITMAPSIZE64((cep)->du_ptr, (cep)->du_len)
#define	BITMAPSIZE32(ptr,len) \
	( (NPAGES32(ptr,len) + BITS_BM - 1) / BITS_BM )
#define	BITMAPSIZE_VR(f,ptr,len) \
	( (NPAGES_VR(f,ptr,len)	+ BITS_BM - 1) / BITS_BM )
/* BITMAPSIZE_CDE32 must be used with a cdt_entry_vr */
#define	BITMAPSIZE_CDE32(cep) \
	BITMAPSIZE_VR(ISADDRREAL(cep), \
	ADDR_VR32(cep),	(cep)->d_len)
#ifdef __64BIT__
#define	BITMAPSIZE(ptr,len) BITMAPSIZE64(ptr,len)
#define	BITMAPSIZE_CDE(cep) (ISCEU(cep)? BITMAPSIZE_U((struct cdt_entry_u *)cep): \
		BITMAPSIZE_CDE64((struct cdt_entry *)cep))
#else /* !__64BIT__ */
#define	BITMAPSIZE(ptr,len) BITMAPSIZE32(ptr,len)
/* BITMAPSIZE_CDE (32-bit) must be used with either a cdt_entry_vr or cdt_entry_u. */
#define	BITMAPSIZE_CDE(cep) (ISCEU(cep)? BITMAPSIZE_U((struct cdt_entry_u *)cep): \
		BITMAPSIZE_CDE32((struct cdt_entry_vr *)cep))
#endif /* __64BIT__ */

#define	DMPD_PRIM	1		/* must	be 1 */
#define	DMPD_SEC	2		/* must	be 2 */
#define	DMPD_AUTO	3
#define	DMPD_PRIM_HALT	4
#define	DMPD_SEC_HALT	5

/*
 * Return codes	from the system	dump.
 */
#define	DMPDO_SUCCESS	  0
#define	DMPDO_DISABLED	 -1
#define	DMPDO_PART	 -2
#define	DMPDO_FAIL	 -3
#define	DMPDO_IOERROR	 -4

#ifdef _KERNEL
#include <sys/mstsave.h>

/*
 * These defines stand for the reason that the system
 * is dumping.	It was automatic, a key	sequence was
 * entered, or the reset button	was hit.
 */
#define	AUTO_DUMP	0
#define	KEYSEQ_DUMP 1
#define	RESET_DUMP  2

struct dump_read {
	struct mbuf *dump_bufread;
	int    wait_time;
};

/*
 * Used	by dump	I/O routines to	report status.
 */
struct dumpio_stat {
	unsigned int version;			/* Version of this structure */
	unsigned int status;			/* returned status value */
};
#define	DUMPIO_STAT_V1 1

/* dmp_add and dmp_ dmp_del take a function pointer. */
#ifdef __64BIT_KERNEL
typedef	struct cdt *((*__CDTFUNC)(int, void *));
#else
typedef	struct cdt *((*__CDTFUNC)());
#endif

/* Note: the dmp_add_buffer service allows dump	routines to share
 * a temporary buffer for staging large	quantities of data that	are
 * not directly	"dumpable".  They must specify the size	of buffer
 * they	need via the bufsize parameter.	 These routines	will be
 * invoked with	a pointer to the buffer	that they can use.  Note that
 * these routines must be capable of being called twice	with the "1"
 * parameter, and must be able to copy the data	twice, so that they can
 * be invoked a	second time in case of a dump device failure and a
 * failover to the secondary device.
 *
 * It is now recommended that dmp_ctl()	be used	instead	of dmp_add(),
 * dmp_add_buffer() and	dmp_del().
 */

#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)

extern void dmp_prinit(int dmp_proto, void *proto_info);
extern int dmp_add_buffer(__CDTFUNC func, size_t bufsize);
extern int dmp_add(__CDTFUNC func);
extern int dmp_del(__CDTFUNC func);
#endif

/* Dump Routine failures data. */
struct __rtnf {
	ulong rv;				/* error code. */
	ulong vaddr;			/* address. */
	vmhandle_t handle;		/* handle */
};

/* dmp_ctl invocation. */
typedef	void *((*__CDTFUNCENH)(int op, void *buf));

#define EXNAMESIZE 128

/* Record dump routine failures	here. */
#define	DMPF_MAX 2
#define MSTPRESENT -2
#define NOMST -3
struct dmpf {
	uint id;		/* Number of entries */
	struct dfail {
	    __CDTFUNCENH f;
	    struct __rtnf rtnf;
	    ulong mst_flag;
	    struct  kmstsave mst;
	    char ldname[EXNAMESIZE];
	} dfail[DMPF_MAX];
};

#define dmpfd_rv rtnf.rv
#define dmpfd_vaddr rtnf.vaddr
#define dmpfd_handle rtnf.handle

struct dmpctl_data {
	int dmpc_magic;			/* magic number	*/
	int dmpc_flags;			/* dump	routine	flags. */
	__CDTFUNCENH dmpc_func;
	union {
		u_longlong_t bsize;	/* Global buffer size requested. */
		struct __rtnf rtnf;
	} dmpc_u;
};
#define	DMPC_MAGIC1 0xdcdcdc01
#define	DMPC_MAGIC DMPC_MAGIC1
#define	dmpc_bsize dmpc_u.bsize
#define dmpcf_rv dmpc_u.rtnf.rv
#define dmpcf_vaddr dmpc_u.rtnf.vaddr
#define dmpcf_handle dmpc_u.rtnf.handle

#ifdef _NO_PROTO
extern int dmp_ctl();
#else
extern int dmp_ctl(int op, struct dmpctl_data *parmp);
#endif

/* dmp_ctl operations. */
#define	DMPCTL_ADD 1
#define	DMPCTL_DEL 2
#define DMPCTL_RTNFAILURE 3		/* dump routine failure */
/*
 * dmpc_flag values.
 * The CALL_ON_RESTART value is	set if the routine should be called each time
 * the dump is restarted.  It must be set if the GLOBAL_BUFFER flag is set.
 * It must also	be set if the routine returns an unlimited dump	table.
 * The GLOBAL_BUFFER flag is set if the	routine	uses global buffer space.
 * The dmpc_bsize value	must also be set to the	number of bytes	being
 * requested.  This value may not exceed DMPBUF_MAX.
 */
#define	DMPFUNC_CALL_ON_RESTART	0x1
#define	DMPFUNC_GLOBAL_BUFFER 0x2
/* Operations passed to	dump routines. */
#define	DMPRTN_START 1
#define	DMPRTN_DONE 2
#define	DMPRTN_AGAIN 3
#define	DMPRTN_ESTIMATE	4

/*
 * Dump	size estimate type.
 * A dump routine, added with dmp_ctl(), must return a pointer to
 * dmp_sizeest_t when requested	to provide an estimate.
 */
typedef	unsigned long long dmp_sizeest_t;

/* Dump	device buffer size query structure. */
struct dmp_query {
	size_t min_tsize;
	size_t max_tsize;
};


/* minidump error log entry types */
typedef struct minidump_log{
        struct err_rec0 erec;
        char minidump_buf[ERR_REC_MAX];
};

typedef struct minidump_err_log{
        struct err_rec0 erec;
        int error_code;
};

typedef struct minidump_info_log{
        struct err_rec0 erec;
        int op_code;
};


#ifdef _KERNSYS
extern int dmp_do(int dmptype, int reason);
extern int dmp_do_excp(int dmptype, int reason, int excp_code);
#endif /* _KERNSYS */

#endif /* _KERNEL */

#endif	/* _H_DUMP */
