/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* perf530 src/perf/perfagent/usr/include/arm.h 1.1                       */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* OBJECT CODE ONLY SOURCE MATERIALS                                      */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1996               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* The source code for this program is not published or otherwise         */
/* divested of its trade secrets, irrespective of what has been           */
/* deposited with the U.S. Copyright Office.                              */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
#ifndef ARM_H_INCLUDED
#define ARM_H_INCLUDED

#include <sys/types.h>     /* C types  definitions */

/****************************************************************************/
/*                The Common Transaction Tracker API                        */
/****************************************************************************/

/* Common Transaction Tracker user defined application identifier           */
/* this is used to uniquely identify a group of transactions  belonging     */
/* to the same user application program(s).  This needs to be a 32-bit      */
/* signed integer.                                                          */

typedef long         arm_appl_id_t;

/* Common Transaction Tracker user defined transaction identifier           */
/* This is used to  uniquely identify an individual transaction that        */
/* has been registered.                                                     */

typedef long         arm_tran_id_t;

/* Common Transaction Tracker user defined transaction identifier tag       */
/* this is used to uniquely identify an individual instance of a            */
/* started transaction.                                                     */

typedef long         arm_start_handle_t;

/* Type definition for flags parameter.  This needs to be a 32-bit unsigned */
/* integer.                                                                 */

typedef unsigned long  arm_flag_t;

/* Type definition for the data field.   This need to be a 32-bit pointer.  */

typedef char          arm_data_t;

/* Type definition for the data size field.  This needs to be a 32-bit      */
/* signed integer.                                                          */

typedef long          arm_data_sz_t;

/* Type definition for all character strings.  This needs to be a 32-bit    */
/* pointer.                                                                 */

typedef char          arm_ptr_t;

/* Type definition for the return status.  This needs to be a 32-bit signed */
/* integer.                                                                 */

typedef long          arm_ret_stat_t;

/* Type definition for completion status.  This needs to be a 32-bit signed */
/* integer.                                                                 */

typedef long    arm_status_t;

/****************************************************************************/

#define ARM_GOOD   0       /* arm_end, transaction completed OK             */
#define ARM_ABORT  1       /* arm_end, transaction aborted                  */
#define ARM_FAILED 2       /* arm_end, transaction completed, but failed    */

/****************************************************************************/

#if defined  _WIN32
 #include <windows.h>
 #define ARM_API WINAPI
#elif defined __OS2__
 #define ARM_API _Pascal
#elif defined _OS216
 #define  arm_data_t char _far
 #define  arm_ptr_t  char _far
 #define ARM_API _far _pascal
#elif defined _WIN16 || _WINDOWS
 #include <windows.h>
 typedef BOOL (FAR PASCAL _export * FPSTRCB) (LPSTR, LPVOID);
 #define  arm_data_t char FAR
 #define  arm_ptr_t  char FAR
 #define ARM_API WINAPI
#else  /* unix */
#define ARM_API
#endif


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef _PROTOTYPES

extern arm_appl_id_t ARM_API arm_init(
           arm_ptr_t     *appname,         /* application name              */
           arm_ptr_t     *appl_user_id,    /* Name of the application user  */
           arm_flag_t     flags,           /* Reserved = 0                  */
           arm_data_t    *data,            /* Reserved = NULL               */
           arm_data_sz_t  data_size);      /* Reserved = 0                  */

extern arm_tran_id_t ARM_API arm_getid(
           arm_appl_id_t     appl_id,      /* application handle            */
           arm_ptr_t        *tran_name,    /* transaction name              */
           arm_ptr_t        *tran_detail,  /* transaction additional info   */
           arm_flag_t        flags,        /* Reserved = 0                  */
           arm_data_t       *data,         /* Reserved = NULL               */
           arm_data_sz_t     data_size);   /* Reserved = 0                  */

extern arm_start_handle_t ARM_API arm_start(
           arm_tran_id_t tran_id,          /* transaction name identifier   */
           arm_flag_t    flags,            /* Reserved = 0                  */
           arm_data_t   *data,             /* Reserved = NULL               */
           arm_data_sz_t data_size);       /* Reserved = 0                  */

extern arm_ret_stat_t ARM_API arm_update(
           arm_start_handle_t  arm_handle, /* unique transaction handle     */
           arm_flag_t          flags,      /* Reserved = 0                  */
           arm_data_t          *data,      /* Reserved = NULL               */
           arm_data_sz_t        data_size);/* Reserved = 0                  */

extern arm_ret_stat_t ARM_API arm_stop(
           arm_start_handle_t arm_handle,  /* unique transaction handle     */
           const arm_status_t comp_status, /* Good=0, Abort=1, Failed=2     */
           arm_flag_t         flags,       /* Reserved = 0                  */
           arm_data_t        *data,        /* Reserved = NULL               */
           arm_data_sz_t      data_size);  /* Reserved = 0                  */

extern arm_ret_stat_t ARM_API arm_end(
           arm_appl_id_t     appl_id,      /* application id                */
           arm_flag_t        flags,        /* Reserved = 0                  */
           arm_data_t       *data,         /* Reserved = NULL               */
           arm_data_sz_t     data_size);   /* Reserved = 0                  */

#else  /* _PROTOTYPES */

extern arm_appl_id_t      ARM_API arm_init();
extern arm_tran_id_t      ARM_API arm_getid();
extern arm_start_handle_t ARM_API arm_start();
extern arm_ret_stat_t     ARM_API arm_update();
extern arm_ret_stat_t     ARM_API arm_stop();
extern arm_ret_stat_t     ARM_API arm_end();

#endif /* _PROTOTYPES */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ARM_H_INCLUDED */


