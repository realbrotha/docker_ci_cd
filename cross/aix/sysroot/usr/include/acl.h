/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53A src/bos/kernel/sys/acl.h 1.4.1.15                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,1994          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)85	1.4.1.15  src/bos/kernel/sys/acl.h, syssdac, bos53A, a2004_35E0 8/4/04 15:53:37 */
/*
 *   COMPONENT_NAME: syssdac
 *
 *   FUNCTIONS(MACROS):
 *		acl_last
 *		acl_nxt
 *		id_last
 *		id_nxt
 *
 * ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1989,1994
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _ACL_H
#define _ACL_H

#include <sys/types.h>
#include <sys/access.h>
#include <sys/vmount.h>

#ifndef _KERNEL
#include <stdio.h>
#endif /* _KERNEL */

/************************************************************************
 *               General ACL infrastructure related definitions
 *               ACL type specific information will follow later.
 ***********************************************************************/

/* Maximum size of ACL supported under the OS. Note that individual
* physical file systems might restrict the sizes of ACLs based on
* the ACL type to a value lesser than this.
*/
#define	MAX_ACL_SIZE		0x10000

/* Bit masks for ctl_flags parameter in aclx_get() and aclx_put() operations */

#define GET_ACLINFO_ONLY	0x01
#define SET_ACL			0x02
#define SET_MODE_S_BITS		0x04

#ifdef _KERNEL
#define SET_MODE_WORD   	0x08
#endif /* _KERNEL */

#define GET_ACL_FOR_LINK	0x10	/* do not traverse final symbolic link */
#define GET_ACL_FOR_MOUNT	0x20	/* do not traverse final mount point */
#define GET_ACL_FOR_HIDDEN	0x40	/* do not traverse final hidden directory */

#define USR_FW_VER_LATEST	1

#ifndef _KERNEL

/* 
 * acl_type_t captures the type of the ACL. Note that it is
 * an 8 byte entity and takes the form of a string with the
 * unused bytes zeroed out. ACL types are unique on the system
 * and any new type chosen should be chosen such that it does
 * not conflict with the existing types.
 */

#define MAX_ACL_TYPE_LEN    8

typedef union _acl_type_t {   
	char		acl_type[MAX_ACL_TYPE_LEN]; /* String form */
	uint64_t	u64;			/* Number form */
} acl_type_t;

int __fstatxacl(int fd, uint64_t ctl_flags, acl_type_t *acl_type,
		void *acl, size_t *acl_sz, mode_t *mode_info);
int __statxacl(char *path, uint64_t ctl_flags, acl_type_t *acl_type,
		void *acl, size_t *acl_sz, mode_t *mode_info);
int __fchxacl(int fd, uint64_t ctl_flags, acl_type_t acl_type,
		void *acl, size_t acl_sz, mode_t mode_info);
int __chxacl(char *path, uint64_t ctl_flags, acl_type_t acl_type,
		void *acl, size_t acl_sz, mode_t mode_info);
#else
/* 
 * In kernel layer it is not expected that the ACL type will
 * be used in the form of a string. Hence the following definition
 * is used
 */
typedef	uint64_t	acl_type_t;
/* 
 * The following prototypes map to the ones defined above, but expand on 64
 * bit arguments such that they could be retrieved from 2 registers in the
 * case of 32 bit kernel
 */
int __fstatxacl(int fd, ulong r4, ulong r5, ulong r6,
				ulong r7, ulong r8, ulong r9);
int __statxacl(char *path, ulong r4, ulong r5, ulong r6,
				ulong r7, ulong r8, ulong r9);
int __fchxacl(int fd, ulong r4, ulong r5, ulong r6, ulong r7,
				ulong r8, ulong r9, ulong r10);
int __chxacl(char *path, ulong r4, ulong r5, ulong r6, ulong r7,
				ulong r8, ulong r9, ulong r10);
#endif /* _KERNEL */

int __aclxcntl(char *path, int cmd, caddr_t arg, size_t *argsize);

/* 
 * Currently following ACL types are defined.
 * Note that type is defined to indicate ANY, which 
 * is useful in cases where requests are made to
 * retrieve the any associated with the File system
 * object.
 */
#define ACL_ANY		0x414E590000000000uLL	/* 'A','N','Y',0... */
#define ACL_AIXC	0x4149584300000000uLL	/* 'A','I','X','C',0... */
#define ACL_NFS4	0x4E46533400000000uLL	/* 'N','F','S','4',0... */

/* 
 * A VFS interface provides control over the ACL
 * operations in the systems. Set of commands are
 * defined uniformly for all the physical file
 * systems in this regards. Following is the list
 * of command constants for __aclxcntl 
 */
#define ACLCNTL_GETACLXTYPES		1
#define ACLCNTL_GETACLXTYPEINFO		2

/* 
 * Following structure provides information about an ACL type. 
 * Information includes minor details about the type such as
 * attributes supported etc
 * The field acl_info is ACL type specific.
 */
typedef struct _acl_type_info_t {
	acl_type_t	acl_type;	/* Type of ACL to which this 
					   structure applies */
	char 		acl_type_info[1];	/* Type specific info. For
					  details refer to type
					  specific info below */
} acl_type_info_t;

/* Maximum number of ACL types supported on system */
#define	MAX_ACL_TYPES		16
typedef	struct   _acl_types_list_t  {
	uint32_t	num_entries;	/* Number of entries */
	uint32_t	pad;		/* make acl_types_list_t to have 
					   same layout for 32 or 64 bit apps */
	acl_type_t	entries[MAX_ACL_TYPES];	/* List of ACL types */
} acl_types_list_t ;

#ifndef _KERNEL

/* 
 * Verbose flag used in aclx_print. This bit mask
 * is passed to aclx_print as one of the arguments
 * to enable display of verbose information as part
 * of the ACL text output
 */
#define V_FLAG      0x00000001

/* 
 * The following section describes the various function
 * prototypes for ACL library interfaces.
 */
#ifdef  _NO_PROTO
extern int aclx_get();
extern int aclx_fget();
extern int aclx_put();
extern int aclx_fput();
extern int aclx_scan();
extern int aclx_scanStr();
extern int aclx_print();
extern int aclx_printStr();
extern int aclx_gettypes();
extern int aclx_convert();
extern int aclx_gettypeinfo();
#else   /* _NO_PROTO */
extern int aclx_get(char *, uint64_t, acl_type_t *, void *, size_t *, mode_t *);
extern int aclx_fget(int, uint64_t, acl_type_t *, void *, size_t *, mode_t *);
extern int aclx_put(char *, uint64_t, acl_type_t, void *, size_t, mode_t);
extern int aclx_fput(int, uint64_t, acl_type_t, void *, size_t, mode_t);
extern int aclx_scan(FILE *, void *, size_t *, acl_type_t, FILE *);
extern int aclx_scanStr(char *, void *, size_t *, acl_type_t);
extern int aclx_print(FILE *, void *, size_t, acl_type_t, char *, int);
extern int aclx_printStr(char *, size_t *, void *, size_t, acl_type_t, char *, int);
extern int aclx_gettypes(char *, acl_types_list_t *, size_t *);
extern int aclx_convert(void *, size_t, acl_type_t, void *, size_t *,
		acl_type_t, char *);
extern int aclx_gettypeinfo(char *, acl_type_t, void *, size_t *);
#endif  /* _NO_PROTO */

#endif /* ! _KERNEL */

/************************************************************************
 *               NFS4 ACL type related definitions
 ***********************************************************************/

/* 
 * Following union captures the identity as 
 * used in the NFS4 ACL structures. 
 */
typedef union _nfs4_acewhoid_t {
	uid_t	uid;	/* User id */
	gid_t	gid;	/* Group id */
	int32_t	special_whoid;	/* Identifies special identities in NFS4 */
/*
 * The following are constants for acewho field, used when ACE_ID_SPECIAL is set.
 * Note that quite a number of these are not supported on AIX currently
 */
#define ACE4_WHO_OWNER         0x00000001 /*The owner of the file. */
#define ACE4_WHO_GROUP         0x00000002 /*The group associated with the file. */
#define ACE4_WHO_EVERYONE      0x00000003 /*The world. */
#define ACE4_WHO_INTERACTIVE   0x00000004 /*Accessed from an interactive terminal. */
#define ACE4_WHO_NETWORK       0x00000005 /*Accessed via the network. */
#define ACE4_WHO_DIALUP        0x00000006 /*Accessed as a dialup user to the server. */
#define ACE4_WHO_BATCH         0x00000007 /*Accessed from a batch job. */
#define ACE4_WHO_ANONYMOUS     0x00000008 /*Accessed without any authentication. */
#define ACE4_WHO_AUTHENTICATED 0x00000009 /*Any authenticated user (opposite of ANONYMOUS) */
#define ACE4_WHO_SERVICE       0x0000000A /*Access from a system service. */
#define ACE4_WHO_MAX		ACE4_WHO_SERVICE  /* largest valid ACE4_WHO */
	int32_t id;
} nfs4_acewhoid_t;

/* 
 * Following marcos help reach for the various union
 * members above with ease
 */
#define	whouid	aceWho.uid
#define	whogid	aceWho.gid
#define	whosid	aceWho.special_whoid
#define	whoid	aceWho.id

/* Typedefs that define the various entities of a NFS4 ACE */
typedef uint32_t nfs4_acetype;
typedef uint32_t nfs4_aceflag;
typedef uint32_t nfs4_acemask;

/* 
 * The following structure captures NFS4 ACE information. Note that  
 * it has additional members when compared to ACE defined by RFC
 * This ACE is used consistently in the OS to represent the NFS4
 * ACE and wire format will be converted to and fro as necessary
 */
typedef struct _nfs4_ace_int_t { 
	int32_t		entryLen;
				/* Total size of this ACE rounded 
				 * up to a 4 byte boundary. It is 
				 * also used to locate the next ACE entry */
	uint32_t	flags;	/* Bit mask defining details of ACE */
/*The following are constants for flags field */
#define	ACE4_ID_NOT_VALID	0x00000001 
#define	ACE4_ID_SPECIAL		0x00000002 

	nfs4_acewhoid_t	aceWho;	/* Identifies to whom this ACE applies */

	/* The following part of ACE has the same layout as NFSv4 wire format. */

	nfs4_acetype	aceType;	/* Type of ACE PERMIT/ALLOW etc*/
/*The constants used for the type field (acetype4) are as follows: */
#define	ACE4_ACCESS_ALLOWED_ACE_TYPE	0x00000000 
#define	ACE4_ACCESS_DENIED_ACE_TYPE	0x00000001 
#define	ACE4_SYSTEM_AUDIT_ACE_TYPE	0x00000002 
#define	ACE4_SYSTEM_ALARM_ACE_TYPE	0x00000003 
#define ACE4_MAX_TYPE			ACE4_SYSTEM_ALARM_ACE_TYPE  /* largest valid ACE4_TYPE */

	nfs4_aceflag	aceFlags;	/* Controls Inheritance and such */
/*The bitmask constants used for the flag field are as follows: */
#define ACE4_FILE_INHERIT_ACE             0x00000001 
#define ACE4_DIRECTORY_INHERIT_ACE        0x00000002 
#define ACE4_NO_PROPAGATE_INHERIT_ACE     0x00000004 
#define ACE4_INHERIT_ONLY_ACE             0x00000008 
#define ACE4_SUCCESSFUL_ACCESS_ACE_FLAG   0x00000010 
#define ACE4_FAILED_ACCESS_ACE_FLAG       0x00000020 
#define ACE4_IDENTIFIER_GROUP             0x00000040 
#define ACE4_ALL_FLAGS			( ACE4_FILE_INHERIT_ACE | ACE4_DIRECTORY_INHERIT_ACE \
| ACE4_NO_PROPAGATE_INHERIT_ACE | ACE4_INHERIT_ONLY_ACE | ACE4_SUCCESSFUL_ACCESS_ACE_FLAG \
| ACE4_FAILED_ACCESS_ACE_FLAG | ACE4_IDENTIFIER_GROUP )


	nfs4_acemask	aceMask;	/* Access rights */
/*The bitmask constants used for the access mask field are as follows: */
#define ACE4_READ_DATA            0x00000001 
#define ACE4_LIST_DIRECTORY       0x00000001 
#define ACE4_WRITE_DATA           0x00000002 
#define ACE4_ADD_FILE             0x00000002 
#define ACE4_APPEND_DATA          0x00000004 
#define ACE4_ADD_SUBDIRECTORY     0x00000004 
#define ACE4_READ_NAMED_ATTRS     0x00000008 
#define ACE4_WRITE_NAMED_ATTRS    0x00000010 
#define ACE4_EXECUTE              0x00000020 
#define ACE4_DELETE_CHILD         0x00000040 
#define ACE4_READ_ATTRIBUTES      0x00000080 
#define ACE4_WRITE_ATTRIBUTES     0x00000100 
#define ACE4_DELETE               0x00010000 
#define ACE4_READ_ACL             0x00020000 
#define ACE4_WRITE_ACL            0x00040000 
#define ACE4_WRITE_OWNER          0x00080000 
#define ACE4_SYNCHRONIZE          0x00100000 
#define ACE4_ALL_MASKS		( ACE4_READ_DATA | ACE4_LIST_DIRECTORY \
| ACE4_WRITE_DATA | ACE4_ADD_FILE | ACE4_APPEND_DATA | ACE4_ADD_SUBDIRECTORY \
| ACE4_READ_NAMED_ATTRS | ACE4_WRITE_NAMED_ATTRS | ACE4_EXECUTE | ACE4_DELETE_CHILD \
| ACE4_READ_ATTRIBUTES | ACE4_WRITE_ATTRIBUTES | ACE4_DELETE | ACE4_READ_ACL \
| ACE4_WRITE_ACL | ACE4_WRITE_OWNER | ACE4_SYNCHRONIZE )

	char		aceWhoString[1]; 
			/* NULL terminated. Always a least 1 char for a '\0' */
	/* The structure is rounded of to 4bytes by padding bytes from here 
	 * onwards.
	 */
} nfs4_ace_int_t; 

typedef struct _nfs4_acl_int_t { 
	int32_t		aclLength;	/* Total length (hdr + ace entries) */
	uint32_t	aclVersion;	/* Version number */
#define	NFS4_ACL_INT_STRUCT_VERSION	1
	int32_t		aclEntryN;	/* Number of ACEs in the acl */
	nfs4_ace_int_t	aclEntry[1];	/* Array of ACEs */
} nfs4_acl_int_t; 


#define	ACE_V4_SIZ	((int) &(((nfs4_ace_int_t*) 0) -> aceWhoString[0]))
#define	ACL_V4_SIZ	((int) &(((nfs4_acl_int_t *) 0) -> aclEntry[0]))


/*
 * ACL type specific information for NFS4 ACL
 */
typedef	struct   _nfs4_acl_type_info_t  {
	uint32_t	version;  	/* Structure version information */
#define	NFS4_ACL_TYPE_INFO_STRUCT_VERSION	1
	uint32_t	acl_support;	/* ACL support attrs for NFS4 RFC */
        /* The possible values of acl_support */
#define ACL4_SUPPORT_ALLOW_ACL    0x00000001
#define ACL4_SUPPORT_DENY_ACL     0x00000002
#define ACL4_SUPPORT_AUDIT_ACL    0x00000004
#define ACL4_SUPPORT_ALARM_ACL    0x00000008
} nfs4_acl_type_info_t ;

/************************************************************************
 *               AIXC ACL type related definitions
 ***********************************************************************/

/* Support AIXC ACL upto 4KB size.  */
#define	MAX_AIXC_ACL_SIZE		0x1000

/* General format of an ace entry (variable length) */
struct	ace_id
{
	unsigned short	id_len;		/* length of identifier */
	unsigned short	id_type;	/* type of specifier */
/* only 1 uid or gid per ace_id struct when id_type is one of these: */
#		define	ACEID_USER	1
#		define	ACEID_GROUP	2
	int	id_data[1];		/* length of data is actually */
					/* (id_len - 4)		      */
};

/* size of the header of an acl entry */
#define	ID_SIZ	((int) &(((struct ace_id *) 0) -> id_data[0]))

/* address past the last ID in the acl */
#define	id_last(a) \
	((struct ace_id *)(((char *)(a)) + (a)->ace_len))

/* advance to the next identifier in an acl entry */
#define	id_nxt(id) \
	((struct ace_id *) (((char*)(id))+(((struct ace_id *)(id))->id_len))) 

/* General format of an acl entry (variable length) */
struct	acl_entry
{
	unsigned short	ace_len;	/* total length of the acl entry */
	unsigned 	ace_type : 2;	/* the type of acl entry:  see   */
					/* <sys/access.h> for more info  */
	unsigned 	ace_access : 14;    /* permission bits           */
					    /* (granted = 1, denied = 0) */

	struct	ace_id	ace_id[1];          /*
	 				     * list of attributes to be 
					     * satisfied for this acl entry 
					     * to be applicable
					     */
};

#define	ACE_SIZ	((int) &(((struct acl_entry *) 0) -> ace_id[0]))

/* advance to the next entry in an acl */
#define	acl_nxt(a) \
	((struct acl_entry *) (((char*)(a))+(((struct acl_entry*)(a))->ace_len))) 

#define acl_last(a) \
	((struct acl_entry *)(((char *)(a)) + (a)->acl_len))

struct	acl
{
	unsigned int	acl_len;
	unsigned int	acl_mode;
		/* TBD: this should include S_TCB */
#		define	ACL_MODE	(S_IXACL|S_ISUID|S_ISGID|S_ISVTX)
	ushort	acl_rsvd;
	ushort	u_access;
	ushort	g_access;
	ushort	o_access;
	struct	acl_entry	acl_ext[1];
};

#define	ACL_SIZ	((int) &(((struct acl *) 0) -> acl_ext[0]))

#ifdef  _NO_PROTO
	extern int chacl();
	extern int fchacl();
	extern int statacl();
	extern int fstatacl();
#else	/* _NO_PROTO */
	extern int chacl(char *, struct acl *, int);
	extern int fchacl(int, struct acl *, int);
	extern int statacl(char *, int, struct acl *, int);
	extern int fstatacl(int, int, struct acl *, int);

	extern int __chaclx (char *, void *, size_t, unsigned int);
	extern int __fchaclx (int, void *, size_t, unsigned int);
	extern int __stataclx (char *, int, void *, size_t, unsigned int);
	extern int __fstataclx (int, int, void *, size_t, unsigned int);
#endif	/* _NO_PROTO */

/*
 * ACL types to be passed to __chaclx, __fchaclx, __stataclx and
 * __fstataclx.  The type is simply the VFS number.
 */

#define	ACL_VFSTYPE_MASK	0xff
#define	ACL_VFSTYPE_ANY		0xff

#define	ACL_VFSTYPE_JFS		MNT_JFS
#define	ACL_VFSTYPE_JFS2	MNT_J2

typedef	struct acl		aixc_acl_t;
typedef	struct acl_entry	aixc_ace_t;
typedef	struct ace_id		aixc_acewhoid_t;

#endif	/* _ACL_H */
