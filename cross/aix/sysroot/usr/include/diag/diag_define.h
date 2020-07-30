/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/diag/diag_define.h 1.15                     */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1993,1994          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)13       1.15  src/bos/usr/include/diag/diag_define.h, cmddiag, bos530 2/5/04 10:01:07 */
/*
 *   COMPONENT_NAME: CMDDIAG
 *
 *   FUNCTIONS:
 *
 *   ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1993, 1997
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */


#define MKDEV                   "/usr/sbin/mkdev"
#define RMDEV                   "/usr/sbin/rmdev"
#define CHDEV                   "/usr/sbin/chdev"
#define LSCONS                  "/usr/sbin/lscons"
#define PENABLE                 "/usr/sbin/penable"
#define PSTART                  "/usr/sbin/pstart"
#define PS                      "/usr/bin/ps"
#define PDISABLE                "/usr/sbin/pdisable"
#define VARYOFFVG               "/usr/sbin/varyoffvg"
#define VARYONVG                "/usr/sbin/varyonvg"
#define CHPV                    "/usr/sbin/chpv"
#define LSPV                    "/usr/sbin/lspv"
#define LSCFG                   "/usr/sbin/lscfg"
#define LSLPP                   "/usr/bin/lslpp"
#define INSTALLP                "/usr/sbin/installp"
#define SAVEBASE                "/usr/sbin/savebase"
#define RESTBYNAME              "/usr/sbin/restbyname"
#define TAR                     "/usr/bin/tar"
#define CPIO                    "/usr/bin/cpio"
#define TTY                     "/usr/bin/tty"
#define FIND                    "/usr/bin/find"
#define ERRPT                   "/usr/bin/errpt"
#define FORMAT                  "/usr/sbin/format"
#define LS                      "/usr/bin/ls"
#define RM                      "/usr/bin/rm"
#define EGREP                   "/usr/bin/egrep"
#define GREP                    "/usr/bin/grep"
#define SED                     "/usr/bin/sed"
#define CP                      "/usr/bin/cp"
#define DOSDIR                  "/usr/bin/dosdir"
#define DOSREAD                 "/usr/bin/dosread"
#define DOSWRITE                "/usr/bin/doswrite"
#define BOOTLIST                "/usr/bin/bootlist"
#define	BOOTINFO		"/usr/sbin/bootinfo"
#define SLIBCLEAN               "/usr/sbin/slibclean"
#define LSATTR                  "/usr/sbin/lsattr"
#define CFGMIR                  "/usr/sbin/cfgmir"
#define	RMPATH			"/usr/sbin/rmpath"

#define DSKT_MISSING	-1	/* open returns errno ENOTREADY */
#define DSKT_ERROR	-2	/* open returns errno other than ENOTREADY. */
#define	DIAG_NO_MEDIA	-3  	/* load_optical_media returns errno ENOTREADY*/
