#include "StdAfx.h"
#include "MdUserApi.h"
#include "XSpeedMsgQueue.h"
#include "include\toolkit.h"
#include "include\Lock.h"

#include <iostream>
using namespace std;

CMdUserApi::CMdUserApi(void)
{
	m_msgQueue = NULL;
	m_status = E_uninit;
	m_lRequestID = 0;

	m_hThread = NULL;
	m_bRunning = false;

	InitializeCriticalSection(&m_csList);
	InitializeCriticalSection(&m_csMap);
	InitializeCriticalSection(&m_csMapInstrumentIDs);
}

CMdUserApi::~CMdUserApi(void)
{
	Disconnect();

	DeleteCriticalSection(&m_csMapInstrumentIDs);
	DeleteCriticalSection(&m_csList);
	DeleteCriticalSection(&m_csMap);
}

void CMdUserApi::StopThread()
{
	WriteLog("StopThread");
	//停止发送线程
	m_bRunning = false;
	WaitForSingleObject(m_hThread,INFINITE);
	CloseHandle(m_hThread);
	m_hThread = NULL;
}

void CMdUserApi::RegisterMsgQueue(CXSpeedMsgQueue* pMsgQueue)
{
	m_msgQueue = pMsgQueue;
}

bool CMdUserApi::IsErrorRspInfo_Output(struct DFITCErrorRtnField *pRspInfo)
{
	bool bRet = ((pRspInfo) && (pRspInfo->nErrorID != 0));
	if(bRet)
	{
		if(m_msgQueue)
			m_msgQueue->Input_OnRspError(this,pRspInfo);
	}
	return bRet;
}

bool CMdUserApi::IsErrorRspInfo(struct DFITCErrorRtnField *pRspInfo)   
{
	bool bRet = ((pRspInfo) && (pRspInfo->nErrorID != 0));

	return bRet;
}

void CMdUserApi::Connect(
		const string& szSvrAddr,
		const string& szAccountID,
		const string& szPassword,
		short sCompanyID)
{
	m_szSvrAddr = szSvrAddr;
	m_szAccountID = szAccountID;
	m_szPassword = szPassword;
	m_sCompanyID = sCompanyID;
	
	m_pApi = DFITCMdApi::CreateDFITCMdApi();

	m_status = E_inited;
	if(m_msgQueue)
		m_msgQueue->Input_OnConnect(this,NULL,m_status);

	SRequest* pRequest = MakeRequestBuf(E_Init);
	if(pRequest)
	{
		AddToSendQueue(pRequest);
	}
}

void CMdUserApi::Disconnect()
{
	StopThread();

	m_status = E_unconnected;
	if(m_pApi)
	{
		WriteLog("MD Disconnect");
		//m_pApi->RegisterSpi(NULL);
		m_pApi->Release();
		m_pApi = NULL;

		if(m_msgQueue)
			m_msgQueue->Input_OnDisconnect(this,NULL,m_status);
	}
}

void CMdUserApi::Subscribe(const string& szInstrumentIDs)
{
	WriteLog("MD Subscribe %s ", szInstrumentIDs.c_str());
	if(NULL == m_pApi)
		return;

	vector<char*> vct;

	size_t len = szInstrumentIDs.length()+1;
	char* buf = new char[len];
	strncpy(buf,szInstrumentIDs.c_str(),len);

	CLock cl(&m_csMapInstrumentIDs);

	char* token = strtok(buf, _QUANTBOXC2XSPEED_SEPS_);
	while(token)
	{
		size_t l = strlen(token);
		if (l>0)
		{
			//合约已经存在，不用再订阅，但多次订阅也没关系
			m_setInstrumentIDs.insert(token);//记录此合约进行订阅
			vct.push_back(token);
		}
		token = strtok( NULL, _QUANTBOXC2XSPEED_SEPS_);
	}
	
	if(vct.size()>0)
	{
		//转成字符串数组
		char** pArray = new char*[vct.size()];
		for (size_t j = 0; j<vct.size(); ++j)
		{
			pArray[j] = vct[j];
		}

		//订阅
		m_pApi->SubscribeMarketData(pArray,(int)vct.size(),m_lRequestID++);

		delete[] pArray;
	}

	//释放内存
	delete[] buf;
}

void CMdUserApi::Subscribe(const set<string>& instrumentIDs)
{
	
	if(NULL == m_pApi)
		return;

	string szInstrumentIDs;
	for(set<string>::iterator i=instrumentIDs.begin();i!=instrumentIDs.end();++i)
	{
		szInstrumentIDs.append(*i);
		szInstrumentIDs.append(";");
	}

	if (szInstrumentIDs.length()>1)
	{
		Subscribe(szInstrumentIDs);
	}
}

void CMdUserApi::Unsubscribe(const string& szInstrumentIDs)
{
	WriteLog("MD Unsubscribe %s ", szInstrumentIDs.c_str());
	if(NULL == m_pApi)
		return;

	vector<char*> vct;
	size_t len = szInstrumentIDs.length()+1;
	char* buf = new char[len];
	strncpy(buf,szInstrumentIDs.c_str(),len);

	CLock cl(&m_csMapInstrumentIDs);

	char* token = strtok(buf, _QUANTBOXC2XSPEED_SEPS_);
	while(token)
	{
		size_t l = strlen(token);
		if (l>0)
		{
			//合约已经不存在，不用再取消订阅，但多次取消也没什么关系
			m_setInstrumentIDs.erase(token);
			vct.push_back(token);
		}
		token = strtok( NULL, _QUANTBOXC2XSPEED_SEPS_);
	}
	
	if(vct.size()>0)
	{
		//转成字符串数组
		char** pArray = new char*[vct.size()];
		for (size_t j = 0; j<vct.size(); ++j)
		{
			pArray[j] = vct[j];
		}

		//订阅
		m_pApi->UnSubscribeMarketData(pArray,(int)vct.size(),m_lRequestID++);

		delete[] pArray;
	}

	//释放内存
	delete[] buf;
}

CMdUserApi::SRequest* CMdUserApi::MakeRequestBuf(RequestType type)
{
	SRequest *pRequest = new SRequest;
	if (NULL == pRequest)
		return NULL;

	memset(pRequest,0,sizeof(SRequest));
	pRequest->type = type;
	switch(type)
	{
	case E_Init:
		break;
	case E_UserLoginField:
		pRequest->pBuf = new DFITCUserLoginField();
		break;
	}
	return pRequest;
}

void CMdUserApi::ReleaseRequestListBuf()
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

void CMdUserApi::ReleaseRequestMapBuf()
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

void CMdUserApi::ReleaseRequestMapBuf(int nRequestID)
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

void CMdUserApi::AddRequestMapBuf(int nRequestID,SRequest* pRequest)
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

DWORD WINAPI SendThread_MD(LPVOID lpParam)
{
	CMdUserApi* pTrade = reinterpret_cast<CMdUserApi *>(lpParam);
	if (pTrade)
		pTrade->RunInThread();
	return 0;
}

void CMdUserApi::AddToSendQueue(SRequest * pRequest)
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
		m_hThread = CreateThread(NULL,0,SendThread_MD,this,0,NULL); 
	}
}


void CMdUserApi::RunInThread()
{
	int iRet = 0;

	while (!m_reqList.empty()&&m_bRunning)
	{
		SRequest * pRequest = m_reqList.front();
		long lRequest = InterlockedIncrement(&m_lRequestID);
		switch(pRequest->type)
		{
		case E_Init:
			iRet = ReqInit();
			break;
		case E_UserLoginField:
			iRet = m_pApi->ReqUserLogin((DFITCUserLoginField*)pRequest->pBuf);
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

int CMdUserApi::ReqInit()
{
	WriteLog("MD ReqInit ");
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

void CMdUserApi::OnFrontConnected()
{
	WriteLog("MD OnFrontConnected ");
	m_status =  E_connected;
	if(m_msgQueue)
		m_msgQueue->Input_OnConnect(this,NULL,m_status);

	//连接成功后自动请求登录
	ReqUserLogin();
}

void CMdUserApi::OnFrontDisconnected(int nReason)
{
	WriteLog("MD OnFrontDisconnected %d", nReason);
	m_status = E_unconnected;
	//CThostFtdcRspInfoField RspInfo;
	////连接失败返回的信息是拼接而成，主要是为了统一输出
	//RspInfo.ErrorID = nReason;
	//GetOnFrontDisconnectedMsg(&RspInfo);
	
	//if(m_msgQueue)
	//	m_msgQueue->Input_OnDisconnect(this,&RspInfo,m_status);
}

void CMdUserApi::ReqUserLogin()
{
    WriteLog("MD ReqUserLogin ");

	if (NULL == m_pApi)
		return;

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
		body->lRequestID = m_lRequestID++;

		AddToSendQueue(pRequest);
	}
}

void CMdUserApi::OnRspUserLogin(struct DFITCUserLoginInfoRtnField *pRspUserLogin, struct DFITCErrorRtnField *pRspInfo)
{
	WriteLog("MD OnRspUserLogin  accountID=%s ErrorID=%d ErrorMsg=%s", pRspUserLogin?pRspUserLogin->accountID:0,pRspInfo?pRspInfo->nErrorID:0,pRspInfo?pRspInfo->errorMsg:"null");
	if (!IsErrorRspInfo(pRspInfo)
		&&pRspUserLogin)
	{
		m_status = E_logined;
		if(m_msgQueue)
			m_msgQueue->Input_OnConnect(this,pRspUserLogin,m_status);
		
		//有可能断线了，本处是断线重连后重新订阅
		set<string> mapOld = m_setInstrumentIDs;//记下上次订阅的合约
		//Unsubscribe(mapOld);//由于已经断线了，没有必要再取消订阅
		Subscribe(mapOld);//订阅
	}
	else
	{
		m_status = E_connected;
		if(m_msgQueue)
			m_msgQueue->Input_OnDisconnect(this,pRspInfo,E_logining);
	}
}

void CMdUserApi::OnRspError(DFITCErrorRtnField *pRspInfo)
{
	WriteLog("MD OnRspError  %d %s", pRspInfo?pRspInfo->nErrorID:0,pRspInfo?pRspInfo->errorMsg:"null");
	if(m_msgQueue)
		m_msgQueue->Input_OnRspError(this,pRspInfo);
}

void CMdUserApi::OnRspSubMarketData(struct DFITCSpecificInstrumentField *pSpecificInstrument, struct DFITCErrorRtnField *pRspInfo)
{
	WriteLog("MD OnRspSubMarketData %s  %d %s", pSpecificInstrument?pSpecificInstrument->InstrumentID:"null",pRspInfo?pRspInfo->nErrorID:0,pRspInfo?pRspInfo->errorMsg:"" );
	if(pRspInfo)
	{
		WriteLog("MD OnRspSubMarketData %s ",pRspInfo->errorMsg);
	}
	
	//在模拟平台可能这个函数不会触发，所以要自己维护一张已经订阅的合约列表
	if(!IsErrorRspInfo_Output(pRspInfo)
		&&pSpecificInstrument)
	{
		CLock cl(&m_csMapInstrumentIDs);

		m_setInstrumentIDs.insert(pSpecificInstrument->InstrumentID);
	}
}

void CMdUserApi::OnRspUnSubMarketData(struct DFITCSpecificInstrumentField *pSpecificInstrument, struct DFITCErrorRtnField *pRspInfo)
{
	WriteLog("MD OnRspUnSubMarketData %s  %d", pSpecificInstrument?pSpecificInstrument->InstrumentID:"null",pRspInfo?pRspInfo->nErrorID:0);
	//模拟平台可能这个函数不会触发
	if(!IsErrorRspInfo_Output(pRspInfo)
		&&pSpecificInstrument)
	{
		CLock cl(&m_csMapInstrumentIDs);

		m_setInstrumentIDs.erase(pSpecificInstrument->InstrumentID);
	}
}

//行情回调，得保证此函数尽快返回
void CMdUserApi::OnMarketData(struct DFITCDepthMarketDataField *pMarketDataField)
{
//	WriteLog("MD OnMarketData %s  %f",pMarketDataField->instrumentID,pMarketDataField->lastPrice);
	if(m_msgQueue)
		m_msgQueue->Input_OnMarketData(this,pMarketDataField);
}
 void CMdUserApi::OnRspTradingDay(struct DFITCTradingDayRtnField * pTradingDayRtnData)
{
	WriteLog("MD OnRspTradingDay %s ",pTradingDayRtnData->date);
}

void CMdUserApi::OnRspUserLogout(struct DFITCUserLogoutInfoRtnField * pRspUsrLogout, struct DFITCErrorRtnField * pRspInfo)
{
	WriteLog("MD OnRspUserLogout  accountID=%s ErrorID=%d ErrorMsg=%s", pRspUsrLogout?pRspUsrLogout->accountID:0,pRspInfo?pRspInfo->nErrorID:0,pRspInfo?pRspInfo->errorMsg:"null");

}