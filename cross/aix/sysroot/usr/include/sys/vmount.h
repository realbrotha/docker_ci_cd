/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/kernel/sys/vmount.h 1.49.1.1                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,2008          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)95	1.49.1.1  src/bos/kernel/sys/vmount.h, syslfs, bos53Q, q2008_03B2 1/4/08 16:27:54  */

#ifndef _H_VMOUNT
#define _H_VMOUNT

/*
 * COMPONENT_NAME: SYSLFS - Logical File System
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27
 *
 */

/*
 * Types of file systems for the vmount system call
 *	NOTE -  When implementing new file system types, ensure
 *              that the vfs numbers do not conflict.
 *
 *  NFS NOTE -  When adding a new version of NFS, checking for the new
 *              NFS type is needed to the following functions/files:
 *                   openpnp / open.c
 *                   insflck and common_reclock / lockctl.c
 *                   jfs_do_cr / lsfs.c
 *              In addition, kdb should be aware of the new type.
 */


#define	MNT_AIX		0	/* Same as MNT_J2		  */
#define	MNT_J2		0	/* AIX physical fs "jfs2"	  */
#define	MNT_NAMEFS	1	/* AIX pseudo fs "namefs"	  */
#define	MNT_NFS		2	/* SUN Network File System "nfs"  */
#define	MNT_JFS		3	/* AIX R3 physical fs "jfs"	  */
#define MNT_CDROM	5	/* CDROM File System "cdrom"	  */
#define MNT_PROCFS	6	/* PROCFS File System "proc"	  */

#define MNT_USRVFS	8	/* first 8 (0 - 7) reserved for IBM use */

/* User file systems use MNT_USRVFS to MNT_USRLAST.               */
#define MNT_SFS	       16	/* AIX Special FS (STREAM mounts) */
#define MNT_CACHEFS    17	/* Cachefs file system            */
#define MNT_NFS3       18	/* NFSv3 file system              */
#define MNT_AUTOFS     19	/* Automount file system          */

#define MNT_USRLAST    31       /* last valid user file system    */

/* vfs numbers above MNT_USRLAST reserved for IBM use only        */
#define MNT_VXFS       32       /* THRPGIO File System "vxfs"     */
#define MNT_VXODM      33       /* For Veritas File System        */
#define MNT_UDF        34       /* UDFS file system               */
#define MNT_NFS4       35       /* NFSv4 file system              */
#define MNT_RFS4       36       /* NFSv4 Pseudo file system       */
#define	MNT_CIFS       37	/* AIX SMBFS (CIFS client)        */

#define MNT_AIXLAST    39	/* last valid vfs number	  */

#define MNT_BADVFS     -1       /* always illegal vfs type	  */


/*
 * Definitions for bits in the vfs_flag field.
 * 
 * Some of these are renamed and used as mount flags
 */

/* VFS flags */

#define	VFS_READONLY	0x00000001	/* rdonly  access to vfs        */
#define	VFS_REMOVABLE	0x00000002	/* removable (diskette) media   */
#define	VFS_DEVMOUNT	0x00000004	/* physical device mount        */
#define	VFS_REMOTE	0x00000008	/* file system is on network    */
#define VFS_SYSV_MOUNT	0x00000010	/* System V style mount		*/
#define	VFS_UNMOUNTING	0x00000020	/* originated by unmount()	*/
#define	VFS_NOSUID	0x00000040	/* don't maintain suid-ness	*/
					/* across this mount		*/
#define	VFS_NODEV	0x00000080	/* don't allow device access	*/
					/* across this mount		*/
#define VFS_NOINTEG	0x00000100	/* no integrity mount option	*/
#define VFS_NOMANAGER	0x00000200	/* mount managed fs w/o manager	*/
#define VFS_NOCASE	0x00000400	/* do not map dir names        	*/
#define VFS_UPCASE	0x00000800	/* map dir names to uppercase  	*/
#define VFS_NBC		0x00001000	/* NBC cached file in this vfs  */
#define VFS_MIND	0x00002000	/* multi-segment .indirect      */
#define VFS_RBR		0x00004000	/* Release-behind when reading	*/
#define VFS_RBW		0x00008000	/* Release-behind when writing	*/
#define	VFS_DISCONNECTED 0x00010000	/* file mount not in use        */
#define	VFS_SHUTDOWN	0x00020000	/* forced unmount for shutdown	*/
#define VFS_VMOUNTOK	0x00040000	/* dir/file mnt permission flag	*/
#define	VFS_SUSER	0x00080000	/* client-side suser perm. flag */
#define VFS_SOFT_MOUNT 	0x00100000	/* file-over-file or directory  */
					/* over directory "soft" mount  */
#define VFS_UNMOUNTED   0x00200000      /* unmount completed, stale     */
					/* vnodes are left in the vfs   */
#define VFS_DEADMOUNT	0x00400000	/* softmount vfs should be      */
					/* disconnected at last vnode   */
					/* free				*/
#define VFS_SNAPSHOT	0x00800000	/* snapshot mount               */
#define VFS_VCM_ON	0x01000000	/* VCM is currently active      */
#define VFS_VCM_MONITOR	0x02000000	/* VCM monitoring is active 	*/
#define VFS_CIO		0x40000000	/* O_CIO mount			*/
#define VFS_DIO		0x80000000	/* O_DIRECT mount		*/


/* Mount flags */
#define	MNT_READONLY	VFS_READONLY
#define	MNT_REMOVABLE	VFS_REMOVABLE
#define	MNT_DEVICE	VFS_DEVMOUNT
#define	MNT_REMOTE	VFS_REMOTE
#define MNT_SYSV_MOUNT	VFS_SYSV_MOUNT
#define	MNT_UNMOUNTING	VFS_UNMOUNTING	
#define	MNT_NOSUID	VFS_NOSUID
#define	MNT_NODEV	VFS_NODEV
#define MNT_NOINTEG	VFS_NOINTEG
#define MNT_NOMANAGER	VFS_NOMANAGER
#define MNT_NOCASE	VFS_NOCASE
#define MNT_UPCASE	VFS_UPCASE
#define MNT_VFS_NBC     VFS_NBC
#define MNT_MIND	VFS_MIND
#define MNT_RBR		VFS_RBR
#define MNT_RBW		VFS_RBW
#define MNT_DIO		VFS_DIO
#define MNT_SNAPSHOT	VFS_SNAPSHOT
#define MNT_CIO		VFS_CIO

/* 
 * J2 specific redifines ..
 * VFS_MIND is not used on JFS2
 * redefining as VFS_ATIMEOFF "mount -o noatime" 
 */     
#define VFS_ATIMEOFF    VFS_MIND        /* no atime updates on read */
#define MNT_ATIMEOFF    VFS_ATIMEOFF


/*
 * The following may be used as flags for mount(2) and vmount(2) calls.  
 * MNT_DEVICE, MNT_REMOTE are output only -- ignored as input, set by vmount
 */
#define VMOUNT_MASK	\
	(MNT_READONLY | MNT_REMOVABLE | MNT_SYSV_MOUNT | MNT_NOSUID | \
	 MNT_NODEV | MNT_NOINTEG | MNT_NOMANAGER | MNT_NOCASE | MNT_UPCASE | \
	 MNT_MIND | MNT_RBR | MNT_RBW | MNT_DIO | \
	 MNT_SNAPSHOT | MNT_CIO )


/*
 * The variable length data descriptors are an array of offsets
 * (from beginning of struct vmount) and sizes.
 * NOTES:
 * If a particular area has no data, offset and size should be 0.
 * The size must always be filled in, even if the data is a NULL
 * terminated printable text string.
 */
#define VMT_OBJECT	0	/* I index of object name		*/
#define VMT_STUB	1	/* I index of mounted over stub name	*/
#define VMT_HOST	2	/* I index of (short) hostname		*/
#define VMT_HOSTNAME	3	/* I index of (long) hostname		*/
#define VMT_INFO	4	/* I index of binary vfs specific info	*/
				/*   includes network address, opts, etc*/
#define VMT_ARGS	5	/* I index of text of vfs specific args	*/
#define VMT_LASTINDEX	5	/* I the last in the array of structs	*/

/*
 * Vmount system call argument, also a mntctl return structure.
 * This structure has a fixed size of data and offsets, and then
 * has the data for the fs pointed to by "vmount ptr + offset".
 * If a particular area has no data, the offset and size should be 0.
 * Input parameters are indicated by "I", output only parameters
 * are indicated by "O" (input parameters are also output).
 */
struct vmount {
	uint	vmt_revision;	/* I revision level, currently 1	*/
	uint	vmt_length;	/* I total length of structure and data	*/
#if !defined(_KERNEL) && defined(__64BIT__)
	fsid64_t  vmt_fsid;	/* O id of file system			*/
#else
	fsid_t	vmt_fsid;	/* O id of file system			*/
#endif
	int	vmt_vfsnumber;	/* O unique mount id of file system	*/
	uint	vmt_time;	/* O time of mount			*/
	uint	vmt_timepad;	/* O (in future, time is 2 longs)	*/
	int	vmt_flags;	/* I general mount flags		*/
				/* O MNT_REMOTE is output only		*/
	int	vmt_gfstype;	/* I type of gfs, see MNT_XXX above	*/
	struct vmt_data {
		short vmt_off;	/* I offset of data, word aligned	*/
		short vmt_size;	/* I actual size of data in bytes	*/
	} vmt_data[VMT_LASTINDEX + 1];
	/*
	 * the variable length data goes here, starting at word (32 bit)
	 * boundaries.
	 */
};

#define	VMT_REVISION	1	/* current version of struct vmount	*/

/*
 * macros to easily get ptr and size of variable length info
 * given ptr to vmount structure and index to object
 */
#define	vmt2dataptr(vmt, idx)	((caddr_t)(((long)(vmt)) + \
				((vmt)->vmt_data[(idx)].vmt_off)))
#define	vmt2datasize(vmt, idx)	((vmt)->vmt_data[(idx)].vmt_size)

/*
 * mntctl operations and arguments.
 *	mntctl(cmd, size, buf)
 * cmd - one of the command defines below (MCTL_????)
 * size - size of the area that buf points to
 * buf - pointer to an argument/results area
 */
#define	MCTL_QUERY	2	/* (new style) query what is mounted
				 * buf points to array of vmount structures
				 * (which are variable length)
				 * returns: 0 = look in first word of buf
				 *	for needed size,
				 * -1 = error,
				 * >0 = number of vmount structs in buf
				 */

/*
 * flags for the uvmount(2) system call
 * int uvmount(vfsnumber, flags)
 *	int	vfsnumber; number from vmount structure, or statfs
 */
#define	UVMNT_FORCE	0x0001	/* force the unmount, regardless! */

/* Function prototypes */
int vmount(struct vmount *, int);
int uvmount(int, int);
int mntctl(int, size_t, char *);
int fscntl(int, int, caddr_t, size_t);

#endif /* _H_VMOUNT */
