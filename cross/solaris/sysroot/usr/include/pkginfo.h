/*	Copyright (c) 1984, 1986, 1987, 1988, 1989 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ifndef	_PKGINFO_H
#define	_PKGINFO_H

#pragma ident	"@(#)pkginfo.h	1.9	94/08/02 SMI"	/* SVr4.0 1.5.1.2 */

#ifdef	__cplusplus
extern "C" {
#endif

#define	PI_INSTALLED 	0
#define	PI_PARTIAL	1
#define	PI_PRESVR4	2
#define	PI_UNKNOWN	3
#define	PI_SPOOLED	4

struct pkginfo {
	char	*pkginst;
	char	*name;
	char	*arch;
	char	*version;
	char	*vendor;
	char	*basedir;
	char	*catg;
	char	status;
};

extern char	*pkgdir;

#ifdef __STDC__
extern char	*pkgparam(char *, char *);
extern int	pkginfo(struct pkginfo *, char *, ...),
		pkgnmchk(char *, char *, int);
#else
extern char	*pkgparam();
extern int	pkginfo(),
		pkgnmchk();
#endif	/* __STDC__ */

#ifdef	__cplusplus
}
#endif

#endif	/* _PKGINFO_H */
