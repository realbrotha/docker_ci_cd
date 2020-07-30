/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/usr/include/stdio.h 1.46.4.2                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1985,1994              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)77  1.46.4.2  src/bos/usr/include/stdio.h, libcio, bos53X, x2009_43A9 7/29/09 09:16:12 */
#ifdef _POWER_PROLOG_
/*
 * COMPONENT_NAME: (INCSTD) Standard Include Files
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27,71
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1996
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#endif /* _POWER_PROLOG_ */

/*
 * (c) Copyright 1990, 1991, 1992 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */

#ifndef _H_STDIO
#define _H_STDIO

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 *
 *      The ANSI and POSIX standards require that certain values be in stdio.h.
 *      It also requires that if _ANSI_C_SOURCE or _POSIX_SOURCE is defined
 *	then ONLY those values are present. This header includes all the ANSI 
 *	and POSIX required entries.
 *      In addition other entries for the AIX system are included.
 *
 */

#ifdef _ANSI_C_SOURCE

/*
 * 	The following definitions are included in <sys/types.h>.  They
 *	are also included here to comply with ANSI standards.
 */

#ifndef NULL
#define NULL	0
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long	size_t;
#endif

#ifndef _FPOS_T
#define	_FPOS_T

#ifdef _LARGE_FILES
typedef long long fpos_t;
#else
typedef long	fpos_t;
#endif /* _LARGE_FILES */

#ifdef _LARGE_FILE_API
typedef long long fpos64_t;
#endif /* _LARGE_FILE_API */

#endif /* _FPOS_T */

#ifdef _LARGE_FILES
#define fseeko fseeko64
#define ftello ftello64
#define fgetpos fgetpos64
#define fsetpos fsetpos64
#define fopen fopen64
#define freopen freopen64
#endif /* _LARGE_FILES */

/*
 *	The definition of TMP_MAX is included in <sys/limits.h>.  It is
 *	also defined here to comply with ANSI standards.
 */

#ifndef TMP_MAX
#define	TMP_MAX		16384
#endif

#define FOPEN_MAX 	32767

#define FILENAME_MAX 	255
#define BUFSIZ		4096
#define _P_tmpdir       "/tmp/"
/* the value of L_tmpnam should be (sizeof(_P_tmpdir) + 15) */
#define L_tmpnam    21

/*
 * _IOLBF means that a file's output will be buffered line by line
 * In addition to being flags, _IONBF, _IOLBF and _IOFBF are possible
 * values for "type" in setvbuf.
 */
#define _IOFBF		0000
#define _IOLBF		0100
#define _IONBF		0004


#ifndef EOF
#define EOF		(-1)
#endif

#ifndef SEEK_SET
#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2
#endif

#if defined(__64BIT__) || defined(__ia64)
typedef struct {
	unsigned char	*_ptr;
	unsigned char	*_base;
	unsigned char   *_bufendp;
	char	*__newbase;
	void	*_lock;
	int	_cnt;
	int	_file;
	int	__stdioid;
	short	_flag;
	short	_unused;
	long	_unused1[4];
} FILE;
#else /* 32-bit POWER */
typedef struct {
	unsigned char	*_ptr;
	int	_cnt;
	unsigned char	*_base;
	unsigned char   *_bufendp;
	short	_flag;
	short	_file;
	int	__stdioid;
	char	*__newbase;
	void	*_lock;
} FILE;
#endif /* __64BIT__ || __ia64 */

#define _IOEOF		0020
#define _IOERR		0040
#define _NIOBRW		16
extern FILE	_iob[_NIOBRW];

#define stdin		(&_iob[0])
#define stdout		(&_iob[1])
#define stderr		(&_iob[2])

#ifdef	_NONSTD_TYPES
extern int 		fread();
extern int		fwrite();
#elif	defined	_NO_PROTO
extern size_t 		fread();
extern size_t		fwrite();
#else	/* _NONSTD_TYPES, _NO_PROTO */
extern size_t 		fread(void *__restrict__, size_t, size_t, FILE *__restrict__);
extern size_t		fwrite(const void *__restrict__, size_t, size_t,FILE *__restrict__);
#endif	/* _NONSTD_TYPES, _NO_PROTO */

#ifdef _ISOC99_SOURCE
#include <va_list.h>  /* needed for v*scanf */
#ifdef _NO_PROTO
extern int  vscanf();
extern int  vfscanf();
extern int  vsscanf();
#else
extern int  vscanf(const char *__restrict__, va_list);
extern int  vfscanf(FILE *__restrict__, const char *__restrict__, va_list);
extern int  vsscanf(const char *__restrict__, const char *__restrict__, va_list);
#endif
#endif

#ifdef _NO_PROTO
extern int	__filbuf();
extern int	__flsbuf();
extern int	ferror();
extern int	feof();
extern void	clearerr();
extern int	putchar();
extern int	getchar();
extern int	putc();
extern int	getc();
extern int	remove();
extern int	rename();
extern FILE 	*tmpfile();
extern char 	*tmpnam();
extern int 	fclose();
extern int 	fflush();
extern FILE *	fopen();
extern FILE *	freopen();
extern void 	setbuf();
extern int 	setvbuf();
extern int	fprintf(); 
extern int	fscanf();
extern int	printf();
extern int	scanf();
extern int	sprintf(); 
extern int	sscanf(); 
extern int	vfprintf();
extern int	vprintf(); 
extern int	vsprintf();
extern int 	fgetc();
extern char *	fgets();
extern int 	fputc();
extern int 	fputs();
extern char 	*gets();
extern int 	puts();
extern int	ungetc();
extern int	fgetpos();
extern int 	fseek();
extern int	fsetpos();
extern long	ftell();
extern void	rewind();
extern void 	perror(); 

#else			/* use ANSI C required prototypes */

extern int	__flsbuf(unsigned char, FILE *);
extern int	__filbuf(FILE *);
extern int 	ferror(FILE *);
extern int 	feof(FILE *);
extern void 	clearerr(FILE *);
extern int 	putchar(int);
extern int 	getchar(void);
extern int 	putc(int, FILE *);
extern int 	getc(FILE *);
extern int	remove(const char *);
extern int	rename(const char *, const char *);
extern FILE 	*tmpfile(void);
extern char 	*tmpnam(char *);
extern int 	fclose(FILE *);
extern int 	fflush(FILE *);
extern FILE *	fopen(const char *__restrict__, const char *__restrict__);
extern FILE *	freopen(const char *__restrict__, const char *__restrict__, FILE *__restrict__);
extern void 	setbuf(FILE *__restrict__, char *__restrict__);
extern int 	setvbuf(FILE *__restrict__, char *__restrict__, int, size_t);
extern int	fprintf(FILE *__restrict__, const char *__restrict__, ...); 
extern int	fscanf(FILE *__restrict__, const char *__restrict__, ...);
extern int	printf(const char *__restrict__, ...); 
extern int	scanf(const char *__restrict__, ...); 
extern int	sprintf(char *__restrict__, const char *__restrict__, ...); 
#if (_XOPEN_SOURCE >= 500) || defined(_ISOC99_SOURCE)
extern int	snprintf(char *__restrict__, size_t, const char *__restrict__, ...);
#endif /* _XOPEN_SOURCE >= 500 */
extern int	sscanf(const char *__restrict__, const char *__restrict__, ...); 

#ifdef _VA_LIST
extern int	vfprintf(FILE *__restrict__, const char *__restrict__, va_list);
extern int	vprintf(const char *__restrict__, va_list); 
extern int	vsprintf(char *__restrict__, const char *__restrict__, va_list);
#if (_XOPEN_SOURCE >= 500) || defined(_ISOC99_SOURCE)
extern int	vsnprintf(char *__restrict__, size_t, const char *__restrict__, va_list);
#endif /* _XOPEN_SOURCE >= 500 || defined(_ISOC99_SOURCE) */
#else
#define _HIDDEN_VA_LIST         /* define a type not in the namespace */
#include <va_list.h>
extern int	vfprintf(FILE *__restrict__, const char *__restrict__, __va_list);
extern int	vprintf(const char *__restrict__, __va_list); 
extern int	vsprintf(char *__restrict__, const char *__restrict__, __va_list);
#if (_XOPEN_SOURCE >= 500) || defined(_ISOC99_SOURCE)
extern int	vsnprintf(char *__restrict__, size_t, const char *__restrict__, __va_list);
#endif /* _XOPEN_SOURCE >= 500 || defined(_ISOC99_SOURCE) */
#endif /* _VA_LIST */

extern int 	fgetc(FILE *);
extern char *	fgets(char *__restrict__, int, FILE *__restrict__);
extern int 	fputc(int, FILE *);
extern int 	fputs(const char *__restrict__, FILE *__restrict__);
extern char 	*gets(char *);
extern int 	puts(const char *);
extern int	ungetc(int, FILE *);
extern int	fgetpos(FILE *__restrict__, fpos_t *__restrict__);
extern int 	fseek(FILE *, long int, int);
extern int	fsetpos(FILE *, const fpos_t *);
extern long	ftell(FILE *);
extern void	rewind(FILE *);
extern void 	perror(const char *); 

#if defined(_ALL_SOURCE) || _XOPEN_SOURCE >= 500
/*
 * These are here because the defines below cause problems
 */
extern int	getc_unlocked(FILE *);
extern int	getchar_unlocked(void);
extern int	putc_unlocked(int, FILE *);
extern int	putchar_unlocked(int);
#endif /* _ALLSOURCE || _XOPEN_SOURCE>=500 */

#endif /* _NO_PROTO */

#ifndef __cplusplus
/* C++ standards require that getc/putc/getchar/putchar be functions.
 * So, only define the thread-safe and non-thread-safe macros if
 * __cplusplus is not defined.
 */

#ifdef _THREAD_SAFE
/*
 * The default for getc and putc are locked for compatibility with 
 * Posix P1003.4a
 * By defining _STDIO_UNLOCK_CHAR_IO before including this
 * file, the default action is changed to unlocked putc and getc.
 * A file lock can still be placed around a block of putc's or getc's
 * regardless of the locking mode, and invoking the locked or
 * unlocked version directly always overrides the default action.
 */
#ifndef _STDIO_UNLOCK_CHAR_IO
#define getc(p)			fgetc(p)
#define putc(x, p)		fputc(x, p)
#else	/* _STDIO_UNLOCK_CHAR_IO */
#define getc(p)			getc_unlocked(p)
#define putc(x, p)		putc_unlocked(x, p)
#endif	/* _STDIO_UNLOCK_CHAR_IO */

#else /* _THREAD_SAFE */

#define getc(__p)       (((!((__p)->_flag & 0xC000)) && \
                        ((__p)->_flag = ((__p)->_flag  & 0x3FFF) | 0x8000)),\
                        (--(__p)->_cnt < 0 ? __filbuf(__p) : (int) *(__p)->_ptr++))
#define putc(__x, __p)  (((!((__p)->_flag & 0xC000)) && \
                        ((__p)->_flag = ((__p)->_flag  & 0x3FFF) | 0x8000)),\
                        (--(__p)->_cnt < 0 ? \
                        __flsbuf((unsigned char) (__x), (__p)) : \
                        (int) (*(__p)->_ptr++ = (unsigned char) (__x))))
#endif /* _THREAD_SAFE */

#define getchar()	getc(stdin)
#define putchar(__x)	putc((__x), stdout)

#endif /* __cplusplus */

#ifdef _THREAD_SAFE
#define getc_unlocked(p)        (((!((p)->_flag & 0xC000)) && \
                                ((p)->_flag = ((p)->_flag  & 0x3FFF) | 0x8000)),\
                                (--(p)->_cnt < 0 ? __filbuf(p) : (int) *(p)->_ptr++))
#define getchar_unlocked()	getc_unlocked(stdin)

#ifdef _ALL_SOURCE
#define getchar_locked()	fgetc(stdin)
#define getc_locked(p)          fgetc(p)
#endif	

#define putc_unlocked(x, p)     (((!((p)->_flag & 0xC000)) && \
                                ((p)->_flag = ((p)->_flag  & 0x3FFF) | 0x8000)),\
                                (--(p)->_cnt < 0 ? \
                                __flsbuf((unsigned char) (x), (p)) : \
                                (int) (*(p)->_ptr++ = (unsigned char) (x))))
#define putchar_unlocked(x)	putc_unlocked(x,stdout)

#ifdef _ALL_SOURCE
#define putc_locked(x, p)	fputc(x, p)
#define putchar_locked(x)	putc_locked(x,stdout)
#endif
	
#ifdef _STDIO_UNLOCK_CHAR_IO
/*
 * if _STDIO_UNLOCK_CHAR_IO is not defined, these macros will not be defined
 * and become functions.
 */
#define clearerr(p)		((void) ((p)->_flag &= ~(_IOERR | _IOEOF)))
#define feof(p)			((p)->_flag & _IOEOF)
#define ferror(p)		((p)->_flag & _IOERR)
#endif /* _STDIO_UNLOCK_CHAR_IO */

#ifdef _ALL_SOURCE
#define clearerr_unlocked(p)	((void) ((p)->_flag &= ~(_IOERR | _IOEOF)))
#define feof_unlocked(p)	((p)->_flag & _IOEOF)
#define ferror_unlocked(p)	((p)->_flag & _IOERR)
#define fileno_unlocked(p)	((p)->_file)
#endif
	
#else /* Not _THREAD_SAFE */

#define clearerr(__p)	((void) ((__p)->_flag &= ~(_IOERR | _IOEOF)))
#define feof(__p)		((__p)->_flag & _IOEOF)
#define ferror(__p)	((__p)->_flag & _IOERR)
#endif /* _THREAD_SAFE */

#endif /*_ANSI_C_SOURCE */


#ifdef _POSIX_SOURCE
/*
 *   The following are values that have historically been in stdio.h.
 *
 *   They are a part of the POSIX defined stdio.h and therefore are
 *   included when _POSIX_SOURCE and _XOPEN_SOURCE are defined.
 *
 */

#ifndef _H_TYPES
#include <sys/types.h>
#endif

#define L_ctermid	9
#if (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE<200112L) || defined(_ALL_SOURCE)
#define L_cuserid	9
#endif
	
#ifdef _NO_PROTO
extern int 	fileno();
extern FILE 	*fdopen();
extern char	*ctermid();
extern FILE 	*popen();
extern int 	pclose();
#else
extern int 	fileno(FILE *);
extern FILE 	*fdopen(int,const char *);
extern char	*ctermid(char *);
extern FILE 	*popen(const char *, const char *);
extern int 	pclose(FILE *);

#if defined(_ALL_SOURCE) || _XOPEN_SOURCE >= 500
extern void	flockfile(FILE *);
extern void	funlockfile(FILE *);
extern int	fseeko(FILE *, off_t, int);
extern off_t	ftello(FILE *);
extern int	ftrylockfile(FILE *);
extern void	funlockfile(FILE *);
#endif /* _ALLSOURCE || _XOPEN_SOURCE>=500 */

#endif /* _NO_PROTO */

#if !defined(_THREAD_SAFE) || !defined(_STDIO_UNLOCK_CHAR_IO)
#define fileno(__p)	((__p)->_file)
#endif

#endif /* _POSIX_SOURCE */

#ifdef _XOPEN_SOURCE

#include <va_list.h>	/* va_list must be define in XPG4 */

#if (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE<200112L) || defined(_ALL_SOURCE)
extern	char	*optarg;
extern	int	opterr;
extern	int	optind;
extern	int	optopt;
#endif

#define P_tmpdir	_P_tmpdir

#ifdef _NO_PROTO
#if (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE<200112L) || defined(_ALL_SOURCE)
extern int 	getw();
extern int      getopt();
extern char     *cuserid();
extern int 	putw();
#endif
extern char 	*tempnam();

#else
#if (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE<200112L) || defined(_ALL_SOURCE)
extern int 	getw(FILE *);
extern int      getopt(int, char * const [], const char*);
extern char     *cuserid(char *);
extern int 	putw(int, FILE *);
#endif
extern char 	*tempnam(const char*, const char*);

#endif /* _NO_PROTO */


#endif /*_XOPEN_SOURCE */

#ifdef _ALL_SOURCE

#ifndef _H_LIMITS
#include <sys/limits.h>   /* limits.h not allowed by Posix.1a.  Must be in _ALL_SOURCE */
#endif

#ifdef _LARGE_FILE_API
extern int fgetpos64(FILE *, fpos64_t *);
extern FILE *fopen64(const char *, const char *);
extern FILE *freopen64(const char *, const char *, FILE *);
extern int fseeko64(FILE *, off64_t, int);
extern int fsetpos64(FILE *, const fpos64_t *);
extern off64_t ftello64(FILE *);
#endif /* _LARGE_FILE_API */

#ifdef _NO_PROTO
extern void setbuffer();
extern void setlinebuf();
#else /* _NO_PROTO */
extern void setbuffer(FILE *, char *, size_t);
extern void setlinebuf(FILE *);
#endif /* _NO_PROTO */

#ifndef WEOF
#define WEOF		(-1)
#endif

#define _NFILE 		32767

			/* For Dynamic iob's. Make sure _NFILE is       */
  			/* a multiple of _NIOBRW (IOB Row).   		*/

#define _NRWS		(_NFILE / _NIOBRW )+1
			/* Number of iob rows should be equal 		*/
			/* to (_NFILE / _NIOBRW ) + 1.  The extra 	*/
			/* row ensures insures that the _NFILE+1th 	*/
			/* fopen fails because of open(). 		*/

/* buffer size for multi-character output to unbuffered files */
#define _SBFSIZ 8

/* _IOFBF(defined above)000000 */
#define _IOREAD		000001
#define _IOWRT		000002
/* _IONBF(defined above)000004 */
#define _IOMYBUF	000010
/* _IOEOF(defined above)000020 */
/* _IOERR(defined above)000040 */
/* _IOLBF(defined above)000100 */
#define _IORW		000200
#define	_IONOFD		000400
#define	_IOUNGETC	001000
#define	_IOCLOSE	002000
#ifdef _THREAD_SAFE
#define _IOINUSE	002000
#endif /* _THREAD_SAFE */
#define	_IONONSTD	004000
#define _IOISTTY        010000
/* _IOReserved1         020000 */
/* _IOReserved2         040000 */
/* _IOReserved3	       0100000 */
/* Orientation Top 2 bits                */
/* These defines are not used, but are   */
/* here to mark the bits as used         */
#define _IO_BYTE       0200000
#define _IO_WIDE       0400000

/*
 * Macros used to set the orientation of the stream.  The upper 2 bits of
 * the _flag member of the FILE structure are used to hold the information.
 * If the bits are 0 then the orientation has not been set.  '10b' is used
 * for byte and '01b' is used for wide.  This may change in the future so any
 * applications that use the following macros may not be binary compatible.  The
 * function fwide() should be use to set and check the current streem orientation.
 */
#define _SET_BYTE(__stream) ((!((__stream)->_flag & 0xC000)) && ((__stream)->_flag = ((__stream)->_flag & 0x3FFF) | 0x8000))
#define _SET_WIDE(__stream) ((!((__stream)->_flag & 0xC000)) && ((__stream)->_flag = ((__stream)->_flag & 0x3FFF) | 0x4000))

#define _bufend(__p)	((__p)->_bufendp)
#define _bufsiz(__p)	(_bufend(__p) - (__p)->_base)

#endif /* _ALL_SOURCE */

#ifdef __cplusplus
}
#endif

#endif /* _H_STDIO */

