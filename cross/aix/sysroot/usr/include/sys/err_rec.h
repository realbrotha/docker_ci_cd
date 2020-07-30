/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53E src/bos/kernel/sys/err_rec.h 1.14                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1993          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)68     1.14  src/bos/kernel/sys/err_rec.h, cmderrlg, bos53E, e2005_27D5 7/7/05 11:21:23 */


/*
 * COMPONENT_NAME:            include/sys/err_rec.h
 *
 * FUNCTIONS: header file for system error log entry
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1993
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_ERR_REC
#define _H_ERR_REC

#ifdef __cplusplus
extern "C" {
#endif

#define ERR_FALSE 0
#define ERR_TRUE  1

#define ERRSET_DESCRIPTION 1
#define ERRSET_PROBCAUSES  2
#define ERRSET_USERCAUSES  3
#define ERRSET_INSTCAUSES  4
#define ERRSET_FAILCAUSES  5
#define ERRSET_RECACTIONS  6
#define ERRSET_DETAILDATA  7
#define NERRSETS           7

#define ERR_NAMESIZE 16

struct err_rec0 {
	unsigned error_id;
	char     resource_name[ERR_NAMESIZE];
};

struct err_rec {
	unsigned error_id;
	char     resource_name[ERR_NAMESIZE];
	char     detail_data[1];
};
#define ERR_REC_SIZE (sizeof(struct err_rec0))

/*
 * ERR_REC_MAX is the maximum amount of detail data that can be logged.
 * However, due to non-volatile memory constraints, it is possible for an
 * entry with more than 2048 bytes of detail data to be truncated across a
 * reboot in certain circumstances.
 * Entries with more than 2048 bytes of detail data are intended for
 * restricted system use only.
 */
#define ERR_REC_MAX  4096

#define ERR_REC_MAX_SIZE (ERR_REC_SIZE + ERR_REC_MAX)

#define ERR_REC(N) \
struct { \
	unsigned error_id; \
	char     resource_name[ERR_NAMESIZE]; \
	char     detail_data[N]; \
}

#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)
void errsave(struct err_rec *ep, int len);
void errlast(struct err_rec *ep, int len);
void errlast_log(struct err_rec *ep, int len);
void errresume(void);
#endif

#ifndef _KERNEL
#ifdef _NO_PROTO
extern int errlog();
#else
extern int errlog(void *buf, int len);
#endif
#endif /* !_KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* _H_ERR_REC */
