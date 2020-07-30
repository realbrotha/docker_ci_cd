/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2007,2009          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

#ifndef __CT_RCE_H
#define __CT_RCE_H

/* sccsid = "@(#)64   1.8   src/rsct/rce/lib/ct_rce.h, rceapi, rsct_rhay53, rhay531006a 5/29/09 09:34:32" */

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/time.h>
#include <rsct/ct.h>

/* RCE API version */    
#define RCE_VERSION    1

/* Return Codes */
typedef int rce_rc_t;

#define RCE_OK                  0    /* Success */
#define RCE_ELIB                1    /* Severe library or system error */
#define RCE_ENOMEM              2    /* out of memory */
#define RCE_EINITIALIZED        3    /* api is already initialized */
#define RCE_ECONNFAILED         4    /* failed to open a session with the RMC */
#define RCE_ENOSESSION          5    /* no existing session with the RCE */
#define RCE_ELOSTRMCSESSION     6    /* lost RMC session */
#define RCE_EINVALIDRCEVERSION  7    /* invalid RCE version */
#define RCE_EINVALIDHANDLE      8    /* invalid handle */
#define RCE_EINVALIDOPTION      9    /* invalid option */
#define RCE_EINVALIDNODENAME   10    /* invalid node name */
#define RCE_EINVALIDCOMMAND    11    /* invalid command */  
#define RCE_EINVALIDSIGNAL     12    /* invalid signal */
#define RCE_EWAITED            13    /* the command is already waited */
#define RCE_ENOACTIVECMDS      14    /* all commands have been waited on */
#define RCE_EWAITTIMEDOUT      15    /* the wait has timed out */
#define RCE_EPENDING           16    /* some commands are not terminated yet */ 
#define RCE_EBUSYHANDLE        17    /* the handle is being waited on */
#define RCE_ECANCELLED         18    /* the command is in the cancelled state */
#define RCE_EFAILED            19    /* the command is in the failed state */
#define RCE_ETIMEDOUT          20    /* the command is in the timed out state */
#define RCE_ETERMINATED        21    /* the command has terminated */
#define RCE_EUNKNOWN           22    /* the command is in an unknown state */

/* Initialize options */
typedef struct
{
    ct_int32_t connect_timeout;    /* 0 = default (indefinite wait) */
    ct_int32_t reconnect_delay;    /* 0 = default (no delay) */
} rce_initialize_opts_t;

/* Finalize options */
typedef enum
{
    /* mutually exclusive options */
    RCE_FINALIZE_OPTS_WHEN_ALL_TERMINATED = 0,  /* (default) wait till all current commands are completed */
    RCE_FINALIZE_OPTS_NOWAIT              = 1,  /* no check or no wait for the current commands */
    RCE_FINALIZE_OPTS_SIGTERM             = 2,  /* send SIGTERM to the current commands */
    RCE_FINALIZE_OPTS_SIGKILL             = 3,  /* send SIGKILL */
    RCE_FINALIZE_OPTS_SIGQUIT             = 4   /* send SIGQUIT */
} rce_finalize_opts_t;


/* Command options */
/* The options can be specified as ORing of each category, except the timeout action */
/* lower-half == signal specification, upper-half = more options */
typedef unsigned rce_cmd_opts_t;

#define RCE_CMD_OPTS_NONE                       0x0000
#define RCE_CMD_OPTS_CSTDERR                    0x0100
#define RCE_CMD_OPTS_CSTDOUT                    0x0200
#define RCE_CMD_OPTS_RUN_LOGIN_USER_PROFILE     0x0400
#define RCE_CMD_OPTS_DOWN_ON_FORK_FAILURE       0x0800

/* The following options must be mutually exclusive*/
#define RCE_CMD_OPTS_TIMEOUT_ACTION_SIGNAL_MASK 0x00ff
#define RCE_CMD_OPTS_TIMEOUT_ACTION_SIGTERM     0x0002
#define RCE_CMD_OPTS_TIMEOUT_ACTION_SIGKILL     0x0003
#define RCE_CMD_OPTS_TIMEOUT_ACTION_SIGQUIT     0x0004


/* Command Status */
typedef enum
{
    RCE_CMD_STATUS_UNKNOWN    = 0,    /* unknown */
    RCE_CMD_STATUS_SUBMITTED  = 1,    /* submitted */
    RCE_CMD_STATUS_RUNNING    = 2,    /* running */
    RCE_CMD_STATUS_COMPLETED  = 3,    /* completed */ 
    RCE_CMD_STATUS_FAILED     = 4,    /* failed before executed */
    RCE_CMD_STATUS_TIMEDOUT   = 5,    /* timed out */
    RCE_CMD_STATUS_CANCELLED  = 6     /* cancelled */
} rce_cmd_status_t;


/* Command Handle */
typedef ct_resource_handle_t    rce_cmd_handle_t;

/* Stdout and Stderr */
typedef char *rce_cmd_stdout_t;
typedef char *rce_cmd_stderr_t;

/* Subroutines */

/* convert between cmd_handle and string */
const char *rce_cmd_handle_to_string(const rce_cmd_handle_t *hndl, ct_char_t *strout);
void rce_string_to_cmd_handle(const char *strin, rce_cmd_handle_t *cmd_handle);

/* rce_initialize()
 * rce_version -  this must be specified as RCE_VERSION to pass the header file version.
 * opts  - pointer to the opts data structure, or NULL (default)
 * For example,
 *         rce_initialize(RCE_VERSION, NULL);
 */
rce_rc_t rce_initialize(int rce_version,
                        const rce_initialize_opts_t *opts);

rce_rc_t rce_finalize(rce_finalize_opts_t options,
                      const struct timeval *wait_timeout);

rce_rc_t rce_cmd_submit(const char *nodename,
                        const char *command,
                        const char **arguments,
                        char **envp,
                        const char *username,
                        rce_cmd_opts_t cmd_options,
                        const struct timeval *cmd_run_timeout,
                        rce_cmd_handle_t *out_cmd_handle);

rce_rc_t rce_cmd_get_status(rce_cmd_handle_t cmd_handle, 
                            rce_cmd_status_t *cmd_status, 
                            int *cmd_exit_code);

rce_rc_t rce_cmd_get_outputs(rce_cmd_handle_t cmd_handle, 
                             rce_cmd_stdout_t *p_cmd_stdout, 
                             rce_cmd_stderr_t *p_cmd_stderr);

rce_rc_t rce_cmd_wait_one(rce_cmd_handle_t cmd_handle,
                          const struct timeval *wait_timeout);

rce_rc_t rce_cmd_wait_any(const struct timeval *wait_timeout,
                          rce_cmd_handle_t *p_cmd_handle);

rce_rc_t rce_cmd_cancel(rce_cmd_handle_t cmd_handle,
                        int signal_num);

rce_rc_t rce_cmd_release(rce_cmd_handle_t cmd_handle,
                         int force);

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif
