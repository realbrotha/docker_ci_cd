/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/nlist.h 1.13                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1994          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)99       1.13  src/bos/usr/include/nlist.h, cmdld, bos530 12/8/97 12:12:14 */
#ifndef _H_NLIST
#define _H_NLIST
/*
 * COMPONENT_NAME: (CMDLD) XCOFF object file format definition
 *
 * STRUCTURES: nlist, nlist64
 * FUNCTIONS:  nlist(), nlist64()
 *
 * ORIGINS: 3, 27
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

/* symbol table entry structure */

/* A 32-bit program must use nlist64(), and struct nlist64, to read an
   XCOFF64 file.  A 64-bit program can use either nlist() or nlist64()
   to read either XCOFF32 or XCOFF64 object files. */

struct nlist {
        union {
                char    *_n_name;       /* symbol name */
        } _n;
        long            n_value;        /* value of symbol */
        short           n_scnum;        /* section number */
        union {
                unsigned short  _n_type; /* type and derived type */
        } _n_tylc;
        char            n_sclass;       /* storage class */
        char            n_numaux;       /* number of aux. entries */
};

struct nlist64 {
        union {
                char    *_n_name;       /* symbol name */
        } _n;
        long long       n_value;        /* value of symbol */
        short           n_scnum;        /* section number */
        union {
                unsigned short  _n_type; /* type and derived type */
        } _n_tylc;
        char            n_sclass;       /* storage class */
        char            n_numaux;       /* number of aux. entries */
};

/* include file <syms.h> also defines n_name and n_type. */
#ifndef n_name
#define n_name          _n._n_name
#endif  /* n_name */

#ifndef n_type
#define n_type          _n_tylc._n_type
#endif /* n_type */

#ifdef _NO_PROTO
extern int nlist();
extern int nlist64();
extern int knlist();
#else /* _NO_PROTO */
extern int nlist  (const char *, struct nlist *);
extern int nlist64(const char *, struct nlist64 *);
extern int knlist( struct nlist *, int, int );
#endif /* _NO_PROTO */

#ifdef __cplusplus
}
#endif
#endif /* _H_NLIST */
