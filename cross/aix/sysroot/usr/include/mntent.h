/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/mntent.h 1.3                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2001               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)50  1.3  src/bos/usr/include/mntent.h, cmdfs, bos530 3/6/01 08:41:15 */

/*
 * Structures, defines, and prototypes for the
 * System V mntent functions.
 */

#ifndef _H_MNTENT
#define _H_MNTENT

#ifndef _H_STDIO
#include <stdio.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Generic mount options.  */
#define MNTOPT_DEFAULTS	"defaults"	/* Use all default options.  */
#define MNTOPT_RO	"ro"		/* Read only.  */
#define MNTOPT_RW	"rw"		/* Read/write.  */
#define MNTOPT_SUID	"suid"		/* Set uid allowed.  */
#define MNTOPT_NOSUID	"nosuid"	/* No set uid allowed.  */
#define MNTOPT_NOAUTO	"noauto"	/* Do not auto mount.  */

/*
 * Define paths to fstab and mtab.
 * AIX uses /etc/filesystems for fstab.
 * AIX uses a virtual "/etc/mtab", so don't try to use either the
 * filename or the FILE * returned by setmntent directly.
 */
#define	MNTTAB	"/etc/filesystems"
#define MOUNTED	"/etc/mtab"

/*
 * Structure section.
 */
struct mntent {
	char *mnt_fsname;	/* Name of block special */
	char *mnt_dir;		/* Mount point */
	char *mnt_type;		/* vfs type */
	char *mnt_opts;		/* mount options */
	int   mnt_freq;		/* dump frequency */
	int   mnt_passno;	/* fsck pass number */
};

/*
 * Function prototype section.
 */
#ifdef _NO_PROTO
extern FILE *setmntent();
extern int endmntent();
extern struct mntent *getmntent();
extern int addmntent();
extern char *hasmntopt();
#else
extern FILE *setmntent(const char *, const char *);
extern int endmntent(FILE *);
extern struct mntent *getmntent(FILE *);
extern int addmntent(FILE *, const struct mntent *);
extern char *hasmntopt(const struct mntent *, const char *);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _H_MNTENT */
