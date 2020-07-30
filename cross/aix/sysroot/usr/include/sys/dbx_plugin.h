/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53J src/bos/usr/ccs/lib/libdbx/dbx_plugin.h 1.3                     */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2003,2006          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)05       1.3  src/bos/usr/ccs/lib/libdbx/dbx_plugin.h, libdbx, bos53J, j2006_23B0 6/1/06 10:08:25 */

#ifndef _DBX_PLUGIN_H_
#define _DBX_PLUGIN_H_

#include <sys/pthdebug.h>
#include <sys/inttypes.h>
#include <sys/types.h>
#include <sys/m_param.h>
#include <procinfo.h>

typedef uint64_t dbx_plugin_session_t;

/* DBX Plugin version control for future backward compat */
#define DBX_PLUGIN_VERSION_1 0xdb10

/* Error Return Codes for DBX Services */
#define DBX_PLUGIN_SUCCESS     0

#define DBX_PLUGIN_BAD_SESSION 10
#define DBX_PLUGIN_BAD_POINTER 11
#define DBX_PLUGIN_BAD_ARG     12
#define DBX_PLUGIN_BAD_ID      13

#define DBX_PLUGIN_UNAVAILABLE 30

/***************************************************************************
 * Session Information
 **************************************************************************/ 

typedef uint64_t dbx_plugin_session_flags_t;

#define DBX_PLUGIN_SESSION_64BIT 0x00000001
#define DBX_PLUGIN_SESSION_CORE  0x00000002

typedef int
(*dbx_plugin_session_service_t)(dbx_plugin_session_t session,
				dbx_plugin_session_flags_t *flagsp);

/***************************************************************************
 * Process Information
 **************************************************************************/ 

typedef struct procentry64 dbx_plugin_procinfo_t;

typedef int
(*dbx_plugin_process_service_t)(dbx_plugin_session_t session,
				dbx_plugin_procinfo_t *infop,
				size_t procinfo_size);

/***************************************************************************
 * File Descriptor Information
 ***************************************************************************/

typedef struct fdsinfox64 dbx_plugin_fdinfo_t;

typedef int
(*dbx_plugin_fds_service_t)(dbx_plugin_session_t session,
			    dbx_plugin_fdinfo_t *infop,
			    size_t fdinfo_size,
			    unsigned int *indexp,
			    unsigned int *countp);

/***************************************************************************
 * Loaded Module Information
 ***************************************************************************/

typedef struct dbx_plugin_modinfo
{
	char *filename;
	char *member;
	uint64_t text_start;
	uint64_t text_size;
	uint64_t data_start;
	uint64_t data_size;
	int fd;
}
dbx_plugin_modinfo_t;

typedef int
(*dbx_plugin_modules_service_t)(dbx_plugin_session_t session,
				dbx_plugin_modinfo_t *infop,
				size_t modinfo_size,
				unsigned int *indexp,
				unsigned int *countp);

/***************************************************************************
 * Memory Region Information
 ***************************************************************************/

#define DBX_PLUGIN_REGION_STACK 1 /* main thread stack */
#define DBX_PLUGIN_REGION_DATA  2 /* user data */
#define DBX_PLUGIN_REGION_SDATA 3 /* process private data */
#define DBX_PLUGIN_REGION_MMAP  4 /* memory mapped */
#define DBX_PLUGIN_REGION_SHM   5 /* shared memory */

typedef struct dbx_plugin_reginfo
{
	int type;
	uint64_t start;
	uint64_t size;
}
dbx_plugin_reginfo_t;

typedef int
(*dbx_plugin_regions_service_t)(dbx_plugin_session_t session,
				dbx_plugin_reginfo_t *infop,
				size_t reginfo_size,
				unsigned int *indexp,
				unsigned int *countp);

/***************************************************************************
 * Kernel Thread Information
 **************************************************************************/ 

typedef struct thrdentry64 dbx_plugin_thrdinfo_t;

typedef int
(*dbx_plugin_threads_service_t)(dbx_plugin_session_t session,
				dbx_plugin_thrdinfo_t *infop,
				size_t thrdinfo_size,
				tid64_t *indexp,
				unsigned int *countp);

/***************************************************************************
 * Pthread Information
 **************************************************************************/ 

#define DBX_PLUGIN_PTHREAD_CURRENT  ((pthdb_pthread_t)-1)

typedef struct dbx_plugin_pthinfo
{
	pthdb_pthread_t handle;
	tid64_t tid;
	pthdb_addr_t addr;
}
dbx_plugin_pthinfo_t;

typedef int
(*dbx_plugin_pthreads_service_t)(dbx_plugin_session_t session,
				 dbx_plugin_pthinfo_t *infop,
				 size_t pthinfo_size,
				 pthdb_pthread_t *indexp,
				 unsigned int *countp);

/***************************************************************************
 * Registers
 **************************************************************************/ 

#define DBX_PLUGIN_REG_GPRS 0x0001
#define DBX_PLUGIN_REG_SPRS 0x0002
#define DBX_PLUGIN_REG_FPRS 0x0004

typedef struct dbx_plugin_context
{
	unsigned long long  gpr[_NGPRS];
	unsigned long long  msr;
	unsigned long long  iar;
	unsigned long long  lr;
	unsigned long long  ctr;
	unsigned int        cr;
	unsigned int        xer;
	unsigned int        fpscr;
	unsigned int        fpscrx;
	unsigned long long  except[1];
	double              fpr[_NFPRS];
	char                fpeu;
	char                fpinfo;
	uchar               fpscr24_31;
	char		    pad;
	unsigned int        mq;
	int                 excp_type;
}
dbx_plugin_context_t;

#define DBX_PLUGIN_REG_EXT 0x0008

typedef struct dbx_plugin_extctx
{
	dbx_plugin_context_t	ctx;
	__extctx_t		extctx;
}
dbx_plugin_extctx_t;

typedef int
(*dbx_plugin_reg_service_t)(dbx_plugin_session_t session,
			    uint64_t reg_flags,
			    uint64_t id,
			    dbx_plugin_context_t *contextp,
			    size_t context_size);

/***************************************************************************
 * Memory Access
 ***************************************************************************/

typedef int
(*dbx_plugin_mem_service_t)(dbx_plugin_session_t session,
			    uint64_t addr,
			    void *buffer,
			    size_t len);

/***************************************************************************
 * Symbolic Infomation
 ***************************************************************************/

typedef struct dbx_plugin_syminfo
{
        char *name;
        uint64_t addr;
	uint mod;
}
dbx_plugin_syminfo_t;

typedef int
(*dbx_plugin_sym_service_t)(dbx_plugin_session_t session,
			    dbx_plugin_syminfo_t *symbols,
			    size_t syminfo_size,
			    unsigned int count);

/***************************************************************************
 * Output
 ***************************************************************************/

#define DBX_PLUGIN_PRINT_MODE_OUT 1
#define DBX_PLUGIN_PRINT_MODE_ERR 2

typedef int
(*dbx_plugin_print_service_t)(dbx_plugin_session_t session,
			      int print_mode,
			      char *message);

/***************************************************************************
 * Subcommand Aliases
 ***************************************************************************/

typedef int
(*dbx_plugin_alias_service_t)(dbx_plugin_session_t session,
			      char *alias,
			      char *expansion);

/***************************************************************************
 * DBX Services Structure
 ***************************************************************************/

typedef struct dbx_plugin_services
{
	dbx_plugin_session_service_t  session;
	dbx_plugin_process_service_t  process;
	dbx_plugin_fds_service_t      fds;
	dbx_plugin_modules_service_t  modules;
	dbx_plugin_regions_service_t  regions;
	dbx_plugin_threads_service_t  threads;
	dbx_plugin_pthreads_service_t pthreads;
	dbx_plugin_reg_service_t      get_thread_context;
	dbx_plugin_reg_service_t      set_thread_context;
	dbx_plugin_reg_service_t      get_pthread_context;
	dbx_plugin_reg_service_t      set_pthread_context;
	dbx_plugin_mem_service_t      read_memory;
	dbx_plugin_mem_service_t      write_memory;
	dbx_plugin_sym_service_t      locate_symbol;
	dbx_plugin_sym_service_t      what_function;
	dbx_plugin_print_service_t    print;
	dbx_plugin_alias_service_t    alias;
}
dbx_plugin_services_t;

/***************************************************************************
 * Event Notification Definitions and Structure
 ***************************************************************************/

#define DBX_PLUGIN_EVENT_RESTART      0
#define DBX_PLUGIN_EVENT_EXIT         1
#define DBX_PLUGIN_EVENT_TERM         2
#define DBX_PLUGIN_EVENT_LOAD         3
#define DBX_PLUGIN_EVENT_UNLOAD       4
#define DBX_PLUGIN_EVENT_BP           5
#define DBX_PLUGIN_EVENT_SIGNAL       6
#define DBX_PLUGIN_EVENT_SWTHRD       7

typedef union dbx_plugin_event_info
{
	/* DBX_PLUGIN_EVENT_RESTART */
	/* no info */

	/* DBX_PLUGIN_EVENT_EXIT */
	int exit_code;

	/* DBX_PLUGIN_EVENT_TERM */
	int term_signal;

	/* DBX_PLUGIN_EVENT_LOAD */
	/* DBX_PLUGIN_EVENT_UNLOAD */
	dbx_plugin_modinfo_t module;

	/* DBX_PLUGIN_EVENT_BP */
	/* no info */

	/* DBX_PLUGIN_EVENT_SIGNAL */
	int signal;

	/* DBX_PLUGIN_EVENT_SWTHRD */
	pthdb_pthread_t pthread;
}
dbx_plugin_event_info_t;

/* NOTE: The notification mechanism for events allocates memory to
 * hold the event information.  This memory will be valid only while
 * the exported plugin routine, dbx_plugin_session_event(), is active.
 * If a plugin wishes to access event information after
 * dbx_plugin_session_event() returns, it is responsible for copying
 * the information into another buffer.  This includes any pointers
 * to memory within the dbx_plugin_event_info_t structure (i.e.
 * the character strings for load/unload events).
 */

/***************************************************************************
 * Prototypes for Mandatory Exported Functions
 ***************************************************************************/

/*
 * The following functions must be exported by the plugin:
 *
 * 	dbx_plugin_version()
 * 	dbx_plugin_session_init()
 * 	dbx_plugin_session_destroy()
 * 	dbx_plugin_session_event()
 * 	dbx_plugin_session_command()
 */

/*
 * dbx_plugin_version()
 *
 * Plugin version check
 *
 * returns:
 *    version plugin conforms
 */
int
dbx_plugin_version(void);

/*
 * dbx_plugin_session_init()
 *
 * Assign session identifier
 * Receive DBX services
 * Perform plugin initialization
 *
 * returns:
 *    0:        success
 *    non-zero: failure
 */
int
dbx_plugin_session_init(dbx_plugin_session_t session,
			const dbx_plugin_services_t *servicesp);

/*
 * dbx_plugin_session_command()
 *
 * Perform plugin subcommands
 */
void
dbx_plugin_session_command(dbx_plugin_session_t session,
			   int argc,
			   char *const argv[]);

/*
 * dbx_plugin_session_event()
 *
 * Receive notification of debug events
 */
void
dbx_plugin_session_event(dbx_plugin_session_t session,
			 int event,
			 dbx_plugin_event_info_t *event_infop);

/*
 * dbx_plugin_session_destroy()
 *
 * Perform plugin cleanup
 */
void
dbx_plugin_session_destroy(dbx_plugin_session_t session);

#endif
