#include "StdAfx.h"
#include "XSpeedMsgQueue.h"

void CXSpeedMsgQueue::Clear()
{
	SMsgItem* pItem = NULL;
	//清空队列
	while(m_queue_TD.dequeue(pItem))
	{
		delete pItem->pBuf;
		delete pItem;
	}
	while(m_queue_MD.dequeue(pItem))
	{
		delete pItem->pBuf;
		delete pItem;
	}
}

bool CXSpeedMsgQueue::Process()
{
	SMsgItem* pItem = NULL;
	if(m_queue_TD.dequeue(pItem))
	{
		_Output_TD(pItem);
		delete pItem->pBuf;
		delete pItem;
		return true;
	}
	else if(m_queue_MD.dequeue(pItem))
	{
		_Output_MD(pItem);
		delete pItem->pBuf;
		delete pItem;
		return true;
	}
	return false;
}

void CXSpeedMsgQueue::StartThread()
{
	if (NULL == m_hThread)
	{
		m_bRunning = true;
		m_hThread = CreateThread(NULL,0,ProcessThread,this,CREATE_SUSPENDED,NULL);
		SetThreadPriority(m_hThread,THREAD_PRIORITY_HIGHEST);
		ResumeThread(m_hThread);
	}
}

void CXSpeedMsgQueue::StopThread()
{
	//停止线程
	m_bRunning = false;

	// 线程可能正在Wait，让它结束等待
	SetEvent(m_hEvent);
	
	WaitForSingleObject(m_hThread,INFINITE);
	CloseHandle(m_hThread);
	m_hThread = NULL;
}

DWORD WINAPI ProcessThread(LPVOID lpParam)
{
	CXSpeedMsgQueue* pMsgQueue = reinterpret_cast<CXSpeedMsgQueue *>(lpParam);
	if (pMsgQueue)
		pMsgQueue->RunInThread();
	return 0;
}

void CXSpeedMsgQueue::RunInThread()
{
	while (m_bRunning)
	{
		if(Process())
		{
		}
		else
		{
			//挂起，等事件到来
			WaitForSingleObject(m_hEvent,INFINITE);
		}
	}

	//清理线程
	CloseHandle(m_hThread);
	m_hThread = NULL;
	m_bRunning = false;
}

void CXSpeedMsgQueue::_Input_MD(SMsgItem* pMsgItem)
{
	m_queue_MD.enqueue(pMsgItem);
	SetEvent(m_hEvent);
}

void CXSpeedMsgQueue::_Input_TD(SMsgItem* pMsgItem)
{
	m_queue_TD.enqueue(pMsgItem);
	SetEvent(m_hEvent);
}

void CXSpeedMsgQueue::_Output_MD(SMsgItem* pMsgItem)
{
	Output_OnMarketData(pMsgItem);
}

void CXSpeedMsgQueue::_Output_TD(SMsgItem* pMsgItem)
{
	//内部调用，不判断指针是否有效
	switch(pMsgItem->type)
	{
	case E_fnOnConnect:
		Output_OnConnect(pMsgItem);
		break;
	case E_fnOnDisconnect:
		Output_OnDisconnect(pMsgItem);
		break;
	case E_fnOnRspError:
		Output_OnRspError(pMsgItem);
		break;
	case E_fnOnRspCancelOrder:
		Output_OnRspCancelOrder(pMsgItem);
		break;
	case E_fnOnRspInsertOrder:
		Output_OnRspInsertOrder(pMsgItem);
		break;
	case E_fnOnRspQryExchangeInstrument:
		Output_OnRspQryExchangeInstrument(pMsgItem);
		break;
	case E_fnOnRspArbitrageInstrument:
		Output_OnRspArbitrageInstrument(pMsgItem);
		break;
	case E_fnOnRspQrySpecifyInstrument:
		Output_OnRspQrySpecifyInstrument(pMsgItem);
		break;
	case E_fnOnRspQryPosition:
		Output_OnRspQryPosition(pMsgItem);
		break;
	case E_fnOnRspQryPositionDetail:
		Output_OnRspQryPositionDetail(pMsgItem);
		break;
	case E_fnOnRspQryOrderInfo:
		Output_OnRspQryOrderInfo(pMsgItem);
		break;
	case E_fnOnRspQryMatchInfo:
		Output_OnRspQryMatchInfo(pMsgItem);
		break;
	case E_fnOnRspCustomerCapital:
		Output_OnRspCustomerCapital(pMsgItem);
		break;
	case E_fnOnRtnInstrumentStatus:
		Output_OnRtnInstrumentStatus(pMsgItem);
		break;
	case E_fnOnRtnOrder:
		Output_OnRtnOrder(pMsgItem);
		break;
	case E_fnOnRtnCancelOrder:
		Output_OnRtnCancelOrder(pMsgItem);
		break;
	case E_fnOnRtnMatchedInfo:
		Output_OnRtnMatchedInfo(pMsgItem);
		break;

	case E_fnOnRspQuoteSubscribe:
		Output_OnRspQuoteSubscribe(pMsgItem);
		break;
	case E_fnOnRtnQuoteSubscribe:
		Output_OnRtnQuoteSubscribe(pMsgItem);
		break;
	case E_fnOnRspQuoteInsertOrder:
		Output_OnRspQuoteInsertOrder(pMsgItem);
		break;
	case E_fnOnRspQuoteCancelOrder:
		Output_OnRspQuoteCancelOrder(pMsgItem);
		break;
	case E_fnOnRtnQuoteCancelOrder:
		Output_OnRtnQuoteCancelOrder(pMsgItem);
		break;
	case E_fnOnRtnQuoteOrder:
		Output_OnRtnQuoteOrder(pMsgItem);
		break;
	default:
		_ASSERT(false);
		break;
	}
}


void CXSpeedMsgQueue::Input_OnConnect(void* pApi,DFITCUserLoginInfoRtnField *pRspUserLogin,ConnectionStatus result)
{
	SMsgItem* pItem = new SMsgItem;
	if(pItem)
	{
		memset(pItem,0,sizeof(SMsgItem));
		pItem->type = E_fnOnConnect;
		pItem->pApi = pApi;
		pItem->RspInfo.nErrorID = result;

		int size = sizeof(DFITCUserLoginInfoRtnField);
		pItem->pBuf = new char[size];
		if(pRspUserLogin)
		{
			memcpy(pItem->pBuf,pRspUserLogin,size);
		}
		else
		{
			memset(pItem->pBuf,0,size);
		}

		_Input_TD(pItem);
	}
}

void CXSpeedMsgQueue::Input_OnDisconnect(void* pApi,DFITCErrorRtnField *pRspInfo,ConnectionStatus step)
{
	SMsgItem* pItem = new SMsgItem;
	if(pItem)
	{
		memset(pItem,0,sizeof(SMsgItem));
		pItem->type = E_fnOnDisconnect;
		pItem->pApi = pApi;
		pItem->RspInfo.nErrorID = step;

		int size = sizeof(DFITCErrorRtnField);
		pItem->pBuf = new char[size];

		if(pRspInfo)
		{			
			memcpy(pItem->pBuf,pRspInfo,size);
		}
		else
		{
			memset(pItem->pBuf,0,size);
		}

		_Input_TD(pItem);
	}
}

void CXSpeedMsgQueue::Input_OnRspError(void* pApi,DFITCErrorRtnField *pRspInfo)
{
	if(NULL==pRspInfo)
		return;

	SMsgItem* pItem = new SMsgItem;
	if(pItem)
	{
		pItem->type = E_fnOnRspError;
		pItem->pApi = pApi;
		pItem->RspInfo = *pRspInfo;
		pItem->pBuf = NULL;

		_Input_TD(pItem);
	}
}
//
void CXSpeedMsgQueue::Input_OnMarketData(void* pMdApi,DFITCDepthMarketDataField *pMarketDataField)
{
	if(NULL == pMarketDataField)
		return;
	SMsgItem* pItem = new SMsgItem;
	if(pItem)
	{
		pItem->type = E_fnOnMarketData;
		pItem->pApi = pMdApi;

		int size = sizeof(DFITCDepthMarketDataField);
		pItem->pBuf = new char[size];
		
		if(pMarketDataField)
		{
			memcpy(pItem->pBuf,pMarketDataField,size);
		}
		else
		{
			memset(pItem->pBuf,0,size);
		}

		_Input_MD(pItem);
	}
}

void CXSpeedMsgQueue::Input_OnRtnInstrumentStatus(void* pTraderApi,DFITCInstrumentStatusField *pInstrumentStatus)
{
	if(NULL == pInstrumentStatus)
		return;

	SMsgItem* pItem = new SMsgItem;
	if(pItem)
	{
		pItem->type = E_fnOnRtnInstrumentStatus;
		pItem->pApi = pTraderApi;
		
		int size = sizeof(DFITCInstrumentStatusField);
		pItem->pBuf = new char[size];

		if(pInstrumentStatus)
		{
			memcpy(pItem->pBuf,pInstrumentStatus,size);
		}
		else
		{
			memset(pItem->pBuf,0,size);
		}

		_Input_TD(pItem);
	}
}

void CXSpeedMsgQueue::Input_OnRtnCancelOrder(void* pTraderApi,DFITCOrderCanceledRtnField * pCancelOrderData)
{
	if(NULL == pCancelOrderData)
		return;

	SMsgItem* pItem = new SMsgItem;
	if(pItem)
	{
		pItem->type = E_fnOnRtnCancelOrder;
		pItem->pApi = pTraderApi;

		int size = sizeof(DFITCOrderCanceledRtnField);
		pItem->pBuf = new char[size];

		if(pCancelOrderData)
		{
			memcpy(pItem->pBuf,pCancelOrderData,size);
		}
		else
		{
			memset(pItem->pBuf,0,size);
		}

		_Input_TD(pItem);
	}
}

void CXSpeedMsgQueue::Input_OnRtnOrder(void* pTraderApi,DFITCOrderRtnField * pRtnOrderData)
{
	if(NULL == pRtnOrderData)
		return;

	SMsgItem* pItem = new SMsgItem;
	if(pItem)
	{
		pItem->type = E_fnOnRtnOrder;
		pItem->pApi = pTraderApi;

		int size = sizeof(DFITCOrderRtnField);
		pItem->pBuf = new char[size];

		if(pRtnOrderData)
		{		
			memcpy(pItem->pBuf,pRtnOrderData,size);
		}
		else
		{
			memset(pItem->pBuf,0,size);
		}

		_Input_TD(pItem);
	}
}

void CXSpeedMsgQueue::Input_OnRtnMatchedInfo(void* pTraderApi,DFITCMatchRtnField * pRtnMatchData)
{
	if(NULL == pRtnMatchData)
		return;

	SMsgItem* pItem = new SMsgItem;
	if(pItem)
	{
		pItem->type = E_fnOnRtnMatchedInfo;
		pItem->pApi = pTraderApi;
		
		int size = sizeof(DFITCMatchRtnField);
		pItem->pBuf = new char[size];

		if(pRtnMatchData)
		{
			memcpy(pItem->pBuf,pRtnMatchData,size);
		}
		else
		{
			memset(pItem->pBuf,0,size);
		}

		_Input_TD(pItem);
	}
}

void CXSpeedMsgQueue::Input_OnRspInsertOrder(void* pTraderApi,struct DFITCOrderRspDataRtnField * pOrderRtn, struct DFITCErrorRtnField * pErrorInfo)
{
	if(NULL == pOrderRtn
		&&NULL == pErrorInfo)
		return;

	SMsgItem* pItem = new SMsgItem;
	if(pItem)
	{
		memset(pItem,0,sizeof(SMsgItem));
		pItem->type = E_fnOnRspInsertOrder;
		pItem->pApi = pTraderApi;

		if(pErrorInfo)
			pItem->RspInfo = *pErrorInfo;

		if(pOrderRtn)
		{
			int size = sizeof(DFITCOrderRspDataRtnField);
			pItem->pBuf = new char[size];
			memcpy(pItem->pBuf,pOrderRtn,size);
		}		

		_Input_TD(pItem);
	}
}

void CXSpeedMsgQueue::Input_OnRspCancelOrder(void* pTraderApi,DFITCOrderRspDataRtnField *pOrderCanceledRtn,DFITCErrorRtnField *pErrorInfo)
{
	if(NULL == pOrderCanceledRtn
		&&NULL == pErrorInfo)
		return;

	SMsgItem* pItem = new SMsgItem;
	if(pItem)
	{
		memset(pItem,0,sizeof(SMsgItem));
		pItem->type = E_fnOnRspCancelOrder;
		pItem->pApi = pTraderApi;

		if(pErrorInfo)
			pItem->RspInfo = *pErrorInfo;

		if(pOrderCanceledRtn)
		{
			int size = sizeof(DFITCOrderRspDataRtnField);
			pItem->pBuf = new char[size];
			memcpy(pItem->pBuf,pOrderCanceledRtn,size);
		}		

		_Input_TD(pItem);
	}
}

void CXSpeedMsgQueue::Input_OnRspQryExchangeInstrument(void* pTraderApi,DFITCExchangeInstrumentRtnField * pInstrumentData,DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	if(NULL == pInstrumentData
		&&NULL == pErrorInfo)
		return;

	SMsgItem* pItem = new SMsgItem;
	if(pItem)
	{
		memset(pItem,0,sizeof(SMsgItem));
		pItem->type = E_fnOnRspQryExchangeInstrument;
		pItem->pApi = pTraderApi;
		pItem->bIsLast = bIsLast;

		if(pErrorInfo)
			pItem->RspInfo = *pErrorInfo;

		if(pInstrumentData)
		{
			int size = sizeof(DFITCExchangeInstrumentRtnField);
			pItem->pBuf = new char[size];
			memcpy(pItem->pBuf,pInstrumentData,size);
		}
		
		_Input_TD(pItem);
	}
}

void CXSpeedMsgQueue::Input_OnRspArbitrageInstrument(void* pTraderApi,DFITCAbiInstrumentRtnField * pAbiInstrumentData, DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	if(NULL == pAbiInstrumentData
		&&NULL == pErrorInfo)
		return;

	SMsgItem* pItem = new SMsgItem;
	if(pItem)
	{
		memset(pItem,0,sizeof(SMsgItem));
		pItem->type = E_fnOnRspArbitrageInstrument;
		pItem->pApi = pTraderApi;
		pItem->bIsLast = bIsLast;

		if(pErrorInfo)
			pItem->RspInfo = *pErrorInfo;

		if(pAbiInstrumentData)
		{
			int size = sizeof(DFITCAbiInstrumentRtnField);
			pItem->pBuf = new char[size];
			memcpy(pItem->pBuf,pAbiInstrumentData,size);
		}
		
		_Input_TD(pItem);
	}
}

void CXSpeedMsgQueue::Input_OnRspQrySpecifyInstrument(void* pTraderApi,DFITCInstrumentRtnField * pInstrument, DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	if(NULL == pInstrument
		&&NULL == pErrorInfo)
		return;

	SMsgItem* pItem = new SMsgItem;
	if(pItem)
	{
		memset(pItem,0,sizeof(SMsgItem));
		pItem->type = E_fnOnRspQrySpecifyInstrument;
		pItem->pApi = pTraderApi;
		pItem->bIsLast = bIsLast;

		if(pErrorInfo)
			pItem->RspInfo = *pErrorInfo;

		if(pInstrument)
		{
			int size = sizeof(DFITCInstrumentRtnField);
			pItem->pBuf = new char[size];
			memcpy(pItem->pBuf,pInstrument,size);
		}
		
		_Input_TD(pItem);
	}
}
//
//void CCTPMsgQueue::Input_OnRspQryInstrumentMarginRate(void* pTraderApi,CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
//{
//	if(NULL == pInstrumentMarginRate
//		&&NULL == pRspInfo)
//		return;
//
//	SMsgItem* pItem = new SMsgItem;
//	if(pItem)
//	{
//		memset(pItem,0,sizeof(SMsgItem));
//		pItem->type = E_fnOnRspQryInstrumentMarginRate;
//		pItem->pApi = pTraderApi;
//		pItem->nRequestID = nRequestID;
//		pItem->bIsLast = bIsLast;
//
//		if(pInstrumentMarginRate)
//			pItem->InstrumentMarginRate = *pInstrumentMarginRate;
//		if(pRspInfo)
//			pItem->RspInfo = *pRspInfo;
//
//		_Input_TD(pItem);
//	}
//}
//
//void CCTPMsgQueue::Input_OnRspQryInstrumentCommissionRate(void* pTraderApi,CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
//{
//	if(NULL == pInstrumentCommissionRate
//		&&NULL == pRspInfo)
//		return;
//
//	SMsgItem* pItem = new SMsgItem;
//	if(pItem)
//	{
//		memset(pItem,0,sizeof(SMsgItem));
//		pItem->type = E_fnOnRspQryInstrumentCommissionRate;
//		pItem->pApi = pTraderApi;
//		pItem->nRequestID = nRequestID;
//		pItem->bIsLast = bIsLast;
//
//		if(pInstrumentCommissionRate)
//			pItem->InstrumentCommissionRate = *pInstrumentCommissionRate;
//		if(pRspInfo)
//			pItem->RspInfo = *pRspInfo;
//
//		_Input_TD(pItem);
//	}
//}

void CXSpeedMsgQueue::Input_OnRspQryPosition(void* pTraderApi,DFITCPositionInfoRtnField * pPositionInfoRtn,DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	if(NULL == pPositionInfoRtn
		&&NULL == pErrorInfo)
		return;

	SMsgItem* pItem = new SMsgItem;
	if(pItem)
	{
		memset(pItem,0,sizeof(SMsgItem));
		pItem->type = E_fnOnRspQryPosition;
		pItem->pApi = pTraderApi;
		pItem->bIsLast = bIsLast;

		if(pErrorInfo)
			pItem->RspInfo = *pErrorInfo;

		if(pPositionInfoRtn)
		{
			int size = sizeof(DFITCPositionInfoRtnField);
			pItem->pBuf = new char[size];
			memcpy(pItem->pBuf,pPositionInfoRtn,size);
		}

		_Input_TD(pItem);
	}
}

void CXSpeedMsgQueue::Input_OnRspQryPositionDetail(void* pTraderApi,DFITCPositionDetailRtnField * pPositionDetailRtn,DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	if(NULL == pPositionDetailRtn
		&&NULL == pErrorInfo)
		return;

	SMsgItem* pItem = new SMsgItem;
	if(pItem)
	{
		memset(pItem,0,sizeof(SMsgItem));
		pItem->type = E_fnOnRspQryPositionDetail;
		pItem->pApi = pTraderApi;
		pItem->bIsLast = bIsLast;

		if(pErrorInfo)
			pItem->RspInfo = *pErrorInfo;

		if(pPositionDetailRtn)
		{
			int size = sizeof(DFITCPositionDetailRtnField);
			pItem->pBuf = new char[size];
			memcpy(pItem->pBuf,pPositionDetailRtn,size);
		}

		_Input_TD(pItem);
	}
}

//void CCTPMsgQueue::Input_OnErrRtnOrderInsert(void* pTraderApi,CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
//{
//	if(NULL == pInputOrder
//		&&NULL == pRspInfo)
//		return;
//
//	SMsgItem* pItem = new SMsgItem;
//	if(pItem)
//	{
//		memset(pItem,0,sizeof(SMsgItem));
//		pItem->type = E_fnOnErrRtnOrderInsert;
//		pItem->pApi = pTraderApi;
//		if(pInputOrder)
//			pItem->InputOrder = *pInputOrder;
//		if(pRspInfo)
//			pItem->RspInfo = *pRspInfo;
//
//		_Input_TD(pItem);
//	}
//}
//
//void CCTPMsgQueue::Input_OnRspOrderAction(void* pTraderApi,CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
//{
//	if(NULL == pInputOrderAction
//		&&NULL == pRspInfo)
//		return;
//
//	SMsgItem* pItem = new SMsgItem;
//	if(pItem)
//	{
//		memset(pItem,0,sizeof(SMsgItem));
//		pItem->type = E_fnOnRspOrderAction;
//		pItem->pApi = pTraderApi;
//		pItem->nRequestID = nRequestID;
//		pItem->bIsLast = bIsLast;
//
//		if(pInputOrderAction)
//			pItem->InputOrderAction = *pInputOrderAction;
//		if(pRspInfo)
//			pItem->RspInfo = *pRspInfo;
//
//		_Input_TD(pItem);
//	}
//}
//
//void CCTPMsgQueue::Input_OnErrRtnOrderAction(void* pTraderApi,CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo)
//{
//	if(NULL == pOrderAction
//		&&NULL == pRspInfo)
//		return;
//
//	SMsgItem* pItem = new SMsgItem;
//	if(pItem)
//	{
//		memset(pItem,0,sizeof(SMsgItem));
//		pItem->type = E_fnOnErrRtnOrderAction;
//		pItem->pApi = pTraderApi;
//		if(pOrderAction)
//			pItem->OrderAction = *pOrderAction;
//		if(pRspInfo)
//			pItem->RspInfo = *pRspInfo;
//
//		_Input_TD(pItem);
//	}
//}

void CXSpeedMsgQueue::Input_OnRspQryOrderInfo(void* pTraderApi,DFITCOrderCommRtnField * pRtnOrderData,DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	if(NULL == pRtnOrderData
		&&NULL == pErrorInfo)
		return;

	SMsgItem* pItem = new SMsgItem;
	if(pItem)
	{
		memset(pItem,0,sizeof(SMsgItem));
		pItem->type = E_fnOnRspQryOrderInfo;
		pItem->pApi = pTraderApi;
		pItem->bIsLast = bIsLast;

		if(pErrorInfo)
			pItem->RspInfo = *pErrorInfo;

		if(pRtnOrderData)
		{
			int size = sizeof(DFITCOrderCommRtnField);
			pItem->pBuf = new char[size];
			memcpy(pItem->pBuf,pRtnOrderData,size);
		}

		_Input_TD(pItem);
	}
}

void CXSpeedMsgQueue::Input_OnRspQryMatchInfo(void* pTraderApi,DFITCMatchedRtnField * pRtnMatchData,DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	if(NULL == pRtnMatchData
		&&NULL == pErrorInfo)
		return;

	SMsgItem* pItem = new SMsgItem;
	if(pItem)
	{
		memset(pItem,0,sizeof(SMsgItem));
		pItem->type = E_fnOnRspQryMatchInfo;
		pItem->pApi = pTraderApi;
		pItem->bIsLast = bIsLast;
		
		if(pErrorInfo)
			pItem->RspInfo = *pErrorInfo;

		if(pRtnMatchData)
		{
			int size = sizeof(DFITCMatchedRtnField);
			pItem->pBuf = new char[size];
			memcpy(pItem->pBuf,pRtnMatchData,size);
		}

		_Input_TD(pItem);
	}
}

void CXSpeedMsgQueue::Input_OnRspCustomerCapital(void* pTraderApi,DFITCCapitalInfoRtnField *pCapitalInfoRtn,DFITCErrorRtnField *pErrorInfo, bool bIsLast)
{
	if(NULL == pCapitalInfoRtn
		&&NULL == pErrorInfo)
		return;

	SMsgItem* pItem = new SMsgItem;
	if(pItem)
	{
		memset(pItem,0,sizeof(SMsgItem));
		pItem->type = E_fnOnRspCustomerCapital;
		pItem->pApi = pTraderApi;
		pItem->bIsLast = bIsLast;
		
		if(pErrorInfo)
			pItem->RspInfo = *pErrorInfo;

		if(pCapitalInfoRtn)
		{
			int size = sizeof(DFITCCapitalInfoRtnField);
			pItem->pBuf = new char[size];
			memcpy(pItem->pBuf,pCapitalInfoRtn,size);
		}

		_Input_TD(pItem);
	}
}

//void CCTPMsgQueue::Input_OnRspQryDepthMarketData(void* pTraderApi,CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
//{
//	if(NULL == pDepthMarketData
//		&&NULL == pRspInfo)
//		return;
//
//	SMsgItem* pItem = new SMsgItem;
//	if(pItem)
//	{
//		memset(pItem,0,sizeof(SMsgItem));
//		pItem->type = E_fnOnRspQryDepthMarketData;
//		pItem->pApi = pTraderApi;
//		pItem->nRequestID = nRequestID;
//		pItem->bIsLast = bIsLast;
//		if(pDepthMarketData)
//			pItem->DepthMarketData = *pDepthMarketData;
//		if(pRspInfo)
//			pItem->RspInfo = *pRspInfo;
//
//		_Input_TD(pItem);
//	}
//}

void CXSpeedMsgQueue::Input_OnRspQuoteSubscribe(void* pTraderApi,DFITCQuoteSubscribeRspField * pRspQuoteSubscribeData)
{
	if(NULL == pRspQuoteSubscribeData)
		return;

	SMsgItem* pItem = new SMsgItem;
	if(pItem)
	{
		memset(pItem,0,sizeof(SMsgItem));
		pItem->type = E_fnOnRspQuoteSubscribe;
		pItem->pApi = pTraderApi;
		
		{
			int size = sizeof(DFITCQuoteSubscribeRspField);
			pItem->pBuf = new char[size];
			memcpy(pItem->pBuf,pRspQuoteSubscribeData,size);
		}

		_Input_TD(pItem);
	}
}

void CXSpeedMsgQueue::Input_OnRtnQuoteSubscribe(void* pTraderApi,DFITCQuoteSubscribeRtnField * pRtnQuoteSubscribeData)
{
	if(NULL == pRtnQuoteSubscribeData)
		return;

	SMsgItem* pItem = new SMsgItem;
	if(pItem)
	{
		memset(pItem,0,sizeof(SMsgItem));
		pItem->type = E_fnOnRtnQuoteSubscribe;
		pItem->pApi = pTraderApi;
		
		{
			int size = sizeof(DFITCQuoteSubscribeRtnField);
			pItem->pBuf = new char[size];
			memcpy(pItem->pBuf,pRtnQuoteSubscribeData,size);
		}

		_Input_TD(pItem);
	}
}

void CXSpeedMsgQueue::Input_OnRspQuoteInsertOrder(void* pTraderApi,DFITCQuoteOrderRspField * pRspQuoteOrderData,DFITCErrorRtnField * pErrorInfo)
{
	if(NULL == pRspQuoteOrderData
		&&NULL == pErrorInfo)
		return;

	SMsgItem* pItem = new SMsgItem;
	if(pItem)
	{
		memset(pItem,0,sizeof(SMsgItem));
		pItem->type = E_fnOnRspQuoteInsertOrder;
		pItem->pApi = pTraderApi;

		if(pErrorInfo)
			pItem->RspInfo = *pErrorInfo;

		if(pRspQuoteOrderData)
		{
			int size = sizeof(DFITCQuoteOrderRspField);
			pItem->pBuf = new char[size];
			memcpy(pItem->pBuf,pRspQuoteOrderData,size);
		}		

		_Input_TD(pItem);
	}
}

void CXSpeedMsgQueue::Input_OnRspQuoteCancelOrder(void* pTraderApi,DFITCQuoteOrderRspField * pRspQuoteOrderData,DFITCErrorRtnField * pErrorInfo)
{
	if(NULL == pRspQuoteOrderData
		&&NULL == pErrorInfo)
		return;

	SMsgItem* pItem = new SMsgItem;
	if(pItem)
	{
		memset(pItem,0,sizeof(SMsgItem));
		pItem->type = E_fnOnRspQuoteCancelOrder;
		pItem->pApi = pTraderApi;

		if(pErrorInfo)
			pItem->RspInfo = *pErrorInfo;

		if(pRspQuoteOrderData)
		{
			int size = sizeof(DFITCQuoteOrderRspField);
			pItem->pBuf = new char[size];
			memcpy(pItem->pBuf,pRspQuoteOrderData,size);
		}		

		_Input_TD(pItem);
	}
}

void CXSpeedMsgQueue::Input_OnRtnQuoteOrder(void* pTraderApi,DFITCQuoteOrderRtnField * pRtnQuoteOrderData)
{
	if(NULL == pRtnQuoteOrderData)
		return;

	SMsgItem* pItem = new SMsgItem;
	if(pItem)
	{
		pItem->type = E_fnOnRtnQuoteOrder;
		pItem->pApi = pTraderApi;

		int size = sizeof(DFITCQuoteOrderRtnField);
		pItem->pBuf = new char[size];

		if(pRtnQuoteOrderData)
		{		
			memcpy(pItem->pBuf,pRtnQuoteOrderData,size);
		}
		else
		{
			memset(pItem->pBuf,0,size);
		}

		_Input_TD(pItem);
	}
}

void CXSpeedMsgQueue::Input_OnRtnQuoteCancelOrder(void* pTraderApi,DFITCQuoteCanceledRtnField * pRtnQuoteCanceledData)
{
	if(NULL == pRtnQuoteCanceledData)
		return;

	SMsgItem* pItem = new SMsgItem;
	if(pItem)
	{
		pItem->type = E_fnOnRtnQuoteCancelOrder;
		pItem->pApi = pTraderApi;

		int size = sizeof(DFITCQuoteCanceledRtnField);
		pItem->pBuf = new char[size];

		if(pRtnQuoteCanceledData)
		{
			memcpy(pItem->pBuf,pRtnQuoteCanceledData,size);
		}
		else
		{
			memset(pItem->pBuf,0,size);
		}

		_Input_TD(pItem);
	}
}