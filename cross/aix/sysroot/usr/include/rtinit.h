/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/rtinit.h 1.2                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1996               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)50	1.2  src/bos/usr/include/rtinit.h, libld, bos530 1/12/96 17:55:44 */
/*
 *   COMPONENT_NAME: libld
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1996
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_RTINIT
#define _H_RTINIT

/* Name of loader-section symbol for __RTINIT structure.
   If symbol exists, it must be first. */
#define RTINIT_NAME "__rtinit"

typedef struct __rtinit_descriptor __RTINIT_DESCRIPTOR;
typedef struct __rtinit {
    int		(*rtl)();		/* Pointer to runtime linker */
    int		init_offset;		/* Offset to array of init functions
					   (0 if none). */
    int		fini_offset;		/* Offset to array of fini functions
					   (0 if none). */
    int		__rtinit_descriptor_size; /* Size of __RTINIT_DESCRIPTOR.
					   This value should be used instead
					   of sizeof(__RTINIT_DESCRIPTOR). */
} __RTINIT;

typedef void __INITFINI_T(const void *,	/* This parameter is NULL if the module
					   being initialized was loaded at exec
					   time.  Otherwise, a call to load()
					   is in progress, and this argument
					   will be the value to be returned by
					   load(). */
	      __RTINIT *,		/* Pointer to this module's
					   __rtinit symbol. */
	      __RTINIT_DESCRIPTOR *);	/* Pointer to this function's
					   __RTINIT_DESCRIPTOR. */

struct __rtinit_descriptor {
    __INITFINI_T	*f;		/* Init/fini function. */
    int			name_offset;	/* Offset (within __rtinit symbol)
					   to name of function. */
    unsigned char	flags;		/* Flags */
#define _RT_CALLED 0x80			/* If flag is set, function is not
					   called.  Otherwise, flag is set
					   before calling function. */
};

#endif /* _H_RTINIT */
