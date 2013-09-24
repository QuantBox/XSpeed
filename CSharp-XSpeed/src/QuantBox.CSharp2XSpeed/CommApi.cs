using System;
using System.Runtime.InteropServices;

namespace QuantBox.CSharp2XSpeed
{
    public class CommApi
    {
        public const string DllFileName = "QuantBox.C2XSpeed.dll";

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_RegOnConnect")]
        public static extern void XSpeed_RegOnConnect(IntPtr pMsgQueue, fnOnConnect pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_RegOnDisconnect")]
        public static extern void XSpeed_RegOnDisconnect(IntPtr pMsgQueue, fnOnDisconnect pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_RegOnRspError")]
        public static extern void XSpeed_RegOnRspError(IntPtr pMsgQueue, fnOnRspError pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_CreateMsgQueue")]
        public static extern IntPtr XSpeed_CreateMsgQueue();

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_ProcessMsgQueue")]
        public static extern bool XSpeed_ProcessMsgQueue(IntPtr pMsgQueue);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_ReleaseMsgQueue")]
        public static extern void XSpeed_ReleaseMsgQueue(IntPtr pMsgQueue);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_ClearMsgQueue")]
        public static extern void XSpeed_ClearMsgQueue(IntPtr pMsgQueue);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_StartMsgQueue")]
        public static extern void XSpeed_StartMsgQueue(IntPtr pMsgQueue);

        [DllImport(CommApi.DllFileName, EntryPoint = "XSpeed_StopMsgQueue")]
        public static extern void XSpeed_StopMsgQueue(IntPtr pMsgQueue);
    }
}
