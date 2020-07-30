/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* IBM CONFIDENTIAL                                                       */
/*                                                                        */
/* OBJECT CODE ONLY SOURCE MATERIALS                                      */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2004,2005          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* The source code for this program is not published or otherwise         */
/* divested of its trade secrets, irrespective of what has been           */
/* deposited with the U.S. Copyright Office.                              */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

#ifndef _PRAGMA_COPYRIGHT_
#define _PRAGMA_COPYRIGHT_
#pragma comment(copyright, "@(#) 1.2 src/css/hps/hal/include/css_shared.h, fed.hal, css_rc15, rc150530a 05/08/02 11:07:25")
#endif /*_PRAGMA_COPYRIGHT_ */

#ifndef _css_shared_h
#define _css_shared_h

#include <sys/types.h>

#define MAX_CAN_ADAPTER_NUM    24
#define MAX_COL_ADAPTER_NUM    2

#define CSS_HAL_LOCAL_INTR        0
#define CSS_HAL_REMOTE_INTR       1
#define CSS_HAL_DISABLE_INTERVAL  0xffffffff

typedef int css_task_t;

typedef unsigned long long ULLONG_t;
typedef enum {NULL_DEV=0, TB2_DEV, TB3_DEV, TB3MX_DEV, TB3PCI_DEV, HAL_COL1,
              HAL_COL2, HAL_COLS, UDP_DEV, VIRTUAL_DEV, HAL_COR1, HAL_COR2,
              HAL_CORS, HAL_CAN, HAL_RCANF, HAL_RCANFR, HAL_RCANPFR, HAL_RES2, HAL_RES3, LAST_DEV} css_dev_t;


/* User thread init function prototype */
typedef void (thread_init_fptr)(void *, void *); 
typedef struct {
    pthread_attr_t   *thread_attr;      /* User defined Pthread attribute  */
    thread_init_fptr *thread_init_func; /* User thread init function       */
    void             *parm_ptr;         /* User supplied parameter to pass */
    void             *extra_ptr;        /* Just in case - future           */
} com_thread_info_t;

/*
** Window type and class to be passed as 
** the device to hal_init.
*/
#define HAL_INVALID_WTC    -1  /* not a supported WTC        */
#define SVC_WTC         0x0000
#define KLAPI_WTC       0x4000
#define LL_WTC          0x8000      /* userspace through LoadLeveler */
#define MPI_WTC         LL_WTC
#define LAPI_WTC        LL_WTC
#define NON_LL_WTC      0x9000      /* userspace not through LoadLeveler */
#define NON_LL_WTC_WOPT 0xA000
#define BOOT_DIAGS_WTC  0xC000
#define OLS_DIAGS_WTC   0xD000
#define OLA_DIAGS_WTC   0xE000
#define OFF_DIAGS_WTC   0xF000

#define GPFS_WTC        0x0001  /* persistent subsystem not through LL */
#define VSD_WTC         0x0002  /* persistent subsystem not through LL */
#define DIAG_WTC        0x0004  /* persistent subsystem not through LL */
#define PSS5_WTC        0x0005  /* reserved for future use    */
#define LLA_WTC         0x000A  /* reserved for future use    */
#define LLB_WTC         0x000B  /* reserved for future use    */
#define LLC_WTC         0x000C  /* reserved for future use    */
#define LLD_WTC         0x000D  /* reserved for future use    */
#define LLE_WTC         0x000E  /* reserved for future use    */
#define LLF_WTC         0x000F  /* reserved for future use    */

#endif /* _css_shared_h */
