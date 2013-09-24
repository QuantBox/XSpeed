using System;
using System.Runtime.InteropServices;

namespace QuantBox.CSharp2XSpeed
{
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void fnOnConnect(IntPtr pApi, ref DFITCUserLoginInfoRtnField pRspUserLogin, ConnectionStatus result);//连接后的结果状态
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void fnOnDisconnect(IntPtr pApi, ref DFITCErrorRtnField pRspInfo, ConnectionStatus step);//出错时所处的状态
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void fnOnMarketData(IntPtr pMdUserApi, ref DFITCDepthMarketDataField pMarketDataField);
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void fnOnRspArbitrageInstrument(IntPtr pTraderApi, ref DFITCAbiInstrumentRtnField pAbiInstrumentData, ref DFITCErrorRtnField pErrorInfo, bool bIsLast);
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void fnOnRspInsertCancelOrder(IntPtr pTraderApi, ref DFITCOrderRspDataRtnField pOrderRtn, ref DFITCErrorRtnField pErrorInfo);
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void fnOnRspCustomerCapital(IntPtr pTraderApi, ref DFITCCapitalInfoRtnField pCapitalInfoRtn, ref DFITCErrorRtnField pErrorInfo, bool bIsLast);
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void fnOnRspError(IntPtr pApi, ref DFITCErrorRtnField pRspInfo);
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void fnOnRspQryExchangeInstrument(IntPtr pTraderApi, ref DFITCExchangeInstrumentRtnField pInstrumentData, ref DFITCErrorRtnField pErrorInfo, bool bIsLast);
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void fnOnRspQryMatchInfo(IntPtr pTraderApi, ref DFITCMatchedRtnField pRtnMatchData, ref DFITCErrorRtnField pErrorInfo, bool bIsLast);
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void fnOnRspQryOrderInfo(IntPtr pTraderApi, ref DFITCOrderCommRtnField pRtnOrderData, ref DFITCErrorRtnField pErrorInfo, bool bIsLast);
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void fnOnRspQryPosition(IntPtr pTraderApi, ref DFITCPositionInfoRtnField pPositionInfoRtn, ref DFITCErrorRtnField pErrorInfo, bool bIsLast);
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void fnOnRspQryPositionDetail(IntPtr pTraderApi, ref DFITCPositionDetailRtnField pPositionDetailRtn, ref DFITCErrorRtnField pErrorInfo, bool bIsLast);
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void fnOnRspQrySpecifyInstrument(IntPtr pTraderApi, ref DFITCInstrumentRtnField pInstrument, ref DFITCErrorRtnField pErrorInfo, bool bIsLast);
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void fnOnRtnCancelOrder(IntPtr pTraderApi, ref DFITCOrderCanceledRtnField pCancelOrderData);
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void fnOnRtnInstrumentStatus(IntPtr pTraderApi, ref DFITCInstrumentStatusField pInstrumentStatus);
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void fnOnRtnMatchedInfo(IntPtr pTraderApi, ref DFITCMatchRtnField pRtnMatchData);
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void fnOnRtnOrder(IntPtr pTraderApi, ref DFITCOrderRtnField pRtnOrderData);
}
