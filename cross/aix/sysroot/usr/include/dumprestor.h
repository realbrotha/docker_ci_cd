/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/usr/include/dumprestor.h 1.14.5.1                       */
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
/* @(#)36 1.14.5.1  src/bos/usr/include/dumprestor.h, cmdarch, bos53X, x2009_25A9 6/11/09 11:10:32 */
/*
 * COMPONENT_NAME: (CMDARCH) Archival Commands
 *                                                                    
 * FUNCTIONS: Include file for backup and restore functions
 *
 * ORIGINS: 3, 26, 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1996
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */                                                                   

#ifndef _H_DUMPRESTOR
#define _H_DUMPRESTOR 

/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *      (#)dumprestore.h       5.1 (Berkeley) 6/5/85
 */

/*
 * The following 'cardinal' types are used for backup and restore headers.
 * Naming convention is 'cardX' for signed integers and 'ucardX' for
 * unsigned integers, where 'X' is a value of 1, 2, 4, or 8, depending
 * on the number of (8 bit) bytes in size.
 */

typedef signed char		card1;
typedef signed short		card2;
typedef signed int		card4;
typedef signed long long	card8;
typedef unsigned char		ucard1;
typedef unsigned short		ucard2;
typedef unsigned int		ucard4;
typedef unsigned long long	ucard8;

/*
 * TP_BSIZE is the size of file blocks on the dump tapes.
 * Note that TP_BSIZE must be a multiple of DEV_BSIZE.
 *
 * NTREC is the number of TP_BSIZE blocks that are written
 * in each tape record. HIGHDENSITYTREC is the number of
 * TP_BSIZE blocks that are written in each tape record on
 * 6250 BPI or higher density tapes.
 *
 * TP_NINDIR is the number of indirect pointers in a TS_INODE
 * or TS_ADDR record. Note that it must be a power of two.
 */
#define TP_BSIZE	1024
#define NTREC   	10
#define HIGHDENSITYTREC	32
#define TP_NINDIR	(TP_BSIZE/2)

#define TS_TAPE 	1
#define TS_INODE	2
#define TS_BITS 	3
#define TS_ADDR 	4
#define TS_END  	5
#define TS_CLRI 	6
#define TS_ACL  	7
#define TS_PCL  	8
#define TS_INODE_LF	9
#define TS_SEC		10
#define TS_J2DIR	11		/* Used for JFS2 directory */
#define TS_INODE_LN	12		/* Used for inode number > 32-bits */
#define	TS_EA		13		/* Used for named extended attributes */
#define	TS_ACL2		14		/* Used for typed-ACLs */
#define OFS_MAGIC   	(int)60011
#define NFS_MAGIC   	(int)60012
#define MAGIC           (int)60011   /* magic number for headers      */
#define PACKED_MAGIC    (int)60012   /* magic # for Huffman packed format */
#define B1V1_MAGIC      (int)60013   /* magic number for B1 V1 headers          */
#define B1V1_PACKED_MAGIC (int)60014 /* magic # for B1 V1 Huffman packed format */
#define B1V2_MAGIC      (int)60015   /* magic number for B1 V2 headers          */
#define B1V2_PACKED_MAGIC (int)60016 /* magic # for B1 V2 Huffman packed format */
#define XIX_MAGIC	(int)60013   /* magic number for AIX v3 */
#define JFS2_MAGIC	(int)60017   /* magic # for JFS2 directory format */
#define CHECKSUM	(int)84446

#define BSD_NDADDR	12
#define BSD_NIADDR	3

struct 	icommon
{
	u_short	ic_mode;	/*  0: mode and type of file */
	short	ic_nlink;	/*  2: number of links to file */
	ushort	ic_uid;		/*  4: owner's user id */
	ushort	ic_gid;		/*  6: owner's group id */
	quad	ic_size;	/*  8: number of bytes in file */
	time_t	ic_atime;	/* 16: time last accessed */
	long	ic_atspare;
	time_t	ic_mtime;	/* 24: time last modified */
	long	ic_mtspare;
	time_t	ic_ctime;	/* 32: last time inode changed */
	long	ic_ctspare;
	daddr_t	ic_db[BSD_NDADDR];	/* 40: disk block addresses */
	daddr_t	ic_ib[BSD_NIADDR];	/* 88: indirect blocks */
	long	ic_flags;	/* 100: status, currently unused */
	long	ic_blocks;	/* 104: blocks actually held */
	long	ic_spare[5];	/* 108: reserved, currently unused */
};

struct bsd_dinode {
	union {
		struct	icommon di_icom;
		char	di_size[128];
	} di_un;
};

/*
 * Note: xix_dinode is actually a JFS struct dinode when backing up a JFS
 *	 filesystem.
 *	 When backing up a JFS2 filesystem c_inumber is not used for the inode
 *	 number and the first 64-bits of xix_dinode contains the inode number
 *	 instead.
 *
 *	 For backwards compatibility xix_dinode needs to stay the size of a
 *	 JFS struct dinode (128 bytes).
 *	 xix_dinode is not actually being used by the restore code when JFS
 *	 stores into it.  It will be used for getting the inode numbers for JFS2
 */
#define JFSDILENGTH	128	/* JFS disk inode length */
union u_spcl {
	char dummy[TP_BSIZE];
	struct	s_spcl {
		int	c_type;
		time_t	c_date;
		time_t	c_ddate;
		int	c_volume;
		daddr_t	c_tapea;
		u_long	c_inumber;
		int	c_magic;
		int	c_checksum;
		struct	bsd_dinode	bsd_c_dinode;
		int	c_count;
		char	c_addr[TP_NINDIR];
		int	xix_flag;
		char	xix_dinode[JFSDILENGTH];
	} s_spcl;
} u_spcl;

#define spcl u_spcl.s_spcl
#define bsd_di_ic		di_un.di_icom
#define	bsd_di_mode		bsd_di_ic.ic_mode
#define	bsd_di_nlink		bsd_di_ic.ic_nlink
#define	bsd_di_uid		bsd_di_ic.ic_uid
#define	bsd_di_gid		bsd_di_ic.ic_gid
#define	bsd_di_db		bsd_di_ic.ic_db
#define	bsd_di_ib		bsd_di_ic.ic_ib
#define	bsd_di_atime		bsd_di_ic.ic_atime
#define	bsd_di_mtime		bsd_di_ic.ic_mtime
#define	bsd_di_ctime		bsd_di_ic.ic_ctime
#define	bsd_di_rdev		bsd_di_ic.ic_db[0]
#define	bsd_di_blocks		bsd_di_ic.ic_blocks
#define bsd_di_size             bsd_di_ic.ic_size.val[1]
#define bsd_di_size_lo          bsd_di_ic.ic_size.val[1]
#define bsd_di_size_hi          bsd_di_ic.ic_size.val[0]

#define	DUMPOUTFMT	"%s %c %s"		/* for printf */
						/* name, incno, ctime(date) */
#define	DUMPINFMT	"%s %c %[^\n]\n"	/* inverse for scanf */


/* The backup command options are also used by the backsnap command.
 * The backsnap options are -R, -m, and -s.  These options should not
 * be passed to the backup command.
 * The -?, -i and -n options are common to both.  Make sure the common
 * options will be parsed by both commands.  The -? option gives the
 * usage of the command it is issued with.
 * Note: any options that take an argument, added to the backup command,
 *       also need to be added to the backsnap command switch statement,
 *       or the backup command invoked from the backsnap command can not
 *       parse the arguments correctly. */
#define BACKOPTS	"?cb:orqwUWu0123456789ivpe:f:l:SL:E:m:s:R"


/*
 * macros for accessing bitmaps
 *      MWORD( map, bitno )     returns word containing specified bit
 *      MBIT(i)                 returns mask for specified bit within map word
 *      BIS                     turns on specified bit in map
 *      BIC                     turns off specified bit in map
 *      BIT                     tests specified bit in map
 */
#define	MWORD(m,i)	(m[(unsigned)(i-1)/NBBY])
#define	MBIT(i)		(1<<((unsigned)(i-1)%NBBY))
#define	BIS(i,w)	(MWORD(w,i) |=  MBIT(i))
#define	BIC(i,w)	(MWORD(w,i) &= ~MBIT(i))
#define	BIT(i,w)	(MWORD(w,i) & MBIT(i))

/* Following definitions are from the version 2 backup.h include file */
/*
 *      bitmap parameters.
 *      note: 8K * 8 == 64K, largest possible inumber
 */
#define MSIZ            (8*1024)        /* number of words in map        */
/*
 * Because of the end-around copying done in readtape, buffers
 * returned by readtape must be no greater than RDTMAX bytes
 */
#define RDTMAX BSIZE	/* maximum tape read length */

/*
 * format of inode dump
 *      FS_VOLUME
 *      FS_CLRI         (if incremental)
 *              list of inodes unallocated at time of dump
 *
 *      FS_BITS         (just before the first FS_INODE header on each vol.)
 *              list of files on this and succeeding volumes
 *
 *      FS_FINDEX
 *              index of files on this volume.  the last file or two
 *              may not be indexed, for space reasons.  the link field
 *              gives the address of the next FS_INDEX on this volume.
 *
 *      FS_DINODE        (before each file)
 *      file data
 *      FS_END or FS_VOLEND
 *
 * format of name dump:
 *      FS_VOLUME
 *      FS_NAME         (before each file)
 *      file data
 *      FS_END
 *
 */

/*
 * the file /etc/dumpdates contains a record for the last dump of each file
 *     system at each level.  This file is used to determine how far back
 *     new dumps should extend.  The record format is ...
 */
struct	idates
{
	char	id_name[MAXNAMLEN+3];
	char	id_incno;
	time_t	id_ddate;
};

/*
 * header types.  the hdrlen[] array (dump and restor) assumes that
 * the numbers begin at 0, and that they are in this order.
 * the OINODE and ONAME records are not produced by dump, but were
 * produced by older versions, and restore knows how to interpret
 * them.
 */
#define FS_VOLUME        0
#define FS_FINDEX        1
#define FS_CLRI          2
#define FS_BITS          3
#define FS_OINODE        4
#define FS_ONAME         5
#define FS_VOLEND        6
#define FS_END           7
#define FS_DINODE        8
#define FS_NAME          9
#define FS_DS           10
#define FS_NAME_X       11
#define FS_NAME_LF      12
#define	FS_NAME_EA	13
#define	FS_NAME_ACL	14
#define	FS_NAME_E	15


/* other constants */
#define FXLEN          80       /* length of file index */

/* commands to findex */
#define TBEG    0               /* start indexing */
#define TEND    1               /* end of this track */
#define TINS    2               /* install new inode in index */

/*
 * the addressing unit is 8-byte "words", also known as dwords
 */
#define BPW     8
#define LOGBPW  3
typedef struct {ucard1 x[BPW];} dword;

/* bytes to "words" and back; must fit into char */
/* must be even -- so always room for VOLEND record (8 bytes long) */
#define btow(x)   ( ((x) + BPW - 1) >> LOGBPW)
#define wtob(x)   ( (x) << LOGBPW )

#define swap_card8(d) \
	((((card8) swap_card4((d) >> 32)) & 0x00000000ffffffffLL) | \
	 ((((card8) swap_card4(d)) << 32) & 0xffffffff00000000LL))

#define swap_card4(d) \
	((((d) >> 24) & 0x000000ff) | (((d) >>  8) & 0x0000ff00) | \
	 (((d) <<  8) & 0x00ff0000) | (((d) << 24) & 0xff000000))

#define swap_card2(d) ((card2) ((((d) >> 8) & 0x00ff) | (((d) << 8) & 0xff00)))

#ifdef _POWER
#define rlonglong(a) ((a) = swap_card8(a))
#define wlonglong(a) ((a) = swap_card8(a))
#define rlong(a)     ((a) = swap_card4(a))
#define wlong(a)     ((a) = swap_card4(a))
#define rshort(a)    ((a) = swap_card2(a))
#define wshort(a)    ((a) = swap_card2(a))
#else
#define rlonglong(a) (a)
#define wlonglong(a) (a)
#define rlong(a)  (a)
#define wlong(a)  (a)
#define rshort(a) (a)
#define wshort(a) (a)
#endif

#define SIZHDR    btow(sizeof(struct hdr))
#define DUMNAME   4     /* dummy name length for FS_NAME */
#define DUMNAME2  8     /* dummy name length for FS_NAME_LF */
#define SIZSTR   16     /* size of strings in the volume record */

/* D41487: In order to allow all valid path names the param.h file has */
/* been included and NAMESZ has been given the value PATH_MAX + 1.       */

#include <sys/param.h>
#define NAMESZ	PATH_MAX+1	/* internal name string sizes */

#define min(a,b)  ( ((a) < (b))? (a): (b) )
#define max(a,b)  ( ((a) > (b))? (a): (b) )

#define BYNAME  100             /* must be illegal v.incno */
#define BYINODE 101             /*    "       "       "    */
#define BYMD    102             /*    "       "       "    */

#define DONTCOUNT   -1          /* for counting # files we want */

/*
 * the headers follow.  note that there are no places that might
 * tempt a compiler to insert gaps for alignment.  for example,
 * making the FS_FINDEX arrays into an array of (inode, address)
 * structs might later cause trouble.  also, there is code in
 * both dump and restor that reorders the bytes in these headers;
 * this code MUST know about any change in the structures.
 */

struct hdr {			/* common part of every header */
	ucard1	len;		/* hdr length in dwords */
	ucard1	type;		/* FS_* */
	ucard2	magic;		/* magic number (MAGIC above) */
	ucard2	checksum;
};

union fs_rec {

	/* common fields */
	struct hdr h;

	/* FS_VOLUME -- (70 bytes) begins each volume */
	struct {
		struct  hdr h;
		ucard2  volnum;         /* volume number */
		card4   date;           /* current date */
		card4   dumpdate;          /* starting date */
		card4   numwds;         /* number of wds this volume */
		char    disk[SIZSTR];   /* name of disk */
		char    fsname[SIZSTR]; /* name of file system */
		char    user[SIZSTR];   /* name of user */
		card2   incno;          /* dump level (or BYNAME) */
	} v;

	/* FS_FINDEX -- (492 bytes) indexes files on this volume */
	struct {
		struct  hdr h;
		ucard2  dummy;          /* get the alignment right */
		ucard2  ino[FXLEN];     /* inumbers */
		card4   addr[FXLEN];    /* addresses */
		card4   link;           /* next volume record */
	} x;

	/* FS_BITS or FS_CLRI (8 bytes) */
	struct {
		struct hdr h;
		ucard2  nwds;           /* number of words of bits */
	} b;

	/* FS_OINODE (40 bytes) */
	struct {
		struct hdr h;
		ucard2  ino;            /* inumber */
		ucard2  mode;           /* info from inode */
		ucard2  nlink;
		ucard2  uid;
		ucard2  gid;
		card4   size;
		card4   atime;
		card4   mtime;
		card4   ctime;
		ucard2  dev;            /* device file is on */
		ucard2  rdev;           /* maj/min devno */
		card4   dsize;          /* dump size if packed */
	} oi;

	/* FS_INODE and FS_DINODE (48 bytes) */
	struct {
		struct hdr h;
		ucard2  ino;            /* inumber */
		ucard2  mode;           /* info from inode */
		ucard2  nlink;
		ucard2  uid;
		ucard2  gid;
		card4   size;
		card4   atime;
		card4   mtime;
		card4   ctime;
		ucard2  devmaj;         /* device file is on */
		ucard2  devmin;
		ucard2  rdevmaj;        /* maj/min devno */
		ucard2  rdevmin;
		card4   dsize;          /* dump size if packed */
		card4   pad;
	} i;

	/* FS_ONAME (40 bytes, without name) */
	/* must be exactly like FS_OINODE except name at end */
	struct {
		struct hdr h;
		ucard2  ino;
		ucard2  mode;
		ucard2  nlink;
		ucard2  uid;
		ucard2  gid;
		card4   size;
		card4   atime;
		card4   mtime;
		card4   ctime;
		ucard2  dev;
		ucard2  rdev;
		card4   dsize;
		char    name[DUMNAME];  /* file name given by user */
	} on;

	/* FS_NAME (48 bytes, without name) */
	/* must be exactly like FS_INODE except name at end */
	struct {
		struct hdr h;
		ucard2  ino;
		ucard2  mode;
		ucard2  nlink;
		ucard2  uid;
		ucard2  gid;
		card4   size;
		card4   atime;
		card4   mtime;
		card4   ctime;
		ucard2  devmaj;         /* device file is on */
		ucard2  devmin;
		ucard2  rdevmaj;        /* maj/min devno */
		ucard2  rdevmin;
		card4   dsize;
		card4   pad;
		char    name[DUMNAME];  /* file name given by user */
	} n;

	/* FS_NAME_X (64 bytes, without name) */
	/* just like FS_NAME except most fields changed in 
	 * Version 3.(from ushort to unsigned long)
	 */
	struct {
		struct hdr h;
		card2   nlink;
		ucard4  ino;
		ucard4  mode;
		ucard4  uid;
		ucard4  gid;
		card4   size;
		card4   atime;
		card4   mtime;
		card4   ctime;
		ucard4  devmaj;         /* device file is on */
		ucard4  devmin;
		ucard4  rdevmaj;        /* maj/min devno */
		ucard4  rdevmin;
		card4   dsize;
		card4   pad;
		char    name[DUMNAME];  /* file name given by user */
	} nx;

	/* FS_NAME_LF (72 bytes, without name) */
	/* just like FS_NAME_X except size & dsize are 64 bits.
	 */
	struct {
		struct  hdr h;
		card2    nlink;
		ucard4   ino;
		ucard4   mode;
		ucard4   uid;
		ucard4   gid;
		card8    size;
		card4    atime;
		card4    mtime;
		card4    ctime;
		ucard4   devmaj;         /* device file is on */
		ucard4   devmin;
		ucard4   rdevmaj;        /* maj/min devno */
		ucard4   rdevmin;
		card4    pad;            /* pad goes here for alignment */
		card8    dsize;
		char     name[DUMNAME2];  /* file name given by user */
	} nlf;

	/* FS_END or FS_VOLEND */
	struct {
		struct hdr h;
	} e;


	/* Obsolete format, needed to decipher some version 2 by name
	   backups */
	/* FS_DS */
	struct {
		struct hdr h;
		char	nid[8];
		char	qdir[2];	/* makes it 2 dwords */
	} ds;

};

/* security header: indicates size of acl and pcl headers which immediately follow it */
struct sac_rec {
		ucard4 aclsize;		/* size of acl in double words */
		ucard4 pclsize;		/* size of pcl in double words */
};

/* output device info */

#define DEF_LEV		'9'	/* default dump level	*/
#define A_WHILE		150	/* period between informative comments	*/
#define NTRACKS		1	/* default number of tracks per tape unit */

#define ROOT_FILSYS     "/dev/hd0"
#define DEF_FILSYS      ROOT_FILSYS
#define DEF_MEDIUM	"/dev/rfd0"
#define DEF_DTYP	DD_DISK
#define DEF_CLUSTER	100	/* default tape cluster in 512-byte units */
#define DEF_TLEN        4500    /* default tape length in feet */
#define DEF_TDEN        700     /* default tape density in bytes/inch */
#define IRG             1       /* tape inter-record gap in inches */

#endif /* _H_DUMPRESTOR */
