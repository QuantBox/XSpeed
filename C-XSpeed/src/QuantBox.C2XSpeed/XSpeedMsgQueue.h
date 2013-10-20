#pragma once

#include "QuantBox.C2XSpeed.h"
#include "include\LockFreeQ.h"

class CXSpeedMsgQueue
{
	//响应队列中可能出现的消息类型（按字母排序）
	enum EnumMsgType
	{
		E_fnOnConnect,	
		E_fnOnDisconnect,
		E_fnOnMarketData,
		E_fnOnRspArbitrageInstrument,
		E_fnOnRspCancelOrder,
		E_fnOnRspCustomerCapital,
		E_fnOnRspError,
		E_fnOnRspInsertOrder,		
		E_fnOnRspQryExchangeInstrument,
		E_fnOnRspQryMatchInfo,
		E_fnOnRspQryOrderInfo,
		E_fnOnRspQryPosition,
		E_fnOnRspQryPositionDetail,
		E_fnOnRspQrySpecifyInstrument,
		E_fnOnRtnCancelOrder,
		E_fnOnRtnInstrumentStatus,
		E_fnOnRtnMatchedInfo,
		E_fnOnRtnOrder,

		E_fnOnRspQuoteSubscribe,
		E_fnOnRtnQuoteSubscribe,
		E_fnOnRspQuoteInsertOrder,
		E_fnOnRspQuoteCancelOrder,
		E_fnOnRtnQuoteCancelOrder,
		E_fnOnRtnQuoteOrder,
	};

	struct SMsgItem
	{
		EnumMsgType							type;			//消息类型
		void*								pApi;			//指向类对象的指针
		DFITCErrorRtnField					RspInfo;		//响应信息
		bool								bIsLast;
		void*								pBuf;
	};

public:
	CXSpeedMsgQueue(void)
	{
		m_hThread = NULL;
		m_bRunning = false;

		//回调函数地址指针
		m_fnOnConnect = NULL;
		m_fnOnDisconnect = NULL;
		m_fnOnMarketData = NULL;
		m_fnOnRspArbitrageInstrument = NULL;
		m_fnOnRspCancelOrder = NULL;
		m_fnOnRspCustomerCapital = NULL;
		m_fnOnRspError = NULL;
		m_fnOnRspInsertOrder = NULL;
		m_fnOnRspQryExchangeInstrument = NULL;
		m_fnOnRspQryMatchInfo = NULL;		
		m_fnOnRspQryOrderInfo = NULL;		
		m_fnOnRspQryPosition = NULL;
		m_fnOnRspQryPositionDetail = NULL;				
		m_fnOnRspQrySpecifyInstrument = NULL;
		m_fnOnRtnCancelOrder = NULL;
		m_fnOnRtnInstrumentStatus = NULL;
		m_fnOnRtnMatchedInfo = NULL;
		m_fnOnRtnOrder = NULL;

		m_fnOnRspQuoteSubscribe = NULL;
		m_fnOnRtnQuoteSubscribe = NULL;
		m_fnOnRspQuoteInsertOrder = NULL;
		m_fnOnRspQuoteCancelOrder = NULL;
		m_fnOnRtnQuoteCancelOrder = NULL;
		m_fnOnRtnQuoteOrder = NULL;
		
		m_hEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
	}
	virtual ~CXSpeedMsgQueue(void)
	{
		StopThread();
		Clear();

		CloseHandle(m_hEvent);
	}

public:
	//清空队列
	void Clear();

	//可以由外部发起，顺序处理队列触发回调函数
	bool Process();

	//由内部启动线程，内部主动调用Process触发回调
	void StartThread();
	void StopThread();

	//将外部的函数地址注册到队列(按字母排序)
	void RegisterCallback(fnOnConnect pCallback){m_fnOnConnect = pCallback;}
	void RegisterCallback(fnOnDisconnect pCallback){m_fnOnDisconnect = pCallback;}
	void RegisterCallback(fnOnMarketData pCallback){m_fnOnMarketData = pCallback;}
	void RegisterCallback(fnOnRspArbitrageInstrument pCallback){m_fnOnRspArbitrageInstrument = pCallback;}
	void RegisterCallback_OnRspCancelOrder(fnOnRspInsertCancelOrder pCallback){m_fnOnRspCancelOrder = pCallback;}
	void RegisterCallback(fnOnRspCustomerCapital pCallback){m_fnOnRspCustomerCapital = pCallback;}
	void RegisterCallback(fnOnRspError pCallback){m_fnOnRspError = pCallback;}
	void RegisterCallback_OnRspInsertOrder(fnOnRspInsertCancelOrder pCallback){m_fnOnRspInsertOrder = pCallback;}
	void RegisterCallback(fnOnRspQryExchangeInstrument pCallback){m_fnOnRspQryExchangeInstrument = pCallback;}
	void RegisterCallback(fnOnRspQryMatchInfo pCallback){m_fnOnRspQryMatchInfo = pCallback;}
	void RegisterCallback(fnOnRspQryOrderInfo pCallback){m_fnOnRspQryOrderInfo = pCallback;}
	void RegisterCallback(fnOnRspQryPosition pCallback){m_fnOnRspQryPosition = pCallback;}
	void RegisterCallback(fnOnRspQryPositionDetail pCallback){m_fnOnRspQryPositionDetail = pCallback;}
	void RegisterCallback(fnOnRspQrySpecifyInstrument pCallback){m_fnOnRspQrySpecifyInstrument = pCallback;}
	void RegisterCallback(fnOnRtnCancelOrder pCallback){m_fnOnRtnCancelOrder = pCallback;}
	void RegisterCallback(fnOnRtnInstrumentStatus pCallback){m_fnOnRtnInstrumentStatus = pCallback;}
	void RegisterCallback(fnOnRtnMatchedInfo pCallback){m_fnOnRtnMatchedInfo = pCallback;}
	void RegisterCallback(fnOnRtnOrder pCallback){m_fnOnRtnOrder = pCallback;}
	void RegisterCallback(fnOnRspQuoteSubscribe pCallback){m_fnOnRspQuoteSubscribe = pCallback;}
	void RegisterCallback(fnOnRtnQuoteSubscribe pCallback){m_fnOnRtnQuoteSubscribe = pCallback;}
	void RegisterCallback_OnRspQuoteInsertOrder(fnOnRspQuoteInsertCancelOrder pCallback){m_fnOnRspQuoteInsertOrder = pCallback;}
	void RegisterCallback_OnRspQuoteCancelOrder(fnOnRspQuoteInsertCancelOrder pCallback){m_fnOnRspQuoteCancelOrder = pCallback;}
	void RegisterCallback(fnOnRtnQuoteCancelOrder pCallback){m_fnOnRtnQuoteCancelOrder = pCallback;}
	void RegisterCallback(fnOnRtnQuoteOrder pCallback){m_fnOnRtnQuoteOrder = pCallback;}


	//响应结果处理后入队列(按字母排序)
	void Input_OnConnect(void* pApi,DFITCUserLoginInfoRtnField *pRspUserLogin,ConnectionStatus result);
	void Input_OnDisconnect(void* pApi,DFITCErrorRtnField *pRspInfo,ConnectionStatus step);
	void Input_OnRspError(void* pApi,DFITCErrorRtnField* pRspInfo);
	void Input_OnRspCancelOrder(void* pTraderApi,DFITCOrderRspDataRtnField *pOrderCanceledRtn,DFITCErrorRtnField *pErrorInfo);
	void Input_OnRspInsertOrder(void* pTraderApi,DFITCOrderRspDataRtnField * pOrderRtn,DFITCErrorRtnField * pErrorInfo);
	void Input_OnRspQryPosition(void* pTraderApi,DFITCPositionInfoRtnField * pPositionInfoRtn,DFITCErrorRtnField * pErrorInfo, bool bIsLast);
	void Input_OnRspQryPositionDetail(void* pTraderApi,DFITCPositionDetailRtnField * pPositionDetailRtn,DFITCErrorRtnField * pErrorInfo, bool bIsLast);
	void Input_OnRspQryExchangeInstrument(void* pTraderApi,DFITCExchangeInstrumentRtnField * pInstrumentData,DFITCErrorRtnField * pErrorInfo, bool bIsLast);
	void Input_OnRspArbitrageInstrument(void* pTraderApi,DFITCAbiInstrumentRtnField * pAbiInstrumentData, DFITCErrorRtnField * pErrorInfo, bool bIsLast);
	void Input_OnRspQrySpecifyInstrument(void* pTraderApi,DFITCInstrumentRtnField * pInstrument, DFITCErrorRtnField * pErrorInfo, bool bIsLast);
	void Input_OnRspQryOrderInfo(void* pTraderApi,DFITCOrderCommRtnField * pRtnOrderData,DFITCErrorRtnField * pErrorInfo, bool bIsLast);
	void Input_OnRspQryMatchInfo(void* pTraderApi,DFITCMatchedRtnField * pRtnMatchData,DFITCErrorRtnField * pErrorInfo, bool bIsLast);
	void Input_OnRspCustomerCapital(void* pTraderApi,DFITCCapitalInfoRtnField *pCapitalInfoRtn,DFITCErrorRtnField *pErrorInfo, bool bIsLast);
	void Input_OnMarketData(void* pMdApi,DFITCDepthMarketDataField *pMarketDataField);
	void Input_OnRtnCancelOrder(void* pTraderApi,DFITCOrderCanceledRtnField * pCancelOrderData);
	void Input_OnRtnInstrumentStatus(void* pTraderApi,DFITCInstrumentStatusField *pInstrumentStatus);
	void Input_OnRtnOrder(void* pTraderApi,DFITCOrderRtnField * pRtnOrderData);
	void Input_OnRtnMatchedInfo(void* pTraderApi,DFITCMatchRtnField * pRtnMatchData);

	void Input_OnRspQuoteSubscribe(void* pTraderApi,DFITCQuoteSubscribeRspField * pRspQuoteSubscribeData);
	void Input_OnRtnQuoteSubscribe(void* pTraderApi,DFITCQuoteSubscribeRtnField * pRtnQuoteSubscribeData);
	void Input_OnRspQuoteInsertOrder(void* pTraderApi,DFITCQuoteOrderRspField * pRspQuoteOrderData,DFITCErrorRtnField * pErrorInfo);
	void Input_OnRspQuoteCancelOrder(void* pTraderApi,DFITCQuoteOrderRspField * pRspQuoteOrderData,DFITCErrorRtnField * pErrorInfo);
	void Input_OnRtnQuoteOrder(void* pTraderApi,DFITCQuoteOrderRtnField * pRtnQuoteOrderData);
	void Input_OnRtnQuoteCancelOrder(void* pTraderApi,DFITCQuoteCanceledRtnField * pRtnQuoteCanceledData);
private:
	friend DWORD WINAPI ProcessThread(LPVOID lpParam);
	void RunInThread();

	//响应结果直接入队列
	void _Input_MD(SMsgItem* pMsgItem);
	void _Input_TD(SMsgItem* pMsgItem);
	//队列中的消息判断分发
	void _Output_MD(SMsgItem* pMsgItem);
	void _Output_TD(SMsgItem* pMsgItem);

	//响应输出
	void Output_OnConnect(SMsgItem* pItem)
	{
		if(m_fnOnConnect)
			(*m_fnOnConnect)(pItem->pApi,(DFITCUserLoginInfoRtnField*)pItem->pBuf,(ConnectionStatus)pItem->RspInfo.nErrorID);
	}
	void Output_OnDisconnect(SMsgItem* pItem)
	{
		if(m_fnOnDisconnect)
			(*m_fnOnDisconnect)(pItem->pApi,(DFITCErrorRtnField*)pItem->pBuf,(ConnectionStatus)pItem->RspInfo.nErrorID);
	}
	void Output_OnRspError(SMsgItem* pItem)
	{
		if(m_fnOnRspError)
			(*m_fnOnRspError)(pItem->pApi,&pItem->RspInfo);
	}
	void Output_OnRspCancelOrder(SMsgItem* pItem)
	{
		if(m_fnOnRspCancelOrder)
			(*m_fnOnRspCancelOrder)(pItem->pApi,(DFITCOrderRspDataRtnField*)pItem->pBuf,&pItem->RspInfo);
	}
	void Output_OnRtnCancelOrder(SMsgItem* pItem)
	{
		if(m_fnOnRtnCancelOrder)
			(*m_fnOnRtnCancelOrder)(pItem->pApi,(DFITCOrderCanceledRtnField*)pItem->pBuf);
	}
	void Output_OnRspInsertOrder(SMsgItem* pItem)
	{
		if(m_fnOnRspInsertOrder)
			(*m_fnOnRspInsertOrder)(pItem->pApi,(DFITCOrderRspDataRtnField*)pItem->pBuf,&pItem->RspInfo);
	}
	void Output_OnRspQryPosition(SMsgItem* pItem)
	{
		if(m_fnOnRspQryPosition)
			(*m_fnOnRspQryPosition)(pItem->pApi,(DFITCPositionInfoRtnField*)pItem->pBuf,&pItem->RspInfo,pItem->bIsLast);
	}
	void Output_OnRspQryPositionDetail(SMsgItem* pItem)
	{
		if(m_fnOnRspQryPositionDetail)
			(*m_fnOnRspQryPositionDetail)(pItem->pApi,(DFITCPositionDetailRtnField*)pItem->pBuf,&pItem->RspInfo,pItem->bIsLast);
	}
	void Output_OnRspQryExchangeInstrument(SMsgItem* pItem)
	{
		if(m_fnOnRspQryExchangeInstrument)
			(*m_fnOnRspQryExchangeInstrument)(pItem->pApi,(DFITCExchangeInstrumentRtnField*)pItem->pBuf,&pItem->RspInfo,pItem->bIsLast);
	}
	void Output_OnRspArbitrageInstrument(SMsgItem* pItem)
	{
		if(m_fnOnRspArbitrageInstrument)
			(*m_fnOnRspArbitrageInstrument)(pItem->pApi,(DFITCAbiInstrumentRtnField*)pItem->pBuf,&pItem->RspInfo,pItem->bIsLast);
	}
	void Output_OnRspQrySpecifyInstrument(SMsgItem* pItem)
	{
		if(m_fnOnRspQrySpecifyInstrument)
			(*m_fnOnRspQrySpecifyInstrument)(pItem->pApi,(DFITCInstrumentRtnField*)pItem->pBuf,&pItem->RspInfo,pItem->bIsLast);
	}
	void Output_OnRspQryOrderInfo(SMsgItem* pItem)
	{
		if(m_fnOnRspQryOrderInfo)
			(*m_fnOnRspQryOrderInfo)(pItem->pApi,(DFITCOrderCommRtnField*)pItem->pBuf,&pItem->RspInfo,pItem->bIsLast);
	}
	void Output_OnRspQryMatchInfo(SMsgItem* pItem)
	{
		if(m_fnOnRspQryMatchInfo)
			(*m_fnOnRspQryMatchInfo)(pItem->pApi,(DFITCMatchedRtnField*)pItem->pBuf,&pItem->RspInfo,pItem->bIsLast);
	}
	void Output_OnRspCustomerCapital(SMsgItem* pItem)
	{
		if(m_fnOnRspCustomerCapital)
			(*m_fnOnRspCustomerCapital)(pItem->pApi,(DFITCCapitalInfoRtnField*)pItem->pBuf,&pItem->RspInfo,pItem->bIsLast);
	}
	void Output_OnMarketData(SMsgItem* pItem)
	{
		if(m_fnOnMarketData)
			(*m_fnOnMarketData)(pItem->pApi,(DFITCDepthMarketDataField*)pItem->pBuf);
	}
	void Output_OnRtnInstrumentStatus(SMsgItem* pItem)
	{
		if(m_fnOnRtnInstrumentStatus)
			(*m_fnOnRtnInstrumentStatus)(pItem->pApi,(DFITCInstrumentStatusField*)pItem->pBuf);
	}
	void Output_OnRtnOrder(SMsgItem* pItem)
	{
		if(m_fnOnRtnOrder)
			(*m_fnOnRtnOrder)(pItem->pApi,(DFITCOrderRtnField*)pItem->pBuf);
	}
	void Output_OnRtnMatchedInfo(SMsgItem* pItem)
	{
		if(m_fnOnRtnMatchedInfo)
			(*m_fnOnRtnMatchedInfo)(pItem->pApi,(DFITCMatchRtnField*)pItem->pBuf);
	}

	void Output_OnRspQuoteSubscribe(SMsgItem* pItem)
	{
		if(m_fnOnRspQuoteSubscribe)
			(*m_fnOnRspQuoteSubscribe)(pItem->pApi,(DFITCQuoteSubscribeRspField*)pItem->pBuf);
	}
	void Output_OnRtnQuoteSubscribe(SMsgItem* pItem)
	{
		if(m_fnOnRtnQuoteSubscribe)
			(*m_fnOnRtnQuoteSubscribe)(pItem->pApi,(DFITCQuoteSubscribeRtnField*)pItem->pBuf);
	}
	void Output_OnRspQuoteInsertOrder(SMsgItem* pItem)
	{
		if(m_fnOnRspQuoteInsertOrder)
			(*m_fnOnRspQuoteInsertOrder)(pItem->pApi,(DFITCQuoteOrderRspField*)pItem->pBuf,&pItem->RspInfo);
	}
	void Output_OnRspQuoteCancelOrder(SMsgItem* pItem)
	{
		if(m_fnOnRspQuoteCancelOrder)
			(*m_fnOnRspQuoteCancelOrder)(pItem->pApi,(DFITCQuoteOrderRspField*)pItem->pBuf,&pItem->RspInfo);
	}
	void Output_OnRtnQuoteOrder(SMsgItem* pItem)
	{
		if(m_fnOnRtnQuoteOrder)
			(*m_fnOnRtnQuoteOrder)(pItem->pApi,(DFITCQuoteOrderRtnField*)pItem->pBuf);
	}
	void Output_OnRtnQuoteCancelOrder(SMsgItem* pItem)
	{
		if(m_fnOnRtnQuoteCancelOrder)
			(*m_fnOnRtnQuoteCancelOrder)(pItem->pApi,(DFITCQuoteCanceledRtnField*)pItem->pBuf);
	}

private:
	volatile bool				m_bRunning;
	HANDLE						m_hEvent;
	HANDLE						m_hThread;

	MSQueue<SMsgItem*>			m_queue_MD;			//响应队列
	MSQueue<SMsgItem*>			m_queue_TD;			//响应队列

	//回调函数指针（按字母排序）
	fnOnConnect						m_fnOnConnect;
	fnOnDisconnect					m_fnOnDisconnect;
	fnOnMarketData					m_fnOnMarketData;
	fnOnRspArbitrageInstrument		m_fnOnRspArbitrageInstrument;
	fnOnRspInsertCancelOrder		m_fnOnRspCancelOrder;
	fnOnRspCustomerCapital			m_fnOnRspCustomerCapital;
	fnOnRspError					m_fnOnRspError;
	fnOnRspInsertCancelOrder		m_fnOnRspInsertOrder;
	fnOnRspQryExchangeInstrument	m_fnOnRspQryExchangeInstrument;
	fnOnRspQryMatchInfo				m_fnOnRspQryMatchInfo;
	fnOnRspQryOrderInfo				m_fnOnRspQryOrderInfo;
	fnOnRspQryPosition				m_fnOnRspQryPosition;
	fnOnRspQryPositionDetail		m_fnOnRspQryPositionDetail;
	fnOnRspQrySpecifyInstrument		m_fnOnRspQrySpecifyInstrument;
	fnOnRtnCancelOrder				m_fnOnRtnCancelOrder;
	fnOnRtnInstrumentStatus			m_fnOnRtnInstrumentStatus;
	fnOnRtnMatchedInfo				m_fnOnRtnMatchedInfo;	
	fnOnRtnOrder					m_fnOnRtnOrder;

	fnOnRspQuoteSubscribe			m_fnOnRspQuoteSubscribe;
	fnOnRtnQuoteSubscribe			m_fnOnRtnQuoteSubscribe;
	fnOnRspQuoteInsertCancelOrder	m_fnOnRspQuoteInsertOrder;
	fnOnRspQuoteInsertCancelOrder	m_fnOnRspQuoteCancelOrder;
	fnOnRtnQuoteCancelOrder			m_fnOnRtnQuoteCancelOrder;
	fnOnRtnQuoteOrder				m_fnOnRtnQuoteOrder;
};

