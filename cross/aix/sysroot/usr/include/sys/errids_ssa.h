/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* ssa530 src/ssa/kernel/sys/POWER/errids_ssa.h 1.9                       */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1994,1999          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)10	1.9  src/ssa/kernel/sys/POWER/errids_ssa.h, ssaadapdd, ssa530 1/14/99 13:17:49 */

/*
 * COMPONENT_NAME: SSAADAPDD
 *
 * FUNCTIONS:  header file for SSA adapter error ids
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1995
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_ERRIDS_SSA
#define _H_ERRIDS_SSA

#define ERRID_SSA_LINK_ERROR        0xabececfd   /* SSA serial link failures          */
#define ERRID_SSA_LINK_OPEN         0x625e6b9a   /* SSA serial link open              */
#define ERRID_SSA_DETECTED_ERROR    0xec9903df   /* SSA detected failures             */
#define ERRID_SSA_DEVICE_ERROR      0xfe9e9357   /* SSA device failures               */
#define ERRID_SSA_DEGRADED_ERROR    0x3db7729e   /* SSA Degraded Condition            */
#define ERRID_SSA_HDW_ERROR         0x05f97a32   /* SSA Hardware Error Condition      */
#define ERRID_SSA_HDW_RECOVERED     0xb3ff2b19   /* Recovered SSA Hardware Error      */
#define ERRID_SSA_SOFTWARE_ERROR    0x91fbd5db   /* SSA Software or microcode errors  */
#define ERRID_SSA_LOGGING_ERROR     0x610bda5e   /* Unable to log against a pdisk     */
#define ERRID_SSA_ARRAY_ERROR       0xb4c00618   /* SSA RAID Array detected error     */
#define ERRID_SSA_SETUP_ERROR       0x48489b00   /* SSA configuration error           */
#define ERRID_SSA_CACHE_ERROR       0xbc31dea7   /* SSA cache error                   */
#define ERRID_SSA_ENCL_ERR1         0xbd797922   /* enclosure hardware error          */
#define ERRID_SSA_ENCL_ERR2         0xa5bed0bc   /* enclosure temperature error       */
#define ERRID_SSA_CACHE_BATTERY     0x26ca120b   /* SSA cache battery failure         */

#endif /*_H_ERRIDS_SSA*/
