/*
 *      Copyright (c) 2004 by Sun Microsystems, Inc.
 *	All rights reserved.
 */

#ifndef	_LIBMTSK_DB_H
#define	_LIBMTSK_DB_H

#pragma ident	"@(#)libmtsk_db.h	1.1	04/07/26 SMI"

#include <proc_service.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mtsk_db_spawn_func_t {
    char *symbol_name;
    int   o_register_num;
} mtsk_db_spawn_func_t;

/*
 * Error codes returned by libmtsk routines.
 */
 
typedef enum {
    MTSK_DB_OK=0,            /* Everything is fine */
    MTSK_DB_VERSION_ERROR,   /* This libmtsk_db cannot support the a.out */
    MTSK_DB_NOT_OMP_THREAD,  /* This thread is not an openmp thread */
    MTSK_DB_NOT_IN_PARALLEL, /* Not in parallel region */
    MTSK_DB_ADDRESS_INVALID, /* If address provided by dbx is invalid */
    MTSK_DB_ERROR            /* Unknown error, like ps_read failed etc. */
} mtsk_db_errno_t;

/*
 * Called by the debugger once to initialize the debug support library.
 * Return handle, that should be used with subsequent queries.
 */

void *mtsk_db_init (struct ps_prochandle *);

/*
 * Called to destroy the handle, and clean up.
 */

void mtsk_db_fini (void *handle);

/*
 * This is called when dbx is about to resume the process, *or* 
 * immediately after dbx has stopped the process.  Either way it
 * indicates that the library needs to flush anyvcached values 
 * from the process that might change.
 */  

void mtsk_db_proc_flush(void *handle);
    
/*
 * Returns a list of items where each item includes the name of a 
 * function which can spawn a new parallel region, and which parameter 
 * holds the pointer to the mfunction.  This is used to support
 * stepping into a region in dbx.
 *
 * This function allocates an array of return type structure
 * using malloc. The count is set to the number of elements in the
 * array. It is the responsibility of the caller to free the returned
 * structure.
 */

struct mtsk_db_spawn_func_t *mtsk_db_spawn_funcs(int *count);
    
/*
 * This is to support the ability to print OMP thread
 * private variables in dbx.  A thread private variable
 * "x" will have a global variable "__tls_x" (or similar)
 * defined by the front end.  This will hold some kind
 * of pointer.  Dbx will need to used stabs info to
 * correlate "x" and "__tls_x", and then read the value
 * in "__tls_x" and use this value as 'base' when calling
 * libmtsk_db_thread_private_addr().  The address
 * in tp_var is the address of the instance of "x" for
 * the given thread.  Note: dbx will have no knowledge
 * of any mangling scheme used to go from the name "x"
 * to the name "__tls_x" (or whatever name it turns out
 * to be) The relationship between these two symbol names
 * will be recorded in the debug information.
 * 
 * For Fortran common blocks dbx will pass in the base
 * address of the common block, and the API will 
 * attempt to return the base address of the 
 * thread private chunk for the given tid. Individual
 * field offsets can be obtained by dbx from the stabs.
 * 
 * Return one of the error codes in libmtsk_db_errno_t
 * On success (MTSK_DB_OK), tp_var will contain the
 * address of the thread private data for this thread.
 */

mtsk_db_errno_t mtsk_db_thread_private_var_addr(void *handle,
                                                int tid,
                                                unsigned long base,
                                                unsigned long *tp_var);
    
/*
 * This function will be called only for the bottom
 * "slave" frame on a stack.  If the master and slave
 * frames are on the same thread, dbx will find the
 * master frame without help.
 *  
 * Dbx provides the thread id of a slave thread which
 * was assigned by the libmtask scheduler.
 * If the tid is not currently assigned to a parallel
 * region, then this function returns -1 as a return value.
 * Otherwise, it returns 0 and assigns a thread id, and
 * a frame pointer value to the reference parameters.
 * 
 * These point to the master frame/thread (or to slightly
 * newer frames).  Dbx will search backwards on the stack
 * from this point looking for the first frame of the function
 * that dbx knows is the "parent" for the mfunction where it
 * started.
 * 
 * Return one of the error codes in in libmtsk_db_errno_t
 * On success (MTSK_DB_OK), solaris_tid and the FP will
 * contain valid information
 */

mtsk_db_errno_t mtsk_db_slave_to_master(void *handle,
                                        int slave_tid,
                                        int *solaris_tid,
                                        unsigned long *FP);

#ifdef __cplusplus
}
#endif

#endif	/* _LIBMTSK_DB_H */
