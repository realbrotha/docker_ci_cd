/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53D src/bos/usr/sbin/perf/pmapi/libhpm/libhpm.h 1.1                 */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2004               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)64	1.1  src/bos/usr/sbin/perf/pmapi/libhpm/libhpm.h, pmapi, bos53D, d2004_50C0 12/6/04 07:28:43 */
/*
 * COMPONENT_NAME: (pmapi) Performance Monitor API
 *
 * FUNCTIONS: HPM Toolkit - declarations for C language programs
 */

#ifndef _H_LIBHPM
#define _H_LIBHPM

#ifdef __cplusplus
extern "C" {
#endif


/* Macro definitions to collect line numbers and program file names */

#define hpmInit(my_ID, progName) _hpmInit_(my_ID, progName, strlen(progName))   
#define hpmStart(id, label) _hpm_start_(id, __LINE__, __FILE__, label, strlen(__FILE__), strlen(label) )
#define hpmStop(id) _hpm_stop_(id, __LINE__)


#ifdef _THREAD_SAFE
#define hpmTstart(id, label) _hpm_tstart_(id, __LINE__, __FILE__, label, strlen(__FILE__), strlen(label) )
#define hpmTstop(id) _hpm_tstop_(id, __LINE__)
#endif /* _THREAD_SAFE */


#define hpm_start(id) _hpm_start_(id, __LINE__, __FILE__, "&nbsp;", strlen(__FILE__), 6 )
#define hpm_stop(id) _hpm_stop_(id, __LINE__)


#ifdef _THREAD_SAFE
#define hpm_tstart(id) _hpm_tstart_(id, __LINE__, __FILE__, "&nbsp;", strlen(__FILE__), 6 )
#define hpm_tstop(id) _hpm_tstop_(id, __LINE__)
#endif /* _THREAD_SAFE */

   
#ifdef _NO_PROTO

/* API and internal function declarations */

extern void _hpmInit_();
extern void hpmTerminate();
extern void hpm_init();
extern void hpm_terminate();
extern void _hpm_start_();
extern void _hpm_stop_();

#ifdef _THREAD_SAFE
extern void _hpm_tstart_();
extern void _hpm_tstop_();
#endif /* _THREAD_SAFE */

extern void hpmGetTimeAndCounters();
extern void hpmGetCounters();


#else /* _NO_PROTO */

/* API and internal function prototypes */

extern void _hpmInit_(int, char*, int);
extern void hpmTerminate(int);
/* convenience function equivalent to hpmInit(my_ID, "main") */
extern void hpm_init(int);
extern void hpm_terminate(int);
extern void _hpm_start_(int, int, char*, char*, int, int);
extern void _hpm_stop_(int, int);

#ifdef _THREAD_SAFE
extern void _hpm_tstart_(int, int, char*, char*, int, int);
extern void _hpm_tstop_(int, int);
#endif /* _THREAD_SAFE */

extern void hpmGetTimeAndCounters(int, double *, long long *);
extern void hpmGetCounters(long long *);

#endif /* ifdef _NO_PROTO */


#ifdef __cplusplus
}
#endif

#endif /* _H_LIBHPM */
