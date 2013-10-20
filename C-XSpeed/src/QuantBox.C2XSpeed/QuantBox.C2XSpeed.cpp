// QuantBox.C2CTP.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "QuantBox.C2XSpeed.h"

#include "MdUserApi.h"
#include "TraderApi.h"
#include "XSpeedMsgQueue.h"

inline CXSpeedMsgQueue* XSpeed_GetQueue(void* pMsgQueue)
{
	return static_cast<CXSpeedMsgQueue*>(pMsgQueue);
}

inline CMdUserApi* MD_GetApi(void* pMdUserApi)
{
	return static_cast<CMdUserApi*>(pMdUserApi);
}

inline CTraderApi* TD_GetApi(void* pTraderApi)
{
	return static_cast<CTraderApi*>(pTraderApi);
}


QUANTBOXC2XSPEED_API void* __stdcall XSpeed_CreateMsgQueue()
{
	return new CXSpeedMsgQueue();
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_ReleaseMsgQueue(void* pMsgQueue)
{
	if(pMsgQueue)
	{
		delete XSpeed_GetQueue(pMsgQueue);
	}
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnConnect(void* pMsgQueue,fnOnConnect pCallback)
{
	if(pMsgQueue)
	{
		XSpeed_GetQueue(pMsgQueue)->RegisterCallback(pCallback);
	}
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnDisconnect(void* pMsgQueue,fnOnDisconnect pCallback)
{
	if(pMsgQueue)
	{
		XSpeed_GetQueue(pMsgQueue)->RegisterCallback(pCallback);
	}
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspError(void* pMsgQueue,fnOnRspError pCallback)
{
	if(pMsgQueue)
	{
		XSpeed_GetQueue(pMsgQueue)->RegisterCallback(pCallback);
	}
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspInsertOrder(void* pMsgQueue,fnOnRspInsertCancelOrder pCallback)
{
	if(pMsgQueue)
	{
		XSpeed_GetQueue(pMsgQueue)->RegisterCallback_OnRspInsertOrder(pCallback);
	}
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspCancelOrder(void* pMsgQueue,fnOnRspInsertCancelOrder pCallback)
{
	if(pMsgQueue)
	{
		XSpeed_GetQueue(pMsgQueue)->RegisterCallback_OnRspCancelOrder(pCallback);
	}
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspQryExchangeInstrument(void* pMsgQueue,fnOnRspQryExchangeInstrument pCallback)
{
	if(pMsgQueue)
	{
		XSpeed_GetQueue(pMsgQueue)->RegisterCallback(pCallback);
	}
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspArbitrageInstrument(void* pMsgQueue,fnOnRspArbitrageInstrument pCallback)
{
	if(pMsgQueue)
	{
		XSpeed_GetQueue(pMsgQueue)->RegisterCallback(pCallback);
	}
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspQrySpecifyInstrument(void* pMsgQueue,fnOnRspQrySpecifyInstrument pCallback)
{
	if(pMsgQueue)
	{
		XSpeed_GetQueue(pMsgQueue)->RegisterCallback(pCallback);
	}
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspQryPosition(void* pMsgQueue,fnOnRspQryPosition pCallback)
{
	if(pMsgQueue)
	{
		XSpeed_GetQueue(pMsgQueue)->RegisterCallback(pCallback);
	}
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspQryPositionDetail(void* pMsgQueue,fnOnRspQryPositionDetail pCallback)
{
	if(pMsgQueue)
	{
		XSpeed_GetQueue(pMsgQueue)->RegisterCallback(pCallback);
	}
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspQryOrderInfo(void* pMsgQueue,fnOnRspQryOrderInfo pCallback)
{
	if(pMsgQueue)
	{
		XSpeed_GetQueue(pMsgQueue)->RegisterCallback(pCallback);
	}
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspQryMatchInfo(void* pMsgQueue,fnOnRspQryMatchInfo pCallback)
{
	if(pMsgQueue)
	{
		XSpeed_GetQueue(pMsgQueue)->RegisterCallback(pCallback);
	}
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspCustomerCapital(void* pMsgQueue,fnOnRspCustomerCapital pCallback)
{
	if(pMsgQueue)
	{
		XSpeed_GetQueue(pMsgQueue)->RegisterCallback(pCallback);
	}
}


QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnMarketData(void* pMsgQueue,fnOnMarketData pCallback)
{
	if(pMsgQueue)
	{
		XSpeed_GetQueue(pMsgQueue)->RegisterCallback(pCallback);
	}
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRtnCancelOrder(void* pMsgQueue,fnOnRtnCancelOrder pCallback)
{
	if(pMsgQueue)
	{
		XSpeed_GetQueue(pMsgQueue)->RegisterCallback(pCallback);
	}
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRtnInstrumentStatus(void* pMsgQueue,fnOnRtnInstrumentStatus pCallback)
{
	if(pMsgQueue)
	{
		XSpeed_GetQueue(pMsgQueue)->RegisterCallback(pCallback);
	}
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRtnOrder(void* pMsgQueue,fnOnRtnOrder pCallback)
{
	if(pMsgQueue)
	{
		XSpeed_GetQueue(pMsgQueue)->RegisterCallback(pCallback);
	}
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRtnMatchedInfo(void* pMsgQueue,fnOnRtnMatchedInfo pCallback)
{
	if(pMsgQueue)
	{
		XSpeed_GetQueue(pMsgQueue)->RegisterCallback(pCallback);
	}
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspQuoteSubscribe(void* pMsgQueue,fnOnRspQuoteSubscribe pCallback)
{
	if(pMsgQueue)
	{
		XSpeed_GetQueue(pMsgQueue)->RegisterCallback(pCallback);
	}
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRtnQuoteSubscribe(void* pMsgQueue,fnOnRtnQuoteSubscribe pCallback)
{
	if(pMsgQueue)
	{
		XSpeed_GetQueue(pMsgQueue)->RegisterCallback(pCallback);
	}
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspQuoteInsertOrder(void* pMsgQueue,fnOnRspQuoteInsertCancelOrder pCallback)
{
	if(pMsgQueue)
	{
		XSpeed_GetQueue(pMsgQueue)->RegisterCallback_OnRspQuoteInsertOrder(pCallback);
	}
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspQuoteCancelOrder(void* pMsgQueue,fnOnRspQuoteInsertCancelOrder pCallback)
{
	if(pMsgQueue)
	{
		XSpeed_GetQueue(pMsgQueue)->RegisterCallback_OnRspQuoteCancelOrder(pCallback);
	}
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRtnQuoteCancelOrder(void* pMsgQueue,fnOnRtnQuoteCancelOrder pCallback)
{
	if(pMsgQueue)
	{
		XSpeed_GetQueue(pMsgQueue)->RegisterCallback(pCallback);
	}
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRtnQuoteOrder(void* pMsgQueue,fnOnRtnQuoteOrder pCallback)
{
	if(pMsgQueue)
	{
		XSpeed_GetQueue(pMsgQueue)->RegisterCallback(pCallback);
	}
}

QUANTBOXC2XSPEED_API bool __stdcall XSpeed_ProcessMsgQueue(void* pMsgQueue)
{
	if(pMsgQueue)
	{
		return XSpeed_GetQueue(pMsgQueue)->Process();
	}
	return false;
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_ClearMsgQueue(void* pMsgQueue)
{
	if(pMsgQueue)
	{
		return XSpeed_GetQueue(pMsgQueue)->Clear();
	}
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_StartMsgQueue(void* pMsgQueue)
{
	if(pMsgQueue)
	{
		return XSpeed_GetQueue(pMsgQueue)->StartThread();
	}
}

QUANTBOXC2XSPEED_API void __stdcall XSpeed_StopMsgQueue(void* pMsgQueue)
{
	if(pMsgQueue)
	{
		return XSpeed_GetQueue(pMsgQueue)->StopThread();
	}
}


QUANTBOXC2XSPEED_API void* __stdcall MD_CreateMdApi()
{
	return new CMdUserApi();
}

QUANTBOXC2XSPEED_API void __stdcall MD_RegMsgQueue2MdApi(void* pMdUserApi,void* pMsgQueue)
{
	if(pMdUserApi)
	{
		MD_GetApi(pMdUserApi)->RegisterMsgQueue((CXSpeedMsgQueue*)pMsgQueue);
	}
}

QUANTBOXC2XSPEED_API void __stdcall MD_Connect(
	void* pMdUserApi,
	const char* szSvrAddr,
	const char* szAccountID,
	const char* szPassword,
	short sCompanyID)
{
	if(pMdUserApi
		&&szSvrAddr
		&&szAccountID
		&&szPassword)
	{
		MD_GetApi(pMdUserApi)->Connect(szSvrAddr,szAccountID,szPassword,sCompanyID);
	}
}

QUANTBOXC2XSPEED_API void __stdcall MD_Disconnect(void* pMdUserApi)
{
	if(pMdUserApi)
	{
		MD_GetApi(pMdUserApi)->Disconnect();
	}
}

QUANTBOXC2XSPEED_API void __stdcall MD_Subscribe(void* pMdUserApi,const char* szInstrumentIDs)
{
	if(pMdUserApi
		&&szInstrumentIDs)
	{
		MD_GetApi(pMdUserApi)->Subscribe(szInstrumentIDs);
	}
}

QUANTBOXC2XSPEED_API void __stdcall MD_Unsubscribe(void* pMdUserApi,const char* szInstrumentIDs)
{
	if(pMdUserApi
		&&szInstrumentIDs)
	{
		MD_GetApi(pMdUserApi)->Unsubscribe(szInstrumentIDs);
	}
}

QUANTBOXC2XSPEED_API void __stdcall MD_ReleaseMdApi(void* pMdUserApi)
{
	if(pMdUserApi)
	{
		delete MD_GetApi(pMdUserApi);
	}
}

QUANTBOXC2XSPEED_API void* __stdcall TD_CreateTdApi()
{
	return new CTraderApi();
}

QUANTBOXC2XSPEED_API void __stdcall TD_RegMsgQueue2TdApi(void* pTraderApi,void* pMsgQueue)
{
	if(pTraderApi)
	{
		TD_GetApi(pTraderApi)->RegisterMsgQueue((CXSpeedMsgQueue*)pMsgQueue);
	}
}

QUANTBOXC2XSPEED_API void __stdcall TD_Connect(
	void* pTraderApi,
	const char* szSvrAddr,
	const char* szAccountID,
	const char* szPassword,
	short sCompanyID)
{
	if(pTraderApi
		&&szSvrAddr
		&&szAccountID
		&&szPassword)
	{
		TD_GetApi(pTraderApi)->Connect(szSvrAddr,szAccountID,szPassword,sCompanyID);
	}
}

QUANTBOXC2XSPEED_API int __stdcall TD_SendOrder(
	void* pTraderApi,
	long localOrderID,
	const char* szInstrumentId,
	DFITCBuySellTypeType sBuySellType,
	DFITCOpenCloseTypeType sOpenCloseType,
	DFITCSpeculatorType sSpeculator,
	DFITCAmountType lAmount,
	DFITCPriceType dbPrice,
	DFITCOrderTypeType orderType,
	DFITCOrderPropertyType orderProperty,
	DFITCInstrumentTypeType nInstrumentType)
{
	if(pTraderApi
		&&szInstrumentId)
	{
		return TD_GetApi(pTraderApi)->ReqInsertOrder(
			localOrderID,
			szInstrumentId,
			sBuySellType,
			sOpenCloseType,
			sSpeculator,
			lAmount,
			dbPrice,
			orderType,
			orderProperty,
			nInstrumentType);
	}
	return 0;
}

QUANTBOXC2XSPEED_API void __stdcall TD_CancelOrder(
	void* pTraderApi,
	const char* szInstrumentId,
	DFITCLocalOrderIDType localOrderID,
	DFITCSPDOrderIDType spdOrderID)
{
	if(pTraderApi
		&&szInstrumentId)
	{
		TD_GetApi(pTraderApi)->ReqCancelOrder(
			szInstrumentId,
			localOrderID,
			spdOrderID);
	}
}

QUANTBOXC2XSPEED_API int __stdcall TD_SendQuoteOrder(
	void* pTraderApi,
	long localOrderID,
	const char* szInstrumentId,
	const char* quoteID,
	DFITCAmountType bOrderAmount,
	DFITCAmountType sOrderAmount,
	DFITCPriceType bInsertPrice,
	DFITCPriceType sInsertPrice,
	DFITCOpenCloseTypeType bOpenCloseType,
	DFITCOpenCloseTypeType sOpenCloseType,
	DFITCSpeculatorType bSpeculator,
	DFITCSpeculatorType sSpeculator,
	DFITCStayTimeType stayTime,
	DFITCInstrumentTypeType nInstrumentType)
{
	if(pTraderApi
		&&szInstrumentId)
	{
		return TD_GetApi(pTraderApi)->ReqQuoteInsertOrder(
			localOrderID,
			szInstrumentId,
			quoteID,
			bOrderAmount,
			sOrderAmount,
			bInsertPrice,
			sInsertPrice,
			bOpenCloseType,
			sOpenCloseType,
			bSpeculator,
			sSpeculator,
			stayTime,
			nInstrumentType);
	}
	return 0;
}

QUANTBOXC2XSPEED_API void __stdcall TD_CancelQuoteOrder(
	void* pTraderApi,
	const char* szInstrumentId,
	DFITCLocalOrderIDType localOrderID,
	DFITCSPDOrderIDType spdOrderID)
{
	if(pTraderApi
		&&szInstrumentId)
	{
		TD_GetApi(pTraderApi)->ReqQuoteCancelOrder(
			szInstrumentId,
			localOrderID,
			spdOrderID);
	}
}


QUANTBOXC2XSPEED_API void __stdcall TD_Disconnect(void* pTraderApi)
{
	if(pTraderApi)
	{
		TD_GetApi(pTraderApi)->Disconnect();
	}
}

QUANTBOXC2XSPEED_API void __stdcall TD_ReleaseTdApi(void* pTraderApi)
{
	if(pTraderApi)
	{
		delete TD_GetApi(pTraderApi);
	}
}

QUANTBOXC2XSPEED_API void __stdcall TD_ReqQryPosition(void* pTraderApi,const char* szInstrumentId)
{
	if(pTraderApi)
	{
		TD_GetApi(pTraderApi)->ReqQryPosition(szInstrumentId);
	}
}

QUANTBOXC2XSPEED_API void __stdcall TD_ReqQryPositionDetail(void* pTraderApi,const char* szInstrumentId)
{
	if(pTraderApi)
	{
		TD_GetApi(pTraderApi)->ReqQryPositionDetail(szInstrumentId);
	}
}

QUANTBOXC2XSPEED_API void __stdcall TD_ReqQryCustomerCapital(void* pTraderApi)
{
	if(pTraderApi)
	{
		TD_GetApi(pTraderApi)->ReqQryCustomerCapital();
	}
}

QUANTBOXC2XSPEED_API void __stdcall TD_ReqQryExchangeInstrument(void* pTraderApi,const char* szExchangeId,DFITCInstrumentTypeType instrumentType)
{
	if(pTraderApi)
	{
		TD_GetApi(pTraderApi)->ReqQryExchangeInstrument(szExchangeId,instrumentType);
	}
}

QUANTBOXC2XSPEED_API void __stdcall TD_ReqQryArbitrageInstrument(void* pTraderApi,const char* szExchangeId)
{
	if(pTraderApi)
	{
		TD_GetApi(pTraderApi)->ReqQryArbitrageInstrument(szExchangeId);
	}
}

QUANTBOXC2XSPEED_API void __stdcall TD_ReqQrySpecifyInstrument(void* pTraderApi,const char* szInstrumentId,const char* szExchangeId,DFITCInstrumentTypeType instrumentType)
{
	if(pTraderApi)
	{
		TD_GetApi(pTraderApi)->ReqQrySpecifyInstrument(szInstrumentId,szExchangeId,instrumentType);
	}
}

QUANTBOXC2XSPEED_API void __stdcall TD_ReqQryMatchInfo(void* pTraderApi,DFITCInstrumentTypeType instrumentType)
{
	if(pTraderApi)
	{
		TD_GetApi(pTraderApi)->ReqQryMatchInfo(instrumentType);
	}
}

QUANTBOXC2XSPEED_API void __stdcall TD_ReqQryOrderInfo(void* pTraderApi,DFITCInstrumentTypeType instrumentType)
{
	if(pTraderApi)
	{
		TD_GetApi(pTraderApi)->ReqQryOrderInfo(instrumentType);
	}
}

QUANTBOXC2XSPEED_API void __stdcall TD_ReqQuoteSubscribe(void* pTraderApi)
{
	if(pTraderApi)
	{
		TD_GetApi(pTraderApi)->ReqQuoteSubscribe();
	}
}

void WriteLog( const char *fmt, ...)
{
    char buff[1024];
    va_list vl;
    va_start (vl, fmt);
    _vsnprintf (buff, 10240, fmt, vl);
    fflush (stdout);
    va_end (vl);
   char temp[2048]="XSpeed:";
   OutputDebugStringA(strcat(temp,buff));
}