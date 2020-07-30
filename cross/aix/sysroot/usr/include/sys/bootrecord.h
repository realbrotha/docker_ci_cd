/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/sys/POWER/bootrecord.h 1.6.4.1                   */
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
/* @(#)27 1.6.4.1  src/bos/kernel/sys/POWER/bootrecord.h, bosboot, bos53X, x2011_31B5 7/14/11 12:42:03 */
#ifndef _H_BOOTRECORD
#define _H_BOOTRECORD
/*
 *   COMPONENT_NAME: BOSBOOT
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1989,1993
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
#include <sys/types.h>         /* include for definition of unique_id struct */

/*****************************************************************************/
/*                                                                           */
/* This file defines the IPL Record template. The IPL Record information is  */
/* contained on one sector.                                                  */
/*                                                                           */
/* Acronyms used in this file:                                               */
/*   PSN          Physical Sector Number                                     */
/*   IPL          Initial Program Load                                       */
/*   BLV          Boot    Logical Volume                                     */
/*   SLV          Service Logical Volume                                     */
/*                                                                           */
/* General notes:                                                            */
/*   Fragmentation implies that code which is loaded into memory may not be  */
/*   loaded in one completely contiguous area and inherently refers to memory*/
/*   above the first megabyte bound of memory since the processor environment*/
/*   requires the first meg to be good. That is, code which crosses or is    */
/*   completely contained above the first meg of memory may need to be       */
/*   fragmented. This is reflected in the value of the "boot_frag" flag which*/
/*   is defined below.                                                       */
/*                                                                           */
/* Usage examples for this file:                                             */
/*                                                                           */
/*   IPL_REC_PTR my_rec_ptr          defines my_rec_ptr as a pointer to the  */
/*                                   struct "ipl_rec_area".                  */
/*                                                                           */
/*   IPL_REC my_rec                  can be used to define memory space for  */
/*                                   an ipl record.                          */
/*                                                                           */
/*   sizeof(IPL_REC)                 will return the size (in bytes) of      */
/*                                   ipl_rec_area                            */
/*                                                                           */
/*   my_rec.field_name               either of these can be used to access   */
/*   my_rec_ptr->field_name          an element of the ipl record (shown     */
/*                                   here as "field_name").                  */
/*                                                                           */
/*****************************************************************************/

#define	BOOTABLE_PART	0x80		/* active boot partition */
#define	BOOT_SIGNATURE  0x55AA		/* Partition table signature	     */
#define	MASTERS		0x41		/* Masters partition type indicator  */
#define	NO_BOOT		0x00		/* Boot indicator		     */
#define	PART_START	0x1BE		/* Offset to start of partition tbl  */
#define	SBSIZE 0x20000			/* Save base size is 64K	*/
#define	SEC_SIZE	512
#define	SIG_START	0x1FE		/* Offset to start of signature      */
#define ENABLE_HMT	1	/* bit flag indicating HMT is to be enabled */
#define DISABLE_SMT	2	/* bit flag indicating SMT is to be disabled */
#define IOS_TRUE	4	/* bit flag indicating IO server OS */
#define BCFG_EXISTS	8	/* indicates boot image contains bcfg data */
#define NOSMT_MOREPP	0x10	/* indicates SMT is not available */

typedef struct ipl_rec_area
{
    unsigned int      IPL_record_id;    /* This physical volume contains a   */
                                        /* valid IPL record if and only if   */
                                        /* this field contains IPLRECID      */

#define IPLRECID 0xc9c2d4c1             /* Value is EBCIDIC 'IBMA'           */

    char              reserved1[20];
    unsigned int      formatted_cap;    /* Formatted capacity. The number of */
                                        /* sectors available after formatting*/
                                        /* The presence or absence of bad    */
                                        /* blocks does not alter this value. */

    char              last_head;        /* THIS IS DISKETTE INFORMATION      */
                                        /* The number of heads minus 1. Heads*/
                                        /* are number from 0 to last_head.   */

    char              last_sector;      /* THIS IS DISKETTE INFORMATION      */
                                        /* The number of sectors per track.  */
                                        /* Sectors are numbered from 1 to    */
                                        /* last_sector.                      */

    char              reserved2[6];

    unsigned int      boot_code_length; /* Boot code length in sectors. A 0  */
                                        /* value implies no boot code present*/

    unsigned int      boot_code_offset; /* Boot code offset. Must be 0 if no */
                                        /* boot code present, else contains  */
                                        /* byte offset from start of boot    */
                                        /* code to first instruction.        */

    unsigned int      boot_lv_start;    /* Contains the PSN of the start of  */
                                        /* the BLV.                          */

    unsigned int      boot_prg_start;   /* Boot code start. Must be 0 if no  */
                                        /* boot code present, else contains  */
                                        /* the PSN of the start of boot code.*/

    unsigned int      boot_lv_length;   /* BLV length in sectors.            */

    unsigned int      boot_load_add;    /* 512 byte boundary load address for*/
                                        /* boot code.                        */

    char              boot_frag;        /* Boot code fragmentation flag. Must*/
                                        /* be 0 if no fragmentation allowed, */
                                        /* else must be 0x01.                */

    char	      boot_emulation;	/* ROS network emulation flag */
					/* 0x0 => not an emul support image   */
					/* 0x1 => ROS network emulation code  */
					/* 0x2 => AIX code supporting ROS emul*/

    char              reserved3[2];

    ushort            basecn_length;    /* Number of sectors for base        */
                                        /* customization. Normal mode.       */

    ushort            basecs_length;    /* Number of sectors for base        */
                                        /* customization. Service mode.      */

    unsigned int      basecn_start;     /* Starting PSN value for base       */
                                        /* customization. Normal mode.       */

    unsigned int      basecs_start;     /* Starting PSN value for base       */
                                        /* customization. Service mode.      */

    char              reserved4[24];

    unsigned int      ser_code_length;  /* Service code length in sectors.   */
                                        /* A 0 value implies no service code */
                                        /* present.                          */

    unsigned int      ser_code_offset;  /* Service code offset. Must be 0 if */
                                        /* no service code is present, else  */
                                        /* contains byte offset from start of*/
                                        /* service code to first instruction.*/

    unsigned int      ser_lv_start;     /* Contains the PSN of the start of  */
                                        /* the SLV.                          */

    unsigned int      ser_prg_start;    /* Service code start. Must be 0 if  */
                                        /* service code is not present, else */
                                        /* contains the PSN of the start of  */
                                        /* service code.                     */

    unsigned int      ser_lv_length;    /* SLV length in sectors.            */

    unsigned int      ser_load_add;     /* 512 byte boundary load address for*/
                                        /* service code.                     */

    char              ser_frag;         /* Service code fragmentation flag.  */
                                        /* Must be 0 if no fragmentation     */
                                        /* allowed, else must be 0x01.       */

    char	      ser_emulation;	/* ROS network emulation flag */
					/* 0x0 => not an emul support image   */
					/* 0x1 => ROS network emulation code  */
					/* 0x2 => AIX code supporting ROS emul*/

    char              reserved5[2];

    unique_id_t       pv_id;            /* The unique identifier for this    */
                                        /* physical volume.                  */
    char              dummy[512 - 128 - sizeof(unique_id_t)];
}IPL_REC, *IPL_REC_PTR;

typedef struct {
	unsigned char	e_ident[16];	/* ELF identification */
	unsigned short	e_type;		/* object file type */
	unsigned short	e_machine;	/* architecture */
	unsigned int	e_version;	/* object file version */
	unsigned int	e_entry;	/* entry point */
	unsigned int	e_phoff;	/* prog hdr byte offset */
	unsigned int	e_shoff;	/* section hdr byte offset */
	unsigned int	e_flags;	/* processor specific flags */
	unsigned short	e_ehsize;	/* ELF header size */
	unsigned short	e_phentsize;	/* prog hdr table entry size */
	unsigned short	e_phnum;	/* prog hdr table entry count */
	unsigned short	e_shentsize;	/* section header size */
	unsigned short	e_shnum;	/* section header entry count */
	unsigned short	e_shstrndx;	/* sect name string tbl idx */
} Elf_Ehdr;

typedef struct {
	unsigned int	p_type;		/* segment type */
	unsigned int	p_offset;	/* offset to this segment */
	unsigned int	p_vaddr;	/* virt addr of seg in memory */
	unsigned int	p_paddr;	/* phy addr of seg in memory */
	unsigned int	p_filesz;	/* file image segment size */
	unsigned int	p_memsz;	/* mem image segment size */
	unsigned int	p_flags;	/* segment flags */
	unsigned int	p_align;	/* segment alignment */
} Elf_Phdr;

typedef struct {
	unsigned int	namesz;		/* size of name */
	unsigned int	descsz;		/* size of descriptor */
	unsigned int	type;		/* descriptor interpretation */
	unsigned char	name[8];	/* the owner of this entry */
	unsigned int	real_mode;	/* ISA env variable */
	unsigned int	real_base;	/* ISA env variable */
	unsigned int	real_size;	/* ISA env variable */
	unsigned int	virt_base;	/* ISA env variable */
	unsigned int	virt_size;	/* ISA env variable */
	unsigned int	load_base;	/* ISA env variable */
} ppc_note_seg;

typedef struct {
	unsigned int	namesz;		/* size of name */
	unsigned int	descsz;		/* size of descriptor */
	unsigned int	type;		/* descriptor interpretation */
	unsigned char	name[24];	/* the owner of this entry */
	unsigned int	lpar_affinity;	/* boolean indicating OS support */
	unsigned int	min_rmo_size;	/* minimum RMO size */
	unsigned int	min_rmo_percent;	/* minimum RMO % of total */
	unsigned int	max_pft_size;	/* max size of hardware page frame */
					/* frame table, as a power of two */
	unsigned int	splpar;		/* boolean indicating shared */
					/* processor support by the OS */
	unsigned int	min_load;	/* amount of client program that */
					/* must be loaded at load-base */
	unsigned int	mem_rep;	/* a flag that indicates whether */
					/* this OS supports dr mem array */
	unsigned int	ignore_cl_cfg;	/* a flag that indicates whether */
					/* fw should ignore boot cfg vars */
	unsigned int	lrg_pg_rdy;	/* a flag that indicates whether */
					/* this OS supports large pages */
	unsigned int	force_alpha;	/* a flag that indicates that the */
					/* client is requesting a non-HMC */	
					/* managed I/O services partition */
} rpa_note_seg;

/* the following structure provides info for use by the OS and boot image */
typedef struct {
	unsigned int	my_size;	/* the size of myself */
	unsigned int	timestamp;	/* boot image creation timestamp */
	unsigned int	aixmon_size;
	unsigned int	comp_kern_size;	/* compressed kernel size */
	unsigned int	kern_size;	/* kernel size */
	unsigned int	ram_fs_start;	/* offset from start of boot image */
	unsigned int	ram_fs_size;
	unsigned int	debug_settings;
	unsigned int	rmalloc_size;
	unsigned int	next_boot_settings;	/* effective next boot */
	unsigned int	reserved[6];
} BL_parms_seg;

typedef struct {
	Elf_Ehdr elf_hdr;
	Elf_Phdr ppc_note_phdr;		/* info about PPC note section */
	Elf_Phdr rpa_note_phdr;		/* info about RPA note section */
	Elf_Phdr load_phdr1;		/* info about boot image parameters */
	Elf_Phdr load_phdr2;		/* info about remaining boot image */
	ppc_note_seg ppc_note_data;	/* the PPC note section */
	rpa_note_seg rpa_note_data;	/* the RPA note section */
	BL_parms_seg BL_parms_data;	/* the boot image parameters */
} ELF_boot_hdr;

typedef struct {
	unsigned char  boot_ind,	/* Boot indicator	     */
		       begin_h,		/* Begin head		     */
		       begin_s,		/* Begin sector		     */
		       begin_c;		/* Begin cylinder	     */
	unsigned char  syst_ind,	/* System indicator	     */
		       end_h,		/* End head		     */
		       end_s,		/* End sector		     */
		       end_c;		/* End cylinder		     */
	unsigned int   RBA,		/* Relative block address    */
		       sectors;		/* Number of sectors	     */
}  partition_table_entry;

typedef struct {
	partition_table_entry partition[4];     /* Partition i		*/
}  boot_partition_table;

#endif /* _H_BOOTRECORD */
