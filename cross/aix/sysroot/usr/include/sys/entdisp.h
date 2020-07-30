/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernext/disp/sky/inc/entdisp.h 1.1                      */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1993               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)60	1.1  src/bos/kernext/disp/sky/inc/entdisp.h, sysxdispsky, bos530 11/3/93 16:42:21 */
/*
 *   COMPONENT_NAME: SYSXDISPSKY
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 27
 *
 *                    -- (                            when
 *   combined with the aggregated modules for this product)
 *   OBJECT CODE ONLY SOURCE MATERIALS
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1993
 *   All Rights Reserved
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

struct sky_map {    /* structure for returning mapping info to apps */
  ulong io_addr;       /* io register addresses */
  ulong cp_addr;       /* co processor base address */
  ulong vr_addr;       /* vram base address     */
  ulong dma_addr[4];   /* dma buffers base addresses */
  ulong screen_height_mm; /* Height of screen in mm */
  ulong screen_width_mm;  /* Height of screen in mm */
};


