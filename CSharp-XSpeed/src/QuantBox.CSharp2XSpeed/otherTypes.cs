
namespace QuantBox.CSharp2XSpeed
{
    //自己定义的
    public enum ConnectionStatus
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
        E_confirming,	//确认中
        E_confirmed,	//已经确认
        E_conn_max		//最大值
    };
}
