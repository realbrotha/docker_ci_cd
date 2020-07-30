/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53S src/bos/kernel/sys/devinfo.h 1.26.3.30                          */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1989,1993              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)47       1.26.3.30  src/bos/kernel/sys/devinfo.h, sysio, bos53S, s2008_40A8 9/22/08 11:48:49 */
/*
 * COMPONENT_NAME: (SYSIO) System I/O
 *
 * FUNCTIONS: IO structure declarations and label definitions.
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1989, 2008
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */




#ifndef _H_DEVINFO
#define _H_DEVINFO

#ifndef IFNAMSIZ
#define IFNAMSIZ        16
#endif

#ifndef IFF_UP
#define IFF_UP          0x01
#endif

#ifndef IFF_RUNNING
#define IFF_RUNNING     0x40
#endif

#ifndef IFF_PRIMARY
#define IFF_PRIMARY     0x80
#endif

#ifndef MAXIFS
#define MAXIFS          8
#endif

#include <sys/types.h>
#include <sys/inttypes.h>

/*
 * Device information
 */
struct devinfo
{       char    devtype;
        char    flags;
        char    devsubtype;             /* device sub type */
        union
        {   struct      /* for disks */
            {   short   	bytpsec;        /* bytes per sector */
                short   	secptrk;        /* sectors per track */
                short   	trkpcyl;        /* tracks per cylinder */
                __long32_t      numblks;        /* blocks this partition */
                uint    	segment_size;   /* seg size for xfer stats */
                uint    	segment_count;  /* seg count for xfer stats */
                uint    	byte_count;     /* byte count for xfer stats */
            } dk;
	    struct	/* for SCSI target mode */
	    {
		uchar	scsi_id;	/* SCSI ID of attached initiator */
		uchar	lun_id;		/* LUN of attached initiator */
					/*   (or 0 for target instance) */
		uint	buf_size;	/* size of receive buffer (bytes) */
		uint	num_bufs;	/* number of receive buffers */
		__long32_t  max_transfer;	/* max request to SCSI DD */
		dev32_t	adapter_devno;	/* device maj/min of SCSI adapter */
	    } tmscsi;
            struct      /* for SCSI-3 target mode */
            {
                                             /* SCSI ID of attached initiator */
                uint    lo_scsi_id;          /* Least Significant word        */
                uint    hi_scsi_id;          /* Most Significant word         */

                                             /* LUN of attached initiator     */
                                             /* (or 0 for target instance)    */
                uint    lo_lun_id;           /* Least Significant word        */
                uint    hi_lun_id;           /* Most Significant word         */

                uint    buf_size;           /* size of receive buffer (bytes) */
                uint    num_bufs;              /* number of receive buffers   */
                __long32_t  max_transfer;      /* max request to SCSI DD      */
                dev32_t adapter_devno;      /* device maj/min of adapter      */
            } scsitm;
            struct      /* for SCSI or IDE disks */
            {   short   blksize;        	/* block size (in bytes) */
                __long32_t    numblks;        	/* total number of blocks */
                __long32_t    max_request;    	/* max request to DD      */
                uint    segment_size;   	/* seg size for xfer stats */
                uint    segment_count;  	/* seg count for xfer stats */
                uint    byte_count;     	/* byte count for xfer stats */
            } scdk, idedk;
            struct      /* for memory mapped displays */
            {   char    capab;          /* capabilities */
                char    mode;           /* current mode */
                short   hres;           /* horizontal resolution */
                short   vres;           /* vertical resolution */
            } tt;
            struct      /* for ethernet/IEEE 802.3 interface                 */
            {
                unsigned int    broad_wrap; /* allows broadcast wrap of data */
                                            /* 1 = supported                 */
                                            /* 0 = not supported             */
                int             rdto;       /* Receive Data Transfer offset  */
                unsigned char   haddr[6];   /* burned in hardware address    */
                unsigned char   net_addr[6]; /* Current network address      */
            } ethernet;
            struct      /* for Token-Ring interfaces */
            {   unsigned short   speed; /* 4/16 Mbps ring speed */
                                        /* 0 = 4 Mbps  */
                                        /* 1 = 16 Mbps */
                unsigned int    broad_wrap;     /* supports broadcast */
                                                /* wrap of data? */
                                                /* TRUE = supported */
                                                /* FALSE = not supported */
                int      rdto;  /* Receive Data Transfer offset */
                unsigned char     haddr[6];      /* hardware address */
                unsigned char     net_addr[6];   /* Current network address */
            } token;
            struct      /* for Serial Optical Link interfaces */
	    {   unsigned int    broad_wrap;     /* supports broadcast */
                                                /* wrap of data? */
                                                /* TRUE = supported */
                                                /* FALSE = not supported */
                int	rdto;  /* Receive Data Transfer offset */
		uchar	processor_id;		/* source id # 	*/
            } sol;
	    struct	/* for FDDI interfaces */
	    {
		uint	broad_wrap;		/* support broadcast */
						/* wrap of data? */
						/* TRUE = supported */
						/* FALSE = not supported */
		int	rdto;	/* Receive Data Transfer offset */
		uint	attach_class;	/* Attachment Class */
					/* 0 = Single Attachment Station */
					/* 1 = Dual Attachment Station */
		uchar 	haddr[6];		/* hardware address */
		uchar	netaddr[6];		/* Current network addr */
	    } fddi;
            struct      /* for block i/o device */
            {
              struct
               {
                char    type;           /* hardware type: ethernet or
                                                token ring */
                char    if_flags;       /* up/down:  1=ATTACHED
                                                     2=RUNNING
                                                     3=PRIMARY INTERFACE */
                char    haddr[6];       	/* hardware address: ethernet or
                                                	token ring */
                __long32_t    mymach;         	/* local IP adress */
                __long32_t    subnet_mask;    	/* subnet mask */
                int     mtu;            	/* maximum transmission unit */
                char    if_name[IFNAMSIZ]; 	/* name of interface */
                int     if_remmtu;      	/* MTU to remote */
                unsigned short  hdr_broadcast;  /* ring=0, local=1      */
               } lan[MAXIFS];
            } bio;
            struct      /* for magnetic tapes */
            {   short   type;           /* what flavor of tape */
                                        /* defined below */
            } mt;
            struct      /* for SCSI magnetic tapes */
            {   short   type;           /* what flavor of tape */
                                        /* defined below */
                int     blksize;        /* block size (in bytes) */
            } scmt;
            struct      /* for SCSI or IDE CDROMs */
            {   short   blksize;        	/* block size (in bytes) */
                __long32_t    numblks;        	/* total number of blocks */
            } sccd, idecd;
            struct      /* for IDE adapters */
            {   char    resv1;          	/* reserved */
                __long32_t    max_transfer;   	/* max xfer size (bytes) */
            } ide;
            struct      /* for SCSI adapters */
            {   
		char    card_scsi_id;   	/* SCSI Id of the adapter */
                __long32_t    max_transfer;   	/* max xfer size (bytes) */
            } scsi;
	    struct      /* for FC SCSI adapters */
            {
                uchar    connection_type;       /* The FC topology that is  */
						/* connected to this adapter*/
		                                /* 0 = Unknown              */
						/* 1 = Point to Point       */
						/* 2 = Switch               */
						/* 3 = Arbitrated Loop      */
						/* see sys/scsi_buf.h for   */
						/* defines.                 */
		uchar    flags;                 /* Flags for device         */
                                                /* 1 = virtual N_Ports      */
                                                /* capable & enabled        */
                                                /* 2 = adapter supports     */
                                                /* virtual N_Ports          */
                uchar    resvd[2];              /* Reserved for future use  */
		uint     lo_scsi_id;            /* Least Significant word of*/
						/* SCSI Id of the adapter   */
		uint     hi_scsi_id;            /* Most Significant word of */
						/* SCSI Id of the adapter   */
		uint     transfer_rate;         /* Speed in MB/sec of the FC*/
						/* link.                    */
		int      max_transfer;  	/* max xfer size (bytes)    */
                uint     num_avail_vports;      /* Number of available      */
                                                /* virtual N_Ports          */
                uint     num_used_vports;       /* Number of used           */
                                                /* virtual N_Ports          */
		uint     resvd2;                /* Reserved for future use  */

            } fcp;
	    struct      /* for iSCSI adapters */
            {
		uchar    flags;
		uchar    reserved1;             /* Reserved for future use  */
		ushort   reserved2;             /* Reserved for future use  */
		uint     reserved3;             /* Reserved for future use  */
		uint     reserved4;             /* Reserved for future use  */
                uint     transfer_rate;         /* Speed in MB/sec of the   */
						/* link.                    */
		int      max_transfer;  	/* max xfer size (bytes)    */

            } iscsi;
	    struct      /* for vSCSI adapters */
            {
		uint     srvr_id;               /* host adapter partition id*/
		uint     reserved2;             /* Reserved for future use  */
						/* link.                    */
		int      max_transfer;  	/* max xfer size (bytes)    */

            } vscsi;

	    struct      /* for V-SCSI-HOST adapters */
            {
		uint     client_partition;      /* partition number of client*/
                __long32_t max_transfer;        /* max xfer size (bytes)    */
		uint     reserved1;             /* Reserved for future use  */
		uint     reserved2;             /* Reserved for future use  */
		uint     reserved3;             /* Reserved for future use  */
            } vscsi_host;
            struct      /* for SAS adapters or protocol buses */
            {
		uchar    flags;
		uchar    reserved1;             /* Reserved for future use  */
		ushort   reserved2;             /* Reserved for future use  */
		uint     reserved3;             /* Reserved for future use  */
		uint     reserved4;             /* Reserved for future use  */
                uint     reserved5;             /* Reserved for future use  */
		int      max_transfer;  	/* max xfer size (bytes)    */

            } sas;
            struct      /* for SATA adapters or protocol buses */
            {
		uchar    flags;
		uchar    reserved1;             /* Reserved for future use  */
		ushort   reserved2;             /* Reserved for future use  */
		uint     reserved3;             /* Reserved for future use  */
		uint     reserved4;             /* Reserved for future use  */
                uint     reserved5;             /* Reserved for future use  */
		int      max_transfer;  	/* max xfer size (bytes)    */

            } sata; 
            

            struct                      /* dump information */
            {
                dev32_t   primary;        /* primary dump device */
                dev32_t   secondary;      /* secondary dump device */
                __long32_t    mdt_size;
            }   dump;
            struct /* for S/370 Channel PCA adapters */
            {
                uchar broad_wrap;       	/* always zero */
                __ulong32_t rdto;             	/* Receive Data xfer Offset */
                __ulong32_t hi_adap_name;     	/* Adapter hardware name */
                __ulong32_t lo_adap_name;     	/*    "       "      "   */
                __ulong32_t hi_ucode_name;    	/* Microcode name */
                __ulong32_t lo_ucode_name;    	/*    "       "   */
                uchar chnl_speed;       	/* interface speed, 
							see cat_adapcfg_t */
            } pca;
            struct      /* for large (DF_LGDSK flag set) SCSI or IDE disks */
            {   short   blksize;                /* block size (in bytes) */
                short   flags;                  /* valid if DF_IVAL set */
                __long32_t    lo_numblks;       /* low order word for    */
                                                /* total number of blocks*/
						/* This field is an      */
						/* unsigned value and    */
						/* should always be      */
						/* recast as a uint      */
                __long32_t    lo_max_request;   /* low order word of max */
                                                /* request to DD         */
                uint    segment_size;           /* seg size for xfer stats */
                uint    segment_count;          /* seg count for xfer stats*/
                uint    byte_count;             /* byte count for xfer stats*/
                __long32_t    hi_numblks;       /* high order word for   */
                                                /* total number of blocks*/
						/* This field is an      */
						/* unsigned value and    */
						/* should always be      */
						/* recast as a uint      */
                __long32_t    hi_max_request;   /* high order word of max*/
                                                /* request to DD         */

            } scdk64, idedk64;
            struct      /* for large (DF_LGDSK flag set) SCSI or IDE CDROMs */
            {   short   blksize;                /* block size (in bytes) */
                short   flags;                  /* valid if DF_IVAL set */
                __long32_t    lo_numblks;       /* low order word for    */
                                                /* total number of blocks*/
                __long32_t    hi_numblks;       /* high order word for   */
                                                /* total number of blocks*/

            } sccd64, idecd64;
            struct      /* for large disks (DF_LGDSK flag set) for LVs*/
            {   short   	bytpsec;        /* bytes per sector */
                short   	secptrk;        /* sectors per track */
                short   	trkpcyl;        /* tracks per cylinder */
                short           flags;          /* valid if DF_IVAL set */
                __long32_t      lo_numblks;     /* low order word for */
						/* total number of blocks */
                uint    	segment_size;   /* seg size for xfer stats */
                uint    	segment_count;  /* seg count for xfer stats */
                uint    	byte_count;     /* byte count for xfer stats */
                __long32_t      hi_numblks;     /* high order word for */
						/* total number of blocks */
            } dk64;
            struct {
                uint reserved0;
                uint reserved1;
                uint reserved2;
                uint reserved3;
            } vdev;

        } un; 
};

/* device types */
#define	DD_TMSCSI 'T'	/* SCSI target mode */
#define DD_SCSITM 'W'   /* SCSI-3 target mode */
#define DD_LP   'P'     /* line printer */
#define DD_TAPE 'M'     /* mag tape */
#define DD_SCTAPE  'm'  /* SCSI tape */
#define DD_TTY  'T'     /* terminal */
#define DD_DISK 'R'     /* disk */
#define DD_CDROM 'C'    /* cdrom */
#define DD_DLC 'D'      /* Data Link Control */
#define DD_SCDISK  'r'  /* SCSI disk */
#define DD_RTC  'c'     /* real-time (calendar) clock */
#define DD_PSEU 'Z'     /* pseudo-device */
#define DD_NET  'N'     /* networks */
#define DD_EN   'E'     /* Ethernet interface */
#define DD_EM78 'e'     /* 3278/79 emulator */
#define DD_TR   't'     /* token ring */
#define DD_BIO  'B'     /* block i/o device */
#define DD_X25  'x'     /* X.25 DDN device driver */
#define DD_IEEE_3  '3'  /* IEEE 802.3 */
#define DD_SL   'S'     /* Serial line IP  */
#define DD_LO   'L'     /* Loopback IP     */
#define DD_DUMP 'd'     /* dump device driver */
#define DD_SCCD    'C'  /* SCSI CDROM */
#define DD_CIO  'n'     /* common communications device driver */
#define DD_BUS  'b'     /* I/O Bus device */
#define DD_HFT  'H'     /* HFT */
#define DD_INPUT 'I'    /* graphic input device */
#define DD_CON  'Q'     /* console */
#define DD_NET_DH 'h'   /* Network device handler */
#define DD_DISK_C 's'   /* Disk Controller */
#define DD_SOL	'o'	/* Serial Optical Link */
#define DD_CAT  'K'     /* S/370 parallel channel */
#define DD_FDDI 'F'	/* FDDI */
#define DD_SCRWOPT 'w'  /* SCSI R/W optical */
#define DD_SES    'a'   /* SCSI Enclosure Services Device */
#define DD_AUDIT 'A'	/* Streams mode auditing virtual device */
#define DD_LIB	'l'	/* Medium library device */
#define DD_VIOA	'v'	/* Virtual IOA  */

/* device sub-types */
#define DS_DLCETHER 'e' /* DLC - Standard Ethernet */
#define DS_DLC8023  'i' /* DLC - IEEE 802.3 Ethernet */
#define DS_DLCTOKEN 't' /* DLC - Token Ring */
#define DS_DLCSDLC  'd' /* DLC - SDLC */
#define DS_DLCQLLC  'q' /* DLC - X.25 Qualified LLC */
#define DS_DLCFDDI  'f' /* DLC - FDDI */
#define DS_LV   'l'     /* logical volume */
#define DS_PV   'p'     /* physical volume - hard disk */
#define DS_SCSI 'S'     /* SCSI adapter */
#define DS_IDE  'I'     /* IDE adapter  */
#define DS_SAS  '7'      /* SAS adapter  */
#define DS_SATA '8'      /* SATA adapter */
#define DS_PP   'p'     /* Parallel printer */
#define DS_SP   's'     /* Serial printer   */
#define	DS_TM	'T'	/* SCSI target mode */
#define DS_SDA   'h'    /* Serial DASD adapter */
#define DS_SDC   'c'     /* Serial DASD Controller */
#define DS_NFS	'N'	/* NFS device for swapping */
#define DS_CAT  'k'     /* S/370 parallel channel */
#define DS_FCP  'F'     /* FC SCSI adapter        */
#define DS_VM   'V'     /* VM logical volume */
#define DS_QIO  'q'     /* Quick IO logical volume */
#define DS_ISCSI 'a'    /* iSCSI adapter           */
#define DS_LVZ  'z'	/* New logical volume type */
#define DS_LV0 DS_LVZ	/* New logical volume type */
#define DS_VMZ  'o'     /* VM logical volume */
#define DS_VDEVICE 'D'  /* Virtual deivce or bus   */
#define DS_CVSCSI 'D'   /* Virtual SCSI Client (hosteD)  */
#define DS_SVSCSI 'G'   /* Virtual SCSI Server (hostinG) */
#define DS_RPV	'R'	/* Remote device */

#ifndef DS_VSD
#define DS_VSD  'v'     /* VSD type device */
#endif

/* Type of tape drive */
#define DT_STREAM       1       /* Streaming tape drive */
#define DT_STRTSTP      2       /* Start-stop tape drive */

/* flags */
#define DF_FIXED 01     /* non-removable */
#define DF_RAND  02     /* random access possible */
#define DF_FAST  04
#define DF_CONC  0x08   /* Concurrent mode supported */
#define DF_LGDSK 0x10   /* Large > 2TB disk.         */
#define DF_IVAL  0x20   /* Inner flags valid in scdk64, idedk64, sccd64, 
                           idecd64, dk64 */

/* scdk64 flags */
#define DF_SSD   0x1    /* Solid state disk device */

#endif /* _H_DEVINFO */
