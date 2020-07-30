/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/net/frca.h 1.4                                   */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2000,2001          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)48	1.4  src/bos/kernel/net/frca.h, sysxfrca, bos530 9/21/01 11:50:34 */
#ifndef _FRCA_H_
#define _FRCA_H_

#include <sys/types.h>
#include <netinet/in.h>

/*
* by default logging will be turned on at initialization time unless the
* FCTRL_LOGINITMODE_OFF flag is set
*
* if listenSocket isn't well defined then it'll default to {AF_INET,0.0.0.0,80}
*
* if serverName exceeds 128 bytes then it won't be send regardless of the
* FCTRL_SENDSERVERHEADER bit in flags
* 
* if logFile exceeds 128 bytes or doesn't specify an absolute path name
* then it defaults to /tmp/frca.log.0; if the logfile exceeds 1gb in size
* frca will switch over to the next logfile, e.g. /tmp/frca.log.1
*/
typedef struct {
	uint32_t	serverType ;	/* type of FRCA server; always */
					/* FCTRL_SERVERTYPE_HTTP for now */
	uint32_t	flags ;		/* see below */
	uint32_t	nLogBufs ;	/* number of intermediate buffers */
					/* for information logging */
	uint32_t	nMaxConnections ;/* maximum number of of connections */
					/* open at any given point in time */
	int32_t		nListenSockets ;/* length of descriptor array */
	int32_t		*listenSockets ;/* array of listen socket descriptors */
	char		*serverName ;	/* server name to include with the */
					/* "Server:" header */
	char		*logFile ;	/* file that log entries are written */
					/* to; if logFile exceeds 128 bytes */
					/* or doesn't specify an absolute */
					/* path name then it defaults to */
					/* /tmp/frca.log.0 */
} frca_ctrl_create_t ;

/*
* Values for	serverType (frca_ctrl_create_t),
*		cacheType (frca_cache_create_t),
*		cacheEntryType (frca_filespec_t),
* and 
*		assocDataType (frca_assocdata_t)
*/
#define FCTRL_SERVERTYPE_HTTP	1	/* valid frca control type */
#define FCTRL_CACHETYPE_HTTP	1	/* valid frca cache type */
#define FCTRL_CET_HTTPFILE	1	/* valid frca cache entry type */
#define FCTRL_ADT_HTTP		1	/* valid frca associated data type */

/*
* Values for	flags (frca_ctrl_create_t)
*/
#define FCTRL_SENDSERVERHEADER	(1L<<0)	/* include the "Server:" header in */
					/* the HTTP response */
#define FCTRL_LOGMODE		(1L<<1)	/* tell FRCA to evaluate information */
					/* about the state of the logging */
					/* subsystem; either on or off */
#define FCTRL_LOGMODE_ON	(1L<<2)	/* turn logging on */
#define FCTRL_LOGFORMAT		(1L<<3)	/* tell FRCA to evaluate information */
					/* specific to the log format */
#define FCTRL_LOGFORMAT_ECLF	(1L<<4)	/* use extended common log format */
#define FCTRL_LOGFORMAT_VHOST	(1L<<5)	/* include virtual host	information */
					/* in log entry */

typedef struct {
	uint32_t	cacheType ;	/* type of FRCA cache */
	uint32_t	nMaxEntries ;	/* maximum number of entries allowed */
} frca_cache_create_t ;

typedef struct {
	uint32_t	cacheEntryType ;/* type of cache entry */
	char		*fileName ;	/* absolute pathname to file content */
	char		*searchKey ;	/* 'abs_path' part of an HTTP url */
					/* according to 3.2.2 in RFC 2616 */
	char		*virtualHost ;	/* virtual host this entry belongs to */
} frca_filespec_t ;

typedef struct {
	uint32_t	assocDataType ;	/* type of associated data */
	char		*contentType ;	/* HTTP content type */
	char		*contentEncoding ;/* HTTP content encoding */
	char		*contentLanguage ;/* HTTP content languate */
	char		*contentCharset ;/* HTTP content character set */
	char		*eTag ;		/* HTTP entity tag */
	char		*expires ;	/* HTTP expiration date */
	char		*cacheControl ;	/* HTTP cache control information */
} frca_assocdata_t ;

/*
* API prototypes
*/
extern int32_t	FrcaCtrlCreate ( int32_t *, frca_ctrl_create_t * ) ;
extern int32_t	FrcaCtrlDelete ( int32_t ) ;
extern int32_t	FrcaCtrlStart ( int32_t ) ;
extern int32_t	FrcaCtrlStop ( int32_t ) ;
extern int32_t	FrcaCacheCreate ( int32_t *, int32_t, frca_cache_create_t * ) ;
extern int32_t	FrcaCacheDelete ( int32_t, int32_t ) ;
extern int32_t	FrcaCacheLoadFile ( int32_t, int32_t, frca_filespec_t *,
			frca_assocdata_t * ) ;
extern int32_t	FrcaCacheUnloadFile ( int32_t, int32_t, frca_filespec_t * ) ;
extern int32_t	FrcaCtrlLog ( int32_t, uint32_t ) ;
extern int32_t	FrcaCtrlGetVersion ( int32_t, int32_t * ) ;

#endif /* _FRCA_H_ */
