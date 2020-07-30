/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53A src/bos/usr/include/jfs/inode.h 1.8.1.42                        */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,2004          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)45	1.8.1.42  src/bos/usr/include/jfs/inode.h, syspfs, bos53A, a2004_41B1 9/27/04 11:30:53 */
/*
 * COMPONENT_NAME: (SYSPFS) Physical File System 
 */

#ifndef _H_JFS_INODE
#define _H_JFS_INODE

#include <sys/types.h>
#include <sys/param.h>
#include <jfs/ino.h>
#include <sys/vnode.h>          
#include <sys/mode.h>
#include <jfs/quota.h>

struct	inode
{
	struct inode	*i_forw;	/* hash chain forw */
	struct inode	*i_back;	/* hash chain back */
	struct inode	*i_next;        /* next on cached list */
	struct inode	*i_prev;        /* previous on cached list */
	struct gnode	i_gnode;	/* generic node information */
	ino32_t		i_number;       /* disk inode number */
	dev_t		i_dev;          /* device on which inode resides */
	struct inode	*i_ipmnt;	/* inode of mount table entry */
	short		i_flag;		/* inode transition/modification */
	short		i_locks;	/* lock allocation flag */
	char		i_bigexp;	/* log2 big alloc multiplier */
	char		i_compress;	/* data compression */
	short		i_cflag;        /* commit flags */
	int		i_count;	/* reference count */
	unsigned int	i_syncsn;	/* serial number from last sync */
	struct movedfrag *i_movedfrag;	/* ptr to list of movedfrags */
	tid_t		i_openevent;	/* event list for nshare open modes */
	int		i_id;		/* capability ID of this inode */
	struct hinode	*i_hip;		/* hash list the inode resides on */
	Simple_lock	i_nodelock;	/* afs toy lock */
	struct dquot	*i_dquot[MAXQUOTAS]; /* disk quota structures */
	union {
		struct dinode	 _i_dinode;
		struct mountnode _i_mountnode;
		struct lognode	 _i_lognode;
	} i_node;
	int		i_cluster;	/* last write cluster for wrbehind */
	offset_t	i_size;		/* file size (previously di_size) */
	int		i_rcluster;	/* last read cluster */
	int		i_diocnt;	/* number of dio openers */
	int		i_nondio;	/* number of non-dio openers */	
	int		i_gets;		/* num threads iget()ing inode */
	vmid_t		i_indsid;	/* SID of .indirect */
	uint		i_indidx;	/* segment index into .indirect */
	struct acl	*i_aclp;	/* incore acl kept here */
	Complex_lock	i_rwlock;	/* data lock / icache mgt lock	*/
	Simple_lock	i_simplelock;	/* exclusive inode lock */
	void		*i_kdmvp;	/* kdmvnode for managed fs */
	uint		i_change;	/* modification indicator */
	struct inode	*i_logforw;	/* inodes list chain forw */
	struct inode	*i_logback;	/* inodes list chain back */
	int		i_did;		/* directory change id */
};

/* iunhash flags */
#define IC_IPKEEP	0x0001	/* keep the inode in the cache */
#define IC_IPFREE	0x0002  /* return the inode to the free list */

/* i_locks */
#define	IQUOTING   0x0004	/* binding to a quota */

/* i_flag */
#define	IACC	0x0008		/* inode access time to be updated */
#define	ICHG	0x0010		/* inode has been changed */
#define	IUPD	0x0020		/* file has been modified */
#define	IFSYNC	0x0040		/* commit changes to data as well as inode */
#define IDIRECT 0x0080		/* file opened for direct io		*/
#define IDEFER  0x0100		/* defered update */
#define IRIP    0x0200		/* read in progress */
#define IRED	0x0400		/* read inode from disk (not in inocache) */

/* additional flags passed to imark, but not put in the inode */
#define ITMPMASK 0xFFFF0000
#define INOEV	 0x40000000	/* no event generation on managed fs */
#define IINVIS	 0x80000000	/* invisible operation, don't set times */

/* i_cflag */
#define DIRTY		0x0001    /* dirty journalled file */
#define CMNEW		0x0002    /* never committed inode   */
#define CMNOLINK	0x0004    /* inode committed with zero link count */
#define CMDIRTY		0x0008    /* inode commited but may have dirty pages */
#define IACTIVITY	0x0010	  /* inode in a file system being unmounted */

/* extended mode bits (i_mode), high order short. */
#define IFJOURNAL 	0x10000		/* journalled file */


#define	i_seg        i_gnode.gn_seg 

#define i_dinode     i_node._i_dinode
#define	i_gen        i_dinode.di_gen
#define i_nlink      i_dinode.di_nlink
#define i_pel        i_dinode.di_pel
#define i_mode       i_dinode.di_mode
#define i_uid        i_dinode.di_uid
#define i_gid        i_dinode.di_gid
#define i_disize_lo  i_dinode.di_size_lo
#define i_disize_hi  i_dinode.di_size_hi
#define i_nblocks    i_dinode.di_nblocks
#define i_mtime      i_dinode.di_mtime
#define i_mtime_ts   i_dinode.di_mtime_ts
#define i_atime      i_dinode.di_atime
#define i_atime_ts   i_dinode.di_atime_ts
#define i_ctime      i_dinode.di_ctime
#define i_ctime_ts   i_dinode.di_ctime_ts
#define i_nacl       i_dinode.di_nacl
#define i_nsec       i_dinode.di_nsec
#define i_acl        i_dinode.di_acl
#define i_attr       i_dinode.di_attr
#define i_security   i_dinode.di_security
#define i_seclab     i_dinode.di_seclab
#define i_priv       i_dinode.di_priv
#define i_pflags     i_dinode.di_pflags
#define i_privoffset i_dinode.di_privoffset
#define i_privflags  i_dinode.di_privflags
#define i_rdaddr     i_dinode.di_rdaddr
#define i_rindirect  i_dinode.di_rindirect
#define i_vindirect  i_dinode.di_vindirect
#define i_rdev       i_dinode.di_rdev
#define i_max        i_dinode.di_max
#define i_min	     i_dinode.di_min
#define ibn_lastr    i_dinode.di_bnlastr	
#define i_pino	     i_dinode.di_pino
#define i_dgp	     i_dinode.di_dgp
#define i_symlink    i_dinode.di_symlink
#define i_symdaddr   i_dinode.di_symaddr

#define i_lognode    i_node._i_lognode
#define i_logptr     i_lognode.di_logptr
#define i_logsize    i_lognode.di_logsize
#define i_logend     i_lognode.di_logend
#define i_logsync    i_lognode.di_logsync
#define i_nextsync   i_lognode.di_nextsync
#define i_logxor     i_lognode.di_logxor
#define i_llogeor    i_lognode.di_llogeor
#define i_llogxor    i_lognode.di_llogxor
#define i_logx	     i_lognode.di_logx
#define i_loglock    i_lognode.di_loglock
#define i_logdgp     i_lognode.di_logdgp
#define i_logpdtx	i_lognode.di_logpdtx
#define i_logwaitcount	i_lognode.di_logwaitcount
#define i_logwaittime	i_lognode.di_logwaittime
#define	i_logilistlock	i_lognode.di_logilistlock
#define	i_logilistanch	i_lognode.di_logilistanchor

#define i_mountnode  i_node._i_mountnode
#define i_iplog      i_mountnode.di_iplog
#define i_ipind      i_mountnode.di_ipind
#define i_ipinode    i_mountnode.di_ipinode
#define i_ipinomap   i_mountnode.di_ipinomap
#define i_ipdmap     i_mountnode.di_ipdmap
#define i_ipsuper    i_mountnode.di_ipsuper
#define	i_ipinodex   i_mountnode.di_ipinodex
#define	i_jmpmnt     i_mountnode.di_jmpmnt
#define	i_agsize     i_mountnode.di_agsize
#define	i_iagsize    i_mountnode.di_iagsize
#define i_logsidx    i_mountnode.di_logsidx
#define	i_fperpage   i_mountnode.di_fperpage
#define	i_fsbigexp   i_mountnode.di_fsbigexp
#define	i_fscompress i_mountnode.di_fscompress
#define i_jfsmnt     i_mountnode.di_jfsmnt
#define i_diodone    i_mountnode.di_diodone
#define i_diofail    i_mountnode.di_diofail
#define i_mntflag    i_mountnode.di_mntflag
#define i_sbinfo     i_mountnode.di_sbinfo
#define i_mount_ts   i_mountnode.di_mount_ts
#define i_dirty_ts   i_mountnode.di_dirty_ts
#define i_pdtx	     i_mountnode.di_pdtx
#define i_indfree    i_mountnode.di_indfree
#define i_kdmfset    i_mountnode.di_kdmfset


/* Some useful macros
 */
#define GTOIP(x)	((struct inode *)(((struct gnode *)(x))->gn_data))
#define VTOIP(x)	(GTOIP(VTOGP(x)))
#define ITOGP(x)	((struct gnode *)(&(((struct inode *)(x))->i_gnode)))
#define VTOGFS(x)	(((struct vnode *)(x))->v_vfsp->vfs_gfs)
#define ISVDEV(t) (((t) == VBLK) || ((t) == VCHR)  \
			|| ((t) == VFIFO) || ((t) == VMPC))

#define ISBIGF(ip)    ((ip)->i_bigexp)

/* hash anchors for inode table
 */
struct hinode
{
	struct	inode	*hi_forw;
	struct	inode 	*hi_back;
	int32long64_t	hi_timestamp;
	Simple_lock	hi_lock;
};

/*      inode lru cache list
 *
 * offsets of ic_next and ic_prev must be same as in the inode
 */
struct icachelist {
        union
	{
		void	*_x1;
		int	_x2;
	}		ic_freecnt_un;  /* # of inodes on the cache list */
        union
	{
		void	*_x1;
		int	_x2;
	}		ic_minfree_un;  /* minimum number of cached inodes */
        struct inode    *ic_next;       /* next cached entry */
        struct inode    *ic_prev;       /* previous cached entry */
	int		ic_gets;	/* number of references to list */
	int		ic_activates;	/* inode on cache list reused */
	int		ic_inodes;	/* inodes on list */
        Simple_lock     ic_lock;        /* cache list lock */
};

#define ic_freecnt	ic_freecnt_un._x2
#define ic_minfree	ic_minfree_un._x2

extern int nhino;
extern struct hinode *hinode;
extern struct icachelist *cinode;

#define IHASH(ino,dev,hip) 			  \
{						  \
        uint hash; 				  \
        hash = (uint)(ino) ^ (uint)(dev); 	  \
        hash = (hash >> 8) + (hash >> 12) + hash; \
        (hip) = &hinode[hash & (uint)(nhino-1)];  \
}


/* number of indrect segments */
#define NUM_INDSEG 8

/* starting value for indirect block free count */
#define IND_FREECOUNT_INIT ((SEGSIZE >> L2PSIZE) - 64)

/* address of  counter for .indirect segment n of inode p */
#define IND_COUNT(_ip,_n) ((_ip)->i_ipmnt->i_indfree + (_n))

/* access to indirect block counters */
#define IND_FREECOUNT(_ip,_ind) (*IND_COUNT((_ip),(_ind)))

/* adjust indirect block count when using a block */
#define IND_COUNT_USED(_ip) \
         (void)fetch_and_add(IND_COUNT((_ip),(_ip)->i_indidx), -1)

/* adjust indirect block count when freeing a block */
#define IND_COUNT_FREE(_ip) \
         (void)fetch_and_add(IND_COUNT((_ip),(_ip)->i_indidx), 1)


#endif /* _H_JFS_INODE */
