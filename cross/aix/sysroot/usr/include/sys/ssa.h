/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* ssa53L src/ssa/kernel/sys/POWER/ssa.h 1.17                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1994,2007          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)12 1.17  src/ssa/kernel/sys/POWER/ssa.h, ssaadapdd, ssa53L, l2007_24A2 6/6/07 11:44:10 */
/************************************************************************/
/*									*/
/*  COMPONENT NAME:	SSAADAPDD SSA Subsystem				*/
/*									*/
/*  FUNCTIONS:		Header file for SSA subsystem			*/
/*									*/
/*  ORIGINS:		27						*/
/*									*/
/*  (C)	COPYRIGHT International	Business Machines Corp.	1995		*/
/*  All	rights reserved.						*/
/*  Licensed Materials - Propery of IBM					*/
/*									*/
/*  US Government Users Restricted Rights - Use, duplication or		*/
/*  disclosure restricted by GSA ADP Schedule Contract with IBM Corp.	*/
/*									*/
/************************************************************************/

#ifndef	_SSA_H_INC
#define	_SSA_H_INC

/************************************************************************/
/* Include system headers						*/
/************************************************************************/

#include <sys/types.h>
#include <sys/cfgdb.h>
#include <sys/utsname.h>

/************************************************************************/
/* Include the IPN header files						*/
/************************************************************************/

#include <ipn/ipndef.h>
#include <ipn/ipntra.h>
#include <ipn/ipnreg.h>
#include <ipn/ipnprs.h>

/************************************************************************/
/* General definitions							*/
/************************************************************************/

#define	SSA_VPD_SIZE	    161		/* Vital Product Data info.	*/
#define SSA_CODE_ID_SIZE    8		/* Size of code identifier	*/
#define	SSA_SERIAL_NO_SIZE  (D__SERIALNUMBERSIZE)
#define	SSA_STA_SIZE	    256		/* Small transfer area size	*/
#define SSA_MAX_STRING_LENGTH 256       /* general string length        */


/************************************************************************/
/* The openx() extension flags to be used when opening /dev/dssaX	*/
/************************************************************************/

#define SSA_DAEMON	    0x0008	/* This is the daemon open	*/

/************************************************************************/
/* The minor number offset which is used for daemon files /dev/dssaX	*/
/************************************************************************/

#define SSA_DAEMON_MINOR    0x1000	/* daemon minor numbers >= this	*/

/************************************************************************/
/* Define the node numbering scheme used				*/
/************************************************************************/

#if defined( NN_NewAdaptor )

# define SSA_FIRST_NODE   NN_NewAdaptor
# define SSA_MAX_NODES	  (NN_NewAdaptorEnd - NN_NewAdaptor + 1)

#else

# define SSA_FIRST_NODE   128		/* Start numbering from 128	*/
# define SSA_MAX_NODES	  64		/* We support upto 64 adapters	*/

#endif

/************************************************************************/
/* Define the data types used in the device driver			*/
/************************************************************************/

/************************************************************************/
/* The device specific data block					*/
/* This is split up into two parts:					*/
/* A generic first half for both PCI and MCA SSA adapters.		*/
/* A second half specific to the MCA SSA adapter.			*/
/************************************************************************/

typedef	struct _SSA_DDS_t	    /* Device Dependent	Structure	*/
{

    __ulong32_t	ulSlotNumber; 		  /* Where the adapter is 	*/
    Inodenum    Node;			  /* The IPN node ID		*/
    __ulong32_t ulBusID;	    	  /* The IO bus ID		*/
    __ulong32_t	ulBusNumber;	    	  /* The bus number (0 or 1)	*/
    __ulong32_t	ulIRQLevel;	    	  /* The interrupt level	*/
    __ulong32_t	ulIRQPriority;	    	  /* The interrupt priority	*/
    uint_t      IOAddress;	    	  /* The I/O base address	*/
    uint_t	WindowAddress; 		  /* Window address		*/
    uint_t	ulWindowSize;  		  /* Size of the window		*/
    uint_t	ulCardID;      		  /* ID of the card 		*/
    char	szDeviceName[ NAMESIZE ]; /* The device's logical name	*/
    Icluster	ClusterNumber;		  /* IPN cluster #, for fencing	*/
    char	Host_ID[SYS_NMLN];	  /* Machine Unique ID 		*/
    char	HostName[D__MAXPEERLABELLENGTH]; /* HostName for Adapter*/

/************************************************************************/
/* Micro Channel specific parts ...					*/
/************************************************************************/

    __ulong32_t	ulBusType;	    	  /* The bus type		*/
    __ulong32_t	DMAAddress;    		  /* DMA'able window		*/
    __ulong32_t	ulDMASize;     		  /* DMA'able window size	*/
    __ulong32_t	ulDMALevel;    		  /* The DMA level		*/

/************************************************************************/
/* PCI specific parts ...						*/
/************************************************************************/

    __ulong32_t	ulSGPages;	 	  /* Size of scatter/gather map	*/
    uint_t	WindowAddress2;		  /* Adapter memory window addr	*/
    uint_t	WindowAddress3; 	  /* Adapter memory window addr	*/
    uint_t	WindowAddress4;		  /* Adapter memory window addr	*/
    int		bStageWrites;		  /* Write staging ?		*/
    int		bStageReads;		  /* Read staging ?		*/
    int		bUseMemoryReadLine;	  /* Use PCI mem read line?	*/
    uint_t      ulPollThreshold;          /* Threshold to switch to poll*/
} SSA_DDS_t, * pSSA_DDS_t;

/************************************************************************/
/* The parameter block passed to the driver direct call	entry point	*/
/************************************************************************/

typedef	struct _SSA_Ioreq_t	    /* A transaction to the IPN kernel	*/
{

    DPB	    SsaDPB;                 /* For use by the adapter driver	*/
    void    (* SsaNotify)( struct _SSA_Ioreq_t * );/* Completion func	*/
    union
    {
	SOP	_SsaSOP;	    /* For slave operations		*/
	SAN	_SsaSAN;	    /* For allocate service number	*/
	SFN	_SsaSFN;	    /* For free	service	number		*/
	SIS	_SsaSIS;	    /* For slave install service	*/
	SRS	_SsaSRS;	    /* For slave remove	service		*/
	MCB	_SsaMCB;	    /* For MCB transactions		*/
    }u0;

} SSA_Ioreq_t, * pSSA_Ioreq_t;

#define	SsaSOP u0._SsaSOP
#define	SsaSAN u0._SsaSAN
#define	SsaSFN u0._SsaSFN
#define	SsaSIS u0._SsaSIS
#define	SsaSRS u0._SsaSRS
#define	SsaMCB u0._SsaMCB

/************************************************************************/
/* With the 64 Bit AIX kernel, the length of a DDR is no longer big     */
/* enough for the data required by a DT_Xmd DDR type. (It requires two  */
/* pointers and there are only 12 spare bytes).  To work around this,   */
/* we define a DDR extension which holds these two pointers and use     */
/* the DDR_Base field to point to the DDR extension.  A number of       */
/* access macros are also defined to setup DT_Xmd DDRs.                 */
/*                                                                      */
/* Note that this structure will never be used in 32 bit mode, but      */
/*  it needs to exist and have its address taken.                       */
/************************************************************************/
typedef struct
{
    caddr_t          base;
    struct xmem *    xmem;
} SSA_XmdDDRExt_t, *pSSA_XmdDDRExt_t;

#ifdef __64BIT_KERNEL
#define SSA_SETUP_XMD_DDR(pBuffer,pXmem,pBase) \
                                ((pSSA_XmdDDRExt_t)(pBuffer))->xmem = pXmem; \
                                ((pSSA_XmdDDRExt_t)(pBuffer))->base = pBase
#define SSA_SETUP_XMD_DDR_DEFAULT(pBuffer,pXmem) SSA_SETUP_XMD_DDR((pBuffer),(pXmem),\
                                           ((char *)(pBuffer) + sizeof(SSA_XmdDDRExt_t)))

#define SSA_DDR_BASE(pBuffer,pXmem)      (pBuffer)
#define SSA_DDR_OFFSET(pBuffer)          (0)
#define SSA_GET_BASE_XMDDR(pDDR)         ((pSSA_XmdDDRExt_t) \
                                          (Ddr_Base( pDDR )))->base
#define SSA_GET_XMEM_XMDDR(pDDR)         ((pSSA_XmdDDRExt_t) \
                                          (Ddr_Base( pDDR )))->xmem
#define SSA_GET_BUFFER_BASE(pDDR)        (caddr_t)Ddr_Base( pDDR )
#else
#define SSA_SETUP_XMD_DDR(Buffer,Xmem,pBase)
#define SSA_SETUP_XMD_DDR_DEFAULT(pBuffer,pXmem)
#define SSA_DDR_BASE(pBuffer,pXmem)          (caddr_t)(pXmem)
#define SSA_DDR_OFFSET(pBuffer)              (Iu32)(pBuffer)
#define SSA_GET_BASE_XMDDR(pDDR)             (caddr_t)Ddr_Offset( pDDR )
#define SSA_GET_XMEM_XMDDR(pDDR)             (struct xmem *)Ddr_Base( pDDR )
#define SSA_GET_BUFFER_BASE(pDDR)            (caddr_t)Ddr_Offset( pDDR )
#endif


/************************************************************************/
/* The IOCTL issued by an other	device driver to get the entry point	*/
/************************************************************************/

#define	SSA_GET_ENTRY_POINT 256	    /* For other device	drivers	only	*/

typedef	struct _SSA_GetEntryPointParms_t    /* To get the entry point	*/
{

    void    (*EntryPoint)( pSSA_Ioreq_t	);  /* Direct call entry point	*/
    int	    InterruptPriority;		    /* Interrupt priority at	*/
					    /* which transactions are	*/
					    /* completed.		*/

} SSA_GetEntryPointParms_t, * pSSA_GetEntryPointParms_t;

/************************************************************************/
/* The IOCTLs issued by a user process to submit a transaction to IPN	*/
/************************************************************************/

#define	SSA_TRANSACTION	     257    /* To submit a transaction directly	*/
#define	SSA_CONC_TRANSACTION 258    /* Submit a transaction directly	*/
				    /* Allows many at a time		*/

typedef struct _SSA_Result_t	    /* Result words for transaction	*/
{
    union
    {
	Iu32	AllResults;	    /* All result fields as one word	*/
	struct			    /* Result word broken down		*/
	{

	    Iu8     Reserved;	    /* Not used	(always set to zero)	*/
	    Idsb    NetworkResult;  /* Network status byte		*/
	    Is16    ServiceResult;  /* Service result word		*/

	} s1;

    } u1;

} SSA_Result_t, * pSSA_Result_t;

#define SSA_AllResults    u1.AllResults
#define SSA_NetworkResult u1.s1.NetworkResult
#define SSA_ServiceResult u1.s1.ServiceResult

typedef	struct _SSA_TransactionParms_t
{

    Inodenum	DestinationNode;    /* Target node for the transaction	*/
    Iservice	DestinationService; /* Target service on that node	*/
    Iu8		MajorFunction;	    /* Major code of function to do	*/
    Iu16	MinorFunction;	    /* Minor code of function to do	*/
    DDR		ParameterDDR;	    /* Parameters to the request	*/
    DDR		TransmitDDR;	    /* Transmitted data	buffer		*/
    DDR		ReceiveDDR;	    /* Received	data buffer		*/
    DDR		StatusDDR;	    /* Status buffer			*/
    SSA_Result_t TransactionResult; /* Result codes for the transaction	*/
    Idsb	DirectiveStatusByte;/* Status byte for this transaction	*/
    Iu32	TimeOutPeriod;	    /* Number of seconds to timeout cmd */
				    /* 0 == no timeout limit		*/

} SSA_TransactionParms_t, * pSSA_TransactionParms_t;

#define	SSA_RESET_MONITOR  259    /* IOCTL code to set parameters for Reset Monitor */

/* Interface structure between user and kernel areas */
typedef struct
{
   int NumberOfSeconds;
   int AcceptableNumberOfResets;
   
} ResetMonitorParameters_t;

#if defined( _KERNEL )

/************************************************************************/
/* Device driver only types required for 64 bit application support	*/
/* A DDR from a 64 bit application has 64 bit pointers in it		*/
/************************************************************************/

typedef struct _DDR64 
{
    union
      {
      Iu16              DD_PageSize;
      struct
        {
        Iu8             DD_Spare[2];
        Iu8             DD_SGCount;
        Iu8             DD_Type;
        } s1;
      } u1;
    ptr64               DDR_Base;
    Iu32                DDR_Offset;
    Iu32                DDR_Length;

} DDR64;

/************************************************************************/
/* A submit transaction IOCTL has 64 bit DDRs in it			*/
/************************************************************************/

typedef	struct _SSA_TransactionParms64_t
{

    Inodenum	DestinationNode;    /* Target node for the transaction	*/
    Iservice	DestinationService; /* Target service on that node	*/
    Iu8		MajorFunction;	    /* Major code of function to do	*/
    Iu16	MinorFunction;	    /* Minor code of function to do	*/
    DDR64	ParameterDDR;	    /* Parameters to the request	*/
    DDR64	TransmitDDR;	    /* Transmitted data	buffer		*/
    DDR64	ReceiveDDR;	    /* Received	data buffer		*/
    DDR64	StatusDDR;	    /* Status buffer			*/
    SSA_Result_t TransactionResult; /* Result codes for the transaction	*/
    Idsb	DirectiveStatusByte;/* Status byte for this transaction	*/
    Iu32	TimeOutPeriod;	    /* Number of seconds to timeout cmd */
				    /* 0 == no timeout limit		*/

} SSA_TransactionParms64_t, * pSSA_TransactionParms64_t;

/************************************************************************/
/* Device driver only types required for 32 bit application support	*/
/* by 64 bit device driver.                                          	*/
/* A DDR from a 32 bit application has 32 bit pointers in it		*/
/************************************************************************/

typedef struct _DDR32
{
    union
      {
      Iu16              DD_PageSize;
      struct
        {
        Iu8             DD_Spare[2];
        Iu8             DD_SGCount;
        Iu8             DD_Type;
        } s1;
      } u1;
    ptr32               DDR_Base;
    Iu32                DDR_Offset;
    Iu32                DDR_Length;

} DDR32;

/************************************************************************/
/* A submit transaction IOCTL has 32 bit DDRs in it			*/
/************************************************************************/

typedef	struct _SSA_TransactionParms32_t
{

    Inodenum	DestinationNode;    /* Target node for the transaction	*/
    Iservice	DestinationService; /* Target service on that node	*/
    Iu8		MajorFunction;	    /* Major code of function to do	*/
    Iu16	MinorFunction;	    /* Minor code of function to do	*/
    DDR32	ParameterDDR;	    /* Parameters to the request	*/
    DDR32	TransmitDDR;	    /* Transmitted data	buffer		*/
    DDR32	ReceiveDDR;	    /* Received	data buffer		*/
    DDR32	StatusDDR;	    /* Status buffer			*/
    SSA_Result_t TransactionResult; /* Result codes for the transaction	*/
    Idsb	DirectiveStatusByte;/* Status byte for this transaction	*/
    Iu32	TimeOutPeriod;	    /* Number of seconds to timeout cmd */
				    /* 0 == no timeout limit		*/

} SSA_TransactionParms32_t, * pSSA_TransactionParms32_t;

#endif				    /* defined _KERNEL			*/

/************************************************************************/
/* The transactions supported by the SSA Gateway service (SSAGS)	*/
/* All fields in the DDR structures listed below must be LITTLE ENDIAN.	*/
/************************************************************************/

#define	FN_SSAGS_Reset		  ((Iu16)64)
#define	FN_SSAGS_Download	  ((Iu16)65)
#define	FN_SSAGS_ResetCount	  ((Iu16)66)
#define FN_SSAGS_IdentifyNode	  ((Iu16)67)
#define FN_SSAGS_GetClusterNumber ((Iu16)68)
#define FN_SSAGS_GetErrorCode	  ((Iu16)69)
#define FN_SSAGS_ChgCluster	  ((Iu16)70)

/************************************************************************/
/* The parameters DDR for the FN_SSAGS_Reset, FN_SSAGS_UcodeLevel,	*/
/* and the FN_SSAGS_ResetCount transactions.				*/
/* Also the status DDR for FN_SSAGS_IdentifyNode transaction.		*/
/************************************************************************/

typedef	struct _SSAGS_NodeParms_t
{

    Inodenum	ulNode;		    /* Node to act on (little endian)	*/

} SSAGS_NodeParms_t, * pSSAGS_NodeParms_t;

/************************************************************************/
/* The parameters DDR for the FN_SSAGS_Download transaction		*/
/************************************************************************/

typedef	struct _SSAGS_DownloadParms_t
{

    Inodenum	ulNode;		     /* Node to act on (little endian)	*/
    __ulong32_t	ulLRC;		     /* Ucode checksum (little endian)	*/
    char	CodeIdentifier[ SSA_CODE_ID_SIZE ]; /* Code identifier	*/

} SSAGS_DownloadParms_t, * pSSAGS_DownloadParms_t;

/************************************************************************/
/* The status DDR for the FN_SSAGS_Download transaction			*/
/************************************************************************/

typedef struct _SSAGS_DownloadStatus_t
{

    int		bValid;		    /* Error value valid (little endian)*/
    Iu8		ErrorRegister;	    /* Contents of adapter error reg.	*/

} SSAGS_DownloadStatus_t, * pSSAGS_DownloadStatus_t;

/************************************************************************/
/* The status DDR for the FN_SSAGS_ResetCount transaction		*/
/************************************************************************/

typedef	struct _SSAGS_ResetCount_t
{

    __ulong32_t	ulResetCount;	    /* Number of resets (little endian)	*/

} SSAGS_ResetCount_t, *pSSAGS_ResetCount_t;

/************************************************************************/
/* The parameters DDR for the FN_SSAGS_IdentifyNode transaction		*/
/************************************************************************/

typedef struct _SSAGS_IdentifyNodeParms_t
{

    TCB	*	pTCB;		    /* TCB addr to match (little endian)*/

} SSAGS_IdentifyNodeParms_t, * pSSAGS_IdentifyNodeParms_t;

/************************************************************************/
/* The status DDR for the FN_SSAGS_GetErrorCode transaction		*/
/************************************************************************/

typedef struct _SSAGS_AdapErrStatus_t
{
    Iu8     ErrorCode[ 4 ];	   /* The error code being reported	*/
    int     bValid;		   /* Is the above valid data		*/

} SSAGS_AdapErrStatus_t, * pSSAGS_AdapErrStatus_t;

/************************************************************************/
/* Errors reported by the SSAGS service					*/
/************************************************************************/

#define AE_SSAGS_UnknownNode		((Is16)(-100+ 0))
#define	AE_SSAGS_BadParmSize		((Is16)(-100+ 1))
#define AE_SSAGS_HardwareError		((Is16)(-100+ 2))

/************************************************************************/
/* Transactions	supported by the error logger (SSAES)			*/
/************************************************************************/

#define	FN_IELL_RegisterForLogging	((Iu16)64)
#define	FN_IELL_UnregisterForLogging	((Iu16)65)
#define	FN_IELL_ResetThreshold		((Iu16)66)

/************************************************************************/
/* The parameters DDR for these	commands				*/
/************************************************************************/

typedef	struct _SSAES_SerialNumber_t	    /* Serial number type	*/
{

    uchar_t SerialNumber[ SSA_SERIAL_NO_SIZE ];

} SSAES_SerialNumber_t,	* pSSAES_SerialNumber_t;

typedef	struct _SSAES_IellTemplate_t	    /* An error	template	*/
{					    /* All fields little endian	*/

    uchar_t	    TemplateNo;		    /* Template	number		*/
    uint_t	    ErrorID;		    /* AIX error ID		*/
    uint_t	    SenseLength;	    /* Length to be logged	*/
    int		    Threshold;		    /* Bool: Threshold this ?	*/
    __ulong32_t	    ThresholdValue;	    /* Number of errors	to log	*/
    __ulong32_t	    ThresholdTime;	    /* Threshold period (secs)	*/
    __ulong32_t	    FirstLogTime;	    /* Start of	thresholding	*/
    __ulong32_t	    ErrorsLogged;	    /* Log book	of errors	*/

} SSAES_IellTemplate_t,	* pSSAES_IellTemplate_t;

typedef	struct _SSAES_IellReg_t		    /* Error logger registration*/
{					    /* All fields little endian	*/

    QUE			  Linkage;	    /* For error logger	use	*/
    uint_t		  Reserved[ 2 ];    /* For error logger	use	*/
    char		  ResourceName[	NAMESIZE ];/* AIX resource name	*/
    uchar_t		  Type;		    /* The error sender's type	*/
    SSAES_SerialNumber_t  SerialNumber;	    /* The serial number	*/
    int			  TemplateCount;    /* Number of templates	*/
    pSSAES_IellTemplate_t pTemplateArray;   /* The error templates	*/

} SSAES_IellReg_t, * pSSAES_IellReg_t;

typedef	struct _SSAES_IellResetThreshold_t  /* Reset thresholding	*/ 
{

    SSAES_SerialNumber_t  SerialNumber;     /* Serial # 		*/
    uchar_t		  Type;		    /* The error sender's type	*/

} SSAES_IellResetThreshold_t;

/************************************************************************/
/* Errors reported by the SSAES service					*/
/************************************************************************/

#define	AE_SSAES_BadParmType		((Is16)(-100+ 0))
#define	AE_SSAES_BadParmSize		((Is16)(-100+ 1))
#define	AE_SSAES_AlreadyRegistered	((Is16)(-100+ 2))
#define	AE_SSAES_NotRegistered		((Is16)(-100+ 3))
#define	AE_SSAES_IllegalTemplate	((Is16)(-100+ 4))

#endif	/* _SSA_H_INC */
