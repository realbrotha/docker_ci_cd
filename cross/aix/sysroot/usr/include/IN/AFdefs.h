/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/usr/include/IN/AFdefs.h 1.13                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1988,1989              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)80	1.13  src/bos/usr/include/IN/AFdefs.h, libIN, bos53Q, q2008_06B9 1/23/08 17:33:30 */
/*
 * COMPONENT_NAME: LIBIN
 *
 * FUNCTIONS:
 *
 * ORIGINS: 9,10,27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 */

#ifndef _H_AFDEFS 
#define _H_AFDEFS 

/*
 * Definitions to be included by programs that use "Attribute Files".
 * stdio.h must be included ahead of this include file.
 */

struct ATTR
{       char *  AT_name;
	char *  AT_value;
};

typedef struct ATTR * ATTR_t;

struct AFILE
{       FILE *  AF_iop;
	int     AF_rsiz;
	int     AF_natr;
	char *  AF_cbuf;
	char *  AF_dbuf;
	ATTR_t  AF_catr;
	ATTR_t  AF_datr;
};

typedef struct AFILE * AFILE_t;

#ifdef _NO_PROTO

extern AFILE_t AFopen();
extern int AFclose();
extern int AFrewind();
extern ATTR_t AFnxtrec();
extern ATTR_t AFgetrec();
extern ATTR_t AFfndrec();
extern char * AFgetatr();
extern int AFclear();
extern int AFreadStr();

#else /* ~ _NO_PROTO */

extern AFILE_t AFopen(char *filename, int maxrecsiz, int maxnumatr);
extern int AFclose(register AFILE_t af);
extern int AFrewind(AFILE_t af);
extern ATTR_t AFnxtrec(register AFILE_t af);
extern ATTR_t AFgetrec(register AFILE_t af, char *name);
extern ATTR_t AFfndrec(register AFILE_t af, ATTR_t pattern);
extern char * AFgetatr(register ATTR_t at, char *name);
extern int AFclear(AFILE_t af);
extern int AFreadStr(char *instr, char **outstr);

#endif /* _NO_PROTO */
#endif /* _H_AFDEFS */
