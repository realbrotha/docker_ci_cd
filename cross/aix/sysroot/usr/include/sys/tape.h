/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53J src/bos/kernel/sys/tape.h 1.10.2.6                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1989          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)19       1.10.2.6  src/bos/kernel/sys/tape.h, sysxtape, bos53J, j2006_34C0 8/15/06 01:42:57 */
/* @(#)19       1.12  R2/inc/sys/tape.h, sysxtape, bos325 5/28/93 09:38:11 */
#ifndef _H_TAPE
#define  _H_TAPE
/*
 * COMPONENT_NAME: (INCSYS) Magnetic Tape User Include File
 *
 * FUNCTIONS: NONE
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/************************************************************************/
/*                                                                      */
/*  NOTE:	This header file contains the definition of the		*/
/*              structures which are used in conjunction with ioctls    */
/*              to execute tape commands.                               */
/*                                                                      */
/************************************************************************/

/* SCSI Tape Ioctls */
#define STIOCTOP        	0x101	/* tape commands         	*/
#define STIOCMD         	0x002	/* diagnostic commands          */
#define STIOCHGP        	0x003	/* change drive parameters      */
#define STPRES_READKEYS		0x010	/* Persistent Reserve In command*/
                        	    	/* read keys service action     */
#define STPRES_READRES		0x011   /* Persistent Reserve In command*/
                           		/* read reservations ser action */
#define STPRES_CLEAR		0x012	/* Persistent ReserveOut command*/
                             		/* with clear service action    */
#define STPRES_PREEMPT		0x013	/* Persistent ReserveOut command*/
                                    	/* with preempt service action  */
#define STPRES_PREEMPT_ABORT 	0x014	/* Persistent ReserveOut command*/
                                    	/* with preempt and abort       */
                                    	/* service action               */
#define STPRES_REGISTER      	0x015	/* Persistent ReserveOut command*/
                                    	/* with Register & Ignore exist */
                                    	/* ing key service action.      */
#define STPASSTHRU              0x017   /* Issue user-defined SCSI      */
                                        /* command with argument of     */
                                        /* struct sc_passthru defined   */
                                        /* in scsi.h                    */
#define STPATHFORCE		0x020	/* Specify a single MPIO path   */
                   			/* for subsequent I/O           */
#define STPATHIOCMD		0x021	/* Issue a user-defined SCSI    */
                       			/* command (like STIOCMD)   to  */
                       			/* a specific MPIO path         */
#define STPATHPASSTHRU 		0x022	/* Issue user-defined SCSI      */
                         		/* command with argument of     */
                         		/* struct sc_passthru defined   */
                         		/* scsi.h to a speicific MPIO   */
                         		/* path                         */
#define STPCMPASSTHRU		0x023	/* Issue a user-defined MPIO    */
                         		/* pass thru command            */

/*
 * Structures and definitions for magnetic tape io control commands
 */

/************************************************************************/
/* structure for STIOCTOP - streaming tape op command                   */
/************************************************************************/
struct  stop    {
	short   st_op;          /* operations defined below */
	daddr_t st_count;       /* how many of them */
};

/* operations */
#define STOFFL	5	/* rewind and unload tape */
#define STREW   6       /* rewind */
#define STERASE 7       /* erase tape, leave at load point */
#define STRETEN 8       /* retension tape, leave at load point */
#define STWEOF  10      /* write an end-of-file record */
#define STFSF   11      /* forward space file */
#define STRSF   12      /* reverse space file */
#define STFSR   13      /* forward space record */
#define STRSR   14      /* reverse space record */
#define STINSRT 15      /* pull tape in from loader */
#define STEJECT 16      /* spit tape out to loader */
#define STDEOF  17      /* disable EOT checking */

/************************************************************************/
/* structure for STIOCHGP - streaming tape change parameters command    */
/************************************************************************/
struct  stchgp  {
	uchar   st_ecc;         /* reserved */
	int     st_blksize;     /* change blocksize to this */
};

/* ecc flags */
#define ST_NOECC   0x00      /* turn off ecc while writing */
#define ST_ECC     0x02      /* turn on ecc while writing  */

/************************************************************************
 * Persistent Reserve In - IOCTL structure.  This structure             *
 * supports STPRES_READKEYS & STPRES_READRES flags.		        *
 ************************************************************************/
struct st_pres_in {
    ushort  version;           		/* Version of Persistent Reserve*/
                               		/* implementation.              */
    ushort  allocation_length; 		/* Allocation space for the     */
                               		/* return parameters pertain to */
                               		/* reservation_info             */
    uint    generation;        		/* counter maintain by the LUN  */
                               		/* to keep track of reservation */
                               		/* key on when it's being    	*/
					/* changed.  			*/
    uint    returned_length;   		/* number of bytes in the       */
                               		/* reservation key list.        */
    uchar   scsi_status;       		/* scsi command status          */
    uchar   sense_key;         		/* check condition data         */
    uchar   scsi_asc;          		/* check condition data         */
    uchar   scsi_ascq;         		/* check condition data         */
    uchar   *reservation_info; 		/*reservation key(s) data return*/
};

#ifdef _KERNEL
/************************************************************************
 * NOTE: This structure is not supported for use by applications. It is *
 *       only for internal device driver use.				*
 *
 * st_pres_in is size variant for 32/64 bit, thus require two separate
 * structure to handle the size differences.
 ************************************************************************/
struct st_pres_in32 {
        ushort  version;                /* Version of Persistent Reserve*/
                                        /* implementation.              */
        ushort  allocation_length;      /* Allocation space for the     */
                                        /* return parameters pertain to */
                                        /* reservation_info             */
        uint    generation;             /* counter maintain by the LUN  */
                                        /* to keep track of reservation */
                                        /* key on when it's being       */
					/* changed.  			*/
        uint    returned_length;        /* number of bytes in the       */
                                        /* reservation key list.        */
        uchar   scsi_status;            /* scsi command status          */
        uchar   sense_key;              /* check condition data         */
        uchar   scsi_asc;               /* check condition data         */
        uchar   scsi_ascq;              /* check condition data         */
        ptr32   reservation_info;       /* reservation key(s) datareturn*/
};

struct st_pres_in64 {
        ushort  version;                /* Version of Persistent Reserve*/
                                        /* implementation.              */
        ushort  allocation_length;      /* Allocation space for the     */
                                        /* return parameters pertain to */
                                        /* reservation_info             */
        uint    generation;             /* counter maintain by the LUN  */
                                        /* to keep track of reservation */
                                        /* key on when it's being 	*/
					/* changed.  			*/
        uint    returned_length;        /* number of bytes in the       */
                                        /* reservation key list.        */
        uchar   scsi_status;            /* scsi command status          */
        uchar   sense_key;              /* check condition data         */
        uchar   scsi_asc;               /* check condition data         */
        uchar   scsi_ascq;              /* check condition data         */
        ptr64   reservation_info;       /* reservation key(s) datareturn*/
};
#endif /* _KERNEL */

/************************************************************************
 * Persistent Reserve Out - IOCTL structure.  This structure		*
 * supports STPRES_CLEAR flag.						*
 ************************************************************************/
struct st_pres_clear {
   ushort               version;        /* Version of Persistent Reserve*/
                                        /* implementation.              */
   uchar              scsi_status;      /* scsi command status          */
   uchar              sense_key;        /* check condition data         */
   uchar              scsi_asc;         /* check condition data         */
   uchar              scsi_ascq;        /* check condition data         */

};

/************************************************************************
 * Persistent Reserve Out - IOCTL structure.  This structure		*
 * supports STPRES_PREEMPT & STPRES_PREEMPT_ABORT flags.		*
 ************************************************************************/
struct st_pres_preempt {
   ushort               version;        /* Version of Persistent Reserve*/
   unsigned long long preempt_key;      /* current key in the LUN being */
                                        /* preempted.                   */
   uchar              scsi_status;      /* scsi command status          */
   uchar              sense_key;        /* check condition data         */
   uchar              scsi_asc;         /* check condition data         */
   uchar              scsi_ascq;        /* check condition data         */
};

/************************************************************************
 * Persistent Reserve Out - IOCTL structure.  This structure		*
 * supports STPRES_REGISTER flag.					*
 ************************************************************************/
struct st_pres_register {
   ushort             version;          /* Version of Persistent Reserve*/
   uchar              scsi_status;      /* scsi command status          */
   uchar              sense_key;        /* check condition data         */
   uchar              scsi_asc;         /* check condition data         */
   uchar              scsi_ascq;        /* check condition data         */
};

/************************************************************************
 * MPIO ioctl structure for STPATHIOCMD STPATHPASSTHRU 			*
 ************************************************************************/
typedef struct pstr_pathiocmd {
   ushort                path_id;       /* path id to issue ioctl       */
   uint                  size;
   void                  *path_iocmd;   /* cmd to issue                 */
}tpathiocmd_t;

#endif /* _H_TAPE */

/* ext flags */
#define TAPE_SHORT_READ	0x01	/* allow reads shorter than a full	*/
				/* block to be legal (variable length	*/
				/* blocksize only.)			*/
