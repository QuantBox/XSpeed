using System;
using System.Runtime.InteropServices;

namespace QuantBox.CSharp2XSpeed
{
    public class MdApi
    {
        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_RegOnMarketData")]
        public static extern void XSpeed_RegOnMarketData(IntPtr pMsgQueue, fnOnMarketData pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "MD_CreateMdApi")]
        public static extern IntPtr MD_CreateMdApi();

        [DllImport(CommApi.DllFileName, EntryPoint = "MD_RegMsgQueue2MdApi")]
        public static extern void MD_RegMsgQueue2MdApi(IntPtr pMdApi, IntPtr pMsgQueue);

        [DllImport(CommApi.DllFileName, EntryPoint = "MD_Connect")]
        public static extern void MD_Connect(IntPtr pMdApi, string szSvrAddr, string szAccountID, string szPassword, short sCompanyID);

        [DllImport(CommApi.DllFileName, EntryPoint = "MD_Subscribe")]
        public static extern void MD_Subscribe(IntPtr pMdApi, string inst);

        [DllImport(CommApi.DllFileName, EntryPoint = "MD_Unsubscribe")]
        public static extern void MD_Unsubscribe(IntPtr pMdApi, string inst);

        [DllImport(CommApi.DllFileName, EntryPoint = "MD_ReleaseMdApi")]
        public static extern void MD_ReleaseMdApi(IntPtr pMdApi);
    }
}
