/* @(#)49	1.11  src/bos/usr/include/dbm.h, libdbm, bos530 6/3/97 09:30:14 */
/* 
 * COMPONENT_NAME: (LIBDBM) Data Base Management Library
 * 
 * FUNCTIONS: 
 *
 * ORIGINS: 26 
 *
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	(#)dbm.h	5.1 (Berkeley) 3/27/86
 */

#ifndef _H_DBM
#define _H_DBM

#ifndef NULL
/*
 * this is lunacy, we no longer use it (and never should have
 * unconditionally defined it), but, this whole file is for
 * backwards compatability - someone may rely on this.
 */
#define	NULL    0
#endif

#include <ndbm.h>

datum	fetch(datum);
datum	firstkey(void);
datum	nextkey(datum);

#endif /* _H_DBM */
