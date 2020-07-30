/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* tcpip530 src/tcpip/usr/lib/libslp/slp.h 1.2                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2004               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)19       1.2  src/tcpip/usr/lib/libslp/slp.h, slp, tcpip530 4/7/04 14:37:19 */

#ifndef SLP_INCLUDE
#define SLP_INCLUDE

#ifdef  __cplusplus
extern "C" {
#endif

/* 
 * Reference RFC 2614 for the following definition. 
 */

#define SLP_LIFETIME_DEFAULT 10800     /* 3 hours  */
#define SLP_LIFETIME_MAXIMUM 65535     /* 18 hours */

typedef enum {
     SLP_LAST_CALL                    = 1,
     SLP_OK                           = 0,
     SLP_LANGUAGE_NOT_SUPPORTED       = -1,
     SLP_PARSE_ERROR                  = -2,
     SLP_INVALID_REGISTRATION         = -3,
     SLP_SCOPE_NOT_SUPPORTED          = -4,
     SLP_AUTHENTICATION_ABSENT        = -6,
     SLP_AUTHENTICATION_FAILED        = -7,
     SLP_INVALID_UPDATE               = -13,
     SLP_REFRESH_REJECTED             = -15,
     SLP_NOT_IMPLEMENTED              = -17,
     SLP_BUFFER_OVERFLOW              = -18,
     SLP_NETWORK_TIMED_OUT            = -19,
     SLP_NETWORK_INIT_FAILED          = -20,
     SLP_MEMORY_ALLOC_FAILED          = -21,
     SLP_PARAMETER_BAD                = -22,
     SLP_NETWORK_ERROR                = -23,
     SLP_INTERNAL_SYSTEM_ERROR        = -24,
     SLP_HANDLE_IN_USE                = -25,
     SLP_TYPE_ERROR                   = -26
} SLPError ;

typedef enum {
     SLP_FALSE = 0,
     SLP_TRUE  = 1
} SLPBoolean;

typedef struct srvurl {
     char *s_pcSrvType;
     char *s_pcHost;
     int   s_iPort;
     char *s_pcNetFamily;
     char *s_pcSrvPart;
} SLPSrvURL;

typedef void* SLPHandle;

typedef void SLPRegReport(SLPHandle hSLP,
                          SLPError errCode,
                          void *pvCookie);

typedef SLPBoolean SLPSrvTypeCallback(SLPHandle hSLP,
                                      const char* pcSrvTypes,
                                      SLPError errCode,
                                      void *pvCookie);

typedef SLPBoolean SLPSrvURLCallback(SLPHandle hSLP,
                                     const char* pcSrvURL,
                                     unsigned short sLifetime,
                                     SLPError errCode,
                                     void *pvCookie);

typedef SLPBoolean SLPAttrCallback(SLPHandle hSLP,
                                   const char* pcAttrList,
                                   SLPError errCode,
                                   void *pvCookie);

SLPError SLPOpen(const char *pcLang, SLPBoolean isAsync, SLPHandle *phSLP);

void SLPClose(SLPHandle hSLP);

void SLPFree(void* pvMem);

SLPError SLPFindSrvs(SLPHandle  hSLP,
                     const char *pcServiceType,
                     const char *pcScopeList,
                     const char *pcSearchFilter,
                     SLPSrvURLCallback callback,
                     void *pvCookie);

SLPError SLPFindSrvTypes(SLPHandle    hSLP,
                         const char  *pcNamingAuthority,
                         const char  *pcScopeList,
                         SLPSrvTypeCallback callback,
                         void *pvCookie);
SLPError SLPFindAttrs(SLPHandle   hSLP,
                         const char *pcURLOrServiceType,
                         const char *pcScopeList,
                         const char *pcAttrIds,
                         SLPAttrCallback callback,
                         void *pvCookie);

SLPError SLPParseSrvURL(char *pcSrvURL,
                        SLPSrvURL** ppSrvURL);

SLPError SLPEscape(const char* pcInbuf,
                   char** ppcOutBuf,
                   SLPBoolean isTag);

SLPError SLPUnescape(const char* pcInbuf,
                     char** ppcOutBuf,
                     SLPBoolean isTag);

const char* SLPGetProperty(const char* pcName);

SLPError SLPFindScopes(SLPHandle hSLP,
                       char** ppcScopeList);

SLPError SLPReg(SLPHandle   hSLP,
                const char  *pcSrvURL,
                const unsigned short usLifetime,
                const char  *pcSrvType,
                const char  *pcAttrs,
                SLPBoolean  fresh,
                SLPRegReport callback,
                void *pvCookie);

SLPError SLPDereg(SLPHandle  hSLP,
                  const char *pcURL,
                  SLPRegReport callback,
                  void *pvCookie);

SLPError SLPDelAttrs(SLPHandle   hSLP,
                     const char  *pcURL,
                     const char  *pcAttrs,
                     SLPRegReport callback,
                     void *pvCookie);

unsigned short SLPGetRefreshInterval();

void SLPSetProperty(const char *pcName,
                    const char *pcValue);

#ifdef  __cplusplus
}
#endif

#endif /* SLP_INCLUDE */
