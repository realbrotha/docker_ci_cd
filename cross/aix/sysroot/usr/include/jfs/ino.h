/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/jfs/ino.h 1.6.1.26                          */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,2002          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)44     1.6.1.26  src/bos/usr/include/jfs/ino.h, syspfs, bos530 5/2/02 18:15:25 */
/*
 * COMPONENT_NAME: (SYSPFS) Physical File System 
 *
 * FUNCTIONS: ino.h
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1996
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef	_H_JFS_INO
#define	_H_JFS_INO

#include <sys/types.h>
#include <sys/time.h>
#include <jfs/fsdefs.h>
#include <jfs/filsys.h>
#include <jfs/jfsmount.h>
#include <sys/priv.h>
#include <sys/acl.h>
#include <sys/lock_def.h>

#ifdef __cplusplus
struct inode;
#endif /* __cplusplus */

/* double indirect block has (PAGESIZE/8) entries of form idblock
 */
struct idblock
{
	uint  id_vaddr;  /* page number in .indirect */
	uint  id_raddr;  /* disk block address in volume */
};

struct dinode
{
	/* generation number */
	uint	di_gen;

	/* the mode_t returned by stat() */
	/* format, attributes and permission bits */
	mode_t	di_mode;

	/* number of links to file (if 0, inode is available) */
	ushort	di_nlink;

	/* persistent event list for managed file system */
	ushort	di_pel;
	/* obsolete name */
#define di_acct	di_pel

	/* user id of owner */
	uid_t	di_uid;

	/* group id of owner */
	gid_t	di_gid;

	/* size of file */
	soff_t	di_size_lo;
#define di_size di_size_lo

	/* number of blocks actually used by file */
	uint	di_nblocks;

	/* time last modified */
#ifndef __64BIT_KERNEL
	struct timestruc_t    di_mtime_ts;
#else
	struct timestruc32_t  di_mtime_ts;
#endif

	/* time last accessed */
#ifndef __64BIT_KERNEL
	struct timestruc_t    di_atime_ts;
#else
	struct timestruc32_t  di_atime_ts;
#endif

	/* time last changed inode */
#ifndef __64BIT_KERNEL
	struct timestruc_t    di_ctime_ts;
#else
	struct timestruc32_t  di_ctime_ts;
#endif

	/* defines for old time_t names */
#define	di_mtime	di_mtime_ts.tv_sec
#define	di_atime	di_atime_ts.tv_sec
#define	di_ctime	di_ctime_ts.tv_sec

	/* extended access control information */
	int	di_acl;		/* acl pointer */

	/* extended attributes */
	uint	di_attr;
	/* obsolete name */
#define di_sec	di_attr

	/* spares */
	uint	di_rsrvd[4];
	soff_t	di_size_hi;	/* most significant word of isize */

	/***** file type-dependent information *****/
	/*
	 * size of private data in disk inode is D_PRIVATE.
	 * location and size of fields depend on object type.
	 */
#	define	D_PRIVATE	48

	union	di_info
	{
		/* all types must fit within d_private */
		char	d_private[D_PRIVATE];

		/* regular file or directory. */
		struct regdir
		{
			/* disk pointers. NDADDR must <= 8 to fit */
			uint	_di_rdaddr[NDADDR]; /* disk addrs */
			struct idblock _di_indblk;

			union
			{
				/* privilege vector - only for non-directory */
				struct
				{
					uint	_di_offset;
					uint	_di_flags;
#					define	PCL_ENABLED    (1<<31)
#					define	PCL_EXTENDED   (1<<30)
#					define	PCL_FLAGS \
						(PCL_ENABLED|PCL_EXTENDED)
				} _di_privinfo;
				priv_t	_di_priv;
				/* ACL templates - only for directory */
				struct
				{
					uint	_di_aclf;
					uint	_di_acld;
				} _di_aclinfo;
			} _di_sec;
		} _di_file;
/* offsets of regular file or directory private data. */
#	define	di_rdaddr	_di_info._di_file._di_rdaddr
#       define  di_vindirect    _di_info._di_file._di_indblk.id_vaddr
#       define  di_rindirect    _di_info._di_file._di_indblk.id_raddr
#	define	di_privinfo	_di_info._di_file._di_sec._di_privinfo
#	define	di_privoffset	di_privinfo._di_offset
#	define	di_privflags	di_privinfo._di_flags
#	define	di_priv		_di_info._di_file._di_sec._di_priv
#	define	di_aclf		_di_info._di_file._di_sec._di_aclinfo._di_aclf
#	define	di_acld		_di_info._di_file._di_sec._di_aclinfo._di_acld

		/* special file (device) */
		struct
		{
			dev32_t	_di_rdev;	/* device major and minor */
		} _di_dev;
/* offsets of special file private data */
#	define	di_rdev		_di_info._di_dev._di_rdev

		/*
		 * symbolic link. link is stored in inode if its
		 * length is less than D_PRIVATE. Otherwise like
		 * a regular file.
		 */
		union
		{
			char	_s_private[D_PRIVATE];
			struct	regdir	_s_symfile;
		} _di_sym;
/* offset of symbolic link private data */
#	define	di_symlink	_di_info._di_sym._s_private

	} _di_info;
};

/*
 * data for mounted filesystem. kept in inode = 0
 * and dev = devt of mounted filesystem in inode table.
 */

struct  jfsmntinfo
{
	uint	_diodone;
	uint	_diofail;
	uint	_mntflag;
	uint	_sbinfo;	/* s_info flag bits from filsys.h */
	time32_t _mount_ts;
	time32_t _dirty_ts;
};

struct mountnode
{
	struct	inode	*_iplog;	/* itab of log */
	struct	inode	*_ipinode;	/* itab of .inodes */
	struct	inode	*_ipind;	/* itab of .indirect */
	struct	inode	*_ipinomap;	/* itab of inode map */
	struct	inode	*_ipdmap;	/* itab of disk map */
	struct	inode	*_ipsuper;	/* itab of super blk */
	struct	inode	*_ipinodex;	/* itab of .inodex */
	struct  jfsmount *_jmpmnt;	/* quota stuff */
	struct  jfsinfo _jfs_info;	/* from fsdefs.h */
	struct	jfsmntinfo *_jfsmnt;
	pdtx_t	_pdtx;			/* for jfspdtdata */
	int	*_indfree;		/* indirect block free counts */
	void	*_kdm_fset;		/* for managed file system */
};
/* offsets of MOUNT data */
#	define	di_iplog	_iplog
#	define	di_ipinode	_ipinode
#	define	di_ipind	_ipind
#	define	di_ipinomap	_ipinomap
#	define	di_ipdmap	_ipdmap
#	define	di_ipsuper	_ipsuper
#	define	di_ipinodex	_ipinodex
#	define	di_jmpmnt	_jmpmnt
#	define	di_agsize	_jfs_info.agsize
#	define	di_iagsize	_jfs_info.iagsize
#       define  di_logsidx      _jfs_info.logsidx
#       define  di_fperpage	_jfs_info.jv_fperpage
#       define  di_fsbigexp	_jfs_info.jv_bigexp
#       define  di_fscompress	_jfs_info.jv_comptype
#	define	di_jfsmnt	_jfsmnt
#	define	di_diodone	_jfsmnt->_diodone
#	define	di_diofail	_jfsmnt->_diofail
#	define	di_mntflag	_jfsmnt->_mntflag
#	define  di_sbinfo	_jfsmnt->_sbinfo
#	define	di_mount_ts	_jfsmnt->_mount_ts
#	define	di_dirty_ts	_jfsmnt->_dirty_ts
#	define	di_pdtx		_pdtx
#	define	di_kdmfset	_kdm_fset
#	define	di_indfree	_indfree
		
/*
 * log info. kept in inode = 0 and dev = devt of
 * log device filesystem in inode table.
 */
struct lognode
{
	int	_logptr;	/* page number end of log     */
	int	_logsize;	/* log size in pages	      */
	int	_logend;	/* eor in page _logptr	      */
	int	_logsync;	/* addr in syncpt record      */
	int	_nextsync;	/* bytes to next logsyncpt    */
	int	_logxor;	/* cumulative checksum for    */
				/*   all log data in the page */
	int	_llogeor;	/* end of record for last log */
				/*   record in the page	      */
	int	_llogxor;	/* checksum up to and includ- */
				/*   ing last log record      */
	struct ilogx *_logx;	/* log inode extension	      */
	struct gnode *_logdgp;	/* pointer to device gnode    */
	Simple_lock   _loglock;	/* lock word for log	      */
	pdtx_t	_logpdtx;	/* pdt index for log device   */
	uint	_logwaitcount;	/* times syncwait for this log*/
	uint	_logwaittime;	/* time of first syncwait     */
	Simple_lock	_lilistlock; /* lock for journalized inodes list  */
	struct inode	*_lforw;     /* journalized inodes list chain forw */
};
/* offsets of LOG data */
#	define di_logptr	_logptr
#	define di_logsize	_logsize
#	define di_logend	_logend
#	define di_logsync	_logsync
#	define di_nextsync	_nextsync
#	define di_logdgp	_logdgp
#	define di_loglock	_loglock
#	define di_logxor	_logxor	
#	define di_llogeor	_llogeor
#	define di_llogxor	_llogxor
#	define di_logx		_logx
#	define di_logpdtx	_logpdtx
#	define di_logwaitcount	_logwaitcount
#	define di_logwaittime	_logwaittime
#	define di_logilistlock	_lilistlock
#	define di_logilistanchor	_lforw


/* layout of a .indirect segment for 4k pagesize. the indirect
 * blocks of .indirect are in root and indptr. the number of pages
 * in the two is FIRSTIND so FIRSTIND is the first page in .indirect
 * that can be allocated for other uses. the free list of pages
 * is initialized to consist of the pages from FIRSTIND to the last
 * one covered by the first indirect block, i.e. PAGESIZE/4 - 1.
 * the variable free points to the index of a free page and the 
 * free pages are chained thru the corresponding indptr (when 
 * a page is not on the free list indptr contains the disk address)
 * more is the the index of the next page of free indptrs. when
 * the free - list is exhausted the page of indptrs pointed to
 * by more is added to the list.
 */ 

/* while a file is open the pointers to disk blocks in .indirect may
 * have the format of a VMM external page table entry : besides 
 * containing a disk block number, the leftmost bits of the word 
 * may be used for flags. however these flag bits never appear on the 
 * permanent disk copy of an indirect block.
 */


#ifdef _KERNEL
#define	 FIRSTIND	65
struct indir {

	struct	idblock root[64];		/* double indirect */
	int	free;				/* index of first free page */
	int	cnt;				/* used for compare/swap */
	int	more;				/* index more free pages */
	int	freebacked;			/* free page disk backed */
	int	pad[1024 - 2*64 - 4];		/* pad to page boundary */
	uint	indptr[SEGSIZE/PAGESIZE];	/* single indirect */  
	union { 
		struct idblock root[PAGESIZE/8]; /* double indirects */
		uint	ptr[PAGESIZE/4];	 /* single indirects */
	} page[SEGSIZE/PAGESIZE - FIRSTIND];	 /* pages to end segment */
};

/* masks for treating disk address fields in disk inodes and
 * indirect blocks as VMM external page table entries.
 */
#define NEWBIT	0x80000000
#define CDADDR	0x0fffffff

/* macros for determining type of indirect blocks required to cover size
 */
#define NOIND(size)	( ((size) <= NDADDR*PAGESIZE ) ? 1 : 0 )
#define SGLIND(size)	( ((size) <= (PAGESIZE/4)*PAGESIZE) ? 1 : 0 )
#define DBLIND(size)	( ((size) >  (PAGESIZE/4)*PAGESIZE) ? 1 : 0 )

#define DABLK		1024
#define L2DABLK		10
#define SGLOFF(pno, bigexp) ( ((pno) - DABLK >> (bigexp)) & DABLK - 1 )
#define DBLOFF(pno, bigexp) ( ((pno) - DABLK >> (bigexp) + L2DABLK) + 1 )

#define PGTOXPT(pno, exp) ( (pno) < DABLK ? (pno) :			\
			    (((pno) - DABLK >> (exp)) + DABLK) )

/* convert size in bytes and fragment per page to number of fragments
 * in last block of a file.
 */
#define BTOFR(b,f)	(((b) > NDADDR * PAGESIZE) ? (f) : \
	((((int)(b) - 1) & (PAGESIZE - 1)) + (PAGESIZE/(f))) / (PAGESIZE/(f)))

#endif /* _KERNEL */

#endif	/* _H_JFS_INO */
