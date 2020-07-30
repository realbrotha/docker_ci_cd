/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/usr/include/sys/lockname.h 1.197.1.24                   */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1994,1995              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)68	1.197.1.24  src/bos/usr/include/sys/lockname.h, lockstat, bos53X, x2011_31A9 5/18/11 05:31:20 */
/*
 * LEVEL 1,  5 Years Bull Confidential Information
 */

/******************************************************************************
 *
 *   COMPONENT_NAME: LOCKSTAT
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 27,83
 *
 ******************************************************************************
 *
 * Lock class 0 is reserved for 3rd party device driver providers.
 * Lock classes 1-100 are test classes reserved for 3rd party device
 *    driver development testing.  After testing is complete,
 *    3rd party users should use lock class 0.  These lock classes
 *    (0 through 100) will not be assigned by IBM.
 * Lock classes 1001-2000 are reserved for use by OEM system providers
 *    and will not be assigned by IBM.
 *
 * Users can define their own lock classes by creating a file in
 * /usr/include/sys with a filename like lockname_<xyz>.h, where
 * <xyz> is a string that the user defines.  For example, to
 * create a lock class 3000 with a lock class name of FOO_LOCK_CLASS
 * and a subsystem of FOO, one can create a file lockname_foo.h in
 * /usr/include/sys and enter the lock class information in the
 * format shown below:
 *
 * #define FOO_LOCK_CLASS 3000 FOO (where this last FOO is in C comments)
 *
 * The lock class name must be <= 20 chars.
 * The lock class must a value that can be stored in an int type.
 * The lock class subsystem (in comments) must be <= 6 chars.
 *
 */


/*
 * WARNING: This header file is for debug purposes only.
 *          The labels and values herein might change with
 *          each release of AIX
 */

#ifndef _H_LOCKNAME
#define _H_LOCKNAME

/*
 * lock class name          lock class  subsystem
 *
 */

#define CDRFS_LOCK_CLASS        101     /* CFS */
#define CDRPAGER_LOCK_CLASS     102     /* CFS */
#define CIO_LOCK_CLASS          103     /* CIE */
#define SCDISK_LOCK_CLASS       104     /* DISK */
#define SD_ADAP_LOCK_CLASS      105     /* DISK */
#define SD_EPOW_LOCK_CLASS      106     /* DISK */
#define ERRDD_LOCK_CLASS        107     /* ERRLG */
#define BIO_LOCK_FAMILY         108     /* IOS */
#define CIO_LOCK_FAMILY         109     /* IOS */
#define CLIST_LOCK_FAMILY       110     /* IOS */
#define CMAINT_LOCK_FAMILY      111     /* IOS */
#define DIL_LOCK_FAMILY         112     /* IOS */
#define DMA_LOCK_CLASS          113     /* IOS */
#define DSL_LOCK_FAMILY         114     /* IOS */
#define IOS_IPOLL_CLASS         115     /* IOS */
#define IOS_LOCK_CLASS          116     /* IOS */
#define PINCF_LOCK_FAMILY       117     /* IOS */
#define SELPOLL_LOCK_CLASS      118     /* IOS */
#define UPHYSIO_LOCK_CLASS      119     /* IOS */
#define MSG_LOCK_CLASS          120     /* IPC */
#define SEM_LOCK_CLASS          121     /* IPC */
#define SHM_LOCK_CLASS          122     /* IPC */
#define DEVNODE_LOCK_CLASS      123     /* LFS */
#define FFREE_LOCK_CLASS        124     /* LFS */
#define FIFOBUF_LOCK_CLASS      125     /* LFS */
#define FILOCK_LOCK_CLASS       126     /* LFS */
#define FOFF_LOCK_CLASS         127     /* LFS */
#define FPTR_LOCK_CLASS         128     /* LFS */
#define GFS_LOCK_CLASS          129     /* LFS */
#define GPA_LOCK_CLASS          130     /* LFS */
#define PATH_LOCK_CLASS         131     /* LFS */
#define U_FD_CLASS              132     /* LFS */
#define U_FSO_CLASS             133     /* LFS */
#define VFS_LIST_LOCK_CLASS     134     /* LFS */
#define VFS_LOCK_CLASS          135     /* LFS */
#define VNODE_LOCK_CLASS        136     /* LFS */
#define MD_LOCK_CLASS           137     /* MACHDD */
#define PGS_BUMP_LOCK_CLASS     138     /* MACHDD */
#define CS_CFG_LOCK             139     /* PCMCIA */
#define CS_CLIENT_LOCK          140     /* PCMCIA */
#define CS_CSWIN_LOCK           141     /* PCMCIA */
#define CS_EVH_LOCK             142     /* PCMCIA */
#define CS_INTR_LOCK            143     /* PCMCIA */
#define CS_IO_LOCK              144     /* PCMCIA */
#define CS_IQUEUE_LOCK          145     /* PCMCIA */
#define CS_QUEUE_LOCK           146     /* PCMCIA */
#define CS_SLOT_LOCK            147     /* PCMCIA */
#define CS_SOCKET_LOCK          148     /* PCMCIA */
#define CS_WINDOW_LOCK          149     /* PCMCIA */
#define SS_ADAPT_LOCK           150     /* PCMCIA */
#define SS_CFG_LOCK             151     /* PCMCIA */
#define SS_INTR_LOCK            152     /* PCMCIA */
#define COMP_LOCK_CLASS         153     /* PFS */
#define ICACHE_LOCK_CLASS       154     /* PFS */
#define INODE_LOCK_CLASS        155     /* PFS */
#define IRDWR_LOCK_CLASS        156     /* PFS */
#define LOG_LOCK_CLASS          157     /* PFS */
#define NCACHE_LOCK_CLASS       158     /* PFS */
#define QUOTA_LOCK_CLASS        159     /* PFS */
#define SYNC_LOCK_CLASS         160     /* PFS */
#define CALLOUT_LOCK_CLASS      161     /* PROC */
#define CORE_LOCK_CLASS         162     /* PROC */
#define CS_LOCK_CLASS           163     /* PROC */
#define LOCK_TABLE_CLASS        164     /* PROC */
#define PROC_INT_CLASS          165     /* PROC */
#define PROC_LOCK_CLASS         166     /* PROC */
#define PROC_TBL_CLASS          167     /* PROC */
#define PROC_ZONE_CLASS         168     /* PROC */
#define PTRACE_CLASS            169     /* PROC */
#define THREAD_LOCK_CLASS       170     /* PROC */
#define THREAD_ZONE_CLASS       171     /* PROC */
#define TIME_LOCK_CLASS         172     /* PROC */
#define TOD_LOCK_CLASS          173     /* PROC */
#define TRB_LOCK_CLASS          174     /* PROC */
#define UPRINTF_CLASS           175     /* PROC */
#define UTHREAD_ZONE_CLASS      176     /* PROC */
#define U_HANDY_CLASS           177     /* PROC */
#define U_TIMER_CLASS           178     /* PROC */
#define WATCHDOG_LOCK_CLASS     179     /* PROC */
#define PM_CORE_LOCK_CLASS      180     /* PWRX */
#define PM_KERNEL_LOCK_CLASS    181     /* PWRX */
#define AUDIT_WRITE_LOCK_CLASS  182     /* SECRTY */
#define AUDIT_LOCK_CLASS        183     /* SECRTY */
#define CRED_LOCK_CLASS         184     /* SECRTY */
#define AUDIT_QUEUE_LOCK_CLASS  185     /* SECRTY */
#define RECLK_LOCK_CLASS        186     /* SPECFS */
#define SPECHASH_LOCK_CLASS     187     /* SPECFS */
#define SPECNODE_LOCK_CLASS     188     /* SPECFS */
#define ACMULTI_LOCK_FAMILY     189     /* TCPKER */
#define ARPTAB_LOCK_FAMILY      190     /* TCPKER */
#define BPF_LOCK_FAMILY         191     /* TCPKER */
#define BUCKET_LOCK_FAMILY      192     /* TCPKER */
#define DEMUXER_LOCK_FAMILY     193     /* TCPKER */
#define DMXCHAIN_LOCK_FAMILY    194     /* TCPKER */
#define DOMAINRC_LOCK_FAMILY    195     /* TCPKER */
#define DOMAIN_LOCK_FAMILY      196     /* TCPKER */
#define ICMPSTAT_LOCK_FAMILY    197     /* TCPKER */
#define IFMULTI_LOCK_FAMILY     198     /* TCPKER */
#define IFQ_LOCK_FAMILY         199     /* TCPKER */
#define IF_SLOCK                200     /* TCPKER */
#define IGMPSTAT_LOCK_FAMILY    201     /* TCPKER */
#define INIFADDR_LOCK_FAMILY    202     /* TCPKER */
#define INPCBRC_LOCK_FAMILY     203     /* TCPKER */
#define IPFRAG_LOCK_FAMILY      204     /* TCPKER */
#define IPINTRQ_LOCK_FAMILY     205     /* TCPKER */
#define IPMISC_LOCK_FAMILY      206     /* TCPKER */
#define IPSTAT_LOCK_FAMILY      207     /* TCPKER */
#define KMEMSTAT_LOCK_FAMILY    208     /* TCPKER */
#define MBUF_LOCK_FAMILY        209     /* TCPKER */
#define NDDCHAIN_LOCK_FAMILY    210     /* TCPKER */
#define NDD_LOCK_FAMILY         211     /* TCPKER */
#define NETID_LOCK_FAMILY       212     /* TCPKER */
#define NETISR_LOCK_FAMILY      213     /* TCPKER */
#define RAW_LOCK_FAMILY         214     /* TCPKER */
#define ROUTE_LOCK_FAMILY       215     /* TCPKER */
#define SOCKET_LOCK_FAMILY      216     /* TCPKER */
#define TCBHEAD_LOCK_FAMILY     217     /* TCPKER */
#define TCPMISC_LOCK_FAMILY     218     /* TCPKER */
#define TCPSTAT_LOCK_FAMILY     219     /* TCPKER */
#define UDBHEAD_LOCK_FAMILY     220     /* TCPKER */
#define UDPSTAT_LOCK_FAMILY     221     /* TCPKER */
#define UNPCONN_LOCK_FAMILY     222     /* TCPKER */
#define UNPMISC_LOCK_FAMILY     223     /* TCPKER */
#define RFC6ADDRH_LOCK_CLASS    224     /* TP1006 */
#define RFC6ADDR_LOCK_CLASS     225     /* TP1006 */
#define RFC6DIV_LOCK_CLASS      226     /* TP1006 */
#define RFC6DPIH_LOCK_CLASS     227     /* TP1006 */
#define RFC6DPI_LOCK_CLASS      228     /* TP1006 */
#define RFC6ENTRY_LOCK_CLASS    229     /* TP1006 */
#define RFC6GLOB_LOCK_CLASS     230     /* TP1006 */
#define RFC6HEAD_LOCK_CLASS     231     /* TP1006 */
#define RFC6ITEM_LOCK_CLASS     232     /* TP1006 */
#define RFC6MISC_LOCK_CLASS     233     /* TP1006 */
#define RFC6NCTX_LOCK_CLASS     234     /* TP1006 */
#define RFC6NHEAD_LOCK_CLASS    235     /* TP1006 */
#define RFC6TCTX_LOCK_CLASS     236     /* TP1006 */
#define RFC6THEAD_LOCK_CLASS    237     /* TP1006 */
#define RFC6TRACE_LOCK_CLASS    238     /* TP1006 */
#define TRACE_LOCK_CLASS        239     /* TRACE */
#define TRCDD_LOCK_CLASS        240     /* TRACE */
#define VMM_LOCK_ALLOC          241     /* VMM */
#define VMM_LOCK_AME            242     /* VMM */
#define VMM_LOCK_APT            243     /* VMM */
#define VMM_LOCK_CLASS          244     /* VMM */
#define VMM_LOCK_LOCKWORD       245     /* VMM */
#define VMM_LOCK_LV             246     /* VMM */
#define VMM_LOCK_PDT            247     /* VMM */
#define VMM_LOCK_PMAP           248     /* VMM */
#define VMM_LOCK_RPT            249     /* VMM */
#define VMM_LOCK_SCB            250     /* VMM */
#define VMM_LOCK_VMAP           251     /* VMM */
#define VMM_LOCK_VMM            253     /* VMM */
#define AIO_AIOQ_LOCK           254     /* XAIO */
#define AIO_DEVTAB_LOCK         255     /* XAIO */
#define AIO_KNOTS_LOCK          256     /* XAIO */
#define AIO_LVM_LOCK            257     /* XAIO */
#define AIO_QUEUE_LOCK          258     /* XAIO */
#define AIO_SERVERS_LOCK        259     /* XAIO */
#define AIO_SUSP_LOCK           260     /* XAIO */
#define C327_CMN_LOCK           261     /* XC327 */
#define C327_INTR_LOCK          262     /* XC327 */
#define C327_TOP_LOCK           263     /* XC327 */
#define CAT_INTERRUPT_LOCK      264     /* XCAT */
#define CAT_QUEUE_LOCK          265     /* XCAT */
#define CAT_THREAD_LOCK         266     /* XCAT */
#define CHANNEL_LIST_LOCK       267     /* XDLC */
#define CHANNEL_LOCK            268     /* XDLC */
#define PORT_LOCK               269     /* XDLC */
#define QLLC_SAP_LOCK           270     /* XDLC */
#define QLLC_STA_LOCK           271     /* XDLC */
#define XENT_CMD_LOCK           272     /* XENT */
#define XENT_CTL_LOCK           273     /* XENT */
#define XENT_DD_LOCK            274     /* XENT */
#define XENT_SLIH_LOCK          275     /* XENT */
#define XENT_TRACE_LOCK         276     /* XENT */
#define XENT_TX_LOCK            277     /* XENT */
#define FDDD_LOCK_CLASS         278     /* XFD */
#define FDDI_CMD_LOCK           279     /* XFDDI */
#define FDDI_SLIH_LOCK          280     /* XFDDI */
#define FDDI_TRACE_LOCK         281     /* XFDDI */
#define FDDI_TX_LOCK            282     /* XFDDI */
#define LVM_LOCK_CLASS          283     /* XLVM */
#define MPQP_ADAP_LOCK          284     /* XMPQP */
#define MPQP_INTR_LOCK          285     /* XMPQP */
#define MPQP_IOCTL_LOCK         286     /* XMPQP */
#define MPQP_TRACE_LOCK         287     /* XMPQP */
#define MPS_CMD_LOCK            288     /* XMPS */
#define MPS_CTL_LOCK            289     /* XMPS */
#define MPS_DD_LOCK             290     /* XMPS */
#define MPS_SLIH_LOCK           291     /* XMPS */
#define MPS_TRACE_LOCK          292     /* XMPS */
#define MPS_TX_LOCK             293     /* XMPS */
#define KRPC_CLNTBUFFER_LOCK    294     /* XNFS */
#define KRPC_DESCRED_LOCK       295     /* XNFS */
#define KRPC_DRCACHE_LOCK       296     /* XNFS */
#define KRPC_SVCBUFFER_LOCK     297     /* XNFS */
#define KRPC_SVCS_LIST_LOCK     298     /* XNFS */
#define NFSCLNT_AUTHTBL_LOCK    299     /* XNFS */
#define NFSCLNT_CHTABLE_LOCK    300     /* XNFS */
#define NFSCLNT_LOCK            301     /* XNFS */
#define NFSCLNT_RNODE_LOCK      302     /* XNFS */
#define NFSCLNT_STRAT_LOCK      303     /* XNFS */
#define NFSCLNT_TOOBSY_LOCK     304     /* XNFS */
#define NFSSRV_ACL_LOCK         305     /* XNFS */
#define NFSSRV_EXPORT_LOCK      306     /* XNFS */
#define NFSSRV_LWAKEUP_LOCK     307     /* XNFS */
#define NFSSRV_RDBUF_LOCK       308     /* XNFS */
#define NFSSRV_RFSRESP_LOCK     309     /* XNFS */
#define NFSSRV_WLIST_LOCK       310     /* XNFS */
#define NFS_SWAP_DEV_LOCK       311     /* XNFS */
#define PRNTDD_LOCK_CLASS       312     /* XPRNT */
#define DLPI_LOCK_FAMILY        313     /* XPSE */
#define PSE_ACTIVE_LOCK         314     /* XPSE */
#define PSE_BUFC_LOCK           315     /* XPSE */
#define PSE_CONF_LOCK           316     /* XPSE */
#define PSE_IOCBLK_LOCK         317     /* XPSE */
#define PSE_LOG_LOCK            318     /* XPSE */
#define PSE_MBLK_LOCK           319     /* XPSE */
#define PSE_MODSW_LOCK          320     /* XPSE */
#define PSE_OPEN_LOCK           321     /* XPSE */
#define PSE_OSRQ_LOCK           322     /* XPSE */
#define PSE_Q_LOCK              323     /* XPSE */
#define PSE_SAD_LOCK            324     /* XPSE */
#define PSE_SQH_LOCK            325     /* XPSE */
#define PSE_STH_EXT_LOCK        326     /* XPSE */
#define PSE_TO_LOCK             327     /* XPSE */
#define PSE_TRB_LOCK            328     /* XPSE */
#define PSE_WELDQ_LOCK          329     /* XPSE */
#define XTISOCFG_LOCK_FAMILY    330     /* XPSE */
#define XTISO_LOCK_FAMILY       331     /* XPSE */
#define PTY_LOCKL_CLASS         332     /* XPTY */
#define PTY_LOCK_CLASS          333     /* XPTY */
#define ASC_EPOW_LOCK_CLASS     334     /* XSCSI */
#define HSC_ADAP_LOCK_CLASS     335     /* XSCSI */
#define HSC_EPOW_LOCK_CLASS     336     /* XSCSI */
#define HSC_IOCTL_LOCK_CLASS    337     /* XSCSI */
#define VSC_IOCTL_LOCK_CLASS    338     /* XSCSI */
#define RS_T_LOCK_HARD          339     /* XSRS */
#define RS_T_LOCK_SOFT          340     /* XSRS */
#define TAPEDD_LOCK_CLASS       341     /* XTAPE */
#define XTI4CDOWN_LOCK_CLASS    342     /* XTI4 */
#define XTI4CHEAD_LOCK_CLASS    343     /* XTI4 */
#define XTI4CITEM_LOCK_CLASS    344     /* XTI4 */
#define XTI4CUP_LOCK_CLASS      345     /* XTI4 */
#define XTI4MCL1_LOCK_CLASS     346     /* XTI4 */
#define XTI4MCL2_LOCK_CLASS     347     /* XTI4 */
#define XTI4MCL3_LOCK_CLASS     348     /* XTI4 */
#define XTI4STAT_LOCK_CLASS     349     /* XTI4 */
#define XTI4TRBF_LOCK_CLASS     350     /* XTI4 */
#define XTI4TRLV_LOCK_CLASS     351     /* XTI4 */
#define TMSCSI_LOCK_CLASS       352     /* XTM */
#define MON_DD_LOCK             353     /* XTOK */
#define MON_SLIH_LOCK           354     /* XTOK */
#define MON_TRACE_LOCK          355     /* XTOK */
#define MON_TX_LOCK             356     /* XTOK */
#define NLS_NLSMAPLOCK          357     /* XTTY */
#define NDD_LOCK_CLASS          358     /* XXNS */
#define DLCTRACE_LIST_LOCK      359     /* XDLC */
#define SSADISK_GLOBAL_LOCKS    360     /* SSA */
#define SSA_GLOBAL_LOCKS        361     /* SSA */
#define XKENT_SLIH_LOCK         362     /* XKENT */
#define XKENT_TX_LOCK           363     /* XKENT */
#define XKENT_CTL_LOCK          364     /* XKENT */
#define XKENT_TRACE_LOCK        365     /* XKENT */
#define XKENT_DD_LOCK           366     /* XKENT */
#define SCARRAY_LOCK            367     /* DISK */
#define SCARRAY_CTRL_LOCK       368     /* DISK */
#define LOGX_LOCK_CLASS         369     /* PFS */
#define XSTOK_SLIH_LOCK         370     /* XSTOK */
#define XSTOK_TX_LOCK           371     /* XSTOK */
#define XSTOK_CTL_LOCK          372     /* XSTOK */
#define XSTOK_CMD_LOCK          373     /* XSTOK */
#define XSTOK_TRACE_LOCK        374     /* XSTOK */
#define XSTOK_DD_LOCK           375     /* XSTOK */
#define CICS_IPC_INIT_LOCK      376     /* CICS */
#define CICS_IPC_EVENT_LOCK     377     /* CICS */
#define CICS_TTY_INIT_LOCK      378     /* CICS */
#define CICS_TTY_DATA_LOCK      379     /* CICS */
#define LSA_POS_LOCK            380     /* LSA */
#define LENT_CMD_LOCK           381     /* LSA */
#define LENT_CTL_LOCK           382     /* LSA */
#define LENT_DD_LOCK            383     /* LSA */
#define LENT_SLIH_LOCK          384     /* LSA */
#define LENT_TRACE_LOCK         385     /* LSA */
#define LENT_TX_LOCK            386     /* LSA */
#define BSC_EPOW_LOCK           387     /* LSA */
#define BSC_IOCTL_LOCK          388     /* LSA */
#define BSC_LOCK1               389     /* LSA */
#define BSC_LOCK2               390     /* LSA */
#define NCR8XX_AP_LOCK          391     /* XSCSI */
#define NCR8XX_IOCTL_LOCK       392     /* XSCSI */
#define HIPPI_DD_CLASS          393     /* HIPPI */
#define HIPPI_SLIH_CLASS        394     /* HIPPI */
#define HIPPI_TX_CLASS          395     /* HIPPI */
#define HIPPI_HCOM_CLASS        396     /* HIPPI */
#define HIPPI_HAPPL_CLASS       397     /* HIPPI */
#define HIPPI_IF_CLASS          398     /* HIPPI */
#define HIPPI_IF_P_CLASS        399     /* HIPPI */
#define HIPPI_FP_CLASS          400     /* HIPPI */
#define HIPPI_IPI_CLASS         401     /* HIPPI */
#define HIPPI_NDA_CLASS         402     /* HIPPI */
#define XATM_CTL_LOCK           403     /* XATM */
#define XATM_CMD_LOCK           404     /* XATM */
#define XATM_SLIH_LOCK          405     /* XATM */
#define XATM_DD_LOCK            406     /* XATM */
#define XATM_TRACE_LOCK         407     /* XATM */
#define ATMCM_TRACE_LOCK        408     /* ATMCM */
#define ATMCM_CTL_LOCK          409     /* ATMCM */
#define ATMCM_DD_LOCK           410     /* ATMCM */
#define ATMCM_CALL_LOCK         411     /* ATMCM */
#define ATMCM_Q_LOCK            412     /* ATMCM */
#define ATMIF_ATMARP_LOCK       413     /* ATMIF */
#define ATMIF_IFATM_LOCK        414     /* ATMIF */
#define ATMIF_TRACE_LOCK        415     /* ATMIF */
#define FCS_CTL_LOCK            416     /* XFCS */
#define FCS_SLIH_LOCK           417     /* XFCS */
#define FCS_TX_LOCK             418     /* XFCS */
#define FCS_BUF_LOCK            419     /* XFCS */
#define FCS_TRACE_LOCK          420     /* XFCS */
#define FCS_DD_LOCK             421     /* XFCS */
#define SCBNDD_CTL_LOCK         422     /* XSCB */
#define SCBNDD_SLIH_LOCK        423     /* XSCB */
#define SCBNDD_TX_LOCK          424     /* XSCB */
#define SCBNDD_TRACE_LOCK       425     /* XSCB */
#define SCBNDD_DD_LOCK          426     /* XSCB */
#define SSA_ADAPTER_LOCKS       427     /* SSA */
#define SSADISK_DEVICE_LOCKS    428     /* SSA */
#define XATM_TX_LOCK            429     /* XATM */
#define CNS_CTS_LOCK_CLASS      430     /* CNS */
#define CNS_SES_LOCK_CLASS      431     /* CNS */
#define ATMIF_RCVP_LOCK         432     /* ATMIF */
#define CNS_SESX_LOCK_CLASS     433     /* CNS */
#define CNSMP_SES_LOCK_CLASS    434     /* CNS */
#define FSC_IOCTL_LOCK_CLASS    435     /* FSC */
#define FSC_LOCK_CLASS          436     /* FSC */
#define FCS_ENTITY_LOCK         437     /* XFCS */
#define XPM_TX_LOCK             438     /* XPM */
#define XPM_ISR_LOCK            439     /* XPM */
#define XPM_VNET_LOCK           440     /* XPM */
#define XPM_ALT_LOCK            441     /* XPM */
#define VMM_ZQ_LOCK             442     /* VMM */
#define SYSCONFIG_LOCK          443     /* IOS */
#define S_SCSI_AP_LOCK          444     /* XSCSI */
#define S_SCSI_IOCTL_LOCK       445     /* XSCSI */
#define VSD_LOCK_CLASS          446     /* PSSP */
#define HSD_LOCK_CLASS          447     /* PSSP */
#define CSS_LOCK_CLASS          448     /* PSSP */
#define USR_SPACE_LOCK_CLASS    449     /* PSSP */
#define ATMSOCK_LOCK            450     /* ATMSOC */
#define ATMSOCK_USRREQ_LOCK     451     /* ATMSOC */
#define RS_T_LOCK_OFFL          452     /* TTY */
#define SCSES_LOCK_CLASS        453     /* SYSXSES */
#define XSRENT_SLIH_LOCK        454     /* XSRENT */
#define XSRENT_TX_LOCK          455     /* XSRENT */
#define XSRENT_CTL_LOCK         456     /* XSRENT */
#define XSRENT_TRACE_LOCK       457     /* XSRENT */
#define XSRENT_DD_LOCK          458     /* XSRENT */
#define ATMLE_LEC_LOCK          459     /* ATMLE */
#define ATMLE_CTL_LOCK          460     /* ATMLE */
#define ATMLE_DMX_LOCK          461     /* ATMLE */
#define ATMLE_CM_LOCK           462     /* ATMLE */
#define ATMLE_OFFL_LOCK         463     /* ATMLE */
#define ATMLE_TMR_LOCK          464     /* ATMLE */
#define ATMLE_DD_LOCK           465     /* ATMLE */
#define ATMLE_TRACE_LOCK        466     /* ATMLE */
#define VDASD_LOCK_CLASS        467     /* VDASD */
#define VCDROM_LOCK_CLASS       468     /* VCDROM */
#define HAL_CTL_LOCK            469     /* 400TR */
#define DT400S_DRIVER_LOCK      470     /* DT400S */
#define NFSV3_SVC_LIST_LOCK     471     /* NFSV3 */
#define NFSV3_RFS_ASYC_LOCK     472     /* NFSV3 */
#define NFSV3_RFS_RLLST_LOCK    473     /* NFSV3 */
#define NFS3CLNT_LOCK           474     /* NFSV3 */
#define NFSV3_RQCRED_LOCK       475     /* NFSV3 */
#define NFSV3_MI_LOCK           476     /* NFSV3 */
#define NFSV3_CLNT_ASYC_LOCK    477     /* NFSV3 */
#define NFSV3_SYNCBUSY          478     /* NFSV3 */
#define NFSV3_KSTAT_LOCK        479     /* NFSV3 */
#define NFSV3_RND_STATE_LOCK    480     /* NFSV3 */
#define NFSV3_RNODE_VLOCK       481     /* NFSV3 */
#define NFSV3_CHTABLE_LOCK      482     /* NFSV3 */
#define NFSV3_UNIXATHTB_LOCK    483     /* NFSV3 */
#define NFSV3_DESATHTB_LOCK     484     /* NFSV3 */
#define NFSV3_KERBATHTB_LOCK    485     /* NFSV3 */
#define NFSV3_RTABLE_LOCK       486     /* NFSV3 */
#define NFSV3_NEWNUM_LOCK       487     /* NFSV3 */
#define NFSV3_MINOR_LOCK        488     /* NFSV3 */
#define NFSV3_NTM_HEAD_LOCK     489     /* NFSV3 */
#define NFSSRV_EXPORTED_LOCK    490     /* NFSV3 */
#define NFSSRV_CL_VN_LOCK       491     /* NFSV3 */
#define NFSV2_CLNT_ASYC_LOCK    492     /* NFSV3 */
#define NFSV3_DNLC_VPLS_LOCK    493     /* NFSV3 */
#define NFSV3_DNLC_FREE_LOCK    494     /* NFSV3 */
#define NFSV3_DNLC_HASH_LOCK    495     /* NFSV3 */
#define NFSV2_SYNCBUSY          496     /* NFSV3 */
#define NFSV3_KRPC_SKPT_HEAD    497     /* NFSV3 */
#define NFSV3_KRPC_WRKQ_LOCK    498     /* NFSV3 */
#define NFSV3_MI_VFS_LOCK       499     /* NFSV3 */
#define NFSV2_MI_VFS_LOCK       500     /* NFSV3 */
#define NFS_RNODE_RWLOCK        501     /* NFSV3 */
#define NFS_TRB_CACHE_LOCK      502     /* NFSV3 */
#define NFS_KMEM_ALLOC_LOCK     503     /* NFSV3 */
#define NFS_PLUS_GLUE_LOCK      504     /* NFSV3 */
#define KUDP_DRCACHE_LOCK       505     /* NFSRPC */
#define KTCP_DRCACHE_LOCK       506     /* NFSRPC */
#define KRPC_CLNTRTCM_LOCK      507     /* NFSRPC */
#define KRPC_RTCMHEAD_LOCK      508     /* NFSRPC */
#define NLM_GLOBAL_LOCK         509     /* NFSNLM */
#define NLM_SYSID_LOCK          510     /* NFSNLM */
#define NLM_DELAY_LOCK          511     /* NFSNLM */
#define NLM_LMSYSID_LOCK        512     /* NFSNLM */
#define NLM_VNODES_LOCK         513     /* NFSNLM */
#define XDPMP_DD_LOCK           514     /* SYSXDPMP */
#define XDPMP_TRACE_LOCK        515     /* SYSXDPMP */
#define XDPMP_SLIH_LOCK         516     /* SYSXDPMP */
#define XDPMP_CTL_LOCK          517     /* SYSXDPMP */
#define XDPMP_TX_LOCK           518     /* SYSXDPMP */
#define SCIE_PORT_LOCK          519     /* SYSXSCIE */
#define SCIE_HNDL_LOCK          520     /* SYSXSCIE */
#define SCIE_TRACE_LOCK         521     /* SYSXSCIE */
#define KRPC_XPRT_LOCK          522     /* NFSRPC */
#define RTI_LOCK_FAMILY         523     /* TCPKER */
#define IP_MROUTE_LOCK_FAM      524     /* TCPKER */
#define IPPMTU_LOCK_FAMILY      525     /* TCPKER */
#define ECP_LOCK_CLASS          526     /* XPRNT */
#define XPHENT_SLIH_LOCK        527     /* XPHENT */
#define XPHENT_TX_LOCK          528     /* XPHENT */
#define XPHENT_CTL_LOCK         529     /* XPHENT */
#define XPHENT_TRACE_LOCK       530     /* XPHENT */
#define XPHENT_DD_LOCK          531     /* XPHENT */
#define XPHENT_IO_LOCK          532     /* XPHENT */
#define VMM_LOCK_STAB           533     /* VMM */
#define IN6IFADDR_LOCK_FAMILY   534     /* TCPKER */
#define IP6FRAG_LOCK_FAMILY     535     /* TCPKER */
#define IFADDRLIST_LOCK_FAMILY  536     /* TCPKER */
#define IF6MULTI_LOCK_FAMILY    537     /* TCPKER */
#define VMM_NEW_PTA_LOCK        538     /* VMM */
#define XSRENT_IO_LOCK          539     /* XSRENT */
#define XCS_SLIH_LOCK           540     /* XCS */
#define XCS_TX_LOCK             541     /* XCS */
#define XCS_CTL_LOCK            542     /* XCS */
#define XCS_TRACE_LOCK          543     /* XCS */
#define XCS_DD_LOCK             544     /* XCS */
#define MTN_DD_LOCK             545     /* MTNDD */
#define VMM_UKERN_LOCK          546     /* VMM */
#define VMM_LOCK_PDT_ALLOC      547     /* VMM */
#define VMM_LOCK_PDT_IOLIST     548     /* VMM */
#define VMM_LOCK_COMP           549     /* VMM */
#define VMM_LOCK_FRS_FREENF     550     /* VMM */
#define VMM_LOCK_LRUREQ		551	/* VMM */
#define VMM_LOCK_PDT_BUF_CLASS  552     /* VMM */
#define DIOPOOL_LOCK_CLASS      553     /* JFS */
#define CACHEFS_CACHELOCK       554     /* CACHFS */
#define CACHEFS_KSTATKEYLOCK    555     /* CACHFS */
#define CACHEFS_CN_FREELIST     556     /* CACHFS */
#define CACHEFS_KMEMLOCK        557     /* CACHFS */
#define CACHEFS_CNODECNT        558     /* CACHFS */
#define CACHEFS_RENAMELOCK      559     /* CACHFS */
#define CACHEFS_MINORLOCK       560     /* CACHFS */
#define CACHEFS_IOMUTEX         561     /* CACHFS */
#define CACHEFS_CFSWORK_LOCK    562     /* CACHFS */
#define CACHEFS_FGMUTEX         563     /* CACHFS */
#define CACHEFS_GCMUTEX         564     /* CACHFS */
#define CACHEFS_FSCACHE         565     /* CACHFS */
#define CACHEFS_CNODELIST       566     /* CACHFS */
#define CACHEFS_CPRLOCK         567     /* CACHFS */
#define CACHEFS_CONTENTS        568     /* CACHFS */
#define CACHEFS_FSLIST          569     /* CACHFS */
#define CACHEFS_LOGGING         570     /* CACHFS */
#define CACHEFS_CFSREQ          571     /* CACHFS */
#define CACHEFS_WORKQ           572     /* CACHFS */
#define CACHEFS_CNODE_RW        573     /* CACHFS */
#define CACHEFS_CNODE_STATE     574     /* CACHFS */
#define CACHEFS_SEGKMAP_LOCK    575     /* CACHFS */
#define VMM_MSEM_LOCK           576     /* VMM */
#define TMSSA_GLOBAL_LOCKS      577     /* SSA */
#define LDR_KERNEL              578     /* LDR */
#define LDR_LIBRARY             579     /* LDR */
#define LDR_PROCESS             580     /* LDR */
#define LDR_KERNEXT             581     /* LDR */
#define LDR_SHLAP               582     /* LDR */
#define SCXMA_CONF_LOCK         583     /* CXMADD*/
#define SCXMA_DR_LOCK           584     /* CXMADD*/
#define SCXMA_POLL_LOCK         585     /* CXMADD*/
#define SCXMA_KME_LOCK          586     /* CXMADD*/
#define SCXMA_BD_LOCK           587     /* CXMADD*/
#define SCXMA_CH_LOCK           588     /* CXMADD*/
#define AUTOFS_NODE_LIST        589     /* AutoFS  */
#define AUTOFS_MINOR            590     /* AutoFS  */
#define AUTOFS_NODE_COUNT       591     /* AutoFS  */
#define AUTOFS_NODE             592     /* AutoFS  */
#define AUTOFS_AI_VFS_LOCK      593     /* AutoFS  */
#define AUTOFS_NODE_RW          594     /* AutoFS  */
#define HIPNDD_DD_LOCK          595     /* HIPNDD  */
#define HIPNDD_TRACE_LOCK       596     /* HIPNDD  */
#define HIPNDD_TX_LOCK          597     /* HIPNDD  */
#define HIPNDD_CLT_LOCK         598     /* HIPNDD  */
#define HIPNDD_SLIH_LOCK        599     /* HIPNDD  */
#define HIPNDD_POOL_LOCK        600     /* HIPNDD  */
#define HIPNDD_TXQ_LOCK         601     /* HIPNDD  */
#define SYSML_LOCK_CLASS        602     /* SYSML   */
#define XATM_RV_LOCK            603     /* XATM */
#define XATM_TXBUF_LOCK         604     /* XATM */
#define GRAPHICS_RCM            605     /* GRA */
#define GRAPHICS_DD             606     /* GRA */
#define GPFS_LOCK_BRL		607	/* GPFS */
#define GPFS_LOCK_LKOBJWAIT	608	/* GPFS */
#define GPFS_LOCK_PUD		609	/* GPFS */
#define GPFS_LOCK_RL		610	/* GPFS */
#define GPFS_LOCK_RLSLEEPER	611	/* GPFS */
#define GPFS_LOCK_PINTABLE	612	/* GPFS */
#define GPFS_LOCK_MB		613	/* GPFS */
#define GPFS_LOCK_VINFOACC	614	/* GPFS */
#define GPFS_LOCK_VINFOINT	615	/* GPFS */
#define GPFS_LOCK_MMFSNODE	616	/* GPFS */
#define GPFS_LOCK_COMMONRL	617	/* GPFS */
#define GPFS_LOCK_TSBUF		618	/* GPFS */
#define GPFS_LOCK_LOOKUP	619	/* GPFS */
#define GPFS_LOCK_NFS		620	/* GPFS */
#define GPFS_LOCK_MOUNTS	621	/* GPFS */
#define GPFS_LOCK_NEEDRESV	622	/* GPFS */
#define GPFS_LOCK_SHSEG		623	/* GPFS */
#define GPFS_LOCK_KSYNCH	624	/* GPFS */
#define SCDISK_LOCK_CLASS2      625     /* DISK */
#define VMM_SERF_LOCK           626     /* VMM */
#define SF_TRACE_LOCK		627     /* TCPKER */ 
#define NBC_LIST_LOCK		628     /* TCPKER */
#define NBC_HASH_LOCK		629     /* TCPKER */
#define NBC_OFILE_LOCK		630     /* TCPKER */
#define NBC_TRACE_LOCK		631     /* TCPKER */
#define GXENT_SLIH_LOCK		632     /* GXENT */
#define GXENT_CTL_LOCK		633     /* GXENT */
#define GXENT_RX_LOCK		634     /* GXENT */
#define GXENT_TX_LOCK		635     /* GXENT */
#define GXENT_TRACE_LOCK	636     /* GXENT */
#define GXENT_DD_LOCK		637     /* GXENT */
#define FLOW6_LOCK_FAMILY	638     /* TCPKER */
#define IN6ANYA_LOCK_FAMILY	639     /* TCPKER */
#define ALLOC_LOCK_CLASS	640     /* SYSALLOC */
#define TS_TRACE_LOCK           641     /* TSHK */
#define TS_PORT_LOCK            642     /* TSHK */
#define TS_HNDL_LOCK            643     /* TSHK */
#define RTENTRY_LOCK_FAMILY	644	/* TCPKER */
#define XPHENT_RX_LOCK          645     /* XPHENT */
#define VMM_LOCK_RMMAP          646     /* SYSVMM */
#define VMM_LOCK_WAITLIST	647	/* VMM */
#define PROC_LOCK_DISA_CLASS	648	/* PROC */
#define RUNQ_CLASS		649	/* PROC */
#define SLIST_CLASS		650	/* PROC */
#define ELIST_CLASS		651	/* PROC */
#define VPATH_DD_LOCK		652	/* VPATH */
#define VPATH_TRACE_LOCK	653	/* VPATH */
#define VPATH_ADPT_LOCK		654	/* VPATH */
#define VPATH_VCBK_LOCK		655	/* VPATH */
#define VPATH_PENDQ_LOCK	656	/* VPATH */
#define VPATH_XBUF_LOCK		657	/* VPATH */
#define SHTOK_SLIH_LOCK         658     /* SHTOK */
#define SHTOK_TX_LOCK           659     /* SHTOK */
#define SHTOK_CTL_LOCK          660     /* SHTOK */
#define SHTOK_TRACE_LOCK        661     /* SHTOK */
#define SHTOK_DD_LOCK           662     /* SHTOK */
#define VNC_INIT_LOCK_CLASS	663	/* SYSPFS */
#define VNC_HASH_LOCK_CLASS	664	/* SYSPFS */
#define XCS_RX_LOCK		665	/* XCS */
#define INADDR_HASH_LOCK_FAMILY 667     /* TCPKER */
#define VMM_LOCK_LRU		668	/* VMM */
#define HA_HAEH_LOCK		669	/* HA */
#define HA_EVENT_LOCK		670	/* HA */
#define HA_FREEZE_LOCK		671	/* HA */
#define NBC_PSEG_LOCK		672     /* TCPKER */
#define CRID_LOCK_CLASS         673     /* PROC */
#define AACCT_LOCK_CLASS        674     /* PROC */
#define FRCA_LOCK_FAMILY        675     /* FRCA */
#define ATM_MPC_LOCK            676     /* ATMLE */
#define ATM_MPOA_LOCK           677     /* ATMLE */
#define ATM_MPC_TRACE_LOCK      678     /* ATMLE */
#define USER_EVENT_CLASS	680     /* -- no longer used -- */
#define	XETHCHAN_DD_LOCK	681	/* ETHERCHANNEL */
#define	XETHCHAN_TRACE_LOCK	682	/* ETHERCHANNEL */
#define DUMP_LOCK_CLASS		683	/* system dump */
#define IHASH_LOCK_CLASS	684	/* JFS */  
#define PROCFS_GLBLOCK_CLASS    685     /* PROCFS */
#define USCHED_LOCK_CLASS	686	/* PROC */  
#define PROCFS_PRCLOCK_CLASS    687     /* PROCFS */
#define PROCFS_PRLOCK_CLASS     688     /* PROCFS */
#define PROCFS_VNODE_CLASS      689     /* PROCFS */
#define IOCP_LOCK_FAMILY	690	/* IOCP */  
#define PROCHR_LOCK		691	/* SYSPROC */  
#define TWD_DD_LOCK             692     /* XTWDLCK */
#define J2_LOCK_CLASS		693	/* J2 */
#define J2_FILESYS_LOCK_CLASS	694	/* J2 */
#define J2_RENAME_LOCK_CLASS	695	/* J2 */
#define J2_NHCLASS_LOCK_CLASS	696	/* J2 */
#define J2_ICACHE_LOCK_CLASS	697	/* J2 */
#define J2_ICCLASS_LOCK_CLASS	698	/* J2 */
#define J2_IHCLASS_LOCK_CLASS	699	/* J2 */
#define J2_IRDWR_LOCK_CLASS	700	/* J2 */
#define J2_INODE_LOCK_CLASS	701	/* J2 */
#define J2_PAGER_XRDWR_CLASS	702	/* J2 */
#define J2_PAGER_XSPIN_CLASS	703	/* J2 */
#define J2_PAGER_LOCK_CLASS	704	/* J2 */
#define J2_PAGERIO_LOCK_CLASS	705	/* J2 */
#define J2_PAGERDEVICE_CLASS	706	/* J2 */
#define J2_PAGEROBJECT_CLASS	707	/* J2 */
#define J2_IOCACHE_LOCK_CLASS	708	/* J2 */
#define J2_BCACHE_LOCK_CLASS	709	/* J2 */
#define J2_BCCLASS_LOCK_CLASS	710	/* J2 */
#define J2_BHCLASS_LOCK_CLASS	711	/* J2 */
#define J2_BMAP_LOCK_CLASS	712	/* J2 */
#define J2_IMAP_LOCK_CLASS	713	/* J2 */
#define J2_IAGFREE_LOCK_CLASS	714	/* J2 */
#define J2_AG_LOCK_CLASS	715	/* J2 */
#define J2_LOG_LOCK_CLASS	716	/* J2 */
#define J2_LOGRDWR_LOCK_CLASS	717	/* J2 */
#define J2_LOGGC_LOCK_CLASS	718	/* J2 */
#define J2_LOGSYNC_LOCK_CLASS	719	/* J2 */
#define J2_LOGTBL_LOCK_CLASS	720	/* J2 */
#define J2_LCACHE_LOCK_CLASS	721	/* J2 */
#define J2_LIO_LOCK_CLASS	722	/* J2 */
#define J2_TXN_LOCK_CLASS	723	/* J2 */
#define J2_DCACHE_LOCK_CLASS	724	/* J2 */
#define J2_DIO_LOCK_CLASS	725	/* J2 */
#define J2_RIO_LOCK_CLASS	726	/* J2 */
#define VMM_ATTACH_LOCK         727     /* VMM */
#define NUMA_MIG_GROUP_LOCK     728     /* NUMA */
#define RS_REGISTRY_LOCK        729     /* NUMA */
#define VMM_LOCK_SCB_GROW       730     /* VMM */
#define VM_LDINFO_CLASS		731	/* IAVMM */
#define SYSINFO_CLASS           732     /* PROC */
#define BATM_DD_LOCK            733     /* BATM */
#define BATM_TRACE_LOCK         734     /* BATM */
#define BATM_CMD_LOCK           735     /* BATM */
#define BATM_SLIH_LOCK          736     /* BATM */
#define BATM_TX_LOCK            737     /* BATM */
#define BATM_RX_LOCK            738     /* BATM */
#define BOOSTABLE_ELIST		739	/* PROC */  
#define WLM_CLASSES_LOCK	740     /* WLM */
#define WLM_RULES_LOCK		741     /* WLM */
#define WLM_BIO_LOCK		742	/* WLM */
#define U_FD_RLOCK_CLASS        743     /* LFS */
#define RID_LOCK_CLASS		744	/* IAVMM */
#define MPDATA_LOCK             745     /* SYSNUMA */  
#define LDATA_GROW_LOCK         746     /* LDATA */
#define SAS_LOCK_CLASS		747	/* IAVMM */
#define PKEY_LOCK_CLASS		748	/* IAVMM */
#define UDBHCHN_LOCK_FAMILY     749     /* TCPKER */
#define TCBHCHN_LOCK_FAMILY     750     /* TCPKER */
#define PMAPI_CONTEXT_LOCK	751     /* PMAPI */
#define PMAPI_ALLOC_LOCK	752     /* PMAPI */
#define PMAPI_PROC_LOCK		753     /* PMAPI */
#define KDM_SYS_LOCK_CLASS      754     /* KDM */
#define KDM_EVENT_LOCK_CLASS    755     /* KDM */
#define KDM_RW_LOCK_CLASS       756     /* KDM */
#define KDM_REQ_LOCK_CLASS      757     /* KDM */
#define VMM_LOCK_CKRS		758     /* VMM */
#define VPATH_RETNQ_LOCK        759     /* VPATH */
#define VPATH_DEAMON_LOCK       760     /* VPATH */
#define AIO_TID_SUSP_LOCK       761     /* XAIO */
#define LDATA_CONTROL_LOCK    	762     /* LDATA */
#define PROC_LOCK_SESS_CLASS    763     /* PROC */
#define PROC_LOCK_PAR_CLASS     764     /* PROC */
#define VMM_ATT_HASH_LOCK       765     /* VMM */
#define CACHEFS_KSTATLIST_LOCK  766     /* CACHFS */
#define	AUDIT_STREAM_CLASS	767	/* SECRTY */
#define U_PN_CLASS              768     /* LFS */
#define PMAPI_PATCH_LOCK	769	/* PMAPI */
#define SECURE_ENV_LOCK         770     /* SECRTY */
#define ICA_RNG_LOCK_CLASS      771     /* IBM Crypto Accerator Random */
#define ICA_DES_LOCK_CLASS      772     /* IBM Crypto Accerator CMD DES/3DES */
#define ICA_DES_USE_LOCK_CLASS  773	/* IBM Crypto Accerator RES DES/3DES */
#define ICA_IWD_LOCK_CLASS      774     /* IBM Crypto Accerator multi-card */
#define ICA_WP_LOCK_CLASS       775     /* IBM Crypto Accerator RSA wait Q */
#define ICA_RSA_LOCK_CLASS	776	/* IBM Crypto Accerator RSA cmd reg */
#define ICA_RSA_PP_LOCK_CLASS	777	/* IBM Crypto Accerator RSA free pp */
#define ICA_VPD_LOCK_CLASS      778     /* IBM Crypto Accerator multi-card */
#define ICA_RNG_USE_LOCK_CLASS  779     /* IBM Crypto Accerator multi-card */
#define SCENT_SLIH_LOCK		780	/* pciscent */
#define SCENT_TX_LOCK		781	/* pciscent */
#define SCENT_RXBUF_LOCK	782	/* pciscent */
#define SCENT_CMD_LOCK		783	/* pciscent */
#define SCENT_CTL_LOCK		784	/* pciscent */
#define SCENT_TRACE_LOCK	785	/* pciscent */
#define SCENT_DD_LOCK		786	/* pciscent */
#define LOSTIO_SCAN_LOCK	787     /* HA/SHD */
#define LDATA_FREE_LOCK    	788     /* LDATA */
#define INTSYS_LOCK_CLASS    	789     /* INTSYS_LOCK */
#define J2_CURSOR_LOCK_CLASS    790     /* J2 */
#define J2_HELP_LOCK_CLASS      791     /* J2 */
#define RPN_LOCK	    	792     /* sysalloc */
#define VMM_LOCK_VMINT		793	/* VMM */
#define ALLOCCDT_LOCK           794     /* SYSALLOC */
#define EEH_LOCK_CLASS          795     /* IOS */
#define VMM_LOCK_DRLIST		796	/* VMM */
#define VMM_FIXLMB_LOCK         797     /* VMM */
#define VMM_RMLMB_LOCK          798     /* VMM */
#define IPSEC_OFFLOAD_LOCK      799     /* IPSEC */
#define IPSEC_OFFLOAD_DEV_LOCK  800     /* IPSEC */
#define VMM_LOCK_LGPG_VSID      801     /* VMM */
#define WLM_LIMITS_LOCK         802     /* WLM */
#define SISSCSI_AP_LOCK         803     /* SIS based SCSI ap lock */
#define SISSCSI_IOCTL_LOCK      804     /* SIS based SCSI IOCTL */
#define ISCSI_IOCTL_LK_CLASS    805     /* ISCSI */
#define ISCSI_LOCK_CLASS        806     /* ISCSI */
#define	RANDOM_LOCK_CLASS	807	/* Random number generator */
#define SF_TTY_LOCK             808     /* SFDD */
#define SF_FREEZE_LOCK          809     /* SFDD */
#define SF_PM_LOCK              810     /* SFDD */
#define WLM_EVENT_LOCK		811	/* WLM */
#define VMM_LOCK_GA_SCB         812     /* VMM */
#define PILE_LIST_LOCK          813     /* lfs/pile */
#define PILE_LOCK_CLASS         814     /* lfs/pile */
#define PILE_ALLOC_LOCK_CLASS   815     /* lfs/pile */
#define IOSTAT_LOCK_CLASS   	816     /* iostat */
#define GOENT_SLIH_LOCK		817     /* pcigoent */
#define GOENT_TX_LOCK		818     /* pcigoent */
#define GOENT_CTL_LOCK		819     /* pcigoent */
#define GOENT_TRACE_LOCK	820     /* pcigoent */
#define GOENT_DD_LOCK		821     /* pcigoent */
#define RMSS_LOCK_CLASS         822     /* rmss tool */
#define PCM_LOCK_CLASS          823     /* mpio path control lock */
#define IP6RTEXPIRE_LOCK_FAMILY 824     /* TCPKER */
#define VMM_LOCK_VMPOOL         825     /* VMM */
#define BATM_EEH_LOCK		826	/* BATM */
#define XDPMP_ENTRY_LOCK	827	/* SYSXDPMP entry LOCK */
#define TCP_PORT_FAMILY		828	/* TCP port lock */
#define UDP_PORT_FAMILY		829	/* UDP port lock */
#define MPATH_DD_LOCK		830	/* MPATH */
#define MPATH_TRACE_LOCK	831	/* MPATH */
#define MPATH_ADPT_LOCK		832	/* MPATH */
#define MPATH_VCBK_LOCK		833	/* MPATH */
#define MPATH_PENDQ_LOCK	834	/* MPATH */
#define MPATH_XBUF_LOCK		835	/* MPATH */
#define MPATH_RETNQ_LOCK        836     /* MPATH */
#define MPATH_DEAMON_LOCK       837     /* MPATH */
#define POLL_CACHE_CLASS	838	/* poll cache lock */
#define POLL_CACHE_EVENT_CLASS	839	/* poll cache event lock */
#define POLL_CACHE_LIST_CLASS	840	/* poll cache list lock */
#define PS_ID_LOCK		841	/* pollset ID lock */
#define AIO_SIGINFO_LOCK	842	/* XAIO */
#define SISRAID_AP_LOCK         843     /* SIS based SCSI (RAID) ap lock */
#define SISRAID_IOCTL_LOCK      844     /* SIS based SCSI (RAID) IOCTL */
#define RTIPC_CLASS		845     /* posix real time ipc locks */
#define IP6NDSOL6_LOCK_FAMILY   846     /* TCPKER */
#define KMEMUSAGE_LOCK		847	/* TCPKER */
#define ACCT_DISKIO_LOCK	848	/* AACCT Disk IO Lock */
#define ACCT_PROJECT_LOCK	849	/* AACCT Project Lock */
#define LOCK_IPFC_TX_CLASS	850	/* IP over FC xmit lock */
#define LOCK_IPFC_RX_CLASS	851	/* IP over FC recv lock */
#define LOCK_IPFC_TRC_CLASS	852	/* IP over FC trace lock */
#define ACCT_CPUMEM_LOCK        853     /* AACCT cpu/memory lock */
#define NRS_LRU_LOCK            854     /* XNFS */
#define NRS_GID_HASH_LOCK       855     /* XNFS */
#define NRS_UID_HASH_LOCK       856     /* XNFS */
#define NRS_STR_HASH_LOCK       857     /* XNFS */
#define NFS4SERV_PFS_LOCK	858	/* XNFS */
#define NFS4SERV_RESARRAY_LOCK	859	/* XNFS */
#define NFS_EXPORT_CACHE_LOCK	860	/* XNFS */
#define NRS_NOBODY_LOCK		861	/* XNFS */
#define KRPC_GSS_LOCK           862     /* XNFS */
#define BENT_SLIH_LOCK		863     /* BENT */
#define BENT_CTL_LOCK		864     /* BENT */
#define BENT_RX_LOCK		865     /* BENT */
#define BENT_TX_LOCK		866     /* BENT */
#define BENT_TRACE_LOCK		867     /* BENT */
#define BENT_DD_LOCK		868     /* BENT */
#define NETWLM_LOCK_FAMILY	869	/* NETWLM */
#define SEA_DD_ACS_LOCK		870	/* SEA */
#define SEA_DD_HASH_LOCK	871	/* SEA */
#define SEA_GVRP_LOCK		872	/* SEA GVRP lock */
#define	NFS4CLNT_FSID_LOCK	873	/* XNFS */
#define	NFS4CLNT_SERV_LOCK	874	/* XNFS */
#define	NFS4CLNT_LOCK		875	/* XNFS */
#define	NFSV4_RND_STATE_LOCK	876	/* XNFS */
#define	NFSV4_RNODE_VLOCK	877	/* XNFS */
#define VENT_SLIH_LOCK		878	/* pcivent */
#define VENT_TX_LOCK		879	/* pcivent */
#define VENT_CTL_LOCK		880	/* pcivent */
#define VENT_TRACE_LOCK		881	/* pcivent */
#define VENT_DD_LOCK		882	/* pcivent */
#define EN_ALLOC_LOCK_FAMILY	883	/* EN TABLE */
#define VIOENT_TX_LOCK          884     /* VIOENT Transmit Lock     */
#define VIOENT_RQ_LOCK          885     /* VIOENT Receive Q Lock    */
#define VIOENT_RPOOL_LOCK       886     /* VIOENT Receive Pool Lock */
#define VIOENT_ACS_LOCK         887     /* VIOENT ACS Lock          */
#define VIOENT_DD_LOCK          888     /* VIOENT DD Control Lock   */
#define VIOENT_TRACE_LOCK       889     /* VIOENT Trace Lock        */
#define PMAPI_PIDCONTEXT_LOCK	890	/* PMAPI */
#define PMAPI_GRPCONTEXT_LOCK	891	/* PMAPI */
#define SCTPCBHEAD_LOCK_FAMILY	892	/* TCPKER */
#define SCTPCBHCHN_LOCK_FAMILY	893	/* TCPKER */
#define VMM_LOCK_LRULIST	894	/* VMM LRULIST */
#define NFSV4_SM_REVOKE_LOCK 	895	/* SM4 revoke locks */
#define NFSV4_SM_XVFS_LOCK	896	/* SM4 XVFS locks */
#define NFSV4_SM_CR_LOCK	897	/* SM4 Client Record locks */
#define NFSV4_SM_OO_LOCK	898	/* SM4 Open Owner locks */
#define NFSV4_SM_OR_LOCK	899	/* SM4 Open Record locks */
#define NFSV4_SM_FR_LOCK	900	/* SM4 File Record locks */
#define NFSV4_SM_LO_LOCK	901	/* SM4 Lock Owner Locks */
#define AIO_REQ_SEC_LOCK        902     /* XAIO */
#define AIO_BUF_SEC_LOCK        903     /* XAIO */
#define AIO_SUSP_SEC_LOCK       904     /* XAIO */
#define AIO_KNOT_SEC_LOCK       905     /* XAIO */
#define NFS_READDIR_CACHE_LOCK  906     /* NFS  */
#define USBMSTOR_LOCK_CLASS     907     /* USB Mass storage device ops */
#define USBMSTORIO_LOCK_CLASS   908     /* USB Mass storage IO */
#define J2_QHOLD_LOCK		909	/* J2 */
#define JAS_TTY_LOCK            910     /* JASDD */
#define JAS_BD_LOCK             911     /* JASDD */
#define JAS_CONF_LOCK           912     /* JASDD */
#define ICS_DD_LOCK 		913	/* iSCSI TOE Adapter DD */
#define LDATA_MASTER_LOCK    	914     /* LDATA */
#define NFSV4_SM_DR_LOCK	915	/* SM4 delegation record (DR) */
#define DC_DATA_LOCK		916	/* PROC disablement checking data */
#define NFSSRV_TOPEN_HASH	917	/* NFS */
#define NFSSRV_TOPEN_FREE	918	/* NFS */
#define KNGENT_SLIH_LOCK        919	/* pcikngent */
#define KNGENT_TX_LOCK		920	/* pcikngent */
#define KNGENT_CTL_LOCK		921	/* pcikngent */
#define KNGENT_TRACE_LOCK	922	/* pcikngent */
#define KNGENT_DD_LOCK		923	/* pcikngent */
#define XRSET_LOCK		924 	/* XRSET creation/deletion */
#define SEAHA_DD_ACS_LOCK	925	/* SEAHA*/
#define VMM_LOCK_PSMD           926     /* VMM PSM */
#define TSIB_CMD_LOCK		927     /* TopSpin 1X/4x Adapter DD */
#define TSIB_QP_LOCK		928     /* TopSpin 1X/4x Adapter DD */
#define TSIB_SLIH_LOCK		929     /* TopSpin 1X/4x Adapter DD */
#define TSIB_TRACE_LOCK		930     /* TopSpin 1X/4x Adapter DD */
#define TSIB_DD_LOCK		931     /* TopSpin 1X/4x Adapter DD */
#define TSIB_AV_LOCK		932     /* TopSpin 1X/4x Adapter DD */
#define TSIB_MPT_LOCK		933     /* TopSpin 1X/4x Adapter DD */
#define TSIB_MC_LOCK		934     /* TopSpin 1X/4x Adapter DD */
#define TSIB_MR_LOCK		935     /* TopSpin 1X/4x Adapter DD */
#define TSIB_GENERAL_LOCK	936     /* TopSpin 1X/4x Adapter DD */
#define TSIB_DBELL_LOCK 	937     /* TopSpin 1X/4x Adapter DD */
#define TSIB_SQP_LOCK   	938	/* TopSpin 1X/4x Adapter DD */
#define TSIB_RQP_LOCK   	939	/* TopSpin 1X/4x Adapter DD */
#define TSIB_SCQ_LOCK   	940	/* TopSpin 1X/4x Adapter DD */
#define TSIB_TABLE_LOCK 	941	/* TopSpin 1X/ Adapter DD */
#define MENT_SLIH_LOCK          942	/* pciment */
#define MENT_TX_LOCK            943	/* pciment */
#define MENT_CTL_LOCK           944	/* pciment */
#define MENT_TRACE_LOCK         945	/* pciment */
#define MENT_DD_LOCK            946	/* pciment */
#define IBKA_AH_LOCK            947	/* IBA */    
#define IBKA_CQ_LOCK            948	/* IBA */
#define IBKA_HCA_LOCK           949	/* IBA */
#define IBKA_QP_LOCK            950  	/* IBA */
#define IBKA_USER_LOCK          951 	/* IBA */
#define IBKA_TX_LOCK            952  	/* IBA */
#define IBKA_RX_LOCK            953	/* IBA */
#define IBKA_TRACE_LOCK         954 	/* IBA */
#define IB_ARRAY_LOCK           955	/* IBA */
#define IB_SPECIFIC_LOCK        956	/* IBA */
#define IBSP_SENDQ_LOCK         957	/* IBA */
#define IBSP_RCVQ_LOCK          958	/* IBA */
#define ICM_CQ_LOCK             959 	/* IBCMDD */
#define ICM_QP_LOCK             960 	/* IBCMDD */
#define ICM_CTL_LOCK            961 	/* IBCMDD */
#define ICM_TRACE_LOCK          962	/* IBCMDD */
#define IBIF_IFIB_LOCK          963 	/* IBIPDD */
#define IBIF_IBARP_LOCK         964 	/* IBIPDD */
#define IBIF_TRACE_LOCK         965 	/* IBIPDD */
#define IBIF_TX_LOCK            966 	/* IBIPDD */
#define IBIF_RX_LOCK            967 	/* IBIPDD */
#define GXIB_ACS_LOCK_CLASS     968	/* IBADD */
#define GXIB_LOCK               969	/* IBADD */
#define XCRYPT_DD_LOCK          970     /* XCRYPT DD Control Lock   */
#define XCRYPT_TRACE_LOCK       971     /* XCRYPT Trace Lock        */
#define XCRYPT_ACS_LOCK         972     /* XCRYPT ACS Lock          */
#define XCRYPT_TX_LOCK          973     /* XCRYPT Transmit Lock     */
#define VASI_DD_LOCK		974	/* VASI DD Control Lock		*/
#define VASI_ACS_LOCK		975	/* VASI ACS Lock		*/
#define VASI_TRACE_LOCK		976	/* VASI Trace Lock		*/
#define VASI_TX_LOCK		977	/* VASI Transmit Lock		*/
#define VASI_CRQ_LOCK		978	/* VASI CRQ Lock		*/
#define VASI_RPOOL_LOCK		979	/* VASI Receive Pool Lock	*/
#define VASI_CRQ_WQ_LOCK	980	/* VASI CRQ Workqueue Lock	*/
#define VASI_OPERATION_LOCK	981	/* VASI Operation Lock		*/

#define MOVER_OP_LOCK		982	/* Mover Operation Lock		*/
#define MIGRATION_LOCK		983	/* Migration Lock			*/
#define MIG_RCVDATA_LOCK	984	/* Receive Data Lock		*/
#define MIG_INFO_LOCK		985	/* Information 	Lock		*/
#define MOVER_HEAD_LOCK		986	/* Mover Head Lock			*/

#define	TIMERWHEEL_LOCK_FAMILY	987 /* timer wheel lock */

#define HEA_SLIH_LOCK		988     /* HEA */
#define HEA_CTL_LOCK		989     /* HEA */
#define HEA_RX_LOCK		990     /* HEA */
#define HEA_TX_LOCK		991     /* HEA */
#define HEA_TRACE_LOCK		992     /* HEA */
#define HEA_DD_LOCK		993     /* HEA */

#define SISSAS_AP_LOCK          994     /* SIS based SAS RAID ap lock */
#define SISSAS_IOCTL_LOCK       995     /* SIS based SAS RAID IOCTL */
#define SDPHCHN_LOCK_FAMILY   	996     /* SDP */
#define IBKA_MR_LOCK            997     /* IBA */
#define IBKA_MW_LOCK            998     /* IBA */

#define VFC_HOST_LOCK           1000    /* VIOS */

#define CSCSI_LOCK_CLASS        1005    /* LSI SAS protocol lock        */
#define CSCSI_IOCTL_LK_CLASS    1006    /* LSI SAS protocol ioctl lock  */
#define MPT_LOCK_CLASS          1007    /* LSI SAS adapter lock         */
#define MPT_IOCTL_LK_CLASS      1008    /* LSI SAS adapter ioctl lock   */
#define MPT_KPROC_LK_CLASS      1009    /* LSI SAS adapter kproc lock   */
#define MPT_KTHREAD_LK_CLASS    1010    /* LSI SAS adapter kthread lock */
#define SEA_TRACE_LOCK		1996	/* SEA trace lock */
#define SEA_ACCT_LOCK           1997    /* SEA accounting lock */
#define	HEA_EQ_INTR_LOCK	2001    /* HEA */
#define HEA_NEQ_INTR_LOCK	2002    /* HEA */
#define HEA_ASYNC_EVENT_LOCK    2003    /* HEA */
#define	HEA_DB_LOCK		2004    /* HEA */
#define HEA_MM_LOCK             2005    /* HEA */

#define VBSD_HOST_LOCK          2007    /* VIOS */

#define RRENT_TRACE_LOCK        2042    /* pcirrent */
#define RRENT_DD_LOCK           2043    /* pcirrent */
#define RRENT_ACS_LOCK          2044    /* pcirrent */
#define RRHBA_TRACE_LOCK        2045    /* pcirrhba */
#define RRHBA_DD_LOCK           2046    /* pcirrhba */
#define RRHBA_ACS_LOCK          2047    /* pcirrhba */
#define RRHBA_MDIO_LOCK         2048    /* pcirrhba */
#define RRHBA_ADAPTER_LOCK      2049    /* pcirrhba */

/* EWLM locks */
#define REGAPP_LIST_LOC		2050	/* EWSYS */
#define PROC_LIST_LOCK		2051	/* EWSYS */
#define INSTR_PROC_LIST_LOCK	2052	/* EWSYS */
#define NEXT_HANDLE_LOCK	2053	/* EWSYS */
#define POLICY_SERVICES_LOCK	2054	/* EWSYS */
#define RESTART_DATA_LOCK	2055	/* EWSYS */
#define ARMTRACE_LOCK		2056	/* ARM TRACE */
#define POLICY_LOCK		2057	/* EWSYS */

#define KXENT_SLIH_LOCK		2058    /* pcikxent */
#define KXENT_TX_LOCK		2059    /* pcikxent */
#define KXENT_CTL_LOCK		2060    /* pcikxent */
#define KXENT_TRACE_LOCK	2061    /* pcikxent */
#define KXENT_DD_LOCK		2062    /* pcikxent */

#define MCLUST_POOL_LOCK	2063	/* sysuipc  */

#define FORWARDER_DD_LOCK	2066	/* Forwarder */
#define FORWARDER_STREAM_LOCK	2067	/* Forwarder stream */

#define MXIB_CMD_LOCK       2084     /* PCIE Dual Port HCA  DDR */
#define MXIB_QP_LOCK        2085     /* PCIE Dual Port HCA  DDR */
#define MXIB_SLIH_LOCK      2086     /* PCIE Dual Port HCA  DDR */
#define MXIB_TRACE_LOCK     2087     /* PCIE Dual Port HCA  DDR */
#define MXIB_DD_LOCK        2088     /* PCIE Dual Port HCA  DDR */
#define MXIB_AV_LOCK        2089     /* PCIE Dual Port HCA  DDR */
#define MXIB_MPT_LOCK       2090     /* PCIE Dual Port HCA  DDR */
#define MXIB_MC_LOCK        2091     /* PCIE Dual Port HCA  DDR */
#define MXIB_MR_LOCK        2092     /* PCIE Dual Port HCA  DDR */
#define MXIB_GENERAL_LOCK   2093     /* PCIE Dual Port HCA  DDR */
#define MXIB_DBELL_LOCK     2094     /* PCIE Dual Port HCA  DDR */
#define MXIB_SQP_LOCK       2095     /* PCIE Dual Port HCA  DDR */
#define MXIB_RQP_LOCK       2096     /* PCIE Dual Port HCA  DDR */
#define MXIB_SCQ_LOCK       2097     /* PCIE Dual Port HCA  DDR */
#define MXIB_TABLE_LOCK     2098     /* PCIE Dual Port HCA  DDR */

#define NLM_SRVRDATA_LOCK       2099    /* NFSNLM */
#define IBIF_MULT_LOCK      2102      /* IBIPDD Multicast lock */
#define IBIF_SPK_LOCK       2103      /* IBIPDD Super Packet   */
#define IB_FPV6_LOCK        2104      /* IBIPDD IPv6 IB Multicast array */
#define IB_PIV6_LOCK        2105      /* IBIPDD  Locks the route IB path information */
#define IB_FINDP_LOCK       2106      /* IBIPDD  Lock array to hold find path request */
#define IB_CORR_LOCK        2107      /* IBIPDD  Lock the find path correlator CB  */

#define PKCS11_DD_LOCK        2108      /* PKCS#11 Device Driver Lock */

#define VPM_DR_LOCK		2135	/* VPM and DR serialization lock */

#define Y4_DD_LOCK_NUM          2150    /* y4crypt device driver */
#define Y4_ACS_LOCK_NUM         2151    /* y4crypt device driver */
#define Y4_TX_LOCK_NUM          2152    /* y4crypt device driver */
#define Y4_MM_TX_LOCK_NUM       2153    /* y4crypt device driver */
#define Y4_SKCH_TX_LOCK_NUM     2154    /* y4crypt device driver */
#define VMM_WLMCNT_LOCK	    	2188    /* VMM WLM count/scb_nppages lock */

#endif /* _H_LOCKNAME */
