/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* tcpip530 src/tcpip/usr/include/tcpip_audit.h 1.14                      */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,1989          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)23	1.14  src/tcpip/usr/include/tcpip_audit.h, tcpip, tcpip530 5/14/97 18:48:12 */
/* 
 * COMPONENT_NAME: TCPIP tcpip_audit.h
 * 
 * FUNCTIONS: CHANGE_CONFIGURATION_WRITE, CHANGE_HOST_ID_WRITE, 
 *            CHANGE_MANUALLY_SET_ROUTE_WRITE, CONNECTION_WRITE, 
 *            EXPORT_DATA_WRITE, IMPORT_DATA_WRITE, 
 *            MAIL_CONFIGURATION_WRITE, MAIL_TO_A_FILE_WRITE, 
 *            NET_ACCESS_WRITE, SET_NETWORK_TIME_WRITE, 
 *            USE_EFFECTIVE_UID, USE_REAL_UID 
 *
 * ORIGINS: 27 
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1989, 1995
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_TCPIP_AUDIT
#define _H_TCPIP_AUDIT

#ifdef _CSECURITY

#include <sys/audit.h>
#include <arpa/inet.h>

#define	PROTOCOL 	"TCP/IP"		/* TCP/IP, SNA, UUCP, etc..*/

/*
 * TCP/IP application auditlog cases.
 * BOS limits event names to 15 characters and NULL...
*/
#define	CHANGE_HOST_ID			0000001
#define	EVENT_CHANGE_HOST_ID		"TCPIP_host_id"

#define	CHANGE_CONFIGURATION		0000002
#define	EVENT_CHANGE_CONFIGURATION	"TCPIP_config"

#define	CHANGE_MANUALLY_SET_ROUTE	0000004
#define	EVENT_CHANGE_MANUALLY_SET_ROUTE	"TCPIP_route"

#define	CONNECTION			0000010
#define	EVENT_CONNECTION		"TCPIP_connect"

#define	IMPORT_DATA			0000020
#define	EVENT_IMPORT_DATA		"TCPIP_data_in"

#define	EXPORT_DATA			0000040
#define	EVENT_EXPORT_DATA		"TCPIP_data_out"

#define	NET_ACCESS			0000100
#define	EVENT_NET_ACCESS		"TCPIP_access"

#define	SET_NETWORK_TIME		0000200
#define	EVENT_SET_NETWORK_TIME		"TCPIP_set_time"

#define MAIL_CONFIGURATION              0000400
#define EVENT_MAIL_CONFIGURATION        "SENDMAIL_Config"

#define MAIL_TO_A_FILE                  0001000
#define EVENT_MAIL_TO_A_FILE            "SENDMAIL_ToFile"

/* globals and externs */

#define TCPIP_MAX_TAIL_FIELDS	8
struct in_addr make_in_addr();


/* Macros */

#define	USE_EFFECTIVE_UID(euid) \
	if ((setuid(euid)) == -1) syslog(LOG_ALERT, "setuid: %m");

#define	USE_REAL_UID(uid) \
	if ((setuid(uid)) == -1) syslog(LOG_ALERT, "setuid: %m");


/* Audit record template macros */

#define CHANGE_HOST_ID_WRITE(HOSTNAME, RESULT, ERRNO) \
	audit_tail[1] = HOSTNAME; \
	audit_tail[2] = RESULT; \
	tcpip_auditlog(CHANGE_HOST_ID, audit_tail, ERRNO);

#define CHANGE_CONFIGURATION_WRITE(ADD_DELETE, INTERFACE, INETADDR, RESULT, ERRNO) \
	audit_tail[1] = ADD_DELETE; \
	audit_tail[2] = INTERFACE; \
	audit_tail[3] = inet_ntoa(INETADDR); \
	audit_tail[4] = RESULT; \
	tcpip_auditlog(CHANGE_CONFIGURATION, audit_tail, ERRNO);

#define CHANGE_MANUALLY_SET_ROUTE_WRITE(DESTINATION, GATEWAY, ADD_OR_DELETE, NET_OR_HOST, RESULT, ERRNO) \
	audit_tail[1] = inet_ntoa(DESTINATION); \
	audit_tail[2] = inet_ntoa(GATEWAY); \
	audit_tail[3] = ADD_OR_DELETE; \
	audit_tail[4] = NET_OR_HOST; \
	audit_tail[5] = RESULT; \
	tcpip_auditlog(CHANGE_MANUALLY_SET_ROUTE, audit_tail, ERRNO);

#define CONNECTION_WRITE(INETADDR, PORT, OPERATION, RESULT, ERRNO) \
	audit_tail[1] = inet_ntoa(INETADDR); \
	audit_tail[2] = PORT; \
	audit_tail[3] = OPERATION; \
	audit_tail[4] = RESULT; \
	tcpip_auditlog(CONNECTION, audit_tail, ERRNO);

#define	AUDIT_TAIL_ADDR_BUF_SZ	256 
#define CONNECTION6_WRITE(INET6ADDR, PORT, OPERATION, RESULT, ERRNO) \
	{ \
		char audit_tail_addr_buf[AUDIT_TAIL_ADDR_BUF_SZ]; \
		audit_tail[1] = (char *)inet_ntop(AF_INET6, INET6ADDR, \
			audit_tail_addr_buf, AUDIT_TAIL_ADDR_BUF_SZ); \
		audit_tail[2] = PORT; \
		audit_tail[3] = OPERATION; \
		audit_tail[4] = RESULT; \
		tcpip_auditlog(CONNECTION, audit_tail, ERRNO); \
	}

#define IMPORT_DATA_WRITE(INETADDR, FROM_FILE, TO_FILE, RESULT, ERRNO) \
	audit_tail[1] = inet_ntoa(INETADDR); \
	audit_tail[2] = FROM_FILE; \
	audit_tail[3] = TO_FILE; \
	audit_tail[4] = RESULT; \
	tcpip_auditlog(IMPORT_DATA, audit_tail, ERRNO);

#define IMPORT6_DATA_WRITE(INET6ADDR, FROM_FILE, TO_FILE, RESULT, ERRNO) \
	{ \
		char audit_tail_addr_buf[AUDIT_TAIL_ADDR_BUF_SZ]; \
	audit_tail[1] = (char *)inet_ntop(AF_INET6, INET6ADDR, \
			audit_tail_addr_buf, AUDIT_TAIL_ADDR_BUF_SZ); \
	audit_tail[2] = FROM_FILE; \
	audit_tail[3] = TO_FILE; \
	audit_tail[4] = RESULT; \
	tcpip_auditlog(IMPORT_DATA, audit_tail, ERRNO); \
	}

#define EXPORT_DATA_WRITE(INETADDR, FROM_FILE, TO_FILE, RESULT, ERRNO) \
	audit_tail[1] = inet_ntoa(INETADDR); \
	audit_tail[2] = FROM_FILE; \
	audit_tail[3] = TO_FILE; \
	audit_tail[4] = RESULT; \
	tcpip_auditlog(EXPORT_DATA, audit_tail, ERRNO);

#define EXPORT6_DATA_WRITE(INET6ADDR, FROM_FILE, TO_FILE, RESULT, ERRNO) \
	{ \
		char audit_tail_addr_buf[AUDIT_TAIL_ADDR_BUF_SZ]; \
	audit_tail[1] = (char *)inet_ntop(AF_INET6, INET6ADDR, \
			audit_tail_addr_buf, AUDIT_TAIL_ADDR_BUF_SZ); \
	audit_tail[2] = FROM_FILE; \
	audit_tail[3] = TO_FILE; \
	audit_tail[4] = RESULT; \
	tcpip_auditlog(EXPORT_DATA, audit_tail, ERRNO); \
	}

#define NET_ACCESS_WRITE(INETADDR, ACCESS_TYPE, USER, RESULT, ERRNO) \
	audit_tail[1] = inet_ntoa(INETADDR); \
	audit_tail[2] = ACCESS_TYPE; \
	audit_tail[3] = USER; \
	audit_tail[4] = RESULT; \
	tcpip_auditlog(NET_ACCESS, audit_tail, ERRNO);

#define NET6_ACCESS_WRITE(INET6ADDR, ACCESS_TYPE, USER, RESULT, ERRNO) \
	{ \
		char audit_tail_addr_buf[AUDIT_TAIL_ADDR_BUF_SZ]; \
	audit_tail[1] = (char *)inet_ntop(AF_INET6, INET6ADDR, \
			audit_tail_addr_buf, AUDIT_TAIL_ADDR_BUF_SZ); \
	audit_tail[2] = ACCESS_TYPE; \
	audit_tail[3] = USER; \
	audit_tail[4] = RESULT; \
	tcpip_auditlog(NET_ACCESS, audit_tail, ERRNO); \
	}

#define SET_NETWORK_TIME_WRITE(INETADDR, TIME, RESULT, ERRNO) \
	audit_tail[1] = inet_ntoa(INETADDR); \
	audit_tail[2] = TIME; \
	/* Get rid of \n from asctime() */ \
	*(audit_tail[2] + strlen(audit_tail[2]) - 1) = '\0'; \
	audit_tail[3] = RESULT; \
	tcpip_auditlog(SET_NETWORK_TIME, audit_tail, ERRNO);

#define MAIL_CONFIGURATION_WRITE(OPERATION, RESULT, ERRNO) \
	audit_tail[1] = OPERATION; \
	audit_tail[2] = RESULT; \
	tcpip_auditlog(MAIL_CONFIGURATION, audit_tail, ERRNO);

#define MAIL_TO_A_FILE_WRITE(FROM, TO, RESULT, ERRNO) \
	audit_tail[1] = FROM; \
	audit_tail[2] = TO; \
	audit_tail[3] = RESULT; \
	tcpip_auditlog(MAIL_TO_A_FILE, audit_tail, ERRNO);

#endif /* _CSECURITY */

#endif /* _H_TCPIP_AUDIT */
