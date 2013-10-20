using System;
using System.Runtime.InteropServices;

namespace QuantBox.CSharp2XSpeed
{
    public class TraderApi
    {
        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_RegOnRspArbitrageInstrument")]
        public static extern void XSpeed_RegOnRspArbitrageInstrument(IntPtr pMsgQueue, fnOnRspArbitrageInstrument pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_RegOnRspCancelOrder")]
        public static extern void XSpeed_RegOnRspCancelOrder(IntPtr pMsgQueue, fnOnRspInsertCancelOrder pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_RegOnRspCustomerCapital")]
        public static extern void XSpeed_RegOnRspCustomerCapital(IntPtr pMsgQueue, fnOnRspCustomerCapital pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_RegOnRspInsertOrder")]
        public static extern void XSpeed_RegOnRspInsertOrder(IntPtr pMsgQueue, fnOnRspInsertCancelOrder pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_RegOnRspQryExchangeInstrument")]
        public static extern void XSpeed_RegOnRspQryExchangeInstrument(IntPtr pMsgQueue, fnOnRspQryExchangeInstrument pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_RegOnRspQryMatchInfo")]
        public static extern void XSpeed_RegOnRspQryMatchInfo(IntPtr pMsgQueue, fnOnRspQryMatchInfo pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_RegOnRspQryOrderInfo")]
        public static extern void XSpeed_RegOnRspQryOrderInfo(IntPtr pMsgQueue, fnOnRspQryOrderInfo pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_RegOnRspQryPosition")]
        public static extern void XSpeed_RegOnRspQryPosition(IntPtr pMsgQueue, fnOnRspQryPosition pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_RegOnRspQryPositionDetail")]
        public static extern void XSpeed_RegOnRspQryPositionDetail(IntPtr pMsgQueue, fnOnRspQryPositionDetail pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_RegOnRspQrySpecifyInstrument")]
        public static extern void XSpeed_RegOnRspQrySpecifyInstrument(IntPtr pMsgQueue, fnOnRspQrySpecifyInstrument pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_RegOnRtnCancelOrder")]
        public static extern void XSpeed_RegOnRtnCancelOrder(IntPtr pMsgQueue, fnOnRtnCancelOrder pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_RegOnRtnInstrumentStatus")]
        public static extern void XSpeed_RegOnRtnInstrumentStatus(IntPtr pMsgQueue, fnOnRtnInstrumentStatus pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_RegOnRtnMatchedInfo")]
        public static extern void XSpeed_RegOnRtnMatchedInfo(IntPtr pMsgQueue, fnOnRtnMatchedInfo pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_RegOnRtnOrder")]
        public static extern void XSpeed_RegOnRtnOrder(IntPtr pMsgQueue, fnOnRtnOrder pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_RegOnRspQuoteSubscribe")]
        public static extern void XSpeed_RegOnRspQuoteSubscribe(IntPtr pMsgQueue, fnOnRspQuoteSubscribe pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_RegOnRtnQuoteSubscribe")]
        public static extern void XSpeed_RegOnRtnQuoteSubscribe(IntPtr pMsgQueue, fnOnRtnQuoteSubscribe pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_RegOnRspQuoteInsertOrder")]
        public static extern void XSpeed_RegOnRspQuoteInsertOrder(IntPtr pMsgQueue, fnOnRspQuoteInsertCancelOrder pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_RegOnRspQuoteCancelOrder")]
        public static extern void XSpeed_RegOnRspQuoteCancelOrder(IntPtr pMsgQueue, fnOnRspQuoteInsertCancelOrder pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_RegOnRtnQuoteCancelOrder")]
        public static extern void XSpeed_RegOnRtnQuoteCancelOrder(IntPtr pMsgQueue, fnOnRtnQuoteCancelOrder pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_RegOnRtnQuoteOrder")]
        public static extern void XSpeed_RegOnRtnQuoteOrder(IntPtr pMsgQueue, fnOnRtnQuoteOrder pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_CreateTdApi")]
        public static extern IntPtr TD_CreateTdApi();

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_RegMsgQueue2TdApi")]
        public static extern void TD_RegMsgQueue2TdApi(IntPtr pTraderApi, IntPtr pMsgQueue);

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_Connect")]
        public static extern void TD_Connect(
            IntPtr pTraderApi,
            string szSvrAddr,
            string szAccountID,
            string szPassword,
            short sCompanyID);

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_SendOrder")]
        public static extern int TD_SendOrder(
            IntPtr pTraderApi,
            int localOrderID,
            string szInstrument,
            DFITCBuySellTypeType sBuySellType,
            DFITCOpenCloseTypeType sOpenCloseType,
            DFITCSpeculatorType sSpeculator,
            int lAmount,
            double dbPrice,
            DFITCOrderTypeType orderType,
            DFITCOrderPropertyType orderProperty,
            DFITCInstrumentTypeType nInstrumentType);

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_SendQuoteOrder")]
        public static extern int TD_SendQuoteOrder(
            IntPtr pTraderApi,
            int localOrderID,
            string szInstrument,
            string quoteID,
            int bOrderAmount,
            int sOrderAmount,
            double bInsertPrice,
            double sInsertPrice,
            DFITCOpenCloseTypeType bOpenCloseType,
            DFITCOpenCloseTypeType sOpenCloseType,
            DFITCSpeculatorType bSpeculator,
            DFITCSpeculatorType sSpeculator,
            int stayTime,
            DFITCInstrumentTypeType nInstrumentType);

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_CancelOrder")]
        public static extern void TD_CancelOrder(
            IntPtr pTraderApi,
            string szInstrument,
            int localOrderID,
            int spdOrderID);

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_CancelQuoteOrder")]
        public static extern void TD_CancelQuoteOrder(
            IntPtr pTraderApi,
            string szInstrument,
            int localOrderID,
            int spdOrderID);

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_ReleaseTdApi")]
        public static extern void TD_ReleaseTdApi(IntPtr pTraderApi);

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_ReqQryPosition")]
        public static extern void TD_ReqQryPosition(IntPtr pTraderApi, string szInstrument);

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_ReqQryPositionDetail")]
        public static extern void TD_ReqQryPositionDetail(IntPtr pTraderApi, string szInstrument);

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_ReqQryCustomerCapital")]
        public static extern void TD_ReqQryCustomerCapital(IntPtr pTraderApi);

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_ReqQryExchangeInstrument")]
        public static extern void TD_ReqQryExchangeInstrument(IntPtr pTraderApi, string szExchangeId, DFITCInstrumentTypeType instrumentType);

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_ReqQryArbitrageInstrument")]
        public static extern void TD_ReqQryArbitrageInstrument(IntPtr pTraderApi, string szExchangeId);

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_ReqQrySpecifyInstrument")]
        public static extern void TD_ReqQrySpecifyInstrument(IntPtr pTraderApi, string szInstrument, string szExchangeId, DFITCInstrumentTypeType instrumentType);

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_ReqQryMatchInfo")]
        public static extern void TD_ReqQryMatchInfo(IntPtr pTraderApi, DFITCInstrumentTypeType instrumentType);

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_ReqQryOrderInfo")]
        public static extern void TD_ReqQryOrderInfo(IntPtr pTraderApi, DFITCInstrumentTypeType instrumentType);

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_ReqQuoteSubscribe")]
        public static extern void TD_ReqQuoteSubscribe(IntPtr pTraderApi);
    }
}
