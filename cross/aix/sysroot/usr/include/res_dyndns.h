/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/res_dyndns.h 1.2                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1996,1995          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)45	1.2  src/bos/usr/include/res_dyndns.h, sockinc, bos530 8/19/95 10:50:58 */
/*
#
# COMPONENT_NAME: DHCP
#
# FUNCTIONS:
#
# ORIGINS: 27
#
#                  -- (                            when
# combined with the aggregated modules for this product)
# OBJECT CODE ONLY SOURCE MATERIALS
# (C) COPYRIGHT International Business Machines Corp. 1995
# All Rights Reserved
#
# US Government Users Restricted Rights - Use, duplication or
# disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#
*/
/* 
* Copyright (c) IBM Corporation 1995.  All Rights Reserved.
*/

#ifndef __INCL_RES_DYNDNS__
#define __INCL_RES_DYNDNS__

/*
 *******************************************************************************
 *
 *******************************************************************************
 */
#define B_ALGORITHM_OBJ	unsigned char *

/* max key size for all encryption algorithms (bytes) */
#define	MAXKEYSZ	320
/* default key size in bits */
#define DEFAULT_KEY_SIZE 360
/* Sig Key RR expiration pad time to give users a small break */
#define DEFAULT_SIG_KEY_EXPIRE_PAD (36*24*60*60)  /* 36 days */

/* Algorithm Id's */
#define ALGID_NONE      0	/* none used (unsecured) */
#define	ALGID_MD5RSA	1	/* MD5/RSA (BSAFE) */

/* value used to indicate a wildcard in DDNS Updates */
#define  WILDCARD    0xffffffff

/* DDNS API Return codes */
#define  RC_NOERR        1
#define  RC_INPUTERR     0
#define  RC_SYSERR      -1

/* handy linked-list structure for juggling RR's */
struct raw_rr_list {
		unsigned char	opcode;	/* add, delete, etc. */
		unsigned char      *raw_rr_ptr;
		u_short	    raw_rr_size;  /* overall size of the RR */
 		u_short	    flags;
#define RAW_RR_COPIED	1
		u_short	    r_type;
		u_short	    r_size;	/* size of the r_data only  */
		unsigned char      *r_data;	/* ptr into raw_rr_ptr area */
		struct raw_rr_list *alt_next;   /* rrs may be kept in 2 lists; this is the alternate next ptr */
		struct raw_rr_list *next;
};

/* handy place to store SIG-related data */
/* note: this struct is not meant to match the actual packet layout */
typedef struct _sigdata {
	u_short	typeCovered;
	unsigned char	algorithm;
	unsigned char	labels;
	u_long	original_ttl;
	u_long	sig_expiration;
	u_long	time_signed;
} SigData;

/* update builder control structure */
typedef struct UpdateCtlStruct  {
    
		    char *updateBuf;		/* buffer to hold update packet */
		    int   updateBufLength;      /* length of packet buffer */
		    int   packetLength;		/* current length of packet */
		    char  hostname[2*MAXDNAME+2];/* hostname being updated */
		    char  primary[2*MAXDNAME+2];/* primary NS for name being updated */
		    int   flags;		/* flags (see below) */
		    int   hostclass;		/* class of hostname */
		    int	  algorithm;		/* algorithm identifier */
		    unsigned int   pkExponent;	/* exponent of public key */
		    int   pkModulusLength;	/* length of PK modulus */
		    char  pkModulus[MAXKEYSZ];  /* ptr to PK modulus */
		    char *pKeyRR;		/* ptr to copy of KEY RR */
		    int   KeyRRlength;		/* total length of KEY RR */
		    char *pSigKeyRR;		/* ptr to copy of SIG KEY RR */
		    unsigned long SigKeyExpiration; /* time SIG RR expires */
		    char *algorithmControl;	/* algorithm-specific use */
		                                /* for MD5/RSA, it's a B_ALGORITHM_OBJ */
		    struct raw_rr_list *updateRRs;/* linked-lists of RR's: */
} UpdateControl;

/* UpdateControl flags definition */
#define UPDCTL_REFRESH	0x00000001	/* UPDATE is for SIG RR's only */
#define UPDCTL_NOKEYRR  0x00000002	/* hostname has no KEY RR in db */
#define UPDCTL_SIGNED   0x10000000	/* UPDATE has been signed; no more changes */
#define UPDCTL_UNUSABLE	0x20000000	/* UPDATE has some error in it */
#define UPDCTL_KEYGEN	0x40000000	/* Key generator mode */
#define UPDCTL_ADMIN	0x80000000	/* administrator mode */

typedef struct MD5FunctList
{
	int (*MD5WRSASigIn)(B_ALGORITHM_OBJ *,unsigned char *,unsigned int);
	int (*MD5WRSASigUp)(B_ALGORITHM_OBJ *,unsigned char *,unsigned int);
	int (*MD5WRSASigFi)(B_ALGORITHM_OBJ *,unsigned char *,unsigned int *);
	int (*MD5MakeKeys)(unsigned char *,
			   unsigned int *,
			   unsigned char *,
			   unsigned int *,
			   unsigned char *,
			   unsigned int *,
			   unsigned int,
			   unsigned char *,
			   unsigned int);
	int (*WriteKey)(unsigned char *,
			unsigned long,
			unsigned char *,
			unsigned char *,
			unsigned char *,
			unsigned char *,
			unsigned char *,
			unsigned long,
			unsigned long);
} MD5RList;

enum UpdateOpcode { noop=0, delete=1, addnew=2, addexists=3, add=4 };
#define ValidOpcode(op) (op==delete||op==addnew||op==addexists||op==add)

/* These functions provide the user API to the DYNDNS capabilities.   */

UpdateControl *
 DDNSInitUpdate( char *updateBuf,	/* buffer in which to build the update packet */
		 int   updateBuflen,	/* maximum length of the buffer */
		 char *keyfile,		/* fileid containing private key info */
		 char *updateName,	/* name to be updated */
		 char *updateDomain,	/* domain of the name to be updated */
		 char *updatePrimary,   /* dname of primary NS for updatee */
		 int   updateClass,     /* class of the name to be updated */
		 int   algorithmId,	/* 0=none, 1=MD5RSA, >1 = undefined */
		 unsigned int   updateFlags, /* update control flags */
		 MD5RList *MD5routines, /* MD5 routines */
		 unsigned long *latestsigexp); /* for threaded purposes this */

/* For updates to the various RR-types, individual functions are      */
/* provided so as to provide argument type and number checking to the */
/* users of the API. These functions actually call AppendDDNSUpdate,  */
/* which is hidden from the user as a static function.                */

/* T_A */
int	DDNSUpdate_A( UpdateControl *puc,	/* update control structure */
		      enum UpdateOpcode op,
		      u_long ttl,
		      u_long addr);

/* T_PTR */
int	DDNSUpdate_PTR( UpdateControl *puc,	/* update control structure */
			enum UpdateOpcode op,
			u_long ttl,
			char *name);

/* T_CNAME */
int	DDNSUpdate_CNAME( UpdateControl *puc,	/* update control structure */
			  enum UpdateOpcode op,
			  u_long ttl,
			  char *cname);

/*--- T_HINFO ---*/
int   DDNSUpdate_HINFO( UpdateControl *puc,
                        enum UpdateOpcode op,
                        u_long ttl,
                        char *cputype,
                        char *ostype );

/*--- T_MX ---*/
int   DDNSUpdate_MX( UpdateControl *puc,
                     enum UpdateOpcode op,
                     u_long ttl,
                     u_short preference,
                     char *exchange);

/* T_KEY */
int DDNSUpdate_KEY( UpdateControl *puc,
		    enum UpdateOpcode op,
		    u_long ttl,
		    u_short flags,
		    char protocol,
		    char algid,
		    int keylen,
		    char *key);

/* The AppendDDNSUpdate function is declared static to the res_dyndns.c file  */
/* so that users will be forced to call it only via the DDNSUpdate_ functions */

int 
 DDNSSignUpdate( UpdateControl *,	/* update control structure */
		 unsigned char *,	/* private key */
		 unsigned long  ,	/* private key length */
		 unsigned long  ,	/* original TTL */
		 unsigned long  ,	/* SIG Expiration time */
	         	  long  ,	/* SIG KEY expiration time pad */
		 MD5RList *	,	/* MD5 routines */
		 unsigned long *latestsigexp); /* for threaded purposes this */

int
 DDNSFinalizeUpdate( UpdateControl * );	/* update control structure */

int
 DumpDDNSUpdate( UpdateControl *pUpdateControl,/* update control structure */
		 int bufferLength,
		 FILE *fp);

int
 DDNSSendUpdate( UpdateControl * );	/* update control structure */

void
 DDNSFreeUpdate( UpdateControl * );	/* update control structure */

#endif /*ifndef __INCL_RES_DYNDNS__*/
