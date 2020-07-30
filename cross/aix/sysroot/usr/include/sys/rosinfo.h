/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53A src/bos/kernel/sys/POWER/rosinfo.h 1.7.3.3                      */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1995          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)50       1.7.3.3  src/bos/kernel/sys/POWER/rosinfo.h, syssi, bos53A, a2004_33E8 8/11/04 14:58:00 */

#ifndef _H_ROSINFO
#define _H_ROSINFO

/*
 * COMPONENT_NAME: (ROSIPL) ros code header file rosinfo.h
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1995
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#include<sys/types.h>

typedef struct ipl_info {

/* The following entry is reserved for IPL ROM usage.
 * The memory bit map's number of bytes per bit.
 * NOTE: the default size is 16K/bit
 */
  unsigned int     bit_map_bytes_per_bit;

/*
 *  The model field contains information which allows software to determine
 *  hardware type, data cache size, and instruction cache size.
 *
 *  The model field is decoded as follows:
 *        0xWWXXYYZZ
 *
 *  case 1: WW = 0x00 This means that the hardware is SGR ss32 or SGR ss64
 *                    (ss is speed in MH). The instruction cache is 8K bytes.
 *          XX = reserved
 *          YY = reserved
 *          ZZ = the model code:
 *                  bits 0 & 1 (low order bits) - indicate style type
 *                        00 = Tower     01 = Desktop
 *                        10 = Rack      11 = Reserved
 *                  bits 2 & 3 - indicate relative speed of processor
 *                        00 = Low       01 = Medium
 *                        10 = High      11 = Very high
 *                  bit 4 - Indicates number of combo chips.
 *                        0 = 2 combo chips
 *                        1 = 1 combo chip
 *                  bit 5 - Indicates the number of DCU's.
 *                        0 = 4 DCU's, data cache is 64 K bytes
 *                        1 = 2 DCU's, data cache is 32 K bytes
 *                  bits 6 & 7 (high order bits) - Reserved.
 *
 *  case 2: WW is nonzero.
 *          WW = 0x01 This means that the hardware is SGR ss32 or SGR ss64
 *                    (ss is speed in MH) -  RS1
 *          WW = 0x02 means the hardware is RSC.
 *          WW = 0x04 means the hardware is RS2 ( POWER2).
 *          WW = 0x08 means the hardware is PowerPC.
 *          XX has the following bit definitions:
 *                  bits 0 & 1 (low order bits) - indicate package type
 *                        00 = Tower     01 = Desktop
 *                        10 = Rack      11 = Entry Server Type
 *		    bit  2 - AIX Hardware Verification Test  Supported (rspc)
 *                  bit  3 - AIX Hardware Error Log Analysis Supported (rspc)
 *                  bits 4 through 7 are reserved.
 *          YY = reserved.
 *          ZZ = the model code.  No further information can be obtained
 *                  from this byte.
 *
 *          The instruction cache K byte size is obtained from entry icache.
 *          The data cache K byte size is obtained from entry dcache.
 *
 */
   unsigned int      model;

/* The next entry is used for system and partition identification. */
  char              sys_part_id[17];          /* identifies sys & partition */

/*
 * The following entries are copied from the IPL ROM Vital Product Data area.
 * These values are used to determine the machine hardware level.
 */
  char              vpd_processor_serial_number[9];

} IPL_INFO;
#endif
