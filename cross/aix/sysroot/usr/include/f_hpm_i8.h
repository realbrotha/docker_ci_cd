! @(#)63	1.2  src/bos/usr/sbin/perf/pmapi/libhpm/f_hpm_i8.h, pmapi, bos53E, e2005_25B6 6/16/05 07:16:48 
! IBM_PROLOG_BEGIN_TAG 
! This is an automatically generated prolog. 
!  
! bos53E src/bos/usr/sbin/perf/pmapi/libhpm/f_hpm_i8.h 1.2 
!  
! Licensed Materials - Property of IBM 
!  
! (C) COPYRIGHT International Business Machines Corp. 2004,2005 
! All Rights Reserved 
!  
! US Government Users Restricted Rights - Use, duplication or 
! disclosure restricted by GSA ADP Schedule Contract with IBM Corp. 
!  
! IBM_PROLOG_END_TAG 
! 
! COMPONENT_NAME: (pmapi) Performance Monitor API
! 
! FUNCTIONS: HPM Toolkit - declarations for Fortran programs
! 

#ifndef _H_F_HPM_I8
#define _H_F_HPM_I8

#ifdef __cplusplus
extern "C" {
#endif

#define f_hpminit(id, s) _f_hpm_init_i8_(id, s)
#define f_hpmterminate(id) _f_hpm_terminate_i8_(id)
#define f_hpmstart(id, s) _f_hpm_start_i8_(id, __LINE__, __FILE__, s)
#define f_hpmtstart(id, s) _f_hpm_tstart_i8_(id, __LINE__, __FILE__, s)
#define f_hpmstop(id) _f_hpm_stop_i8_(id, __LINE__ )
#define f_hpmtstop(id) _f_hpm_tstop_i8_(id, __LINE__ )
#define f_hpmgettimeandcounters(nc, time, values) _f_hpm_gettimeandcounters_i8_(nc, time, values)

#ifdef __cplusplus
}
#endif

#endif /* _H_F_HPM_I8 */
