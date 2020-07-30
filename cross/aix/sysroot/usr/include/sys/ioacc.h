/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53J src/bos/kernel/sys/ioacc.h 1.41                                 */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1994          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)30       1.41  src/bos/kernel/sys/ioacc.h, sysios, bos53J, j2006_18D6 5/5/06 14:02:29 */

#ifndef _H_IOACC
#define _H_IOACC
/*
 *				I/O ACCESS
 *
 *	This header file defines a set of macros that provide a machine
 *	independent interface to either the PC AT bus or the Micro
 *	Channel bus. A different version of this header file exists
 *	for each unique machine type that supports these busses.
 *	Multiple I/O buses are supported by these macros.
 *
 *	These macros are typically used as follows.
 *
 *      ulong32int64_t *p;
 *	p = (ulong32int64_t *)BUSMEM_ATT(config_bid + my_device_offset);
 *	BUS_PUTL(p,value_to_write_to_device);
 *	BUSMEM_DET(p);
 */

#include <sys/types.h>

#ifdef __ia64

/*
 * The following macros can be used for accessing IA64 PORT I/O Space
 *
 *	_b is the BID for the bus the device is attached to, with the
 *         IO Region set
 *
 *	_p is the I/O Port Address
 *
 *	_d is the data (for writes)
 */
#define INBYTE(_b,_p)  pal_portio_read((_b),(1),(_p))
#define INHALF(_b,_p)  pal_portio_read((_b),(2),(_p))
#define INWORD(_b,_p)  pal_portio_read((_b),(4),(_p))
#define OUTBYTE(_b,_p,_d)  pal_portio_write((_b),(1),(_p),(_d))
#define OUTHALF(_b,_p,_d)  pal_portio_write((_b),(2),(_p),(_d))
#define OUTWORD(_b,_p,_d)  pal_portio_write((_b),(4),(_p),(_d))


#endif /* __ia64 */


/*
 *	The following macros write the specified data to bus memory.
 *	These macros are statements.
 */

#define BUS_PUTL(p,v)   *(ulong32int64_t volatile *)(p) = (ulong32int64_t)(v)
#define BUS_PUTS(p,v)   *(ushort volatile *)(p) = (ushort)(v)
#define BUS_PUTC(p,v)   *(uchar volatile *)(p) = (uchar)(v)


/*
 *	The following macros read the specified data from bus memory.
 *	These macros are expressions.
 */

#define BUS_GETL(p)     (*((ulong32int64_t volatile *)(p)))
#define BUS_GETS(p)     (*((ushort volatile *)(p)))
#define BUS_GETC(p)     (*((uchar volatile *)(p)))

/*
 *	The following macros write the specified data to bus I/O.
 *	These macros are statements.
 */

#define BUSIO_PUTL(p,v) *(ulong32int64_t volatile *)(p) = (ulong32int64_t)(v)
#define BUSIO_PUTS(p,v) *(ushort volatile *)(p) = (ushort)(v)
#define BUSIO_PUTC(p,v) *(uchar volatile *)(p) = (uchar)(v)

/*
 *	The following macros read the specified data from bus I/O.
 *	These macros are expressions.
 */

#define BUSIO_GETL(p)   (*((ulong32int64_t volatile *)(p)))
#define BUSIO_GETS(p)   (*((ushort volatile *)(p)))
#define BUSIO_GETC(p)   (*((uchar volatile *)(p)))

#ifndef __ia64
/*
 * Bus Memory and I/O Access, byte reversed.  These routines are not exported 
 * to the user community and are not documented.  They are not supported
 * on ia64.
 *
 * p is the pointer to the address to be accessed
 * v is the data to be written
 *
 */
#ifdef __64BIT_KERNEL

int BUS_GETLR(void *addr);
#pragma mc_func 	BUS_GETLR	{ "7c601c2c" }   /* lbrx r3,0,r3 */
#pragma reg_killed_by 	BUS_GETLR	gr3

int BUS_GETSR(void *addr);
#pragma mc_func 	BUS_GETSR	{ "7c601e2c" }   /* lhbrx r3,0,r3 */
#pragma reg_killed_by 	BUS_GETSR	gr3

void BUS_PUTLR(int val,void *addr);
#pragma mc_func 	BUS_PUTLR	{ "7c60252c" }   /* stbrx r3,0,r4 */
#pragma reg_killed_by 	BUS_PUTLR	gr3-gr4

void BUS_PUTSR(short val,void *addr);
#pragma mc_func 	BUS_PUTSR	{ "7c60272c" }   /* sthbrx r3,0,r4 */
#pragma reg_killed_by 	BUS_PUTSR	gr3-gr4

int BUSIO_GETLR(void *addr);
#pragma mc_func 	BUSIO_GETLR	{ "7c601c2c" }   /* lbrx r3,0,r3 */
#pragma reg_killed_by 	BUSIO_GETLR	gr3

int BUSIO_GETSR(void *addr);
#pragma mc_func 	BUSIO_GETSR	{ "7c601e2c" }   /* lhbrx r3,0,r3 */
#pragma reg_killed_by 	BUSIO_GETSR	gr3

void BUSIO_PUTLR(int val,void *addr);
#pragma mc_func 	BUSIO_PUTLR	{ "7c60252c" }   /* stbrx r3,0,r4 */
#pragma reg_killed_by 	BUSIO_PUTLR	gr3-gr4

void BUSIO_PUTSR(short val,void *addr);
#pragma mc_func 	BUSIO_PUTSR	{ "7c60272c" }   /* sthbrx r3,0,r4 */
#pragma reg_killed_by 	BUSIO_PUTSR	gr3-gr4

#else

/* note the 4 implementing routines are in a non-shipped library */

#define	BUS_GETLR(p)		((ulong32int64_t)BusGetLR(p))
#define	BUS_GETSR(p)		((unsigned short)BusGetSR(p))

#define	BUS_PUTLR(p,v)		((void)BusPutLR(p,v))
#define	BUS_PUTSR(p,v)		((void)BusPutSR(p,v))

#define	BUSIO_GETLR(p)		((ulong32int64_t)BusGetLR(p))
#define	BUSIO_GETSR(p)		((unsigned short)BusGetSR(p))

#define	BUSIO_PUTLR(p,v)	((void)BusPutLR(p,v))
#define	BUSIO_PUTSR(p,v)	((void)BusPutSR(p,v))

#endif /* __64BIT_KERNEL */
#endif /* __ia64 */

/* 
 * Bus Memory and I/O Access, String Movement.  These routines are not 
 * exported to the user community and are not documented.
 *
 * d is the destination pointer
 * s is the source pointer
 * l is the byte count of the transfer
 *
 */

#define	BUS_GETSTR(d,s,l)	((void)BusCpy(d,s,l))
#define	BUS_PUTSTR(d,s,l)	((void)BusCpy(d,s,l))

#define	BUSIO_GETSTR(d,s,l)	((void)BusCpy(d,s,l))
#define	BUSIO_PUTSTR(d,s,l)	((void)BusCpy(d,s,l))

#ifndef __64BIT_KERNEL
/*
 *	The following macros read/write the specified data to bus memory.
 *	These functions set up an exception handler.  They will return
 *	0 if the IO access was successful, and the exception code if an
 *	exception occured
 */
#define BUS_PUTLX(p,v)		busputl(p,v)
#define BUS_PUTLRX(p,v)		busputlr(p,v)
#define BUS_PUTSRX(p,v)		busputsr(p,v)
#define BUS_PUTSX(p,v)		busputs(p,v)
#define BUS_PUTCX(p,v)		busputc(p,v)
#define BUS_GETLX(p,v)		busgetl(p,v)
#define BUS_GETLRX(p,v)		busgetlr(p,v)
#define BUS_GETSRX(p,v)		busgetsr(p,v)
#define BUS_GETSX(p,v)		busgets(p,v)
#define BUS_GETCX(p,v)		busgetc(p,v)
#define BUS_GETSTRX(io,s,l)	buscpy(io,s,l)
#define BUS_PUTSTRX(io,s,l)	buscpy(s,io,l)

#ifndef _NO_PROTO
int busputl(long32int64_t *ioaddr, long32int64_t data);
int busputs(short *ioaddr, short data);
int busputc(char *ioaddr, char data);
int busgetl(long32int64_t *ioaddr, long32int64_t *data);
int busgets(short *ioaddr, short *data);
int busgetc(char *ioaddr, char *data);
int busputlr(long32int64_t *ioaddr, long32int64_t data);
int busgetlr(long32int64_t *ioaddr, long32int64_t *data);
int busputsr(short *ioaddr, short data);
int busgetsr(short *ioaddr, short *data);
int buscpy(void *source, void *dest, int count);
#endif /* _NO_PROTO */
#endif /* __64BIT_KERNEL */

/*
 *      The BID is an input parameter to many bus dependent kernel
 *      services (PIO, DMA, interrupt).  A BID is defined for bit0=0
 *      buses to contain information describing the type, number,
 *      and regions for one bus.  This same information is also
 *      contained in T=1 BIDs, so this approach provides a more
 *      consistent programming model.
 *
 * bit0=0 BID format
 *
 *   +---------------------------------------------------------------+
 *   |rsvd |1|high 4 | flags |region |      type         | low 6bits |
 *   |     | |bit nbr|       |       |                   |bus number |
 *   | | | | | | | | | | |1|1|1|1|1|1|1|1|1|1|2|2|2|2|2|2|2|2|2|2|3|3|
 *   |0|1|2|3|4|5|6|7|8|9|0|1|2|3|4|5|6|7|8|9|0|1|2|3|4|5|6|7|8|9|0|1|
 *   +---------------------------------------------------------------+
 *
 *      flags - These flags are bus type dependent.
 *
 *      region - This is used if a IO bus does not occupy one
 *      contiguous space.  For example, PC buses distinguish IO
 *      space and bus memory.
 *
 *      type - This is a bus architecture the bid refers to.  Examples
 *	of bus type are PCI and ISA
 *
 *      num - This is the instance of particular type.  It is not a
 *      global bus number.  Instead it is incremented for each type.
 *      This is ten bits; the low order 6 bits are located at bits
 *	26:31; the high 4 bits are located in bits 4:7.
 *
 *	Bit 3 is always b'1' to identify that this bid may have
 *	valid number bits in bits 4:7.
 *
 *
 * bit0=1 BID format
 *
 *   +-------------------------------------------------------------------+
 *   |1|  MSB  |1| mid1  | mid0  |region |     type          | low 6bits |
 *   | |Bus Num| |    bus number |       |                   |bus number |
 *   | |   |   | | | | | | | |1|1|1|1|1|1|1|1|1|1|2|2|2|2|2|2|2|2|2|2|3|3|
 *   |0|  1| 2 |3|4|5|6|7|8|9|0|1|2|3|4|5|6|7|8|9|0|1|2|3|4|5|6|7|8|9|0|1|
 *   +-------------------------------------------------------------------+
 * 
 *      bit0=1 BID format extends the bus numbers to 16 bits for a 
 *      total of 64k.  The flags field has been eliminated ( it is not 
 *      used in bit0=0 format ).
 * 
 *      region and type - field meanings are the same for bit0=0
 * 
 *      num - This is the instance of particular type.  It is not a
 *      global bus number.  Instead it is incremented for each type.
 *      This is sixteen bits; the low order 6 bits are located at bits
 *	26:31; the middle 8 bits are composesd as mid0 and mid1:
 *      mid0 respresent bits 2:5. mid1 represent bits 6:9.
 *      MSB bits 0 and 1 are found in 1:2.  
 *  
 */

/*
 * The following macro sould be used by device drivers or config methods
 * to generate a BID.
 */

#define BID_VAL(type, region, num) \
 ( ((num) & 0x90000000) ? \
   ( ((num) & 0xFFF0003F ) | ((region) << 16) | ((type) << 6) ) : \
   ( 0x90000000 | ((type) << 6) | ((region) << 16) | \
     ((num & 0xc000 ) << 15 ) | ((num & 0x3c00) << 10 ) | \
     ((num & 0x3C0) << 18) | (num & 0x3F)))


#define BID_VERSION1 0x10000000
#define BID_VERSION2 0x80000000 | BID_VERSION1

/*
 * The following macros can bue used to extract type, number and region
 * from a bit0=0 or bit0=1 BID
 */
#define BID_TYPE(bid) ((((uint)(bid)) >> 6) & 0x3FF)
#define BID_NUM(bid) ((((bid) >> 15 ) & 0xc000) | (((bid) >> 10 ) & 0x3c00 ) | \
			(((bid) >> 18) & 0x3C0) | ((bid) & 0x3F))
#define BID_REGION(bid) ((((uint)(bid)) >> 16) & 0xF)

/*
 * Mask of all non-reserved bits in the BID, not including the version
 * bit.  When comparing two BID values only the bits in the mask should
 * be compared.
 */
#define BID_BITMASK 0x6fffffff

/*
 * generate a BID, given a bid and region.  i.e. alters the region field
 * of the BID
 */
#define BID_ALTREG(bid, region) ((bid & 0xFFF0FFFF) | (region << 16))

/*
 *	Valid bus types known to AIX
 */
#if defined(_KERNEL) || defined(_KERNSYS)
#define IO_REALMEM	0x0001		/* Memory mapped IO */
#endif
#define IO_DIAG		0x0002		/* Testing (internal use only */
#define IO_PCI		0x0003		/* PCI bus */
#define IO_ISA		0x0004		/* ISA bus */
#define IO_VME		0x0005		/* VME bus */
#define IO_FT		0x0006		/* Fault-tolerant bus */
#define IO_MBUS		0x0007		/* Maintenance bus */
#ifdef _POWER_PC
#define IO_TCE		0x0008		/* Internal use only, for TCE tables */
#endif
#define IO_SYSTEM	0x000C		/* system bus attached */
#define IO_VDEVICE      0x000D          /* vdevice I/O bus     */
#define IO_PCIE		0x000E		/* PCI-Express bus */
/*
 * The following bus types are reserved for OEM use
 */
#define IO_OEM_0	0x0008		/* OEM bus type 0 */
#define IO_OEM_1	0x0009		/* OEM bus type 1 */
#define IO_OEM_2	0x000A		/* OEM bus type 2 */
#define IO_OEM_3	0x000B		/* OEM bus type 3 */

#define	INVALID_BID	0xFFFFFFFF	/* indicated invalid bid */
#define	MAX_BID_TYPES	0x10		/* maximium number bus types */
#define MAX_BUS_NUM_PER_TYPE    512     /* max number of busses per type */
#define MAX_HASH_LIST   4               /* max number of hash collisions */
/* max number of hash buckets--this must always be a power of 2*/
#define NUM_HASH_BKTS 	MAX_BUS_NUM_PER_TYPE/MAX_HASH_LIST
#ifdef __64BIT_KERNEL
#define	MAX_FIXED_PER_TYPE	16	/* maximium fixed per bus type */
#else
#define	MAX_FIXED_PER_TYPE	2	/* maximium fixed per bus type */
#endif
#define	MAX_REGIONS	16		/* maximium number of regions per bus */

/*
 * The following defines are for the PCI bus
 *
 * The PCI bus has four defined regions:
 *	IO memory - PCI_IOMEM
 *	BUS memory - PCI_BUSMEM
 *	configuration - PCI_CFGMEM
 *	CHRP bus memory alias - PCI_MEMALIAS
 *
 */	
#define PCI_IOMEM	0		/* PCI I/O memory region */
#define PCI_BUSMEM	1		/* PCI bus memory region */
#ifdef _KERNSYS
#define PCI_CFGMEM	2		/* PCI configuration region */
#define PCI_MEMALIAS	3		/* Addressability to first 16 Meg */
#define MAX_ALIAS_ADDR	0x1000000	/* maximum address for PCI bus memory */
					/* alias */
#endif

/*
 * The following defines are for the ISA bus
 *
 * The ISA bus has two regions:
 *	IO memory - ISA_IOMEM
 *	BUS memory - ISA_BUSMEM
 */
#define ISA_IOMEM	0		/* ISA I/O memory region */
#define ISA_BUSMEM	1		/* ISA bus memory region */

#if defined(_KERNSYS) && !defined(__64BIT_KERNEL)

/*
 * Internal data structure used to track memory mapped I/O.  One mapping
 * is supported per I/O region.  Mapping is done with 256 Meg segments.
 * A base address "busaddr" is the bus address.  An array of segments,
 * "iosegs" contains each a mapping segment for each 256 Meg.  "num_segs"
 * is the number of mapping segments.  This should be checked before
 * referencing "iosegs". The "count" field is a reference count.  It is
 * used for PCI mappings since a child PCI to PCI bridge can use the PHBs
 * mapping
 */
struct busmap {
	int count;
	struct mapentry {
		unsigned long long busaddr;
		vmhandle_t *iosegs;
		long num_segs;
	}map[MAX_REGIONS];
};

#endif /* _KERNSYS && !__64BIT_KERNEL */

/*
 * The following structure is for internal use only
 */
struct businfo {
	struct businfo *next;		/* pointer to next in chain of type*/
	int bid;			/* bus type and number */
	void *(*d_map_init)();		/* DMA services */
	void *(*disable_io)();		/* Disable all I/O activiey   */
	int num_regions;		/* number of regions */
	long long ioaddr[MAX_REGIONS];	/* real address */
	int bus_specific_data;		/* bus specific data           */
					/* For bid type IO_PCI/IO_PCIE:*/
					/*   = PCI hardware bus number */
#if	defined( __64BIT_KERNEL) || !defined(_KERNSYS)
	int reserved1;			/* pad, future expansion       */
#else
	struct busmap *bmap;
#endif	/* __64BIT_KERNEL && !_KERNSYS */
	void *(*eeh_init)();		/* EEH services		       */
	long long PHB_Unit_ID;		/* Host Bridge UNit ID	       */
	void *(*eeh_init_multifunc)();	/* EEH services		       */
	uint devfunc;			/* devfunc=slot=connwhere      */
	int reserved4;			/* pad, future expansion       */
};

#ifndef __64BIT_KERNEL

/*
 * map_bus_memory service provides addition information to the kernel, so
 * that the kernel can establish page mappings for the bus
 */
struct bus_mem_range {
        int version;                    /* API version number.  set to 0 */
        long bus_id;                    /* id being mapped */
        long phb_id;                    /* id of parent host bridge */
        long long busaddr;              /* bus address */
        long long physaddr;		/* system address */
        long long size;			/* size of region to be mapped */
};

long
map_bus_memory(
        struct bus_mem_range *bm);

#endif /* __64BIT_KERNEL */


#if defined(_KERNEL) || defined(_KERNSYS)
/*
 * BID for real memory PIO access
 */
#define REALMEM_BID	BID_VAL(IO_REALMEM, 0, 0)	/* real memory access */

#endif /* _KERNEL || _KERNSYS */

#ifdef _KERNSYS
/*
 * Macro to produce index by type from a BID.  
 */
#define BID_TYPE_INDEX(bid) BID_TYPE(bid)
/*
 * Macro to produce index by bus number from a BID.  
 */
#define BID_NUM_INDEX(bid) BID_NUM(bid)

#define MAX_BID_TYPE_INDEX MAX_BID_TYPES	/* maximium BIDs to register */
#define MAX_BID_NUM_INDEX MAX_FIXED_PER_TYPE	/* maximium BIDs to register */

/*
 * Get the "businfo" structure that coresponds to a bid.  Internal kernel use
 * only
 */
#define BID_2_BINFO(_bp,_bid)					\
{								\
	(_bp) = find_businfo(_bid);				\
}

/*
 * extract region ID from a BID, taking into account the PCI memory alias
 * if attaching to the first 16 Megs of PCI bus memory space, and
 * an alias region exists then convert the region to the alias
 * region
 *
 * This is for internal kernel use only
 */
#define REGION_W_ALIAS(_region, _bp, _iop, _bid)			\
{									\
	_region = BID_REGION(_bid);					\
	if (((_bp)->num_regions > PCI_MEMALIAS) &&			\
	  (BID_TYPE(_bid) == IO_PCI) && (_region == PCI_BUSMEM) &&	\
	  (((unsigned long long)((_iop)->busaddr) +			\
	      (unsigned long long)((_iop)->size))			\
		<= (unsigned long long)MAX_ALIAS_ADDR) )		\
	{								\
		_region = PCI_MEMALIAS;					\
	}								\
}


#endif /* _KERNSYS */

#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)

int bus_register(		/* register a bus type */
        struct businfo *bp);    /* bus structure to register */

int bus_unregister(		/* unregister a bus */ 
        uint    bid);           /* bid of bus to unregister */

struct mdio;
int pci_cfgrw(			/* read/write PCI bus config space */
	int bid, 		/* BID for bus */
	struct mdio *md, 	/* pointer to mdio structure */
	int write_flag);	/* 1 for read, 0 for write */

int pio_assist(                         /* assist programmed I/O */
        caddr_t ioparms,                /* pointer to I/O parameters */
        int (*iofunc)(),                /* ptr to I/O  routine  */
        int (*iorecov)());              /* ptr to I/O  recovery routine */


#endif /* (__64BIT_KERNEL) || (__FULL_PROTO) */

#define SYSMEM_BID	BID_VAL(IO_SYSTEM, 0, 0)

#ifdef _POWER_PC
#define TCEMEM_BID	BID_VAL(IO_TCE, 0, 0)
#endif

#endif /* _H_IOACC */







