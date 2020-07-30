/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/diag/tucb.h 1.4                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1995,1996          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)40	1.4  src/bos/usr/include/diag/tucb.h, cmddiag, bos530 1/16/96 09:26:43 */
/*
 *   COMPONENT_NAME: CMDDIAG
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1995
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _h_tucb
#define _h_tucb

#ifndef OUTPUT_DATA
#define OUTPUT_DATA void
#endif

#ifndef INPUT_DATA
#define INPUT_DATA  void
#endif

/*****************************************************************************/
/* This structure is used for passing of information to the test units.      */
/*****************************************************************************/

typedef struct tucb_in_t {
	ulong tu;		/* Test unit number of the test unit to run. */

        ulong loop;		/* Indicates the number of times the test    */
                		/* unit should be run provided that an error */
				/* does not occur.		             */

        OUTPUT_DATA *data_log;  /* Error details log and or output data log. */
                                /* This log is device specific and is defined*/
                		/* by the {device}_output_data.h file.       */
                		/* It should point to an empty array of      */
                		/* structures and then filled in with output */
                		/* or error detail data by the test unit(s). */
                		/* This parameter should be initialized      */
				/* by the calling application if intended    */
				/* to be used.                               */

        ulong data_log_length;	/* Size of the data_log structure.           */
                		/* This field is used when passing the tucb  */
				/* data to a remote managing application.    */
				/* This number is initialized by the calling */
				/* application by calculating the size of the*/
				/* data structure to be filled in and        */
				/* multiplying it by the number of records to*/
				/* be logged.                                */
				/* The test unit calculates the number of    */
			        /* records by dividing this number by the    */
				/* size of the intended OUTPUT_DATA structure*/
				/* to be used.                               */
				/* A data_log_length value of zero results   */
				/* in no data being logged to the data_log.  */
 
        INPUT_DATA  *tu_data;	/* Input parameter to be used to pass extra  */
                		/* input data to the test units. This        */
			        /* parameter must only be used as special    */
				/* case scenarios. It is intended for        */
				/* special applications such as manufacturing*/
                		/* or hardware exercisers.                   */

        ulong tu_data_length;	/* Size of the tu_data structure.      	     */
                		/* This field is used when passing the tucb  */
				/* data to a remote managing application.    */
				/* This number is initialized by the calling */
				/* application by calculating the size of the*/
				/* data structure to be filled in and        */
				/* multiplying it by the number of records to*/
				/* be logged.                                */
				/* The test unit calculates the number of    */
			        /* data records by dividing this number by   */
				/* the size of the intended INPUT_DATA       */
			        /* structure to be used.                     */

        FILE *msg_file;		/*  Message file pointer which must be 	     */
				/* initialized by the calling application if */
				/* DEBUG output is desired.	             */
} TU_INPUT_TYPE;


/*****************************************************************************/
/* This structure is used for return code information and detailed output.   */
/*****************************************************************************/

/* severity definitions */
#define CRITICAL_FAILURE   0	/* Critical failure		     	     */
#define PARTIAL_FAILURE    1	/* Partial loss of function, performance, or */
				/* resource                                  */
#define LOST_REDUNDANCY    2	/* Increased exposure to secondary failure   */
#define DEFERRABLE_FAILURE  3	/* No immediate exposure, repair can be      */
				/* deferred.                                 */

typedef struct tucb_out_t {
        ulong major_rc;		/* Major return code. Used for FRU isolation.*/
        ulong minor_rc;		/* Minor return code. Used for more granular */
				/* detailed error information. 		     */
        ulong actual_loop;	/* Indicates the number of times the test    */
				/* unit actually ran, or looped. 	     */
        ulong data_log_length;	/* Returns the actual length of the data log */
				/* used                                      */
	ulong severity;	        /* Indicates the severity level of the error.*/
				/* Default value of 0 indicates fatal.       */
} TU_RETURN_TYPE;

/*****************************************************************************/
/* The TU_INFO_HANDLE is a void pointer allowing it to                       */
/* point to data that must remain persistent between test unit               */
/* invocations. This handle is context specific; in that it only has         */
/* meaning for a specific set of test units and can vary between             */
/* test unit sets and operating systems. The TU_INFO_HANDLE is               */
/* supplied by the diagnostic application and is initialized by              */
/* the first test unit, and is used by other test units in subsequent        */
/* invocations of exectu().                                                  */
/*****************************************************************************/

 typedef void *TU_INFO_HANDLE;  /* Test Unit handle containing context       */
				/* specific information for inter-test unit  */
				/* data persistence                          */

/*****************************************************************************/
/* This structure is used for passing of information to the test units.      */
/*****************************************************************************/

typedef struct tucb_t {
        char  *resource_name;	/* Name of hardware/physical device instance */
				/* on which to run the test unit             */
        TU_INPUT_TYPE parms;    /* Input parameters for test unit execution  */
} TU_TYPE;


#endif
