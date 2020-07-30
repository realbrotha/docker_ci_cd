/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/kernel/sys/IbUserProto.h 1.5                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 2005,2008              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)11  1.5  src/bos/kernel/sys/IbUserProto.h, sysxicm, bos53Q, q2008_19B9 4/24/08 16:23:10 */
/*****************************************************************************
 * COMPONENT_NAME: sysxicm
 *
 * ORIGINS: 27
 *
 * MODULE: Infiniband: User Application Library Prototypes
 *
 *****************************************************************************/

#ifndef _H_IB_U_PROTO
#define _H_IB_U_PROTO

/*****************************************************************************
 *                      BASE USER LIBRARY PROTOTYPES
 *****************************************************************************/

/*********************** General Prototypes **************************/
extern IbDevice_t ** IbGetDeviceList(int *devcnt);
extern const char * IbGetDeviceName(IbDevice_t *IbDevice);
extern const char * IbGetDeviceId (IbDevice_t *IbDevice);

/*********************** Address Handle Prototypes **************************/
extern int IbAddrHandleCreate(
	IbAhCreateCb_t *pAhCreateCb);

extern int IbAddrHandleDestroy(
	IbAhDestroyCb_t *pAhDestroyCb);

extern int IbAddrHandleModify(
	IbAhModifyCb_t *pAhModifyCb);

extern int IbAddrHandleQuery(
	IbAhQueryCb_t *pAhQueryCb);

/*********************** Callback Prototypes ********************************/
/* Asynchronous Event Callback */
extern void IbEqCallBack(
	Ib64bit UserCorrelator,
	IbHandle_t HcaHandle,
	IbEventTypes_t EventType,
	IbEqEvent_t *pEqEvent);

/* Communication Management Event Callback */
extern void IbCmCallBack(
	Ib64bit UserCorrelator,
	IbHandle_t HcaHandle,
	IbEventTypes_t EventType,
	IbCmEvent_t *pCmEvent);

/* Completion Queue Event Callback */
extern void IbCqCallBack(
	Ib64bit UserCorrelator,
	IbHandle_t HcaHandle,
	IbEventTypes_t EventType,
	IbHandle_t CqHandle);

/*********************** Connection Prototypes ******************************/
extern int IbCmAccept(
	IbAcceptCb_t *pAcceptCb);

extern int IbCmConnect(
	IbConnectCb_t *pConnectCb);

extern int IbCmBusy(
	IbBusyCb_t *pBusyCb);

extern int IbCmDisconnect(
	IbDisconnectCb_t *pDisconnectCb);

extern int IbCmListen(
	IbListenCb_t *pListenCb);

extern int IbCmReady(
	IbReadyCb_t *pReadyCb);

extern int IbCmReject(
	IbRejectCb_t *pRejectCb);

extern int IbCmStopListen(
	IbUnlistenCb_t *pUnlistenCb);

/*********************** Completion Queue Prototypes ************************/
extern int IbCqCreate(
	IbCqCreateCb_t *pCqCreateCb);

extern int IbCqDestroy(
	IbCqDestroyCb_t *pCqDestroyCb);

extern int IbCqPoll(
	IbCqPollCb_t *pCqPollCb);

extern int IbCqQuery(
	IbCqQueryCb_t *pCqQueryCb);

extern int IbCqReqNotify(
	IbCqReqNotifyCb_t *pCqReqNotifyCb);

extern int IbCqResize(
	IbCqResizeCb_t *pCqResizeCb);

/*********************** Event Queue Prototypes *****************************/
extern int IbSetCqHandler(
	IbCqRegHandlerCb_t *pCqRegHandlerCb);

extern int IbSetAsyncHandler(
	IbSetHandlerCb_t *pSetAsyncHandlerCb);

extern int IbSetCmHandler(
	IbSetHandlerCb_t *pSetCmHandlerCb);

/*********************** HCA Prototypes *************************************/
extern int IbHcaClose(
	IbHandle_t HcaHandle);

extern int IbHcaOpen(
	IbHcaOpenCb_t *pHcaOpenCb);

extern int IbHcaQuery(
	IbHcaQueryCb_t *pHcaQueryCb);

extern int IbHcaQueryPort(
	IbHcaQueryPortCb_t *pHcaQueryPortCb);

extern int IbHcaQueryInfo(
	IbHcaQueryInfoCb_t *pHcaQueryInfoCb);

/*********************** Multicast Prototypes *******************************/
extern int IbMcastAttach(
	IbMcastAttachCb_t *pMcastAttachCb);

extern int IbMcastDetach(
	IbMcastDetachCb_t *pMcastDetachCb);

extern int IbMcastFetchRecords(
	IbMcastCtl_t *pMcastCtl);

extern int IbMcastGroupJoin(
	IbMcastCtl_t *pMcastCtl);

extern int IbMcastGroupLeave(
	IbMcastCtl_t *pMcastCtl);

extern int IbMcastGroupQuery(
	IbMcastCtl_t *pMcastCtl);

extern int IbMcastSubscribe(
	IbMcastSubscrCb_t *pMcastSubscrCb);

extern int IbMcastUnSubscribe(
	IbMcastUnSubscrCb_t *pMcastUnSubscrCb);

/*********************** Memory Region Prototypes ***************************/
extern int IbMemRegionDereg(
	IbMrDeregCb_t *pMrDeregCb);

extern int IbMemRegionQuery(
	IbMrQueryCb_t *pMrQueryCb);

extern int IbMemRegionReg(
	IbMrRegisterCb_t *pMrRegisterCb);

extern int IbMemRegionRegPhys(
	IbMrRegPhysCb_t *pMrRegPhysCb);

extern int IbMemRegionRegShared(
	IbMrRegSharedCb_t *pMrRegSharedCb);

/*********************** Memory Window Prototypes ***************************/
extern int IbMemWindowAlloc(
	IbMwAllocCb_t *pMwAllocCb);

extern int IbMemWindowBind(
	IbMwBindCb_t *pMwBindCb);

extern int IbMemWindowDealloc(
	IbMwDeallocCb_t *pMwDeallocCb);

extern int IbMemWindowQuery(
	IbMwQueryCb_t *pMwQueryCb);

/*********************** Protection Domain Prototypes ***********************/
extern int IbPdAlloc(
	IbPdAllocCb_t *pPdAllocCb);

extern int IbPdDealloc(
	IbPdDeallocCb_t *pPdDeallocCb);

/*********************** Path Prototypes ************************************/
extern int IbPathAltRsp(
	IbPathAltRspCb_t *pPathAltRspCb);
	
extern int IbPathFetchRecords(
	IbPathFetchCb_t *pPathFetchCb);

extern int IbPathFind(
	IbPathFindCb_t *pPathFindCb);

extern int IbPathLoadAlternate(
	IbLoadAltPathCb_t *pLoadAltPathCb);

/*********************** Queue Pair Prototypes ******************************/
extern int IbQpCreate(
	IbQpCreateCb_t *pQpCreateCb);

extern int IbQpDestroy(
	IbQpDestroyCb_t *pQpDestroyCb);

extern int IbQpModify(
	IbQpModifyCb_t *pQpModifyCb);

extern int IbQpPostSend(
	IbQpPostSendCb_t *pQpPostSendCb);

extern int IbQpPostRecv(
	IbQpPostRecvCb_t *pQpPostRecvCb);

extern int IbQpQuery(
	IbQpQueryCb_t *pQpQueryCb);

/*********************** Service ID Prototypes ******************************/
extern int IbServiceFind(
	IbServiceFindCb_t *pServiceFindCb);

extern int IbServiceRegister(
	IbServiceRegCb_t *pServiceRegCb);

extern int IbServiceReply(
	IbServiceReplyCb_t *pServiceReplyCb);

extern int IbServiceUnregister(
	IbServiceUnregCb_t *pServiceUnregCb);

/*********************** Special Queue Pair Prototypes **********************/
extern int IbSpecialQpGet(
	IbSpecialQpGetCb_t *pSpecialQpGetCb);

#endif /* _H_IB_U_PROTO */

