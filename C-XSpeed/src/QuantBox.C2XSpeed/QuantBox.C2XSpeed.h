// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� QUANTBOXC2XSPEED_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// QUANTBOXC2XSPEED_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifndef _QUANTBOXC2XSPEED_H_
#define _QUANTBOXC2XSPEED_H_

#ifdef QUANTBOXC2XSPEED_EXPORTS
#define QUANTBOXC2XSPEED_API __declspec(dllexport)
#else
#define QUANTBOXC2XSPEED_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "include\XSpeed\DFITCApiStruct.h"

//���ڷָ�����ĺ��б���ǰ�û���ַ�б����Բ��ܳ��֡�:��һ���
#define _QUANTBOXC2XSPEED_SEPS_ ",;"

//����״̬ö��
enum ConnectionStatus
{
	E_uninit,		//δ��ʼ��
	E_inited,		//�Ѿ���ʼ��
	E_unconnected,	//�����Ѿ��Ͽ�
	E_connecting,	//������
	E_connected,	//���ӳɹ�
	E_authing,		//��Ȩ��
	E_authed,		//��Ȩ�ɹ�
	E_logining,		//��¼��
	E_logined,		//��¼�ɹ�
	E_confirming,	//���㵥ȷ����
	E_confirmed,	//�Ѿ�ȷ��
	E_conn_max		//���ֵ
};

//�ص��������Ͷ��壨Ϊ��д���㣬����ĸ����
typedef void (__stdcall *fnOnConnect)(void* pApi,DFITCUserLoginInfoRtnField *pRspUserLogin,ConnectionStatus result);//���Ӻ�Ľ��״̬
typedef void (__stdcall *fnOnDisconnect)(void* pApi,DFITCErrorRtnField *pRspInfo,ConnectionStatus step);//����ʱ������״̬
typedef void (__stdcall *fnOnMarketData)(void* pMdUserApi,DFITCDepthMarketDataField *pMarketDataField);
typedef void (__stdcall *fnOnRspArbitrageInstrument)(void* pTraderApi,DFITCAbiInstrumentRtnField * pAbiInstrumentData, DFITCErrorRtnField * pErrorInfo, bool bIsLast);

typedef void (__stdcall *fnOnRspInsertCancelOrder)(void* pTraderApi,DFITCOrderRspDataRtnField *pOrderRtn,DFITCErrorRtnField *pErrorInfo);

typedef void (__stdcall *fnOnRspCustomerCapital)(void* pTraderApi,DFITCCapitalInfoRtnField *pCapitalInfoRtn,DFITCErrorRtnField *pErrorInfo, bool bIsLast);
typedef void (__stdcall *fnOnRspError)(void* pApi,DFITCErrorRtnField *pRspInfo);
typedef void (__stdcall *fnOnRspQryExchangeInstrument)(void* pTraderApi,DFITCExchangeInstrumentRtnField * pInstrumentData,DFITCErrorRtnField * pErrorInfo, bool bIsLast);
typedef void (__stdcall *fnOnRspQryMatchInfo)(void* pTraderApi,DFITCMatchedRtnField * pRtnMatchData,DFITCErrorRtnField * pErrorInfo, bool bIsLast);
typedef void (__stdcall *fnOnRspQryOrderInfo)(void* pTraderApi,DFITCOrderCommRtnField * pRtnOrderData,DFITCErrorRtnField * pErrorInfo, bool bIsLast);
typedef void (__stdcall *fnOnRspQryPosition)(void* pTraderApi,DFITCPositionInfoRtnField * pPositionInfoRtn,DFITCErrorRtnField * pErrorInfo, bool bIsLast);
typedef void (__stdcall *fnOnRspQryPositionDetail)(void* pTraderApi,DFITCPositionDetailRtnField * pPositionDetailRtn,DFITCErrorRtnField * pErrorInfo, bool bIsLast);
typedef void (__stdcall *fnOnRspQrySpecifyInstrument)(void* pTraderApi,DFITCInstrumentRtnField * pInstrument,DFITCErrorRtnField * pErrorInfo, bool bIsLast);
typedef void (__stdcall *fnOnRtnCancelOrder)(void* pTraderApi, DFITCOrderCanceledRtnField * pCancelOrderData);
typedef void (__stdcall *fnOnRtnExchangeStatus)(void* pTraderApi, DFITCExchangeStatusRtnField * pRtnExchangeStatusData);
typedef void (__stdcall *fnOnRtnMatchedInfo)(void* pTraderApi,DFITCMatchRtnField * pRtnMatchData);
typedef void (__stdcall *fnOnRtnOrder)(void* pTraderApi,DFITCOrderRtnField * pRtnOrderData);
// ������ѯ����Ӧ��
typedef void (__stdcall *fnOnRspQuoteSubscribe)(void* pTraderApi,DFITCQuoteSubscribeRspField * pRspQuoteSubscribeData);
typedef void (__stdcall *fnOnRtnQuoteSubscribe)(void* pTraderApi,DFITCQuoteSubscribeRtnField * pRtnQuoteSubscribeData);
typedef void (__stdcall *fnOnRspQuoteInsertCancel)(void* pTraderApi,DFITCQuoteRspField * pRspQuoteData,DFITCErrorRtnField * pErrorInfo);
typedef void (__stdcall *fnOnRtnQuote)(void* pTraderApi,DFITCQuoteRtnField * pRtnQuoteData);
typedef void (__stdcall *fnOnRtnQuoteCancel)(void* pTraderApi,DFITCQuoteCanceledRtnField * pRtnQuoteCanceledData);

//����������Ϣ���У�֧����Ӧ����ͽ���
QUANTBOXC2XSPEED_API void* __stdcall XSpeed_CreateMsgQueue();

//����Ϣ����ע��ص�����
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnConnect(void* pMsgQueue,fnOnConnect pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnDisconnect(void* pMsgQueue,fnOnDisconnect pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspError(void* pMsgQueue,fnOnRspError pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspCancelOrder(void* pMsgQueue,fnOnRspInsertCancelOrder pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspInsertOrder(void* pMsgQueue,fnOnRspInsertCancelOrder pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspQryExchangeInstrument(void* pMsgQueue,fnOnRspQryExchangeInstrument pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspArbitrageInstrument(void* pMsgQueue,fnOnRspArbitrageInstrument pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspQrySpecifyInstrument(void* pMsgQueue,fnOnRspQrySpecifyInstrument pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspQryPosition(void* pMsgQueue,fnOnRspQryPosition pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspQryPositionDetail(void* pMsgQueue,fnOnRspQryPositionDetail pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspQryOrderInfo(void* pMsgQueue,fnOnRspQryOrderInfo pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspQryMatchInfo(void* pMsgQueue,fnOnRspQryMatchInfo pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspCustomerCapital(void* pMsgQueue,fnOnRspCustomerCapital pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnMarketData(void* pMsgQueue,fnOnMarketData pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRtnCancelOrder(void* pMsgQueue,fnOnRtnCancelOrder pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRtnExchangeStatus(void* pMsgQueue, fnOnRtnExchangeStatus pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRtnOrder(void* pMsgQueue,fnOnRtnOrder pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRtnMatchedInfo(void* pMsgQueue,fnOnRtnMatchedInfo pCallback);
// ������
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspQuoteSubscribe(void* pMsgQueue,fnOnRspQuoteSubscribe pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRtnQuoteSubscribe(void* pMsgQueue,fnOnRtnQuoteSubscribe pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspQuoteInsert(void* pMsgQueue,fnOnRspQuoteInsertCancel pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspQuoteCancel(void* pMsgQueue,fnOnRspQuoteInsertCancel pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRtnQuoteCancel(void* pMsgQueue,fnOnRtnQuoteCancel pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRtnQuote(void* pMsgQueue,fnOnRtnQuote pCallback);

//�ͷ���Ϣ����
QUANTBOXC2XSPEED_API void __stdcall XSpeed_ReleaseMsgQueue(void* pMsgQueue);
//�����Ϣ��������
QUANTBOXC2XSPEED_API void __stdcall XSpeed_ClearMsgQueue(void* pMsgQueue);

//������Ϣ���е�һ����¼
QUANTBOXC2XSPEED_API bool __stdcall XSpeed_ProcessMsgQueue(void* pMsgQueue);
//�������лص����������߳�
QUANTBOXC2XSPEED_API void __stdcall XSpeed_StartMsgQueue(void* pMsgQueue);
//ֹͣ���лص����������߳�
QUANTBOXC2XSPEED_API void __stdcall XSpeed_StopMsgQueue(void* pMsgQueue);

//����ӿ�=======================================

//��������ӿ�
QUANTBOXC2XSPEED_API void* __stdcall MD_CreateMdApi();
//����Ϣ����ע�ᵽ����ӿ���
QUANTBOXC2XSPEED_API void __stdcall MD_RegMsgQueue2MdApi(void* pMdUserApi,void* pMsgQueue);
//����
QUANTBOXC2XSPEED_API void __stdcall MD_Connect(
	void* pMdUserApi,
	const char* szSvrAddr,
	const char* szAccountID,
	const char* szPassword,
	short sCompanyID);

//���ĺ�Լ�������Լ�ԡ�,���ָ�
QUANTBOXC2XSPEED_API void __stdcall MD_Subscribe(void* pMdUserApi,const char* szInstrumentIDs);
//ȡ�����ģ������Լ�ԡ�,���ָ�
QUANTBOXC2XSPEED_API void __stdcall MD_Unsubscribe(void* pMdUserApi,const char* szInstrumentIDs);
//�Ͽ�����
QUANTBOXC2XSPEED_API void __stdcall MD_Disconnect(void* pMdUserApi);
//�ͷ�����ӿ�
QUANTBOXC2XSPEED_API void __stdcall MD_ReleaseMdApi(void* pMdUserApi);

//���׽ӿ�=======================================
QUANTBOXC2XSPEED_API void* __stdcall TD_CreateTdApi();
//����Ϣ����ע�ᵽ���׽ӿ���
QUANTBOXC2XSPEED_API void __stdcall TD_RegMsgQueue2TdApi(void* pTraderApi,void* pMsgQueue);
//����
QUANTBOXC2XSPEED_API void __stdcall TD_Connect(
	void* pTraderApi,
	const char* szSvrAddr,
	const char* szAccountID,
	const char* szPassword,
	short sCompanyID);

//����
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
	DFITCInstrumentTypeType nInstrumentType,
	DFITCInsertType insertType);

//����
QUANTBOXC2XSPEED_API void __stdcall TD_CancelOrder(
	void* pTraderApi,
	const char* szInstrumentId,
	DFITCLocalOrderIDType localOrderID,
	DFITCSPDOrderIDType spdOrderID
	);

//����
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
	DFITCInstrumentTypeType nInstrumentType);

//����
QUANTBOXC2XSPEED_API void __stdcall TD_CancelQuoteOrder(
	void* pTraderApi,
	const char* szInstrumentId,
	DFITCLocalOrderIDType localOrderID,
	DFITCSPDOrderIDType spdOrderID
	);

//�Ͽ�����
QUANTBOXC2XSPEED_API void __stdcall TD_Disconnect(void* pTraderApi);
//�ͷ�����ӿ�
QUANTBOXC2XSPEED_API void __stdcall TD_ReleaseTdApi(void* pTraderApi);
//���ۺϳֲ�
QUANTBOXC2XSPEED_API void __stdcall TD_ReqQryPosition(void* pTraderApi,const char* szInstrumentId);
//��ֲ���ϸ
QUANTBOXC2XSPEED_API void __stdcall TD_ReqQryPositionDetail(void* pTraderApi,const char* szInstrumentId);
//���ʽ��˺�
QUANTBOXC2XSPEED_API void __stdcall TD_ReqQryCustomerCapital(void* pTraderApi);
//���Լ
QUANTBOXC2XSPEED_API void __stdcall TD_ReqQryExchangeInstrument(void* pTraderApi,const char* szExchangeId,DFITCInstrumentTypeType instrumentType);
QUANTBOXC2XSPEED_API void __stdcall TD_ReqQryArbitrageInstrument(void* pTraderApi,const char* szExchangeId);
QUANTBOXC2XSPEED_API void __stdcall TD_ReqQrySpecifyInstrument(void* pTraderApi,const char* szInstrumentId,const char* szExchangeId,DFITCInstrumentTypeType instrumentType);

QUANTBOXC2XSPEED_API void __stdcall TD_ReqQryMatchInfo(void* pTraderApi,DFITCInstrumentTypeType instrumentType);
QUANTBOXC2XSPEED_API void __stdcall TD_ReqQryOrderInfo(void* pTraderApi,DFITCInstrumentTypeType instrumentType);

// ������
QUANTBOXC2XSPEED_API void __stdcall TD_ReqQuoteSubscribe(void* pTraderApi);

void WriteLog(const char *fmt, ...);
#ifdef __cplusplus
}
#endif


#endif//end of _QUANTBOXC2XSPEED_H_