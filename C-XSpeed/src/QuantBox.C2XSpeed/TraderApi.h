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
	//�������ݰ�����
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
		E_QuoteInsertField,
		E_QuoteCancelField,
	};

	//�������ݰ��ṹ��
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
		DFITCInstrumentTypeType nInstrumentType,
		DFITCInsertType insertType);
	void ReqCancelOrder(
		const string& szInstrumentId,
		DFITCLocalOrderIDType localOrderID,
		DFITCSPDOrderIDType spdOrderID);

	long ReqQuoteInsert(
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
	//���ݰ������߳�
	friend DWORD WINAPI SendThread_TD(LPVOID lpParam);
	void RunInThread();
	void StopThread();

	//ָ�����ݰ����ͣ����ɶ�Ӧ���ݰ�
	SRequest * MakeRequestBuf(RequestType type);
	//������������������
	void ReleaseRequestListBuf();
	//����ѷ����������
	void ReleaseRequestMapBuf();
	//���ָ�����������ָ����
	void ReleaseRequestMapBuf(int nRequestID);
	//��ӵ��Ѿ��������
	void AddRequestMapBuf(int nRequestID,SRequest* pRequest);
	//��ӵ������Ͱ�����
	void AddToSendQueue(SRequest * pRequest);

	int ReqInit();
	//��¼����
	void ReqUserLogin();

	//����Ƿ����
	bool IsErrorRspInfo_Output(struct DFITCErrorRtnField *pRspInfo);//��������Ϣ�͵���Ϣ����
	bool IsErrorRspInfo(struct DFITCErrorRtnField *pRspInfo); //�������Ϣ

	//����
	virtual void OnFrontConnected();
	virtual void OnFrontDisconnected(int nReason);

	//��֤
	virtual void OnRspUserLogin(struct DFITCUserLoginInfoRtnField *pRspUserLogin, struct DFITCErrorRtnField *pRspInfo);
	virtual void OnRspUserLogout(struct DFITCUserLogoutInfoRtnField * pUserLogoutInfoRtn, struct DFITCErrorRtnField * pErrorInfo);
	//�µ�
	virtual void OnRspInsertOrder(struct DFITCOrderRspDataRtnField * pOrderRtn, struct DFITCErrorRtnField * pErrorInfo);
	virtual void OnRtnOrder(struct DFITCOrderRtnField * pRtnOrderData);

	virtual void OnRspQryOrderInfo(struct DFITCOrderCommRtnField * pRtnOrderData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);
	
	//����
	virtual void OnRspCancelOrder( struct DFITCOrderRspDataRtnField *pOrderCanceledRtn,struct DFITCErrorRtnField *pErrorInfo);
	virtual void OnRtnCancelOrder(struct DFITCOrderCanceledRtnField * pCancelOrderData);

	//�ɽ��ر�
	virtual void OnRspQryMatchInfo(struct DFITCMatchedRtnField * pRtnMatchData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);
	virtual void OnRtnMatchedInfo(struct DFITCMatchRtnField * pRtnMatchData);

	//��λ
	virtual void OnRspQryPosition(struct DFITCPositionInfoRtnField * pPositionInfoRtn, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);
	virtual void OnRspQryPositionDetail(struct DFITCPositionDetailRtnField * pPositionDetailRtn, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);
	
	//�ʽ�
	virtual void OnRspCustomerCapital(struct DFITCCapitalInfoRtnField * pCapitalInfoRtn, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);
	
	//��Լ��������
	virtual void OnRspQryExchangeInstrument(struct DFITCExchangeInstrumentRtnField * pInstrumentData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);
	virtual void OnRspArbitrageInstrument(struct DFITCAbiInstrumentRtnField * pAbiInstrumentData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);
	virtual void OnRspQrySpecifyInstrument(struct DFITCInstrumentRtnField * pInstrument, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	////����
	virtual void OnRtnErrorMsg( struct DFITCErrorRtnField *pErrorInfo );
	virtual void OnRtnExchangeStatus(struct DFITCExchangeStatusRtnField * pRtnExchangeStatusData);
    
	virtual void OnRspResetPassword(struct DFITCResetPwdRspField * pResetPassword, struct DFITCErrorRtnField * pErrorInfo);
    virtual void OnRspQryTradeCode(struct DFITCQryTradeCodeRtnField * pTradeCode, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);
    virtual void OnRspBillConfirm(struct DFITCBillConfirmRspField * pBillConfirm, struct DFITCErrorRtnField * pErrorInfo);
    virtual void OnRspEquityComputMode(struct DFITCEquityComputModeRtnField * pEquityComputMode);
    virtual void OnRspQryBill(struct DFITCQryBillRtnField *pQryBill, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);
    virtual void OnRspConfirmProductInfo(struct DFITCProductRtnField * pProductRtnData);
    virtual void OnRspTradingDay(struct DFITCTradingDayRtnField * pTradingDayRtnData);

	// ������
	virtual void OnRspQuoteSubscribe(struct DFITCQuoteSubscribeRspField * pRspQuoteSubscribeData);
	virtual void OnRtnQuoteSubscribe(struct DFITCQuoteSubscribeRtnField * pRtnQuoteSubscribeData);
	virtual void OnRspQuoteInsert(struct DFITCQuoteRspField * pRspQuoteData, struct DFITCErrorRtnField * pErrorInfo);
	virtual void OnRtnQuote(struct DFITCQuoteRtnField * pRtnQuoteData);
	virtual void OnRspQuoteCancel( struct DFITCQuoteRspField * pRspQuoteCanceledData,struct DFITCErrorRtnField * pErrorInfo);
	virtual void OnRtnQuoteCancel(struct DFITCQuoteCanceledRtnField * pRtnQuoteCanceledData);

private:
	ConnectionStatus			m_status;				//����״̬
	volatile LONG				m_lRequestID;			//����ID,�ñ�������
	
	DFITCUserLoginInfoRtnField	m_RspUserLogin;			//���صĵ�¼�ɹ���Ӧ��Ŀǰ���ô��ڳ�Ա���б�����������

	CRITICAL_SECTION			m_csOrderRef;
	long		m_lLocalOrderID;			//�������ã��������ֱ�������������

	DFITCTraderApi*		m_pApi;					//����API
	CXSpeedMsgQueue*				m_msgQueue;				//��Ϣ����ָ��

	string						m_szSvrAddr;
	string						m_szAccountID;			//Ͷ����ID
	string						m_szPassword;			//����
	short						m_sCompanyID;			//����ID

	int							m_nSleep;
	volatile bool				m_bRunning;
	HANDLE						m_hThread;

	CRITICAL_SECTION			m_csList;
	list<SRequest*>				m_reqList;				//�������������

	CRITICAL_SECTION			m_csMap;
	map<int,SRequest*>			m_reqMap;				//�ѷ��������

	
};

