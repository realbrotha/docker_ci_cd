/*
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * $Id: papi.h,v 1.1.1.1 2004/02/06 16:34:09 njacobs Exp $
 */

#ifndef _PAPI_H
#define	_PAPI_H

#pragma ident	"@(#)papi.h	1.2	04/02/06 SMI"


#include <sys/types.h>
#include <time.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Types
 */

/*	service related types	*/
typedef void *papi_service_t;
typedef void *papi_printer_t;
typedef void *papi_job_t;
typedef void *papi_stream_t;

typedef enum {
	PAPI_ENCRYPT_IF_REQUESTED,	/* Encrypt if requested (TLS upgrade) */
	PAPI_ENCRYPT_NEVER,		/* Never encrypt */
	PAPI_ENCRYPT_REQUIRED,		/* Encryption required (TLS upgrade) */
	PAPI_ENCRYPT_ALWAYS		/* Always encrypt (SSL) */
} papi_encryption_t;

/*	attribute related types	*/
typedef enum {
	PAPI_STRING,
	PAPI_INTEGER,
	PAPI_BOOLEAN,
	PAPI_RANGE,
	PAPI_RESOLUTION,
	PAPI_DATETIME,
	PAPI_COLLECTION,
	PAPI_METADATA
} papi_attribute_value_type_t;

typedef enum {
	PAPI_RES_PER_INCH = 3,
	PAPI_RES_PER_CM
} papi_resolution_unit_t;

enum {	/* for boolean values */
	PAPI_FALSE = 0,
	PAPI_TRUE = 1
};

typedef enum {
	PAPI_UNSUPPORTED = 0x10,
	PAPI_DEFAULT = 0x11,
	PAPI_UNKNOWN,
	PAPI_NO_VALUE,
	PAPI_NOT_SETTABLE = 0x15,
	PAPI_DELETE = 0x16
} papi_metadata_t;

#define	PAPI_LIST_JOBS_OTHERS		0x0001
#define	PAPI_LIST_JOBS_COMPLETED	0x0002
#define	PAPI_LIST_JOBS_NOT_COMPLETED	0x0004
#define	PAPI_LIST_JOBS_ALL		0xFFFF

typedef struct papi_attribute_s papi_attribute_t;

typedef union {
	char *string;				/* PAPI_STRING value */
	int integer;				/* PAPI_INTEGER value */
	char boolean;				/* PAPI_BOOLEAN value */
	struct {				/* PAPI_RANGE value */
		int lower;
		int upper;
	} range;
	struct {				/* PAPI_RESOLUTION value */
		int xres;
		int yres;
		papi_resolution_unit_t units;
	} resolution;
	time_t datetime;			/* PAPI_DATETIME value */
	papi_attribute_t **collection;		/* PAPI_COLLECTION value */
	papi_metadata_t metadata;		/* PAPI_METADATA value */
} papi_attribute_value_t;

struct papi_attribute_s {
	char *name;				/* attribute name */
	papi_attribute_value_type_t type;	/* type of values */
	papi_attribute_value_t **values;	/* list of values */
};

#define	PAPI_ATTR_APPEND	0x0001	/* Add values to attr */
#define	PAPI_ATTR_REPLACE	0x0002	/* Delete existing values, then add */
#define	PAPI_ATTR_EXCL		0x0004	/* Fail if attr exists */

/*	job related types	*/
typedef enum {
	PAPI_JT_FORMAT_JDF = 0,
	PAPI_JT_FORMAT_PWG = 1
} papi_jt_format_t;

typedef struct {
	papi_jt_format_t format;
	char *ticket_data;
	char *file_name;
} papi_job_ticket_t;

/*	status related types	*/
typedef enum {
	PAPI_OK = 0x0000,
	PAPI_OK_SUBST,
	PAPI_OK_CONFLICT,
	PAPI_OK_IGNORED_SUBSCRIPTIONS,
	PAPI_OK_IGNORED_NOTIFICATIONS,
	PAPI_OK_TOO_MANY_EVENTS,
	PAPI_OK_BUT_CANCEL_SUBSCRIPTION,
	PAPI_REDIRECTION_OTHER_SITE = 0x0300,
	PAPI_BAD_REQUEST = 0x0400,
	PAPI_FORBIDDEN,
	PAPI_NOT_AUTHENTICATED,
	PAPI_NOT_AUTHORIZED,
	PAPI_NOT_POSSIBLE,
	PAPI_TIMEOUT,
	PAPI_NOT_FOUND,
	PAPI_GONE,
	PAPI_REQUEST_ENTITY,
	PAPI_REQUEST_VALUE,
	PAPI_DOCUMENT_FORMAT,
	PAPI_ATTRIBUTES,
	PAPI_URI_SCHEME,
	PAPI_CHARSET,
	PAPI_CONFLICT,
	PAPI_COMPRESSION_NOT_SUPPORTED,
	PAPI_COMPRESSION_ERROR,
	PAPI_DOCUMENT_FORMAT_ERROR,
	PAPI_DOCUMENT_ACCESS_ERROR,
	PAPI_ATTRIBUTES_NOT_SETTABLE,
	PAPI_IGNORED_ALL_SUBSCRIPTIONS,
	PAPI_TOO_MANY_SUBSCRIPTIONS,
	PAPI_IGNORED_ALL_NOTIFICATIONS,
	PAPI_PRINT_SUPPORT_FILE_NOT_FOUND,
	PAPI_INTERNAL_ERROR = 0x0500,
	PAPI_OPERATION_NOT_SUPPORTED,
	PAPI_SERVICE_UNAVAILABLE,
	PAPI_VERSION_NOT_SUPPORTED,
	PAPI_DEVICE_ERROR,
	PAPI_TEMPORARY_ERROR,
	PAPI_NOT_ACCEPTING,
	PAPI_PRINTER_BUSY,
	PAPI_ERROR_JOB_CANCELLED,
	PAPI_MULTIPLE_JOBS_NOT_SUPPORTED,
	PAPI_PRINTER_IS_DEACTIVATED,
	PAPI_BAD_ARGUMENT,
	PAPI_JOB_TICKET_NOT_SUPPORTED
} papi_status_t;

/*	list filter related	*/
typedef enum {
	PAPI_FILTER_BITMASK = 0
} papi_filter_type_t;

typedef struct {
	papi_filter_type_t type;
	union {
		struct {			/* PAPI_FILTER_BITMASK */
			unsigned int mask;
			unsigned int value;
		} bitmask;
	} filter;
} papi_filter_t;

enum {
	PAPI_PRINTER_LOCAL = 0x0000,	/* Local destination */
	PAPI_PRINTER_CLASS = 0x0001,	/* Printer class */
	PAPI_PRINTER_REMOTE = 0x0002,	/* Remote destination */
	PAPI_PRINTER_BW = 0x0004,	/* Can do B&W printing */
	PAPI_PRINTER_COLOR = 0x0008,	/* Can do color printing */
	PAPI_PRINTER_DUPLEX = 0x0010,	/* Can do duplex printing */
	PAPI_PRINTER_STAPLE = 0x0020,	/* Can do stapling */
	PAPI_PRINTER_COPIES = 0x0040,	/* Can do copies */
	PAPI_PRINTER_COLLATE = 0x0080,	/* Can collate copies */
	PAPI_PRINTER_PUNCH = 0x0100,	/* Can punch output */
	PAPI_PRINTER_COVER = 0x0200,	/* Can cover output */
	PAPI_PRINTER_BIND = 0x0400,	/* Can bind output */
	PAPI_PRINTER_SORT = 0x0800,	/* Can sort output */
	PAPI_PRINTER_SMALL = 0x1000,	/* Can do letter/legal/a4 */
	PAPI_PRINTER_MEDIUM = 0x2000,	/* Can do tabloid/B/C/A3/A2 */
	PAPI_PRINTER_LARGE = 0x4000,	/* Can do D/E/A1/A0 */
	PAPI_PRINTER_VARIABLE = 0x8000,	/* Can do variable sizes */
	PAPI_PRINTER_IMPLICIT = 0x10000, /* implicit class */
	PAPI_PRINTER_DEFAULT = 0x20000,	/* Default printer on network */
	PAPI_PRINTER_OPTIONS = 0xfffc	/* ~ (CLASS | REMOTE | IMPLICIT) */
};

/*
 * Functions
 */

/* 	Service related		*/
extern papi_status_t papiServiceCreate(papi_service_t *handle,
					const char *service_name,
					const char *user_name,
					const char *password,
					const int (*authCB)(papi_service_t svc),
					const papi_encryption_t encryption,
					void *app_data);
extern void papiServiceDestroy(papi_service_t handle);
extern papi_status_t papiServiceSetUserName(papi_service_t handle,
					const char *user_name);
extern papi_status_t papiServiceSetPassword(papi_service_t handle,
					const char *password);
extern papi_status_t papiServiceSetEncryption(papi_service_t handle,
					const papi_encryption_t encryption);
extern papi_status_t papiServiceSetAuthCB(papi_service_t handle,
					const int (*authCB)(papi_service_t s));
extern papi_status_t papiServiceSetAppData(papi_service_t handle,
					const void *app_data);
extern char *papiServiceGetServiceName(papi_service_t handle);
extern char *papiServiceGetUserName(papi_service_t handle);
extern char *papiServiceGetPassword(papi_service_t handle);
extern papi_encryption_t papiServiceGetEncryption(papi_service_t handle);
extern void *papiServiceGetAppData(papi_service_t handle);
extern papi_attribute_t **papiServiceGetAttributeList(papi_service_t handle);
extern char *papiServiceGetStatusMessage(papi_service_t handle);

/*	Attribute related	 */
extern papi_status_t papiAttributeListAdd(papi_attribute_t ***attrs,
					const int flags,
					const char *name,
					const papi_attribute_value_type_t type,
					const papi_attribute_value_t *value);
extern papi_status_t papiAttributeListAddString(papi_attribute_t ***attrs,
					const int flags, const char *name,
					const char *string);
extern papi_status_t papiAttributeListAddInteger(papi_attribute_t ***attrs,
					const int flags, const char *name,
					const int integer);
extern papi_status_t papiAttributeListAddBoolean(papi_attribute_t ***attrs,
					const int flags, const char *name,
					const char boolean);
extern papi_status_t papiAttributeListAddRange(papi_attribute_t ***attrs,
					const int flags, const char *name,
					const int lower, const int upper);
extern papi_status_t papiAttributeListAddResolution(papi_attribute_t ***attrs,
					const int flags, const char *name,
					const int xres, const int yres,
					papi_resolution_unit_t units);
extern papi_status_t papiAttributeListAddDatetime(papi_attribute_t ***attrs,
					const int flags, const char *name,
					const time_t datetime);
extern papi_status_t papiAttributeListAddCollection(papi_attribute_t ***attrs,
					const int flags, const char *name,
					const papi_attribute_t **collection);
extern papi_status_t papiAttributeListAddMetadata(papi_attribute_t ***attrs,
					const int flags, const char *name,
					const papi_metadata_t metadata);
extern papi_status_t papiAttributeListDelete(papi_attribute_t ***attributes,
					const char *name);
extern papi_status_t papiAttributeListGetValue(papi_attribute_t **list,
					void **iterator, const char *name,
					papi_attribute_value_type_t type,
					papi_attribute_value_t **value);
extern papi_status_t papiAttributeListGetString(papi_attribute_t **list,
					void **iterator, const char *name,
					char **vptr);
extern papi_status_t papiAttributeListGetInteger(papi_attribute_t **list,
					void **iterator, const char *name,
					int *vptr);
extern papi_status_t papiAttributeListGetBoolean(papi_attribute_t **list,
					void **iterator, const char *name,
					char *vptr);
extern papi_status_t papiAttributeListGetRange(papi_attribute_t **list,
					void **iterator, const char *name,
					int *min, int *max);
extern papi_status_t papiAttributeListGetResolution(papi_attribute_t **list,
					void **iterator, const char *name,
					int *x, int *y,
					papi_resolution_unit_t *units);
extern papi_status_t papiAttributeListGetDatetime(papi_attribute_t **list,
					void **iterator, const char *name,
					time_t *dt);
extern papi_status_t papiAttributeListGetCollection(papi_attribute_t **list,
					void **iterator, const char *name,
					papi_attribute_t ***collection);
extern papi_status_t papiAttributeListGetMetadata(papi_attribute_t **list,
					void **iterator, const char *name,
					papi_metadata_t *vptr);
extern papi_attribute_t *papiAttributeListFind(papi_attribute_t **list,
					const char *name);
extern papi_attribute_t *papiAttributeListGetNext(papi_attribute_t **list,
					void **iterator);
extern void papiAttributeListFree(papi_attribute_t **attributes);

extern papi_status_t papiAttributeListFromString(papi_attribute_t ***attrs,
					const int flags, const char *string);
extern papi_status_t papiAttributeListToString(const papi_attribute_t **attrs,
					const char *delim,
					char *buffer, const size_t buflen);
extern void papiAttributeListPrint
			(FILE *fp, char *prefix, papi_attribute_t **list);

/*	Printer related		 */
extern papi_status_t papiPrintersList(papi_service_t handle,
					const char **requested_attrs,
					const papi_filter_t *filter,
					papi_printer_t **printers);
extern papi_status_t papiPrinterQuery(papi_service_t handle, const char *name,
					const char **requested_attrs,
					const papi_attribute_t **job_attributes,
					papi_printer_t *printer);
extern papi_status_t papiPrinterModify(papi_service_t handle, const char *name,
					const papi_attribute_t **attributes,
					papi_printer_t *printer);
extern papi_status_t papiPrinterPause(papi_service_t handle, const char *name,
					const char *message);
extern papi_status_t papiPrinterResume(papi_service_t handle, const char *name);
extern papi_status_t papiPrinterPurgeJobs(papi_service_t handle,
					const char *name, papi_job_t **jobs);
extern papi_status_t papiPrinterListJobs(papi_service_t handle,
					const char *name,
					const char **requested_attrs,
					const int type_mask,
					const int max_num_jobs,
					papi_job_t **jobs);
extern papi_attribute_t **papiPrinterGetAttributeList(papi_printer_t printer);
extern void papiPrinterFree(papi_printer_t printer);
extern void papiPrinterListFree(papi_printer_t *printers);

/*	Job related		*/
extern papi_status_t papiJobSubmit(papi_service_t handle, const char *printer,
					const papi_attribute_t **job_attributes,
					const papi_job_ticket_t *job_ticket,
					const char **files, papi_job_t *job);
extern papi_status_t papiJobSubmitByReference(papi_service_t handle,
					const char *printer,
					const papi_attribute_t **job_attributes,
					const papi_job_ticket_t *job_ticket,
					const char **files, papi_job_t *job);
extern papi_status_t papiJobValidate(papi_service_t handle, const char *printer,
					const papi_attribute_t **job_attributes,
					const papi_job_ticket_t *job_ticket,
					const char **files, papi_job_t *job);
extern papi_status_t papiJobStreamOpen(papi_service_t handle,
					const char *printer,
					const papi_attribute_t **job_attributes,
					const papi_job_ticket_t *job_ticket,
					papi_stream_t *stream);
extern papi_status_t papiJobStreamWrite(papi_service_t handle,
					papi_stream_t stream,
					const void *buffer,
					const size_t buflen);
extern papi_status_t papiJobStreamClose(papi_service_t handle,
					papi_stream_t stream,
					papi_job_t *job);
extern papi_status_t papiJobQuery(papi_service_t handle, const char *printer,
					const int32_t job_id,
					const char **requested_attrs,
					papi_job_t *job);
extern papi_status_t papiJobModify(papi_service_t handle, const char *printer,
					const int32_t job_id,
					const papi_attribute_t **attributes,
					papi_job_t *job);
extern papi_status_t papiJobCancel(papi_service_t handle, const char *printer,
					const int32_t job_id);
extern papi_status_t papiJobHold(papi_service_t handle, const char *printer,
					const int32_t job_id,
					const char *hold_until,
					const time_t *hold_until_time);
extern papi_status_t papiJobRelease(papi_service_t handle, const char *printer,
					const int32_t job_id);
extern papi_status_t papiJobRestart(papi_service_t handle, const char *printer,
					const int32_t job_id);
extern papi_attribute_t **papiJobGetAttributeList(papi_printer_t printer);
extern char *papiJobGetPrinterName(papi_printer_t printer);
extern int32_t papiJobGetId(papi_printer_t printer);
extern papi_job_ticket_t *papiJobGetJobTicket(papi_printer_t printer);
extern void papiJobFree(papi_job_t job);
extern void papiJobListFree(papi_job_t *jobs);

#ifdef SOLARIS_PRIVATE_POST_0_9
/*
 * These have been added to support IPP create-job/send-document with PAPI v0.9
 * in an IPP listener using PAPI as it's spooler interface.  A future version
 * of the API is expected to support this type of functionality
 */
extern papi_status_t papiJobCreate(papi_service_t handle, const char *printer,
					const papi_attribute_t **job_attributes,
					const papi_job_ticket_t *job_ticket,
					papi_job_t *job);
extern papi_status_t papiJobStreamAdd(papi_service_t handle, char *printer,
					int32_t id, papi_stream_t *stream);
extern papi_status_t papiJobCommit(papi_service_t handle, char *printer,
					int32_t id);
#endif /* SOLARIS_PRIVATE_POST_0_9 */

extern char *papiStatusString(const papi_status_t status);
extern void list_append();

#ifdef __cplusplus
}
#endif

#endif /* _PAPI_H */