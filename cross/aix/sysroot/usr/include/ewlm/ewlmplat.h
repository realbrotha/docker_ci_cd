/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/kernel/ewlm/ewlmplat.h 1.10                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2003               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)95       1.10  src/bos/kernel/ewlm/ewlmplat.h, sysewlm, bos53L, l2007_03C2 1/18/07 15:33:16 */
/*
 *   COMPONENT_NAME: SYSEWLM
 *
 *   DESCRIPTION:  EWLM common code native service definitions
 *
 *   ORIGINS: 27
 */
/* ------------------------------------------------------------------------- */
/* ewlmplat.h - EWLM Platform Services API Declarations header file          */
/*                                                                           */
/* This header file declares the platform service APIs.                      */
/* -------------------------------------------------------------------------
 * Change Activity:
 * Reason      Date      Origin               Description
 * -------  ----------  -----------     ------------------------------------
 * DCR 011  2003-08-28  John Arwe       Pass policy into ewlm_xxx_policy APIs
 *                                      as unencodedbytestream
 * DCR 002  2003-08-31  John Arwe       Add AIID to parent identity, 4 records
 * DCR 011  2003-09-01  John Arwe       Allow thread-level idle and other
 *                                      samples rather than process-level only
 * DCR 011  2003-09-01  John Arwe       Removed process name from query
 *                                      server configuration.  Seems to have
 *                                      been copied in error from get_appldata
 * DCR 011  2003-09-02  John Arwe       Rename files to be within 8-char limit
 * DCR xxx  2003-09-17  John Arwe       Fix typo in invalidation record name
 * DCR xxx  2003-09-21  John Arwe       Distinguish between required and
 *                                      optional return codes for each API
 * DCR xxx  2003-09-23  Geoff Lubold    Change XXX_t types to ewlm_XXX_t
 *                                      types
 * DCR xxx  2003-09-29  Geoff Lubold    AEIID changed to AEID
 * DCR xxx  2003-09-29  Geoff Lubold    Partially Instrumented #define sizeof
 *                                      fixed
 * DCR 018  2003-09-29  Geoff Lubold    Instrumented application termination
 *                                      handling - AIID termination records
 *          2003-10-10  Geoff Lubold    Moved EWLM_ARM_STATUS_ABANDONED from
 *                                      ewlmplos.h to ewlmplat.h
 *          2003-10-25  Geoff Lubold    get_completion cancel wait comment
 *                                      text changed.
 * F2691    2003-10-28  Geoff Lubold    Includes changed from " " to < >
 * DCR 010  2003-10-31  Geoff Lubold    Removed local server ID from
 *                                      ewlm_connect_input_t
 * DCR 030  2003-11-23  John Arwe       Fix doc:
 *                                      - blocked time always in total mode
 *                                      - remove DE references and open
 *                                        questions
 *                                      - correct start time description
 *                                        to allow for non-zero queue time
 *                                      - change EWLM_SUPPORT_NOT_ENABLED from
 *                                        optional to required on all APIs
 *                                      - final policy management API rc doc
 * DCR 030  2003-11-23  John Arwe       Document new rc for get_activedata
 *                                        continue requests with invalid
 *                                        cursor
 * DCR 030  2003-11-26  John Arwe       Document new bit on ewlm_query
 *                                        ResourceMetricsCollected
 *                                      Document blocked time overflow bits
 *                                      Remove extraneous record mappings
 *                                      Reorder performance-sensitive record
 *                                        mappings to minimize wasted space
 *                                        (averaged across all platforms)
 *                                      Rename enforcement layer bit
 *                                      Rename EWLM 1st release bit
 *                                      Reword comment to address legal issue
 * D3094   2003-12-08   Geoff Lubold    Addition of C++ support
 * D3127   2003-12-09   Geoff Lubold    moved hopcount and classification ID
 *                                      to arm4ewlm.h. Also included
 *                                      arm4ewlm.h
 * D3395   2004-01-09   Geoff Lubold    Removal of *VERSIONLATEST
 * DCR 021 2004-01-08   Geoff Lubold    Created new internal error code range
 *                                      & changed comment wording for error -222
 * DCR 034  2004-01-07  John Arwe       Define bit to detect a system time
 *                                        change occurred which the OS
 *                                        believes might impact reported times.
 *                                        Adds version 002 of get_activedata
 *                                        end of buffer record.
 * DCR 033  2004-01-07  John Arwe       Define version 002 of query resource
 *                                        metrics to allow OS to return
 *                                        its sample conversion factor.
 * D4040    2004-02-10  G. Lubold       Copyright updates
 * D4380    2004-02-25  G. Lubold       Copyright updates
 * F12760   2004-11-01  G. Lubold       QueryServerConfig output buffer version 2,
 *                                      pass samplingTimer value on ewlmConnect
 *                                      call from Java
 * F15321   2005-01-13  G. Lubold       new define for release level for
 *                                      ewlm_query
 * F15541   2005-01-27  G. Lubold       correct version for platforms at higher
 *                                      level than EWLM
 * F16156   2005-03-02  G. Lubold               Added Solaris and HP/UX return code ranges
 * F16861   2005-03-29  G. Lubold       DCR 19- microsecond reporting and versioning
 *                                      changes
 * F28712   2006-06-07  G  Readler      Local CPU resource management support
 *          2006-06-19  K. Ng           z/OS End-to-End support
 *          2006-07-13  G.  Bosch       Added MQ support
 *          2006-07-23  D.  Manners     Additional MQ support
 * F29843   2006-07-24  G  Readler      Put into cmvc
 *          2006-08-01  D.  Manners     Corrections to 2006-07-23 adds
 * F30117   2006-08-21  G Readler       change EWLM_QUERY_HYPERVISOR_VMWARE back to 4
 * DCR 015  2006-09-08  G Readler       New types for async get_completions
 *                                      and get_activedata output records.
 *                                      Additional 16Bit flagsv3 fields for
 *                                      in-flight and completion records.
 * F30592   2006-09-19  G Readler       management_id changed to 64 bit value.
 * F32148   2006-11-16  G Readler       DCR24 scaled cpu clock  
 * ------------------------------------------------------------------------- */

#ifndef _H_EWLM_EWLMPLAT
#define _H_EWLM_EWLMPLAT

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Pending issues - may or may not be implemented
 *
 * Guidelines for files like this which are intended to be the same across all
 * platforms:
 * - Not all platforms support int_64 natively, so an ewlm_int64 type is defined
 *   in ewlmplatos.h, and each platform completes the definition there.
 * - Not all C compilers support the double-slash end of line comments, so stick
 *   to the explicit open/close style comments.
 * - Use char * instead of void * for better OS/400 performance.
 * - REQUIREMENT: Code to use C89 (1989 C standard) constructs only!  Not all
 *   supported platforms have compilers which support the 1999 C standard yet.
 * - REQUIREMENT: Do not define flag constants as 0x80000000.  Code exists to
 *   verify at compile time that the EWLM agent's Java flags are the same as
 *   this file's C declarations.  The javah process which generates the JNI
 *   constants generates numeric constant values for 0x8000000 as a signed
 *   32-bit integer which the Windows C compiler flags as being out of range.
 */


/* -------------------------------------------------------------------------
 * ---------------------------  DOCUMENTATION  -----------------------------
 * -------------------------------------------------------------------------
 * Finding things:
 * - Function signatures: search for ewlm_status_t
 * - Inputs or outputs for a particular API: apiname_input/output, e.g.
 *   for ewlm_connect search for ewlm_connect_input and ewlm_connect_output
 * - Output records from get_activedata and get_completions: search on
 *   apiname_
 *
--- API Signature ---
input_buffer
    Storage allocated by EWLM agent for API inputs.  Required for all APIs.

input__buffer_size
    Size of the input buffer (in bytes) allocated by the API caller.

output_buffer
    Storage allocated by EWLM agent for API outputs.  Required for all APIs.

output_buffer_size
    Size of the output buffer (in bytes) allocated by the API caller.

--- Common API fields ---
version
    In order to support migration goals, virtually every structure mapping
    has a version.  Version numbers for each structure are independent.  A
    given version number + structure combination implicitly determines the set
    of data and offsets used to map the structure.

    Version numbers should be incremented for each structure update.  Such
    updates must be compatible (no removal of existing field names, changes
    to offsets of existing fields, changes to values of existing constants,
    changes to lengths of existing fields).

request_type
    For APIs which support multiple functions, this parameter determines which
    function the caller wishes performed.

connect_handle
    A platform-specific token whose value is opaque to the caller.  It is an
    output from ewlm_connect(), and input to all other services.  It's function
    is to restrict the usage of ewlm_ APIs to the set of user(s) authorized
    by ewlm_connect's platform-specific checks.

sizeneeded
    The size in bytes of the storage area needed to hold the API's output.
    APIs with versioned output buffers use this field to return the size of the
    output area needed to hold the API's output.  It is filled in with the OS's
    storage size requirement whenever the API return code indicates that the
    output buffer size is too small, but large enough to contain version 1's
    output buffer mapping.

    A valid migration scenario is one where a caller compiled to use version 1
    input/output buffer mappings, but the caller's code is run on an OS which
    has been compiled with version 2 input/output mappings.  This field allows
    the caller to find out the proper size buffers to pass in (version 1 input,
    version 2 output).


--- OS identity - processes and fully instrumented ARM transactions ---
pid
    Opaque identifier owned by the ARM/OS layer which uniquely identifies a
    unit of work ("process") to the OS.  This is a platform-dependent value,
    which might be called by different native terms on each platform (e.g. a
    process ID on Unix platforms, a Job ID on OS/400, an ASID/STOKEN/EncToken
    on z/OS).

--- Reporting aggregation data - all work types ---
reporting_id
    Output ID from EWLM classification which maps to a transaction class (ARM
    transactions), process class (processes), or tier (processes controlled by
    an entitlement policy).  Its value is implicitly scoped by the active
    policies.

period_number
    Period number within the service class that the work is being reported in.
    Always 1 (one) in EWLM 1.0.

--- Reporting aggregation data - ARM work only ---
hop_count
    Value which influences reporting aggregation.  This is determined during
    arm_start_transaction() based upon examination of the parent correlator
    if one exists, and stored in the owning transaction's correlator.

--- ARM transaction identity ---
appl_inst_id
        This represents the application instance in a specific process which
        executed the transaction.  The AIID is created by the ARM implementation
        and needs to be unique relative to all active application instances
        currently running on the system.  It does not need to be the same value
        that is returned as a handle to the application (though it can be, if it
        fits in 64 bits).  The first time that WLM encounters a particular AIID
        value it will invoke ewlm_get_appldata() to get the definition of  the
        application instance.

---    Parent ARM transaction identity ---
parent_applenv_id
    Proxy for the application environment (application name and application
    group name) of the parent transaction.  It comes from the transaction's
    parent correlator.  If the transaction has no parent correlator, the value
    should be 0.  The ID is assigned by the ARM component which constructed
    the parent correlator.  Since the ID is not guaranteed to be unique within
    the management domain, the EWLM agent must resolve it in combination with
    the transaction's parent server identity.

parent_applinst_id
    Application instance of the parent transaction.
    It comes from the transaction's
    parent correlator.  If the transaction has no parent correlator, the value
    should be 0.  The ID is assigned by the ARM component which constructed
    the parent correlator.  Since the ID is not guaranteed to be unique within
    the management domain, the EWLM agent must resolve it in combination with
    the transaction's parent server identity.

parent_sys_id
        The server ID that was in the transaction's parent correlator.  If the
        transaction had no parent correlator or the parent correlator was not in
        EWLM's format, this field is zero.

--- Generic completion transaction/process data ---
response_time
    Elapsed time in milliseconds that the work was associated with the OS or
    ARM instance; sum of queue time and active time.  Since response time is
    only reported once per completed transaction/process, its value is always
    in total mode.

    The minimum value is 0 millisecond.  The maximum value is 2147483647
    (value of the maximum signed integer) which represents over 24 days of
    time.  If the platform calculates a response time greater than the max
    value, it must turn on EWLM_GET_COMPLETIONS_RESPONSE_TIME_OVERFLOW in
    the corresponding get_completions record and set the reported value to the
    max value (this allows OS's to track
    times using precisions different from EWLM without adding new code).
    The remainder ,micro seconds, should be reported in the associated micro
    second field.

    Queue_time = max( Start time - arrival time , 0 )
    Active_time = Stop time - start time

    - Arrival time
        - ARM transactions
            A transaction's arrival time is
            set via the optional arrival time subbuffer passed to
            arm_start_transaction().  If no such subbuffer is passed,
            the arrival time defaults to the time that arm_start_transaction()
            is invoked and the resulting queue time is zero.
        - Processes
            A process's arrival time is the time at which the OS accepted
            the work for later execution.  If process-oriented work is not
            queued prior to execution, arrival time is equal to start time.

            Arrival time is reset to time of classification if the process is
            reclassified after it is initially queued or after it begins
            execution.  If the EWLM agent has been made aware of the work via
            an in-flight record before reclassification occurs, the revised
            arrival time takes effect *after* generating an artificial
            completion record covering the process's resource usage prior to
            reclassification.
    - Start time
        - ARM transactions
            The transaction's start time is the time that arm_start_transaction()
            is invoked.
        - Processes
            The process's start time is the later of two events: process
            creation and latest reclassification.  Processes may be reclassified
            in response to changes in their classification attributes (change
            of user ID/name, group ID) or in response to policy activation.

            Start time is reset to time of classification if the process is
            reclassified after it begins
            execution.  If the EWLM agent has been made aware of the work via
            an in-flight record before reclassification occurs, the revised
            start time takes effect *after* generating an artificial
            completion record covering the process's resource usage prior to
            reclassification.

    - Stop time
        - ARM transactions
            The stop time is set when arm_stop_transaction() is invoked.

        - Processes
            Stop time is the time at which the process terminates.

EWLM_GET_COMPLETIONS_RESPONSE_TIME_OVERFLOW
    Response time calculated for the work described by this record was greater
    than the max value allowed by EWLM (see response_time description) so its
    data needs special handling.

EWLM_GET_COMPLETIONS_ARTIFICIAL_COMPLETION
    The work described by this record has not actually ended, but a change
    to its management (e.g. a change in process service class triggered by a
    change in userid) requires that its historical times and resource usage
    be recorded here for proper reporting bookkeeping.  If the platform is
    reporting metrics data in total mode, the EWLM agent will use the values
    in this record as bases going forward.

--- Generic ARM transaction completion data ---
completion_status
    - ARM transactions
        Value describing the final disposition of the transaction, from
        arm_stop_transaction.

--- Generic process/transaction data ---
queue_time
    Elapsed time in milliseconds between the transaction's arrival time
    and its start time (see the response_time explanation for definitions
    of these values).  Always reported in total mode.

    If the platform calculates a queue time greater
    than the max allowed (same value as for response times), it must set
    EWLM_GET_ACTIVEDATA_QUEUE_TIME_OVERFLOW (get_activedata record) or
    EWLM_GET_COMPLETIONS_QUEUE_TIME_OVERFLOW (get_completions record) in
    each record generated for the transaction and return the max value as
    the queue time.

EWLM_GET_ACTIVEDATA_QUEUE_TIME_OVERFLOW and
EWLM_GET_COMPLETIONS_QUEUE_TIME_OVERFLOW
    Calculated queue time exceeded the maximum value which fits in a signed
    integer (see response_time for exact value).

--- Generic ARM transaction data ---
blocked_time
    - ARM transactions
        Elapsed time in milliseconds that the transaction was in a blocked
        state (one or more arm_block()s was outstanding).
        Always in total mode.  The EWLM agent could not support delta mode
        reporting of this field without maintaining a per-transaction base
        value, or having the platform report the value of blocked time as
        reported at the last get_activedata before completion as well as
        the total at completion,
        which is believed to result in too much overhead.

EWLM_GET_ACTIVEDATA_BLOCKED_TIME_OVERFLOW and
EWLM_GET_COMPLETIONS_BLOCKED_TIME_OVERFLOW
    Calculated blocked time exceeded the maximum value which fits in a signed
    integer (see response_time for exact value).

EWLM_GET_ACTIVEDATA_STALE_REPORTING_ID and
EWLM_GET_COMPLETIONS_STALE_REPORTING_ID
    If on, this bit indicates that the work described by the record was
    classified using a policy that is no longer active.  Hence its
    reporting_id may be invalid, and its data requires special handling.


--- Generic in-flight data ---
classify_time
    Time when the work (transaction or process) was last EWLM-classified.
    (see the response_time explanation for related information).
    - ARM transactions
        Transaction start time (transactions are not reported prior to
        beginning execution), as defined under response_time.
    - Processes
        Process start time, as defined under response_time.

--- Metrics ---
Metrics in general may be reported by each platform in either total mode or
delta mode.  EWLM knows which mode to expect, by field, based on the output
of ewlm_query Resource Metrics Collected which is invoked during EWLM agent
initialization.

times_sampled
    This count is logically incremented each time that a call to
    ewlm_collect_samples() results in at least one state sample being collected
    for the process.  Unlike the state samples themselves, if the OS separates
    the concepts of thread and process then this should be incremented once
    per process.  Thus for any given interval, dividing the total of all state
    samples by times_sampled would provide a good approximation of the
    average process multithreading level.

    times_sampled should be the
    same as the number of calls to ewlm_collect_samples() during which the
    entity being sampled (e.g. process) existed.  The preceding text is the
    logical view that EWLM expects.  Each platform is free to implement the
    actual state sampling in any way which preserves the appearance of
    ewlm_collect_samples() acting as the trigger for state sampling.

cpu_time
    Microseconds of CPU time consumed by the work being measured.

    More exact platform-dependent definitions of what is returned for each
    state sample type are located in ewlmplatos.h.

    cpu_using
        This count is incremented once for each thread found to be dispatched
        (running on a CPU) during state sampling.  The state sampler also
        attributes a single cpu_using sample to whichever thread the OS would
        dispatch if a work search were done at the instant the state sampler
        runs, in place of the thread under which the state sampler is running,
        to preserve the illusion that the state sampler does not exist.
        This prevents a built-in sampling bias where the thread running the
        state sampler code would always be observed to be using a CPU.

    cpu_delay
        This count is incremented once for each thread found to be ready for
        dispatch (waiting for a CPU).  One CPU delay sample per call to
        ewlm_collect_samples() is converted to a CPU using sample, as
        described under cpu_using.

    page_delay
        This count is incremented once for each thread found to be waiting for
        resolution of paging I/O due to lack of real memory.

    io_delay
        This count is incremented once for each thread found to be waiting for
        a user-initiated I/O request to complete.


    idle
        This count is incremented once for each process (or thread, depending
        upon the platform) found to
        have no work at all to do, and the OS knows that at least one thread
        in the process is in a wait (e.g. timer wait) that indicates it is
        definitely waiting to receive work to do.

    other
        This count is incremented once for each process (or thread, depending
        upon the platform) found to
        have no work at all to do, but the OS is unaware that the process is
        definitely waiting to receive work to do.

    scaled_cpu_time (added by DCR24)
        Scaled microseconds of CPU time consumed by the work being measured.   
        
VERSIONING - PLEASE NOTE
Problem - In EWLM release 1 each structure's version 1 size was set to the
sizeof(struct). The sizeof operator according to the ISO/IEC 9899:1999 states
"When (sizeof is) applied to an operand that has structure or union type,
the result is the total number of bytes in such an object, including internal
and trailing padding." This causes EWLM problems when structs are modified to
include version 2 fields, since the assumption was that sizeof() did not
include trailing padding. The size of the version 1 structure in the version
2 header file can be smaller if the version 2 fields fit within the trailing
padding added by the compiler in version 1.

Solution - Get rid of calculations and code constant based on platform for all
but latest version. This would move constant definitions to ewlmplos.h.
*/
/* DCR 19
 * queue_time_microsec
 * blocked_time_microsec
 * response_time_microsec
 *
 * If a platform can measure time more accurately than milliseconds, it would set
 * version of the output record to 2 and put the microsecond part of these times in
 * the new fields. If the accuracy of the platform's time measurement is somewhere
 * between milliseconds and microseconds, the platform code needs convert its time
 * stamp to microsecond.
 *
 * The other mapping EWLMPLAT.H that will be impacted:
 *
 * ewlm_get_completions_process_output
 * version 2 mapping
 * add queue_time_microsec
 * add response_time microsec
 *
 * ewlm_get_activedata_inflight_process_output
 * add version 2 mapping
 * add queue_time_microsec
 *
 * ewlm_get_activedata_inflight_ARM_partially_instrumented_output
 * add version 2 mapping
 * add queue_time_microsec
 * add blocked_time_microsec
*/

/* --------------------------------------------------------------------------*/
/* --------------------- contents from ewlmplos.h ---------------------------*/
/* ------------------------------------------------------------------------- */
typedef long long ewlm_process_id_t;   /* process ID, various APIs */
typedef long long ewlm_get_activedata_cursor_t; /* restart cursor,
                                                         ewlm_get_activedata */
typedef long long ewlm_connect_handle_t;         /* All ewlm_ APIs */
#define EWLM_INVALID_CONNECT_HANDLE \
((ewlm_connect_handle_t)(-1LL))

typedef long long           ewlm_cpu_time_t;
typedef int                 ewlm_num_samples_t;
typedef int                 ewlm_state_sample_t; /* all state samples 
                                    must be the same size */

#define EWLM_BIG_ENDIAN  1 /* define if big endian */

#define EWLM_MAX(a,b)	(a > b ? a : b)

typedef char                 ewlm_char_t;
typedef signed char          ewlm_int8_t;
typedef unsigned char        ewlm_uint8_t;
typedef signed short         ewlm_int16_t;
typedef unsigned short       ewlm_uint16_t;
typedef signed int           ewlm_int32_t;
typedef unsigned int         ewlm_uint32_t;
typedef signed long long     ewlm_int64_t;
typedef unsigned long long   ewlm_uint64_t;
typedef long long            ewlmpol_int_t; /* Used by ewlmpols.h. */

/*
 * previous version constant defintion
 */
#define EWLM_GET_ACTIVEDATA_INFLIGHT_PROCESSES_V001SIZE         (72)
#define EWLM_GET_ACTIVEDATA_INFLIGHT_PARTIALINSTARM_V001SIZE    (64)
#define EWLM_GET_COMPLETIONS_PROCESSES_V001SIZE                 (72)
#define EWLM_GET_COMPLETIONS_PARTIALINSTARM_V001SIZE            (56)

/* --------------------------------------------------------------------------*/
/* ------------------------ content of ewlmrcs.h ----------------------------*/
/* ------------------------------------------------------------------------- */
/*
 * Change Activity:
 * Reason      Date      Origin               Description
 * -------  ----------  -----------     ------------------------------------
 *          2003-09-29  Geoff Lubold    Return Codes updated to new structure
 *          2003-09-29  Geoff Lubold    ARM Standard Reserved codes added
 *          2003-10-03  Geoff Lubold    Removal and addition of common error
 *                                      EWLM services (policy changes).
 *          2003-10-29  Geoff Lubold    Addition of common error EWLM
 *                                      services (policy changes).
 *          2003-10-31  Geoff Lubold    Merged common EWLM Java and JNI codes
 * D2944    2003-11-18  Geoff Lubold    Common C ARM API's moved to arm4ewlm.h
 * D2989    2003-11-23  John Arwe       Renamed -204 symbol to get rid of DE
 *                                      API name reference
 *                                      from: _TRANDATA_ALREADY_WAITER
 *                                      to:   _GETCOMPLETIONS_SECOND_WAITER
 * ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* -----------------------non-error return codes --------------------------- */
/* ------------------------------------------------------------------------- */

/*
 * Return codes 0 through 999 are reserved for common non-error
 * EWLM services use.
 */
#define EWLM_IRC_EWLM_RANGE_START        (0)

#define EWLM_SUCCESS                     (0)/* Data was returned in the buffer
                                               provided, and no more data
                                               can be returned at this time. */
#define EWLM_MORE_DATA                   (1)/* Data was returned in the buffer
                                               provided, and more data can be
                                               returned at this time.  The
                                               cursor parameter has been
                                               updated to contain a
                                               platform-dependent restart
                                               point, and this value must be
                                               passed on a CONTINUE request in
                                               order to obtain the next window
                                               of data. */

#define EWLM_IRC_EWLM_RANGE_END          (999)

/*
 * Return codes 1000 through 1999 are reserved for common non-error
 * ARM services use.
 */
#define EWLM_IRC_ARM_RANGE_START           (1000)
#define EWLM_IRC_ARM_RANGE_END             (1999)

/*
 * Return codes 2000 through 2999 are reserved for AIX non-error use.
 */
#define EWLM_IRC_AIX_RANGE_START           (2000)
#define EWLM_IRC_AIX_RANGE_END             (2999)

/*
 * Return codes 3000 through 3999 are reserved for OS/400 non-error use.
 */
#define EWLM_IRC_OS_400_RANGE_START        (3000)
#define EWLM_IRC_OS_400_RANGE_END          (3999)

/*
 * Return codes 4000 through 4999 are reserved for z/OS non-error use.
 */
#define EWLM_IRC_Z_OS_RANGE_START          (4000)
#define EWLM_IRC_Z_OS_RANGE_END            (4999)

/*
 * Return codes 5000 through 5999 are reserved for common EWLM Java and JNI
 * services non-error use.
 */
#define EWLM_IRC_EWLM_JAVA_RANGE_START     (5000)
#define EWLM_IRC_EWLM_JAVA_RANGE_END       (5999)

/*
 * Return codes 6000 through 6999 are reserved for Windows non-error use.
 */
#define EWLM_IRC_WINDOWS_RANGE_START       (6000)
#define EWLM_IRC_WINDOWS_RANGE_END         (6999)

/*
 * Return codes 7000 through 7999 are reserved for Linux non-error use.
 */
#define EWLM_IRC_LINUX_RANGE_START         (7000)
#define EWLM_IRC_LINUX_RANGE_END           (7999)

/*
 * Return codes 8000 through 8999 are reserved for Solaris non-error use.
 */
#define EWLM_IRC_SOLARIS_RANGE_START       (8000)
#define EWLM_IRC_SOLARIS_RANGE_END         (8999)

/*
 * Return codes 9000 through 9999 are reserved for HP/UX non-error use.
 */
#define EWLM_IRC_HP_UX_RANGE_START         (9000)
#define EWLM_IRC_HP_UX_RANGE_END           (9999)


/*
 * Return codes 15000 through 16999 are reserved for common ARM Java and JNI
 * services non-error use.
 */
#define EWLM_IRC_ARM_JAVA_RANGE_START      (15000)
#define EWLM_IRC_ARM_JAVA_RANGE_END        (16999)

#define EWLM_IRC_JAVA_RANGE_START          (15000)
#define EWLM_IRC_JAVA_RANGE_END            (16999)

/*
 * Return codes 20000 through 20999 are reserved for ARM Standard
 * services use.
 */
#define ARM_IRC_RESERVED_START             (20000)
#define ARM_IRC_RESERVED_END               (20999)


/* ------------------------------------------------------------------------- */
/* -------------------------error return codes ----------------------------- */
/* ------------------------------------------------------------------------- */

/*
 * Return codes -1 through -999 are reserved for common EWLM services use.
 */
#define EWLM_RC_EWLM_RANGE_START            (-1)
#define EWLM_RC_EWLM_RANGE_END            (-999)

#define EWLM_RC_POLICY_MAX                (-100)
#define EWLM_NO_CONNECTION                (-100)/* The EWLM agent was not
                                                   connected to the platform
                                                   component. */
#define EWLM_BAD_CONNECT_HANDLE           (-101)/* The input connect handle was
                                                   not recognized as valid by
                                                   the platform component.
                                                   Either the value is invalid,
                                                   or the value is valid but
                                                   the connect handle is not
                                                   associated with the EWLM
                                                   agent this latter check is
                                                   not implemented by all
                                                   platforms, i.e. Linux). */
#define EWLM_BAD_POLICY                   (-102)
#define EWLM_NO_PREPARED_POLICY           (-103)
#define EWLM_WRONG_POLICY                 (-104)
#define EWLM_BAD_POLICY_ADDR              (-105)
#define EWLM_BAD_POLICY_HEADER            (-106)
#define EWLM_BAD_POLICY_SIZE              (-107)

#define EWLM_BAD_POLICY_TRIPLET_POLICY    (-108)
#define EWLM_BAD_POLICY_TRIPLET_WORKLOAD  (-109)
#define EWLM_BAD_POLICY_TRIPLET_SCLS      (-110)
#define EWLM_BAD_POLICY_TRIPLET_GOAL      (-111)
#define EWLM_BAD_POLICY_TRIPLET_APPLENV1  (-112)
#define EWLM_BAD_POLICY_TRIPLET_APPLENV2  (-113)
#define EWLM_BAD_POLICY_TRIPLET_APPLENV3  (-114)
#define EWLM_BAD_POLICY_TRIPLET_TCCLS     (-115)
#define EWLM_BAD_POLICY_TRIPLET_TCFILT    (-116)
#define EWLM_BAD_POLICY_TRIPLET_SERV      (-117)
#define EWLM_BAD_POLICY_TRIPLET_PCCLS     (-118)
#define EWLM_BAD_POLICY_TRIPLET_PCFILT    (-119)
#define EWLM_BAD_POLICY_TRIPLET_FILTVAL   (-120)
#define EWLM_BAD_POLICY_APPLENV1          (-121)
#define EWLM_BAD_POLICY_APPLENV2          (-122)
#define EWLM_BAD_POLICY_APPLENV3          (-123)
#define EWLM_BAD_POLICY_TCLASS1           (-124)
#define EWLM_BAD_POLICY_TCLASS2           (-125)
#define EWLM_BAD_POLICY_TCLASS3           (-126)
#define EWLM_BAD_POLICY_TCFILTER_EYE      (-127)
#define EWLM_BAD_POLICY_TCFILTER_INDEX    (-128)
#define EWLM_BAD_POLICY_TCFILTER_SDA      (-129)
#define EWLM_BAD_POLICY_SERV              (-130)
#define EWLM_BAD_POLICY_PCLASS            (-131)
#define EWLM_BAD_POLICY_PCFILTER_EYE      (-132)
#define EWLM_BAD_POLICY_PCFILTER_INDEX    (-133)
#define EWLM_BAD_POLICY_PCFILTER_SDA      (-134)

#define EWLM_BAD_POLICY_TYPE              (-199)/* Policy type not supported */
#define EWLM_RC_POLICY_MIN                (-199)


#define EWLM_RC_COM_MIN                   (-200)
#define EWLM_BAD_FLAGS                    (-200)
#define EWLM_BAD_BUFFER                   (-201)
#define EWLM_BAD_TIMEOUT                  (-202)/* Timeout value not in range
                                                   1..600,000 inclusive */
#define EWLM_ENOMEM                       (-203)
#define EWLM_GETCOMPLETIONS_SECOND_WAITER (-204)
#define EWLM_MISSING_PARM                 (-205)/* Required input parameter s)
                                                   not provided. */
#define EWLM_BAD_PARAMETER_ADDRESS        (-206)
#define EWLM_NOT_AUTHORIZED               (-207)
#define EWLM_BAD_APPL_INST                (-208)
#define EWLM_LIMITOF1_CONNECTION          (-209)/* The platform has another
                                                   connection currently open.
                                                   This connection request was
                                                   rejected due to the limit of
                                                   one active connection per OS
                                                   image. */
#define EWLM_INVALID_SIZE                 (-210)
#define EWLM_INVALID_TOKEN                (-211)/* API such as get_activedata
                                                   received a value, such as a
                                                   token or cursor, which is
                                                   invalid and the platform can
                                                   guarantee that this is the
                                                   result of a bug in the caller
                                                   */
#define EWLM_BAD_IN_BUFFER                (-212)/* Error referencing input
                                                   buffer bad address, not
                                                   readable...). */
#define EWLM_BAD_OUTBUFFER                (-213)/* Error referencing output
                                                   buffer bad address, not
                                                   writable...). */
#define EWLM_UNSUPPORTED_REQUEST_TYPE     (-214)/* Request type not
                                                   supported */
#define EWLM_OUTBUFFER_BELOW_V1SIZE       (-215)/* Output buffer below minimum
                                                   size. At least enough
                                                   storage must be provided to
                                                   return the version number
                                                   and required output size. */
#define EWLM_OUTBUFFER_TOO_SMALL          (-216)/* Output buffer too small to
                                                   contain all data the OS
                                                   returns. Sizeneeded contains
                                                   the buffer size that should
                                                   be used. */
#define EWLM_OUTBUFFER_TOO_LARGE          (-217)/* Output buffer above maximum
                                                   size. */
#define EWLM_INBUFFER_BELOW_V1SIZE        (-218)/* Input buffer below minimum
                                                   size. */
#define EWLM_INBUFFER_TOO_SMALL           (-219)/* Input buffer too small. */
#define EWLM_INBUFFER_TOO_LARGE           (-220)/* Input buffer too large. */
#define EWLM_AIID_NOT_FOUND               (-221)/* AIID not found */
#define EWLM_SUPPORT_NOT_ENABLED          (-222)/* Error because ewlm support
                                                   not enabled in the OS by
                                                   default. */
#define EWLM_COMPONENT_ERROR              (-223)/* The platform experienced an
                                                   error not covered by other
                                                   return codes, and recovered.
                                                   This is normally an
                                                   environmental error such as
                                                   an unsolicited exception.
                                                   For errors whose cause can
                                                   be narrowed down, use and/or
                                                   define a specific return
                                                   code rather than using this
                                                   catch-all.*/
#define EWLM_LOCAL_WLM_NOT_ACTIVE         (-224) /* Return code to signal
                                                    that local WLM is not
                                                    active.*/
#define EWLM_LOCAL_WLM_PASSIVE            (-225) /* Return code to signal
                                                    that local WLM is in
                                                    passive mode. */
#define EWLM_MAX_MGMTCLASSES              (-226) /* Return code to signal
                                                    that platform reached
                                                    maximum number of
                                                    classes it can support.*/
#define EWLM_PROCESS_LOCAL_WLM_MANAGED    (-227) /* Return code to signal
                                                    that platform can not
                                                    manage process to EWLM
                                                    policy because process
                                                    is already associated
                                                    to local WLM management.*/
#define EWLM_BAD_MANAGEMENT_ID            (-228) /* Return code to signal
                                                    that platform can not
                                                    find the management
                                                    class for the
                                                    specified id */
#define EWLM_UNSUPPORTED_RESOURCE_TYPE    (-229) /* Return code to signal
                                                    that platform does not
                                                    support local
                                                    resource management
                                                    for the specified
                                                    resource type. */
#define EWLM_PLATFORM_COMPONENT_ERROR     (-230) /* Return to indicate
                                                    that a severe error was
                                                    encountered during 
                                                    platform service 
                                                    processing */
#define EWLM_RC_PROBLEMATIC_ENV           (-231) /* There is a configuration
                                                    problem detected on the managed
                                                    node that prevent EWLM to manage
                                                    effectively. Details of the
                                                    problem are logged in the
                                                    system logs, such as Linux
                                                    syslogs or Windows event logs.
                                                    If you are running an EWLM MS 
                                                    after the problem is fixed,
                                                    restart the MS. */
#define EWLM_RC_NOT_IN_LPAR               (-232) /* The managed node was previously
                                                    running in an LPAR (or VM), but
                                                    it's been detected that it now
                                                    runs on a different LPAR
                                                    environment, or possibly, on
                                                    a non-LPAR environment.
                                                    If you are running an EWLM MS
                                                    then restarting the MS may be
                                                    required to allow the MS to
                                                    reconfigure itself for the
                                                    new environment, accordingly. */
#define EWLM_LOCAL_MANAGEMENT_NOT_ACTIVE  (-233) /* Local resource management
                                                    not active. */
#define EWLM_LOCAL_MANAGEMENT_ALREADY_ACTIVE (-234) /* Local resource management
                                                       already active.*/
#define EWLM_INVALID_PID                  (-235) /* PID argument to reassign
                                                    function is invalid. */

#define EWLM_RC_COM_MAX                   (-235)


/*
 * Return codes -1000 through -1999 are reserved for common ARM services use.
 */
#define EWLM_RC_ARM_RANGE_START           (-1000)
#define EWLM_RC_ARM_RANGE_END             (-1999)

/*
 * Return codes -2000 through -2999 are reserved for AIX use.
 */
#define EWLM_RC_AIX_RANGE_START           (-2000)
#define EWLM_RC_CONVERT_INVAL             (-2000)/* Unable to open string converter */
#define EWLM_RC_INVAL_STRING              (-2001)/* Invalid input string, 
                                                    string has an input character
                                                    that can not be converted  */ 
#define EWLM_BAD_IN_VERSION               (-2002) /* version number <= 0 */
#define EWLM_RC_INT_ERROR_0               (-2003) /* string table overflow
                                                     in libewlmplat.a       */
#define EWLM_RC_AIX_RANGE_END             (-2999)

/*
 * Return codes -3000 through -3999 are reserved for OS/400 use.
 */
#define EWLM_RC_OS_400_RANGE_START        (-3000)
#define EWLM_RC_OS_400_RANGE_END          (-3999)

#define EWLM_INT_ERROR_0                  (-3003)
#define EWLM_INT_ERROR_1                  (-3004)

/*
 * Return codes -4000 through -4999 are reserved for z/OS use.
 */
#define EWLM_RC_Z_OS_RANGE_START          (-4000)
#define EWLM_RC_Z_OS_RANGE_END            (-4999)

/*
 * Return codes -5000 through -5999 are reserved for common EWLM Java and JNI
 * services use.
 */
#define EWLM_RC_EWLM_JAVA_RANGE_START     (-5000)

#define EWLM_RC_EWLM_ARMJNI_START         (-5001)
#define EWLM_RC_EWLM_ARMJNI_END           (-5099)

#define EWLM_RC_EWLM_PLATJNI_START        (-5101)
#define EWLM_RC_EWLM_PLATJNI_END          (-5199)

#define EWLM_RC_EWLM_NONIBMJNI_START      (-5201)
#define EWLM_RC_EWLM_NONIBMJNI_END        (-5299)

#define EWLM_RC_EWLM_NETWLMJNI_START      (-5301)
#define EWLM_RC_EWLM_NETWLMJNI_END        (-5399)

#define EWLM_RC_EWLM_LOCALRESMGMTJNI_START (-5401)
#define EWLM_RC_EWLM_LOCALRESMGMTJNI_END   (-5449)

#define EWLM_RC_EWLM_JAVA_RANGE_END       (-5999)

/*
 * Return codes -6000 through -6999 are reserved for Windows use.
 */
#define EWLM_RC_WINDOWS_RANGE_START       (-6000)
#define EWLM_RC_WINDOWS_RANGE_END         (-6999)

/*
 * Return codes -7000 through -7999 are reserved for Linux use.
 */
#define EWLM_RC_LINUX_RANGE_START         (-7000)
#define EWLM_RC_LINUX_RANGE_END           (-7999)

/*
 * Return codes -8000 through -8999 are reserved for Solaris use.
 */
#define EWLM_RC_SOLARIS_RANGE_START       (-8000)
#define EWLM_RC_SOLARIS_RANGE_END         (-8999)

/*
 * Return codes -9000 through -9999 are reserved for HP/UX use.
 */
#define EWLM_RC_HP_UX_RANGE_START         (-9000)
#define EWLM_RC_HP_UX_RANGE_END           (-9999)

/*
 * Return codes -15000 through -16999 are reserved for common ARM Java and JNI
 * services use.
 */
#define EWLM_RC_ARM_JAVA_RANGE_START      (-15000)
#define EWLM_RC_ARM_JAVA_RANGE_END        (-16999)

#define EWLM_RC_JAVA_RANGE_START          (-15000)
#define EWLM_RC_JAVA_RANGE_END            (-16999)

/*
 *Return codes -17000 to -17999 are reserved for internal error codes.
 */
#define EWLM_RC_EWLMOTHR_ERROR_RANGE_START                (-17000)
#define EWLM_RC_EWLMOTHR_ERROR_RANGE_END                  (-17999)
/*
 * Return codes -20000 through -20999 are reserved for ARM Standard
 * services use.
 */
#define ARM_ERROR_CODE_RESERVED_START     (-20000)
#define ARM_ERROR_CODE_RESERVED_END       (-20999)

/*
 * Return codes -28000 to -29999 are reserved for EWLM common use.
 * No dump will be generated.  A configuration error will be issued.
 */
#define EWLM_RC_EWLM_COMMON_NODUMP_CONFIG_RANGE_START     (-28000)
#define EWLM_RC_EWLM_COMMON_NODUMP_CONFIG_RANGE_END       (-29999)

/*
 * Return codes -30000 to -32767 are reserved for EWLM common use.
 * No dump will be generated and no configuration error will be issued.
 */
#define EWLM_RC_EWLM_COMMON_NODUMP_NOCONFIG_RANGE_START   (-30000)
#define EWLM_RC_EWLM_COMMON_NODUMP_NOCONFIG_RANGE_END     (-32767)

/* --------------------------------------------------------------------------*/
/* ------------------------ content of ewlmtype.h ---------------------------*/
/* ------------------------------------------------------------------------- */
/* Change Activity:
 * Reason      Date      Origin               Description
 * -------  ----------  -----------     ------------------------------------
 * DCR 002  2003-08-31  John Arwe       Add 2 bits to completion records for
 *                                      tracking of why hop count was not
 *                                      incremented
 * DCR 011  2003-09-01  John Arwe       Change duration to signed per Yocom
 *                                      note
 * DCR 011  2003-09-02  John Arwe       Rename files to be within 8-char limit
 *                                      Update un/encodedbytestream comments
 *                                      with default origin
 * DCR xxx  2003-09-23  Geoff Lubold    Change XXX_t types to ewlm_XXX_t
 *                                      types
 * DCR 010  2003-10-01  Geoff Lubold    updated Platform OS API LLD to
 *                                      include flag under Generic ARM
 *                                      transaction Data.
 * F2691    2003-10-28  Geoff Lubold    Includes changed from " " to < >
 * D2593    2003-11-11  John Arwe       Clarify encodings comments
 * DCR 030  2003-11-24  John Arwe       Add blocked time overflow bits
 * ------------------------------------------------------------------------- */
/*
 * Guidelines for files like this which are intended to be the same across all
 * platforms:
 * - Not all platforms support int_64 natively, so an ewlm_int64 type is defined
 *   in ewlmplatos.h, and each platform completes the definition there.
 * - Not all C compilers support the double-slash end of line comments, so stick
 *   to the explicit open/close style comments.
 */ 
#include <arm4ewlm.h>

/* ------------------------------------------------------------------------- */
/* --------------------------- type definitions ---------------------------- */
/* ------------------------------------------------------------------------- */

typedef ewlm_int8_t             ewlm_period_t;
typedef ewlm_int64_t            ewlm_timestamp_t;    /* Same as ARM 4.0 timestamps:
                                                microseconds since
                                                1 January 2000 using the
                                                Gregorian calendar
                                                */
typedef ewlm_int32_t            ewlm_duration_t;  /* Millisecond unit elapsed
                                                time.  Intentionally smaller
                                                than timestamp to limit the
                                                size of in-flight and
                                                completion records.
                                                */
typedef ewlm_int16_t            ewlm_get_activedata_flags_t; /*
                                                for in-flight records */

typedef ewlm_int16_t            ewlm_micro_duration_t; /* Microsecond unit elapsed
                                                          time. (remainder of
                                                          millisecond unit elapsed
                                                          time.)*/
typedef ewlm_int64_t            ewlm_arrival_delay_duration_t; /* Microsecond unit
                                                 duration from tran edge arrival
                                                 time to current hop arrival
                                                 time.  (This delay can only be
                                                 computed when EWLM time sync is
                                                 actively monitoring clock deltas
                                                 on the transaction edge and at
                                                 the current hop.) */


#define EWLM_GET_ACTIVEDATA_STALE_REPORTING_ID      (0x8000)
#define EWLM_GET_ACTIVEDATA_QUEUE_TIME_OVERFLOW     (0x4000)
#define EWLM_GET_ACTIVEDATA_NO_HOP_SAME_AE          (0x2000)
#define EWLM_GET_ACTIVEDATA_NO_HOP_SAME_AI          (0x1000)
#define EWLM_GET_ACTIVEDATA_TOPOLOGY_NOT_VALID      (0x0800)
#define EWLM_GET_ACTIVEDATA_REPORTING_GAP           (0x0400)
#define EWLM_GET_ACTIVEDATA_BLOCKED_TIME_OVERFLOW   (0x0200)
#define EWLM_GET_ACTIVEDATA_LOCAL_WLM_MANAGED       (0x0100)
#define EWLM_GET_ACTIVEDATA_TIME_SUSPECTED          (0x0080)

/* definitions for flagsv3 */
#define EWLM_GET_ACTIVEDATA_ARRIVAL_DELAY           (0x8000)
#define EWLM_GET_ACTIVEDATA_ASYNC_PARENT            (0x4000)
#define EWLM_GET_ACTIVEDATA_INDEPENDENT_TRAN        (0x2000)
#define EWLM_GET_ACTIVEDATA_MSGEVENT_START          (0x1000)
#define EWLM_GET_ACTIVEDATA_BLOCKED_ON_MESSAGE      (0x0800)

typedef ewlm_int16_t           ewlm_get_completions_flags_t; /*
                                                for completion records */
#define EWLM_GET_COMPLETIONS_STALE_REPORTING_ID     (0x8000)
#define EWLM_GET_COMPLETIONS_QUEUE_TIME_OVERFLOW    (0x4000)
#define EWLM_GET_COMPLETIONS_NO_HOP_SAME_AE         (0x2000)
#define EWLM_GET_COMPLETIONS_NO_HOP_SAME_AI         (0x1000)
#define EWLM_GET_COMPLETIONS_TOPOLOGY_NOT_VALID     (0x0800)
#define EWLM_GET_COMPLETIONS_REPORTING_GAP          (0x0400)
#define EWLM_GET_COMPLETIONS_BLOCKED_TIME_OVERFLOW  (0x0200)
#define EWLM_GET_COMPLETIONS_ARTIFICIAL_COMPLETION  (0x0080)
#define EWLM_GET_COMPLETIONS_RESPONSE_TIME_OVERFLOW (0x0040)
#define EWLM_GET_COMPLETIONS_LOCAL_WLM_MANAGED      (0x0020)
#define EWLM_GET_COMPLETIONS_TIME_SUSPECTED         (0x0010)

/* definitions for flagsv3 */
#define EWLM_GET_COMPLETIONS_ARRIVAL_DELAY          (0x8000)
#define EWLM_GET_COMPLETIONS_ASYNC_PARENT           (0x4000)
#define EWLM_GET_COMPLETIONS_INDEPENDENT_TRAN       (0x2000)
#define EWLM_GET_COMPLETIONS_MSGEVENT_START         (0x1000)
#define EWLM_GET_COMPLETIONS_MSGFLOW_COMPLETE       (0x0800)
#define EWLM_GET_COMPLETIONS_REPORTED_TRANSACTION   (0x0400)

typedef ewlm_int16_t            ewlm_ARM_completion_status_t; /* ARM transaction
                                                completion status
                                                */

typedef ewlm_int32_t            ewlm_policytype_t;   /* ewlm_x_policy APIs
                                                Policy type
                                                */

typedef ewlm_int32_t            ewlm_status_t;       /* API return code
                                                */
typedef ewlm_int64_t      ewlm_applenv_id_t;   /* AEID:
                                                application environment ID
                                                assigned by ARM implementation
                                                */
typedef ewlm_int64_t      ewlm_applinst_id_t;  /* AIID:
                                                application instance ID
                                                assigned by ARM implementation
                                                */
typedef ewlm_int16_t            ewlm_local_server_id_t; /* Local server ID
                                                (short form of server UUID)
                                                assigned by EWLM
                                                */
typedef ewlm_int32_t            ewlm_bytelength_t;   /* Size in bytes of
                                                whatever context it describes
                                                */
typedef ewlm_int16_t            ewlm_APIlevel_t;     /* Support level of a set of
                                                APIs, used by EWLM to know if
                                                a given set of API signatures
                                                is supported by the platform
                                                (thus EWLM may call them).
                                                */
typedef ewlm_int16_t            ewlm_APIversion_t;   /* Version number,
                                                specific to each API.  Replaces
                                                any code dependency on size to
                                                know which data is returned.  So
                                                if version 2 of an interface
                                                adds 3 pieces of data, the
                                                receiver of the structure would
                                                test the version to know whether
                                                or not the 3 new pieces of data
                                                came back.
                                                */

typedef ewlm_int16_t           ewlm_tranevent_count_t; /* Transaction
                                                instance event count
                                                type.        */
typedef ewlm_int16_t            ewlm_msg_correlation_flags_t; /* Flags
                                                for message correlation
                                                records      */
/* Flag to indicate this correlator was a secondary  correlator from the
   arm_start_transaction() event.                            */
#define EWLM_MSG_CORR_STARTTRAN     (0x8000)

/* ------------------------------------------------------------------------- */
/* --------------------------- macro definitions --------------------------- */
/* ------------------------------------------------------------------------- */

#define MAXVERSIONSIZE(old,latest) (old>latest ? old:latest)
#define IS_EWLM_PROC(pv) (((pv->pv_class >= WLM_EWLM_LOW) && \
                          (pv->pv_class < WLM_EWLM_HI))? 1 : 0)

/* --------------------------------------------------------------------------
The string descriptor type allows the size of a string returned to change
without causing a version number or API support level change (in other words,
simply by recompiling).  If the string were allocated in-line as an array of
char, a subsequent length change (e.g. from a later version of some standard,
or an OS change which increases the maximum size of a string already being
returned) would force one of the following:
- Splitting of the string into new and old pieces (compatible)
- Changing the offset of the string in the output buffer (incompatible)
- Changing the length of the string in the output buffer, but not the offset
  (incompatible, since later fields would have to change offsets to make room).
Can be used by APIs which return several strings with the same encoding to save
memory.
---------------------------------------------------------------------------- */
typedef struct ewlm_unencodedbytestream
{
    ewlm_int32_t        offset;       /* Offset from some documented point to the
                                  first byte.  If the place where this type
                                  is instantiated does not document the origin
                                  the default is the containing structure */

    ewlm_int32_t        length;       /* Length of value in bytes not characters
                                  excluding any termination byte(s). */

/* If both the offset and length are zero the string is not provided.
 * A non-zero offset and zero length denote the null string (which might be
 * considered equivalent to not providing the string, depending upon the
 * the API where this is used).
 */
} ewlm_unencodedbytestream_t;

/* --------------------------------------------------------------------------
The string described may be in any supported encoding.
Used by APIs which find it more efficient to
encapsulate the encoding with the string.
---------------------------------------------------------------------------- */

typedef struct ewlm_encodedbytestream
{
    ewlm_int32_t        offset;       /* Offset from some documented point to the
                                  first byte.  If the place where this type
                                  is instantiated does not document the origin
                                  the default is the containing structure */

    ewlm_int32_t        length;       /* Length of value in bytes (not characters)
                                  excluding any termination byte(s). */
/* If both the offset and length are zero the string is not provided.
 * A non-zero offset and zero length denote the null string (which might be
 * considered equivalent to not providing the string, depending upon the
 * the API where this is used).
 */
    ewlm_int16_t        value;       /* The same encoding values as supported in
                                   the ARM 4.0 standard are used.  Reqd-ARM shows
                                   those required by the ARM standard, Reqd-EWLM
                                   shows those required by the EWLM ARM
                                   implementation, Allowed shows those allowed by
                                   the EWLM product/supporting ARM implementations.
                                                  ARM APIs          ewlmplat APIs
                             3    US-ASCII        Reqd-ARM          specify 106
                           106    UTF-8           Reqd-ARM          Allowed
                          1013    UTF-16BE        z,i,p             specify 1015
                          1014    UTF-16LE        Reqd-ARM-Windows  specify 1015
                          1015    UTF-16          Reqd-EWLM         Allowed
                          2028    EBCDIC IBM037   i: Reqd-ARM
                          2102    EBCDIC IBM1047  z: Reqd-ARM       z: Allowed

                                  Note on UTF-16: only 1015 is supported by
                                  the ewlmplat APIs, which uses platform default
                                  Endian-ness.  Thus on z,i,p it is equivalent to
                                  1013 without a byte order marker, and on x it is
                                  equivalent to 1014 without a marker.
                                */

    ewlm_int16_t        flags;

    #define EWLM_NULL_TERMINATED      (0x0001)
    /* If EWLM_NULL_TERMINATED is on, the termination byte(s) are dependent upon
       the encoding value used.
       UTF-8         Single null terminator
       UTF-16        Double null terminator
    */
} ewlm_encodedbytestream_t;

/* ------------------------------------------------------------------------- */
/* --------------------------- query services ------------------------------ */
/* ------------------------------------------------------------------------- */

/*
 *  Signature:
 *              EWLM query
 */
ewlm_status_t   ewlm_query(
    /* [in]  */ ewlm_char_t                       *input_buffer,
    /* [in]  */ ewlm_bytelength_t          input__buffer_size,
    /* [i/o] */ ewlm_char_t                       *output_buffer,
    /* [in]  */ ewlm_bytelength_t          output_buffer_size
);

/*
    Required Return codes:
       0    EWLM_SUCCESS
    -100    EWLM_NO_CONNECTION
    -214    EWLM_UNSUPPORTED_REQUEST_TYPE
    -215    EWLM_OUTBUFFER_BELOW_V1SIZE
    -216    EWLM_OUTBUFFER_TOO_SMALL
    -218    EWLM_INBUFFER_BELOW_V1SIZE
    -219    EWLM_INBUFFER_TOO_SMALL
    -222    EWLM_SUPPORT_NOT_ENABLED

    Optional Return codes:
    -101    EWLM_BAD_CONNECT_HANDLE
    -205    EWLM_MISSING_PARM
    -212    EWLM_BAD_IN_BUFFER
    -213    EWLM_BAD_OUTBUFFER
*/


/*
 * Query Server Configuration Input
 */
typedef struct ewlm_query_server_configuration_input
{
    ewlm_APIversion_t          version;
    ewlm_int32_t                    request_type;
    #define EWLM_QUERY_SERVER_CONFIGURATION        (1)
    #define EWLM_QUERY_SERVER_STATISTICS           (2)
    #define EWLM_QUERY_RESOURCE_METRICS_COLLECTED  (3)

    ewlm_connect_handle_t      connect_handle;
    /* ------- end of data present in version 1        */
    #define EWLM_QUERY_SERVER_CONFIGURATION_IN_VERSION001     (1)
    #define EWLM_QUERY_SERVER_CONFIGURATION_INPUT_V001SIZE \
    sizeof(ewlm_query_server_configuration_input_t)
} ewlm_query_server_configuration_input_t;

/*
 * Query Server Configuration Output
 */
typedef struct ewlm_query_server_configuration_output
{
   ewlm_APIversion_t           version;
   ewlm_bytelength_t           sizeneeded;

   ewlm_int32_t                platform_support_level1; /* ewlm_ API support */
   /* F15321 */
   #define EWLM_QUERY_PLATFORMAPI_EWLM12    (0x80000000)/* EWLM 1.2 release */
   #define EWLM_QUERY_PLATFORMAPI_EWLM10    (0x40000000)/* EWLM 1.0 release */
   #define EWLM_QUERY_PLATFORMAPI_EL        (0x20000000)/* Non-IBM
                                                           enforcement layer
                                                           APIs exist */
   #define EWLM_QUERY_PLATFORMAPI_EWLM31    (0x01000000)/* EWLM 3.1 release */

   ewlm_int32_t                platform_support_level2;
   #define EWLM_QUERY_GLOBAL_PERF_DATA      (0x80000000) /* Platform supports the
                                                             ewlm_global_perf_data
                                                             API                */
    #define EWLM_QUERY_SPURR_SUPPORTED      (0x40000000) /* F32148 DCR24
                                                            Platform supports reporting
                                                            Scaled CPU Utilization when
                                                            processor frequency is 
                                                            variable */
                                                            
   #define EWLM_QUERY_PROC_SPURR_CAPPED     (0x20000000) /* F32148 DCR24
                                                            Platform is capping per process
                                                            scaled CPU utilization to
                                                            un-scaled CPU utilization.
                                                            cpu_time and scaled_cpu_time 
                                                            reported in process data will 
                                                            be same. System level scaled
                                                            CPU utilization reported in 
                                                            server statistics is not capped */                                                           

   ewlm_int32_t                entitlement_support_level;
   #define EWLM_QUERY_ENTITLEMENTAPI_NONE   (0x40000000)/* No entitlement    */
   #define EWLM_QUERY_ENTITLEMENTAPI_CPU    (0x80000000)/* Local CPU Resource*/
                                                        /* Management        */


   ewlm_int32_t                network_support_level;
   #define EWLM_QUERY_NETWORKAPI_NONE       (0x40000000)/* No net_ APIs */
   #define EWLM_QUERY_NETWORKAPI_LOADBAL    (0x20000000)/* Load balancing */
   #define EWLM_QUERY_NETWORKAPI_ACCEPTQ    (0x10000000)/* Accept queue */

   ewlm_bytelength_t           max_practical_get_completions_buffer_size;/*
                                OS-suggested size for ewlm_get_completions
                                output buffer.  The value returned should be no
                                larger than the size of the buffer used by the
                                OS to buffer completion records. */
    ewlm_bytelength_t          recommended_get_activedata_buffer_size;/*
                                OS-suggested size for ewlm_get_activedata
                                output buffer.
                                The platform will be in a better position
                                than the caller to understand the relative
                                importance of memory size, and any limits
                                within the platform code that would influence
                                the maximum number of concurrent processes
                                and/or ARM transactions. The tradeoff here is
                                between memory size and the number of restarts.
                                The callers is free to accept or ignore the
                                recommendation, but as long as it appears to be
                                reasonable it should be used. */
    ewlm_int32_t                    flags001;
   /* Hypervisors */
   #define EWLM_QUERY_SERVER_CONFIGURATION_OS_UNDER_ZVM     (0x40000000)
   #define EWLM_QUERY_SERVER_CONFIGURATION_OS_UNDER_LPAR    (0x20000000)
   #define EWLM_QUERY_SERVER_CONFIGURATION_OS_UNDER_VMWARE  (0x10000000)

    ewlm_encodedbytestream_t   hostname;/* TCP hostname */
    ewlm_encodedbytestream_t   software_cluster_name;/*
                                If the platform has a platform-specific cluster
                                name, e.g. z/OS sysplex, the sysplex name is
                                here. Null string otherwise. */
    ewlm_encodedbytestream_t   hardware_cluster_name;/*
                                If the image is running in a hypervisor-managed
                                cluster, this field contains a numeric group ID
                                followed by a space, the manufacturer name
                                followed by a space and model number
                                concatenated with serial number
                                e.g 9406-57010-XYZ10. '-' in model number or
                                serial number should be included. If model
                                number and serial number contains manufacturer
                                name it should be stripped off. For example, if
                                model number is "IBM,9119-595", only "9119-595"
                                should be included in model number and "IBM"
                                should be returned as part of manufacturer name.
                                */
                                /*
                                with EWLM Release 3.1 the hardware_cluster_name
                                can be the hostname of the LPAR hosting server
                                when the MS is running in an LPAR/VM. The
                                hardware_cluster_name can also be an empty
                                string when the MS is running on an LPAR/VM
                                if the platform support code cannot access this
                                information.
                                */
    ewlm_unencodedbytestream_t hardware_cluster_name_binary;/*
                                Same info as the previous field, but not
                                required to be in printable format. Used to
                                recognize the boundary of the hardware cluster.
                                All images with an identical binary h/w cluster
                                name are assumed to belong to the same
                                hypervisor cluster. */
    ewlm_encodedbytestream_t   os_platform;/* Classification filter, value is
                                one of:
                                z/OS, AIX, OS/400, Solaris, Linux, Windows */
    ewlm_encodedbytestream_t   os_architecture;/* Used for reporting only.
                                Reflects the machine's hardware architecture
                                family.  The value returned is owned by the
                                platform. */
    ewlm_encodedbytestream_t   os_level_summary;/* Used for classification.
                                Format of the value is
                                v.r.j.n, where
                                    v = version
                                    r = release
                                    j = major modification level
                                    n = minor modification level
                                Any of the component values maybe alphanumeric.
                                Leading zeros on numeric values should be
                                suppressed. */
    ewlm_encodedbytestream_t   os_level_detail;/*
                                Used for reporting only.  Should include the
                                same info as the summary version, although
                                not necessarily in the same format.  Can
                                optionally include more detailed info such
                                as service pack level. */
    ewlm_encodedbytestream_t   os_instance_name;/*
                                If the platform has a native image name, e.g.
                                z/OS system name, its value goes here.
                                Otherwise the TCP hostname should be used. */

    /* ------- end of data present in version 1 */
    #define EWLM_QUERY_SERVER_CONFIGURATION_OUTVERSION001     (1)
    #define EWLM_QUERY_SERVER_CONFIGURATION_OUTPUT_V001SIZE \
        offsetof(ewlm_query_server_configuration_output_t,\
                 hypervisor_capability)
/*F12760 */
      ewlm_int32_t                hypervisor_capability;
   #define EWLM_QUERY_HYPERVISOR_NONE    0            /* None or unknown
                                                         hypervisor */
   #define EWLM_QUERY_HYPERVISOR_POWER5  1            /* IBM i/p POWER5/later */
           /* If POWER5 capability is true, the OS supports APIs to query and
              update partition attributes consistent with the POWER5 platform.
              The actual hardware may be at a later level than POWER5, with
              additional capabilities.  */
   #define EWLM_QUERY_HYPERVISOR_PRSM    2            /* IBM z PR/SM */
   #define EWLM_QUERY_HYPERVISOR_VMWARE  4            /* VMware ESX  */

      ewlm_int32_t                os_dynamic_lpar_capability;
   #define EWLM_QUERY_DLPAR_NONE    (0x000000000) /* partition does not supports
                                                 dynamic lpar management because
                                                 it is running on non supported
                                                 platform or it is not part of
                                                 any partition group */

   #define EWLM_QUERY_DLPAR_CPU_CAPACITY (0x00000001) /* partition supports
                                                      dynamic lpar management
                                                      of CPU capacity */
   #define EWLM_QUERY_DLPAR_CPU_WEIGHT   (0x00000002) /* partition supports
                                                      dynamic lpar management
                                                      of CPU weight */
   #define EWLM_QUERY_DLPAR_INT_CAPACITY (0x00000004) /* partition supports
                                                      dynamic lpar management
                                                      of interactive capacity
                                                      */
   #define EWLM_QUERY_DLPAR_VIRTUAL_CPU  (0x00000008) /* partition supports
                                                      dynamic management of
                                                      virtual processors */
   #define EWLM_QUERY_DLPAR_MEMORY       (0x00000010) /* partition supports
                                                      dynamic lpar management
                                                      of memory */

   ewlm_encodedbytestream_t    hypervisor_group_id;/*
                                Printable hypervisor group ID (IBM zSeries
                                sysplex name IBM p/iSeries: binary hypervisor
                                value converted to numeric printable format.
                                Platform should not provide any leading 0s. For
                                example, if binary group ID is x'0001', the
                                printable group ID will be "1".) or null string
                                if not available. */
   ewlm_encodedbytestream_t    hw_manufacturer;/*
                                Printable hardware manufacturer name,
                                or null string if not available. For example,
                                for IBM hardware this field should be set to
                                "IBM" */
   ewlm_encodedbytestream_t    modelno_serialno; /*
                                Printable hardware model number and serial
                                Number or null string if not available. '-' in
                                model number or serial number should be
                                included. Model number should include
                                the hardware type e.g. 9406-570. The serial
                                number (e.g. 10-XYZ10) is appended to
                                model number without any intervening
                                character e.g. "9406-57010-XYZ10" */

    /* ------- end of data present in version 2 */
    #define EWLM_QUERY_SERVER_CONFIGURATION_OUTVERSION002     (2)
    #define EWLM_QUERY_SERVER_CONFIGURATION_OUTPUT_V002SIZE \
        sizeof(ewlm_query_server_configuration_output_t)

    /*
     * In storage, this buffer should be immediately followed by the contents
     * of the data described by the ewlm_encodedbytestream_t components.
     * All offsets in these components are relative to the beginning of the
     * ewlm_query_server_configuration_output structure.
     */
} ewlm_query_server_configuration_output_t;

/*
 *    Query Server Statistics Input
 */
typedef struct ewlm_query_server_statistics_input
{
    ewlm_APIversion_t          version;
    ewlm_int32_t               request_type;
    ewlm_connect_handle_t      connect_handle;
    /* ------- end of data present in version 1        */

    #define EWLM_QUERY_SERVER_STATISTICS_IN_VERSION001     (1)
    #define EWLM_QUERY_SERVER_STATISTICS_INPUT_V001SIZE \
        offsetof(ewlm_query_server_statistics_input_t, flags)
    ewlm_int32_t         flags;
    #define EWLM_QUERY_SERVER_STATISTICS_CLOCK_ACCOUNTING_INACTIVE (0x80000000)
    #define EWLM_QUERY_SERVER_STATISTICS_CLOCK_ACCOUNTING_UPDATE   (0x40000000)
    ewlm_int64_t         master_clock_delta;
    #define EWLM_QUERY_SERVER_STATISTICS_IN_VERSION002     (2)
    #define EWLM_QUERY_SERVER_STATISTICS_INPUT_V002SIZE \
        sizeof(ewlm_query_server_statistics_input_t)
} ewlm_query_server_statistics_input_t;

/*
 *    Query Server Statistics Output
 */
typedef struct ewlm_query_server_statistics_output
{
    ewlm_APIversion_t          version;
    ewlm_bytelength_t          sizeneeded;
    /*
     * All of the version 1 data is used for reporting only, and may not be
     * (in some cases, definitely is not) suitable for management uses.
     * PBY decided to go with this for the first release, and we will add data
     * in later release(s) as needed for management.
     */
    ewlm_int32_t                    online_cpus;/*
                                Number of online logical CPUs the instant this
                                interface is called */
    ewlm_cpu_time_t            cpu_time;/*
                                Total mode microseconds of CPU time consumed by
                                the OS image since a platform-dependent
                                initialization point (e.g. boot)
                                This field should not include idle time */
    ewlm_int64_t               physical_memory_size;/*
                                Kilobytes of real memory configured to the OS at
                                the instant this interface is called */
    ewlm_uint64_t              paging_space_faults;/*
                                Number of page faults requiring I/O since the
                                same system initialization point as used for
                                cpu_time. May wrap. Thus this describes page-ins
                                due to lack of memory, exclusive of file system
                                activity. */

    /* ------- end of data present in version 1 */
    #define EWLM_QUERY_SERVER_STATISTICS_OUTVERSION001     (1)
    #define EWLM_QUERY_SERVER_STATISTICS_OUTPUT_V001SIZE \
        offsetof(ewlm_query_server_statistics_output_t,\
                 local_wlm_state)


    ewlm_int32_t               local_wlm_state; /* If platform has local work
                                                 load manager, report the
                                                 current state of the local
                                                 wlm */
    #define EWLM_QUERY_LOCAL_WLM_NOT_ACTIVE   (0x00000000) /* Either
                                                 platform does not support
                                                 local WLM or it is not
                                                 running */

    #define EWLM_QUERY_LOCAL_WLM_ACTIVE       (0x40000000) /* Local WLM is
                                                 active */
    #define EWLM_QUERY_LOCAL_WLM_PASSIVE      (0x80000000) /* Local WLM is
                                                 passive, monitoring mode
                                                 only */

     ewlm_int32_t             ewlm_manageable_resources; /* Types of system
                                                 resources that EWLM
                                                 can manage*/
     #define EWLM_QUERY_NO_LOCAL_RESOURCE_MGMT   (0x00000000) /* System does
                                                not support any EWLM resource
                                                management at this point. If
                                                ewlm_query() is invoked
                                                while EWLM local resource
                                                management is disabled,
                                                platform reports that there
                                                are no EWLM manageable
                                                resources */
     #define EWLM_QUERY_LOCAL_CPU_MGMT   (0x40000000) /* System supports
                                                 local CPU management. At
                                                 present only local CPU
                                                 mgmt support is provided */


     ewlm_int32_t             ewlm_cpu_share; /* CPU share assigned to EWLM
                                                 managed work. 0 means
                                                 local resource management
                                                 is not active. -1 indicates
                                                 that shares for EWLM managed
                                                 work is not defined and
                                                 EWLM managed work can
                                                 consume 100% of system
                                                 CPU resources if there is a
                                                 demand for CPU and there is
                                                 no competition from other
                                                 non EWLM managed work. */

      ewlm_int32_t            ewlm_cpu_consumed; /* Percentage of processing
                                                 capacity consumed by OS
                                                 image that is attributed to
                                                 to work running under
                                                 EWLM management. 0 means
                                                 local resource management
                                                 is not active. This number
                                                 is scaled by 100. So, to
                                                 compute percentage,
                                                 this number needs to be
                                                 divided by 100*/
      ewlm_cpu_time_t         scaled_cpu_time;   /* F32148 DCR24
                                                    Total mode microseconds
                                                    of scaled CPU time consumed
                                                    by the OS image since a
                                                    platform-dependent
                                                    initialization point
                                                    (e.g. boot).
                                                    This field should not 
                                                    include idle time */
      /* ------- end of data present in version 2 */
    #define EWLM_QUERY_SERVER_STATISTICS_OUTVERSION002     (2)
    #define EWLM_QUERY_SERVER_STATISTICS_OUTPUT_V002SIZE \
        sizeof(ewlm_query_server_statistics_output_t)


} ewlm_query_server_statistics_output_t;

/* 
 *    Query Resource Metrics Collected Input
 */

typedef struct ewlm_query_resource_metrics_collected_input
{
    ewlm_APIversion_t          version;
    ewlm_int32_t                    request_type;
    ewlm_connect_handle_t      connect_handle;

    /* ------- end of data present in version 1 */
    #define EWLM_QUERY_RESOURCE_METRICS_IN_VERSION001     (1)
    #define EWLM_QUERY_RESOURCE_METRICS_COLLECTED_INPUT_V001SIZE \
        sizeof(ewlm_query_resource_metrics_collected_input_t)

} ewlm_query_resource_metrics_collected_input_t;

/*
 *    Query Resource Metrics Collected Output
 */
typedef struct ewlm_query_resource_metrics_collected_output
{
    ewlm_APIversion_t          version;
    ewlm_bytelength_t          sizeneeded;
    ewlm_int8_t                     cpu_time_mode;   /* total or delta mode */
    #define EWLM_QUERY_RESOURCE_METRICS_COLLECTED_TOTAL_MODE  (1)
    #define EWLM_QUERY_RESOURCE_METRICS_COLLECTED_DELTA_MODE  (2)

    ewlm_int8_t                     samples_mode;    /* total or delta mode,
                                applies to all state samples and
                                number of samples collected */
    ewlm_int32_t                    samplescollectedflags;/*
                                Idle and Other are required if any of the other
                                types are collected, hence they are not
                                explicitly flagged here */
    #define EWLM_QUERY_RESOURCE_METRICS_COLLECTED_CPU_USING         (0x40000000)
    #define EWLM_QUERY_RESOURCE_METRICS_COLLECTED_CPU_DELAY         (0x20000000)
    #define EWLM_QUERY_RESOURCE_METRICS_COLLECTED_PAGE_DELAY        (0x10000000)
    #define EWLM_QUERY_RESOURCE_METRICS_COLLECTED_IO_DELAY          (0x08000000)
            /* Some platforms which collect process delay samples may choose to
               not return records for processes which are idle (no sampled delay
               or using states observed between two invocations of get_activedata
               omitting CONTINUE requests).  The caller must then adjust the
               idle samples accordingly. */
    #define EWLM_QUERY_RESOURCE_METRICS_COLLECTED_IDLEPROCS_SKIPPED (0x04000000)

    /* ------- end of data present in version 1 */
    #define EWLM_QUERY_RESOURCE_METRICS_OUTVERSION001     (1)
    #define EWLM_QUERY_RESOURCE_METRICS_COLLECTED_OUTPUT_V001SIZE \
        offsetof(ewlm_query_resource_metrics_collected_output_t,\
                 os_sampling_1000sec_conversion_factor)

    ewlm_int32_t              os_sampling_1000sec_conversion_factor;/*
                                If the platform calculates its samples rather
                                than directly sampling them, then this constant
                                represents the number of samples which the
                                platform would return for a single threaded
                                process over one thousand seconds of wall clock
                                time.  Platforms which do not calculate
                                their samples should return 0. If version 1 of
                                this area is returned, its value is assumed
                                to be 0. The value may only used if
                                COLLECTED_IDLEPROCS_SKIPPED is on. */

    /* ------- end of data present in version 2 */
    #define EWLM_QUERY_RESOURCE_METRICS_OUTVERSION002     (2)
    #define EWLM_QUERY_RESOURCE_METRICS_COLLECTED_OUTPUT_V002SIZE \
        sizeof(ewlm_query_resource_metrics_collected_output_t)
} ewlm_query_resource_metrics_collected_output_t;

/* ------------------------------------------------------------------------- */
/* --------------------------- state services ------------------------------ */
/* ------------------------------------------------------------------------- */

/*
 *  EWLM Connect Input
 */
typedef struct ewlm_connect_input
{
    ewlm_APIversion_t          version;
    /* ------- end of data present in version 1        */
    #define EWLM_CONNECT_IN_VERSION001     (1)
    /* F15541 fix versioning for platform at higher level than EWLM */
    #define EWLM_CONNECT_INPUT_V001SIZE \
        (offsetof(ewlm_connect_input_t, version) + sizeof(ewlm_APIversion_t))

    ewlm_int32_t           sampling_timer;  /*F12760
                                              Optional input that identifies
                                              the time interval at which
                                              platform needs to collect
                                              samples. This field is millisec
                                              units. This field is mainly for
                                              LINUX platform to setup the
                                              sampling interval. Other
                                              platforms that run the sampling
                                              task can also use this input to
                                              configure the sampling interval */
    /* ------- end of data present in version 2 */
    #define EWLM_CONNECT_IN_VERSION002     (2)
    #define EWLM_CONNECT_INPUT_V002SIZE sizeof(ewlm_connect_input_t)
} ewlm_connect_input_t;

/*
 *  EWLM Connect Output
 */
typedef struct ewlm_connect_output
{
    ewlm_APIversion_t          version;
    ewlm_bytelength_t          sizeneeded;
    ewlm_connect_handle_t      connect_handle;
    /* ------- end of data present in version 1 */
    #define EWLM_CONNECT_OUTVERSION001  (1)
    #define EWLM_CONNECT_OUTPUT_V001SIZE sizeof(ewlm_connect_output_t)
} ewlm_connect_output_t;

/* ewlm_connect() enforces that only one EWLM Workload Manager is active on a
system.  The EWLM agent calls ewlm_connect() during its initialization to
establish a connection with the platform component.  If there is no active EWLM
already connected, ewlm_connect() records a successful connection and returns
a valid connection handle and a zero status code.  If there is an active EWLM
agent already connected, ewlm_connect() returns an invalid connection handle
and a negative status code.

There is a complementary function called ewlm_disconnect() that the EWLM agent
calls before it shuts down.  In order to handle cases where the EWLM agent fails
and might not be able to call ewlm_disconnect(), the platform must either set
up to be notified of the termination of the EWLM agent process so that it can
disconnect implicitly, or it must be able to recognize in a subsequent
ewlm_connect() call that the existing connection information refers to a process
that no longer exists.

Notes:
-  Although the EWLM management server prevents duplicate WLMs on a single
    system from joining the management domain, this leaves exposed the case
    where a WLM cannot join due to communication problems.  In that case the
    EWLM agent proceeds by activating a cached policy or a default policy.
    The ewlm_connect() function ensures only one WLM can invoke the ewlm_ APIs.

-    When ewlm_connect() returns the error code indicating a WLM is already
    connected, the calling WLM terminates with an indicative error code.  It is
    assumed that system operations personnel will be able to use existing
    operating system commands to identify the EWLM agent that is already running
    (e.g. by process name or by userid, if they have assigned a special userid
    to the EWLM agent).  Therefore there is no requirement to implement a new
    command to display the status of the EWLM agent connection.

-    The connect handle allows for the possibility that someday EWLM might
    support some structure other than the current 1:1 agent:OS image
    mapping, e.g. by sharing a single handle amongst several processes or
    by allowing multiple valid handles.

*/

/*
 *  Signature:
 *              EWLM Connect
 */

ewlm_status_t ewlm_connect(
    /* [in]  */ ewlm_connect_input_t       *input_buffer,
    /* [in]  */ ewlm_bytelength_t          input__buffer_size,
    /* [i/o] */ ewlm_connect_output_t      *output_buffer,
    /* [in]  */ ewlm_bytelength_t          output_buffer_size
);

/*
    Required Return codes:
       0    EWLM_SUCCESS
    -209    EWLM_LIMITOF1_CONNECTION
    -215    EWLM_OUTBUFFER_BELOW_V1SIZE
    -216    EWLM_OUTBUFFER_TOO_SMALL
    -218    EWLM_INBUFFER_BELOW_V1SIZE
    -219    EWLM_INBUFFER_TOO_SMALL
    -222    EWLM_SUPPORT_NOT_ENABLED

    Optional Return codes:
    -205    EWLM_MISSING_PARM
    -212    EWLM_BAD_IN_BUFFER
    -213    EWLM_BAD_OUTBUFFER
 */


typedef struct ewlm_disconnect_input
{
    ewlm_APIversion_t          version;
    ewlm_connect_handle_t      connect_handle;
    /* ------- end of data present in version 1        */
    #define EWLM_DISCONNECT_IN_VERSION001     (1)
    #define EWLM_DISCONNECT_INPUT_V001SIZE sizeof(ewlm_disconnect_input_t)
} ewlm_disconnect_input_t;

typedef struct ewlm_disconnect_output
{
    ewlm_APIversion_t          version;
    ewlm_bytelength_t          sizeneeded;
    /* ------- end of data present in version 1 */
    #define EWLM_DISCONNECT_OUTVERSION001     (1)
    #define EWLM_DISCONNECT_OUTPUT_V001SIZE sizeof(ewlm_disconnect_output_t)
} ewlm_disconnect_output_t;

/*
ewlm_disconnect() ends the connection established by ewlm_connect().
The EWLM agent calls this function before it shuts down.  Nevertheless the
platform must handle the case when the EWLM agent fails and does not call
ewlm_disconnect().  The platform must either be notified of the termination of
the EWLM agent process so that it can delete the connection information, or it
must be able to recognize in a subsequent ewlm_connect() call that the existing
connection information refers to a process that no longer exists.

ewlm_disconnect() performs the following cleanup:
- The ARM implementation's copy of any committed service policy is unaffected.
- The platform's copy of any committed service policy, if any, is either
  discarded or kept at the sole discretion of the platform.
- Completion records returned via the get_completions interface need not be
  collected any longer, and any OS-owned buffers for them may be freed.
*/

/*
 *  Signature:
 *              EWLM Disconnect
 */

ewlm_status_t ewlm_disconnect(
    /* [in]  */ ewlm_disconnect_input_t    *input_buffer,
    /* [in]  */ ewlm_bytelength_t          input__buffer_size,
    /* [i/o] */ ewlm_disconnect_output_t   *output_buffer,
    /* [in]  */ ewlm_bytelength_t          output_buffer_size
);

/*
    Required Return codes:
       0    EWLM_SUCCESS
    -100    EWLM_NO_CONNECTION
    -215    EWLM_OUTBUFFER_BELOW_V1SIZE
    -216    EWLM_OUTBUFFER_TOO_SMALL
    -218    EWLM_INBUFFER_BELOW_V1SIZE
    -219    EWLM_INBUFFER_TOO_SMALL
    -222    EWLM_SUPPORT_NOT_ENABLED

    Optional Return codes:
    -101    EWLM_BAD_CONNECT_HANDLE
    -205    EWLM_MISSING_PARM
    -212    EWLM_BAD_IN_BUFFER
    -213    EWLM_BAD_OUTBUFFER
 */

/* ------------------------------------------------------------------------- */
/* --------------------------- sampling services --------------------------- */
/* ------------------------------------------------------------------------- */


/*
ewlm_collect_samples() causes state sampling to occur on the local image (IBM
platforms only...enforcement layer calls implement sampling on other platforms).

The implementation is platform-dependent.  EWLM requires that the sampling
output data gives the appearance that state sampling was triggered by this
call, regardless of the underlying platform implementation.

In other words, if a single-threaded process existed during an interval where
this interface was called three times, EWLM would expect to see three state
samples on average over the same interval returned as part of process metrics
on ewlm_get_activedata and/or ewlm_get_completions.

Functions currently supported by the command parameter:
Collect_now
    Called on the fine-grained sampling interval to trigger a single sampling
    cycle (all work supported by the sampler is sampled).  Some platforms sample
    both in-flight processes and ARM transactions as a result of this call,
    others sample only ARM transactions.
    The output buffer is not used by this request.

*/


typedef struct ewlm_collect_samples_collect_now_input
{
    ewlm_APIversion_t          version;
    ewlm_int32_t                    request_type;
#define EWLM_COLLECT_SAMPLES_REQUEST_COLLECT_NOW  (1)

    ewlm_connect_handle_t      connect_handle;
    /* ------- end of data present in version 1        */
    #define EWLM_COLLECT_SAMPLES_COLLECT_NOW_IN_VERSION001     (1)
    #define EWLM_COLLECT_SAMPLES_COLLECT_NOW_INPUT_V001SIZE \
        sizeof(ewlm_collect_samples_collect_now_input_t)
} ewlm_collect_samples_collect_now_input_t;

typedef struct ewlm_collect_samples_collect_now_output
{
    ewlm_APIversion_t          version;
    ewlm_bytelength_t          sizeneeded;
     /* ------- end of data present in version 1 */
    #define EWLM_COLLECT_SAMPLES_COLLECT_NOW_OUTVERSION001  (1)
    #define EWLM_COLLECT_SAMPLES_COLLECT_NOW_OUTPUT_V001SIZE \
        sizeof(ewlm_collect_samples_collect_now_output_t)
} ewlm_collect_samples_collect_now_output_t;

ewlm_status_t ewlm_collect_samples(
    /* [in]  */ ewlm_char_t                       *input_buffer,
    /* [in]  */ ewlm_bytelength_t          input__buffer_size,
    /* [i/o] */ ewlm_char_t                       *output_buffer,
    /* [in]  */ ewlm_bytelength_t          output_buffer_size
);

/*
    Required Return codes:
       0    EWLM_SUCCESS
    -100    EWLM_NO_CONNECTION
    -101    EWLM_BAD_CONNECT_HANDLE
    -214    EWLM_UNSUPPORTED_REQUEST_TYPE
    -215    EWLM_OUTBUFFER_BELOW_V1SIZE
    -216    EWLM_OUTBUFFER_TOO_SMALL
    -218    EWLM_INBUFFER_BELOW_V1SIZE
    -219    EWLM_INBUFFER_TOO_SMALL
    -222    EWLM_SUPPORT_NOT_ENABLED

    Optional Return codes:
    -205    EWLM_MISSING_PARM
    -212    EWLM_BAD_IN_BUFFER
    -213    EWLM_BAD_OUTBUFFER
*/



/*
ewlm_get_appldata() returns data about a given application instance ID.
The EWLM agent calls this function the first time it sees a given application
instance ID returned by ewlm_get_completions() or ewlm_get_activedata().
Note that the EWLM agent does not harden these definitions so it will ask for
them again each time it is started.

It is possible that an instrumented application could start, run one or
more transactions, and then terminate before EWLM gets any of its
transaction completion records via ewlm_get_completions() or in-flight data
via ewlm_get_activedata().  If the platform simply deletes the definition
of the application as soon as it terminates, then EWLM will get
transaction completion records for an application instance ID which it
would not be able to resolve via ewlm_get_appldata().
In order to deal with this problem, the platform should not delete the
definition of the application unless EWLM has retrieved it via
ewlm_get_appldata() or the application has terminated and the ARM
implementation has written the corresponding AEID/AIID invalidation
records to the get_completions record buffer.
*/

typedef struct ewlm_get_appldata_input
{
    ewlm_APIversion_t          version;
    ewlm_applinst_id_t         applInstanceId;
    ewlm_connect_handle_t      connect_handle;
    /* ------- end of data present in version 1 */
    #define EWLM_GET_APPLDATA_IN_VERSION001     (1)
    #define EWLM_GET_APPLDATA_INPUT_V001SIZE sizeof(ewlm_get_appldata_input_t)
} ewlm_get_appldata_input_t;

typedef struct ewlm_get_appldata_output
{
    ewlm_APIversion_t          version;
    ewlm_bytelength_t          sizeneeded;
    ewlm_applenv_id_t          application_environment_id;/* ARM implementation-
                                assigned application environment ID,
                                unique ID for combination of ARM appl name and
                                group name */
    ewlm_process_id_t          process_id;/*
                                Opaque platform-dependent process identifier.
                                Must match the value returned to the EWLM agent
                                on the sampling interfaces (ewlm_get_activedata,
                                ewlm_get_completions) for the same process. */

    ewlm_encodedbytestream_t   process_name;/*
                                Printable version of a platform-dependent process
                                identifier that would be recognized by humans.
                                */
    ewlm_encodedbytestream_t   application_name;/* specified on
                                arm_register_application API */
    ewlm_encodedbytestream_t   application_group_name;/* specified on
                                arm_start_application API */
    ewlm_encodedbytestream_t   application_instance_name;/* specified on
                                arm_start_application API */
    /* ------- end of data present in version 1 */
    #define EWLM_GET_APPLDATA_OUTVERSION001  (1)
    #define EWLM_GET_APPLDATA_OUTPUT_V001SIZE sizeof(ewlm_get_appldata_output_t)
} ewlm_get_appldata_output_t;
/*
 * In storage, this buffer should be immediately followed by the contents of the
 * data described by the ewlm_encodedbytestream_t components.  All offsets in
 * these components are relative to the beginning of the
 * ewlm_get_appldata_output structure.
 */

ewlm_status_t ewlm_get_appldata(
    /* [in]  */ ewlm_get_appldata_input_t      *input_buffer,
    /* [in]  */ ewlm_bytelength_t              input__buffer_size,
    /* [i/o] */ ewlm_get_appldata_output_t     *output_buffer,
    /* [in]  */ ewlm_bytelength_t              output_buffer_size
);

/*
    Required Return codes:
       0    EWLM_SUCCESS
    -100    EWLM_NO_CONNECTION
    -211    EWLM_INVALID_TOKEN
    -215    EWLM_OUTBUFFER_BELOW_V1SIZE
    -216    EWLM_OUTBUFFER_TOO_SMALL
    -218    EWLM_INBUFFER_BELOW_V1SIZE
    -219    EWLM_INBUFFER_TOO_SMALL
    -221    EWLM_AIID_NOT_FOUND
    -222    EWLM_SUPPORT_NOT_ENABLED

    Optional Return codes:
    -101    EWLM_BAD_CONNECT_HANDLE
 */


/*
ewlm_ARM_message_correlation_output_t is an additional structure to
record message correlation information in the get_activedata and
get_completions records for transactions. Several of these structures
(up to ARM_MESSAGE_RCVD_EVENT_MAX_COUNT - see ARM 4.1 standard) can
be present in one record. The number, offset and length of the
ewlm_ARM_message_correlation_output_t records is stored in the
messages_correlation_count/offset/length fields of the conatining
get_activedata or get_completions transaction records
*/
typedef struct ewlm_ARM_message_correlation_output
{
/* Message originator identity */
    ewlm_applenv_id_t            msgcorr_applenv_id; /* AEID */
    ewlm_applinst_id_t           msgcorr_applinst_id;/* AIID */
    ewlm_local_server_id_t       parent_sys_id;      /* SysId*/
/* Message originator hop count */
    ewlm_hopcount_t              hop_count;
/* Message originator transaction class */
    ewlm_classification_id_t     reporting_id;
/* Correlation flags */
    ewlm_msg_correlation_flags_t flags;
} ewlm_ARM_message_correlation_output_t;


/*
ewlm_get_activedata() collects data about in-flight ARM transactions (all
platforms) and processes (IBM platforms).  It is called at the end of each
coarse-grained sampling interval to collect the in-flight data as well as any
metrics sampled during the just-ended coarse-grained sampling interval.
Metrics data may be returned
either in delta mode or total mode, as communicated on an earlier ewlm_query
ResourceMetricsCollected.

If the buffer is not sufficiently large to contain all of the data,
only the portion which will fit is returned and a cursor is returned which
allows the caller to re-invoke the service to collect more of the data.
An end of data record is returned for each call to signal the last record
which fit in the output buffer; only the return code may be used by the caller
to decide whether or not more data is immediately available.

This interface is serially reusable with respect to restarts
(only one restart cursor is saved).  If a restart cursor has been saved and
a new request (not a continue at restart point request) comes in the saved
restart point is lost.

Supported Request Types

PROCESSES_AND_TRANSACTIONS_START
    Synchronously return as much of the process and ARM transaction    data as
    fits in the buffer provided, starting from the beginning of the set of all
    in-flight work.  The value in the cursor parameter is ignored.
PROCESSES_AND_TRANSACTIONS_CONTINUE
    Synchronously return as much of the process and ARM transaction    data as
    fits in the buffer provided, starting from point where the prior START
    request ended.  The value in the cursor parameter contains the restart
    point; this value was set by the platform on the previous START/CONTINUE
    call which returned the "more data available" return code.
    If the cursor is invalid, the platform must select one of two possible
    behaviors:
    - If the platform's cursor implementation is such that its value cannot
      become invalid (e.g. due to timing, process or transaction completion)
      then this condition signals a bug on the part of the caller and return
      code EWLM_INVALID_TOKEN should be used.
    - If the platform's cursor implementation is such that its value can
      become invalid (e.g. due to timing, process or transaction completion)
      and the platform has no way to distinguish the cursor becoming stale
      from a bug in the API caller, then the API implementation should restart
      from the beginning (as if _START had been requested).  No indication of
      this is provided to the caller.
*/

typedef struct ewlm_get_activedata_input
{
    ewlm_APIversion_t          version;
    ewlm_int32_t                    request_type;
#define EWLM_GET_ACTIVEDATA_REQUEST_PROCESSES_AND_TRANSACTIONS_START     (1)
#define EWLM_GET_ACTIVEDATA_REQUEST_PROCESSES_AND_TRANSACTIONS_CONTINUE  (2)

    ewlm_connect_handle_t      connect_handle;
    ewlm_get_activedata_cursor_t cursor;/*
                                 Opaque value used to continue an earlier
                                 request when the buffer is too small to hold
                                 all of the data.  */
    /* ------- end of data present in version 1 */
    #define EWLM_GET_ACTIVEDATA_IN_VERSION001     (1)
    #define EWLM_GET_ACTIVEDATA_IN_V001SIZE sizeof(ewlm_get_activedata_input_t)
} ewlm_get_activedata_input_t;

ewlm_status_t ewlm_get_activedata(
    /* [in]  */ ewlm_get_activedata_input_t     *input_buffer,
    /* [in]  */ ewlm_bytelength_t               input__buffer_size,
    /* [i/o] */ ewlm_char_t                            *output_buffer,
    /* [in]  */ ewlm_bytelength_t               output_buffer_size
);

/*
    Required Return codes:
       0    EWLM_SUCCESS
       1    EWLM_MORE_DATA
    -100    EWLM_NO_CONNECTION
    -215    EWLM_OUTBUFFER_BELOW_V1SIZE
    -218    EWLM_INBUFFER_BELOW_V1SIZE
    -219    EWLM_INBUFFER_TOO_SMALL
    -222    EWLM_SUPPORT_NOT_ENABLED

    Optional Return codes:
    -101    EWLM_BAD_CONNECT_HANDLE
    -213    EWLM_BAD_OUTBUFFER
    -205    EWLM_MISSING_PARM
    -212    EWLM_BAD_IN_BUFFER
 */

typedef struct ewlm_generic_header
{
    ewlm_uint16_t                   type;    /* Record type */
    ewlm_uint16_t                   length;  /* Length of record in bytes */
    ewlm_uint16_t                   version; /* within type, increment with each
                                            compatible change */
    ewlm_uint16_t                   _reserved1;  /* 8 byte size & alignment */
/* THIS RECORD MAY *NEVER* BE EXPANDED
 * Doing so would cause an incompatible change (new offsets) in all records
 */
} ewlm_generic_header_t;


typedef struct ewlm_get_activedata_inflight_process_output
{
    ewlm_generic_header_t      header;
    #define EWLM_GET_ACTIVEDATA_INFLIGHT_PROCESSES_TYPE         (001)
    ewlm_process_id_t          pid;
    ewlm_cpu_time_t            cpu_time; /* metric */
/* Generic in-flight data */
    ewlm_timestamp_t           classify_time;
/* Generic transaction/process data */
    ewlm_duration_t            queue_time;
/* Metrics */
    ewlm_num_samples_t         times_sampled;
    ewlm_state_sample_t        cpu_using;
    ewlm_state_sample_t        cpu_delay;
    ewlm_state_sample_t        page_delay;
    ewlm_state_sample_t        io_delay;
    ewlm_state_sample_t        idle;
    ewlm_state_sample_t        other;
/* Generic in-flight data */
    ewlm_get_activedata_flags_t  flags;
/* Reporting aggregation data - all work types */
    ewlm_classification_id_t   reporting_id;
    ewlm_period_t              period_number;
    /* ------- end of data present in version 1 */
    #define EWLM_GET_ACTIVEDATA_INFLIGHT_PROCESSES_VERSION001     (1)
/* microsecond transaction/process data */
    ewlm_micro_duration_t      queue_time_microsec;
    /* ------- end of data present in version 2 */
    #define EWLM_GET_ACTIVEDATA_INFLIGHT_PROCESSES_VERSION002     (2)
    #define EWLM_GET_ACTIVEDATA_INFLIGHT_PROCESSES_V002SIZE_USED \
     (offsetof(ewlm_get_activedata_inflight_process_output_t, \
     queue_time_microsec) + sizeof(ewlm_micro_duration_t))
    #define EWLM_GET_ACTIVEDATA_INFLIGHT_PROCESSES_V002SIZE \
        EWLM_MAX(EWLM_GET_ACTIVEDATA_INFLIGHT_PROCESSES_V001SIZE, \
            EWLM_GET_ACTIVEDATA_INFLIGHT_PROCESSES_V002SIZE_USED)

    ewlm_int64_t    management_id;        /*  Represents the class ID of the
                                              local WLM class created for
                                              EWLM service class and DISP. */
 
    ewlm_cpu_time_t              scaled_cpu_time; /* F32148 DCR24
                                                     Scaled microseconds 
                                                     of CPU time consumed
                                                     by the work being measured. */
    ewlm_get_activedata_flags_t  flagsv3;  /* v3 flags field               */  	
    /* ------- end of data present in version 3 */
    #define EWLM_GET_ACTIVEDATA_INFLIGHT_PROCESSES_VERSION003         (3)
    #define EWLM_GET_ACTIVEDATA_INFLIGHT_PROCESSES_V003SIZE_USED \
    (offsetof(ewlm_get_activedata_inflight_process_output_t, \
      flagsv3) + sizeof(ewlm_get_activedata_flags_t))
    #define EWLM_GET_ACTIVEDATA_INFLIGHT_PROCESSES_V003SIZE \
        EWLM_MAX(EWLM_GET_ACTIVEDATA_INFLIGHT_PROCESSES_V002SIZE, \
            EWLM_GET_ACTIVEDATA_INFLIGHT_PROCESSES_V003SIZE_USED)
} ewlm_get_activedata_inflight_process_output_t;

/*
 * Get Active Data Inflight ARM partially Instrumented Output
 */
typedef struct ewlm_get_activedata_inflight_ARM_partially_instrumented_output
{
/* header.length contains the length of all embedded
   ewlm_ARM_message_correlation_output sections that are potentially
   included in this record, so header.length is basically
   EWLM_GET_ACTIVEDATA_INFLIGHT_PARTIALINSTARM_V00xSIZE +
     (message_correlation_length * messages_correlation_count)
   and messages_correlation_offset will be usually (except alignment)
   be equal to EWLM_GET_ACTIVEDATA_INFLIGHT_PARTIALINSTARM_V00xSIZE
*/
    ewlm_generic_header_t      header;
    #define EWLM_GET_ACTIVEDATA_INFLIGHT_PARTIALINSTARM_TYPE         (003)
    #define EWLM_GET_ACTIVEDATA_INFLIGHT_PARTIALINSTARM_TYPE_ASYNC   (005)
/* ARM transaction identity */
    ewlm_applinst_id_t         appl_inst_id;    /* application instance ID */
/* Parent ARM transaction identity */
    ewlm_applenv_id_t          parent_applenv_id;   /* AEID */
    ewlm_applinst_id_t         parent_applinst_id;  /* AIID */
/* Generic in-flight data */
    ewlm_timestamp_t           classify_time;
/* Generic transaction/process data */
    ewlm_duration_t            queue_time;
/* Generic ARM transaction data */
    ewlm_duration_t            blocked_time;
/* Generic in-flight data */
    ewlm_get_activedata_flags_t  flags;
/* Parent ARM transaction identity */
    ewlm_local_server_id_t     parent_sys_id;       /* System ID */
/* Reporting aggregation data - ARM work only */
    ewlm_hopcount_t                 hop_count;
/* Reporting aggregation data - all work types */
    ewlm_classification_id_t   reporting_id;
    ewlm_period_t              period_number;
    /* ------- end of data present in version 1 */
    #define EWLM_GET_ACTIVEDATA_INFLIGHT_PARTIALINSTARM_VERSION001     (1)
/* microsecond transaction/process data */
    ewlm_micro_duration_t      queue_time_microsec;
/* microsecond ARM transaction data */
    ewlm_micro_duration_t      blocked_time_microsec;
    /* ------- end of data present in version 2 */
    #define EWLM_GET_ACTIVEDATA_INFLIGHT_PARTIALINSTARM_VERSION002     (2)
    #define EWLM_GET_ACTIVEDATA_INFLIGHT_PARTIALINSTARM_V002SIZE_USED \
     (offsetof(ewlm_get_activedata_inflight_ARM_partially_instrumented_output_t, \
      blocked_time_microsec) + sizeof(ewlm_micro_duration_t))
    #define EWLM_GET_ACTIVEDATA_INFLIGHT_PARTIALINSTARM_V002SIZE \
	    (EWLM_MAX(EWLM_GET_ACTIVEDATA_INFLIGHT_PARTIALINSTARM_V001SIZE, \
		EWLM_GET_ACTIVEDATA_INFLIGHT_PARTIALINSTARM_V002SIZE_USED))

/* Arrival delay time.  This is the number of microseconds that have elapsed
    from the E2E transaction's edge arrival time until the captured arrival
    time at this reported hop.  This field is valid only if the
    EWLM_GET_ACTIVEDATA_ARRIVAL_DELAY flag is true. */
    ewlm_arrival_delay_duration_t   arrival_delay_time;
/* Number of messages sent */
    ewlm_tranevent_count_t      messages_sent_count;
/* Messages received count */
    ewlm_tranevent_count_t      messages_received_count;
/* Blocked instances due to awaiting message or message response */
    ewlm_tranevent_count_t      blocked_msgwait_count;
/* Total blocked instances count */
    ewlm_tranevent_count_t      total_blocked_instance_count;
/* Messages received correlation count */
    ewlm_tranevent_count_t      messages_correlation_count;
/* Offset to post-start messages received correlation information.
   This offset is defined to be the number of bytes from the beginning
   of this active transaction record.
   Received message correlation information for an active transaction
   instance is provided in the record buffer included in its associated
   active transaction record.
   This field is ignored if messages_correlation_count is zero*/
    ewlm_int16_t      messages_correlation_offset;
/* Length of one message received correlation information. This length
   is defined to be the number of bytes consumed by one received
   message.  This field is ignored by data collection if
   messages_correlation_count is zero. */
    ewlm_int16_t      messages_correlation_length;
    ewlm_get_activedata_flags_t  flagsv3;  /* v3 flags field     */
/* ------- end of data present in version 3 */
    #define EWLM_GET_ACTIVEDATA_INFLIGHT_PARTIALINSTARM_VERSION003 (3)
    #define EWLM_GET_ACTIVEDATA_INFLIGHT_PARTIALINSTARM_V003SIZE_USED \
      (offsetof(ewlm_get_activedata_inflight_ARM_partially_instrumented_output_t, \
      flagsv3) + sizeof(ewlm_get_activedata_flags_t))
    #define EWLM_GET_ACTIVEDATA_INFLIGHT_PARTIALINSTARM_V003SIZE \
      MAXVERSIONSIZE(EWLM_GET_ACTIVEDATA_INFLIGHT_PARTIALINSTARM_V002SIZE, \
      EWLM_GET_ACTIVEDATA_INFLIGHT_PARTIALINSTARM_V003SIZE_USED)

} ewlm_get_activedata_inflight_ARM_partially_instrumented_output_t;

/*
 * Get Active Data End of Data Output
 */

typedef struct ewlm_get_activedata_endofdata_output
{
    ewlm_generic_header_t        header;
    #define EWLM_GET_ACTIVEDATA_ENDOFDATA_TYPE                        (99)
    ewlm_get_activedata_cursor_t cursor;    /* Opaque value used to continue
                                            an earlier request when the buffer
                                            is too small to hold all of the
                                            data.  */

    /* ------- end of data present in version 1 */
    #define EWLM_GET_ACTIVEDATA_ENDOFDATA_VERSION001                   (1)
    #define EWLM_GET_ACTIVEDATA_ENDOFDATA_V001SIZE \
        offsetof(ewlm_get_activedata_endofdata_output_t,flags)

    ewlm_int32_t                    flags;
            /* A time change occurred which the underlying implementation
             * believes might impact reported elapsed time values or data
             * based on elapsed times.  Platforms which can detect this
             * communicate it to the caller for diagnostic purposes, i.e. to
             * allow the caller to propagate the suspicious nature of the
             * data along with a likely cause.  No specificity is provided as
             * to which values might be suspect at run time, because in
             * aggregate they are unpredictable.  In cases where elapsed times
             * are returned to the caller, the platform may choose any
             * combination of using defined overflow bits to flag specific
             * fields, returning a maximum value as the elapsed time, and
             * returning zero as the elapsed time.
             * Detection of this condition is optional, and not all possible
             * cases are necessarily detected on any given platform for
             * performance reasons.
             * If version 1 of this struct is returned,
             * this bit is assumed to be off. */
    #define EWLM_GET_ACTIVEDATA_ELAPSED_TIMES_SUSPECT             (0x40000000)

    /* ------- end of data present in version 2 */
    #define EWLM_GET_ACTIVEDATA_ENDOFDATA_VERSION002                   (2)
    #define EWLM_GET_ACTIVEDATA_ENDOFDATA_V002SIZE \
        sizeof(ewlm_get_activedata_endofdata_output_t)
} ewlm_get_activedata_endofdata_output_t;

/*
ewlm_get_completions() extracts statistics for ARM transactions and processes
that have completed since the last time it was called.

If the output buffer is not sufficiently large to contain all of the data,
only the portion which will fit is returned and a return code signals
the caller to re-invoke the service to collect more of the data.
An end of data record is returned for each call to signal the last record
which fit in the output buffer; only the return code may be used by the caller
to decide whether or not more data is immediately available.

Supported Commands

SYNCHRONOUS
    Synchronously return as much of the data as fits in the buffer provided.
WAIT
    Return to the caller when the first of the following conditions is true:
    1.    the caller-specified timeout expires (see timeout parameter)
    2.    enough transactions have completed to fill the caller's buffer
    3.    the platform's completion buffer has reached an internal threshold
        (e.g. 50% full)
    4.    the wait is cancelled by using the CANCEL_WAIT command
    Only a single caller can be waiting at any given time.  If a caller is
    waiting and a second WAIT call arrives, the second call is rejected with
    return code EWLM_GETCOMPLETIONS_SECOND_WAITER.
CANCEL_WAIT
    If any callers are suspended in a WAIT request, they should be immediately
    resumed.  The platform returns all completion records accumulated so far
    to the canceller (not the waiter).  The waiter, if any exists, receives
    a normal completion code and an end_of_buffer record.  Since only the
    called API can guarantee sufficient serialization, it is not an error to
    attempt to cancel a wait when no waiters exist.
    For example the EWLM agent will use this form of the invocation in the
    policy management component to finish its bookkeeping before switching
    to a new active service policy.

Lost record counts:
the EWLM agent depends upon seeing all completion records
in order to keep the bookkeeping data correct.  In particular, if AEID/AIID
invalidation records are lost the agent might have to restart bookkeeping in
order to solve all the potential problems.  Total_lost-(ARM_lost+process_lost)
tells the agent whether or not any such records might have been lost; the
overall total gives the agent a quick way to check that all the data is fine.
*/

/*
 * Completed transactions and processes Input
 */


typedef struct ewlm_get_completions_input
{
    ewlm_APIversion_t          version;
    ewlm_int32_t                    timeout;/*
                               Maximum amount of time the caller is willing to
                               be suspended,in millisecond units. The value
                               specified must be between 1 (1 ms) and 600,000
                               (10 minutes) inclusive */
    ewlm_int32_t                    request_type;
    #define EWLM_GET_COMPLETIONS_REQUEST_SYNCHRONOUS        (1)
    #define EWLM_GET_COMPLETIONS_REQUEST_WAIT               (2)
    #define EWLM_GET_COMPLETIONS_REQUEST_CANCEL_WAIT        (3)

    ewlm_connect_handle_t      connect_handle;
    /* ------- end of data present in version 1 */
    #define EWLM_GET_COMPLETIONS_IN_VERSION001              (1)
    #define EWLM_GET_COMPLETIONS_IN_V001SIZE \
        sizeof(ewlm_get_completions_input_t)
} ewlm_get_completions_input_t;

ewlm_status_t ewlm_get_completions(
    /* [in]  */ ewlm_get_completions_input_t *input_buffer,
    /* [in]  */ ewlm_bytelength_t            input__buffer_size,
    /* [i/o] */ ewlm_char_t                         *output_buffer,
    /* [in]  */ ewlm_bytelength_t            output_buffer_size
);

/*
    Required Return codes:
       0    EWLM_SUCCESS
       1    EWLM_MORE_DATA
    -100    EWLM_NO_CONNECTION
    -202    EWLM_BAD_TIMEOUT
    -204    EWLM_GETCOMPLETIONS_SECOND_WAITER
    -214    EWLM_UNSUPPORTED_REQUEST_TYPE
    -215    EWLM_OUTBUFFER_BELOW_V1SIZE
    -218    EWLM_INBUFFER_BELOW_V1SIZE
    -219    EWLM_INBUFFER_TOO_SMALL
    -222    EWLM_SUPPORT_NOT_ENABLED

    Optional Return codes:
    -101    EWLM_BAD_CONNECT_HANDLE
    -205    EWLM_MISSING_PARM
    -212    EWLM_BAD_IN_BUFFER
    -213    EWLM_BAD_OUTBUFFER
*/


typedef struct ewlm_get_completions_process_output
{
/* header.length contains the length of all embedded
   ewlm_ARM_message_correlation_output sections that are potentially
   included in this record, so header.length is basically
   EWLM_GET_COMPLETIONS_PARTIALINSTARM_V00xSIZE +
     (message_correlation_length * messages_correlation_count)
   and messages_correlation_offset will be usually (except alignment)
   be equal to EWLM_GET_COMPLETIONS_PARTIALINSTARM_V00xSIZE
*/
    ewlm_generic_header_t      header;
    #define EWLM_GET_COMPLETIONS_PROCESSES_TYPE                  (101)
    ewlm_process_id_t          pid;
    ewlm_cpu_time_t            cpu_time; /* Metric */
/* Generic transaction/process data */
    ewlm_duration_t            queue_time;
/* Generic completion transaction/process data */
    ewlm_duration_t            response_time;
/* Metrics */
    ewlm_num_samples_t         times_sampled;
    ewlm_state_sample_t        cpu_using;
    ewlm_state_sample_t        cpu_delay;
    ewlm_state_sample_t        page_delay;
    ewlm_state_sample_t        io_delay;
    ewlm_state_sample_t        idle;
    ewlm_state_sample_t        other;
/* Generic transaction completion data */
    ewlm_get_completions_flags_t flags;
/* Reporting aggregation data - all work types */
    ewlm_classification_id_t   reporting_id;
    ewlm_period_t              period_number;

    /* ------- end of data present in version 1 */
    #define EWLM_GET_COMPLETIONS_PROCESSES_VERSION001              (1)
/* microsecond transaction/process data */
    ewlm_micro_duration_t       queue_time_microsec;
/* microsecond completion transaction/process data */
    ewlm_micro_duration_t       response_time_microsec;

    /* ------- end of data present in version 2 */
    #define EWLM_GET_COMPLETIONS_PROCESSES_VERSION002              (2)
    #define EWLM_GET_COMPLETIONS_PROCESSES_V002SIZE_USED \
    (offsetof(ewlm_get_completions_process_completion_output_t, \
     response_time_microsec) + sizeof(ewlm_micro_duration_t))
    #define EWLM_GET_COMPLETIONS_PROCESSES_V002SIZE \
	EWLM_MAX(EWLM_GET_COMPLETIONS_PROCESSES_V001SIZE, \
             EWLM_GET_COMPLETIONS_PROCESSES_V002SIZE_USED)

    ewlm_int64_t    management_id;        /*  Represents the class ID of the
                                              local WLM class created for
                                              EWLM */
                                                  
    ewlm_cpu_time_t               scaled_cpu_time ;/* F32148 DCR24
                                                     Scaled microseconds 
                                                     of CPU time consumed
                                                     by the work being measured. */ 
    ewlm_get_completions_flags_t  flagsv3;  /* v3 flags field        */
    /* ------- end of data present in version 3 */
    #define EWLM_GET_COMPLETIONS_PROCESSES_VERSION003              (3)
    #define EWLM_GET_COMPLETIONS_PROCESSES_V003SIZE_USED \
    (offsetof(ewlm_get_completions_process_completion_output_t, \
      flagsv3) + sizeof(ewlm_get_completions_flags_t))
    #define EWLM_GET_COMPLETIONS_PROCESSES_V003SIZE \
        EWLM_MAX(EWLM_GET_COMPLETIONS_PROCESSES_V002SIZE, \
	    EWLM_GET_COMPLETIONS_PROCESSES_V003SIZE_USED)
} ewlm_get_completions_process_completion_output_t;

typedef struct ewlm_get_completions_ARM_partially_instrumented_output
{
    ewlm_generic_header_t      header;
    #define EWLM_GET_COMPLETIONS_PARTIALINSTARM_TYPE                (103)
    #define EWLM_GET_COMPLETIONS_PARTIALINSTARM_TYPE_ASYNC          (105)
/* ARM transaction identity */
    ewlm_applinst_id_t         appl_inst_id;    /* application instance ID */
/* Parent ARM transaction identity */
    ewlm_applenv_id_t          parent_applenv_id;   /* AEID */
    ewlm_applinst_id_t         parent_applinst_id;  /* AIID */
/* Generic transaction/process data */
    ewlm_duration_t            queue_time;
/* Generic ARM transaction data */
    ewlm_duration_t            blocked_time;
/* Generic completion data */
    ewlm_duration_t            response_time;
/* Generic ARM transaction completion data */
    ewlm_ARM_completion_status_t completion_status;
/* Generic transaction completion data */
    ewlm_get_completions_flags_t flags;
/* Parent ARM transaction identity */
    ewlm_local_server_id_t     parent_sys_id;       /* System ID */
/* Reporting aggregation data - ARM work only */
    ewlm_hopcount_t                 hop_count;
/* Reporting aggregation data - all work types */
    ewlm_classification_id_t   reporting_id;
    ewlm_period_t              period_number;
    /* ------- end of data present in version 1 */
    #define EWLM_GET_COMPLETIONS_PARTIALINSTARM_VERSION001            (1)
/* microsecond transaction/process data */
    ewlm_micro_duration_t      queue_time_microsec;
/* microsecond ARM transaction data */
    ewlm_micro_duration_t      blocked_time_microsec;
/*microsecond completion data */
    ewlm_micro_duration_t      response_time_microsec;
    /* ------- end of data present in version 2 */
    #define EWLM_GET_COMPLETIONS_PARTIALINSTARM_VERSION002            (2)
    #define EWLM_GET_COMPLETIONS_PARTIALINSTARM_V002SIZE_USED \
    (offsetof(ewlm_get_completions_ARM_partially_instrumented_output_t, \
     response_time_microsec) + sizeof(ewlm_micro_duration_t))
    #define EWLM_GET_COMPLETIONS_PARTIALINSTARM_V002SIZE \
	    (EWLM_MAX(EWLM_GET_COMPLETIONS_PARTIALINSTARM_V001SIZE, \
		EWLM_GET_COMPLETIONS_PARTIALINSTARM_V002SIZE_USED))

/* Arrival delay time.  This is the number of microseconds that have elapsed
    from the E2E transaction's edge arrival time until the captured arrival
    time at this reported hop.  This field is valid only if the
    EWLM_GET_COMPLETIONS_ARRIVAL_DELAY flag is true. */
    ewlm_arrival_delay_duration_t   arrival_delay_time;
/* Number of messages sent */
    ewlm_tranevent_count_t      messages_sent_count;
/* Messages received count */
    ewlm_tranevent_count_t      messages_received_count;
/* Blocked instances due to awaiting message or message response */
    ewlm_tranevent_count_t      blocked_msgwait_count;
/* Total blocked instances count */
    ewlm_tranevent_count_t      total_blocked_instance_count;
/* Post-start messages received correlation count */
    ewlm_tranevent_count_t      messages_correlation_count;
/* Offset to post-start messages received correlation information.
   This offset is defined to be the number of bytes from the beginning
   of this transaction completion record.
   Received message correlation information for an completed transaction
   instance is provided in the record buffer included in its associated
   transaction completion record.
   This field is ignored if messages_correlation_count is zero*/
    ewlm_int16_t      messages_correlation_offset;
/* Length of one message received correlation information. This length
   is defined to be the number of bytes consumed by one received
   message.  This field is ignored by data collection if
   messages_correlation_count is zero. */
    ewlm_int16_t      messages_correlation_length;
    ewlm_get_completions_flags_t  flagsv3;  /* v3 flags field         */
/* ------- end of data present in version 3 */
    #define EWLM_GET_COMPLETIONS_PARTIALINSTARM_VERSION003  (3)
    #define EWLM_GET_COMPLETIONS_PARTIALINSTARM_V003SIZE_USED \
      (offsetof(ewlm_get_completions_ARM_partially_instrumented_output_t, \
      flagsv3) + sizeof(ewlm_get_completions_flags_t))
    #define EWLM_GET_COMPLETIONS_PARTIALINSTARM_V003SIZE \
      MAXVERSIONSIZE(EWLM_GET_COMPLETIONS_PARTIALINSTARM_V002SIZE, \
      EWLM_GET_COMPLETIONS_PARTIALINSTARM_V003SIZE_USED)

} ewlm_get_completions_ARM_partially_instrumented_output_t;

typedef struct ewlm_get_completions_appl_instance_id_termination_output
{
    ewlm_generic_header_t      hdr;
    #define EWLM_GET_COMPLETIONS_AIID_INVALID_TYPE                  (201)
    ewlm_applinst_id_t         appl_inst_id;
    /* ------- end of data present in version 1 */
    #define EWLM_GET_COMPLETIONS_AIID_VERSION001                      (1)
    #define EWLM_GET_COMPLETIONS_AIID_V001SIZE \
        offsetof(ewlm_get_completions_appl_instance_id_termination_output_t,\
flags)

    ewlm_int32_t                   flags;
    #define EWLM_GET_COMPLETIONS_AIID_INVALID_APPLDATA        (0x40000000) /*
                                          Version 2 data is present.  If this\
                                          flag is on, the version 2 data \
                                          from AEID forward contains no\
                                          predictable content and should \
                                          not be used by the EWLM agent */
    ewlm_applenv_id_t          application_environment_id;/* ARM
                                implementation assigned AEID */
    ewlm_process_id_t          process_id;/* Opaque platform dependent
                                process identifier */
    ewlm_encodedbytestream_t   process_name;/* Printable version of a
                                platform dependent process identifier
                                that would be recognized by humans */
    ewlm_encodedbytestream_t   application_name;/* specified on
                                arm_register_application API */
    ewlm_encodedbytestream_t   application_group_name;/* specified on
                                arm_start_application API */
    ewlm_encodedbytestream_t   application_instance_name;/* specified on
                                arm_start_application API */
    /* ------- end of data present in version 2 */
    #define EWLM_GET_COMPLETIONS_AIID_VERSION002                      (2)
    #define EWLM_GET_COMPLETIONS_AIID_V002SIZE \
        sizeof(ewlm_get_completions_appl_instance_id_termination_output_t)
    } ewlm_get_completions_appl_instance_id_termination_output_t;

typedef struct ewlm_get_completions_appl_environment_id_termination_output
{
    ewlm_generic_header_t      hdr;
    #define EWLM_GET_COMPLETIONS_AEID_INVALID_TYPE                 (301)
    ewlm_applenv_id_t          appl_env_id;

    /* ------- end of data present in version 1 */
    #define EWLM_GET_COMPLETIONS_AEID_VERSION001                      (1)
    #define EWLM_GET_COMPLETIONS_AEID_V001SIZE \
        sizeof(ewlm_get_completions_appl_environment_id_termination_output_t)
} ewlm_get_completions_appl_environment_id_termination_output_t;

typedef struct ewlm_get_completions_endofdata_output
{
    ewlm_generic_header_t      header;
    #define EWLM_GET_COMPLETIONS_ENDOFDATA_TYPE                     (999)

    ewlm_int32_t                    lost_tran_count; /*
                                Total mode count of the number of transaction
                                completion records lost for any reason,
                                including wrap of the OS buffer */
    ewlm_int32_t                    lost_process_count; /*
                                Total mode count of the number of process
                                completion records lost for any reason,
                                including wrap of the OS buffer */
    ewlm_int32_t                    lost_total_count;/*
                                Total mode count of the total number of
                                completion records (all types) lost for any
                                reason, including wrap of the OS buffer. This
                                total INCLUDES the values in the two counts
                                above.  total-(process+trxn) = count of other
                                record types, like AIID/AEID termination,
                                which have been lost.  */
    /* ------- end of data present in version 1 */
    #define EWLM_GET_COMPLETIONS_ENDOFDATA_VERSION001                 (1)
    #define EWLM_GET_COMPLETIONS_ENDOFDATA_V001SIZE \
        sizeof(ewlm_get_completions_endofdata_output_t)
}    ewlm_get_completions_endofdata_output_t;

/* ------------------------------------------------------------------------- */
/* ------------------------- policy management services -------------------- */
/* ------------------------------------------------------------------------- */

/*
 *    Normal flow: policy activation
 *        -    prepare
 *        -    commit or abort
 *    Verify policy flow
 *        -    verify
 */

/*
ewlm_prepare_policy()
-    Signals the start of a policy activation sequence.
-    is passed a contiguous, self-describing policy data structure.
-    allows the platform to validate the policy structure is usable.
    It also allows the platform to build its own platform-specific
    policy-related data structures (though at present no such structures are
    required).
-    does NOT make the new policy structures active.
    The platform should continue to classify work according to the
    currently active policy if there is one.  The EWLM agent calls another
    function, ewlm_commit_policy(), when it is ready for the prepared policy
    to replace the active policy.  If ewlm_prepare_policy() is successful
    but an error occurs later in the policy activation sequence, the EWLM
    agent calls ewlm_abort_policy() to discard the prepared policy.

If for some reason the platform already has a prepared policy in storage when
the EWLM agent calls ewlm_prepare_policy(), the platform should simply discard
the previous prepared policy.  This can happen if:
-    ewlm_commit_policy() fails on the policy cross-check
    (see the description of ewlm_commit_policy()).
-    if the EWLM agent fails after preparing a policy, is
    subsequently restarted, and the platform's disconnect/reconnect logic does
    not purge the prepared policy as normally expected.

*/

typedef struct ewlm_prepare_policy_input
{
    ewlm_APIversion_t          version;
    ewlm_policytype_t          policy_type;
    #define EWLM_PREPARE_POLICY_SERVICE           (1)

    ewlm_unencodedbytestream_t policy;/* Policy to be operated upon */
    ewlm_connect_handle_t       connect_handle;

    /* ------- end of data present in version 1 */
    #define EWLM_PREPARE_POLICY_IN_VERSION001        (1)
    #define EWLM_PREPARE_POLICY_INPUT_V001SIZE \
        sizeof(ewlm_prepare_policy_input_t)
} ewlm_prepare_policy_input_t;

typedef struct ewlm_prepare_policy_output
{
    ewlm_APIversion_t          version;
    ewlm_bytelength_t          sizeneeded;
    /* ------- end of data present in version 1 */
    #define EWLM_PREPARE_POLICY_OUTVERSION001        (1)
    #define EWLM_PREPARE_POLICY_OUTPUT_V001SIZE \
        sizeof(ewlm_prepare_policy_output_t)
} ewlm_prepare_policy_output_t;

ewlm_status_t ewlm_prepare_policy(
    /* [in]  */ ewlm_char_t                        *input_buffer,
    /* [in]  */ ewlm_bytelength_t                  input__buffer_size,
    /* [i/o] */ ewlm_char_t                        *output_buffer,
    /* [in]  */ ewlm_bytelength_t                  output_buffer_size
);

/*
    Required Return codes:
       0    EWLM_SUCCESS
    -100    EWLM_NO_CONNECTION
    -117    EWLM_BAD_POLICY_TYPE
    -205    EWLM_MISSING_PARM
    -212    EWLM_BAD_IN_BUFFER
    -218    EWLM_INBUFFER_BELOW_V1SIZE
    -219    EWLM_INBUFFER_TOO_SMALL
    -222    EWLM_SUPPORT_NOT_ENABLED
    various EWLM_BAD_POLICY_xxxxx

    Optional Return codes:
    -101    EWLM_BAD_CONNECT_HANDLE
*/



/* --------------------------------------------------------------------------
ewlm_commit_policy()
-    causes the platform to make the prepared policy previously passed by
    ewlm_prepare_policy() be the active service policy.  The platform
    classifies new work according to this new policy.  Existing active ARM
    transactions remain classified according to the former policy and are
    not reclassified; platform processes are reclassified atomically using
    the new service policy.
-    deletes the platform's copy of the former service policy.  The platform is
    responsible for serializing the deletion with all the services which may
    be trying to classify work using those policy data structures.

The policy structure is passed to ewlm_commit_policy() to allow verification
that it is the same policy previously passed to ewlm_prepare_policy().  This
is most easily implemented as a bitwise comparison.
If it is not the same policy, ewlm_commit_policy() does not make the prepared
policy active and it returns a negative status code.  The prepared policy
structures remain in storage.  The caller can abort the policy activation
sequence by calling ewlm_abort_policy(), or start the policy activation
sequence over by calling ewlm_prepare_policy() again.
*/

typedef struct ewlm_commit_policy_input
{

    ewlm_APIversion_t          version;
    ewlm_policytype_t          policy_type;
    #define EWLM_COMMIT__POLICY_SERVICE           (EWLM_PREPARE_POLICY_SERVICE)

    ewlm_unencodedbytestream_t policy;/* Policy to be operated upon */
    ewlm_connect_handle_t      connect_handle;
    /* ------- end of data present in version 1 */
    #define EWLM_COMMIT_POLICY_IN_VERSION001             (1)
    #define EWLM_COMMIT_POLICY_INPUT_V001SIZE sizeof(ewlm_commit_policy_input_t)
} ewlm_commit_policy_input_t;

typedef struct ewlm_commit_policy_output
{
    ewlm_APIversion_t        version;
    ewlm_bytelength_t        sizeneeded;
    /* ------- end of data present in version 1 */
    #define EWLM_COMMIT_POLICY_OUTVERSION001        (1)
    #define EWLM_COMMIT_POLICY_OUTPUT_V001SIZE \
        sizeof(ewlm_commit_policy_output_t)
} ewlm_commit_policy_output_t;

ewlm_status_t ewlm_commit_policy(
    /* [in]  */ ewlm_char_t                         *input_buffer,
    /* [in]  */ ewlm_bytelength_t            input__buffer_size,
    /* [i/o] */ ewlm_char_t                         *output_buffer,
    /* [in]  */ ewlm_bytelength_t            output_buffer_size
);

/*
    Required Return codes:
       0    EWLM_SUCCESS
    -100    EWLM_NO_CONNECTION
    -101    EWLM_BAD_CONNECT_HANDLE
    -102    EWLM_BAD_POLICY
    -103    EWLM_NO_PREPARED_POLICY
    -104    EWLM_WRONG_POLICY
    -117    EWLM_BAD_POLICY_TYPE
    -218    EWLM_INBUFFER_BELOW_V1SIZE
    -219    EWLM_INBUFFER_TOO_SMALL
    -222    EWLM_SUPPORT_NOT_ENABLED

    Optional Return codes:
    various EWLM_BAD_POLICY_xxxxx
*/

/*
 * Abort Policy Inputs
 */

typedef struct ewlm_abort_policy_input
{
    ewlm_APIversion_t          version;
    ewlm_policytype_t          policy_type;
    #define EWLM_ABORT___POLICY_SERVICE           (EWLM_PREPARE_POLICY_SERVICE)

    ewlm_unencodedbytestream_t policy;
    ewlm_connect_handle_t      connect_handle;
        /* ------- end of data present in version 1 */
    #define EWLM_ABORT_POLICY_IN_VERSION001             (1)
    #define EWLM_ABORT_POLICY_INPUT_V001SIZE sizeof(ewlm_abort_policy_input_t)
} ewlm_abort_policy_input_t;

typedef struct ewlm_abort_policy_output
{
    ewlm_APIversion_t          version;
    ewlm_bytelength_t          sizeneeded;
    /* ------- end of data present in version 1 */
    #define EWLM_ABORT_POLICY_OUTVERSION001       (1)
    #define EWLM_ABORT_POLICY_OUTPUT_V001SIZE sizeof(ewlm_abort_policy_output_t)
} ewlm_abort_policy_output_t;

/* --------------------------------------------------------------------------
ewlm_abort_policy() causes the platform to delete its copy of the prepared
service policy.  The EWLM agent calls this function if it encounters some
error during the policy activation sequence after having called
ewlm_prepare_policy().
*/
ewlm_status_t ewlm_abort_policy(
    /* [in]  */ ewlm_char_t                         *input_buffer,
    /* [in]  */ ewlm_bytelength_t            input__buffer_size,
    /* [i/o] */ ewlm_char_t                         *output_buffer,
    /* [in]  */ ewlm_bytelength_t            output_buffer_size
);

/*
    Required Return codes:
       0    EWLM_SUCCESS
    -100    EWLM_NO_CONNECTION
    -117    EWLM_BAD_POLICY_TYPE
    -218    EWLM_INBUFFER_BELOW_V1SIZE
    -219    EWLM_INBUFFER_TOO_SMALL
    -222    EWLM_SUPPORT_NOT_ENABLED

    Optional Return codes:
    -101    EWLM_BAD_CONNECT_HANDLE
    -205    EWLM_MISSING_PARM
    -212    EWLM_BAD_IN_BUFFER
 */



/* --------------------------------------------------------------------------
ewlm_verify_policy() is identical to ewlm_prepare_policy() with two exceptions:
-    If there is an existing prepared service policy, ewlm_verify_policy() does
    not delete it.
-    ewlm_verify_policy() does not retain the service policy in storage for a
    subsequent commit or abort call.

The EWLM agent calls ewlm_verify_policy() to simulate as much of a policy
activation sequence as possible, to verify that an actual policy activation is
likely to be successful.  The EWLM agent can call ewlm_verify_policy() in
parallel to an actual end to end policy activation sequence, which is why the
EWLM agent cannot accomplish this function by reusing the ewlm_prepare_policy()
and ewlm_abort_policy() calls.  ewlm_verify_policy() must not affect the
operation of ewlm_prepare_policy(), ewlm_commit_policy(), or
ewlm_abort_policy().
*/

typedef struct ewlm_verify_policy_input
{
    ewlm_APIversion_t          version;
    ewlm_policytype_t          policy_type;
    #define EWLM_VERIFY__POLICY_SERVICE           (EWLM_PREPARE_POLICY_SERVICE)

    ewlm_unencodedbytestream_t policy;/* Policy to be operated upon */
    ewlm_connect_handle_t      connect_handle;
    /* ------- end of data present in version 1 */
    #define EWLM_VERIFY_POLICY_IN_VERSION001             (1)
    #define EWLM_VERIFY_POLICY_INPUT_V001SIZE sizeof(ewlm_verify_policy_input_t)
} ewlm_verify_policy_input_t;

typedef struct ewlm_verify_policy_output
{
    ewlm_APIversion_t          version;
    ewlm_bytelength_t          sizeneeded;
    /* ------- end of data present in version 1 */
    #define EWLM_VERIFY_POLICY_OUTVERSION001        (1)
    #define EWLM_VERIFY_POLICY_OUTPUT_V001SIZE \
        sizeof(ewlm_verify_policy_output_t)
} ewlm_verify_policy_output_t;

ewlm_status_t ewlm_verify_policy(
    /* [in]  */ ewlm_char_t                         *input_buffer,
    /* [in]  */ ewlm_bytelength_t            input__buffer_size,
    /* [i/o] */ ewlm_char_t                         *output_buffer,
    /* [in]  */ ewlm_bytelength_t            output_buffer_size
);

/*
    Required Return codes:
       0    EWLM_SUCCESS
    -100    EWLM_NO_CONNECTION
    -101    EWLM_BAD_CONNECT_HANDLE
    -117    EWLM_BAD_POLICY_TYPE
    -218    EWLM_INBUFFER_BELOW_V1SIZE
    -219    EWLM_INBUFFER_TOO_SMALL
    various EWLM_BAD_POLICY_xxxxx
    -222    EWLM_SUPPORT_NOT_ENABLED

    Optional Return codes:
    -205    EWLM_MISSING_PARM
    -212    EWLM_BAD_IN_BUFFER
 */

/* This is an additional value for transaction status.
 * The other possible transaction status values can
 * be found in arm4.h. They are prefixed with:
 * ARM_STATUS. Found in this file because it's not
 * part of the std.
 */
#define EWLM_ARM_STATUS_ABANDONED (-1)

/* ------------------------------------------------------------------------- */
/* ------------------------- local cpu management       -------------------- */
/* ------------------------------------------------------------------------- */

typedef struct ewlm_create_mgmtclass_output
{
    ewlm_APIversion_t          version;
    ewlm_bytelength_t          sizeneeded;
    ewlm_int64_t               management_id;
    /* ------- end of data present in version 1 */
    #define EWLM_CREATE_MGMTCLASS_OUTVERSION001  (1)
    #define EWLM_CREATE_MGMTCLASS_OUTPUT_V001SIZE  \
             sizeof(ewlm_create_mgmtclass_output_t)
} ewlm_create_mgmtclass_output_t;

typedef struct ewlm_create_mgmtclass_input
{
    ewlm_APIversion_t           version;
    ewlm_connect_handle_t       connect_handle;
    ewlm_encodedbytestream_t    service_class_name;
    ewlm_classification_id_t    service_class_id;
    ewlm_int32_t                tier;   /* Tier value for management class. 0
                                           when tier management is not
                                           available or does not fit with EWLM
                                           requirement. Not currently
                                           supported, should be set to 0. */
    ewlm_int32_t                cpu_shares;     /* CPU shares - ranges from
                                                   1 - 65535 */
    /* ------- end of data present in version 1 */
    #define EWLM_CREATE_MGMTCLASS_INVERSION001  (1)
    #define EWLM_CREATE_MGMTCLASS_INPUT_V001SIZE  \
             sizeof(ewlm_create_mgmtclass_input_t)
} ewlm_create_mgmtclass_input_t;

/*
     Required Return codes:

       0    EWLM_SUCCESS
    -100    EWLM_NO_CONNECTION
    -215    EWLM_OUTBUFFER_BELOW_V1SIZE
    -216    EWLM_OUTBUFFER_TOO_SMALL
    -218    EWLM_INBUFFER_BELOW_V1SIZE
    -219    EWLM_INBUFFER_TOO_SMALL
    -222    EWLM_SUPPORT_NOT_ENABLED
    -224    EWLM_LOCAL_WLM_NOT_ACTIVE
    -225    EWLM_LOCAL_WLM_PASSIVE
    -226    EWLM_MAX_MGMTCLASSES

    Optional Return codes:
    -101    EWLM_BAD_CONNECT_HANDLE
    -205    EWLM_MISSING_PARM
    -212    EWLM_BAD_IN_BUFFER
    -213    EWLM_BAD_OUTBUFFER
*/
ewlm_status_t ewlm_create_mgmtclass(
    /* [in]  */ ewlm_create_mgmtclass_input_t   *input_buffer,
    /* [in]  */ ewlm_bytelength_t               input_buffer_size,
    /* [i/o] */ ewlm_create_mgmtclass_output_t  *output_buffer,
    /* [in]  */ ewlm_bytelength_t               output_buffer_size);


typedef struct ewlm_change_mgmtclass_attribute_output
{
    ewlm_APIversion_t          version;
    ewlm_bytelength_t          sizeneeded;
    /* ------- end of data present in version 1 */
    #define EWLM_CHANGE_MGMTCLASS_ATTRIBUTE_OUTVERSION001  (1)
    #define EWLM_CHANGE_MGMTCLASS_ATTRIBUTE_OUTPUT_V001SIZE  \
             sizeof(ewlm_change_mgmtclass_attribute_output_t)
} ewlm_change_mgmtclass_attribute_output_t;

typedef struct ewlm_mgmtclass_attribute_list
{
    ewlm_int32_t               offset_first_entry;
    ewlm_int32_t               number_of_entries;
    ewlm_int32_t               length_of_entry;
} ewlm_mgmtclass_attribute_list_t;

typedef struct ewlm_change_mgmtclass_attribute_input
{
    ewlm_APIversion_t          version;
    ewlm_connect_handle_t      connect_handle;
    ewlm_int32_t               resource_type;

    #define EWLM_LOCAL_CPU_RESOURCES    (0x80000000)

    ewlm_mgmtclass_attribute_list_t     class_attribute_list;

    /* ------- end of data present in version 1 */
    #define EWLM_CHANGE_MGMTCLASS_ATTRIBUTE_INVERSION001  (1)
    #define EWLM_CHANGE_MGMTCLASS_ATTRIBUTE_INPUT_V001SIZE  \
             sizeof(ewlm_change_mgmtclass_attribute_input_t)
} ewlm_change_mgmtclass_attribute_input_t;

typedef struct ewlm_change_mgmtclass_attribute_entry
{
    ewlm_classification_id_t   service_class_id;
    ewlm_int32_t               shares;           /* Resource shares ranges
                                                    from 1 to 65535 */
}ewlm_change_mgmtclass_attribute_entry_t;

/*
    Required Return codes:
       0    EWLM_SUCCESS
    -100    EWLM_NO_CONNECTION
    -218    EWLM_INBUFFER_BELOW_V1SIZE
    -219    EWLM_INBUFFER_TOO_SMALL
    -222    EWLM_SUPPORT_NOT_ENABLED
    -224    EWLM_LOCAL_WLM_NOT_ACTIVE
    -225    EWLM_LOCAL_WLM_PASSIVE
    -228    EWLM_BAD_MANAGEMENT_ID


    Optional Return codes:
    -101    EWLM_BAD_CONNECT_HANDLE
    -205    EWLM_MISSING_PARM
    -212    EWLM_BAD_IN_BUFFER
*/
ewlm_status_t ewlm_change_mgmtclass_attribute(
    /* [in]  */ ewlm_change_mgmtclass_attribute_input_t  *input_buffer,
    /* [in]  */ ewlm_bytelength_t                        input_buffer_size,
    /* [i/o] */ ewlm_change_mgmtclass_attribute_output_t *output_buffer,
    /* [in]  */ ewlm_bytelength_t                        output_buffer_size);

typedef struct ewlm_reassign_mgmtclass_output
{
    ewlm_APIversion_t          version;
    ewlm_bytelength_t          sizeneeded;
    /* ------- end of data present in version 1 */
    #define EWLM_REASSIGN_MGMTCLASS_OUTVERSION001  (1)
    #define EWLM_REASSIGN_MGMTCLASS_OUTPUT_V001SIZE  \
             sizeof(ewlm_reassign_mgmtclass_output_t)
} ewlm_reassign_mgmtclass_output_t;


typedef struct ewlm_reassign_mgmtclass_input
{
    ewlm_APIversion_t          version;
    ewlm_connect_handle_t      connect_handle;
    ewlm_classification_id_t   service_class_id;
    ewlm_process_id_t          pid;
    /* ------- end of data present in version 1 */
    #define EWLM_REASSIGN_MGMTCLASS_INVERSION001  (1)
    #define EWLM_REASSIGN_MGMTCLASS_INPUT_V001SIZE  \
             sizeof(ewlm_reassign_mgmtclass_input_t)
} ewlm_reassign_mgmtclass_input_t;


/*
    Required Return codes:
       0    EWLM_SUCCESS
    -100    EWLM_NO_CONNECTION
    -218    EWLM_INBUFFER_BELOW_V1SIZE
    -219    EWLM_INBUFFER_TOO_SMALL
    -222    EWLM_SUPPORT_NOT_ENABLED
    -224    EWLM_LOCAL_WLM_NOT_ACTIVE
    -225    EWLM_LOCAL_WLM_PASSIVE
    -227    EWLM_PROCESS_LOCAL_WLM_MANAGED
    -228    EWLM_BAD_MANAGEMENT_ID

    Optional Return codes:
    -101    EWLM_BAD_CONNECT_HANDLE
    -205    EWLM_MISSING_PARM
    -212    EWLM_BAD_IN_BUFFER
*/

ewlm_status_t ewlm_reassign_mgmtclass(
    /* [in]  */ ewlm_reassign_mgmtclass_input_t         *input_buffer,
    /* [in]  */ ewlm_bytelength_t                       input_buffer_size,
    /* [i/o] */ ewlm_reassign_mgmtclass_output_t        *output_buffer,
    /* [in]  */ ewlm_bytelength_t                       output_buffer_size);

typedef struct ewlm_delete_mgmtclass_output
{
    ewlm_APIversion_t          version;
    ewlm_bytelength_t          sizeneeded;
    /* ------- end of data present in version 1 */
    #define EWLM_DELETE_MGMTCLASS_OUTVERSION001  (1)
    #define EWLM_DELETE_MGMTCLASS_OUTPUT_V001SIZE  \
             sizeof(ewlm_delete_mgmtclass_output_t)
} ewlm_delete_mgmtclass_output_t;


typedef struct ewlm_delete_mgmtclass_input
{
    ewlm_APIversion_t          version;
    ewlm_connect_handle_t      connect_handle;
    ewlm_classification_id_t   service_class_id;
    /* ------- end of data present in version 1 */
    #define EWLM_DELETE_MGMTCLASS_INVERSION001  (1)
    #define EWLM_DELETE_MGMTCLASS_INPUT_V001SIZE  \
             sizeof(ewlm_delete_mgmtclass_input_t)
} ewlm_delete_mgmtclass_input_t;


/*
    Required Return codes:
       0    EWLM_SUCCESS
    -100    EWLM_NO_CONNECTION
    -218    EWLM_INBUFFER_BELOW_V1SIZE
    -219    EWLM_INBUFFER_TOO_SMALL
    -222    EWLM_SUPPORT_NOT_ENABLED
    -224    EWLM_LOCAL_WLM_NOT_ACTIVE
    -225    EWLM_LOCAL_WLM_PASSIVE

    Optional Return codes:
    -101    EWLM_BAD_CONNECT_HANDLE
    -205    EWLM_MISSING_PARM
    -212    EWLM_BAD_IN_BUFFER
*/
ewlm_status_t ewlm_delete_mgmtclass(
    /* [in]  */ ewlm_delete_mgmtclass_input_t   *input_buffer,
    /* [in]  */ ewlm_bytelength_t               input_buffer_size,
    /* [i/o] */ ewlm_delete_mgmtclass_output_t  *output_buffer,
    /* [in]  */ ewlm_bytelength_t               output_buffer_size);

typedef struct ewlm_activate_localresourcemgmt_output
{
    ewlm_APIversion_t          version;
    ewlm_bytelength_t          sizeneeded;
    /* ------- end of data present in version 1 */
    #define EWLM_ACTIVATE_LOCALRESOURCEMGMT_OUTVERSION001  (1)
    #define EWLM_ACTIVATE_LOCALRESOURCEMGMT_OUTPUT_V001SIZE  \
             sizeof(ewlm_activate_localresourcemgmt_output_t)
} ewlm_activate_localresourcemgmt_output_t;


typedef struct ewlm_activate_localresourcemgmt_input
{
    ewlm_APIversion_t          version;
    ewlm_connect_handle_t      connect_handle;
    ewlm_int32_t               resource_types;

    /* Following are four resources that EWLM is expected
       to manage over time. */

    #define EWLM_LOCAL_CPU_RESOURCES         (0x80000000)
    #define EWLM_LOCAL_MEMORY_RESOURCES      (0x40000000)
    #define EWLM_LOCAL_DISKIO_RESOURCES      (0x20000000)
    #define EWLM_LOCAL_NETWORK_RESOURCES     (0x10000000)

    /* ------- end of data present in version 1 */
    #define EWLM_ACTIVATE_LOCALRESOURCEMGMT_INVERSION001  (1)
    #define EWLM_ACTIVATE_LOCALRESOURCEMGMT_INPUT_V001SIZE  \
             sizeof(ewlm_activate_localresourcemgmt_input_t)
} ewlm_activate_localresourcemgmt_input_t;


/*
    Required Return codes:
       0    EWLM_SUCCESS
    -100    EWLM_NO_CONNECTION
    -218    EWLM_INBUFFER_BELOW_V1SIZE
    -219    EWLM_INBUFFER_TOO_SMALL
    -222    EWLM_SUPPORT_NOT_ENABLED
    -224    EWLM_LOCAL_WLM_NOT_ACTIVE
    -229    EWLM_UNSUPPORTED_RESOURCE_TYPE

    Optional Return codes:
    -101    EWLM_BAD_CONNECT_HANDLE
    -205    EWLM_MISSING_PARM
    -212    EWLM_BAD_IN_BUFFER
*/
ewlm_status_t ewlm_activate_localresourcemgmt(
    /* [in]  */ ewlm_activate_localresourcemgmt_input_t *input_buffer,
    /* [in]  */ ewlm_bytelength_t                       input_buffer_size,
    /* [i/o] */ ewlm_activate_localresourcemgmt_output_t        *output_buffer,
    /* [in]  */ ewlm_bytelength_t                       output_buffer_size);


typedef struct ewlm_deactivate_localresourcemgmt_output
{
    ewlm_APIversion_t          version;
    ewlm_bytelength_t          sizeneeded;
    /* ------- end of data present in version 1 */
    #define EWLM_DEACTIVATE_LOCALRESOURCEMGMT_OUTVERSION001  (1)
    #define EWLM_DEACTIVATE_LOCALRESOURCEMGMT_OUTPUT_V001SIZE  \
             sizeof(ewlm_deactivate_localresourcemgmt_output_t)
} ewlm_deactivate_localresourcemgmt_output_t;


typedef struct ewlm_deactivate_localresourcemgmt_input
{
    ewlm_APIversion_t          version;
    ewlm_connect_handle_t      connect_handle;
    ewlm_int32_t               resource_types;

    /* Following are four primary resources that EWLM is expected
       to manage over time. */

    #define EWLM_LOCAL_CPU_RESOURCES            (0x80000000)
    #define EWLM_LOCAL_MEMORY_RESOURCES         (0x40000000)
    #define EWLM_LOCAL_DISKIO_RESOURCES         (0x20000000)
    #define EWLM_LOCAL_NETWORK_RESOURCES        (0x10000000)

    /* ------- end of data present in version 1 */
    #define EWLM_DEACTIVATE_LOCALRESOURCEMGMT_INVERSION001  (1)
    #define EWLM_DEACTIVATE_LOCALRESOURCEMGMT_INPUT_V001SIZE  \
             sizeof(ewlm_deactivate_localresourcemgmt_input_t)
} ewlm_deactivate_localresourcemgmt_input_t;


/*
    Required Return codes:
       0    EWLM_SUCCESS
    -100    EWLM_NO_CONNECTION
    -218    EWLM_INBUFFER_BELOW_V1SIZE
    -219    EWLM_INBUFFER_TOO_SMALL
    -222    EWLM_SUPPORT_NOT_ENABLED
    -224    EWLM_LOCAL_WLM_NOT_ACTIVE
    -225    EWLM_LOCAL_WLM_PASSIVE
    -229    EWLM_UNSUPPORTED_RESOURCE_TYPE

    Optional Return codes:
    -101    EWLM_BAD_CONNECT_HANDLE
    -205    EWLM_MISSING_PARM
    -212    EWLM_BAD_IN_BUFFER
*/
ewlm_status_t ewlm_deactivate_localresourcemgmt(
    /* [in]  */ ewlm_deactivate_localresourcemgmt_input_t    *input_buffer,
    /* [in]  */ ewlm_bytelength_t               input__buffer_size,
    /* [i/o] */ ewlm_deactivate_localresourcemgmt_output_t   *output_buffer,
    /* [in]  */ ewlm_bytelength_t               output_buffer_size);
/* ------------------------------------------------------------------------- */
/* --------------------Global Performance Data API-------------------------- */
/* ------------------------------------------------------------------------- */

typedef struct ewlm_global_perf_data_input
{
    ewlm_APIversion_t          version;
    ewlm_policytype_t          policy_type;

    ewlm_unencodedbytestream_t reportData;/* Global Performance
                                             data */
    ewlm_connect_handle_t      connect_handle;

    /* ------- end of data present in version 1 */
    #define EWLM_GLOBAL_PERF_DATA_IN_VERSION001        (1)
    #define EWLM_GLOBAL_PERF_DATA_INPUT_V001SIZE \
        sizeof(ewlm_global_perf_data_input_t)
} ewlm_global_perf_data_input_t;


typedef struct ewlm_global_perf_data_output
{
    ewlm_APIversion_t          version;
    ewlm_bytelength_t          sizeneeded;
    /* ------- end of data present in version 1 */
    #define EWLM_GLOBAL_PERF_DATA_OUTVERSION001        (1)
    #define EWLM_GLOBAL_PERF_DATA_OUTPUT_V001SIZE \
        sizeof(ewlm_global_perf_data_output_t)
} ewlm_global_perf_data_output_t;



ewlm_status_t ewlm_global_perf_data(
    /* [in]  */ ewlm_char_t         *input_buffer,
    /* [in]  */ ewlm_bytelength_t   input__buffer_size,
    /* [i/o] */ ewlm_char_t         *output_buffer,
    /* [in]  */ ewlm_bytelength_t   output_buffer_size
);

/*
    Required Return codes:
       0    EWLM_SUCCESS
    -100    EWLM_NO_CONNECTION
    -205    EWLM_MISSING_PARM
    -212    EWLM_BAD_IN_BUFFER
    -218    EWLM_INBUFFER_BELOW_V1SIZE
    -219    EWLM_INBUFFER_TOO_SMALL

    Optional Return codes:
    -101    EWLM_BAD_CONNECT_HANDLE
*/
/* --------------------------------------------------------------------------
    net_ prefixed services: see netwlm.h
   ------------------------------------------------------------------------- */
#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _H_EWLM_EWLMPLAT */
