#pragma once

#include "QuantBox.C2XSpeed.h"
#include "include\XSpeed\DFITCMdApi.h"

#include <list>
#include <set>
#include <map>
#include <string>

using namespace std;
using namespace DFITCXSPEEDMDAPI;

class CXSpeedMsgQueue;

class CMdUserApi :
	public DFITCMdSpi
{
	//请求数据包类型
	enum RequestType
	{
		E_Init,
		E_UserLoginField,
	};

	//请求数据包结构体
	struct SRequest
	{
		RequestType type;
		void* pBuf;
	};

public:
	CMdUserApi(void);
	virtual ~CMdUserApi(void);

	void RegisterMsgQueue(CXSpeedMsgQueue* pMsgQueue);

	void Connect(
		const string& szSvrAddr,
		const string& szAccountID,
		const string& szPassword,
		short sCompanyID);
	void Disconnect();

	void Subscribe(const string& szInstrumentIDs);
	void Unsubscribe(const string& szInstrumentIDs);

private:
		//数据包发送线程
	friend DWORD WINAPI SendThread_MD(LPVOID lpParam);
	void RunInThread();
	void StopThread();

	//指定数据包类型，生成对应数据包
	SRequest * MakeRequestBuf(RequestType type);
	//清除将发送请求包队列
	void ReleaseRequestListBuf();
	//清除已发送请求包池
	void ReleaseRequestMapBuf();
	//清除指定请求包池中指定包
	void ReleaseRequestMapBuf(int nRequestID);
	//添加到已经请求包池
	void AddRequestMapBuf(int nRequestID,SRequest* pRequest);
	//添加到将发送包队列
	void AddToSendQueue(SRequest * pRequest);


	//订阅行情
	void Subscribe(const set<string>& instrumentIDs);
	int ReqInit();
	//登录请求
	void ReqUserLogin();

	virtual void OnFrontConnected();
	virtual void OnFrontDisconnected(int nReason);
	virtual void OnRspUserLogin(struct DFITCUserLoginInfoRtnField *pRspUserLogin, struct DFITCErrorRtnField *pRspInfo);
	virtual void OnRspUserLogout(struct DFITCUserLogoutInfoRtnField * pRspUsrLogout, struct DFITCErrorRtnField * pRspInfo);
	virtual void OnRspError(struct DFITCErrorRtnField *pRspInfo);
	virtual void OnRspSubMarketData(struct DFITCSpecificInstrumentField *pSpecificInstrument, struct DFITCErrorRtnField *pRspInfo);
	virtual void OnRspUnSubMarketData(struct DFITCSpecificInstrumentField *pSpecificInstrument, struct DFITCErrorRtnField *pRspInfo);
	virtual void OnMarketData(struct DFITCDepthMarketDataField *pMarketDataField);
	virtual void OnRspTradingDay(struct DFITCTradingDayRtnField * pTradingDayRtnData);
	//检查是否出错
	bool IsErrorRspInfo_Output(struct DFITCErrorRtnField *pRspInfo);//将出错消息送到消息队列
	bool IsErrorRspInfo(struct DFITCErrorRtnField *pRspInfo); //不输出信息

private:
	CRITICAL_SECTION			m_csMapInstrumentIDs;

	ConnectionStatus			m_status;				//连接状态
	long						m_lRequestID;			//请求ID，每次请求前自增
	
	set<string>					m_setInstrumentIDs;		//正在订阅的合约
	DFITCMdApi*					m_pApi;					//行情API
	CXSpeedMsgQueue*			m_msgQueue;				//消息队列指针

	string						m_szSvrAddr;
	string						m_szAccountID;			//投资者ID
	string						m_szPassword;			//密码
	short						m_sCompanyID;			//期商ID

	int							m_nSleep;
	volatile bool				m_bRunning;
	HANDLE						m_hThread;

	CRITICAL_SECTION			m_csList;
	list<SRequest*>				m_reqList;				//将发送请求队列

	CRITICAL_SECTION			m_csMap;
	map<int,SRequest*>			m_reqMap;				//已发送请求池
};

