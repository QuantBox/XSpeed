using System;
using System.ComponentModel;

namespace QuantBox.CSharp2XSpeed
{
    /// <summary>
    /// DFITCExecStateType：执行状态数据类型
    /// </summary>
    public enum DFITCExecStateType : int
    {
        /// <summary>
        /// 成功
        /// </summary>
        SUCCESS = 0,
        /// <summary>
        /// 失败
        /// </summary>
        FAIL = 1,
    }

    /// <summary>
    /// DFITCBuySellTypeType:买卖数据类型
    /// </summary>
    public enum DFITCBuySellTypeType:short
    {
        /// <summary>
        /// 双边，做市商操作特有字段
        /// </summary>
        ALL = 0,
        /// <summary>
        /// 买
        /// </summary>
        BUY = 1,
        /// <summary>
        /// 买
        /// </summary>
        SELL = 2,
    }

    /// <summary>
    /// DFITCOpenCloseTypeType：开平标志数据类型
    /// </summary>
    public enum DFITCOpenCloseTypeType : int
    {
        /// <summary>
        /// 开仓
        /// </summary>
        OPEN = 1,
        /// <summary>
        /// 平仓
        /// </summary>
        CLOSE = 2,
        /// <summary>
        /// 平今
        /// </summary>
        CLOSETODAY = 4,
        /// <summary>
        /// 期权执行
        /// </summary>
        EXECUTE = 6,
        /// <summary>
        /// 询价
        /// </summary>
        QUOTE = 9,
    }

    /// <summary>
    /// DFITCExchangeIDType:交易所编码数据类型
    /// </summary>
    public class DFITCExchangeIDType
    {
        /// <summary>
        /// 大商所
        /// </summary>
        public const string DCE = "DCE";
        /// <summary>
        /// 郑商所
        /// </summary>
        public const string CZCE = "CZCE";
        /// <summary>
        /// 上期所
        /// </summary>
        public const string SHFE = "SHFE";
        /// <summary>
        /// 中金所
        /// </summary>
        public const string CFFEX = "CFFEX";
    }

    /// <summary>
    /// DFITCOrderType:报单类型
    /// </summary>
    public enum DFITCOrderTypeType : int
    {
        /// <summary>
        /// 限价委托
        /// </summary>
        LIMITORDER = 1,
        /// <summary>
        /// 市价委托
        /// </summary>
        MKORDER = 2,
        /// <summary>
        /// 套利委托
        /// </summary>
        ARBITRAGE = 4,
    }

    /// <summary>
    /// DFITCOrderAnswerStatusType:委托回报类型
    /// </summary>
    public enum DFITCOrderAnswerStatusType : short
    {
        /// <summary>
        /// 全部撤单
        /// </summary>
        CANCELED = 1,
        /// <summary>
        /// 全部成交
        /// </summary>
        FILLED = 2,
        /// <summary>
        /// 未成交还在队列中
        /// </summary>
        IN_QUEUE = 3,
        /// <summary>
        /// 部分成交还在队列中
        /// </summary>
        PARTIAL = 4,
        /// <summary>
        /// 撤单中
        /// </summary>
        PAPRIAL_CANCELED = 5,
        /// <summary>
        /// 未成交还在队列中
        /// </summary>
        IN_CANCELING = 6,
        /// <summary>
        /// 错误(废单错误)
        /// </summary>
        ERROR = 7,
        /// <summary>
        /// 交易所已接受，但尚未成交
        /// </summary>
        PLACED = 8,
        /// <summary>
        /// 报单的初始状态，表示单子刚刚开始，尚未报到柜台。
        /// </summary>
        STARTED = 9,
        /// <summary>
        /// 交易所已接受，但尚未成交
        /// </summary>
        TRIGGERED = 10,
        /// <summary>
        /// 撤单成功
        /// </summary>
        SUCCESS_CANCELED = 11,
        /// <summary>
        /// 成交成功
        /// </summary>
        SUCCESS_FILLED = 12,
    }

    /// <summary>
    /// DFITCMatchType:成交类型数据类型
    /// </summary>
    public enum DFITCMatchType : int
    {
        /// <summary>
        /// 普通成交
        /// </summary>
        BASIC_TRADE = 0,
    }

    /// <summary>
    /// DFITCSpeculatorType:投保类型
    /// </summary>
    public enum DFITCSpeculatorType : int
    {
        /// <summary>
        /// 投机
        /// </summary>
        SPECULATOR = 0,
        /// <summary>
        /// 套保
        /// </summary>
        HEDGE = 1,
        /// <summary>
        /// 套利
        /// </summary>
        ARBITRAGE = 2
    }

    /// <summary>
    /// DFITCAccountLoginResultType:资金账户登录结果
    /// </summary>
    public enum DFITCAccountLoginResultType : int
    {
        /// <summary>
        /// 登录成功
        /// </summary>
        LOGIN_SUCCESS = 0,
        /// <summary>
        /// 登录失败
        /// </summary>
        LOGIN_FAILED = 1,
        /// <summary>
        /// 已退出
        /// </summary>
        LOGIN_QUIT = 2,
        /// <summary>
        /// 未操作
        /// </summary>
        LOGIN_NOT_OPERATE = 9,
    }

    /// <summary>
    /// DFITCQuotationType:接收行情类型
    /// </summary>
    public enum DFITCQuotationType : short
    {
        /// <summary>
        /// TCP行情
        /// </summary>
        TCP = 1,
        /// <summary>
        /// UDP行情
        /// </summary>
        UPD = 2
    }

    /// <summary>
    /// DFITCAbiPolicyCodeType: 套利策略代码数据类型
    /// </summary>
    public class DFITCAbiPolicyCodeType
    {
        /// <summary>
        /// 跨期套利
        /// </summary>
        public const string SP = "SP";
        /// <summary>
        /// 两腿跨品种套利
        /// </summary>
        public const string SPC = "SPC";
        /// <summary>
        /// 压榨套利
        /// </summary>
        public const string SPX = "SPX";
        /// <summary>
        /// Call Spread
        /// </summary>
        public const string CALL = "CSPR";
        /// <summary>
        /// Put Spread
        /// </summary>
        public const string PUT = "PSPR";
        /// <summary>
        /// Combo
        /// </summary>
        public const string COMBO = "COMBO";
        /// <summary>
        /// Straddle
        /// </summary>
        public const string STRADDLE = "STD";
        /// <summary>
        /// Strangle
        /// </summary>
        public const string STRANGLE = "STG";
        /// <summary>
        /// Guts
        /// </summary>
        public const string GUTS = "GUTS";
        /// <summary>
        /// Synthetic Underlying
        /// </summary>
        public const string SYNUND = "SYN";
    }

    /// <summary>
    /// DFITCOrderPropertyType:订单属性
    /// </summary>
    public enum DFITCOrderPropertyType : byte
    {
        NON = (byte)'0',

        FAK = (byte)'1',

        FOK = (byte)'2'
    }

    /// <summary>
    /// DFITCLossProfitTypeType:止盈止损标志
    /// </summary>
    public enum XSpeedLossProfitType : int
    {
        /// <summary>
        /// 止损标志
        /// </summary>
        LOSS_USE = 1,
        /// <summary>
        /// 
        /// </summary>
        LOSS_UNUSE = 0,
        /// <summary>
        /// 止盈标志
        /// </summary>
        PROFIT_USE = 1,
        /// <summary>
        /// 
        /// </summary>
        PROFIT_UNUSE = 0
    }

    /// <summary>
    /// DFITCInsertType:委托类别
    /// </summary>
    public enum DFITCInsertType : int
    {
        /// <summary>
        /// 普通委托单
        /// </summary>
        BASIC_ORDER = 1,
        /// <summary>
        /// 自动单
        /// </summary>
        AUTO_ORDER = 2,
    }

    /// <summary>
    /// DFITCOptionTypeType:期权类别数据类型
    /// </summary>
    public enum DFITCOptionTypeType : int
    {
        /// <summary>
        /// 看涨
        /// </summary>
        LOOK_UP = 1,
        /// <summary>
        /// 看跌
        /// </summary>
        LOOK_DOWN = 2,
    }

    /// <summary>
    /// DFITCInstrumentTypeType:合约类型数据类型
    /// </summary>
    public enum DFITCInstrumentTypeType : int
    {
        /// <summary>
        /// 期货
        /// </summary>
        COMM_TYPE = 0,
        /// <summary>
        /// 期权
        /// </summary>
        OPT_TYPE = 1,
    }

    /// <summary>
    /// DFITCCancelTypeType:撤销标志数据类型
    /// </summary>
    public enum DFITCCancelTypeType : byte
    {
        /// <summary>
        /// 代表订单
        /// </summary>
        BOOK = (byte)'O',
        /// <summary>
        /// 代表撤销
        /// </summary>
        CANCEL = (byte)'W'
    }

    /// <summary>
    /// DFITCNoticeType:消息数据类型
    /// </summary>
    public enum DFITCNoticeType : short
    {
        /// <summary>
        /// 表示系统广播
        /// </summary>
        SYS_BROADCAST_MSG = 1,
        /// <summary>
        /// 表示指定客户
        /// </summary>
        ACCOUNT_ID_MSG = 2
    }

    /// <summary>
    /// DFITCSubscribeFlagType:订阅状态
    /// </summary>
    public enum DFITCSubscribeFlagType : short
    {
        /// <summary>
        /// 订阅成功
        /// </summary>
        QUOTE_SUB_SUCCESS = 0,
        /// <summary>
        /// 订阅失败
        /// </summary>
        QUOTE_SUB_FAILED = 1
    }

    /// <summary>
    /// DFITCSourceType:来源
    /// </summary>
    public enum DFITCSourceType : short
    {
        /// <summary>
        /// 会员
        /// </summary>
        SOURCE_MEMBER = 0,
        /// <summary>
        /// 交易所
        /// </summary>
        SOURCE_EXCHANGE = 1
    }
}
