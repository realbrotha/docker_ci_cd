/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/kernel/sys/ras_base.h 1.9.1.1                           */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2004,2007          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)14       1.9.1.1  src/bos/kernel/sys/ras_base.h, sysras, bos53Q, q2007_51B4 11/26/07 17:22:01 */

/*
 * COMPONENT_NAME: (sysras) RAS Component Infrastructure
 *
 * FUNCTIONS: 
 *
 * ORIGINS: 27
 */

/* Component type and subtype for use with ras_register.
 *
 * To add a new type or subtype, add it to the table below with the
 * appropriate eye-catcher. The first two characters are for type,
 * the rest are subtype.
 *
 * After adding it to the ras_type enum, add it to the ras_type_lookup
 * table at the bottom.
 */

#ifndef _H_RAS_BASE
#define _H_RAS_BASE

enum ras_type
{
	RAS_TYPE_CHILD = 0x0,
	
	RAS_TYPE_OTHER = 0x4f544852,			/* OTHR */

	RAS_TYPE_DEVICE = 0x44450000,			/* DE   */
	RAS_TYPE_DEVICE_BUS = 0x44454255,		/* DEBU */
	RAS_TYPE_DEVICE_CRYPT = 0x44454352,		/* DECR */
	RAS_TYPE_DEVICE_PARALLEL = 0x44455041,		/* DEPA */
	RAS_TYPE_DEVICE_PLANAR = 0x4445504c,		/* DEPL */
	RAS_TYPE_DEVICE_SERIAL = 0x44455345,		/* DESE */
	RAS_TYPE_DEVICE_USB = 0x44455553,		/* DEUS */

	RAS_TYPE_FILESYSTEM = 0x46490000,		/* FI   */
	RAS_TYPE_FILESYSTEM_DISTRIBUTED = 0x46494449,	/* FIDI */
	RAS_TYPE_FILESYSTEM_LOCAL = 0x46494c4f,		/* FILO */
	RAS_TYPE_FILESYSTEM_NETWORK = 0x46494e45,	/* FINE */
	RAS_TYPE_FILESYSTEM_PSEUDO = 0x46495053,	/* FIPS */

	RAS_TYPE_NETWORK = 0x4e450000,			/* NE   */
	RAS_TYPE_NETWORK_API = 0x4e454150,		/* NEAP */
	RAS_TYPE_NETWORK_ATM = 0x4e454154,		/* NEAT */
	RAS_TYPE_NETWORK_ETHERNET = 0x4e454554,		/* NEET */
	RAS_TYPE_NETWORK_FDDI = 0x4e454644,		/* NEFD */
	RAS_TYPE_NETWORK_IB = 0x4e454942,		/* NEIB */
	RAS_TYPE_NETWORK_DLC = 0x4e45444c,		/* NEDL */
	RAS_TYPE_NETWORK_PROTOCOL = 0x4e455052,		/* NEPR */
	RAS_TYPE_NETWORK_MEMORY = 0x4e454d45,		/* NEME */
	RAS_TYPE_NETWORK_SERIAL = 0x4e455345,		/* NESE */
	RAS_TYPE_NETWORK_TOKENRING = 0x4e45544f,	/* NETO */
	RAS_TYPE_NETWORK_X25 = 0x4e453235,		/* NE25 */
	RAS_TYPE_NETWORK_VASI = 0x4e455641,		/* NEVA */
	RAS_TYPE_NETWORK_MOVER = 0x4e454d4f,		/* NEMO */
	RAS_TYPE_NETWORK_SEA = 0x4e455365,		/* NESe */
	RAS_TYPE_NETWORK_PAGER = 0x4e455041,		/* NEPA */

	RAS_TYPE_SERVICES = 0x53450000,			/* SE   */
	RAS_TYPE_SERVICES_BASE = 0x53454241,		/* SEBA */
	RAS_TYPE_SERVICES_CHARACTER = 0x53454348,	/* SECH */
	RAS_TYPE_SERVICES_PERF = 0x53455045,		/* SEPE */
	RAS_TYPE_SERVICES_RAS = 0x53455241,		/* SERA */
	RAS_TYPE_SERVICES_SECURITY = 0x53455345,	/* SESE */
	RAS_TYPE_SERVICES_ARM = 0x53454152,		/* SEAR */

	RAS_TYPE_STORAGE = 0x53540000,			/* ST   */
	RAS_TYPE_STORAGE_ARRAY = 0x53544152,		/* STAR */
	RAS_TYPE_STORAGE_CDROM = 0x53544344,		/* STCD */
	RAS_TYPE_STORAGE_DISK = 0x53544449,		/* STDI */
	RAS_TYPE_STORAGE_DRIVER = 0x53544452,		/* STDR */
	RAS_TYPE_STORAGE_IDE = 0x53544944,		/* STID */
	RAS_TYPE_STORAGE_ISCSI = 0x53544953,		/* STIS */
	RAS_TYPE_STORAGE_FC = 0x53544643,		/* STFC */
	RAS_TYPE_STORAGE_FLOPPY = 0x5354464c,		/* STFL */
	RAS_TYPE_STORAGE_RAID = 0x53545241,		/* STRA */
	RAS_TYPE_STORAGE_SAS = 0x53545341,		/* STSA */
	RAS_TYPE_STORAGE_SATA = 0x53545361,		/* STSa */
	RAS_TYPE_STORAGE_SCSI = 0x53545343,		/* STSC */
	RAS_TYPE_STORAGE_SSA = 0x53545353,		/* STSS */
	RAS_TYPE_STORAGE_TAPE = 0x53545441,		/* STTA */

	RAS_TYPE_UI = 0x55490000,			/* UI   */
	RAS_TYPE_UI_GRAPHICS = 0x55494752,		/* UIGR */
	RAS_TYPE_UI_KEYBOARD = 0x55494b45,		/* UIKE */
	RAS_TYPE_UI_LFT = 0x55494c46,			/* UILF */
	RAS_TYPE_UI_MOUSE = 0x55494d4f,			/* UIMO */
	RAS_TYPE_UI_TABLET = 0x55495441,		/* UITA */

	RAS_TYPE_LAST = 0x0E0F0E0F			/* Terminator */
};

/* ras_type_lookup table - ras_type_lookup is a table of type/string
 * pairs for ease in type lookup. The list is terminated by an entry
 * of RAS_TYPE_LAST.  Sample iteration of the table:
 *
 *   for (rtp = ras_type_lookup;
 *        rtp->rast_type != RAS_TYPE_LAST;
 *        rtp++)
 *
 * Note: ras_type_lookup is declared using RAS_TYPE_LOOKUP_DECL. The
 * declaration is #defined below so that this table and the enum table
 * below are in the same file. However, because this is C,
 * ras_type_lookup can't be initialized in a .h file. In order to use
 * ras_type_lookup, RAS_TYPE_LOOKUP_DECL must be a global declaration
 * in a source file that is linked against where ras_type_lookup is to
 * be used. The extern below will allow it to be used anywhere that
 * includes ras.h, but the linkage issue must be resolved. (At the
 * very least, it's declared in the kernel. Commands will also have to
 * link against something that defines the symbol.) An example follows:
 *
 * If decl.c defines:
 *
 *   #include <sys/ras_base.h>
 *
 *   RAS_TYPE_LOOKUP_DECL;
 *
 * And myfile.o links against decl.o, then myfile.c can just do:
 *
 *   #include <sys/ras_base.h>
 *
 *   int somefunc(...)
 *   {
 *      const ras_type_entry_t *rtp;
 *
 *      for (rtp = ras_type_lookup;
 *           rtp->rast_type != RAS_TYPE_LAST;
 *           rtp++)
 *        ...
 *   }
 */

typedef enum ras_type ras_type_t;

struct ras_type_entry
{
	ras_type_t rast_type;
	const char *rast_string;
};

typedef struct ras_type_entry ras_type_entry_t;

extern const ras_type_entry_t ras_type_lookup[];

#define RAS_TYPE_LOOKUP_DECL						\
const ras_type_entry_t ras_type_lookup[] = 				\
{									\
	{ RAS_TYPE_CHILD, "child" },					\
	{ RAS_TYPE_OTHER, "other" },					\
	{ RAS_TYPE_DEVICE, "device" },					\
	{ RAS_TYPE_DEVICE_BUS, "device_bus" },				\
	{ RAS_TYPE_DEVICE_CRYPT, "device_crypt" },			\
	{ RAS_TYPE_DEVICE_PARALLEL, "device_parallel" },		\
	{ RAS_TYPE_DEVICE_PLANAR, "device_planar" },			\
	{ RAS_TYPE_DEVICE_SERIAL, "device_serial" },			\
	{ RAS_TYPE_DEVICE_USB, "device_usb" },				\
	{ RAS_TYPE_FILESYSTEM, "filesystem" },				\
	{ RAS_TYPE_FILESYSTEM_DISTRIBUTED, "filesystem_distributed" },	\
	{ RAS_TYPE_FILESYSTEM_LOCAL, "filesystem_local" },		\
	{ RAS_TYPE_FILESYSTEM_NETWORK, "filesystem_network" },		\
	{ RAS_TYPE_FILESYSTEM_PSEUDO, "filesystem_pseudo" },		\
	{ RAS_TYPE_NETWORK, "network" },				\
	{ RAS_TYPE_NETWORK_API, "network_api" },			\
	{ RAS_TYPE_NETWORK_ATM, "network_atm" },			\
	{ RAS_TYPE_NETWORK_ETHERNET, "network_ethernet" },		\
	{ RAS_TYPE_NETWORK_FDDI, "network_fddi" },			\
	{ RAS_TYPE_NETWORK_IB, "network_ib" },				\
	{ RAS_TYPE_NETWORK_DLC, "network_dlc" },			\
	{ RAS_TYPE_NETWORK_PROTOCOL, "network_protocol" },		\
	{ RAS_TYPE_NETWORK_MEMORY, "network_memory" },			\
	{ RAS_TYPE_NETWORK_SERIAL, "network_serial" },			\
	{ RAS_TYPE_NETWORK_TOKENRING, "network_tokenring" },		\
	{ RAS_TYPE_NETWORK_X25, "network_x25" },			\
	{ RAS_TYPE_NETWORK_VASI, "network_vasi" },			\
	{ RAS_TYPE_NETWORK_MOVER, "network_mover" },			\
	{ RAS_TYPE_NETWORK_SEA, "network_sea" },			\
	{ RAS_TYPE_NETWORK_PAGER, "network_pager" },			\
	{ RAS_TYPE_SERVICES, "services" },				\
	{ RAS_TYPE_SERVICES_BASE, "services_base" },			\
	{ RAS_TYPE_SERVICES_CHARACTER, "services_character" },		\
	{ RAS_TYPE_SERVICES_PERF, "services_perf" },			\
	{ RAS_TYPE_SERVICES_RAS, "services_ras" },			\
	{ RAS_TYPE_SERVICES_SECURITY, "services_security" },		\
	{ RAS_TYPE_SERVICES_ARM, "services_arm" },			\
	{ RAS_TYPE_STORAGE, "storage" },				\
	{ RAS_TYPE_STORAGE_ARRAY, "storage_array" },			\
	{ RAS_TYPE_STORAGE_CDROM, "storage_cdrom" },			\
	{ RAS_TYPE_STORAGE_DISK, "storage_disk" },			\
	{ RAS_TYPE_STORAGE_DRIVER, "storage_driver" },			\
	{ RAS_TYPE_STORAGE_IDE, "storage_ide" },			\
	{ RAS_TYPE_STORAGE_ISCSI, "storage_iscsi" },			\
	{ RAS_TYPE_STORAGE_FC, "storage_fc" },				\
	{ RAS_TYPE_STORAGE_FLOPPY, "storage_floppy" },			\
	{ RAS_TYPE_STORAGE_RAID, "storage_raid" },			\
	{ RAS_TYPE_STORAGE_SAS, "storage_sas" },			\
	{ RAS_TYPE_STORAGE_SATA, "storage_sata" },			\
	{ RAS_TYPE_STORAGE_SCSI, "storage_scsi" },			\
	{ RAS_TYPE_STORAGE_SSA, "storage_ssa" },			\
	{ RAS_TYPE_STORAGE_TAPE, "storage_tape" },			\
	{ RAS_TYPE_UI, "ui" },						\
	{ RAS_TYPE_UI_GRAPHICS, "ui_graphics" },			\
	{ RAS_TYPE_UI_KEYBOARD, "ui_keyboard" },			\
	{ RAS_TYPE_UI_LFT, "ui_lft" },					\
	{ RAS_TYPE_UI_MOUSE, "ui_mouse" },				\
	{ RAS_TYPE_UI_TABLET, "ui_tablet" },				\
	{ RAS_TYPE_LAST, NULL }						\
}
#define RAS_BASE_NETINET        "netinet"
#define RAS_BASE_ETHCHAN        "etherchannel"
#define RAS_BASE_IF_EN          "ethernet"
#define RAS_BASE_MBUF           "mbuf"
#define RAS_BASE_SOCKET         "socket"
#define RAS_BASE_NETMALLOC      "netmalloc"
#define RAS_BASE_NET            "net"
#define RAS_BASE_VASI		"vasi"
#define RAS_BASE_MOVER		"mover"
#define RAS_BASE_SEA		"sea"
#define RAS_BASE_PAGER		"pager"


#endif /* _H_RAS_BASE */
