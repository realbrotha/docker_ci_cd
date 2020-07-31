/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/isc/tree.h 1.1                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1997               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* tree.h - declare structures used by tree library
 *
 * vix 22jan93 [revisited; uses RCS, ANSI, POSIX; has bug fixes]
 * vix 27jun86 [broken out of tree.c]
 *
 * $Id: tree.h,v 8.2 1996/10/25 18:11:03 vixie Exp $
 */


#ifndef	_TREE_H_INCLUDED
#define	_TREE_H_INCLUDED


#ifndef __P
# if defined(__STDC__) || defined(__GNUC__)
#  define __P(x) x
# else
#  define __P(x) ()
# endif
#endif

/*
 * tree_t is our package-specific anonymous pointer.
 */
#if defined(__STDC__) || defined(__GNUC__)
typedef	void *tree_t;
#else
typedef	char *tree_t;
#endif


typedef	struct tree_s {
		tree_t		data;
		struct tree_s	*left, *right;
		short		bal;
	}
	tree;


void	tree_init	__P((tree **));
tree_t	tree_srch	__P((tree **, int (*)(), tree_t));
tree_t	tree_add	__P((tree **, int (*)(), tree_t, void (*)()));
int	tree_delete	__P((tree **, int (*)(), tree_t, void (*)()));
int	tree_trav	__P((tree **, int (*)()));
void	tree_mung	__P((tree **, void (*)()));


#endif	/* _TREE_H_INCLUDED */