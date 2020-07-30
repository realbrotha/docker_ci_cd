/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/jcode.h 1.4                                 */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,1991          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)21	1.4  src/bos/usr/include/jcode.h, libcnls, bos530 6/16/90 00:10:47 */
/*
 * COMPONENT_NAME: (LIBCNLS) Standard C Library National Library Support 
 *
 * FUNCTIONS: 
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 *   jcode.h: definitions for jis/sj/uj conversion routines
 */

extern unsigned char
		*cjistosj(),	/* character conversion */
		*cjistouj(),
		*csjtojis(),
		*csjtouj(),
		*cujtojis(),
		*cujtosj(),

		*jistosj(),	/* string conversion */
		*jistouj(),
		*sjtojis(),
		*sjtouj(),
		*ujtojis(),
		*ujtosj();
