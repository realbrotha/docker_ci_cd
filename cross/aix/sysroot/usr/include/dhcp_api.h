/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* tcpip530 src/tcpip/usr/include/dhcp_api.h 1.2                          */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1999               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)69	1.2  src/tcpip/usr/include/dhcp_api.h, dhcp, tcpip530 6/9/99 23:05:51 */

#ifndef _DHCP_API_H_
#define _DHCP_API_H_

struct dhcpmessage
  {
          uint8_t         op;
          uint8_t         htype;
          uint8_t         hlen;
          uint8_t         hops;
          uint32_t        xid;
          uint16_t        secs;
          uint16_t        flags;
          uint32_t        ciaddr;
          uint32_t        yiaddr;
          uint32_t        siaddr;
          uint32_t        giaddr;
          uint8_t         chaddr[16];
          uint8_t         sname[64];
          uint8_t         file[128];
          uint8_t         options[1];
  };

struct dhcpoption
  {
          uint8_t         code;
          uint8_t         len;
          uint8_t         data[1];
  };

struct dhcpclientid
  {
          uint8_t         type;
          uint8_t         len;
          uint8_t         id[64];
  };


enum dhcplogseverity
  {
          dhcplog_syserr = 1 ,
          dhcplog_objerr ,
          dhcplog_protocol ,
          dhcplog_warning ,
          dhcplog_event ,
          dhcplog_action ,
          dhcplog_info ,
          dhcplog_accounting ,
          dhcplog_stats ,
          dhcplog_trace
  };

extern void dhcpapi_logmessage(enum dhcplogseverity s ,
                               char * ,
                               ... );


#endif /* _DHCP_API_H_ */
