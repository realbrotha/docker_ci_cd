/*
../../../../../../src/bos/usr/bin/errlg/bos.sysmgt.serv_aid.err.S:
@(#)89        1.169.1.20  src/bos/usr/bin/errlg/bos.sysmgt.serv_aid.err.S, cmderrlg, bos53X, x2011_31A7 6/8/11 15:37:56
*/

/*
 * COMPONENT_NAME: CMDERRLG  system error logging facility
 *
 * FUNCTIONS:  header file for error ids
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1989, 1990
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_ERRIDS
#define _H_ERRIDS

#include "sys/err_rec.h"


#define ERRID_NVRAM_NIC_PURGE 0x5006a81a /* NIC ip settings purged in NVRAM */
#define ERRID_CORRUPT_LOG    0x088700a6 /* Error log corrupted and recovered */
#define ERRID_LOG_COPY_FAILED 0xaebd9845 /* Error log copy failed */
#define ERRID_LOG_RECOVER_IO 0x9c955a91 /* i/o error recovering log file */
#define ERRID_DUPCHECK_ON    0x86dc0701 /* dup checking turned on */
#define ERRID_DUPCHECK_OFF   0x45e4e066 /* dup checking turned off */
#define ERRID_OPMSG          0xaa8ab241 /* alertable operator message */
#define ERRID_SYSLOG         0xc6aca566 /* syslog msg routed to error log */
#define ERRID_DISKETTE_ERR1  0xa92ae715 /* diskette device overrun error */
#define ERRID_DISKETTE_ERR2  0x3a9c2352 /* diskette timeout error */
#define ERRID_DISKETTE_ERR3  0x0734da1d /* diskette media error */
#define ERRID_DISKETTE_ERR4  0xb73bc3cd /* diskette unknown error */
#define ERRID_DISKETTE_ERR5  0xefec314d /* temporary diskette PIO error */
#define ERRID_DISKETTE_ERR6  0x8fef9795 /* permanent diskette PIO error */
#define ERRID_SCSI_ERR1      0x0502f666 /* permanent SCSI adapter hardware error */
#define ERRID_SCSI_ERR2      0xc14c511c /* temporary SCSI adapter hardware error */
#define ERRID_SCSI_ERR3      0x5cc986a0 /* permanent unknown SCSI adapter sfw error */
#define ERRID_SCSI_ERR4      0x13881423 /* temporary unknown SCSI adapter sfw error */
#define ERRID_SCSI_ERR6      0x52db7218 /* temporary unknown driver error */
#define ERRID_SCSI_ERR7      0xfec31570 /* permanent unknown system error */
#define ERRID_SCSI_ERR8      0xb18287f3 /* temporary unknown system error */
#define ERRID_SCSI_ERR10     0x0ba49c99 /* temporary SCSI bus error */
#define ERRID_DISK_ERR1      0x425bdd47 /* CD-ROM, disk, or read/write optical medi */
#define ERRID_DISK_ERR2      0x16f35c72 /* CD-ROM, disk, or read/write optical hard */
#define ERRID_DISK_ERR3      0x8647c4e2 /* adapter-detected CD-ROM, disk, or read/w */
#define ERRID_DISK_ERR4      0x49a83216 /* CD-ROM, disk, or read/write optical reco */
#define ERRID_DISK_ERR5      0xfefd41ff /* unknown CD-ROM, disk, or read/write opti */
#define ERRID_DISK_ERR6      0x080784a7 /* path has failed */
#define ERRID_TAPE_ERR1      0x4865fa9b /* tape media error */
#define ERRID_TAPE_ERR2      0x476b351d /* tape hardware/aborted command error */
#define ERRID_TAPE_ERR4      0x5537ac5f /* tape SCSI adapter detected error */
#define ERRID_TAPE_ERR5      0xffe2f73a /* tape unknown error */
#define ERRID_DMA_ERR        0xc8bac8c9 /* DMA unknown error, see device's error lo */
#define ERRID_EEH_ERR        0x32651a56 /* EEH error, see device's error log */
#define ERRID_PCI_PERMANENT_ERR 0x6472e03b /* EEH error, see device's error log */
#define ERRID_PCI_RECOVERABLE_ERR 0xe142c6d4 /* EEH error, see device's error log */
#define ERRID_EPOW_SUS       0x74533d1a /* EPOW: Loss of primary power. */
#define ERRID_EPOW_RES       0x0ec7e7e5 /* EPOW: Resumption of primary power. */
#define ERRID_SRC            0xe18e984f /* System Resource Controler */
#define ERRID_SRC_SVKO       0xbc3be5a3 /* SRC Subsystem terminated */
#define ERRID_SRC_TRYX       0x1ba7df4e /* Retry limit exceeded restarting subsyste */
#define ERRID_SRC_RSTRT      0xcb4a951f /* Subsystem ended -- will be restarted */
#define ERRID_RCMERR         0xeb5f98b2 /* Rendering Context Mgr error */
#define ERRID_CONSOLE        0x7f88e76d /* Console device driver error */
#define ERRID_PPRINTER_ERR1  0xdfc508f5 /* pprinter unknown error */
#define ERRID_MPQP_QUE       0x84ee0148 /* MPQP Queue Unavailable */
#define ERRID_MPQP_XFTO      0x7a9e20bb /* Transmit Failsafe Timeout  */
#define ERRID_MPQP_X21TO     0xe61501a6 /* X.21 Timeout */
#define ERRID_MPQP_DSRTO     0x44cb9ece /* DRS Going On Timeout */
#define ERRID_MPQP_DSROFFTO  0xa741ad52 /*  DSR already on for switched line  */
#define ERRID_MPQP_CTSTO     0x56816728 /*  CTS going On Timeout  */
#define ERRID_MPQP_DSRDRP    0x038f3117 /*  DSR Dropped During Transmit  */
#define ERRID_MPQP_CTSDRP    0x038f3117 /*  CTS Dropped During Transmit  */
#define ERRID_MPQP_RCVERR    0x10c6ced6 /*  MPQP Error On Receive Data */
#define ERRID_MPQP_ADPERR    0xb312955a /*  Adapter Not Present or not functioning  */
#define ERRID_MPQP_X21CECLR  0x8c0353cb /*  X.21 Unexpected Clear During Call Estab */
#define ERRID_MPQP_X21DTCLR  0xe252fe92 /*  X.21 Unexpected Clear During Data Trans */
#define ERRID_MPQP_BFR       0x2b76062d /*  MPQP -  Memory Resources Unavailable  */
#define ERRID_MPQP_XMTUND    0x1b1647df /*  Transmit Underrun  */
#define ERRID_CMDLVM         0x4523caa9 /* Logical Volume Manager  */
#define ERRID_COM_PERM_PIO   0x74859b9d /* permanent PIO error detected by driver */
#define ERRID_COM_TEMP_PIO   0x1fe5db4f /* temporary PIO error detected by driver */
#define ERRID_TTY_BADINPUT   0xc0073bb4 /* ttyinput routine returned with error cod */
#define ERRID_TTY_PARERR     0x43d4adce /* Parity/Framing error on input */
#define ERRID_TTY_OVERRUN    0x9d30b78e /* Receiver over-run on input */
#define ERRID_TTY_TTYHOG     0x0873cf9f /* ttyhog over-run */
#define ERRID_RS_PROG_SLIH   0x0cfad921 /* Unconfiguration process could not find s */
#define ERRID_TTY_PROG_PTR   0xe2b9e02b /* Pointer to private structure is null */
#define ERRID_RS_PROG_IOCC   0x0cacec26 /* IOCC is not configured at unconfig time. */
#define ERRID_COM_CFG_ADPT   0xf5458763 /* adapter already configured */
#define ERRID_COM_CFG_NADP   0x3ec3c657 /* adapter not present */
#define ERRID_COM_CFG_BUSI   0xfde6a5a1 /* bad bus id */
#define ERRID_COM_CFG_BUST   0x06abb2eb /* bad bus type */
#define ERRID_COM_CFG_IFLG   0x5114c792 /* bad interrupt flags */
#define ERRID_COM_CFG_ILVL   0x92a72c14 /* bad interrupt level */
#define ERRID_COM_CFG_INTR   0xfe6a2d60 /* bad interrupt priority */
#define ERRID_COM_CFG_MNR    0x2a7392a2 /* bad minor number */
#define ERRID_COM_CFG_BUSID  0x4287a984 /* bus id out of range */
#define ERRID_COM_CFG_DEVA   0xbc8f0bbb /* devswadd failed */
#define ERRID_COM_CFG_PIN    0xda244dca /* pincode failed */
#define ERRID_COM_CFG_DEVD   0x29975223 /* devswdel failed */
#define ERRID_COM_CFG_UNPIN  0x7f0052c6 /* unpincode failed */
#define ERRID_COM_CFG_SLIH   0x544ff289 /* i_init of slih failed */
#define ERRID_COM_CFG_PORT   0xb216db3e /* port already configured */
#define ERRID_COM_CFG_RESID  0x804c1878 /* resid not correct */
#define ERRID_COM_CFG_UIO    0x4cebe931 /* uiomove failed */
#define ERRID_COM_CFG_UNK    0x7993098b /* Unknown adapater type */
#define ERRID_RS_MEM_EDGE    0x66c3412b /* can't allocate edge structure */
#define ERRID_RS_MEM_IOCC    0x22f7b47b /* can't allocate iocc structure */
#define ERRID_RS_MEM_EDGEV   0xe2a4ec26 /* can't allocate edge vector */
#define ERRID_COM_MEM_SLIH   0x29202ca2 /* can't allocate slih structure */
#define ERRID_RS_MEM_PVT     0xe97374ff /* can't allocate private structure */
#define ERRID_RS_8_16_ARB    0x1e629bb1 /* 8/16 arbitration register failure */
#define ERRID_LION_BOX_DIED  0x3f86401a /* 64port concentrator died */
#define ERRID_LION_HRDWRE    0x1251b5b7 /* Failure in adapter hardware */
#define ERRID_LION_MEM_LIST  0xd84b1c5b /* can't allocate ttyp_t list */
#define ERRID_LION_MEM_ADAP  0x9c7fe90b /* can't allocate adap structure */
#define ERRID_LION_BUFFERO   0x50ca5315 /* Buffer over-run on input */
#define ERRID_LION_UNKCHUNK  0xbf6d9219 /* Unknown error code in chunk */
#define ERRID_LION_CHUNKNUMC 0xb76a0a99 /* Bad value in chunk numc */
#define ERRID_C327_START     0x1a660730 /*  C327 Start Error  */
#define ERRID_C327_INTR      0xc89de914 /*  C327 Interrupt Error  */
#define ERRID_ISI_PROC       0x3bbd4751 /* instuction storage interrupt : processor */
#define ERRID_DSI_PROC       0x9d035e4d /* data storage interrupt : processor */
#define ERRID_DSI_SCU        0xb8892a14 /* data storage interrupt : storage control */
#define ERRID_DSI_IOCC       0x27c1efff /* data storage interrupt : IOCC */
#define ERRID_DSI_MEMOVLY    0x9aa1914a /* A kernel memory overlay has been detecte */
#define ERRID_MACHINECHECK   0x9d972716 /* machine check */
#define ERRID_MACHINE_CHK_604_620 0x87f378ec /* Machine check interrupt (604 and 620) */
#define ERRID_RTAS_ERROR     0xe7aaa79d /* RTAS call failure */
#define ERRID_UPDATE_FLASH_ERR 0x3704506b /* update flash-memory failure */
#define ERRID_MACHINE_CHECK_RECUE 0xf7442702 /* Machine Check UE Recoverable Handler */
#define ERRID_MACHINE_CHECK_CHRP 0x56cdc3c8 /* Machine Check Error Handler */
#define ERRID_SCAN_ERROR_CHRP 0xbfe4c025 /* Internal Error */
#define ERRID_INTERNAL_ERROR_INT 0x924d8791 /* Internal Error Interrupt */
#define ERRID_EPOW_SUS_CHRP  0xbe0a03e5 /* EPOW: Environmental Problem. */
#define ERRID_KERNEL_PANIC   0x225e3b63 /* Kernel Panic! */
#define ERRID_DOUBLE_PANIC   0x358d0a3e /* Double Panic! */
#define ERRID_ATE_ERR1       0x36c3328b /* no pacing character received */
#define ERRID_ATE_ERR2       0x36c3328b /* too many transmission errors */
#define ERRID_ATE_ERR3       0x36c3328b /* no acknowledgement from receiving site */
#define ERRID_ATE_ERR4       0x36c3328b /* receiving site is not ready */
#define ERRID_ATE_ERR5       0x36c3328b /* sending site is not sending */
#define ERRID_ATE_ERR7       0xf6e3c547 /* checksum error */
#define ERRID_ATE_ERR8       0xf6e3c547 /* sector received twice */
#define ERRID_ATE_ERR9       0xf6e3c547 /* incorrect sector received */
#define ERRID_ATE_ERR10      0xf6e3c547 /* sector could not be verified */
#define ERRID_PROGRAM_INT    0xdd11b4af /* program interrupt */
#define ERRID_CORE_DUMP      0xc69f5c9b /* Core dump caused by signal */
#define ERRID_ACCT_OFF       0x2e7c3756 /* Accounting off */
#define ERRID_LVM_SWREL      0xd8cf8401 /* SW relocation successful */
#define ERRID_LVM_HWREL      0x03913b94 /* HW relocation successful */
#define ERRID_LVM_HWFAIL     0x9811eb50 /* HW relocation failed */
#define ERRID_LVM_BBFAIL     0x80d3764c /* Error during BB relocation */
#define ERRID_LVM_BBNOREL    0x333bd283 /* LV is marked no BB relocation */
#define ERRID_LVM_BBRELMAX   0xdafee4d6 /* Max retries during BB relocation */
#define ERRID_LVM_BBEPOOL    0x320b8ed9 /* BB relocation pool is empty */
#define ERRID_LVM_BBDIRERR   0x438e027e /* Error during BB dir IO op */
#define ERRID_LVM_BBDIRBAD   0x88453987 /* BB directory corrupted */
#define ERRID_LVM_BBDIRFUL   0x688b4101 /* BB directory is full */
#define ERRID_LVM_BBDIR90    0x33604aef /* BB directory is over 90% full */
#define ERRID_DUMP_STATS     0x67145a39 /* System dump statistics */
#define ERRID_SYSDUMP_SYMP   0x3573a829 /* Symptom data for a system dump */
#define ERRID_SYSDUMP_STACK  0xb38e3397 /* Stack data for a system dump */
#define ERRID_MINIDUMP_LOG   0xf48137ac /* System Minimal Dump */
#define ERRID_MINIDUMP_ERROR 0x6b96d2b0 /* Minidump Error */
#define ERRID_MINIDUMP_INFO  0x1850f542 /* Minidump Operation */
#define ERRID_DMPCHK_COMPON  0xc291a40c /* Dump compression was turned on. */
#define ERRID_DMPCHK_TOOSMALL 0xe87ef1be /* The largest dump device is too small. */
#define ERRID_DMPCHK_NOSPACE 0xf89fb899 /* The copy directory is too small. */
#define ERRID_DMPCHK_TOOSMALLC 0x9c92e5b6 /* The largest dump device is too small. */
#define ERRID_DMPCHK_NOSPACEC 0xf37f3b92 /* The copy directory is too small. */
#define ERRID_PGSP_KILL      0xc5c09ffa /* Process killed due to low paging space */
#define ERRID_NO_PGSP        0x8527f6f4 /* Out of paging space */
#define ERRID_NLS_MAP        0x28935927 /* NLS mapping problem */
#define ERRID_NLS_BADMAP     0xe7e2e3e9 /* bad NLS map removed */
#define ERRID_LVM_MISSPVADDED 0x26120107 /* A physical volume has been defined as mi */
#define ERRID_LVM_SA_WRTERR  0x52715fa5 /* Failed to write Volume Group Status area */
#define ERRID_LVM_SA_FRESHPP 0x41e36337 /* Physical partition marked active. */
#define ERRID_LVM_SA_QUORCLOSE 0xcad234be /* Quorum lost, volume group closing. */
#define ERRID_LVM_MWCWFAIL   0x41bf2110 /* Mirror write consistency cache write fai */
#define ERRID_SDA_ERR3       0xfec31570 /* permanent unknown system error */
#define ERRID_SDA_ERR4       0xb18287f3 /* temporary unknown system error */
#define ERRID_SYS_RESET      0x1104aa28 /* system reset button pushed */
#define ERRID_REBOOT_ID      0x2bfa76f6 /* system shutdown by user */
#define ERRID_TMSCSI_READ_ERR 0x868921f2 /* non-retriable hdw err receiving data */
#define ERRID_TMSCSI_CMD_ERR 0xee18df01 /* non-retriable hdw err sending cmd */
#define ERRID_TMSCSI_UNRECVRD_ERR 0xfbf0bfc1 /* unrecovered error sending command */
#define ERRID_TMSCSI_RECVRD_ERR 0x98f39a90 /* recovered error sending command */
#define ERRID_TMSCSI_UNKN_SFW_ERR 0x72cbc436 /* device driver detected sfw err */
#define ERRID_CORRECTED_SCRUB 0xa6bad8e6 /* Corrected memory via scrubbing */
#define ERRID_CAT_ERR1       0xd7dddc46 /* microcode abnormally terminated */
#define ERRID_CAT_ERR2       0x4ab56573 /* microcode load failed */
#define ERRID_CAT_ERR3       0x9060a2f8 /* no mbuf available */
#define ERRID_CAT_ERR4       0x80f672ff /* no pinned memory available */
#define ERRID_CAT_ERR5       0xd080e08d /* permanent channel adapter hardware error */
#define ERRID_CAT_ERR6       0x9060a2f8 /* 370 Parallel Channel Adapter system reso */
#define ERRID_CAT_ERR7       0xbe910c7f /* 370 Parallel Channel Adapter driver reso */
#define ERRID_CAT_ERR8       0x5d1f16fa /* 370 Parallel Channel Adapter detected a  */
#define ERRID_REPLACED_FRU   0x2f3e09a4 /* FRU replacement in the field */
#define ERRID_VCA_INITZ      0x04b1c8c0 /* VCA Host independent initialization fail */
#define ERRID_VCA_INTR1      0x904c6053 /* interrupt handler registration failed */
#define ERRID_VCA_IOCTL1     0xe70473e7 /* Unsupported video control request */
#define ERRID_TTY_INTR_HOG   0x345707f5 /* temporary interrupt hog detected by driv */
#define ERRID_PSIGDELIVERY   0xa2a97a5f /* Program Interrupt During Signal Delivery */
#define ERRID_HARDWARE_SYMPTOM 0xcb36dff0 /* Symptom data reported by hardware */
#define ERRID_SOFTWARE_SYMPTOM 0x20746462 /* Symptom data reported by software */
#define ERRID_INIT_RAPID     0x3a30359f /* init command respawning too rapidly  */
#define ERRID_INIT_UTMP      0xe47e212e /* init failed write of utmp entry */
#define ERRID_INIT_CREATE    0x80a357f9 /* init cannot create utmp */
#define ERRID_INIT_OPEN      0x5ce03b80 /* init cannot open */
#define ERRID_INIT_UNKNOWN   0x4f3e9630 /* init unknown err logged -- check detail  */
#define ERRID_LOG_PRE_WRAP   0xf2936fc5 /* Error log file premature wrap */
#define ERRID_LOG_REG_WRAP   0xd1e21ba3 /* Error log file regular wrap */
#define ERRID_INTRPPC_ERR    0x922a35b8 /* INTERRUPT unknown error */
#define ERRID_GRAPHICS       0xe85c5c4c /* Graphics subsystem errors */
#define ERRID_LOST_EVENTS    0xa39f8a49 /* error logging buffer lost events error */
#define ERRID_BAD_BUF_ENTRY  0x18592686 /* Error demon annunciate bad buffer entry */
#define ERRID_ODM_CHANGE_SWSERVAT 0x27ea672a /* Errdemon cannont change SWservAt in ODM */
#define ERRID_LOW_MBUFS      0xe931ba9f /* Low Mbufs */
#define ERRID_OSTD_LOW_MBUF  0xe931ba9f /* Ostd Alloc Fail */
#define ERRID_LOW_POLICE_BUFS 0xe931ba9f /* Low net_malloc_police buffers */
#define ERRID_PEND_LOW_MBUFS 0xe9b4eb4b /* Pending Low Mbufs */
#define ERRID_MID_UCODE      0x9198533d /* Microcode CRC test failed */
#define ERRID_MID_PIPE1      0x88bc536d /* PIPE processor 1 not responding */
#define ERRID_MID_PIPE2      0x5f0bc7c4 /* PIPE processor 2 not responding */
#define ERRID_MID_PIPE3      0x984f565b /* PIPE processor 3 not responding */
#define ERRID_MID_PIPE4      0xcd5f7617 /* PIPE processor 4 not responding */
#define ERRID_MID_BLAST      0xf07d3c3d /* BLAST processor not responding */
#define ERRID_MID_BLASTB     0x662ab9a3 /* BLAST (backend) processor not responding */
#define ERRID_MID_SW         0x2adff53f /* Datastream (software) error */
#define ERRID_BUMP_ERROR_TABLES 0x3fa9ce30 /* bump errors detected */
#define ERRID_AIO_XMEMOUT_FAIL 0x4912cb07 /* Aynchronous IO: xmemout failed */
#define ERRID_NVRAM_ERRDATA  0xb0787f02 /* Corrupt NVRAM Error Log Data */
#define ERRID_TTY_RRBENABLE  0x11955704 /* TTY Remote reboot enabled */
#define ERRID_TTY_RRBDISABL  0x00093f2c /* TTY Remote reboot disabled */
#define ERRID_TTY_RRB        0x1960e672 /* System rebooted using TTY Remote Reboot */
#define ERRID_AIXIF_ARP_DUP_ADDR 0xfe2dee00 /* Duplicate IP address in the network */
#define ERRID_SPECFS_DDINTPRI 0xae26dd07 /* driver returned with interrupts disabled */
#define ERRID_JFS_USER_HARDLINK 0x5ece4a58 /* directory hardlink created or removed */
#define ERRID_JFS_USER_WRITEMOUNT 0xd73189f6 /* process wrote to device containing a mou */
#define ERRID_JFS_FS_FULL    0x369d049b /* unable to allocate space in file system */
#define ERRID_JFS_FS_FRAGMENTED 0x5dfed6f1 /* file system free space excessively fragm */
#define ERRID_JFS_FS_NOINODES 0x8988389f /* unable to allocate inodes in file system */
#define ERRID_JFS_KERNHEAP_LOW 0x83f4b3cb /* unable to allocate space in kernel heap */
#define ERRID_JFS_KERNHEAP_DELAY 0x7975092c /* able to allocate space in kernel heap af */
#define ERRID_JFS_FSCK_REQUIRED 0xcd546b25 /* file system recovery required */
#define ERRID_JFS_META_CORRUPTION 0x684a365b /* invalid file system control data */
#define ERRID_JFS_META_EXCEPTION 0x0ec00096 /* exception on file system control data */
#define ERRID_JFS_META_WRITE_ERR 0xd2a1b43e /* i/o error on file system control data */
#define ERRID_JFS_LOG_EXCEPTION 0x00a1e866 /* exception on file system log device */
#define ERRID_JFS_LOG_WRITE_ERR 0x1ed0a744 /* i/o error on file system log device */
#define ERRID_JFS_LOG_WRAP   0x061675cf /* jfs log full (wrapped) */
#define ERRID_JFS_LOG_WAIT   0xcf71b5b3 /* file system performance impaired */
#define ERRID_JFS_COMP_CORRUPTION 0x4b6da1f5 /* corrupted file in compressed filesystem */
#define ERRID_LVM_NO_MWCENTRY 0x56116bf9 /* MWC entry not found. */
#define ERRID_CPU_FAIL_PREDICTED 0x1b963892 /* CPU Failure Predicted */
#define ERRID_CPU_DEALLOC_SUCCESS 0x804e987a /* CPU deallocation is successful */
#define ERRID_CPU_DEALLOC_ABORTED 0x4056f04c /* CPU deallocation is aborted */
#define ERRID_CPU_ALLOC_ABORTED 0x8663c805 /* CPU allocation is aborted */
#define ERRID_LVM_IO_FAIL    0xe86653c3 /* I/O error detected by LVM. */
#define ERRID_SH_PRIORITY_PROBLEM 0xd869e7f3 /* SYSTEM HANG DUE TO A PROCESS PRIORITY PR */
#define ERRID_JFS_DMAPI_FORCE 0x6cceb582 /* User mounted managed with no manager */
#define ERRID_FPSWA_CORE     0xbe0375ea /* Floating Point Software Assist not avail */
#define ERRID_SERVICE_EVENT  0xc231441f /* diagServiceEvent Failure */
#define ERRID_SH_LOST_IO     0x1b1e26fb /* SYSTEM HANG DUE TO A LOST I/O PROBLEM */
#define ERRID_EPOW_RES_CHRP  0x3997d500 /* EPOW: Resumption of primary power. */
#define ERRID_ERRRESUME      0x8c41bdf0 
#define ERRID_WLM_KILL       0xe942001f /* PROCESS KILLED DUE TO EXCESSIVE WLM TOTA */
#define ERRID_WLM_TERM       0x28e0275e /* TERM SENT TO PROCESS DUE TO EXCESSIVE WL */
#define ERRID_CMDCFG_RTAS    0x579abe0b /* RTAS failure from ioctl call */
#define ERRID_DR_RTAS        0xa2f875e0 /* DR: RTAS failure from ioctl call */
#define ERRID_DR_SCRIPT_MSG  0xdd42a684 /* DRAF - Script error and other messages */
#define ERRID_DR_CPU_HANDLER_ERR 0xd8f47df1 /* DR: CPU add/removal failed by reconfig h */
#define ERRID_DR_MEM_HANDLER_ERR 0x252d3145 /* DR: LMB add/removal failed by reconfig h */
#define ERRID_DR_APPS_ERR    0x2da324cb /* DR: DR operation failed by an applicatio */
#define ERRID_DR_MEM_UNSAFE_USE 0x12337a8d /* DR: affected memory not available for DR */
#define ERRID_DR_DMA_MIGRATE_FAIL 0x4da8fe60 /* DR: DMA specific memory migration failed */
#define ERRID_DR_DMA_MAPPER_FAIL 0x268da6a3 /* DR: DMA specific memory mapper failed */
#define ERRID_CPU_SPARING_SUCCESS 0xde0966ba /* CPU Sparing is successful */
#define ERRID_CPU_FAIL_CAP_REDUCTION_PREDICTED 0x0bd8a97c /* SPLPAR: CPU Failure - Capacity Reduction */
#define ERRID_CPU_FAIL_CAP_REDUCTION_SUCCESS 0x12e7b75c /* SPLPAR: CPU Failure - Capacity Reduction */
#define ERRID_CPU_FAIL_CAP_REDUCTION_ABORTED 0x41007351 /* SPLPAR: CPU Failure - Capacity Reduction */
#define ERRID_DR_UNSAFE_PROCESS 0xb6648805 /* DR - Application using DR unsafe library */
#define ERRID_LVM_FORCEVARYON 0x078ba0eb /* The Volume Group has been forced on via  */
#define ERRID_LVM_QUORUMNOQUORUM 0x5bead71b /* No quorum volume group activated with a  */
#define ERRID_J2_SNAP_FULL   0xab06bb2d /* J2 snapshot full, deleted */
#define ERRID_J2_SNAP_EIO    0xa616e0cf /* i/o error on write to J2 snapshot, delet */
#define ERRID_FIRMWARE_EVENT 0xa6d1bd62 /* Firmware specified event */
#define ERRID_DMPCHK_PLATEXP 0x509695ef /* platform dump space expanded */
#define ERRID_DMPCHK_PLATMNT 0x818ce818 /* platform dump fs not mounted */
#define ERRID_J2_LOG_WRAP_START 0x4c41c0d0 /* JFS2 log records forced overwritten */
#define ERRID_J2_LOG_WRAP_STOP 0x854d3b24 /* JFS2 logging is back to normal */
#define ERRID_LVM_NOMIRRCOPIES 0x28d33163 /* No mirror copies were available to read  */
#define ERRID_J2_FSCK_REQUIRED 0xb6db68e0 /* File system recovery required */
#define ERRID_J2_METADATA_EIO 0x78abddeb /* Meta-data I/O error */
#define ERRID_J2_LOG_EIO     0xc1348779 /* Log I/O error */
#define ERRID_J2_USERDATA_EIO 0xea88f829 /* User data I/O error */
#define ERRID_J2_CORRUPTION  0x8839874a /* Invalid file system control data */
#define ERRID_J2_DIOBUF_CORRUPT 0xa7db9774 /* Invalid file system control data */
#define ERRID_J2_DTREE_CORRUPT 0x3db0aa71 /* Invalid file system control data */
#define ERRID_J2_XTREE_CORRUPT 0xabed1ba8 /* Invalid file system control data */
#define ERRID_J2_DMAP_CORRUPT 0x7b82439b /* Invalid file system control data */
#define ERRID_J2_IMAP_CORRUPT 0x61277850 /* Invalid file system control data */
#define ERRID_J2_LOG_CORRUPT 0x9a8401bb /* Invalid file system control data */
#define ERRID_J2_VCPAGER_CORRUPT 0x2d3689c8 /* Invalid file system control data */
#define ERRID_J2_PAGER_CORRUPT 0x7576b6d9 /* Invalid file system control data */
#define ERRID_J2_TXN_CORRUPT 0x4b6ba416 /* Invalid file system control data */
#define ERRID_J2_TXNLOCK_CORRUPT 0x8c9704ca /* Invalid file system control data */
#define ERRID_J2_SNAPSHOT_CORRUPT 0x0e2fa7b4 /* Invalid file system control data */
#define ERRID_J2_BUFMGR_CORRUPT 0x01218d09 /* Invalid file system control data */
#define ERRID_J2_DMAPI_CORRUPT 0xf8521fc5 /* Invalid file system control data */
#define ERRID_J2_TXCMABRT_CORRUPT 0xe1d58c79 /* Invalid file system control data */
#define ERRID_J2_IMFRLIST_CORRUPT 0x12cc838f /* Invalid file system control data */
#define ERRID_J2_METADATA_CORRUPT 0x4b97b439 /* Invalid file system control data */
#define ERRID_J2_STATE_CORRUPT 0x2cfa53e6 /* Invalid file system control data */
#define ERRID_LFS_INVALID_VNODE 0xd5022e14 /* Invalid vnode */
#define ERRID_LFS_FILE_TABLE_FULL 0xe2c5afa7 /* Out of file descriptor */
#define ERRID_LFS_FD_PROCESS_FULL 0xa7432fb3 /* Out of file descriptor */
#define ERRID_J2_FSCK_INFO   0xae3e3fad /* FSCK information */
#define ERRID_J2_FS_FULL     0xf7fa22c9 /* unable to allocate space in file system */
#define ERRID_J2_LOGREDO_INFO 0x5f46bbb9 /* logredo information */
#define ERRID_CORE_DUMP_FAILED 0x2f64580c /* Core dump failed */
#define ERRID_GATEWAY_IS_DOWN 0x101f1d7c /* Gateway Down Detected */
#define ERRID_J2_FREEZE_TIMEOUT 0x86ca9d0c /* File system freeze timeout expired */
#define ERRID_J2_FSCK_LOG_FAIL 0x2c2f1fff /* Unable to write to fsck log */
#define ERRID_LP_NOT_SUPPORTED 0x8924bf96 
#define ERRID_DELAYED_INTS   0xa2205861 /* excessive processor interrupt disablemen */
#define ERRID_J2_FREEZE_CORRUPTFS 0xa7aaf1f8 /* Freeze a corrupted file system */
#define ERRID_SEDEXCP_MONITOR 0xa84a7a8d /* Stack Execution Disabled Violation */
#define ERRID_LGPG_FREED     0xc4c3339d /* Large page(s) freed */
#define ERRID_XM_MEMLEAK_PCT 0x661fe038 /* Kernel heap use exceeds percentage thres */
#define ERRID_XM_MEMLEAK_COUNT 0x9616486d /* Kernel heap use exceeds allocation count */
#define ERRID_XM_BUFFER      0x7103c23a /* Allocated buffer overrun */
#define ERRID_XM_REC_FULL    0x820aad70 /* Cannot allocate additional segment for X */
#define ERRID_XM_PIN_FAIL    0x1c5086b1 /* Cannot pin additional memory for XMDBG */
#define ERRID_GEN_XMDBG      0xf050286a /* General xmalloc debug error */
#define ERRID_XM_READ_FREE   0xfe60a7be /* Read of deferred-free or redzoned memory */
#define ERRID_SYSTEM_STACK_OVFL 0xcb7a9979 /* System stack overflow */
#define ERRID_CLIENT_PMIG_STARTED 0x08917dc6 
#define ERRID_CLIENT_PMIG_DONE 0xa5e6db96 
#define ERRID_CLIENT_PMIG_ABORTED 0x5e075adf 
#define ERRID_CPU_FAIL       0x952d504f /* CPU Failure */
#define ERRID_LVM_GS_RLEAVE  0xab59abff /* Remote node Concurrent Volume Group fail */
#define ERRID_LVM_GS_LLEAVE  0xc84c68d4 /* Local node Concurrent Volume Group failu */
#define ERRID_LVM_GS_CFGTIME 0x9956461b /* Vote Time Limit Expired */
#define ERRID_LVM_GS_CFGFAIL 0xe45fa721 /* Concurrent Volume Group Configuration Ch */
#define ERRID_LVM_GS_CONNECTIVITY 0xdb14100e /* Group Services detected a failure */
#define ERRID_LVM_GS_CHILDGONE 0x4b219aea /* Concurrent LVM daemon forced Volume Grou */
#define ERRID_LVM_GS_NOENV   0x9bd08d55 /* Unable to start gsclvmd */
#define ERRID_LVM_GS_CHILDREVIVE 0x6fe3fcd0 /* Concurrent LVM daemon child revived */
#define ERRID_LVM_FORCEOFF_VG 0x66206e7b /* Volume group forced off-line */
#define ERRID_J2_MAKE_RDONLY 0x2818db2c /* chfs command failed, filesystem is now r */
#define ERRID_J2_INODE_EXCEPTION 0x871ab40d /* Inode encountered Exception */
#define ERRID_ERRLOG_OFF     0x192ac071 /* errdemon turned off */
#define ERRID_ERRLOG_ON      0x9dbcfdee /* errdemon turned on */
#define ERRID_SCANOUT        0xcf8cadb6 /* A system failure with scan data */
#define ERRID_TAPE_ERR3      0x22006523 /* recovered error threshold exceeded */
#define ERRID_TAPE_ERR6      0xb617e928 /* tape drive needs cleaning */
#define ERRID_LVM_SA_PVMISS  0xf7dda124 /* A physical volume has been defined as mi */
#define ERRID_LVM_SA_STALEPP 0xeaa3d429 /* Physical partition marked stale. */
#define ERRID_PLAT_DUMP_ERR  0x9d3b9a10 /* platform_dump processing failures */
#define ERRID_PLAT_DUMP_INFO 0xe2581f6c /* platform_dump informational messages */
#define ERRID_PLAT_DUMP_COMPLETE 0x51e537b5 /* platform_dump complete */
#define ERRID_PLAT_DUMP_INDICATOR 0x291d64c3 /* platform_dump indicator event */

#endif /* _H_ERRIDS */

