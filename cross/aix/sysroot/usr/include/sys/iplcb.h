/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/sys/POWER/iplcb.h 1.10.6.16                      */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1988,1994              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)12       1.10.6.16  src/bos/kernel/sys/POWER/iplcb.h, syssi, bos53X, x2010_32A0 6/10/10 09:49:30 */

/*
 * COMPONENT_NAME: ROSIPL
 *
 * FUNCTIONS: Defines the RAM resident interface between
 *            the IPL Boot Process and the Operating System
 *
 * ORIGINS: 27, 83
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1994
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * @BULL_COPYRIGHT@
 *
 * Copyright (C) Bull S.A. 1994
 * LEVEL 1,  5 Years Bull Confidential and Proprietary Information
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
*/

#ifndef _H_IPLCB
#define _H_IPLCB

#include <sys/types.h>

#define HMT_ENABLED	   (0x00100000)		 /* Internal use only */
#define SMT_ENABLED	   (0x00200000)		 /* Internal use only */

typedef struct ipl_directory {                   /* IPL ROS DIRECTORY       */
  char             ipl_control_block_id[8];      /* IPL ROS ASCII string ID */
  unsigned int     ipl_cb_and_bit_map_offset;    /* offset to gpr_save_area */
  unsigned int     ipl_cb_and_bit_map_size;      /* IPL CB and bit map size */
  unsigned int     bit_map_offset;               /* offset to RAM bit map   */
  unsigned int     bit_map_size;                 /* size of the RAM bit map */
  unsigned int     ipl_info_offset;
  unsigned int     ipl_info_size;
  unsigned int     smt_info_offset;
  unsigned int     smt_info_size;
  unsigned int     splpar_info_offset;
  unsigned int     splpar_info_size;
  unsigned int	   bsr_info_offset;
  unsigned int	   bsr_info_size;
  unsigned int	   ras_info_offset;
  unsigned int	   ras_info_size;
  unsigned int	   segment_pg_offset;
  unsigned int	   segment_pg_size;
  unsigned int	   processor_sgmt_offset;
  unsigned int	   processor_sgmt_size;
  unsigned int	   console_info_offset;
  unsigned int	   console_info_size;
  unsigned int	   vrma_page_size_offset;	/* raw data as described */
  unsigned int	   vrma_page_size_size;		/* in the Oct 10, 2005 PAPR */
  unsigned int     reserved1[12];
  unsigned int     net_boot_results_offset;
  unsigned int     net_boot_results_size;
  unsigned int     reserved2[88];
  unsigned int     system_info_offset;
  unsigned int     system_info_size;
  unsigned int     buc_info_offset;
  unsigned int     buc_info_size;
  unsigned int     processor_info_offset;
  unsigned int     processor_info_size;
  unsigned int     reserved3[8];
  unsigned int     l2_data_offset;
  unsigned int     l2_data_size;
  unsigned int     reserved4[6];
  unsigned int     user_struct_offset;
  unsigned int     user_struct_size;
  unsigned int     residual_offset;
  unsigned int     residual_size;
  unsigned int     numatopo_offset;
  unsigned int     numatopo_size;
  unsigned int     lpar_id_info_offset;
  unsigned int     lpar_id_info_size;
  unsigned int     dr_proc_info_offset;
  unsigned int     dr_proc_info_size;
  unsigned int     dr_mem_info_offset;
  unsigned int     dr_mem_info_size;
  unsigned int     res_asso_id_offset;
  unsigned int     res_asso_id_size;
  unsigned int     res_asso_group_offset;
  unsigned int     res_asso_group_size;
  unsigned int     rel_prf_dst_offset;
  unsigned int     rel_prf_dst_size;
  unsigned int     asso_ref_pnt_offset;
  unsigned int     asso_ref_pnt_size;
  unsigned int	   lpar_info_offset;
  unsigned int	   lpar_info_size;
} IPL_DIRECTORY, *IPL_DIRECTORY_PTR;

/*
 * DIR_EXISTS checks the for the existence of a directory entry
 *	iplcb - pointer to the IPL control block
 *	mem - member to be checked
 */
#define DIR_EXISTS(iplcb,mem) \
	( ((uint)(&((IPL_DIRECTORY_PTR)(0))->mem)) < \
	(iplcb->s0.ipl_info_offset - sizeof(iplcb->gpr_save_area)) )

#include <sys/rosinfo.h>                  /* Information used by IPL ROS   */
typedef int ROS_TEST_TYPE;

typedef unsigned long IP_ADDR;            /* Typedefs used by network boot */
typedef unsigned char HW_ADDR[6];
typedef struct {
  IP_ADDR ip;
  HW_ADDR hw;
  } IP_HW_ADDRS;

typedef struct {
  unsigned short rcf;
  unsigned short seg[8];
  } TOK_ROUTE;

typedef struct {
  IP_ADDR ip;
  HW_ADDR hw;
  TOK_ROUTE route;
  } ARP_ENTRY;

typedef struct {
	unsigned char op;             /* opcode                       */
	unsigned char htype;          /* hardware type ethernet, etc. */
	unsigned char hlen;           /* hardware address length      */
	unsigned char hops;           /* number of gateway hops       */
	unsigned long xid;            /* transaction id               */
	unsigned short secs;          /* seconds since boot started   */
	unsigned short unused;        /* unused                       */
	IP_ADDR ciaddr;               /* client IP address (request)  */
	IP_ADDR yiaddr;               /* client IP address (reply)    */
	IP_ADDR siaddr;               /* server IP address            */
	IP_ADDR giaddr;               /* gateway IP address           */
	unsigned char chaddr[16];     /* client hardware address      */
	char sname[64];               /* server host name             */
	char file[128];               /* boot file name               */
	char vend[64];                /* vendor string                */
	} t_bootp;

typedef struct net_data2 {                      /* net boot scratch pad area */
  char is_802_3;                   /* 802.3 Ethernet protocol flag   */
  char is_IPv6;                    /* IP version 6 flag              */
  char is_iSCSI;                   /* iSCSI boot flag                */
  char unused[5];
  char chaddr[64];                 /* client hardware address        */
  char ciaddr[64];                 /* client ip address (request)    */
  char yiaddr[64];                 /* client ip address  (reply)     */
  char siaddr[64];                 /* server ip address              */
  char giaddr[64];                 /* gateway ip address             */
  char subnetmask[64];
  char vend_gw[64];                /* gateway from vendor string     */
  char bootfile[128];              /* boot file name                 */
} NET_DATA2, *NET_DATA2_PTR;

typedef struct net_data {                      /* net boot scratch pad area */
  ROS_TEST_TYPE test_mode;     /* the post test mode                        */
  int detected_error;          /* 0 implies no error detected               */
			       /* != 0 implies device specific error        */
  int adapter_present;         /* 0 implies not present, != 0 is present    */
  int adapter_bad;             /* only valid if adapter_present != 0,       */
			       /* 0 implies good, != 0 implies bad          */

  t_bootp bootpr;                  /* BOOTP Reply packet contents.  Filled    */
				   /* in if a valid BOOTP reply was received, */
				   /* otherwise will be zeros                 */
  IP_HW_ADDRS client_IP_HW;        /* Client IP and hardware addresses.       */
  ARP_ENTRY server_IP_HW;          /* BOOTP server IP, HW, and routing info   */
  ARP_ENTRY gateway_IP_HW;         /* Gateway IP, HW, and routing info        */
  ARP_ENTRY tftp_IP_HW;            /* TFTP server IP, HW, and routing info    */
  ARP_ENTRY red_gw_IP_HW;          /* Redirected GW IP, HW, and routing info  */
  ARP_ENTRY bootpr_IP_HW;          /* IP, HW, and routing info for BOOTP rep  */
  unsigned int network_type;       /* Token Ring or Ethernet                  */
  unsigned int slot_number;        /* Network adapter slot number             */
  int is_802_3;                    /* 802.3 Ethernet protocol flag            */
  int eth_dir_type;                /* Integrated ethernet or plug-in          */
  unsigned short ip_id;            /* IP identification counter               */
  unsigned int rand;               /* Random number for transaction ID's      */
  unsigned short tftp_serv_tid;    /* Transaction ID for server port          */
  unsigned short tftp_loc_tid;     /* Transaction ID for local port           */
  unsigned int adapter_open;       /* Adapter state flag                      */
  unsigned int send_counter;       /* Counter for display of packets sent     */
  unsigned int rcv_counter;        /* Counter for display of packets received */
  unsigned int net_timeout;        /* Timeout value for network reads (secs)  */
  char trans_buf[2048];            /* Transmit buffer                         */
  char rec_buf[2048];              /* Receive buffer                          */
  char frag_buf[2048];             /* Fragmentation buffer                    */

} NET_DATA, *NET_DATA_PTR;

typedef struct system_info {  /* REFER TO NOTE 1 BELOW                    */
  int num_of_procs;           /* number of processors supported           */
			      /* num_of_procs == 1 => Uni; > 1 => n-way MP*/
			      /* the value refers to the number this      */
			      /* platform is designed to handle, must look*/
			      /* at processor_info structure to determine */
			      /* the number actually present              */
  int coherency_size;         /* size of the coherence block              */
  int resv_size;              /* size of the reservation granule          */
  int lg_pg_capable;	      /* a boolean indicating large page capability */
  uint lic_perms;             /* licensing permission information that    */
			      /* has been copied from the device tree     */
#define AIX_ALLOWED	1
#define STANDALONE_DIAG_ALLOWED		2
#define ALPHA_VIOS_ALLOWED		4
  int num_of_bsrr;            /* number of 4 byte bus slot reset regs     */
  __ptr32 bsrr_addr;          /* real address of bus slot reset reg       */
			      /* PSUEDO-COMPLETE CONNECTIVITY RESET REG   */
  int tod_type;               /* type of time of day structure            */
  __ptr32 todr_addr;          /* real address of time of day regs         */
			      /* TIME OF DAY REGS                         */
  __ptr32 rsr_addr;           /* real address of reset status reg         */
			      /* SYSTEM RESET COUNT REGISTER              */
  __ptr32 pksr_addr;          /* real address of power/keylock status reg */
			      /* POWER STATUS/KEYLOCK REG                 */
  __ptr32 prcr_addr;          /* real address of power/reset control reg  */
			      /* SOFTWARE POWER ON RESET CONTROL REG      */
  __ptr32 sssr_addr;          /* real address of system specific regs     */
			      /* SYSTEM SPECIFIC SYSTEM REGISTERS         */
  __ptr32 sir_addr;           /* real address of system interrupt regs    */
			      /* ARCHITECTED SYSTEM INTERRUPT REGS        */
  __ptr32 scr_addr;           /* real address of standard config reg      */
			      /* ARCHITECTED CONFIGURATION REGS           */
  __ptr32 dscr_addr;          /* real address of device specific cfg reg  */
			      /* DEVICE SPECIFIC CONFIGURATION REGS       */
  int nvram_size;             /* byte size of nvram                       */
  __ptr32 nvram_addr;         /* real address of nvram                    */
			      /* NVRAM                                    */
  __ptr32 vpd_rom_addr;       /* real address of VPD ROM space            */
			      /* ARCHITECTED FEATURE/VPD ROM SPACE        */
  int ipl_rom_size;           /* byte size IPL ROM space                  */
  __ptr32 ipl_rom_addr;       /* real address of IPL ROM space            */
			      /* BOOT ROM                                 */
  __ptr32 g_mfrr_addr;        /* real address of global mfrr reg  if != 0 */
  __ptr32 g_tb_addr;          /* real address of global time base if != 0 */
  int g_tb_type;              /* global time base type                    */
  int g_tb_mult;              /* global time base multiplier              */
  int SP_Error_Log_Table;     /* offset from base address of NVRAM to     */
			      /* Service Processor Error Logging Table    */
  __ptr32 pcccr_addr;         /* real address of connectivity config reg  */
			      /* PSUEDO-COMPLETE CONNECTIVITY CONFIG REG  */
  __ptr32 spocr_addr;         /* real address software power off cntrl reg*/
			      /* SOFTWARE POWER OFF CONTROL REG           */
  __ptr32 pfeivr_addr;        /* real address of                          */
			      /* SMP POWER FAILURE (EPOW) EXTERNAL        */
			      /* INTERRUPT VECTOR REG                     */

			      /* beginning of APM interface (See Note 2)  */
  int access_id_waddr;        /* type of access to "loc_waddr"            */
  __ptr32 loc_waddr;          /* real address of APM space write          */
  int access_id_raddr;        /* type of access to "loc_raddr"            */
  __ptr32 loc_raddr;          /* real address of APM space read           */
			      /* end of APM interface                     */

			      /* CHRP systems use the above fields for    */
			      /* the RMO region size.  This is a 64 bit	  */
			      /* value that represents the RMO size       */
			      /* On a CHRP system a non-zero value	  */
			      /* indicates the system is in LPAR mode     */
#define rmo_size access_id_raddr			  /* High 32-bits */
#define rmo_size_lo loc_raddr				  /* Low 32-bits  */

  int architecture;           /* The model architecture of this platform  */
			      /* RS6K => RISC/6000 system architecture    */
			      /* RSPC => "PReP" system architecture       */
			      /* RS6K = 1, RSPC = 2,                      */
			      /* see AIX systemcfg.h for future values    */
  int implementation;         /* The model implementation of this platform*/
			      /* RS6K_UP_MCA => RS1, RS2, RSC, PPC UP     */
			      /* RS6K_SMP_MCA => PPC SMP                  */
			      /* RSCP_UP_PCI => PPC/PReP UP               */
			      /* RS6K_UP_MCA = 1, RS6K_SMP_MCA = 2,       */
			      /* RSCP_UP_PCI = 3                          */
			      /* see AIX systemcfg.h for future values    */
  char pkg_descriptor[16];    /* NULL terminated ASCII string             */
			      /*                                          */
			      /* EX:     'r','s','6','k','\0'             */
			      /* "rs6k" => RS1,RS2,RSC, RS6K/PPC UP models*/
			      /* "rs6ksmp" => RISC6000/PowerPC SMP models */
			      /* "rspc" => PReP/PowerPC models            */
  char subplatform[16];	      /* NULL terminated ASCII string		  */
  int spec_hw_present;        /* bit field summary of HW elements on the  */
/* platform which require special handling  */
			      /* by AIX (workarounds).                    */
			      /* For instance GR20_PRESENT indicates that */
			      /* at least one GR 2.0 part is present and  */
			      /* GR 2.0 workarounds need to be activated. */
			      /* see AIX systemcfg.h for future values    */
  char model_class[8];	      /* NULL terminated ASCII string		  */
  char eco_status;	      /* extended cache options                   */
  char unused1[1];
  ushort phn_ver;
} SYSTEM_INFO, *SYSTEM_INFO_PTR;

/****************************************************************************
   THE FOLLOWING NOTES APPLY TO THE system_info STRUCTURE DEFINED ABOVE

1. Most of these fields had been defined previous to the RISC System/6000
architecture document being approved. Those fields that refer to fields
in the architecture document contain the architecture nameing convention
in capital letters following the structure name. E.G.

  void *bsrr_addr;             * real address of bus slot reset reg       *
			       * PSUEDO-COMPLETE CONNECTIVITY RESET REG   *

2. The APM (Available Processor Mask) interface:
The loc_raddr and loc_waddr addresses are 32-bit word aligned addresses
and software is expected to access from them in 32-bit word mode.  The
space represented by *loc_raddr and *loc_waddr (which we will refer to
as APM space) represents a bitmap string in which the state of each bit
defines which processors in an SMP environment, numbered 1 through N,
are enabled and which are disabled. At least N sequential bits of APM
space must be implemented.

Processor number 1 is represented by the high order bit of the first
word with each successive bit representing the next processor number in
turn, and processor number 33 being represented by the high order bit
of the next word, etc.

The number of read words (and write words) reserved in APM space
must be at least QUOTIENT((num_of_procs - 1)/32)+1, were num_of_procs
are the number of processors supported on a given platform. To enable,
disable, or verify a given processor, software must create a 32 bit
mask and the correct APM space read/write address using the following
algorithm or equivalent:

proc_mask = (1 >> REMAINDER((proc_number - 1)/32));
wr_word_number = QUOTIENT((proc_number - 1)/32);

where the single active "1" bit in the 32-bit mask "proc_mask"
cooresponds to the processor whose number is "proc_number"; and where
wr_word_number is the zero-based 32-bit word-offset value into APM
space to be added to the read or write address (loc_raddr or loc_waddr)
to address the proper 32-bit read or write address, in APM space,
which contains the bit that cooresponds to "proc_number". NOTE:
wr_word_number is a 32-bit word offset and will need to be multiplied
by 4 to get a byte offset if required.

access_id_waddr and access_id_raddr defines the type of access required
to access APM space. 0 implies the access is a normal memory mapped
access using loads and stores. 1 implies the access must be through the
AIX machine device driver or equivalent.

if loc_raddr == loc_waddr == 0, this interface is not supported via
the IPL control block.

For more information refer to the RISC System/6000 PowerPC System
Architecture document

   END OF NOTES APPLYING TO THE system_info STRUCTURE DEFINED ABOVE
****************************************************************************/

typedef struct buc_info {
  uint  num_of_structs;       /* contains the run time value corresponding*/
			      /* the number of buc's present              */
  uint  index;                /* 0 <= index <= num_of_structs - 1,        */
			      /* assume index = n, then this              */
			      /* is the n+1th array element               */
  uint struct_size;           /* size of this structure (in bytes)        */
  int bsrr_offset;            /* bus slot reset register offset           */
			      /* (see NOTE 2 below)                       */
  uint bsrr_mask;             /* bus slot reset register mask             */
			      /* a one bit only mask which identifies the */
			      /* bit that controls the reset of this buc  */
			      /* (see NOTE 2 below)                       */
  int bscr_value;             /* configuration register value to enable   */
			      /* configuration of this buc                */
  int cfg_status;             /*  0 => buc is not configured              */
			      /*  1 => buc is configured via config regs  */
			      /*  2 => configured via hardware defaults   */
			      /*       i.e., does not have config regs    */
			      /* -1 => configuration failed               */
  int device_type;            /*  1 => this buc is executable memory      */
			      /*  2 => this buc is a processor            */
			      /*  3 => this buc is an io type             */
  int num_of_buids;           /* num of buids required by this buc (<=4)  */
  struct buid_data {
    int  buid_value;          /* assigned BUID value                      */
			      /* these values have meaning if and only    */
			      /* if the num_of_buids != 0, they are       */
			      /* assigned in order until the num_of_buids */
			      /* is satisfied. Unused buids will = -1     */
    __ptr32 buid_Sptr;        /* pointer to this BUID's own post structure*/
			      /* a NULL value => N/A                      */
  } buid_data[4];
  int mem_alloc1;             /* 1st memory allocation required (in MB)   */
  __ptr32 mem_addr1;          /* real address of mem_alloc1 area          */
			      /* if mem_alloc1 != 0, otherwise N/A        */
  int mem_alloc2;             /* 2nd memory allocation required (in MB)   */
  __ptr32 mem_addr2;          /* real address of mem_alloc2 area          */
			      /* if mem_alloc2 != 0, otherwise N/A        */
  int vpd_rom_width;          /* width of vpd interface in bytes          */
			      /* -1 => not applicable, no vpd rom present */
  int cfg_addr_inc;           /* configuration address increment in bytes */
			      /* Refer to NOTE 4 below                    */
  int device_id_reg;          /* standard configuration register contents */
			      /* -1 => not applicable                     */
  uint aux_info_offset;       /* the iplcb offset to the "device_specific"*/
			      /* array defined for this buc. e.g.,        */
			      /* if this is a processor buc, the auxilary */
			      /* struct is the processor_info array struct*/
			      /* if the device type is io type, the aux   */
			      /* struct is an io_info array struct, etc.  */
			      /* Refer to NOTE 1 below                    */
  uint feature_rom_code;      /* romscan post controls this flag          */
			      /* == 0, no test performed for romscan code */
			      /* == 1, implies romscan code device boot   */
			      /*       code detected on this card         */
			      /* == 2, implies video romscan code detected*/
			      /*       on this card.                      */
			      /* == 3->7, Reserved                        */
			      /* == 8, no romscan code found              */
  uint IOCC_flag;             /* 0 = Not IOCC. 1 = IOCC                   */
  char location[4];           /* Location code of the BUC                 */
} BUC_DATA, *BUC_DATA_PTR;

/****************************************************************************
   THE FOLLOWING NOTES APPLY TO THE buc_info STRUCTURE DEFINED ABOVE

Notes on BUC data:
1. An aux_info_offset will always point to an array element that describes
   the device that is related to the buc. For example, if the buc is a
   processor, the aux_info_offset will point to the appropriate array
   element, within the per processor array, that is associated with this
   buc.  If there is more that one aux array element related to the buc
   (such as an IOCC buc, which can support an IO bus that can contain up
   to sixteen adapters), the aux_info_offset will point to the first array
   element in the array.

2. This value, bsrr_offset, added to the bsrr_address contained in struct
   system_info, provides the address for the appropriate bus slot reset
   register for this BUC. The value bsrr_mask, when effectively or'ed
   into the bus slot reset register, will enable the appropriate buc. The
   bit inversion of bsrr_mask, when effectively and'ed into the bus slot
   reset register, will reset the appropriate buc.

3. This array is pointed to by IPL directory entry "buc_info_offset"

4. This value, cfg_addr_inc, added to the scr_addr contained in struct
   system_info, provides the addressing for the standard configuration
   registers.

   THE ABOVE NOTES APPLY TO THE buc_info STRUCTURE DEFINED ABOVE
****************************************************************************/

typedef struct processor_info {
  uint  num_of_structs;       /* contains the run time value corresponding*/
			      /* to the number of processors supported    */
  uint  index;                /* 0 <= index <= num_of_structs - 1,        */
			      /* assume index = n, then this              */
			      /* is the n+1th array element               */
  uint struct_size;           /* size of this structure (in bytes)        */
  uint per_buc_info_offset;   /* the iplcb offset to the "buc_info"       */
			      /* structure related to this device         */
  __ptr32 proc_int_area;      /* Base Address (BA) of this processors     */
			      /* interrupt presentation layer registers   */
			      /* BA+0  (CPPR||XISR without side effects)  */
			      /* BA+4  (CPPR||XISR with    side effects)  */
			      /* BA+8  (DSIER)                            */
			      /* BA+12 (MFRR)                             */
			      /* BA+xx (Additional Optional MFRR's)       */
  uint proc_int_area_size;    /* proc_int_area_size/4 is the  number of   */
			      /* interrupt presentation registers         */
  int processor_present;      /*  0 implies not present, != 0 is present  */
			      /* -1 implies not operational (failed test) */
			      /*  1 implies processor is "running" AIX    */
			      /*  2 implies processor is "looping"        */
			      /*    with link = 0 (see NOTE 1 below)      */
			      /*  3 implies this processor is available   */
			      /*    in the reset state                    */
			      /*  additional values TBDefined             */
#define PROC_DISABLED		-2
#define PROC_FAILED		-1
#define PROC_ABSENT		0
#define PROC_RUNNING_AIX	1
#define PROC_LOOPING		2
#define PROC_IN_RESET		3

  uint test_run;              /* this is a bit significant variable       */
			      /* indicating which tests were run on this  */
			      /* processor. bits are or'ed for each test. */
			      /* the corresponding bit values are herein  */
			      /* defined:                                 */
			      /* bit 0 is the least significant bit       */
			      /* test was run if and only if bit == 1     */
			      /* bit: state definition:                   */
			      /* 0  : local address bus test              */
			      /* 1  : shared address bus test             */
			      /* 2  : local data bus test                 */
			      /* 3  : shared data bus test                */
			      /* 4  : local memory data test              */
			      /* 5  : shared memory data test             */
			      /* 6  : fixed point unit test               */
			      /* 7  : floating point unit test            */
			      /* undefined bits are reserved              */
  uint test_stat;             /* this status is valid whenever test_run   */
			      /* contains a non-zero value. a value of 1  */
			      /* signifies the test corresponding to the  */
			      /* test_run bit has failed, a value of 0    */
			      /* signifies the test passed. the test      */
			      /* results DO NOT necessarily imply the     */
			      /* processor_present value == -1            */
  int  link;                  /* if  = 0, loop until non-zero             */
			      /* if != 0, branch to link_address          */
			      /* (see NOTE 1 below)                       */
  __ptr32 link_address;       /* this is branch address when link != 0    */
			      /* (see NOTE 1 below)                       */
  union {		      /*                                          */
	uint p_id;            /* unique processor identifier              */
	struct {              /*                                          */
	   ushort p_nodeid;   /* Physical NUMA Node id                    */
	   ushort p_cpuid;    /* Physical CPU id                          */
	} s0;                 /*                                          */
  } u0;                       /*                                          */
  int architecture;           /* POWER_RS   processor architecture        */
			      /* POWER_PC   etc                           */
			      /* see AIX systemcfg.h for future values    */
  int implementation;         /* POWER_RS1  processor implementation      */
			      /* POWER_RS2                                */
			      /* POWER_RSC                                */
			      /* POWER_601  etc                           */
			      /* see AIX systemcfg.h for future values    */
  int version;                /* processor version number                 */
			      /* PPC_601    etc                           */
  int width;                  /* max processor data word size (32 or 64)  */
			      /* NOT the current execution mode           */
  int cache_attrib;           /* cache attribute bit field                */
			      /* bit: state definition: (bit 0 = LSB)     */
			      /*  #       0/1                             */
			      /*  0   cache-not-present/cache-present     */
			      /*  1   separate-cache/combined-inst-data   */
			      /* undefined bits are reserved              */
  int coherency_size;         /* size of coherence block                  */
  int resv_size;              /* size of reservation granule              */
  int icache_block;           /* L1 instruction cache block size          */
  int dcache_block;           /* L1 data cache block size                 */
  int icache_size;            /* L1 instruction cache size                */
  int dcache_size;            /* L1 data cache size                       */
  int icache_line;            /* L1 instruction cache line size           */
  int dcache_line;            /* L1 data cache line size                  */
  int icache_asc;             /* L1 instruction cache associativity       */
  int dcache_asc;             /* L1 data cache associativity              */
  int L2_cache_size;          /* L2 cache size; see NOTE 6 below          */
  int L2_cache_asc;           /* L2 cache associativity                   */
  int tlb_attrib;             /* translation look-asside buffer attribute */
			      /* bit: state definition: (bit 0 = LSB)     */
			      /*  #       0/1                             */
			      /*  0   tlb-not-present/tlb-present         */
			      /*  1   separate-tlb/combined-inst-data-tlb */
			      /*  4   processor supports tlbia            */
			      /* undefined bits are reserved              */
  int itlb_size;              /* entries in instruction tlb               */
  int dtlb_size;              /* entries in data tlb                      */
  int itlb_asc;               /* instruction tlb associativity            */
  int dtlb_asc;               /* data tlb associativity                   */
  int slb_size;               /* slb size from device tree; default is 64 */
  int reserved1;
  unsigned long long ext_cl_freq;	/* extended clock frequency       */
  int reserved2;
  int priv_lck_cnt;           /* supervisor state spin lock count         */
  int prob_lck_cnt;           /* problem    state spin lock count         */
			      /* refer to notes 4,7,8 for timebase info   */
  int rtc_type;               /* processor's time base type               */
  int rtcXint;                /* nano-seconds per time base tick          */
			      /* integer  multiplier (see NOTE 4 below)   */
  int rtcXfrac;               /* nano-seconds per time base tick          */
			      /* fraction multiplier (see NOTE 4 below)   */
  uint busCfreq_HZ;           /* bus clock frequency in HERTZ             */
  int tbCfreq_HZ;             /* effective time base clock freq ( NOTE 7) */
  char proc_descriptor[16];   /* NULL terminated ASCII string for ODM DB  */
			      /* EX:     'P','O','W','E','R','\0'         */
			      /* "POWER" for POWER_RS1 & Power_RSC procs  */
			      /* "POWER2" for POWER_RS2 processors        */
			      /* "PowerPC_601" for PowerPC 601 processors */
			      /* "PowerPC_603" for PowerPC 603 processors */
			      /* "PowerPC_604" for PowerPC 604 processors */
			      /* "PowerPC_620" for PowerPC 620 processors */
  uint cec_cookie;	      /* the NUMA CEC cookie */
  uint pft_size;	      /* base 2 log of the the size of the pf table */
  uint reg_value;
  uint vmx_version;	      /* vmx version of this processor, 0 = no VMX  */
  uint dfp_version;	      /* dfp version of this processor, 0 = no DFP  */
  struct pa_prop {
        unsigned char numbytes;    /* Number of bytes of data present */
        unsigned char type;        /* attribute specifier type        */
        unsigned char data[30];    /* Data bytes. Defined in the PAPR */
				   /* as up to 256 bytes, but 30      */
				   /* should be enough for a while.   */
  } ibm_pa_features;
  uint donation;              /* Dedicated Donation enabled */
  uint spurr_version;	      /* spurr version of this processor,0=no SPURR */
#define PROC_DED_DONATION  0x1
#define PROC_SMT_BOOSTED   0x2
  uint has_purr;              /* 1 = has PURR, 0 = does not have PURR       */
  struct pa_prop ibm_pa_optimizations;
  struct pa_prop ibm_pi_features;
} PROCESSOR_DATA, *PROCESSOR_DATA_PTR;

#define phys_id u0.p_id
#define phys_cpuid u0.s0.p_cpuid
#define phys_nodeid u0.s0.p_nodeid

#define TLBIA_SUPPORT_MASK 0x08000000	/* (9) */

/*
 * Description of pa_features type 0 data bytes of interest for AIX
 *
 * Byte 2
 */
#define DATA_STREAMS_V205       0x40
#define PPR_SUPPORTED           0x4
/*
 * Byte 5
 */
#define CFAR_SUPPORTED		0x40


/*
 * Description of pa_optimizations type 0 data bytes of interest for AIX
 */

#define DATA_STREAMS_IDS        0       /* byte 0: Number of HW streams IDs */
#define DEFAULT_PREFETCH_DEPTH  1       /* byte 1: Default Prefetch Depth   */

/*
 * Description of pi_features type 0 data bytes of interest for AIX
 *
 * Byte 0
 */
#define SMT_ORDER_DEFINED       0x20	/* SMT order of activation defined */



/****************************************************************************
   THE FOLLOWING NOTES APPLY TO THE processor_info STRUCTURE DEFINED ABOVE

Notes on processor data:
1. Each processor_info structure is a template for a processor that may
   exist in a given "slot" (location).  Any processor "slots" that are
   empty will contain a value of 0 in their processor_present
   variable.

   Any processors that are present will have their state defined in the
   processor_present variable.

   When IPL ROS transfers control to AIX, one and only one processor
   will be running the AIX code and its processor_present variable will
   contain a value of "1".  This processor will be referred to as the
   "master" processor. When AIX gets control, R3 will contain the
   IPL_CB_PTR and R4 will contain the address of the "processor_info"
   structure of the running processor.

   Any remaining processors in an MP environment may be running a
   protected, memory resident program provided by IPL ROS (a value of
   "2" in the processor_present variable), or will be "available" but
   in the reset state (a value of "3" in the processor_present
   variable).  In the former case, the code continually interrogates
   the value of the "link" variable within its own processor_info
   structure as follows: If this value is 0, the processor continues to
   interrogate it; if the value is non-zero, the link_address variable
   is interpreted as a branch address and a branch to the address is
   affected by IPL ROS for the coresponding processor. When the branch
   is affected, R3 will contain the IPL_CB_PTR and R4 will contain the
   address of the "processor_info" structure of the processor.  The
   link and link_address variables of the master processor will be set,
   by IPL ROS, to indicate the starting address of the loaded code.

2. num_of_structs is a value that is dynamically determined by IPL
   ROS. Its value will be placed in each processor_info structure
   contained within the array. This value will specify the number of
   processors that is supported (but not neccessarily present) in the
   processor complex that is controlled by the IPL_ROS.

3. To guarantee compatibility between different levels of ROS and AIX,
   one must traverse through the array structure using pointers and
   offset values:

    To get to the beginning of the processor_info array,
    define your pointer variable and assign to it as follows:
    PROCESSOR_DATA_PTR per_proc_info_ptr =
	 (struct processor_info *)
	   ((uint)IPL_CB_PTR + IPL_CB_PTR->s0.processor_info_offset);

    per_proc_info_ptr may now be used for accessing and traversing
    the array.

    To find the size of the array, read it directly from the
    ipl_directory.

4. rtcXint and rtcXfrac allow for conversion between time base counter
   ticks and time-of-day.

   SUB-NOTE:
   Their values are dependent on the processors time base type,
   rtc_type. For rtc_type "1" (i.e. 601 based machines) these variables
   are set to 0 since the time base counter is defined such that its
   least significant bit is to change once per nanosecond. For other
   rtc_type values, rtcXint will be the integral number of nanoseconds
   per time base tick and rtcXfrac will be the fraction part, expressed
   to the nearest thousandth. The net result is the timebase period in
   picoseconds.

   EX: assume that the time base counter is driven by a 66MHZ clock.
   Therefor, the timebase "tick" period is 15152  rounded to the
   nearest picoseconds, from which rtcXint = 15 and rtcXfrac = 152.

   REFER TO NOTEs 7 & 8 for additional details.

5. This array is pointed to by IPL directory entry
   "processor_info_offset"

6. L2_cache_size indicates the configured or "in use" size (in bytes) of
   the L2 cache. Additional information on the L2 cache is contained in
   the l2_data structure. L2_cache_size will be set to 0 if the L2 cache
   could not be configured.

7. tbCfreq_HZ is the effective time base clock frequency rounded to the
   nearest HERTZ. If this value is set to -1, the time base counter is
   driven by a variable speed clock (as allowed by the PowerPC
   architecture).  For this case, the time base count rate must be
   determined completely by software (refer to Chapter 4 of the PowerPC
   Architecture Book II).

   REFER TO NOTEs 4 & 8 for additional details.

8. The effective time base frequency is defined to be the frequency
   that the least significant bit of the timebase counter is driven,
   assuming that the least significant bit is implemented. If some of
   the low order bits are not implemented, this does not change the
   effective time base frequency. However, it does change the minimum
   perceptible time interval that can be detected from the timebase
   counter. For example:

   assume the effective time base frequency is 500MHZ, which represents
   an effective timebase tick every 2 nanoseconds. If the two low order
   bits of the timebase reg are not implemented, the minimum detectible
   timebase increment would be 8 nanoseconds given that the effective
   frequency is 500MHZ. For this example we would have rtcXint = 2,
   rtcXfrac = 0, tbCfreq_HZ = 500,000,000.

   REFER TO NOTEs 4 & 7 for additional details.

9. If the tlbia instruction is supported, bit 4 is set in the tlb_attrib
   field.  Currently softros only sets this up for CHRP platforms.

   THE ABOVE NOTES APPLY TO THE processor_info STRUCTURE DEFINED ABOVE
****************************************************************************/

typedef struct l2_data {

  ROS_TEST_TYPE test_mode;              /* POST test mode                    */
  int  detected_error;                  /* 0 = no error; !0 = Error(s) found */
  int  adapter_present;                 /* 1 = present; 0 = absent           */
  int  adapter_bad;                     /* 0 = OK; !0 = Bad                  */
  int  mode;                            /* 0 = I/D cache; 1 = I-cache        */
  int  installed_size;                  /* Actual total size of L2 in Kbytes */
  int  configured_size;                 /* size (KB) configured by IPL ROS   */
  char type[16];                        /* See note (1)                      */
  int  size[16];                        /* See note (2)                      */
  char location[16][4];
  uint  num_of_structs;          /* contains the run time value corresponding*/
				 /* to the number of elements in this array. */
				 /* refer to notes (3) and (4) below.        */
  uint  index;                   /* 0 <= index <= num_of_structs - 1         */
				 /* assume index = n, then this              */
				 /* is the n+1th array element.              */
  uint struct_size;              /* size of this structure (in bytes)        */
  int shared_L2_cache;           /* shared by more than one using resource   */
				 /* 0 => not shared, 1 => shared.            */
  int using_resource_offset;     /* iplcb offset to the structure of the     */
				 /* environment resource that uses this      */
				 /* cache (usually a processor structure).   */
				 /* refer to NOTE (4) below                  */

/* NOTES: (1) type[i] can have one of these values:                          */
/*            - 'P' means the bad L2 cache is part of the CPU planar.        */
/*            - 'R' means the bad L2 cache is a riser card.                  */
/*            - 'L' means L2 cache consists of SIMMs and the SIMM at         */
/*               physical location location[i][] is bad.                     */
/*            - '0' means this and all subsequent entries are invalid.       */
/*                                                                           */
/*        (2) size[i] gives the size (KB) of the FRU at physical location    */
/*            location[i][].                                                 */
/*        (3) this struct, "l2_data", is an IPL ROS array. refer to the      */
/*            notes after the struct processor_info for general information  */
/*            about ROS arrays.                                              */
/*        (4) this array exists if and only if IPL_DIRECTORY.l2_data_offset  */
/*            != NULL, in which case L2_DATA.num_of_structs will indicate    */
/*            the number of L2_DATA elements in the array. if a given L2     */
/*            cache is shared by more than one resource, it's array element  */
/*            will be replicated for each resource. e.g., if two processors  */
/*            use a given L2 cache, there will be two elements in this array */
/*            describing the same physical L2 cache but pointing to the two  */
/*            different using resources (it is done this way because IPL ROS */
/*            is not allowed to change a given array element size            */
/*            dynamically). lastly, in the event of disjoint I and D caches, */
/*            two separate elements may be pointing to the same using        */
/*            resource. recapping, the L2 cache array is all inclusive in    */
/*            terms of the L2 cache compliment of the environment but may    */
/*            have replicated entries describing the same cache, in which    */
/*            case the "shared_L2_cache" flag will indicate shared L2 cache. */

} L2_DATA, *L2_DATA_PTR;

typedef struct user_info {
  __ptr32 user_id_offset;       /* pointer to a NULL terminated ascii  */
				/* string identifier. Ex: "XYZ company"*/
				/* Refer to note 4 for additional info */
  __ptr32 user_data_offset;     /* pointer to the user's data          */
  uint user_data_len;           /* byte length of *use_data_offset     */
#ifdef __64BIT_KERNEL
  __ptr32 next_offset;		/* pointer to the next user_info struct*/
#else
  struct user_info *next_offset;
#endif /* __64BIT_KERNEL */
} USER_INFO, *USER_INFO_PTR;

/************************************************************************
   THE FOLLOWING NOTES APPLY TO THE user_info STRUCTURE DEFINED ABOVE

1. The ipl_directory structure defines the presence of this structure
   as follows:

     If the "user_struct_offset" field and the "user_struct_size"
     fields are present in the ipl_directory structure (as determined
     by the length of the ipl_directory), then the control block
     supports the user_info structure. However, support does not
     neccessarily imply that there is an actual structure present. It
     is present if and only if user_struct_offset != NULL and the
     user_struct_size != 0. This is "business as usual" for determining
     which control block structures are supported and present.

     NOTE: user_struct_size should be set to "sizeof(user_info)".

2. All of the "pointers" in this structure are actually offset values
   relative to the beginning of the ipl control block.

3. Memory allocation is the users responsibility. If it is required
   that any allocated memory be protected from being reused by the OS,
   the memory bit map must be updated by the user to achieve this.

4. The user id string should identify the company (user). It can be
   used to identify to the cooresponding company specific code
   (possibly operating system code) that there is user-specific "boot"
   information in this structure. IBM does not guarantee the uniqueness
   of the user_id string. Of course, the string is assumed to be
   present if and only if user_id_offset != NULL. The memory space for
   this string must be included in the area define by user_data_offset
   and user_data_len.

5. Each user must provide their own data access via "user_data_offset".
************************************************************************/

typedef struct dr_proc_info {
	uint max_proc;			/* max possible number of processors */
	uint actual_proc;		/* actual number of processors present*/
} DR_PROC_INFO;

typedef struct dr_mem_info {
	uint max_lmb;			/* max possible number of LMBs */
	uint actual_lmb;		/* actual number of LMBs present */
	uint dma_delay;			/* DMA serialization time */
	unsigned long long lmb_size;	/* LMB size (memory increment value)*/
	unsigned long long rmo_size;	/* initialized to reg property value */
					/* in the /memory node */
	unsigned long long maxmemsize;  /* maximum possible memory size */
} DR_MEM_INFO;

typedef struct lpar_info {
	uint	vcons_termno;		/* termno for vcons */
	uint	hcall_set_bitmap;	/* indicates which hcall sets exist */
#define SPLPAR_HCALLS 1
#define BULK_HCALLS 2
#define XDABR_HCALLS 4
#define VASI_HCALLS 8
	uint	vcons_protocol;		/* protocol version for vcons */
	uint	hosting_partition;	/* true if this is hosting partition */
	uchar	migratable;		/* true if this is a migratable part. */
	char	pad[3];			/* for future use */
} LPAR_INFO;

typedef struct smt_info {
	uint	smt_status;
	uint	smt_threads;
} SMT_INFO;

typedef struct splpar_info {
	uint	BoundThrds;		/* see the RISC Platform Architecture */
	uint	CapInc;			/* Architecture document for an */
	unsigned long long DisWheRotPer;  /* explanation of these fields */
	uint	MinEntCap;
	uint	MinEntCapPerVP;
	uint	MinMem;
	uint	MinProcs;
	uint	MaxEntCap;
	uint	MaxPlatProcs;
	uint	hcall_splpar;		/* shared cpu h-calls */
	uint	hcall_pic;		/* shared cpu pool idle authority */
	uint	DesEntCap;		/* additional fields from the RPA */
	uint	DesMem;			/* added via ACR dated 10/19/2004 */
	uint	DesProcs;
	uint	DesVarCapWt;
        uint    DedDonMode;
	uint	hcall_ext;		/* Extended H_PIC and H_GET_PPP   */
} SPLPAR_INFO;

/* BSR information.  GR has a 16 byte BSR with 4 windows;  GT and P6
 * have 64-byte BSRs with 9 windows.
 */
typedef struct bsr_info {
	short	windows;		/* total number of mapping windows */
	short	index;			/* this windows index in the array */
	short	node;			/* which BSR node this window belongs*/
	short	start_byte;		/* byte of the node window starts */
	short	primary;		/* is this the node primary window */
	short	pad;			/* unused */
	int	lock_bytes;		/* size in bytes of this window */
	int	lock_stride;		/* stride on which the window repeats*/
	int	map_size;		/* map size in bytes */
	unsigned long long map_addr;	/* system address for this window */
} BSR_INFO;

typedef struct ras_info {
	int	enter_dbg;		/* to be copied into kernel's var */
	signed char errchecklevel;	/* RAS: kernel error checking level */
	char	pad[3];			/* for future use */
	int	num_hkeys;		/* Number of hardware keys for data */
} RAS_INFO;

typedef struct console_info {
  uint  num_of_structs;       /* contains the run time value corresponding*/
  uint  index;                /* 0 <= index <= num_of_structs - 1,        */
			      /* assume index = n, then this              */
			      /* is the n+1th array element               */
  uint struct_size;           /* size of this structure (in bytes)        */
  short console_flags;        /* bitmap of flags                          */
  short console_type;         /* enum type describes console device       */
  unsigned long long sys_addr;   /* system memory address for access      */
} CONSOLE_INFO, *CONSOLE_INFO_PTR;
enum { ISA_SER_PORT, VTY_SER_DEV, PCI_A8135201, NOT_SERIAL_DEV };
#define IS_FW_CONSOLE	1     /* bit value to be used in console_flags    */

#ifdef MSG

typedef struct ipl_cb {                    /* IPL Control Block front end   */
  unsigned int  gpr_save_area[32];         /* Reg save area, ROS interrupts */
  IPL_DIRECTORY                s0;         /* Offsets/sizes directory       */
} IPL_CB, *IPL_CB_PTR;

#endif
#endif
