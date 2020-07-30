/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/j2/include/j2_quota.h 1.14                       */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 2003,2007              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)00     1.14  src/bos/kernel/j2/include/j2_quota.h, sysj2, bos53X, x2009_34A1 6/25/07 20:52:42 */

#ifndef _H_J2_QUOTA
#define _H_J2_QUOTA

#include <sys/types.h>
#include <j2/j2_types.h>
#include <sys/fs/quota_common.h>

/* On-disk Limits record: Each record can have its own grace period
 * time limits set. Note that the 32-bit time value limits the maximum
 * grace period to about 68 years.
 */
#define J2QL_REFERENCED	(0x0001)	/* referenced by a usage record	*/
#define J2QL_CHAINED	(0x0002)	/* to avoid loops in free list	*/
#define J2QL_DELETED	(0x8000)	/* record has been deleted	*/
typedef struct {
	uint64    ql_bhard;	/* absolute limit on 512-byte dblks	*/
	uint64    ql_bsoft;	/* preferred limit on 512-byte dblks	*/
	uint64    ql_ihard;	/* maximum # allocated inodes		*/
	uint64    ql_isoft;	/* preferred inode limit		*/
	time32_t  ql_btime;	/* time limit for excessive disk use	*/
	time32_t  ql_itime;	/* time limit for excessive files	*/
	uint16    ql_flags;	/* control flags			*/
	uint16    ql_index;	/* index number for verification	*/
	uchar     pad[20];
} j2qlimit_t;	                /* 44 bytes, padded to 64 bytes		*/


/* On-disk Usage record: Note that using a 32-bit time value to store
 * the end of grace periods introduces an issue around the year 2038,
 * but the advantages of a 32-byte structure size far outweighs the
 * minor difficulty of coding special cases for the grace period
 * lengths of time on either side of the end of the epoch. There will
 * be no special processing in the initial release, under the
 * assumption that there will be additional releases better able to
 * address this issue sometime in the next 35 years.
 */
#define J2QU_REFERENCED	(0x0001)	/* has usage or defined limit	*/
#define J2QU_WARNB      (0x0010)	/* warned about block hard lim	*/
#define J2QU_WARNI      (0x0020)	/* warned about inode hard lim	*/
#define J2QU_NOID       (0x4000)	/* UID/GID undefined in system	*/
#define J2QU_DELETED    (0x8000)	/* record has been deleted	*/
#define J2QU_ALLFLAGS	(J2QU_REFERENCED | J2QU_WARNB | J2QU_WARNI \
				| J2QU_NOID | J2QU_DELETED)
typedef uint32 qid_t;
typedef struct {
	int64     qu_bused;	/* current 512-byte block count		*/
	int64     qu_iused;	/* current # allocated inodes		*/
	time32_t  qu_btime;	/* deadline for excessive disk use	*/
	time32_t  qu_itime;	/* deadline for excessive files		*/
	uint16    qu_lindex;	/* limits record index			*/
	uint16    qu_flags;	/* control flags			*/
	qid_t     qu_qid;	/* UID or GID, depending...		*/
} j2qusage_t;	                /* 32 bytes				*/
/* deal with 512 block sizes when we store and report everything by 1K  */
#define J2QL2BSIZE	9


/* Due to the maximum size of the quotas files, page numbers are
 * easily contained in 28 bits; the remaining four bits are used for
 * condition flags.
 */
typedef struct {
	unsigned refd   :1;	/* quotacheck has referenced this page	*/
	unsigned avail  :1;	/* page contains inactive record(s)	*/
	unsigned        :2;
	unsigned pageno :28;
} j2qpno_t;


/* Quotas file Usage pages: Each quota usage data page is a portion of
 * the array of usage structures indexed by UID, and contains 2^7
 * structures. Each metadata page is an array of 2^10 page numbers of
 * the next level down in the triple-indirect hierarchy.
 */
#define J2L2U		(7)
#define J2UPERPAGE	(1<<J2L2U) /* 128 usage records per page	  */
typedef struct {
	j2qusage_t qu_page[J2UPERPAGE];
} j2qupage_t; 

#define J2L2UI		(10)
#define J2UPNOPERPAGE	(1<<J2L2UI) /* 1K page numbers per usage metapage */
typedef struct {
	j2qpno_t   qu_upno[J2UPNOPERPAGE];
} j2quindex_t; 


/* Quotas file Limits pages: Only used if the number of Limits records
 * overflows the control page. Each quota limits data page is a
 * portion of an array of limits structures indexed by a unique record
 * number, and contains 2^6 structures.
 */
#define J2L2L		(6)
#define J2LPERPAGE 	(1<<J2L2L)	/* 64 limits records per page */
typedef struct {
	j2qlimit_t ql_page[J2LPERPAGE];
} j2qlpage_t; 


/* Free pages: Allocated but "undefined" pages within the file
 * (i.e. They haven't yet been assigned to be a Usage page, Limits page,
 * or Index page) need to be tagged as such; this makes it easier...
 */
#define J2QF_FREE	(0x46524545)	/* "FREE" */
typedef struct {
	uint32	  qf_tag;
	uint32	  qf_fnext;
	time32_t  qf_stamp;
} j2qfpage_t;


/* File control page: Finally, page 0 contains the top level Usage
 * index array (2^5 page numbers) plus additional metadata.
 */

/* file grow size; each time file needs expanding, add this many pages */
#define J2QZ_GROWSIZE	(8)

#define J2QZ_MAGIC   	(0x6A3271756F746173LL)	/* "j2quotas" */

/* version numbers, both historical and current */
#define J2QZ_V1		(0x0001)
#define J2QZ_VERSION	(J2QZ_V1)

/* j2qzh_flags values */
#define J2QZ_REBUILD 	(0x0001)  /* quota file MUST be rebuilt		*/
#define J2QZ_RECHECK 	(0x0002)  /* quota file SHOULD be rebuilt	*/

typedef struct {
	uint64	  qzh_magic;	/* "j2quotas"				*/
	uint16    qzh_vers;	/* allows for on-disk format changes	*/
	uint16	  qzh_flags;	/* control flags			*/
	uint32	  qzh_flist;	/* head of chained unused pages		*/
	uint16	  qzh_lnext;	/* next Limits index number assigned	*/
	uint16	  qzh_lfree;	/* head of chained unused limits recds	*/
	uint32	  qzh_reserved[11];
} j2qzhead_t; 

#define J2L2UZ		(5)
#define J2UPNOPERQZPAGE (1<<J2L2UZ)  /* 32 usage metapage numbers on page 0 */
#define J2L2LZ		(6)
#define J2LPNOPERQZPAGE (1<<J2L2LZ)  /* 64 limits page numbers on page 0    */
#define J2QZPAGEACOUNT  (J2UPNOPERQZPAGE+J2LPNOPERQZPAGE)
#define J2QZPAGEPAD (2048-sizeof(j2qzhead_t)-(J2QZPAGEACOUNT*sizeof(j2qpno_t)))
#define J2LPERQZPAGE    (2048/sizeof(j2qlimit_t)) /* 2048 bytes of limits */
typedef struct {
	j2qzhead_t  qz_head;
	j2qpno_t    qz_upno[J2UPNOPERQZPAGE];	/* Usage index pno array */
	j2qpno_t    qz_lpno[J2LPNOPERQZPAGE];	/* Limits pno array	 */
	uchar       pad[J2QZPAGEPAD];
	j2qlimit_t  qz_limits[J2LPERQZPAGE];
} j2qzpage_t; 

#define qz_magic    qz_head.qzh_magic
#define qz_vers     qz_head.qzh_vers
#define qz_flags    qz_head.qzh_flags
#define qz_flist    qz_head.qzh_flist
#define qz_lnext    qz_head.qzh_lnext
#define qz_lfree    qz_head.qzh_lfree


typedef char j2qcflags_t;	/* flags for quota control structures	*/
#define J2QC_ACTIVE	0x01	/* accumulate quota stats for this type	*/
#define J2QC_ENFORCE	0x02	/* enforce quota limits for this type	*/

/* Macros: Miscellaneous stuff */
#define J2QUOTASON(__ip)   ((__ip->i_ipmnt->i_qctl) ? TRUE : FALSE)

/* Flags for qAlloc() */
#define J2QMDATA	(0x00000001)	/* allocating space for metadata  */
#define J2QIGNOREU	(0x80000000)	/* ignore user when check/alloc   */
#define J2QIGNOREG	(0x40000000)	/* ignore group when check/alloc  */
#define J2QCHOWNLOCKED	(0x20000000)	/* locks already held via chown   */

/* Flags for qChownLocks() */
#define J2QCLOCK	TRUE
#define J2QCUNLOCK	FALSE

/* j2_quota.c */
int	j2_quotactl(struct vfs *, int, qid_t, caddr_t, struct ucred *);
int	j2_qInit(void);
int	qAlloc(struct inode *, int64, int, uint, struct ucred *);
void	qFree(struct inode *, int64, int, uint);
int	qChown(struct inode *, long, uid_t, gid_t, struct ucred *);
void	qChownHold(struct inode *, long, uid_t, gid_t);
void	qChownRele(struct inode *, int, long, uid_t, gid_t);
int	qHold(struct inode *);
int	qRele(struct inode *);
int	qMount(struct inode *, struct vfs *, struct ucred *);
int	qUnmount(struct inode *);
void	qSync(struct inode *);
boolean_t qIsQuotaFile(struct inode *);

/* Quota file names, cannot be changed by user */
#define UFNAME "/quota.user"
#define GFNAME "/quota.group"

/* Flags to use a crfs/chfs time... can't use what's in quota_common.h
 * because the user quota type there is defined as 0 so there is no
 * way to tell the difference between the "nothing" 0 and the "user" 0.
 */
#define CRQATTR		0x01
#define CRQUSER		0x02
#define CRQGROUP	0x04


#endif /* _H_J2_QUOTA */
