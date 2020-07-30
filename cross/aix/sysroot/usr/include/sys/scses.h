/* @(#)61       1.3  src/bos/kernel/sys/scses.h, sysxses, bos53N, n2007_44A0 9/14/07 15:23:08 */
#ifndef _H_SCSES
#define _H_SCSES
/*
 * COMPONENT_NAME: (SYSXSES) SCSI Enclosure Device Driver Include File
 *
 * FUNCTIONS:  NONE
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1996
 *
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/************************************************************************/
/* SCSI Enclosure Driver Ioctls 				        */
/************************************************************************/

#define SESIOCMD         0x03   /* Issue a user-defined SCSI-2 command  */
                                /* with argument of struct sc_iocmd     */
                                /* defined in scsi.h.                   */
#define SESPASSTHRU      0x17   /* Issue a user-defined SCSI-3 command  */
                                /* with argument of struct sc_passthru  */
                                /* defined in scsi.h                    */
#define SESPATHPASSTHRU  0x33   /* Issue a user-defined SCSI-3 command  */
                                /* with argument of struct sc_passthru  */
                                /* defined in scsi.h                    */

/************************************************************************/
/* MPIO ioctl structure for SESPATHPASSTHRU 			        */
/************************************************************************/
typedef struct scsises_pathiocmd {
	ushort   path_id;          /* Path ID of CuPath object to issue command */
	ushort   version;          /* Version structure,set to SCSI_VERSION_0 	*/
	uint     size;             /* Size of structure, in bytes, pointed to   */
				   /* by path_iocmd.      			*/
        void     *path_iocmd;      /* struct sc_passthru ptr defined in scsi.h  */
}sespathiocmd_t;

#endif /* _H_SCSES */
