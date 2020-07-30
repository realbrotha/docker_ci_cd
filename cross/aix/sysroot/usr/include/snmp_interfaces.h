/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* tcpip530 src/tcpip/usr/include/snmp_interfaces.h 1.1                   */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1996               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)81	1.1  src/tcpip/usr/include/snmp_interfaces.h, snmp, tcpip530 12/6/96 14:46:39 */
/*
 * 
 * COMPONENT_NAME: SNMP 
 * 
 * FUNCTIONS: 
 *
 * ORIGINS: 27 
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1996
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication o
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp
 *
 *
 */

#ifndef _SNMP_INTERFACES_H_
#define _SNMP_INTERFACES_H_

#include <sys/time.h>
#include <sys/signal.h>

#define DEFAULT_DIRECTORY	"/etc/snmpinterfaces/"

#define SNMP_GET_DELAY		1
#define SNMP_SET_DELAY		5

#define IF_TABLE_MAX_STR_LEN	256
#define IF_NAME_SIZE		16

struct ifTableEntry {
	/*
	 *  Of all the variables, the ifIndex and ifAdminStatus are settable
	 *  by the snmpd side.  The rest are set by the subagent side.
	 */
	unsigned int	ifIndex;
	char		name[IF_NAME_SIZE];
	char		ifDescr[IF_TABLE_MAX_STR_LEN];
	unsigned int	ifType;
	unsigned int	ifMtu;
	unsigned int	ifSpeed;
	unsigned char	ifPhysAddress[IF_TABLE_MAX_STR_LEN];
#define IF_STATUS_LINK_UP	1
#define IF_STATUS_LINK_DOWN	2
	unsigned int	ifAdminStatus;
	unsigned int	ifOperStatus;
	unsigned int	ifLastChange;
	unsigned int	ifInOctets;
	unsigned int	ifInUcastPkts;
	unsigned int	ifInNUcastPkts;
	unsigned int	ifInDiscards;
	unsigned int	ifInErrors;
	unsigned int	ifInUnknownProtos;
	unsigned int	ifOutOctets;
	unsigned int	ifOutUcastPkts;
	unsigned int	ifOutNUcastPkts;
	unsigned int	ifOutDiscards;
	unsigned int	ifOutErrors;
	unsigned int	ifOutQlen;
	char		ifSpecific[IF_TABLE_MAX_STR_LEN];
};
typedef struct ifTableEntry ifTableEntry;


#define DEFAULT_SNMPSUBAGENT_SIGNAL	SIGINT
#define DEFAULT_SIGNALINTERVAL		2000
#define DEFAULT_SNMPMINREQUESTS		23


struct ifTableHeader {
	int	SharedMemoryId;		/* The shared memory Id */
	int	NumberOfInterfaces;	/* Number of interfaces in ifTable */
	int	Pid;			/* Process Id of the subagent */
	int	SignalToUse;		/* Signal used to indicate chg/update */
	int	MinTimeBetweenSignals;	/* Min Time (usecs) between signals */
	int	ReadyCounter;		/* increment after update */
	int	SNMPReady;		/* value for SNMP to keep track */
	struct timeval	LastTimeSignaled;/* used by snmpd to track time */
	int	SnmpVersion;		/* Version of ifTable  1=rfc1213 */
	int	MinRequestBeforeUpdate;	/* Min number of ifTable reqs before */
					/*    update is requested */
	int	ifIndexChanged;		/* If -1, indicates that snmpd wants */
					/* ifTable refreshed, else it shows */
					/* which ifTable entry has a */
					/* ifAdminStatus change */
	struct timeval	SysUpTime;	/* So, link up times can be */
					/* calculated */
					/* Used this way: */
					/* diff=(now.tv_sec-sut.tv_sec)*100 + */
					/*    (now.tv_usec-sut.tv_usec)/10000 */
	ifTableEntry iflist[1];		/* This can be overloaded and */
					/* indexed beyond 0 */
};
typedef struct ifTableHeader ifTableHeader;


#define CURRENT_SYSUPTIME(table_ptr, tv) \
	(((tv).tv_sec - (table_ptr)->SysUpTime.tv_sec) * 100 + \
	 ((tv).tv_usec - (table_ptr)->SysUpTime.tv_usec) / 10000)


struct ifTableHeaderPtr
{
	ifTableHeader  *iftableheader;
	char		filename[IF_TABLE_MAX_STR_LEN];
	struct ifTableHeaderPtr *next;
};
typedef struct ifTableHeaderPtr ifTableHeaderPtr;


ifTableHeader *ifTableCreate(char *basename, int numentries, char **errmsg);
int ifTableDestroy(char *basename, ifTableHeader *ifData, char **errmsg);
ifTableHeader *ifTableAttach(char *basename, char **errmsg);
int ifTableDetach(ifTableHeader *ifData, char **errmsg);
int signalIfTable(ifTableHeader *ifData, char **errmsg, int delay);

#endif /* _SNMP_INTERFACES_H_ */

