/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53H src/bos/kernel/j2/include/j2_types.h 1.15                       */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1999,2006          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

/* @(#)98       1.15  src/bos/kernel/j2/include/j2_types.h, sysj2, bos53H, h2006_07C4 2/9/06 14:22:34 */
/*
 * COMPONENT_NAME: (SYSJ2) JFS2 Physical File System
 *
 * FUNCTIONS: 
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1996, 1999
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_J2_TYPES
#define	_H_J2_TYPES
/*
 * FUNCTION: basic type/utility definitions
 *
 * note: this header file must be the 1st include file 
 *       of include list in all J2 .c files.
 */

/* define macros to prevent inclusion of original jfs headers */
#define _H_JFS_FILSYS
#define _H_JFS_INODE
#define _H_JFS_INO
#define _H_JFS_DIR

#include <sys/types.h>
#include <sys/sysmacros.h>


/*
 *	unicode types
 */
#ifdef _J2_UNICODE
#ifndef _ULS_UNICHAR_DEFINED
typedef unsigned short UniChar;
#define _ULS_UNICHAR_DEFINED
#endif
#else /* _J2_UNICODE */
/* define rather than typedef here because
 * sys/types.h already typedefs UniChar to a short
 */
#define UniChar unsigned char
#endif /* _J2_UNICODE */


/*
 *	primitive types (based on LP64 C language data model)
 *
 *	these are defined in inttypes.h, as are the u_int* types:
 *
 *	  typedef signed char	int8;
 *	  typedef short		int16;
 *	  typedef int		int32;
 *	  typedef long long	int64;
 */
typedef	u_int8		uint8;
typedef	u_int16		uint16;
typedef	u_int32		uint32;
typedef	u_int64		uint64;


/* natural register size for temporary generic integer */
typedef	long		reg_t;
typedef	unsigned long	ureg_t;

#define	ALIGNMENT_OFFSET	7	/* 8-byte boundary alignment */

/*
 * DEV64 produces a 64 bit device number from a source that may
 *   be either 32 or 64 bit. It is used to write 64 bit device
 *   numbers into metadata.
 * DEV64TODEVT produces a native-sized device number from a source
 *   that is known to be a 64 bit device number.
 */
#define DEV64(_devno) ((dev64_t) ((((uint64)_devno) & DEVNO64) \
		? _devno \
		: (((_devno & (uint64)0xFFFF0000) << 16) | \
			(_devno & 0xFFFF) | DEVNO64)))
#if defined(__64BIT_KERNEL) || defined(__64BIT__)
#define DEV64TODEVT(_devno) (_devno)
#else
#define DEV64TODEVT(_devno) ((dev_t) \
	(((_devno & 0x0000FFFF00000000LL) >> 16) | (_devno & 0xFFFF)))
#endif /* __64BIT_KERNEL */


/*
 * memory object types
 */
typedef vmid_t	memoryObject_t;


/*
 *	handy
 */
#undef MIN
#define	MIN(a,b) (((a)<(b))?(a):(b))
#undef MAX
#define	MAX(a,b) (((a)>(b))?(a):(b))
#undef ROUNDUP
#define	ROUNDUP(x, y)	( ((x) + ((y) - 1)) & ~((y) - 1) )
#define CircularLength(delta, to, from, circle)\
{\
	delta = (to) - (from);\
	if (delta < 0)\
		delta += (circle);\
}

#define LEFTMOSTONE	0x80000000
#define	HIGHORDER	0x80000000u	/* high order bit on		*/
#undef ONES				/* vmm/vmdefs.h also defines ONES */
#define	ONES		0xffffffffu	/* all bit on			*/
#define	BITSPERINT32	32		/* number of bits in uint32	*/
#define	BITSPERINT64	64		/* number of bits in uint64	*/


#ifdef _notdef_
// following definitions are unused...

/*
 *	simple extent descriptor (xd)
 */
typedef struct {
	unsigned	flag:8;		/* 1: flags */
	unsigned	rsrvd:8;	/* 1: */
	unsigned	len:8;		/* 1: length in unit of fsblksize */
	unsigned	addr1:8;	/* 1: address in unit of fsblksize */
	uint32		addr2;		/* 4: address in unit of fsblksize */
} xd_t;					/* - 8 - */

/* xd_t field construction */
#define	XDlength(xd, length32)	( (xd)->len = length32 )
#define	XDaddress(xd, address64)\
{\
	(xd)->addr1 = (address64) >> 32;\
	(xd)->addr2 = (address64) & 0xffffffff;\
}

/* xd_t field extraction */
#define	lengthXD(xd)	( (xd)->len )
#define	addressXD(xd)\
	( ((int64)((xd)->addr1)) << 32 | (xd)->addr2 )

/*
 *	logical xd (lxd)
 */
typedef struct {
	unsigned	len:24;
	unsigned	off1:8;
	uint32		off2;
} lxd_t;

/* lxd_t field construction */
#define	LXDlength(lxd, length32)	( (lxd)->len = length32 )
#define	LXDoffset(lxd, offset64)\
{\
	(lxd)->off1 = (offset64) >> 32;\
	(lxd)->off2 = (offset64) & 0xffffffff;\
}

/* lxd_t field extraction */
#define	lengthLXD(lxd)	( (lxd)->len )
#define	offsetLXD(lxd)\
	( ((int64)((lxd)->off1)) << 32 | (lxd)->off2 )

/* lxd list */
typedef struct {
	int16	maxnlxd;
	int16	nlxd;
	lxd_t	*lxd;
} lxdlist_t;
#endif /* _notdef_ */

/*
 *	physical xd (pxd)
 */
typedef struct {
	unsigned	len:24;
	unsigned	addr1:8;
	uint32		addr2;
} pxd_t;

/* pxd_t field construction */
#define	PXDlength(pxd, length32)	( (pxd)->len = length32 )
#define	PXDaddress(pxd, address64)\
{\
	(pxd)->addr1 = (address64) >> 32;\
	(pxd)->addr2 = (address64) & 0xffffffff;\
}

/* pxd_t field extraction */
#define	lengthPXD(pxd)	( (pxd)->len )
#define	addressPXD(pxd)\
	( ((int64)((pxd)->addr1)) << 32 | (pxd)->addr2 )

/* pxd_t raw data extraction */
#define	highPXD(pxd)	( ((pxd)->len << 8) | ((pxd)->addr1) )
#define	lowPXD(pxd)	( (pxd)->addr2 )

/* pxd list */
typedef struct {
	int16	maxnpxd;
	int16	npxd;
	pxd_t	pxd[8];
} pxdlist_t;

/*
 *	Extended Attribute root/descriptor
 *
 * EAv2 eaRoot descriptor overlaied on EAv1 ea descriptor
 */
/* flag field for EAv1 and EAv2 */
#define	eaRootEAv1	0x00
#define	eaRootEAv2	0x01

/*
 *	EAv2: eaRoot in inode: i_eaRoot
 */
typedef struct {
	uint8	eaFlag;	/* EAv2: eaRootEAv2; EAv1: eaRootEAv1 */
	uint8	rsrvd1;
	uint16	rsrvd2;
	int32	rsrvd3;
	ino64_t	eaDirectory;	/* eaDirectory object */

	uint64	eaMode;	/* extended mode */
	ino64_t	eaACL;	/* extended ACL object */

	union {
		struct {
			uint64	eaRootEntry[8];
		} primaryObject;
		struct {
			uint64	aclType;
			ino64_t	aclOwner;
			uint64	eaRootEntry[6];
		} aclObject;
		struct {
			uint64	eaRootEntry[8];
		} eaObject;
	} eaRootData;
} eaRoot_t; /* 96 */

/*
 *	EAv1: ea descriptor in inode: i_ea
 */
typedef	struct {
	uint8	flag;		/* 1: flags */
	uint8	nEntry;		/* 1: */
	uint8	len;		/* 1: length in unit of fsblksize */
	uint8	addr1;		/* 1: address in unit of fsblksize */
	uint32	addr2;		/* 4: address in unit of fsblksize */
	uint16	type;		/* 2: ea type */
	int16	nblocks;	/* 2: nBlocks for outline pages */
	int32	rsrvd;		/* 4: */
} ead_t; /* 16 */

/* ead_t field construction */
#define	EADlength(ead, length8)	( (ead)->len = length8 )
#define	EADaddress(ead, address64)\
{\
	(ead)->addr1 = (address64) >> 32;\
	(ead)->addr2 = (address64) & 0xffffffff;\
}

/* ead_t field extraction */
#define	lengthEAD(ead)	( (ead)->len )
#define	addressEAD(ead)\
	( ((int64)((ead)->addr1)) << 32 | (ead)->addr2 )


/*
 *	data extent descriptor (dxd)
 */
typedef struct {
	unsigned	flag:8;		/* 1: flags */
	unsigned	rsrvd:24;	/* 3: */
	uint32		rsrvd2;		/* 4: */
	unsigned	len:24;		/* 3: size in bytes */
	unsigned	addr1:8;	/* 1: address in unit of fsblksize */
	uint32		addr2;		/* 4: address in unit of fsblksize */
} dxd_t;				/* - 16 - */

/* dxd_t flags */
#define	DXD_INDEX	0x80	/* B+-tree index */
#define	DXD_INLINE	0x40	/* in-line data extent */
#define	DXD_EXTENT	0x20	/* out-of-line single extent */	
#define	DXD_FILE	0x10	/* out-of-line file (inode) */	
#define DXD_CORRUPT	0x08	/* Inconsistency detected */

/* dxd_t field construction */
#define	DXDlength(dxd, length32)	( (dxd)->len = length32 )
#define	DXDaddress(dxd, address64)\
{\
	(dxd)->addr1 = (address64) >> 32;\
	(dxd)->addr2 = (address64) & 0xffffffff;\
}

/* dxd_t field extraction */
#define	lengthDXD(dxd)	( (dxd)->len )
#define	addressDXD(dxd)\
	( ((int64)((dxd)->addr1)) << 32 | (dxd)->addr2 )


/*
 *	extent allocation descriptor (xad)
 */
typedef struct xad {
	unsigned	flag:8;		/* 1: flag */
	unsigned	rsvrd:16;	/* 2: reserved */
	unsigned	off1:8;		/* 1: offset in unit of fsblksize */
	uint32		off2;		/* 4: offset in unit of fsblksize */
	unsigned	len:24;		/* 3: length in unit of fsblksize */
	unsigned	addr1:8;	/* 1: address in unit of fsblksize */
	uint32		addr2;		/* 4: address in unit of fsblksize */
} xad_t;				/* (16) */

#define MAXXLEN		((1 << 24) - 1)

#define XTSLOTSIZE	16
#define	L2XTSLOTSIZE	4

/* xad_t field construction */
#define	XADoffset(xad, offset64)\
{\
	(xad)->off1 = (offset64) >> 32;\
	(xad)->off2 = (offset64) & 0xffffffff;\
}
#define	XADaddress(xad, address64)\
{\
	(xad)->addr1 = (address64) >> 32;\
	(xad)->addr2 = (address64) & 0xffffffff;\
}
#define	XADlength(xad, length32)	(xad)->len = length32

/* xad_t field extraction */
#define	offsetXAD(xad)\
	( ((int64)((xad)->off1)) << 32 | (xad)->off2 )
#define	addressXAD(xad)\
	( ((int64)((xad)->addr1)) << 32 | (xad)->addr2 )
#define	lengthXAD(xad)	( (xad)->len )

/* xad_t flags */
#define XAD_NEW		0x01	/* new */
#define XAD_EXTENDED	0x02	/* extended */
#define	XAD_ABNR	0x04	/* allocated but not recorded */
/* #define XAD_RELOC       0x08    NO LONGER USED */

#define XAD_COW		0x10	/* copy-on-write */
#define XAD_COMPRESSED	0x20	/* compressed with recorded length */
#define XAD_EOF		0x80	
/* extended flag */
#define XAD_RBNA		0x1000	/* reserved but not allocated */
#define XAD_NOTALLOCATED	0x8000	/* not allocated */

/* The mask of flags that it makes sense to
   call xtUpdate on */
#define XAD_UPDATABLE   XAD_ABNR

/* extent type for relocation */
#define	INODE_TYPE	0x0000F000   /* IFREG or IFDIR */
#define EXTENT_TYPE	0x000000ff
#define EXTENT_DTPAGE	0x00000001
#define EXTENT_XTPAGE	0x00000002
#define EXTENT_DATA	0x00000004
#define EXTENT_EAv1	0x00000008

#ifdef _notdef_
// unused...

/*
 *	DFS primitive types
 */
/* DCE globally unique name */
typedef struct {
	uint32 uuid[4];
} uuid_t;

typedef uuid_t	dfsUUID;

/* a 64-bit identifier */
typedef struct {
	uint32 id[2];
} dfsHyper;
#endif /* _notdef_ */


/*
 *	name argument
 */
typedef struct component_name {
	int16	namlen;
	UniChar	*name;
} component_t;

/*
 *	client/server cookie
 */
typedef struct cookie {
	void	*handle;
	uint32	timestamp;
} cookie_t;

#ifndef _KERNEL
/* 
 * CDLL macros need to function both and in out of kernel.
 */
#define J2ERRAVOW(_level, _id, _CONDITION) ASSERT(_CONDITION)
#endif

/*
 *		circular doubly-linked list (cdll)
 *
 * A circular doubly-linked list (cdll) is anchored by a pair of pointers,
 * one to the head of the list and the other to the tail of the list. 
 * The elements are doubly linked so that an arbitrary element can be 
 * removed without a need to traverse the list. 
 * New elements can be added to the list before or after an existing element, 
 * at the head of the list, or at the tail of the list.
 * A circle queue may be traversed in either direction.
 *
 * +----------+        +-------------------------------------+
 * |          |        |                                     |
 * +->+-----+ |        +->+-----+  +->+-----+    +->+-----+  |
 * |  |  h  +-+        |  |  h  +--+  |  n  +----+  |  n  +--+
 * |  +-----+          |  +-----+  |  +-----+    |  +-----+
 * |  |  t  +-+     +-----+  t  |  |  |  p  +--+ |  |  p  +--+
 * |  +-----+ |     |  |  +-----+  |  +-----+  | |  +-----+  |
 * +----------+     |  +-----------------------+ |           |
 *                  |              |             |           |
 *                  |              +-------------------------+
 *                  |                            |
 *                  +----------------------------+
 */
/*
 *	define header
 *
 * list header field definition in header element:
 *
 * type - type of list element struct embedding the link field
 */
#define CDLL_HEADER(type)\
struct {\
	struct type *head;\
	struct type *tail;\
}

struct cdll_header {
	struct cdll_header *head;
	struct cdll_header *tail;
};

/*
 *	define link
 *
 * list link field definition in list element: 
 *
 * type - type of parent list element struct embedding the link field
 */
#define CDLL_ENTRY(type)\
struct {\
	struct type *next;\
	struct type *prev;\
}

struct cdll_entry {
	struct cdll_entry *next;
	struct cdll_entry *prev;
};

/*
 *	initialize header
 *
 * header - ptr to the header field in the header element
 */
#define	CDLL_INIT(header) {\
	(header)->head = (void *)(header);\
	(header)->tail = (void *)(header);\
}

/*
 *	scan list
 *
 * header - ptr to the header field in the header element
 * elm - ptr to the element to be inserted
 * field - name of the link field in the list element
 *
 * struct header_container	*container;
 * struct header_type	*header;
 * struct element_type	*elm;
 *
 * header = &container->header_field;
 * for (elm = header->head; elm != (void *)header; elm = elm->field.next)
 */

/*
 *	insert <elm> at head of list anchored at <header>
 *
 * header - ptr to the header field in the header element
 * elm - ptr to the list element to be inserted
 * field - name of the link field in the list element
 */
#define CDLL_INSERT_HEAD(header, elm, field) {\
	J2ERRAVOW(J2ERRALWAYS,\ 
		  ECORRUPT_J2_TYPES_INVARIANT,\
		  (elm)->field.next == NULL &&\
		  (header)->head &&\
		  (header)->tail );\
	(elm)->field.next = (header)->head;\
	(elm)->field.prev = (void *)(header);\
	if ((header)->tail == (void *)(header))\
		(header)->tail = (elm);\
	else\
		(header)->head->field.prev = (elm);\
	(header)->head = (elm);\
}

/*
 *	insert <elm> at tail of list anchored at <header>
 *
 * header - ptr to the header field in the header element
 * elm - ptr to the list element to be inserted
 * field - name of the link field in the list element
 */
#define CDLL_INSERT_TAIL(header, elm, field) {\
	J2ERRAVOW(J2ERRALWAYS,\ 
		  ECORRUPT_J2_TYPES_INVARIANT,\
		  (elm)->field.next == NULL &&\
		  (header)->head &&\
		  (header)->tail );\
	(elm)->field.next = (void *)(header);\
	(elm)->field.prev = (header)->tail;\
	if ((header)->head == (void *)(header))\
		(header)->head = (elm);\
	else\
		(header)->tail->field.next = (elm);\
	(header)->tail = (elm);\
}

/*
 *	insert <elm> after <listelm> of list anchored at <header>
 *
 * header - ptr to the header field in the header element
 * listelm - ptr to the list element at insertion point
 * elm - ptr to the list element to be inserted
 * field - name of the link field in the list element
 */
#define CDLL_INSERT_AFTER(header, listelm, elm, field) {\
	J2ERRAVOW(J2ERRALWAYS,\ 
		  ECORRUPT_J2_TYPES_INVARIANT,\
		  (elm)->field.next == NULL &&\
		  (listelm)->field.next &&\
		  (listelm)->field.prev );\
	(elm)->field.next = (listelm)->field.next;\
	(elm)->field.prev = (listelm);\
	if ((listelm)->field.next == (void *)(header))\
		(header)->tail = (elm);\
	else\
		(listelm)->field.next->field.prev = (elm);\
	(listelm)->field.next = (elm);\
}

/*
 *	insert <elm> before <listelm> of list anchored at <header>
 *
 * header - ptr to the header field in the header element
 * listelm - ptr to list element at insertion point
 * elm - ptr to the element to be inserted
 * field - name of the link field in the list element
 */
#define CDLL_INSERT_BEFORE(header, listelm, elm, field) {\
	J2ERRAVOW(J2ERRALWAYS,\ 
		  ECORRUPT_J2_TYPES_INVARIANT,\
		  (elm)->field.next == NULL &&\
		  (listelm)->field.next &&\
		  (listelm)->field.prev );\
	(elm)->field.next = (listelm);\
	(elm)->field.prev = (listelm)->field.prev;\
	if ((listelm)->field.prev == (void *)(header))\
		(header)->head = (elm);\
	else\
		(listelm)->field.prev->field.next = (elm);\
	(listelm)->field.prev = (elm);\
}

/*
 *	remove <elm> from list anchored at <header>
 *
 * header - ptr to the header field in the header element
 * elm - ptr to the list element to be removed
 * field - name of the link field in the list element
 */
#define	CDLL_REMOVE(header, elm, field) {\
	J2ERRAVOW(J2ERRALWAYS,\
		  ECORRUPT_J2_TYPES_INVARIANT,\
		  (elm)->field.next );\
	if ((elm)->field.next == (void *)(header))\
		(header)->tail = (elm)->field.prev;\
	else\
		(elm)->field.next->field.prev = (elm)->field.prev;\
	if ((elm)->field.prev == (void *)(header))\
		(header)->head = (elm)->field.next;\
	else\
		(elm)->field.prev->field.next = (elm)->field.next;\
	(elm)->field.next = NULL;\
}

#define CDLL_MOVE_TO_HEAD(header, elm, field) {\
	J2ERRAVOW(J2ERRALWAYS,\
		  ECORRUPT_J2_TYPES_INVARIANT,\
		  (elm)->field.next );\
	if ((elm)->field.prev != (void *)(header))\
	{\
		if ((elm)->field.next == (void *)(header))\
			(header)->tail = (elm)->field.prev;\
		else\
			(elm)->field.next->field.prev = (elm)->field.prev;\
		(elm)->field.prev->field.next = (elm)->field.next;\
		(elm)->field.next = (header)->head;\
		(elm)->field.prev = (void *)(header);\
		(header)->head->field.prev = (elm);\
		(header)->head = (elm);\
	}\
}

#define CDLL_MOVE_TO_TAIL(header, elm, field) {\
	J2ERRAVOW(J2ERRALWAYS,\
		  ECORRUPT_J2_TYPES_INVARIANT,\
		  (elm)->field.next );\
	if ((elm)->field.next != (void *)(header))\
	{\
		(elm)->field.next->field.prev = (elm)->field.prev;\
		if ((elm)->field.prev == (void *)(header))\
			(header)->head = (elm)->field.next;\
		else\
			(elm)->field.prev->field.next = (elm)->field.next;\
		(elm)->field.next = (void *)(header);\
		(elm)->field.prev = (header)->tail;\
		(header)->tail->field.next = (elm);\
		(header)->tail = (elm);\
	}\
}

/*
 *	orphan list element
 */
#define	CDLL_SELF(elm, field)\
	J2ERRAVOW(J2ERRALWAYS,\
		  ECORRUPT_J2_TYPES_INVARIANT,\
		  (elm)->field.next );\
	(elm)->field.next = (elm)->field.prev = (elm);


/*
 *		single head doubly-linked list
 *
 * A list is headed by a single head pointer.
 * The elements are doubly linked so that an arbitrary element can be 
 * removed without a need to traverse the list. 
 * New elements can be added to the list at the head of the list, or 
 * after an existing element (NO insert at tail).
 * A list may only be traversed in the forward direction.
 * (note: the list is NULL terminated in next field.)
 *
 *   +-----+          +->+-----+  +->+-----+    +->+-----+  
 *   | NULL|          |  |  h  +--+  |  n  +----+  | NULL|     
 *   +-----+          |  +-----+  |  +-----+       +-----+
 *                    |           |  |  p  +--+    |  p  +--+
 *                    |           |  +-----+  |    +-----+  |
 *                    +-----------------------+             |
 *                                |                         |
 *                                +-------------------------+
 */
#define LIST_HEADER(type)\
struct {\
	struct type *head;\
}

#define LIST_ENTRY(type)\
struct {\
	struct type *next;\
	struct type **prev;\
}

#define	LIST_INIT(header)	{ (header)->head = NULL; }

/*
 *	scan list
 *
 * header - ptr to the header (field in header element)
 * elm - ptr to the element to be inserted
 * field - name of the link field in list element
 *
 * struct header_container	*container;
 * struct header_type	*header;
 * struct element_type	*elm;
 *
 * header = &container->header_field;
 * for (elm = header->head; elm; elm = elm->field.next)
 */

#define LIST_INSERT_HEAD(header, elm, field) {\
	if (((elm)->field.next = (header)->head) != NULL)\
		(header)->head->field.prev = &(elm)->field.next;\
	(header)->head = (elm);\
	(elm)->field.prev = &(header)->head;\
}

#define LIST_INSERT_AFTER(listelm, elm, field) {\
	if (((elm)->field.next = (listelm)->field.next) != NULL)\
		(listelm)->field.next->field.prev = &(elm)->field.next;\
	(listelm)->field.next = (elm);\
	(elm)->field.prev = &(listelm)->field.next;\
}

#define LIST_REMOVE(elm, field) {\
	if ((elm)->field.next != NULL)\
		(elm)->field.next->field.prev = (elm)->field.prev;\
	*(elm)->field.prev = (elm)->field.next;\
}

#define LIST_SELF(elm, field) {\
	(elm)->field.next = NULL;\
	(elm)->field.prev = &(elm)->field.next;\
}

/* queue macros */

#define QUEUE_INSERT_LIST(_queue, _head, _tail, _field) \
{							\
	if (_queue)					\
	{						\
		(_tail)->_field = (_queue)->_field;	\
		(_queue)->_field = _head;		\
	}						\
	else						\
	{						\
		(_tail)->_field = _head;		\
	}						\
							\
	_queue = _tail;					\
}

#define QUEUE_INSERT(_queue, _elm, _field) \
	QUEUE_INSERT_LIST(_queue, _elm, _elm, _field)

#define QUEUE_DEQUEUE(_queue, _var, _field) \
{							\
	if ((_var = (_queue)->_field) == (_queue))	\
		_queue = NULL;				\
	else						\
		(_queue)->_field = (_var)->_field;	\
							\
	(_var)->_field = NULL;				\
}

/* Compile time assert. Shamelessly cribbed from vmmacs.h. */
#define J2_FILE_ASSERT(id,test)				\
	struct CoMpIlE_aSsErT__##id { char v[(test) ? 1 : -1]; }

#endif /* !_H_J2_TYPES */
