/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/ldfcn.h 1.18                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,1998          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)47	1.18  src/bos/usr/include/ldfcn.h, cmdaout, bos530 7/30/98 16:49:56 */
/*	src/bos/usr/include/ldfcn.h, cmdaout, bos530 - 98/07/30 - 16:49:56  	*/
/*
 * COMPONENT_NAME: CMDAOUT
 *
 * FUNCTIONS: none
 *
 * ORIGINS: 3, 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_LDFCN
#define _H_LDFCN


/*
 * This file must be compiled with the following capabilities enabled:
 *	"long long" data types	(8-byte long-long types in C)
 * Large files support is also intended.  Certain structure members
 * below require 64-bit quantities when accessing large files, but
 * will work with 32-bit values (files less than 2GB in size).  In
 * this case, prototypes for any function call using any of these
 * structure members is recommended.
 */

#ifndef	_LONG_LONG
#error	-qlonglong must be used
#endif


#include <filehdr.h>
#include <scnhdr.h>
#include <linenum.h>
#include <syms.h>


#ifndef LDFILE


/*
 * Composite data structure to hold information about the file
 * to which an LDFILE points.  This members are large enough
 * to contain values for both 32-bit and 64-bit XCOFF files.
 */
typedef	struct	_ldheader
{
	unsigned short	f_magic;	/* magic number */
	unsigned short	f_nscns;	/* number of sections */
	_LONG32		f_timdat;	/* time & date stamp */
	long long	f_symptr;	/* File offset to symbol table. */
	int		f_nsyms;
	unsigned short	f_opthdr;	/* Size of the auxiliary header */
	unsigned short	f_flags;	/* flags */
} _ldheader;



struct	ldfile {
	int		_fnum_; /* so each instance of an LDFILE is unique */
	unsigned short	type;	/* indicator of the type of the file */
	unsigned short	flags;	/* flag bits */
				/* For TYPE() == ARTYPE:             */
#define	AR_TYPE_BIG	0x01 	/*    4.3 big archive format         */
	long long	offset; /* absolute offset to the start of the file */
	long long	ar_off; /* archive header offset for file (or zero) */
	long long	ar_end_off; /* offset of first ar hdr after the normal  */
				/* headers.				    */
	_ldheader	header;	/* the file header of the opened file */
	FILE		*ioptr; /* system I/O pointer value */
	int		resvd[10]; /* future enhancements */
};

/*
 *	provide a structure "type" definition, and the associated
 *	"attributes"
 */

#define	LDFILE		struct ldfile
#define IOPTR(x)	x->ioptr
#define OFFSET(x)	x->offset
#define TYPE(x)		x->type
#define LDFLAGS(x)	x->flags
#define	HEADER(x)	x->header
#define LDFSZ		sizeof(LDFILE)
#define	AR_OFF(x)	x->ar_off
#define	AR_END_OFF(x)	x->ar_end_off

/*
 *	define various values of TYPE(ldptr)
 */
#define ARTYPE	0177545


/*
 *	define a structure "type" for an archive header
 */

typedef struct
{
	long long	ar_size;
#ifdef	_LARGE_FILES
	off_t	ar_nxtmem;
	off_t	ar_prvmem;
#else
	long long	ar_nxtmem;
	long long	ar_prvmem;
#endif
	long	ar_date;
	long	ar_uid;
	long	ar_gid;
	long	ar_mode;
	int	ar_namlen;
	char	ar_name[256];
} archdr;
#define	ARCHDR	archdr
#define ARCHSZ	sizeof(ARCHDR)

/*
 *	define some useful symbolic constants
 */

#define SYMTBL	0	/* section number and/or section name of the Symbol Table */

#define	SUCCESS		1
#define	CLOSED		1
#define	FAILURE		0
#define	NOCLOSE		0
#define	BADINDEX	-1L

#define	OKFSEEK		0



#ifdef _NO_PROTO

extern	int	ldaclose();
extern	int	ldahread();
extern	LDFILE	*ldaopen();
extern	int	ldclose();
extern	int	ldfhread();
extern	char	*ldgetname();
extern	int	ldlinit();
extern	int	ldlitem();
extern	int	ldlread();
extern	int	ldlseek();
extern	int	ldnlseek();
extern	int	ldnshread();
extern	int	ldnsseek();
extern	int	ldohseek();
extern	LDFILE	*ldopen();
extern	LDFILE	*lddopen();
extern	int	ldrseek();
extern	int	ldnrseek();
extern	int	ldshread();
extern	int	ldsseek();
extern	int	ldtbseek();
#ifdef	_LARGE_FILES
extern	off_t	ldtbindex();
#else
extern	long long	ldtbindex();
#endif
extern	int	ldtbread();
extern	long	sgetl();
extern	void	sputl();

#else

extern	int	ldaclose( LDFILE * );
extern	int	ldahread( LDFILE *, ARCHDR * );
extern	LDFILE	*ldaopen( char *, LDFILE * );
extern	int	ldclose( LDFILE * );
extern	int	ldfhread( LDFILE *, void * );
extern	char	*ldgetname( LDFILE *, void * );
extern	int	ldlinit( LDFILE *, int );
extern	int	ldlitem( LDFILE *, unsigned int, void * );
extern	int	ldlread( LDFILE *, int, unsigned int, void * );
extern	int	ldlseek( LDFILE *, unsigned short );
extern	int	ldnlseek( LDFILE *, char * );
extern	int	ldnshread( LDFILE *, char *, void * );
extern	int	ldnsseek( LDFILE *, char * );
extern	int	ldohseek( LDFILE * );
extern	LDFILE	*ldopen( char *, LDFILE * );
extern	LDFILE	*lddopen( int, char *, LDFILE * );
extern	int	ldrseek( LDFILE *, unsigned short );
extern	int	ldnrseek( LDFILE *, char * );
extern	int	ldshread( LDFILE *, unsigned short, void * );
extern	int	ldsseek( LDFILE *, unsigned short );
extern	int	ldtbseek( LDFILE * );
#ifdef	_LARGE_FILES
extern	off_t	ldtbindex( LDFILE * );
#else
extern	long long	ldtbindex( LDFILE * );
#endif
extern	int	ldtbread( LDFILE *, int, void * );
extern	long	sgetl( char * );
extern	void	sputl( long, char * );

#endif


/*
 * define symbolic positioning information for FSEEK (and fseek)
 */
#define BEGINNING 0	/* SEEK_SET from unistd.h */
#define CURRENT   1	/* SEEK_CUR   "           */
#define END       2	/* SEEK_END   "           */

/*
 * Define macros to permit the direct use of LDFILE pointers with
 * the standard I/O library procedures.
 */
#define	GETC(ldptr)		getc(IOPTR(ldptr))
#define	GETW(ldptr)		getw(IOPTR(ldptr))
#define	FEOF(ldptr)		feof(IOPTR(ldptr))
#define	FERROR(ldptr)		ferror(IOPTR(ldptr))
#define	FGETC(ldptr)		fgetc(IOPTR(ldptr))
#define	FGETS(s,n,ldptr)	fgets(s,n,IOPTR(ldptr))
#define	FILENO(ldptr)		fileno(IOPTR(ldptr))
#define	FREAD(p,s,n,ldptr)	fread(p,s,n,IOPTR(ldptr))
#define	FSEEK(ldptr,o,p)	fseek(IOPTR(ldptr),(p==BEGINNING)?(OFFSET(ldptr)+o):o,p)
#define	FTELL(ldptr)		ftell(IOPTR(ldptr))
#define	FWRITE(p,s,n,ldptr)	fwrite(p,s,n,IOPTR(ldptr))
#define	REWIND(ldptr)		rewind(IOPTR(ldptr))
#define	SETBUF(ldptr,b)		setbuf(IOPTR(ldptr),b)
#define	UNGETC(c,ldptr)		ungetc(c,IOPTR(ldptr))
#define	STROFFSET(ldptr)	(HEADER(ldptr).f_symptr+HEADER(ldptr).f_nsyms*SYMESZ)

#endif
 
#endif /* _H_LDFCN */
