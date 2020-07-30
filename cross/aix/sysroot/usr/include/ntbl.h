/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2004,2005          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/*===================================================================*/
/*                                                                   */
/* Module Name: ntbl.h                                               */
/*                                                                   */
/*-------------------------------------------------------------------*/
/*                                                                   */
/* Description:  Header file for the Network Table                   */
/*               Services library 			             */
/*===================================================================*/
/* "@(#)94   1.7   src/css/hps/ntbl/include/ntbl.h, fed.ntbl, css_rc15, rc150530a 1/7/05 11:22:28"                                      */

#ifndef _NTBL_H
#define _NTBL_H

#include<sys/param.h>
#include<stropts.h>

#define DESCLEN 51
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/* Define name for device type returned by ntbl_adapter_resources */
/* enum name does not correlate directly to ntbl release          */
enum NTBL_DEVICE_TYPE {	HPS_V11 = 0x25e0,
			HPS_V12 = 0x25e1,
			HPS_V13 = 0x25e2,
			HPS_V14 = 0x25e3
			};

enum NTBL_RC {  NTBL_SUCCESS, 		/*  0 - Success			*/
		NTBL_EINVAL,		/*  1 - Invalid argument	*/
		NTBL_EPERM,		/*  2 - Caller not authorized	*/
		NTBL_EIOCTL,		/*  3 - Ioctl issued an error	*/
		NTBL_EADAPTER,		/*  4 - Invalid adapter		*/
		NTBL_ESYSTEM,		/*  5 - System Error occurred	*/
		NTBL_EMEM,		/*  6 - Memory error		*/
		NTBL_ELID,		/*  7 - Invalid LID		*/
		NTBL_EIO,		/*  8 - Adapter reports down    */
		NTBL_UNLOADED_STATE,    /*  9 - Window not currently loaded */
		NTBL_LOADED_STATE,	/*  10- Window is currently loaded */
		NTBL_DISABLED_STATE,	/*  11- Window is currently disabled */
		NTBL_ACTIVE_STATE,	/*  12- Window is currently active */
		NTBL_BUSY_STATE,	/*  13- Window is currently busy */
		NTBL_NO_RDMA_AVAIL      /*  14- No RDMA windows available */
                }; 

/* Structure for internal Network Table data */
/* Used for ntbl_load_table and ntbl_load_table_rdma */
/* Each structure represents a single window and task combination */
typedef struct {
    	unsigned short task_id;	   /* Task designated to use window	*/
	unsigned short lid;	   /* Logical ID of adapter 		*/
	unsigned short window_id;  /* Window id				*/
} NTBL;

/* Structure for status of Network Table Windows */
/* Each STATUS pointer represents a window's information */
/* Used for ntbl_status_adapter */
struct NTBL_STATUS {
	struct NTBL_STATUS *next;	  /* If not NULL, next window status */
	char user_name[MAXHOSTNAMELEN];      /* User name of uid             */
	pid_t client_pid;		     /* Pid of process that loaded   */
    	uid_t uid;			     /* Uid using the window         */
	unsigned short window_id;	     /* Window being reported        */
	char adapter[MAXHOSTNAMELEN];	     /* Adapter window resides on    */
        unsigned long long memory_requested; /* Memory requested by load     */
        unsigned long long memory_allocated; /* Memory allocated by load     */
	char time_loaded[100];		     /* Time load request was made   */
	char description[DESCLEN];	     /* Description given by load    */
	enum NTBL_RC rc;  		     /* Return code for window       */
	unsigned int bulk_transfer;	     /* Is this load using rDMA ?    */
	unsigned int rcontext_blocks;	     /* rcontexts per window         */
};

/* Structure for obtaining adapter resource information */
typedef struct {
	unsigned int device_type;	/* LED representing device type	    */ 
	unsigned short lid;		/* Logical ID of adapter            */
	unsigned short network_id;	/* Network ID of adapter            */
	unsigned long long max_window_memory;/* Max memory per window       */
	unsigned long long min_window_memory;/* Guaranteed minimum memory   */
	unsigned long long avail_adapter_memory;/* Aggregate device memory
					           available for windows    */
	unsigned long long fifo_slot_size;	/* Size of FIFO slot        */
	unsigned int window_count;	/* Count of windows in window_list  */
	unsigned short *window_list;    /* List of available windows	    */
	unsigned long long rcontext_block_count;/* available rcontext blocks*/
} ADAPTER_RESOURCES;

enum CLEAN_OPTION { LEAVE_INUSE, ALWAYS_KILL };

#define NTBL_VERSION  130  /* Release 1.3 of the interfaces */

#ifdef __cplusplus
extern "C"
{
#endif
extern int ntbl_version(void);
extern int ntbl_load_table(int version,char *adapter,unsigned short network_id,uid_t uid,pid_t pid,unsigned short job_key,char *job_desc,unsigned long long *window_memory,int table_size,NTBL **);
extern int ntbl_unload_window(int version,char *adapter,unsigned short job_key,unsigned short window_id);
extern int ntbl_clean_window(int version,char *adapter,enum CLEAN_OPTION,unsigned short window_id);
extern int ntbl_adapter_resources(int version,char *adapter,ADAPTER_RESOURCES *);
extern int ntbl_query_window(int version,char *adapter,unsigned short window_id, int *status);
extern int ntbl_status_adapter(int version,char *adapter,int *window_count,struct NTBL_STATUS **);
extern int ntbl_enable_window(int version,char *adapter,unsigned short window_id); 
extern int ntbl_disable_window(int version,char *adapter,unsigned short window_id); 
extern int ntbl_load_table_rdma(int version,char *adapter,unsigned short network_id,uid_t uid,pid_t pid,unsigned short job_key,char *job_desc,unsigned int bulk_transfer, unsigned int rcontext_blocks,int table_size,NTBL **);
extern int ntbl_rdma_jobs(int version,char *adapter,unsigned int *job_count, unsigned int **job_keys);
#ifdef __cplusplus
}
#endif
/* Structure for doing dynamic "load" call */
typedef struct {
	int (*ntbl_version)(void);
	int (*ntbl_load_table)(int,char *,unsigned short,uid_t,pid_t,unsigned short,char *,unsigned long long *,int,NTBL **);
	int (*ntbl_unload_window)(int,char*,unsigned short,unsigned short);
	int (*ntbl_clean_window)(int,char *,enum CLEAN_OPTION,unsigned short);
	int (*ntbl_adapter_resources)(int,char *,ADAPTER_RESOURCES *);
	int (*ntbl_query_window)(int,char *,unsigned short, int *);
	int (*ntbl_status_adapter)(int,char *,int*,struct NTBL_STATUS **);
	int (*ntbl_enable_window)(int,char *,unsigned short); 
	int (*ntbl_disable_window)(int,char *,unsigned short); 
	int (*ntbl_load_table_rdma)(int,char *,unsigned short,uid_t,pid_t,unsigned short,char *,unsigned int, unsigned int,int,NTBL **);
	int (*ntbl_rdma_jobs)(int,char *,unsigned int *,unsigned int **);
} NTBL_API;
#endif /* _NTBL_H */
