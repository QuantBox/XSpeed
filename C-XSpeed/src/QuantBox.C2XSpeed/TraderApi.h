#pragma once

#include "QuantBox.C2XSpeed.h"
#include "include\XSpeed\DFITCTraderApi.h"

#include <set>
#include <list>
#include <map>
#include <string>

using namespace std;
using namespace DFITCXSPEEDAPI;

class CXSpeedMsgQueue;

class CTraderApi :
	public DFITCTraderSpi
{
	//请求数据包类型
	enum RequestType
	{
		E_AbiInstrumentField,
		E_CancelOrderField,
		E_CapitalField,
		E_ExchangeInstrumentField,
		E_Init,
		E_InsertOrderField,
		E_MatchField,
		E_OrderField,
		E_PositionField,
		E_PositionDetailField,
		E_SpecificInstrumentField,
		E_UserLoginField,
		E_QuoteSubscribeField,
		E_QuoteInsertOrderField,
		E_QuoteCancelOrderField,
	};

	//请求数据包结构体
	struct SRequest
	{
		RequestType type;
		void* pBuf;
	};

public:
	CTraderApi(void);
	virtual ~CTraderApi(void);

	void RegisterMsgQueue(CXSpeedMsgQueue* pMsgQueue);

	void Connect(
		const string& szSvrAddr,
		const string& szAccountID,
		const string& szPassword,
		short sCompanyID);
	void Disconnect();

	long ReqInsertOrder(
		long localOrderID,
		const string& szInstrumentId,
		DFITCBuySellTypeType sBuySellType,
		DFITCOpenCloseTypeType sOpenCloseType,
		DFITCSpeculatorType sSpeculator,
		DFITCAmountType lAmount,
		DFITCPriceType dbPrice,
		DFITCOrderTypeType orderType,
		DFITCOrderPropertyType orderProperty,
		DFITCInstrumentTypeType nInstrumentType);
	void ReqCancelOrder(
		const string& szInstrumentId,
		DFITCLocalOrderIDType localOrderID,
		DFITCSPDOrderIDType spdOrderID);

	long ReqQuoteInsertOrder(
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
			DFITCInstrumentTypeType nInstrumentType);
	void ReqQuoteCancelOrder(
		const string& szInstrumentId,
		DFITCLocalOrderIDType localOrderID,
		DFITCSPDOrderIDType spdOrderID);

	void ReqQryMatchInfo(DFITCInstrumentTypeType instrumentType);
	void ReqQryOrderInfo(DFITCInstrumentTypeType instrumentType);
	void ReqQryCustomerCapital();
	void ReqQryPosition(const string& szInstrumentId);
	void ReqQryPositionDetail(const string& szInstrumentId);
	void ReqQryExchangeInstrument(const string& szExchangeId,DFITCInstrumentTypeType instrumentType);
	void ReqQryArbitrageInstrument(const string& szExchangeId);
	void ReqQrySpecifyInstrument(const string& szInstrumentId,const string& szExchangeId,DFITCInstrumentTypeType instrumentType);
	void ReqQuoteSubscribe();

private:
	//数据包发送线程
	friend DWORD WINAPI SendThread_TD(LPVOID lpParam);
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

	int ReqInit();
	//登录请求
	void ReqUserLogin();

	//检查是否出错
	bool IsErrorRspInfo_Output(struct DFITCErrorRtnField *pRspInfo);//将出错消息送到消息队列
	bool IsErrorRspInfo(struct DFITCErrorRtnField *pRspInfo); //不输出信息

	//连接
	virtual void OnFrontConnected();
	virtual void OnFrontDisconnected(int nReason);

	//认证
	virtual void OnRspUserLogin(struct DFITCUserLoginInfoRtnField *pRspUserLogin, struct DFITCErrorRtnField *pRspInfo);
	virtual void OnRspUserLogout(struct DFITCUserLogoutInfoRtnField * pUserLogoutInfoRtn, struct DFITCErrorRtnField * pErrorInfo);
	//下单
	virtual void OnRspInsertOrder(struct DFITCOrderRspDataRtnField * pOrderRtn, struct DFITCErrorRtnField * pErrorInfo);
	virtual void OnRtnOrder(struct DFITCOrderRtnField * pRtnOrderData);

	virtual void OnRspQryOrderInfo(struct DFITCOrderCommRtnField * pRtnOrderData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);
	
	//撤单
	virtual void OnRspCancelOrder( struct DFITCOrderRspDataRtnField *pOrderCanceledRtn,struct DFITCErrorRtnField *pErrorInfo);
	virtual void OnRtnCancelOrder(struct DFITCOrderCanceledRtnField * pCancelOrderData);

	//成交回报
	virtual void OnRspQryMatchInfo(struct DFITCMatchedRtnField * pRtnMatchData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);
	virtual void OnRtnMatchedInfo(struct DFITCMatchRtnField * pRtnMatchData);

	//仓位
	virtual void OnRspQryPosition(struct DFITCPositionInfoRtnField * pPositionInfoRtn, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);
	virtual void OnRspQryPositionDetail(struct DFITCPositionDetailRtnField * pPositionDetailRtn, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);
	
	//资金
	virtual void OnRspCustomerCapital(struct DFITCCapitalInfoRtnField * pCapitalInfoRtn, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);
	
	//合约、手续费
	virtual void OnRspQryExchangeInstrument(struct DFITCExchangeInstrumentRtnField * pInstrumentData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);
	virtual void OnRspArbitrageInstrument(struct DFITCAbiInstrumentRtnField * pAbiInstrumentData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);
	virtual void OnRspQrySpecifyInstrument(struct DFITCInstrumentRtnField * pInstrument, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	////其它
	virtual void OnRtnErrorMsg( struct DFITCErrorRtnField *pErrorInfo );
	virtual void OnRtnInstrumentStatus(DFITCInstrumentStatusField *pInstrumentStatus);
    
	virtual void OnRspResetPassword(struct DFITCResetPwdRspField * pResetPassword, struct DFITCErrorRtnField * pErrorInfo);
    virtual void OnRspQryTradeCode(struct DFITCQryTradeCodeRtnField * pTradeCode, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);
    virtual void OnRspBillConfirm(struct DFITCBillConfirmRspField * pBillConfirm, struct DFITCErrorRtnField * pErrorInfo);
    virtual void OnRspEquityComputMode(struct DFITCEquityComputModeRtnField * pEquityComputMode);
    virtual void OnRspQryBill(struct DFITCQryBillRtnField *pQryBill, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);
    virtual void OnRspConfirmProductInfo(struct DFITCProductRtnField * pProductRtnData);
    virtual void OnRspTradingDay(struct DFITCTradingDayRtnField * pTradingDayRtnData);

	// 做市商
	virtual void OnRspQuoteSubscribe(struct DFITCQuoteSubscribeRspField * pRspQuoteSubscribeData);
	virtual void OnRtnQuoteSubscribe(struct DFITCQuoteSubscribeRtnField * pRtnQuoteSubscribeData);
	virtual void OnRspQuoteInsertOrder(struct DFITCQuoteOrderRspField * pRspQuoteOrderData, struct DFITCErrorRtnField * pErrorInfo);
	virtual void OnRtnQuoteOrder(struct DFITCQuoteOrderRtnField * pRtnQuoteOrderData);
	virtual void OnRspQuoteCancelOrder( struct DFITCQuoteOrderRspField * pRspQuoteCanceledData,struct DFITCErrorRtnField * pErrorInfo);
	virtual void OnRtnQuoteCancelOrder(struct DFITCQuoteCanceledRtnField * pRtnQuoteCanceledData);   

private:
	ConnectionStatus			m_status;				//连接状态
	volatile LONG				m_lRequestID;			//请求ID,得保持自增
	
	DFITCUserLoginInfoRtnField	m_RspUserLogin;			//返回的登录成功响应，目前利用此内成员进行报单所属区分

	CRITICAL_SECTION			m_csOrderRef;
	long		m_lLocalOrderID;			//报单引用，用于区分报单，保持自增

	DFITCTraderApi*		m_pApi;					//交易API
	CXSpeedMsgQueue*				m_msgQueue;				//消息队列指针

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

