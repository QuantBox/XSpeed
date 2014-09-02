/**
* ��Ȩ����(C)2012-2016, �����ɴ���Ϣ�������޹�˾
* �ļ����ƣ�DFITCApiStruct.h
* �ļ�˵��������ӿ���������ݽӿ�
* ��ǰ�汾��1.0.13
* ���ߣ�XSpeed��Ŀ��
* �������ڣ�2014��5��27��
*/

#ifndef DFITCAPISTRUCT_H_
#define DFITCAPISTRUCT_H_
#ifndef DFITCAPIDATATYPE_H
#include "DFITCApiDataType.h"
#endif

#ifdef WIN32
    #ifdef DFITCAPI_EXPORTS
        #define APISTRUCT __declspec(dllexport)
    #else
        #define APISTRUCT __declspec(dllimport)
    #endif//DFITCAPI_EXPORTS
#else
    #define APISTRUCT
#endif//WIN32

///������
struct APISTRUCT DFITCTimeOutField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
};


///���󱨵���������(��������)
struct APISTRUCT DFITCInsertOrderField
{
    DFITCAccountIDType                  accountID;                    //�ʽ��˻�
    DFITCLocalOrderIDType               localOrderID;                 //����ί�к�, ��APIʹ����ά������ͬһ���Ự�в����ظ�
    DFITCInstrumentIDType               instrumentID;                 //��Լ����, ֧��Ŀǰ����4���ڻ������������к�Լ������������/֣������������Լ
    DFITCPriceType                      insertPrice;                  //�����۸�, ����������Ϊ�м�ʱ�����ֶβ�������
    DFITCAmountType                     orderAmount;                  //��������
    DFITCBuySellTypeType                buySellType;                  //������־
    DFITCOpenCloseTypeType              openCloseType;                //��ƽ��־
    DFITCSpeculatorType                 speculator;                   //Ͷ������, ֧��Ͷ�����������ױ�
    DFITCInsertType                     insertType;                   //ί�����(Ĭ��Ϊ��ͨ����)
    DFITCOrderTypeType                  orderType;                    //��������, ֧���޼� ���мۣ���������Լ��֧���мۣ������޼۽��д���
    DFITCOrderPropertyType              orderProperty;                //������������, ֧��None��FAK��FOK��Ŀǰֻ�д�������Լ֧�ָñ����������� FAK/FOK
    DFITCInstrumentTypeType             instrumentType;               //��Լ����, ��ѡֵ���ڻ�����Ȩ
    DFITCReservedType                   reservedType1;                //Ԥ���ֶ�1
    DFITCReservedType                   reservedType2;                //Ԥ���ֶ�2
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCCustomCategoryType             customCategory;               //�Զ������

    DFITCInsertOrderField();
};


///������������
struct APISTRUCT DFITCCancelOrderField
{
    DFITCAccountIDType                  accountID;                    //�ʽ��˻�ID
    DFITCSPDOrderIDType                 spdOrderID;                   //��̨ί�к�
    DFITCLocalOrderIDType               localOrderID;                 //����ί�к�
    DFITCInstrumentIDType               instrumentID;                 //��Լ����
    DFITCRequestIDType                  lRequestID;                   //����ID

    DFITCCancelOrderField();
};


///ί����Ӧ����
struct APISTRUCT DFITCOrderRspDataRtnField
{
    DFITCLocalOrderIDType               localOrderID;                 //����ί�к�
    DFITCSPDOrderIDType                 spdOrderID;                   //��̨ί�к�
    DFITCOrderAnswerStatusType          orderStatus;                  //ί��״̬
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCPriceType                      fee;                          //������,���ֶν����µ�ʱʹ��
    DFITCPriceType                      margin;                       //���ᱣ֤��,���ֶν����µ�ʱʹ��
    DFITCCustomCategoryType             customCategory;               //�Զ������

    DFITCOrderRspDataRtnField();
};


///��ѯ�ʽ���������
struct APISTRUCT DFITCCapitalField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCAccountIDType                  accountID;                    //�ʽ��˻�ID

    DFITCCapitalField();
};


///��ѯ�ֲ���������
struct APISTRUCT DFITCPositionField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCAccountIDType                  accountID;                    //�ʽ��˻�ID
    DFITCInstrumentIDType               instrumentID;                 //��Լ����
    DFITCInstrumentTypeType             instrumentType;               //��Լ����

    DFITCPositionField();
};


///��������Լ
struct APISTRUCT DFITCExchangeInstrumentField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCAccountIDType                  accountID;                    //�ʽ��˻�ID
    DFITCExchangeIDType                 exchangeID;                   //����������
    DFITCInstrumentTypeType             instrumentType;               //��Լ����

    DFITCExchangeInstrumentField();
};


///�û���¼��������
struct APISTRUCT DFITCUserLoginField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCAccountIDType                  accountID;                    //�ʽ��˻�ID
    DFITCPasswdType                     passwd;                       //����
    DFITCCompanyIDType                  companyID;                    //����ID

    DFITCUserLoginField();
};


///�û��˳�����
struct APISTRUCT DFITCUserLogoutField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCAccountIDType                  accountID;                    //�ʽ��ʺ�ID
    DFITCSessionIDType                  sessionID;                    //�ỰID

    DFITCUserLogoutField();
};


///ί�лر�
struct APISTRUCT DFITCOrderRtnField
{
    DFITCLocalOrderIDType               localOrderID;                 //����ί�к�
    DFITCSPDOrderIDType                 spdOrderID;                   //��̨ί�к�
    DFITCOrderSysIDType                 OrderSysID;                   //�������
    DFITCOrderAnswerStatusType          orderStatus;                  //ί��״̬
    DFITCSessionIDType                  sessionID;                    //�ỰID
    DFITCDateType                       SuspendTime;                  //����ʱ��
    DFITCInstrumentIDType               instrumentID;                 //��Լ����
    DFITCExchangeIDType                 exchangeID;                   //������
    DFITCBuySellTypeType                buySellType;                  //����
    DFITCOpenCloseTypeType              openCloseType;                //��ƽ
    DFITCInstrumentTypeType             instrumentType;               //��Լ����
    DFITCSpeculatorType                 speculator;                   //Ͷ�����
    DFITCPriceType                      insertPrice;                  //ί�м�
    DFITCAccountIDType                  accountID;                    //�ʽ��˺�
    DFITCAmountType                     cancelAmount;                 //��������
    DFITCAmountType                     orderAmount;                  //ί������
    DFITCInsertType                     insertType;                   //ί�����
    DFITCSPDOrderIDType                 extSpdOrderID;                //�㷨�����
    DFITCReservedType                   reservedType2;                //Ԥ���ֶ�2	
    DFITCCustomCategoryType             customCategory;               //�Զ������

    DFITCOrderRtnField();
};


///�ɽ��ر�
struct APISTRUCT DFITCMatchRtnField
{
    DFITCLocalOrderIDType               localOrderID;                 //����ί�к�
    DFITCOrderSysIDType                 OrderSysID;                   //�������(�������������)
    DFITCMatchIDType                    matchID;                      //�ɽ����
    DFITCInstrumentIDType               instrumentID;                 //��Լ����
    DFITCBuySellTypeType                buySellType;                  //����
    DFITCOpenCloseTypeType              openCloseType;                //��ƽ��־
    DFITCPriceType                      matchedPrice;                 //�ɽ��۸�
    DFITCAmountType                     orderAmount;                  //ί������
    DFITCAmountType                     matchedAmount;                //�ɽ�����
    DFITCDateType                       matchedTime;                  //�ɽ�ʱ��
    DFITCPriceType                      insertPrice;                  //����
    DFITCSPDOrderIDType                 spdOrderID;                   //��̨ί�к�
    DFITCMatchType                      matchType;                    //�ɽ�����
    DFITCSpeculatorType                 speculator;                   //Ͷ��
    DFITCExchangeIDType                 exchangeID;                   //������ID
    DFITCFeeType                        fee;                          //������
    DFITCSessionIDType                  sessionID;                    //�Ự��ʶ
    DFITCInstrumentTypeType             instrumentType;               //��Լ����
    DFITCAccountIDType                  accountID;                    //�ʽ��˺�
    DFITCOrderAnswerStatusType          orderStatus;                  //�걨���
    DFITCPriceType                      margin;                       //����Ϊ��֤��,ƽ��Ϊ�ⶳ��֤��
    DFITCPriceType                      frozenCapita;                 //�ɽ��ⶳί�ж�����ʽ�
    DFITCAdjustmentInfoType             adjustmentInfo;               //��ϻ�����ı�֤�������Ϣ,��ʽ:[��Լ����,������־,Ͷ�����,�������;] 
    DFITCCustomCategoryType             customCategory;               //�Զ������
    DFITCPriceType                      turnover;                     //�ɽ����

    DFITCMatchRtnField();
};


///�����ر�
struct APISTRUCT DFITCOrderCanceledRtnField
{
    DFITCLocalOrderIDType               localOrderID;                 //����ί�к�
    DFITCOrderSysIDType                 OrderSysID;                   //�������  
    DFITCInstrumentIDType               instrumentID;                 //��Լ����     
    DFITCPriceType                      insertPrice;                  //�����۸�  
    DFITCBuySellTypeType                buySellType;                  //��������
    DFITCOpenCloseTypeType              openCloseType;                //��ƽ��־
    DFITCAmountType                     cancelAmount;                 //��������
    DFITCSPDOrderIDType                 spdOrderID;                   //��̨ί�к�
    DFITCSpeculatorType                 speculator;                   //Ͷ��
    DFITCExchangeIDType                 exchangeID;                   //������ID
    DFITCDateType                       canceledTime;                 //����ʱ��
    DFITCSessionIDType                  sessionID;                    //�Ự��ʶ
    DFITCOrderAnswerStatusType          orderStatus;                  //�걨���
    DFITCInstrumentTypeType             instrumentType;               //��Լ����
    DFITCAccountIDType                  accountID;                    //�ʽ��˺�
    DFITCAmountType                     orderAmount;                  //ί������   
    DFITCPriceType                      margin;                       //��֤��
    DFITCPriceType                      fee;                          //������

    DFITCOrderCanceledRtnField();
};


///������Ϣ
struct APISTRUCT DFITCErrorRtnField
{
    DFITCRequestIDType                  requestID;                    //����ID
    DFITCSessionIDType                  sessionID;                    //�Ự��ʶ
    DFITCAccountIDType                  accountID;                    //�ʽ��˺�
    DFITCErrorIDType                    nErrorID;                     //����ID
    DFITCSPDOrderIDType                 spdOrderID;                   //��̨ί�к�
    DFITCLocalOrderIDType               localOrderID;                 //����ί�к�
    DFITCErrorMsgInfoType               errorMsg;                     //������Ϣ

    DFITCErrorRtnField();
};


///�����ʽ���Ϣ
struct APISTRUCT DFITCCapitalInfoRtnField
{
    DFITCRequestIDType                  requestID;                    //����ID
    DFITCAccountIDType                  accountID;                    //�ʽ��ʺ�
    DFITCEquityType                     preEquity;                    //����Ȩ��
    DFITCEquityType                     todayEquity;                  //���տͻ�Ȩ��
    DFITCProfitLossType                 closeProfitLoss;              //ƽ��ӯ��
    DFITCProfitLossType                 positionProfitLoss;           //�ֲ�ӯ��
    DFITCProfitLossType                 frozenMargin;                 //�����ʽ�
    DFITCProfitLossType                 margin;                       //�ֱֲ�֤��
    DFITCProfitLossType                 fee;                          //����������
    DFITCProfitLossType                 available;                    //�����ʽ�
    DFITCProfitLossType                 withdraw;                     //��ȡ�ʽ�
    DFITCRiskDegreeType                 riskDegree;                   //���ն�
    DFITCPremiumType                    todayPremiumIncome;           //����Ȩ��������
    DFITCPremiumType                    todayPremiumPay;              //����Ȩ���𸶳�
    DFITCPremiumType                    yesterdayPremium;             //��Ȩ�����ո�
    DFITCMarketValueType                optMarketValue;               //��Ȩ��ֵ
    DFITCProfitLossType                 floatProfitLoss;              //����ӯ��
    DFITCProfitLossType                 totFundOut;                   //�ܳ���
    DFITCProfitLossType                 totFundIn;                    //�����

    DFITCCapitalInfoRtnField();
};


///���سֲ���Ϣ
struct APISTRUCT DFITCPositionInfoRtnField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCAccountIDType                  accountID;                    //�ʽ��ʺ�ID
    DFITCExchangeIDType                 exchangeID;                   //����������
    DFITCInstrumentIDType               instrumentID;                 //��Լ��
    DFITCBuySellTypeType                buySellType;                  //����
    DFITCPriceType                      openAvgPrice;                 //���־���
    DFITCPriceType                      positionAvgPrice;             //�ֲ־���
    DFITCAmountType                     positionAmount;               //�ֲ���
    DFITCAmountType                     totalAvaiAmount;              //�ܿ���
    DFITCAmountType                     todayAvaiAmount;              //�����
    DFITCAmountType                     lastAvaiAmount;               //�����
    DFITCAmountType                     todayAmount;                  //���
    DFITCAmountType                     lastAmount;                   //���
    DFITCAmountType                     tradingAmount;                //�ҵ���
    DFITCProfitLossType                 datePositionProfitLoss;       //���гֲ�ӯ��
    DFITCProfitLossType                 dateCloseProfitLoss;          //����ƽ��ӯ��
    DFITCProfitLossType                 dPremium;                     //Ȩ����
    DFITCProfitLossType                 floatProfitLoss;              //����ӯ��
    DFITCProfitLossType                 dMargin;                      //ռ�ñ�֤��
    DFITCSpeculatorType                 speculator;                   //Ͷ�����
    DFITCClientIDType                   clientID;                     //���ױ���
    DFITCPriceType                      preSettlementPrice;           //������
    DFITCInstrumentTypeType             instrumentType;               //��Լ����

    DFITCPositionInfoRtnField();
};


///�û���¼������Ϣ
struct APISTRUCT DFITCUserLoginInfoRtnField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCAccountIDType                  accountID;                    //�ʽ��ʺ�ID
    DFITCAccountLoginResultType         loginResult;                  //��¼���
    DFITCLocalOrderIDType               initLocalOrderID;             //��ʼ����ί�к�
    DFITCSessionIDType                  sessionID;                    //sessionID
    DFITCErrorIDType                    nErrorID;                     //����ID
    DFITCErrorMsgInfoType               errorMsg;                     //������Ϣ
    DFITCTimeType                       DCEtime;                      //������ʱ��
    DFITCTimeType                       SHFETime;                     //������ʱ��
    DFITCTimeType                       CFFEXTime;                    //�н���ʱ��
    DFITCTimeType                       CZCETime;                     //֣����ʱ��

    DFITCUserLoginInfoRtnField();
};


///�û��˳�������Ϣ
struct APISTRUCT DFITCUserLogoutInfoRtnField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCAccountIDType                  accountID;                    //�ʽ��˻�ID
    DFITCAccountLogoutResultType        logoutResult;                 //�˳����
    DFITCErrorIDType                    nErrorID;                     //����ID
    DFITCErrorMsgInfoType               errorMsg;                     //������Ϣ

    DFITCUserLogoutInfoRtnField();
};


///������Լ��ѯ
struct  APISTRUCT DFITCAbiInstrumentField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCAccountIDType                  accountID;                    //�ʽ��˻�ID
    DFITCExchangeIDType                 exchangeID;                   //����������

    DFITCAbiInstrumentField();
};


///������Լ������Ϣ
struct APISTRUCT DFITCAbiInstrumentRtnField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCExchangeIDType                 exchangeID;                   //����������
    DFITCInstrumentIDType               InstrumentID;                 //��Լ����
    DFITCInstrumentNameType             instrumentName;               //��Լ����

    DFITCAbiInstrumentRtnField();
};


///ָ���ĺ�Լ
struct APISTRUCT DFITCSpecificInstrumentField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCAccountIDType                  accountID;                    //�ʽ��˻�ID
    DFITCInstrumentIDType               InstrumentID;                 //��Լ����
    DFITCExchangeIDType                 exchangeID;                   //������ID
    DFITCInstrumentTypeType             instrumentType;               //��Լ����

    DFITCSpecificInstrumentField();
};


///���鶩�ķ�����Ϣ
struct APISTRUCT DFITCActiveContractField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCActiveContractType             activeContract;               //��Ч��Լ

    DFITCActiveContractField();
};


///��������Լ������Ϣ
struct APISTRUCT DFITCExchangeInstrumentRtnField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCExchangeIDType                 exchangeID;                   //����������
    DFITCInstrumentIDType               instrumentID;                 //��Լ����
    DFITCVarietyNameType                VarietyName;                  //Ʒ������
    DFITCInstrumentTypeType             instrumentType;               //��Լ����
    DFITCAmountType                     orderTopLimit;                //ί������
    DFITCPriceType                      contractMultiplier;           //��Լ����
    DFITCPriceType                      minPriceFluctuation;          //��С�䶯��λ
    DFITCInstrumentMaturityType         instrumentMaturity;           //��Լ�������
    DFITCPriceType                      upperLimitPrice;              //��ͣ���
    DFITCPriceType                      lowerLimitPrice;              //��ͣ���
    DFITCPriceType                      preClosePrice;                //������
    DFITCPriceType                      preSettlementPrice;           //������
    DFITCPriceType                      settlementPrice;              //�����
    DFITCAmountType                     preOpenInterest;              //��ֲ���

    DFITCExchangeInstrumentRtnField();
};


///ί�в�ѯ���ݽṹ
struct APISTRUCT DFITCOrderField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCAccountIDType                  accountID;                    //�ʽ��˻�ID
    DFITCInstrumentTypeType             instrumentType;               //��Լ����
    DFITCCustomCategoryType             customCategory;               //�Զ������

    DFITCOrderField();
};


///�ɽ���ѯ���ݽṹ
struct APISTRUCT DFITCMatchField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCAccountIDType                  accountID;                    //�ʽ��˻�ID
    DFITCInstrumentTypeType             instrumentType;               //��Լ����
    DFITCCustomCategoryType             customCategory;               //�Զ������

    DFITCMatchField();
};


///ί�в�ѯ��Ӧ���ݽṹ
struct APISTRUCT DFITCOrderCommRtnField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCSPDOrderIDType                 spdOrderID;                   //��̨ί�к�
    DFITCOrderAnswerStatusType          orderStatus;                  //ί��״̬
    DFITCInstrumentIDType               instrumentID;                 //��Լ����
    DFITCBuySellTypeType                buySellType;                  //����
    DFITCOpenCloseTypeType              openClose;                    //��ƽ��־
    DFITCPriceType                      insertPrice;                  //ί�м�
    DFITCAmountType                     orderAmount;                  //ί������
    DFITCPriceType                      matchedPrice;                 //�ɽ��۸�
    DFITCAmountType                     matchedAmount;                //�ɽ�����
    DFITCAmountType                     cancelAmount;                 //��������
    DFITCInsertType                     insertType;                   //ί�����
    DFITCSpeculatorType                 speculator;                   //Ͷ��
    DFITCDateType                       commTime;                     //ί��ʱ��
    DFITCDateType                       submitTime;                   //�걨ʱ��
    DFITCClientIDType                   clientID;                     //���ױ���
    DFITCExchangeIDType                 exchangeID;                   //������ID
    DFITCFrontAddrType                  operStation;                  //ί�е�ַ
    DFITCAccountIDType                  accountID;                    //�ͻ���
    DFITCInstrumentTypeType             instrumentType;               //��Լ����
    DFITCReservedType                   reservedType1;                //Ԥ���ֶ�1
    DFITCReservedType                   reservedType2;                //Ԥ���ֶ�2
    DFITCOrderSysIDType                 OrderSysID;                   //�������
    DFITCCustomCategoryType             customCategory;               //�Զ������
    DFITCPriceType                      margin;                       //��֤��
    DFITCPriceType                      fee;                          //������
    DFITCLocalOrderIDType               localOrderID;                 //����ί�к�

    DFITCOrderCommRtnField();
};


//�ɽ���ѯ������Ӧ
struct APISTRUCT DFITCMatchedRtnField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCSPDOrderIDType                 spdOrderID;                   //��̨ί�к�
    DFITCExchangeIDType                 exchangeID;                   //������ID
    DFITCInstrumentIDType               instrumentID;                 //��Լ����
    DFITCBuySellTypeType                buySellType;                  //����
    DFITCOpenCloseTypeType              openClose;                    //��ƽ
    DFITCPriceType                      matchedPrice;                 //�ɽ��۸�
    DFITCAmountType                     matchedAmount;                //�ɽ�����
    DFITCPriceType                      matchedMort;                  //�ɽ����
    DFITCSpeculatorType                 speculator;                   //Ͷ�����
    DFITCDateType                       matchedTime;                  //�ɽ�ʱ��
    DFITCMatchIDType                    matchedID;                    //�ɽ����
    DFITCLocalOrderIDType               localOrderID;                 //����ί�к�
    DFITCClientIDType                   clientID;                     //���ױ���
    DFITCMatchType                      matchType;                    //�ɽ�����
    DFITCInstrumentTypeType             instrumentType;               //��Լ����
    DFITCReservedType                   reservedType1;                //Ԥ���ֶ�1
    DFITCReservedType                   reservedType2;                //Ԥ���ֶ�2
    DFITCCustomCategoryType             customCategory;               //�Զ������
    DFITCPriceType                      fee;                          //������

    DFITCMatchedRtnField();
};


///���غ�Լ��Ϣ���ݽṹ
struct APISTRUCT DFITCInstrumentRtnField
{
    DFITCRequestIDType                  lRequestID;                   //������
    DFITCInstrumentIDType               instrumentID;                 //��Լ����
    DFITCRatioType                      longMarginRatio;              //��ͷ��֤����
    DFITCRatioType                      shortMarginRatio;             //��ͷ��֤����
    DFITCRatioType                      openFeeVolRatio;              //���������� ����������
    DFITCRatioType                      closeFeeVolRatio;             //ƽ�������� ����������
    DFITCRatioType                      closeTodayFeeVolRatio;        //ƽ�������� ����������
    DFITCRatioType                      openFeeAmtRatio;              //������������ ��������
    DFITCRatioType                      closeFeeAmtRatio;             //ƽ���������� ��������
    DFITCRatioType                      closeTodayFeeAmtRatio;        //ƽ���������� ��������
    DFITCAmountType                     orderTopLimit;                //ί������
    DFITCPriceType                      contractMultiplier;           //��Լ����
    DFITCPriceType                      minimumPriceChange;           //��С�䶯��λ
    DFITCInstrumentTypeType             instrumentType;               //��Լ����
    DFITCInstrumentMaturityType         instrumentMaturity;           //��Լ�������
    DFITCComputeModeType                computeMode;                  //���㷽ʽ             
    DFITCPriceType                      atMoneyNorm;                  //ƽֵ������
    DFITCPriceType                      upperLimitPrice;              //��ͣ���
    DFITCPriceType                      lowerLimitPrice;              //��ͣ���
    DFITCPriceType                      preClosePrice;                //������
    DFITCPriceType                      preSettlementPrice;           //������
    DFITCPriceType                      settlementPrice;              //�����
    DFITCAmountType                     preOpenInterest;              //��ֲ���
    DFITCRatioType                      optExecRatio;                 //��Ȩ����Ȩ������ �ڻ����������
    DFITCRatioType                      optExecRatioPerVol;           //��Ȩ����Ȩ������ �ڻ����������

    DFITCInstrumentRtnField();
};


///�������
struct APISTRUCT DFITCDepthMarketDataField
{
    DFITCDateType                       tradingDay;                   //������
    DFITCInstrumentIDType               instrumentID;                 //��Լ����
    DFITCExchangeIDType                 exchangeID;                   //����������
    DFITCInstrumentIDType               exchangeInstID;               //��Լ�ڽ������Ĵ���
    DFITCPriceType                      lastPrice;                    //���¼�
    DFITCPriceType                      preSettlementPrice;           //�ϴν����
    DFITCPriceType                      preClosePrice;                //������
    DFITCAmountType                     preOpenInterest;              //��ֲ���
    DFITCPriceType                      openPrice;                    //����
    DFITCPriceType                      highestPrice;                 //��߼�
    DFITCPriceType                      lowestPrice;                  //��ͼ�
    DFITCAmountType                     Volume;                       //�ɽ�����
    DFITCPriceType                      turnover;                     //�ɽ����
    DFITCAmountType                     openInterest;                 //�ֲ���
    DFITCPriceType                      closePrice;                   //������
    DFITCPriceType                      settlementPrice;              //���ν����
    DFITCPriceType                      upperLimitPrice;              //��ͣ���
    DFITCPriceType                      lowerLimitPrice;              //��ͣ���
    DFITCDeltaType                      preDelta;                     //����ʵ��
    DFITCDeltaType                      currDelta;                    //����ʵ��
    DFITCDateType                       UpdateTime;                   //����޸�ʱ��
    DFITCMilliSecType                   UpdateMillisec;               //����޸ĺ���
    DFITCPriceType                      BidPrice1;                    //�����һ
    DFITCVolumeType                     BidVolume1;                   //������һ
    DFITCPriceType                      AskPrice1;                    //������һ
    DFITCVolumeType                     AskVolume1;                   //������һ
    DFITCPriceType                      BidPrice2;                    //����۶�
    DFITCVolumeType                     BidVolume2;                   //��������
    DFITCPriceType                      AskPrice2;                    //�����۶�
    DFITCVolumeType                     AskVolume2;                   //��������
    DFITCPriceType                      BidPrice3;                    //�������
    DFITCVolumeType                     BidVolume3;                   //��������
    DFITCPriceType                      AskPrice3;                    //��������
    DFITCVolumeType                     AskVolume3;                   //��������
    DFITCPriceType                      BidPrice4;                    //�������
    DFITCVolumeType                     BidVolume4;                   //��������
    DFITCPriceType                      AskPrice4;                    //��������
    DFITCVolumeType                     AskVolume4;                   //��������
    DFITCPriceType                      BidPrice5;                    //�������
    DFITCVolumeType                     BidVolume5;                   //��������
    DFITCPriceType                      AskPrice5;                    //��������
    DFITCVolumeType                     AskVolume5;                   //��������
    DFITCPriceType                      AveragePrice;                 //���վ���
    DFITCDateType                       XSpeedTime;                   //��̨ϵͳʱ��

    DFITCDepthMarketDataField();
};

//�Զ����������
struct APISTRUCT DFITCCustomMarketDataField
{
    DFITCInstrumentIDType               instrumentID;                 //��Լ����
    DFITCExchangeIDType                 exchangeID;                   //������
    DFITCVolumeType                     bidVolume1;                   //��һ��
    DFITCPriceType                      bidPrice1;                    //��һ��(�Ҽۼ۲�)
    DFITCVolumeType                     askVolume1;                   //��һ��
    DFITCPriceType                      askPrice1;                    //��һ��(�Լۼ۲�)
    DFITCPriceType                      lastPrice;                    //���¼ۼ۲�

    DFITCCustomMarketDataField();
};

///��ѯ�ֲ���ϸ
struct APISTRUCT DFITCPositionDetailField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCAccountIDType                  accountID;                    //�ʽ��˻�ID
    DFITCInstrumentIDType               instrumentID;                 //��Լ����
    DFITCInstrumentTypeType             instrumentType;               //��Լ����

    DFITCPositionDetailField();
};


///��ѯ�ֲ���ϸ��Ӧ
struct APISTRUCT DFITCPositionDetailRtnField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCAccountIDType                  accountID;                    //�ʽ��ʺ�ID
    DFITCExchangeIDType                 exchangeID;                   //����������
    DFITCInstrumentIDType               instrumentID;                 //��Լ��
    DFITCBuySellTypeType                buySellType;                  //����
    DFITCPriceType                      openPrice;                    //���ּ�
    DFITCAmountType                     volume;                       //����
    DFITCMatchIDType                    matchID;                      //�ɽ����
    DFITCDateType                       matchedDate;                  //�ɽ�����
    DFITCProfitLossType                 datePositionProfitLoss;       //���гֲ�ӯ��
    DFITCProfitLossType                 dateCloseProfitLoss;          //����ƽ��ӯ��
    DFITCProfitLossType                 floatProfitLoss;              //����ӯ��
    DFITCProfitLossType                 dMargin;                      //ռ�ñ�֤��
    DFITCSpeculatorType                 speculator;                   //Ͷ�����
    DFITCClientIDType                   clientID;                     //���ױ���
    DFITCPriceType                      preSettlementPrice;           //������
    DFITCInstrumentTypeType             instrumentType;               //��Լ����
    DFITCSPDOrderIDType                 spdOrderID;                   //��̨ί�к�
    DFITCCustomCategoryType             customCategory;               //�Զ������

    DFITCPositionDetailRtnField();
};


///�û��¼�֪ͨ��Ϣ
struct APISTRUCT DFITCTradingNoticeInfoField
{
    DFITCAccountIDType                  accountID;                    //�ʽ��ʺ�ID
    DFITCTimeType                       SendTime;                     //����ʱ��
    DFITCContentType                    FieldContent;                 //��Ϣ����
    DFITCNoticeType                     noticeType;                   //��Ϣ����

    DFITCTradingNoticeInfoField();
};


///�û������޸�
struct APISTRUCT DFITCResetPwdField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCAccountIDType                  accountID;                    //�ʽ��ʺ�ID
    DFITCPasswdType                     oldpasswd;                    //������
    DFITCPasswdType                     newpasswd;                    //������

    DFITCResetPwdField();
};


///�û������޸ķ�����Ϣ
struct APISTRUCT DFITCResetPwdRspField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCAccountIDType                  accountID;                    //�ʽ��˻�ID
    DFITCExecStateType                  execState;                    //״̬��־

    DFITCResetPwdRspField();
};


///�˵�ȷ��
struct APISTRUCT DFITCBillConfirmField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCAccountIDType                  accountID;                    //�ʽ��ʺ�ID
    DFITCDateType                       date;                         //ȷ������  ��ʽ��yyyy.mm.dd
    DFITCConfirmMarkType                confirmFlag;                  //ȷ�ϱ�־

    DFITCBillConfirmField();
};


///�˵�ȷ����Ӧ
struct APISTRUCT DFITCBillConfirmRspField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCAccountIDType                  accountID;                    //�ʽ��˻�ID
    DFITCExecStateType                  execState;                    //״̬��־

    DFITCBillConfirmRspField();
};


///���ױ����ѯ
struct APISTRUCT DFITCQryTradeCodeField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCAccountIDType                  accountID;                    //�ʽ��˻�ID

    DFITCQryTradeCodeField();
};


///���ױ����ѯ��Ӧ
struct APISTRUCT DFITCQryTradeCodeRtnField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCAccountIDType                  accountID;                    //�ʽ��˻�
    DFITCExchangeIDType                 exchangeCode;                 //����������
    DFITCClientIDType                   clientID;                     //���ױ��� 
    DFITCClientStatusType               clientStatus;                 //���ױ���״̬
    DFITCSpeculatorType                 clientIDType;                 //���ױ�������

    DFITCQryTradeCodeRtnField();
}; 


///��ӯ�����Ƿ���㵽Ȩ����
struct APISTRUCT DFITCEquityComputModeRtnField
{
    DFITCCapControlModeType             capConMode;                   //�ʽ���Ʒ�ʽ,�÷�ʽ��Ҫ�û���λ�ж�,����Ϊ�������
    DFITCPriceNoteType                  priceNote;                    //��Ȩ��֤�����˵��

    DFITCEquityComputModeRtnField();
};


///��ѯ�˵�
struct APISTRUCT DFITCQryBillField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCAccountIDType                  accountID;                    //�ʽ��˻�
    DFITCDateType                       date;                         //��ѯ����   ��ʽ��yyyy.mm.dd

    DFITCQryBillField();
};


///��ѯ�˵���Ӧ
struct APISTRUCT DFITCQryBillRtnField 
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCAccountIDType                  accountID;                    //�ʽ��˻�
    DFITCMsgInfoType                    message;                      //������Ϣ

    DFITCQryBillRtnField();
};


///����IDȷ������
struct APISTRUCT DFITCProductField
{
    DFITCProductIDType                  productID;                    //��Ʒ���
    DFITCSoftwareVendorIDType           vendorID;                     //�����Ӧ�̱�� 

    DFITCProductField();
};


///����IDȷ����Ӧ
struct APISTRUCT DFITCProductRtnField 
{
    DFITCProductIDType                  productID;                    //��Ʒ���
    DFITCSoftwareVendorIDType           vendorID;                     //�����Ӧ��
    DFITCProductOnlineCountType         productOnlineCount;           //��Ʒ��������
    DFITCBrokerInfoType                 brokerInfoName;               //�ڻ���˾����
    DFITCFrontIDType                    frontID;                      //ǰ�û�ID

    DFITCProductRtnField();
};


//�����㷨��������������
struct APISTRUCT DFITCInsertExtOrderField
{
    DFITCAccountIDType                accountID;                      //�ʽ��˺�
    DFITCLocalOrderIDType             localOrderID;                   //����ί�к�
    DFITCInstrumentIDType             instrumentID;                   //��Լ����
    DFITCRequestIDType                lRequestID;                     //����ID
    DFITCPriceType                    insertPrice;                    //ί�м۸�
    DFITCAmountType                   orderAmount;                    //ί������
    DFITCBuySellTypeType              buySellType;                    //������־
    DFITCOpenCloseTypeType            openCloseType;                  //��ƽ��־
    DFITCSpeculatorType               speculator;                     //Ͷ�����ͣ�֧��Ͷ�����������ױ�
    DFITCInsertType                   insertType;                     //ί�����(Ĭ��Ϊ��ͨ����)
    DFITCOrderTypeType                orderType;                      //��������, ֧���޼� ���мۣ���������Լ��֧���мۣ������޼۽��д���
    DFITCExtOrderType                 extOrderType;                   //�㷨������
    DFITCTriggerTime                  triggerTime;                    //����ʱ��
    DFITCPriceReference               priceReference;                 //�۸����
    DFITCCompareFlag                  compareFlag;                    //�Ƚϱ�־
    DFITCOvernightFlag                overnightFlag;                  //��ҹ��־
    DFITCArbitragePrice               arbitragePrice;                 //�����۸�
    DFITCInstrumentTypeType           instrumentType;                 //��Լ����, ��ѡֵ���ڻ�����Ȩ
    DFITCCustomCategoryType           customCategory;                 //�Զ������
    DFITCReservedType                 reservedType1;                  //Ԥ���ֶ�1
    DFITCReservedType                 reservedType2;                  //Ԥ���ֶ�2

    DFITCInsertExtOrderField();
};


///�㷨��ί�в�ѯ���ݽṹ
struct APISTRUCT DFITCExtOrderField
{
    DFITCRequestIDType                lRequestID;                      //����ID
    DFITCAccountIDType                accountID;                       //�ʽ��˻�ID
    DFITCSPDOrderIDType               spdOrderID;                      //��̨ί�к�

    DFITCExtOrderField();
};


///�㷨����ѯ��Ӧ
struct APISTRUCT DFITCExtOrderCommRtnField
{
    DFITCAccountIDType                accountID;                      //�ʽ��˺�
    DFITCSPDOrderIDType               spdOrderID;                     //��̨ί�к�
    DFITCInstrumentIDType             instrumentID;                   //��Լ����
    DFITCRequestIDType                lRequestID;                     //����ID
    DFITCPriceType                    insertPrice;                    //ί�м۸�
    DFITCAmountType                   orderAmount;                    //ί������
    DFITCBuySellTypeType              buySellType;                    //������־
    DFITCOpenCloseTypeType            openCloseType;                  //��ƽ��־
    DFITCSpeculatorType               speculator;                     //Ͷ�����ͣ�֧��Ͷ�����������ױ�
    DFITCInsertType                   insertType;                     //ί�����(Ĭ��Ϊ��ͨ����)
    DFITCOrderTypeType                orderType;                      //��������, ֧���޼� ���мۣ���������Լ��֧���мۣ������޼۽��д���
    DFITCExtOrderType                 extOrderType;                   //�㷨������
    DFITCTriggerTime                  triggerTime;                    //����ʱ��
    DFITCPriceReference               priceReference;                 //�۸����
    DFITCCompareFlag                  compareFlag;                    //�Ƚϱ�־
    DFITCOvernightFlag                overnightFlag;                  //��ҹ��־
    DFITCOrderAnswerStatusType        extOrderStatus;                 //�㷨������״̬
    DFITCExchangeIDType               exchangeCode;                   //����������
    DFITCClientIDType                 clientID;                       //���ױ��� 
    DFITCMsgInfoType                  message;                        //������Ϣ

    DFITCExtOrderCommRtnField();
};


///��ѯ����������
struct APISTRUCT DFITCTradingDayField
{
    DFITCRequestIDType                  lRequestID;                   //����ID

    DFITCTradingDayField();
};


///������������Ӧ
struct APISTRUCT DFITCTradingDayRtnField
{
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCDateType                       date;                         //������

    DFITCTradingDayRtnField();
};


///����֪ͨ��������
struct APISTRUCT DFITCQuoteSubscribeField
{
    DFITCAccountIDType                  accountID;                    //�ʽ��˺�
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCExchangeIDType                 exchangeID;                   //������
    DFITCInstrumentTypeType             instrumentType;               //��Լ����

    DFITCQuoteSubscribeField();
};


///����֪ͨ������Ӧ
struct APISTRUCT DFITCQuoteSubscribeRspField
{	
    DFITCExecStateType                  subscribeFlag;                //����״̬
    DFITCRequestIDType                  lRequestID;                   //����ID
   
    DFITCQuoteSubscribeRspField();
};


///����֪ͨ�˶�����
struct APISTRUCT DFITCQuoteUnSubscribeField
{
    DFITCAccountIDType                  accountID;                    //�ʽ��˺�
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCExchangeIDType                 exchangeID;                   //������
    DFITCInstrumentTypeType             instrumentType;               //��Լ����

    DFITCQuoteUnSubscribeField();
};


///����֪ͨ�˶���Ӧ
struct APISTRUCT DFITCQuoteUnSubscribeRspField
{	
    DFITCExecStateType                  subscribeFlag;                //�˶�״̬
    DFITCRequestIDType                  lRequestID;                   //����ID

    DFITCQuoteUnSubscribeRspField();
};


///����֪ͨ���Ļر�
struct APISTRUCT DFITCQuoteSubscribeRtnField
{
    DFITCQuoteIDType                    quoteID;                      //ѯ�۱��
    DFITCExchangeIDType                 exchangeID;                   //������
    DFITCInstrumentIDType               instrumentID;                 //��Լ����
    DFITCBuySellTypeType                buySellType;                  //������־
    DFITCSourceType                     source;                       //��Դ
    DFITCClientIDType                   clientID;                     //���ױ���
    DFITCSeatCodeType                   seatCode;                     //ϯλ����
    DFITCDateType                       tradingDate;                  //��������
    DFITCDateType                       quoteTime;                    //ѯ��ʱ��
    DFITCDateType                       quoteRecvTime;                //ѯ�۽���ʱ��

    DFITCQuoteSubscribeRtnField();
};


//�����̱�������
struct APISTRUCT DFITCQuoteInsertField
{
    DFITCAccountIDType                  accountID;                    //�ʽ��˺�
    DFITCRequestIDType                  lRequestID;                   //����ID
    DFITCLocalOrderIDType               localOrderID;                 //����ί�к�
    DFITCInsertType                     insertType;                   //ί�����
    DFITCInstrumentIDType               instrumentID;                 //��Լ����
    DFITCQuoteIDType                    quoteID;                      //ѯ�۱��
    DFITCInstrumentTypeType             instrumentType;               //��Լ���� 
    DFITCAmountType                     bOrderAmount;                 //������������
    DFITCAmountType                     sOrderAmount;                 //��������������
    DFITCPriceType                      bInsertPrice;                 //ί�м۸���         
    DFITCPriceType                      sInsertPrice;                 //ί�м۸�����          
    DFITCOpenCloseTypeType              bOpenCloseType;               //��ƽ��־����  
    DFITCOpenCloseTypeType              sOpenCloseType;               //��ƽ��־������
    DFITCSpeculatorType                 bSpeculator;                  //Ͷ������� 	  
    DFITCSpeculatorType                 sSpeculator;                  //Ͷ���������          
    DFITCStayTimeType                   stayTime;                     //ͣ��ʱ�䣬��֧��֣�ݡ��������������Ϊ0 
    DFITCBuySellTypeType                buySellType;                  //������־

    DFITCQuoteInsertField();
};


//�����̱�����Ӧ
struct APISTRUCT DFITCQuoteRspField
{  
    DFITCLocalOrderIDType               localOrderID;                 //����ί�к�              
    DFITCSPDOrderIDType                 spdOrderID;                   //��̨ί�к�                
    DFITCRequestIDType                  lRequestID;                   //����ID                    
    DFITCPriceType                      fee;                          //˫��������֮��            
    DFITCPriceType                      margin;                       //˫�߱�֤��֮��
    DFITCDateType                       orderTime;                    //ί��ʱ��      
	
    DFITCQuoteRspField();
};


//�����̱����ر�
struct APISTRUCT DFITCQuoteRtnField
{
    DFITCExchangeIDType                 exchangeID;                    //������                   
    DFITCClientIDType                   clientID;                      //���ױ���  
    DFITCOrderSysIDType                 orderSysID;                    //�������
    DFITCInstrumentIDType               instrumentID;                  //��Լ����                   
    DFITCLocalOrderIDType               localOrderID;                  //����ί�к�                
    DFITCSeatCodeType                   seatCode;                      //ϯλ����                  
    DFITCOpenCloseTypeType              bOpenCloseType;                //��ƽ��־����          
    DFITCOpenCloseTypeType              sOpenCloseType;                //��ƽ��־������             
    DFITCSpeculatorType                 bSpeculator;                   //Ͷ�������             
    DFITCSpeculatorType                 sSpeculator;                   //Ͷ���������           
    DFITCAmountType                     bOrderAmount;                  //ί����������            
    DFITCAmountType                     sOrderAmount;                  //ί������������           
    DFITCPriceType                      bInsertPrice;                  //ί�м�  ����               
    DFITCPriceType                      sInsertPrice;                  //ί�м�  ������               
    DFITCSPDOrderIDType                 spdOrderID;                    //��̨ί�к�                               
    DFITCAccountIDType                  accountID;                     //�ʽ��˺�                     
    DFITCInstrumentTypeType             instrumentType;                //��Լ����                  
    DFITCDateType                       suspendTime;                   //�ҵ�ʱ��                  
    DFITCCloseIDType                    closeID;                       //ƽ��ִ�е���               
    DFITCEntrusTellerType               entrusTeller;                  //ί�й�Ա   	
    DFITCOrderAnswerStatusType          orderStatus;                   //ί��״̬ 
    DFITCOrderSysIDType                 bOrderSysID;                   //����������
    DFITCOrderSysIDType                 sOrderSysID;                   //������������

    ///�����ֶν��� orderStatusΪ2��ʱ�򷵻�

    DFITCAmountType                     bCancelAmount;                 //������������               
    DFITCAmountType                     sCancelAmount;                 //��������������                
    DFITCPriceType                      fee;                           //�ⶳ������                  
    DFITCPriceType                      margin;                        //�ⶳ��֤�� 
    DFITCErrorMsgInfoType               errorMsg;                      //������Ϣ
	
    DFITCQuoteRtnField();
};


//���г������ر�
struct APISTRUCT DFITCQuoteCanceledRtnField
{	
    DFITCLocalOrderIDType               localOrderID;                  //����ί�к�
    DFITCOrderSysIDType                 orderSysID;                    //�������  
    DFITCInstrumentIDType               instrumentID;                  //��Լ���� 
    DFITCInstrumentTypeType             instrumentType;                //��Լ����
    DFITCPriceType                      bInsertPrice;                  //ί�м۸���
    DFITCPriceType                      sInsertPrice;                  //ί�м۸�����
    DFITCAmountType                     bAmount;                       //������������
    DFITCAmountType                     sAmount;                       //��������������
    DFITCOpenCloseTypeType              bOpenCloseType;                //��ƽ��־����
    DFITCOpenCloseTypeType              sOpenCloseType;                //��ƽ��־������
    DFITCSpeculatorType                 bSpeculator;                   //Ͷ�����ͣ���
    DFITCSpeculatorType                 sSpeculator;                   //Ͷ�����ͣ�����
    DFITCSPDOrderIDType                 spdOrderID;                    //��̨ί�к�
    DFITCExchangeIDType                 exchangeID;                    //������ID
    DFITCDateType                       canceledTime;                  //����ʱ��
    DFITCSessionIDType                  sessionID;                     //�Ự��ʶ
    DFITCOrderAnswerStatusType          orderStatus;                   //�걨���
    DFITCAccountIDType                  accountID;                     //�ʽ��˺�
    DFITCPriceType                      margin;                        //�ⶳ��֤��
    DFITCPriceType                      fee;                           //�ⶳ������

    DFITCQuoteCanceledRtnField();
};

//����״̬��ѯ����
struct APISTRUCT DFITCQryExchangeStatusField
{
    DFITCRequestIDType                  lRequestID;                    //����ID
    DFITCExchangeIDType                 exchangeID;                    //����������

    DFITCQryExchangeStatusField();
};
//������״̬��ѯ��Ӧ
struct APISTRUCT DFITCExchangeStatusRspField
{
    DFITCRequestIDType                  lRequestID;                    //����ID
    DFITCExchangeStatusType             exchangeStatus;                //������״̬

    DFITCExchangeStatusRspField();
};

//������״̬֪ͨ
struct APISTRUCT DFITCExchangeStatusRtnField
{
    DFITCExchangeIDType                 exchangeID;                   //������
    DFITCExchangeStatusType             exchangeStatus;               //������״̬

    DFITCExchangeStatusRtnField();
};
#endif//DFITCAPISTRUCT_H_
