/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2000,2009          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/*===========================================================================*/
/*                                                                           */
/* Module Name:  ct_cu_proc.h                                                */
/*                                                                           */
/* Description:                                                              */
/*     Interface definitions for the Cluster Utilities (process related).    */
/*                                                                           */
/*     This file is formatted to be viewed with tab stops set to 4.          */
/*===========================================================================*/
/* @(#)32   1.2   src/rsct/utils/ct_cu_proc.h, common_utils, rsct_rhay53, rhay531006a 10/24/00 17:02:11 */

#ifndef _H_CT_CU_PROC
#define _H_CT_CU_PROC

#include <rsct/ct_cu.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef _AIX
#include <procinfo.h>
#include <sys/proc.h>
#endif

/*---------------------------------------------------------------------------*/
/*  Cluster Utilities API constants.                                         */
/*---------------------------------------------------------------------------*/

/*	Error code definitions	*/

/*
 *  The following macros convert references to the generic names of CUAPI
 *  routines, like cu_get_proc_info(), to references to version specific
 *  CUAPI routines, like cu_get_proc_info_1(). The version used during
 *  conversion is determined by the value of CU_VERSION.  Note that these
 *  macros can deal with the different versions of a routine having different
 *  arguments.
 */

#define cu_get_proc_info                                                 \
    CU_ROUTINE_VERSION(cu_get_proc_info, CU_VERSION)

#define cu_get_procs                                                     \
    CU_ROUTINE_VERSION(cu_get_procs, CU_VERSION)

#define cu_get_proc_args                                                 \
    CU_ROUTINE_VERSION(cu_get_proc_args, CU_VERSION)

#define cu_get_keyword_info                                              \
    CU_ROUTINE_VERSION(cu_get_keyword_info, CU_VERSION)
    
/*---------------------------------------------------------------------------*
 *  The following data types are used by the process info functions.      
 *---------------------------------------------------------------------------*/
#ifdef _AIX

/* On AIX, just use the procs info structure definition */
typedef struct procsinfo cu_proc_info_t;

/*
 *  Since the process state (pi_state) is OS specific, the following macros are
 *  defined to check it for common situations.
 */
#define CU_PROC_SNOTPROC(p) ((p) == SNONE)    /* Not a process                         */
#define CU_PROC_STRANS(p)   ((p) == SIDL)     /* Process state in transition           */
#define CU_PROC_SZOMBIE(p)  ((p) == SZOMB)    /* Process is a zombie                   */
#define CU_PROC_SACTIVE(p)  ((p) == SACTIVE)  /* Process is active or sleeping         */
#define CU_PROC_SRUNNING(p) ((p) == SACTIVE)  /* Process is running (can't tell on AIX */
#define CU_PROC_SSTOP(p)    ((p) == SSTOP)    /* Process is stopped                    */
#define CU_PROC_SWAIT(p)    ((p) == SSWAP)    /* Process is waiting or swapped         */

/*
 * Macros to test the bits in the pi_flags field. 
 */

#define CU_PROC_FLAG_KPROC(p)    ((p) & SKPROC)
#define CU_PROC_FLAG_EXITING(p)  ((p) & SEXIT)
#define CU_PROC_FLAG_EXECED(p)   ((p) & SEXECED)
#define CU_PROC_FLAG_STARTING(p) ((p) & SEXECING)
#define CU_PROC_FLAG_TRACED(p)   ((p) & STRC)

#else

/* On Linux, we define our own struct that has the same field names */
/* as those in the AIX procsinfo structure.                         */
typedef struct {
    /* identification/authentication */
    unsigned long  pi_pid;              /* Process identifier                */
    unsigned long  pi_ppid;             /* Pid of parent process             */
    unsigned long  pi_sid;              /* Session identifier                */
    unsigned long  pi_pgrp;             /* Process group                     */
    unsigned long  pi_uid;              /* Real user id of the process       */
    unsigned long  pi_suid;             /* Effective user id of the process  */
    unsigned long  pi_start;            /* Process start time                */

    /* scheduler information */
    char           pi_state;            /* Process state                     */
    int            pi_flags;            /* Process flags                     */

    /* Controlling tty info */
    unsigned long  pi_ttyp;             /* has a controlling terminal        */

    /* Command Info */
    char           pi_comm[40];         /* (truncated) command               */
    
} cu_proc_info_t;


/*
 *  Since the process state (pi_state) is OS specific, the following macros are
 *  defined to check it for common situations.
 */
#define CU_PROC_SNOTPROC(p) ((p) == ' ')                     /* Not a process                 */
#define CU_PROC_STRANS(p)   (0)                              /* Process state in transition   */
#define CU_PROC_SZOMBIE(p)  ((p) == 'Z')                     /* Process is a zombie           */
#define CU_PROC_SACTIVE(p)  ( ((p) == 'S') || ((p) == 'R') ) /* Process is active or sleeping */
#define CU_PROC_SRUNNING(p) ((p) == 'R')                     /* Process is running            */
#define CU_PROC_SSTOP(p)    ((p) == 'T')                     /* Process is stopped            */
#define CU_PROC_SWAIT(p)    ((p) == 'D')                     /* Process is waiting or swapped */

/*
 * Macros to test the bits in the pi_flags field.
 *
 *    These bit definitions came from linux/include/linux/sched.h
 */

#define CU_PROC_FLAG_KPROC(p)    ((p) & 0x00000000)
#define CU_PROC_FLAG_STARTING(p) ((p) & 0x00000002)
#define CU_PROC_FLAG_EXITING(p)  ((p) & 0x00000004)
#define CU_PROC_FLAG_TRACED(p)   ((p) & 0x00000010)
#define CU_PROC_FLAG_EXECED(p)   (((p) & 0x00000040)==0)
    
#endif

/*---------------------------------------------------------------------------*/
/*  Cluster Utilites API function prototypes - Version 1                     */
/*---------------------------------------------------------------------------*/

/*
 * Function prototypes for functions intended for Cluster Utilities API clients.
 * Clients should use the generic routine names defined by macros included
 * in this header file, such as cu_get_proc_info(), instead of the version
 * specific routine names, like cu_get_proc_info_1().  Those macros
 * convert the generic names to the appropriate version specific names.
 */

#if (CU_VERSION == 1) || defined(CU_ALL_VERSIONS)

extern int
cu_get_proc_info_1(
    cu_proc_info_t   *p_proc_info,      /* output: process info              */
    pid_t            pid                /* input:  process identifier        */
);

extern int
cu_get_procs_1(
    cu_proc_info_t   **p_proc_info      /* output: pointer to process info   */
);

extern int
cu_get_proc_args_1(
    pid_t      pid,                      /* input: process's arguments to get */
    char       *p_buffer,                /* output: Null terminated args      */
    int        size 
);
    

extern int
cu_get_keyword_info_1(
    char *pFilename,
    int         numKeywords,
    ...
);

#endif /* (CU_VERSION == 1) || defined(CU_ALL_VERSIONS) */

#ifdef __cplusplus
} // end extern "C"
#endif /* __cplusplus */

#endif	/* _H_CT_CU_PROC */



