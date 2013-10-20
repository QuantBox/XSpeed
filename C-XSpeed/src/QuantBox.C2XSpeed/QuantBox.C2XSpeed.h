// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 QUANTBOXC2XSPEED_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// QUANTBOXC2XSPEED_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
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

//用于分隔输入的合列表，与前置机地址列表，所以不能出现“:”一类的
#define _QUANTBOXC2XSPEED_SEPS_ ",;"

//连接状态枚举
enum ConnectionStatus
{
	E_uninit,		//未初始化
	E_inited,		//已经初始化
	E_unconnected,	//连接已经断开
	E_connecting,	//连接中
	E_connected,	//连接成功
	E_authing,		//授权中
	E_authed,		//授权成功
	E_logining,		//登录中
	E_logined,		//登录成功
	E_confirming,	//结算单确认中
	E_confirmed,	//已经确认
	E_conn_max		//最大值
};

//回调函数类型定义（为编写方便，按字母排序）
typedef void (__stdcall *fnOnConnect)(void* pApi,DFITCUserLoginInfoRtnField *pRspUserLogin,ConnectionStatus result);//连接后的结果状态
typedef void (__stdcall *fnOnDisconnect)(void* pApi,DFITCErrorRtnField *pRspInfo,ConnectionStatus step);//出错时所处的状态
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
typedef void (__stdcall *fnOnRtnInstrumentStatus)(void* pTraderApi,DFITCInstrumentStatusField *pInstrumentStatus);
typedef void (__stdcall *fnOnRtnMatchedInfo)(void* pTraderApi,DFITCMatchRtnField * pRtnMatchData);
typedef void (__stdcall *fnOnRtnOrder)(void* pTraderApi,DFITCOrderRtnField * pRtnOrderData);
// 做市商询价与应价
typedef void (__stdcall *fnOnRspQuoteSubscribe)(void* pTraderApi,DFITCQuoteSubscribeRspField * pRspQuoteSubscribeData);
typedef void (__stdcall *fnOnRtnQuoteSubscribe)(void* pTraderApi,DFITCQuoteSubscribeRtnField * pRtnQuoteSubscribeData);
typedef void (__stdcall *fnOnRspQuoteInsertCancelOrder)(void* pTraderApi,DFITCQuoteOrderRspField * pRspQuoteOrderData,DFITCErrorRtnField * pErrorInfo);
typedef void (__stdcall *fnOnRtnQuoteOrder)(void* pTraderApi,DFITCQuoteOrderRtnField * pRtnQuoteOrderData);
typedef void (__stdcall *fnOnRtnQuoteCancelOrder)(void* pTraderApi,DFITCQuoteCanceledRtnField * pRtnQuoteCanceledData);

//创建接收消息队列，支持响应行情和交易
QUANTBOXC2XSPEED_API void* __stdcall XSpeed_CreateMsgQueue();

//向消息队列注册回调函数
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
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRtnInstrumentStatus(void* pMsgQueue,fnOnRtnInstrumentStatus pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRtnOrder(void* pMsgQueue,fnOnRtnOrder pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRtnMatchedInfo(void* pMsgQueue,fnOnRtnMatchedInfo pCallback);
// 做市商
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspQuoteSubscribe(void* pMsgQueue,fnOnRspQuoteSubscribe pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRtnQuoteSubscribe(void* pMsgQueue,fnOnRtnQuoteSubscribe pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspQuoteInsertOrder(void* pMsgQueue,fnOnRspQuoteInsertCancelOrder pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRspQuoteCancelOrder(void* pMsgQueue,fnOnRspQuoteInsertCancelOrder pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRtnQuoteCancelOrder(void* pMsgQueue,fnOnRtnQuoteCancelOrder pCallback);
QUANTBOXC2XSPEED_API void __stdcall XSpeed_RegOnRtnQuoteOrder(void* pMsgQueue,fnOnRtnQuoteOrder pCallback);

//释放消息队列
QUANTBOXC2XSPEED_API void __stdcall XSpeed_ReleaseMsgQueue(void* pMsgQueue);
//清空消息队列内容
QUANTBOXC2XSPEED_API void __stdcall XSpeed_ClearMsgQueue(void* pMsgQueue);

//处理消息队列第一条记录
QUANTBOXC2XSPEED_API bool __stdcall XSpeed_ProcessMsgQueue(void* pMsgQueue);
//开启队列回调主动推送线程
QUANTBOXC2XSPEED_API void __stdcall XSpeed_StartMsgQueue(void* pMsgQueue);
//停止队列回调主动推送线程
QUANTBOXC2XSPEED_API void __stdcall XSpeed_StopMsgQueue(void* pMsgQueue);

//行情接口=======================================

//创建行情接口
QUANTBOXC2XSPEED_API void* __stdcall MD_CreateMdApi();
//将消息队列注册到行情接口上
QUANTBOXC2XSPEED_API void __stdcall MD_RegMsgQueue2MdApi(void* pMdUserApi,void* pMsgQueue);
//连接
QUANTBOXC2XSPEED_API void __stdcall MD_Connect(
	void* pMdUserApi,
	const char* szSvrAddr,
	const char* szAccountID,
	const char* szPassword,
	short sCompanyID);

//订阅合约，多个合约以“,”分隔
QUANTBOXC2XSPEED_API void __stdcall MD_Subscribe(void* pMdUserApi,const char* szInstrumentIDs);
//取消订阅，多个合约以“,”分隔
QUANTBOXC2XSPEED_API void __stdcall MD_Unsubscribe(void* pMdUserApi,const char* szInstrumentIDs);
//断开连接
QUANTBOXC2XSPEED_API void __stdcall MD_Disconnect(void* pMdUserApi);
//释放行情接口
QUANTBOXC2XSPEED_API void __stdcall MD_ReleaseMdApi(void* pMdUserApi);

//交易接口=======================================
QUANTBOXC2XSPEED_API void* __stdcall TD_CreateTdApi();
//将消息队列注册到交易接口上
QUANTBOXC2XSPEED_API void __stdcall TD_RegMsgQueue2TdApi(void* pTraderApi,void* pMsgQueue);
//连接
QUANTBOXC2XSPEED_API void __stdcall TD_Connect(
	void* pTraderApi,
	const char* szSvrAddr,
	const char* szAccountID,
	const char* szPassword,
	short sCompanyID);

//报单
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
	DFITCInstrumentTypeType nInstrumentType);

//撤单
QUANTBOXC2XSPEED_API void __stdcall TD_CancelOrder(
	void* pTraderApi,
	const char* szInstrumentId,
	DFITCLocalOrderIDType localOrderID,
	DFITCSPDOrderIDType spdOrderID
	);

//报单
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

//撤单
QUANTBOXC2XSPEED_API void __stdcall TD_CancelQuoteOrder(
	void* pTraderApi,
	const char* szInstrumentId,
	DFITCLocalOrderIDType localOrderID,
	DFITCSPDOrderIDType spdOrderID
	);

//断开连接
QUANTBOXC2XSPEED_API void __stdcall TD_Disconnect(void* pTraderApi);
//释放行情接口
QUANTBOXC2XSPEED_API void __stdcall TD_ReleaseTdApi(void* pTraderApi);
//查综合持仓
QUANTBOXC2XSPEED_API void __stdcall TD_ReqQryPosition(void* pTraderApi,const char* szInstrumentId);
//查持仓明细
QUANTBOXC2XSPEED_API void __stdcall TD_ReqQryPositionDetail(void* pTraderApi,const char* szInstrumentId);
//查资金账号
QUANTBOXC2XSPEED_API void __stdcall TD_ReqQryCustomerCapital(void* pTraderApi);
//查合约
QUANTBOXC2XSPEED_API void __stdcall TD_ReqQryExchangeInstrument(void* pTraderApi,const char* szExchangeId,DFITCInstrumentTypeType instrumentType);
QUANTBOXC2XSPEED_API void __stdcall TD_ReqQryArbitrageInstrument(void* pTraderApi,const char* szExchangeId);
QUANTBOXC2XSPEED_API void __stdcall TD_ReqQrySpecifyInstrument(void* pTraderApi,const char* szInstrumentId,const char* szExchangeId,DFITCInstrumentTypeType instrumentType);

QUANTBOXC2XSPEED_API void __stdcall TD_ReqQryMatchInfo(void* pTraderApi,DFITCInstrumentTypeType instrumentType);
QUANTBOXC2XSPEED_API void __stdcall TD_ReqQryOrderInfo(void* pTraderApi,DFITCInstrumentTypeType instrumentType);

// 做市商
QUANTBOXC2XSPEED_API void __stdcall TD_ReqQuoteSubscribe(void* pTraderApi);

void WriteLog(const char *fmt, ...);
#ifdef __cplusplus
}
#endif


#endif//end of _QUANTBOXC2XSPEED_H_