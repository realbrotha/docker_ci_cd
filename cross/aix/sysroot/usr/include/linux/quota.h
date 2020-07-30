/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/linux/quota.h 1.3                           */
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
/* @(#)99     1.3  src/bos/usr/include/linux/quota.h, libcquota, bos530 1/12/01 15:35:03 */
/*
 * /usr/include/linux/quota.h
 *
 * If <linux/quota.h> is included, the default quotactl system call
 * syntax needs to be overridden with the linux quotactl syntax.
 * The functionality of the two versions of quotactl() is identical, but
 * the first two arguments are specified in reverse order.
 * This header will redefine quotactl so that __linux_quotactl is used.
 */
#ifndef _H_LINUX_QUOTA
#define _H_LINUX_QUOTA

#ifndef _LINUX_SOURCE_COMPAT
#define _LINUX_SOURCE_COMPAT
#endif

#include <sys/types.h>
#include <jfs/quota.h>

#ifndef quotactl
#define quotactl __linux_quotactl
#endif

int __linux_quotactl(int, const char *, int, caddr_t);

#endif /* _H_LINUX_QUOTA */
