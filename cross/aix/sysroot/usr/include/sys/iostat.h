/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/sys/iostat.h 1.17.1.1                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1989,2009              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)28     1.17.1.1  src/bos/kernel/sys/iostat.h, sysios, bos53X, x2009_50A1 11/23/09 03:29:11 */

#ifndef	_H_IOSTAT
#define	_H_IOSTAT
#include <sys/types.h>
/*
 * COMPONENT_NAME: (SYSIOS) I/O Subsystem
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 * Iostat structure for tty
 */
struct ttystat
{
	long rawinch;		/* tty raw characters in count		*/
	long caninch;		/* tty canonical characters in count	*/
	long rawoutch;		/* tty characters out count		*/
};

/*
 * Iostat structure for tty (size-invariant - 64 bits)
 */
#ifdef _LONG_LONG
struct ttystat64
{
	long long rawinch;	/* tty raw characters in count		*/
	long long caninch;	/* tty canonical characters in count	*/
	long long rawoutch;	/* tty characters out count		*/
};
#endif

/*
 * Iostat structure for disks
 */
struct dkstat
{
	char		diskname[32];	/* disk's logical name		*/
	struct dkstat	*dknextp;	/* ptr to next entry in chain	*/
	ushort		dk_status; 	/* disk entry status flags	*/ 
#define IOST_DK_BUSY	0x1		/* disk is currently busy	*/
	ulong		dk_time;  	/* amount of time disk is active*/
	ulong		dk_xrate;	/* OBSOLETE: xfer rate capability*/
#define	__dk_rxfers	dk_xrate	/* #transfers from disk         */
	ulong		dk_bsize;	/* #bytes in a block for this disk*/
	ulong		dk_xfers;	/* #transfers to/from disk	*/
	ulong		dk_rblks;	/* #blocks read from disk	*/
	ulong		dk_wblks;	/* #blocks written to disk	*/
	ulong		dk_seek;	/* #seek operations for disks
					   with discrete seek commands	*/
/*
   Disks that support the q depth version of the dkstat structure
   will set dk_version to the dk_q_depth_magic number.  Similarly, 
   disks supporting the MPIO enabled version of the dkstat structure 
   will set dk_version to dk_qd_mpio_magic.  Users of the dkstat
   structure should test the version field for validity before
   reporting statistics dependent on the structure version.
 */
#define dk_q_depth_magic     0x31C4AF8C /* magic number for q depth	     */
#define dk_qd_mpio_magic     0x31C4AF8D /* magic number for q depth+MPIO     */
#define dk_qd_service_magic  0x31C4AF8E /* magic number for service+MPIO     */
#define dk_qd_service2_magic 0x31C4AF8F /* magic number for rxfers+q_sampled */
#define dk_tape_magic        0x31C4AF90 /* magic number for tapes            */
#define dk_qd_magic dk_version          /* for source compatibility     */
	ulong		dk_version;	/* dkstat struct version	*/
	ulong		dk_q_depth;	/* queue depth 			*/
	struct dkstat *dk_mpio_anchor;  /* pointer to path data anchor  */
	struct dkstat *dk_mpio_next_path;/* pointer to next path in chain */
#define dk_vscsi_initiator	0x1	/* vscsi initiator dk_mpio_path_id */
#define dk_vscsi_server		0x2	/* vscsi server dk_mpio_path_id */
#define dk_vscsi_target_device	0x3	/* vscsi target device dk_mpio_path_id*/
#define dk_pseudo_device        0x4     /* Pseudo devices dk_mpio_path_id */
	ushort          dk_mpio_path_id;/* MPIO path id                 */
	ushort          pad;		/* pad                          */
	ulong		dk_q_full;	/*in flight queue full occurence count*/
	u_longlong_t	dk_rserv;	/* read or receive service time */
	ulong		dk_rtimeout;	/* number of read request timeouts */
	ulong		dk_rfailed;	/* number of failed read requests */
	u_longlong_t	dk_min_rserv;	/* min read or receive service time */
	u_longlong_t	dk_max_rserv;	/* max read or receive service time */
	u_longlong_t	dk_wserv;	/* write or send service time */
	ulong		dk_wtimeout;	/* number of write request timeouts */
	ulong		dk_wfailed;	/* number of failed write requests */
	u_longlong_t	dk_min_wserv;	/* min write or send service time */
	u_longlong_t	dk_max_wserv;	/* max write or send service time */
	ulong		dk_wq_depth;	/* driver wait queue depth */
	ulong		dk_wq_sampled;	/* accumulated sampled dk_wq_depth */
	u_longlong_t	dk_wq_time;	/* accumulated wait queueing time */
	u_longlong_t	dk_wq_min_time;	/* min wait queueing time */
	u_longlong_t	dk_wq_max_time;	/* max wait queueing time */
	union {
		/* adapter name (NULL for MPIO and vscsi server) */
		char	adapter[32];
		/* used only by initiator to identify server */
		struct {
			ulong partition_id;	/* server partition id */
			ulong instance_id;	/* server instance id */
		} serv;
	} ident;
	ulong		dk_q_sampled;	/* accumulated sampled dk_q_depth */
};

/*
 * Kernel structure for keeping i/o statistics on disks
 */
struct iostat
{
	struct dkstat	*dkstatp;	/* ptr to linked list of disk
					   entries, one per configured disk */
	ulong		dk_cnt;		/* # dkstat structures in list	*/
	ulong		dk_path_cnt;	/* # path dkstat structures in list */
};

#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)

int iostadd(			/* register an entry in iostat table */
	int    devtype,		/* device type */
        struct  dkstat  *dkstp);

void iostdel(			/* delete an entry from iostat table */
       struct  dkstat  *dkstp); /* pointer to structure to remove */

void update_stats(void);	/* update sysinfo/syswait data structures */
void update_stats64(void);	/* update sysinfo64 data structures */
void update_iostats(int tick_size);	/* update disk info structures */

#endif /* (__64BIT_KERNEL) || (__FULL_PROTO) */

#endif	/* _H_IOSTAT */
