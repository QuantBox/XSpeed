#include "StdAfx.h"
#include "TraderApi.h"
#include "XSpeedMsgQueue.h"
#include "include\toolkit.h"
#include "include\Lock.h"

#include <time.h>

CTraderApi::CTraderApi(void)
{
	m_msgQueue = NULL;
	m_status = E_uninit;
	m_lRequestID = 0;

	m_hThread = NULL;
	m_bRunning = false;

	InitializeCriticalSection(&m_csList);
	InitializeCriticalSection(&m_csMap);
	InitializeCriticalSection(&m_csOrderRef);
}


CTraderApi::~CTraderApi(void)
{
	Disconnect();

	DeleteCriticalSection(&m_csList);
	DeleteCriticalSection(&m_csMap);
	DeleteCriticalSection(&m_csOrderRef);
}

void CTraderApi::StopThread()
{
	WriteLog("StopThread");
	//停止发送线程
	m_bRunning = false;
	WaitForSingleObject(m_hThread,INFINITE);
	CloseHandle(m_hThread);
	m_hThread = NULL;
}

void CTraderApi::RegisterMsgQueue(CXSpeedMsgQueue* pMsgQueue)
{
	WriteLog("RegisterMsgQueue");
	m_msgQueue = pMsgQueue;
}

bool CTraderApi::IsErrorRspInfo_Output(struct DFITCErrorRtnField *pRspInfo)
{
	bool bRet = ((pRspInfo) && (pRspInfo->nErrorID != 0));
	if(bRet)
	{
		if(m_msgQueue)
			m_msgQueue->Input_OnRspError(this,pRspInfo);
	}
	return bRet;
}

bool CTraderApi::IsErrorRspInfo(struct DFITCErrorRtnField *pRspInfo)   
{
	bool bRet = ((pRspInfo) && (pRspInfo->nErrorID != 0));

	return bRet;
}

void CTraderApi::Connect(
		const string& szSvrAddr,
		const string& szAccountID,
		const string& szPassword,
		short sCompanyID)
{
	WriteLog("Connect %s %s",szSvrAddr.c_str(),szAccountID.c_str());
	m_szSvrAddr = szSvrAddr;
	m_szAccountID = szAccountID;
	m_szPassword = szPassword;
	m_sCompanyID = sCompanyID;
	
	m_pApi = DFITCTraderApi::CreateDFITCTraderApi();

	m_status = E_inited;
	if(m_msgQueue)
		m_msgQueue->Input_OnConnect(this,NULL,m_status);

	SRequest* pRequest = MakeRequestBuf(E_Init);
	if(pRequest)
	{
		AddToSendQueue(pRequest);
	}
}

void CTraderApi::Disconnect()
{
	StopThread();

	m_status = E_unconnected;
	if(m_pApi)
	{
		//m_pApi->RegisterSpi(NULL);
		m_pApi->Release();
		m_pApi = NULL;

		if(m_msgQueue)
			m_msgQueue->Input_OnDisconnect(this,NULL,m_status);
	}

	

	m_lRequestID = 0;//由于线程已经停止，没有必要用原子操作了

	ReleaseRequestListBuf();
	ReleaseRequestMapBuf();
}

CTraderApi::SRequest* CTraderApi::MakeRequestBuf(RequestType type)
{
	SRequest *pRequest = new SRequest;
	if (NULL == pRequest)
		return NULL;

	memset(pRequest,0,sizeof(SRequest));
	pRequest->type = type;
	switch(type)
	{
	case E_AbiInstrumentField:
		pRequest->pBuf = new DFITCAbiInstrumentField();
		break;
	case E_CancelOrderField:
		pRequest->pBuf = new DFITCCancelOrderField();
		break;
	case E_CapitalField:
		pRequest->pBuf = new DFITCCapitalField();
		break;
	case E_ExchangeInstrumentField:
		pRequest->pBuf = new DFITCExchangeInstrumentField();
		break;
	case E_Init:
		pRequest->pBuf = NULL;
		break;
	case E_InsertOrderField:
		pRequest->pBuf = new DFITCInsertOrderField();
		break;
	case E_MatchField:
		pRequest->pBuf = new DFITCMatchField();
		break;
	case E_OrderField:
		pRequest->pBuf = new DFITCOrderField();
		break;
	case E_PositionField:
		pRequest->pBuf = new DFITCPositionField();
		break;
	case E_PositionDetailField:
		pRequest->pBuf = new DFITCPositionDetailField();
		break;
	case E_SpecificInstrumentField:
		pRequest->pBuf = new DFITCSpecificInstrumentField();
		break;
	case E_UserLoginField:
		pRequest->pBuf = new DFITCUserLoginField();
		break;
	case E_QuoteSubscribeField:
		pRequest->pBuf = new DFITCQuoteSubscribeField();
		break;
	case E_QuoteInsertOrderField:
		pRequest->pBuf = new DFITCQuoteInsertOrderField();
		break;
	case E_QuoteCancelOrderField:
		pRequest->pBuf = new DFITCCancelOrderField();
		break;
	default:
		_ASSERT(FALSE);
		break;
	}
	return pRequest;
}

void CTraderApi::ReleaseRequestListBuf()
{
	CLock cl(&m_csList);
	while (!m_reqList.empty())
	{
		SRequest * pRequest = m_reqList.front();
		delete pRequest->pBuf;
		delete pRequest;
		m_reqList.pop_front();
	}
}

void CTraderApi::ReleaseRequestMapBuf()
{
	CLock cl(&m_csMap);
	for (map<int,SRequest*>::iterator it=m_reqMap.begin();it!=m_reqMap.end();++it)
	{
		SRequest * pRequest = it->second;
		delete pRequest->pBuf;
		delete pRequest;
	}
	m_reqMap.clear();
}

void CTraderApi::ReleaseRequestMapBuf(int nRequestID)
{
	CLock cl(&m_csMap);
	map<int,SRequest*>::iterator it = m_reqMap.find(nRequestID);
	if (it!=m_reqMap.end())
	{
		SRequest * pRequest = it->second;
		delete pRequest->pBuf;
		delete pRequest;
		m_reqMap.erase(nRequestID);
	}
}

void CTraderApi::AddRequestMapBuf(int nRequestID,SRequest* pRequest)
{
	if(NULL == pRequest)
		return;

	CLock cl(&m_csMap);
	map<int,SRequest*>::iterator it = m_reqMap.find(nRequestID);
	if (it!=m_reqMap.end())
	{
		SRequest* p = it->second;
		if(pRequest != p)//如果实际上指的是同一内存，不再插入
		{
			delete p->pBuf;
			delete p;
			m_reqMap[nRequestID] = pRequest;
		}
	}
}

DWORD WINAPI SendThread_TD(LPVOID lpParam)
{
	CTraderApi* pTrade = reinterpret_cast<CTraderApi *>(lpParam);
	if (pTrade)
		pTrade->RunInThread();
	return 0;
}

void CTraderApi::AddToSendQueue(SRequest * pRequest)
{
	if (NULL == pRequest)
		return;

	CLock cl(&m_csList);
	bool bFind = false;

	if (!bFind)
		m_reqList.push_back(pRequest);

	if (NULL == m_hThread
		&&!m_reqList.empty())
	{
		m_bRunning = true;
		m_hThread = CreateThread(NULL,0,SendThread_TD,this,0,NULL); 
	}
}


void CTraderApi::RunInThread()
{
	int iRet = 0;

	while (!m_reqList.empty()&&m_bRunning)
	{
		SRequest * pRequest = m_reqList.front();
		long lRequest = InterlockedIncrement(&m_lRequestID);
		switch(pRequest->type)
		{
		case E_AbiInstrumentField:
			{
				DFITCAbiInstrumentField* body = (DFITCAbiInstrumentField*)pRequest->pBuf;
				body->lRequestID = lRequest;
				iRet = m_pApi->ReqQryArbitrageInstrument(body);
			}
			break;
		case E_CapitalField:
			{
				DFITCCapitalField* body = (DFITCCapitalField*)pRequest->pBuf;
				body->lRequestID = lRequest;
				iRet = m_pApi->ReqQryCustomerCapital(body);
			}
			break;
		case E_ExchangeInstrumentField:
			{
				DFITCExchangeInstrumentField* body = (DFITCExchangeInstrumentField*)pRequest->pBuf;
				body->lRequestID = lRequest;
				iRet = m_pApi->ReqQryExchangeInstrument(body);
			}
			break;
		case E_Init:
			lRequest = 0;
			iRet = ReqInit();
			break;
		case E_InsertOrderField:
			_ASSERT(FALSE);
			break;
		case E_MatchField:
			{
				DFITCMatchField* body = (DFITCMatchField*)pRequest->pBuf;
				body->lRequestID = lRequest;
				iRet = m_pApi->ReqQryMatchInfo(body);
			}
			break;
		case E_OrderField:
			{
				DFITCOrderField* body = (DFITCOrderField*)pRequest->pBuf;
				body->lRequestID = lRequest;
				iRet = m_pApi->ReqQryOrderInfo(body);
			}
			break;
		case E_PositionField:
			{
				DFITCPositionField* body = (DFITCPositionField*)pRequest->pBuf;
				body->lRequestID = lRequest;
				iRet = m_pApi->ReqQryPosition(body);
			}
			break;
		case E_PositionDetailField:
			{
				DFITCPositionDetailField* body = (DFITCPositionDetailField*)pRequest->pBuf;
				body->lRequestID = lRequest;
				iRet = m_pApi->ReqQryPositionDetail(body);
			}
			break;
		case E_SpecificInstrumentField:
			{
				DFITCSpecificInstrumentField* body = (DFITCSpecificInstrumentField*)pRequest->pBuf;
				body->lRequestID = lRequest;
				iRet = m_pApi->ReqQrySpecifyInstrument(body);
			}
			break;
		case E_UserLoginField:
			{
				DFITCUserLoginField* body = (DFITCUserLoginField*)pRequest->pBuf;
				body->lRequestID = lRequest;
				iRet = m_pApi->ReqUserLogin(body);
			}
			break;
		case E_QuoteSubscribeField:
			{
				DFITCQuoteSubscribeField * body = (DFITCQuoteSubscribeField*)pRequest->pBuf;
				//body->lRequestID = lRequest;
				iRet = m_pApi->ReqQuoteSubscribe(body);
			}
			break;
		default:
			_ASSERT(FALSE);
			break;
		}

		if (0 == iRet)
		{
			//返回成功，填加到已发送池
			m_nSleep = 1;
			AddRequestMapBuf(lRequest,pRequest);

			CLock cl(&m_csList);
			m_reqList.pop_front();
		}
		else
		{
			//失败，按4的幂进行延时，但不超过1s
			m_nSleep *= 4;
			m_nSleep %= 1023;
		}
		Sleep(m_nSleep);
	}

	//清理线程
	CloseHandle(m_hThread);
	m_hThread = NULL;
	m_bRunning = false;
}

int CTraderApi::ReqInit()
{
	WriteLog("ReqInit");
	m_status = E_connecting;
	if(m_msgQueue)
		m_msgQueue->Input_OnConnect(this,NULL,m_status);

	int	iRet = m_pApi->Init(const_cast<char*>(m_szSvrAddr.c_str()),this);
	if(0 == iRet)
	{
	}
	else
	{
		m_status = E_unconnected;
		if(m_msgQueue)
			m_msgQueue->Input_OnDisconnect(this,NULL,m_status);
	}
	return iRet;
}

void CTraderApi::OnFrontConnected()
{
	WriteLog("OnFrontConnected");
	m_status =  E_connected;
	if(m_msgQueue)
		m_msgQueue->Input_OnConnect(this,NULL,m_status);

	ReqUserLogin();
}

void CTraderApi::OnFrontDisconnected(int nReason)
{
	WriteLog("OnFrontDisconnected  %d",nReason  );
	m_status = E_unconnected;
	DFITCErrorRtnField RspInfo;
	//构造出来的错误消息，为了统一出错信息
	RspInfo.nErrorID = nReason;
	//GetOnFrontDisconnectedMsg(&RspInfo);

	if(m_msgQueue)
		m_msgQueue->Input_OnDisconnect(this,&RspInfo,m_status);
}

void CTraderApi::ReqUserLogin()
{
	if (NULL == m_pApi)
		return;
	WriteLog("ReqUserLogin");
	SRequest* pRequest = MakeRequestBuf(E_UserLoginField);
	if (pRequest)
	{
		m_status = E_logining;
		if(m_msgQueue)
			m_msgQueue->Input_OnConnect(this,NULL,m_status);

		DFITCUserLoginField* body = (DFITCUserLoginField*)pRequest->pBuf;

		strncpy(body->accountID, m_szAccountID.c_str(),sizeof(DFITCAccountIDType));
		strncpy(body->passwd, m_szPassword.c_str(),sizeof(DFITCPasswdType));
		body->companyID = m_sCompanyID;

		AddToSendQueue(pRequest);
	}
}

void CTraderApi::OnRspUserLogin(struct DFITCUserLoginInfoRtnField *pRspUserLogin, struct DFITCErrorRtnField *pRspInfo)
{
	
	if (!IsErrorRspInfo(pRspInfo)
		&&pRspUserLogin)
	{
		WriteLog("OnRspUserLogin OnConnect %s" , pRspUserLogin->accountID  );
		m_status = E_logined;
		if(m_msgQueue)
			m_msgQueue->Input_OnConnect(this,pRspUserLogin,m_status);
		
		memcpy(&m_RspUserLogin,pRspUserLogin,sizeof(DFITCUserLoginInfoRtnField));
		m_lLocalOrderID = pRspUserLogin->initLocalOrderID;
	}
	else
	{
		WriteLog("OnRspUserLogin OnDisconnect  %s" , pRspUserLogin->accountID  );
		m_status = E_connected;
		if(m_msgQueue)
			m_msgQueue->Input_OnDisconnect(this,pRspInfo,E_logining);
	}

	if (pRspInfo)
		ReleaseRequestMapBuf(pRspInfo->requestID);
}

long CTraderApi::ReqInsertOrder(
	long localOrderID,
	const string& szInstrumentId,
	DFITCBuySellTypeType sBuySellType,
	DFITCOpenCloseTypeType sOpenCloseType,
	DFITCSpeculatorType sSpeculator,
	DFITCAmountType lAmount,
	DFITCPriceType dbPrice,
	DFITCOrderTypeType orderType,
	DFITCOrderPropertyType orderProperty,
	DFITCInstrumentTypeType nInstrumentType
	)
{
	if (NULL == m_pApi)
		return 0;

	WriteLog("ReqInsertOrder localOrderID=%d  szInstrumentId=%s lAmount=%d dbPrice=%f orderType=%s ",localOrderID ,szInstrumentId.c_str(),lAmount,dbPrice,orderType==DFITC_LIMITORDER?"限价":"市价");
	//WriteLog("ReqInsertOrder  "+szInstrumentId  + localOrderID);
	SRequest* pRequest = MakeRequestBuf(E_InsertOrderField);
	if (NULL == pRequest)
		return 0;

	DFITCInsertOrderField* body = (DFITCInsertOrderField*)pRequest->pBuf;

	strncpy(body->accountID, m_szAccountID.c_str(),sizeof(DFITCAccountIDType));
	// 合约
	strncpy(body->instrumentID,szInstrumentId.c_str(),sizeof(DFITCInstrumentIDType));
	// 价格
	body->insertPrice = dbPrice;
	// 数量
	body->orderAmount = lAmount;
	// 买卖
	body->buySellType = sBuySellType;
	// 开平
	body->openCloseType = sOpenCloseType;
	// 投保
	body->speculator = sSpeculator;
	body->insertType = DFITC_BASIC_ORDER;
	body->orderType= orderType;
	body->orderProperty = orderProperty;
	body->instrumentType = nInstrumentType;
	
	long nRet = 0;
	{
		//可能报单太快，m_nMaxOrderRef还没有改变就提交了
		CLock cl(&m_csOrderRef);

		char buf[255] = {0};
		sprintf(buf,"clock = %d",clock());
		OutputDebugStringA(buf);

		//不保存到队列，而是直接发送
		if(localOrderID == -1)
		{
			InterlockedIncrement(&m_lLocalOrderID);
			body->localOrderID = m_lLocalOrderID;
		}
		else
		{
			body->localOrderID = localOrderID;
		}
		int n = m_pApi->ReqInsertOrder((DFITCInsertOrderField*)pRequest->pBuf);
		nRet = body->localOrderID;
	}
	delete pRequest->pBuf;
	delete pRequest;//用完后直接删除
	WriteLog("订单%d已发送",nRet);
	return nRet;
}

void CTraderApi::OnRspInsertOrder(struct DFITCOrderRspDataRtnField * pOrderRtn, struct DFITCErrorRtnField * pErrorInfo)
{
	if (pErrorInfo)
		WriteLog("OnRspInsertOrder localOrderID=%d   spdOrderID =%d  pErrorInfo=%s",pErrorInfo->localOrderID , pErrorInfo->spdOrderID, pErrorInfo->errorMsg);
	else
		WriteLog("OnRspInsertOrder localOrderID=%d   spdOrderID =%d  ",pOrderRtn->localOrderID , pOrderRtn->spdOrderID);

	if(m_msgQueue)
		m_msgQueue->Input_OnRspInsertOrder(this,pOrderRtn,pErrorInfo);
}

void CTraderApi::OnRspQuoteInsertOrder(struct DFITCQuoteOrderRspField * pRspQuoteOrderData, struct DFITCErrorRtnField * pErrorInfo)
{
	if (pErrorInfo)
		WriteLog("OnRspQuoteInsertOrder localOrderID=%d   spdOrderID =%d  pErrorInfo=%s",pErrorInfo->localOrderID , pErrorInfo->spdOrderID, pErrorInfo->errorMsg);
	else
		WriteLog("OnRspQuoteInsertOrder localOrderID=%d   spdOrderID =%d  ",pRspQuoteOrderData->localOrderID , pRspQuoteOrderData->spdOrderID);

	if(m_msgQueue)
		m_msgQueue->Input_OnRspQuoteInsertOrder(this,pRspQuoteOrderData,pErrorInfo);
}

void CTraderApi::OnRtnMatchedInfo(struct DFITCMatchRtnField * pRtnMatchData)
{
	WriteLog("OnRtnMatchedInfo localOrderID=%d   spdOrderID =%d  matchID=%s Amount=%d Time=%s",pRtnMatchData->localOrderID , pRtnMatchData->spdOrderID, pRtnMatchData->matchID ,pRtnMatchData->matchedAmount,pRtnMatchData->matchedTime);

	if(m_msgQueue)
		m_msgQueue->Input_OnRtnMatchedInfo(this,pRtnMatchData);
}

void CTraderApi::ReqCancelOrder(
		const string& szInstrumentId,
		DFITCLocalOrderIDType localOrderID,
		DFITCSPDOrderIDType spdOrderID)
{
	
	WriteLog("ReqCancelOrder localOrderID=%d   spdOrderID =%d  szInstrumentId=%s ",localOrderID , spdOrderID, szInstrumentId.c_str());

	if (NULL == m_pApi)
		return;

	SRequest* pRequest = MakeRequestBuf(E_CancelOrderField);
	if (NULL == pRequest)
		return;

	DFITCCancelOrderField* body = (DFITCCancelOrderField*)pRequest->pBuf;

	strncpy(body->accountID, m_szAccountID.c_str(),sizeof(DFITCAccountIDType));
	// 合约
	strncpy(body->instrumentID,szInstrumentId.c_str(),sizeof(DFITCInstrumentIDType));

	body->localOrderID = localOrderID;
	body->spdOrderID = spdOrderID;
	
	m_pApi->ReqCancelOrder(body);

	delete pRequest->pBuf;
	delete pRequest;//用完后直接删除
}

void CTraderApi::ReqQuoteCancelOrder(
		const string& szInstrumentId,
		DFITCLocalOrderIDType localOrderID,
		DFITCSPDOrderIDType spdOrderID)
{
	
	WriteLog("ReqQuoteCancelOrder localOrderID=%d   spdOrderID =%d  szInstrumentId=%s ",localOrderID , spdOrderID, szInstrumentId.c_str());

	if (NULL == m_pApi)
		return;

	SRequest* pRequest = MakeRequestBuf(E_QuoteCancelOrderField);
	if (NULL == pRequest)
		return;

	DFITCCancelOrderField* body = (DFITCCancelOrderField*)pRequest->pBuf;

	strncpy(body->accountID, m_szAccountID.c_str(),sizeof(DFITCAccountIDType));
	// 合约
	strncpy(body->instrumentID,szInstrumentId.c_str(),sizeof(DFITCInstrumentIDType));

	body->localOrderID = localOrderID;
	body->spdOrderID = spdOrderID;
	
	m_pApi->ReqQuoteCancelOrder(body);

	delete pRequest->pBuf;
	delete pRequest;//用完后直接删除
}

void CTraderApi::OnRspCancelOrder(struct DFITCOrderRspDataRtnField *pOrderCanceledRtn,struct DFITCErrorRtnField *pErrorInfo)
{
	if (pErrorInfo)
	WriteLog("OnRspCancelOrder localOrderID=%d   spdOrderID =%d  pErrorInfo=%s ",pErrorInfo->localOrderID , pErrorInfo->spdOrderID, pErrorInfo->errorMsg);
	else
	   WriteLog("OnRspCancelOrder localOrderID=%d   spdOrderID =%d  ",pOrderCanceledRtn->localOrderID , pOrderCanceledRtn->spdOrderID);

	if(m_msgQueue)
		m_msgQueue->Input_OnRspCancelOrder(this,pOrderCanceledRtn,pErrorInfo);
}

void CTraderApi::OnRspQuoteCancelOrder( struct DFITCQuoteOrderRspField * pRspQuoteCanceledData,struct DFITCErrorRtnField * pErrorInfo)
{
	if (pErrorInfo)
	WriteLog("OnRspQuoteCancelOrder localOrderID=%d   spdOrderID =%d  pErrorInfo=%s ",pErrorInfo->localOrderID , pErrorInfo->spdOrderID, pErrorInfo->errorMsg);
	else
	   WriteLog("OnRspQuoteCancelOrder localOrderID=%d   spdOrderID =%d  ",pRspQuoteCanceledData->localOrderID , pRspQuoteCanceledData->spdOrderID);

	if(m_msgQueue)
		m_msgQueue->Input_OnRspQuoteCancelOrder(this,pRspQuoteCanceledData,pErrorInfo);
}

void CTraderApi::OnRtnCancelOrder(struct DFITCOrderCanceledRtnField * pCancelOrderData)
{
	WriteLog("OnRtnCancelOrder localOrderID=%d   spdOrderID =%d  DFITCAmountType=%d  ",pCancelOrderData->localOrderID , pCancelOrderData->spdOrderID, pCancelOrderData->cancelAmount);
	if(m_msgQueue)
		m_msgQueue->Input_OnRtnCancelOrder(this,pCancelOrderData);
}

void CTraderApi::OnRtnQuoteCancelOrder(struct DFITCQuoteCanceledRtnField * pRtnQuoteCanceledData)
{
	WriteLog("OnRtnQuoteCancelOrder localOrderID=%d   spdOrderID =%d  DFITCAmountType=%d  ",pRtnQuoteCanceledData->localOrderID , pRtnQuoteCanceledData->spdOrderID, pRtnQuoteCanceledData->bAmount);
	if(m_msgQueue)
		m_msgQueue->Input_OnRtnQuoteCancelOrder(this,pRtnQuoteCanceledData);
}

void CTraderApi::OnRtnOrder(struct DFITCOrderRtnField * pRtnOrderData)
{
	WriteLog("OnRtnOrder localOrderID=%d   spdOrderID =%d  OrderSysID=%s  ",pRtnOrderData->localOrderID , pRtnOrderData->spdOrderID, pRtnOrderData->OrderSysID);
	if(m_msgQueue)
		m_msgQueue->Input_OnRtnOrder(this,pRtnOrderData);
}

void CTraderApi::OnRtnQuoteOrder(struct DFITCQuoteOrderRtnField * pRtnQuoteOrderData)
{
	WriteLog("OnRtnQuoteOrder localOrderID=%d   spdOrderID =%d  OrderSysID=%s  ",pRtnQuoteOrderData->localOrderID , pRtnQuoteOrderData->spdOrderID, pRtnQuoteOrderData->bOrderSysID);
	if(m_msgQueue)
		m_msgQueue->Input_OnRtnQuoteOrder(this,pRtnQuoteOrderData);
}

void CTraderApi::ReqQryCustomerCapital()
{
	if (NULL == m_pApi)
		return;
	
	SRequest* pRequest = MakeRequestBuf(E_CapitalField);
	if (NULL == pRequest)
		return;
	
	DFITCCapitalField* body = (DFITCCapitalField*)pRequest->pBuf;

	strncpy(body->accountID, m_szAccountID.c_str(),sizeof(DFITCAccountIDType));

	AddToSendQueue(pRequest);
}

void CTraderApi::OnRspCustomerCapital(struct DFITCCapitalInfoRtnField * pCapitalInfoRtn, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	if(m_msgQueue)
		m_msgQueue->Input_OnRspCustomerCapital(this,pCapitalInfoRtn,pErrorInfo,bIsLast);

	if (bIsLast&&pErrorInfo)
		ReleaseRequestMapBuf(pErrorInfo->requestID);
}

void CTraderApi::ReqQryPosition(const string& szInstrumentId)
{
	if (NULL == m_pApi)
		return;
	
	SRequest* pRequest = MakeRequestBuf(E_PositionField);
	if (NULL == pRequest)
		return;
	
	DFITCPositionField* body = (DFITCPositionField*)pRequest->pBuf;

	strncpy(body->accountID, m_szAccountID.c_str(),sizeof(DFITCAccountIDType));
	strncpy(body->instrumentID,szInstrumentId.c_str(),sizeof(DFITCInstrumentIDType));
	//body->instrumentType;

	AddToSendQueue(pRequest);
}

void CTraderApi::OnRspQryPosition(struct DFITCPositionInfoRtnField * pPositionInfoRtn, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	if(m_msgQueue)
		m_msgQueue->Input_OnRspQryPosition(this,pPositionInfoRtn,pErrorInfo,bIsLast);

	if (bIsLast&&pErrorInfo)
		ReleaseRequestMapBuf(pErrorInfo->requestID);
}

void CTraderApi::ReqQryPositionDetail(const string& szInstrumentId)
{
	if (NULL == m_pApi)
		return;

	SRequest* pRequest = MakeRequestBuf(E_PositionDetailField);
	if (NULL == pRequest)
		return;

	DFITCPositionDetailField* body = (DFITCPositionDetailField*)pRequest->pBuf;

	strncpy(body->accountID, m_szAccountID.c_str(),sizeof(DFITCAccountIDType));
	strncpy(body->instrumentID,szInstrumentId.c_str(),sizeof(DFITCInstrumentIDType));
	//body->instrumentType;

	AddToSendQueue(pRequest);
}

void CTraderApi::OnRspQryPositionDetail(struct DFITCPositionDetailRtnField * pPositionDetailRtn, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	if(m_msgQueue)
		m_msgQueue->Input_OnRspQryPositionDetail(this,pPositionDetailRtn,pErrorInfo,bIsLast);

	if (bIsLast&&pErrorInfo)
		ReleaseRequestMapBuf(pErrorInfo->requestID);
}

void CTraderApi::ReqQryExchangeInstrument(const string& szExchangeId,DFITCInstrumentTypeType instrumentType)
{
	if (NULL == m_pApi)
		return;
	WriteLog("ReqQryExchangeInstrument %s %d",szExchangeId.c_str(),instrumentType); 
	SRequest* pRequest = MakeRequestBuf(E_ExchangeInstrumentField);
	if (NULL == pRequest)
		return;
	
	DFITCExchangeInstrumentField* body = (DFITCExchangeInstrumentField*)pRequest->pBuf;
	
	strncpy(body->accountID,m_szAccountID.c_str(),sizeof(DFITCAccountIDType));
	strncpy(body->exchangeID,szExchangeId.c_str(),sizeof(DFITCExchangeIDType));
	body->instrumentType = instrumentType;
	
	AddToSendQueue(pRequest);
}

void CTraderApi::OnRspQryExchangeInstrument(struct DFITCExchangeInstrumentRtnField * pInstrumentData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{

	WriteLog("OnRspQryExchangeInstrument %s %s",pInstrumentData?pInstrumentData->instrumentID:"Null",pErrorInfo?pErrorInfo->errorMsg:""); 

	if(m_msgQueue)
		m_msgQueue->Input_OnRspQryExchangeInstrument(this,pInstrumentData,pErrorInfo,bIsLast);

	if (bIsLast&&pErrorInfo)
		ReleaseRequestMapBuf(pErrorInfo->requestID);
}

void CTraderApi::ReqQryArbitrageInstrument(const string& szExchangeId)
{
	if (NULL == m_pApi)
		return;
	
	SRequest* pRequest = MakeRequestBuf(E_AbiInstrumentField);
	if (NULL == pRequest)
		return;
	
	DFITCAbiInstrumentField* body = (DFITCAbiInstrumentField*)pRequest->pBuf;
	
	strncpy(body->accountID,m_szAccountID.c_str(),sizeof(DFITCAccountIDType));
	strncpy(body->exchangeID,szExchangeId.c_str(),sizeof(DFITCExchangeIDType));
	
	AddToSendQueue(pRequest);
}

void CTraderApi::OnRspArbitrageInstrument(struct DFITCAbiInstrumentRtnField * pAbiInstrumentData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	if(m_msgQueue)
		m_msgQueue->Input_OnRspArbitrageInstrument(this,pAbiInstrumentData,pErrorInfo,bIsLast);

	if (bIsLast&&pErrorInfo)
		ReleaseRequestMapBuf(pErrorInfo->requestID);
}

void CTraderApi::ReqQrySpecifyInstrument(const string& szInstrumentId,const string& szExchangeId,DFITCInstrumentTypeType instrumentType)
{
	if (NULL == m_pApi)
		return;
	
	SRequest* pRequest = MakeRequestBuf(E_SpecificInstrumentField);
	if (NULL == pRequest)
		return;
	
	DFITCSpecificInstrumentField* body = (DFITCSpecificInstrumentField*)pRequest->pBuf;
	
	strncpy(body->accountID,m_szAccountID.c_str(),sizeof(DFITCAccountIDType));
	strncpy(body->exchangeID,szExchangeId.c_str(),sizeof(DFITCExchangeIDType));
	strncpy(body->InstrumentID,szInstrumentId.c_str(),sizeof(DFITCInstrumentIDType));
	body->instrumentType = instrumentType;
	
	AddToSendQueue(pRequest);
}

void CTraderApi::OnRspQrySpecifyInstrument(struct DFITCInstrumentRtnField * pInstrument, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	if(m_msgQueue)
		m_msgQueue->Input_OnRspQrySpecifyInstrument(this,pInstrument,pErrorInfo,bIsLast);

	if (bIsLast&&pErrorInfo)
		ReleaseRequestMapBuf(pErrorInfo->requestID);
}

void CTraderApi::OnRtnErrorMsg( struct DFITCErrorRtnField *pErrorInfo )
{
	WriteLog("OnRtnErrorMsg localOrderID=%d  errorMsg=%s",pErrorInfo->localOrderID, pErrorInfo->errorMsg);
	if(m_msgQueue)
		m_msgQueue->Input_OnRspError(this,pErrorInfo);

	if (pErrorInfo)
		ReleaseRequestMapBuf(pErrorInfo->requestID);
}

void CTraderApi::ReqQryOrderInfo(DFITCInstrumentTypeType instrumentType)
{
	if (NULL == m_pApi)
		return;
	WriteLog("ReqQryOrderInfo");
	SRequest* pRequest = MakeRequestBuf(E_OrderField);
	if (NULL == pRequest)
		return;
	
	DFITCOrderField* body = (DFITCOrderField*)pRequest->pBuf;
	
	strncpy(body->accountID,m_szAccountID.c_str(),sizeof(DFITCAccountIDType));
	body->instrumentType = instrumentType;
	
	AddToSendQueue(pRequest);
}

void CTraderApi::OnRspQryOrderInfo(struct DFITCOrderCommRtnField * pRtnOrderData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	WriteLog("OnRspQryOrderInfo");
	if(m_msgQueue)
		m_msgQueue->Input_OnRspQryOrderInfo(this,pRtnOrderData,pErrorInfo,bIsLast);

	if (bIsLast&&pErrorInfo)
		ReleaseRequestMapBuf(pErrorInfo->requestID);
}

void CTraderApi::ReqQryMatchInfo(DFITCInstrumentTypeType instrumentType)
{
	if (NULL == m_pApi)
		return;
	WriteLog("ReqQryMatchInfo");
	SRequest* pRequest = MakeRequestBuf(E_MatchField);
	if (NULL == pRequest)
		return;
	
	DFITCMatchField* body = (DFITCMatchField*)pRequest->pBuf;
	
	strncpy(body->accountID,m_szAccountID.c_str(),sizeof(DFITCAccountIDType));
	body->instrumentType = instrumentType;
	
	AddToSendQueue(pRequest);
}

void CTraderApi::OnRspQryMatchInfo(struct DFITCMatchedRtnField * pRtnMatchData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	if(m_msgQueue)
		m_msgQueue->Input_OnRspQryMatchInfo(this,pRtnMatchData,pErrorInfo,bIsLast);

	if (bIsLast&&pErrorInfo)
		ReleaseRequestMapBuf(pErrorInfo->requestID);
}

void CTraderApi::OnRtnInstrumentStatus(DFITCInstrumentStatusField *pInstrumentStatus)
{
	if(m_msgQueue)
		m_msgQueue->Input_OnRtnInstrumentStatus(this,pInstrumentStatus);
}

void CTraderApi::ReqQuoteSubscribe()
{
	if (NULL == m_pApi)
		return;
	WriteLog("ReqQuoteSubscribe");
	SRequest* pRequest = MakeRequestBuf(E_QuoteSubscribeField);
	if (NULL == pRequest)
		return;
	
	DFITCQuoteSubscribeField * body = (DFITCQuoteSubscribeField*)pRequest->pBuf;
	
	strncpy(body->accountID,m_szAccountID.c_str(),sizeof(DFITCAccountIDType));
	
	AddToSendQueue(pRequest);
}

void CTraderApi::OnRspQuoteSubscribe(struct DFITCQuoteSubscribeRspField * pRspQuoteSubscribeData)
{
	if(m_msgQueue)
		m_msgQueue->Input_OnRspQuoteSubscribe(this,pRspQuoteSubscribeData);
}

void CTraderApi::OnRtnQuoteSubscribe(struct DFITCQuoteSubscribeRtnField * pRtnQuoteSubscribeData)
{
	if(m_msgQueue)
		m_msgQueue->Input_OnRtnQuoteSubscribe(this,pRtnQuoteSubscribeData);
}

long CTraderApi::ReqQuoteInsertOrder(
	long localOrderID,
	const string& szInstrumentId,
	const string& quoteID,
	DFITCAmountType bOrderAmount,
	DFITCAmountType sOrderAmount,
	DFITCPriceType bInsertPrice,
	DFITCPriceType sInsertPrice,
	DFITCOpenCloseTypeType bOpenCloseType,
	DFITCOpenCloseTypeType sOpenCloseType,
	DFITCSpeculatorType bSpeculator,
	DFITCSpeculatorType sSpeculator,
	DFITCStayTimeType stayTime,
	DFITCInstrumentTypeType nInstrumentType
	)
{
	if (NULL == m_pApi)
		return 0;

	//WriteLog("ReqQuoteInsertOrder localOrderID=%d  szInstrumentId=%s lAmount=%d dbPrice=%f orderType=%s ",localOrderID ,szInstrumentId.c_str(),lAmount,dbPrice,orderType==DFITC_LIMITORDER?"限价":"市价");

	SRequest* pRequest = MakeRequestBuf(E_QuoteInsertOrderField);
	if (NULL == pRequest)
		return 0;

	DFITCQuoteInsertOrderField* body = (DFITCQuoteInsertOrderField*)pRequest->pBuf;

	strncpy(body->accountID, m_szAccountID.c_str(),sizeof(DFITCAccountIDType));
	// 合约
	strncpy(body->instrumentID,szInstrumentId.c_str(),sizeof(DFITCInstrumentIDType));
	// 价格
	body->bInsertPrice = bInsertPrice;
	body->sInsertPrice = sInsertPrice;
	// 数量
	body->bOrderAmount = bOrderAmount;
	body->sOrderAmount = sOrderAmount;
	// 买卖
	body->buySellType = DFITC_SPD_ALL;
	// 开平
	body->bOpenCloseType = bOpenCloseType;
	body->sOpenCloseType = sOpenCloseType;
	// 投保
	body->bSpeculator = bSpeculator;
	body->sSpeculator = sSpeculator;

	body->stayTime = stayTime;

	body->insertType = DFITC_BASIC_ORDER;
	body->instrumentType = nInstrumentType;
	
	long nRet = 0;
	{
		//可能报单太快，m_nMaxOrderRef还没有改变就提交了
		CLock cl(&m_csOrderRef);

		char buf[255] = {0};
		sprintf(buf,"clock = %d",clock());
		OutputDebugStringA(buf);

		//不保存到队列，而是直接发送
		if(localOrderID == -1)
		{
			InterlockedIncrement(&m_lLocalOrderID);
			body->localOrderID = m_lLocalOrderID;
		}
		else
		{
			body->localOrderID = localOrderID;
		}
		int n = m_pApi->ReqQuoteInsertOrder((DFITCQuoteInsertOrderField*)pRequest->pBuf);
		nRet = body->localOrderID;
	}
	delete pRequest->pBuf;
	delete pRequest;//用完后直接删除
	WriteLog("订单%d已发送",nRet);
	return nRet;
}



void CTraderApi::OnRspUserLogout(struct DFITCUserLogoutInfoRtnField * pUserLogoutInfoRtn, struct DFITCErrorRtnField * pErrorInfo)
{
}
void CTraderApi::OnRspResetPassword(struct DFITCResetPwdRspField * pResetPassword, struct DFITCErrorRtnField * pErrorInfo)
{}
void CTraderApi::OnRspQryTradeCode(struct DFITCQryTradeCodeRtnField * pTradeCode, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{}
void CTraderApi::OnRspBillConfirm(struct DFITCBillConfirmRspField * pBillConfirm, struct DFITCErrorRtnField * pErrorInfo)
{}
void CTraderApi::OnRspEquityComputMode(struct DFITCEquityComputModeRtnField * pEquityComputMode)
{}
void CTraderApi::OnRspQryBill(struct DFITCQryBillRtnField *pQryBill, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{}
void CTraderApi::OnRspConfirmProductInfo(struct DFITCProductRtnField * pProductRtnData)
{}
void CTraderApi::OnRspTradingDay(struct DFITCTradingDayRtnField * pTradingDayRtnData)
{}
