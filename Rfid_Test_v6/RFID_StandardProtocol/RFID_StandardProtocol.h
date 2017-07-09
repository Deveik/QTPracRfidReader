// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the RFID_STANDARDPROTOCOL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// RFID_STANDARDPROTOCOL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

////////////////////////////////////////////////////////////////////////
// Module:  xxx
// Author:  xx
////////////////////////////////////////////////////////////////////////
#pragma once

#ifdef RFID_STANDARDPROTOCOL_EXPORTS
#define RFID_STANDARDPROTOCOL_API __declspec(dllexport)
#else
#define RFID_STANDARDPROTOCOL_API __declspec(dllimport)
#endif

// This class is exported from the RFID_StandardProtocol.dll
//////////////////////////////////////////////////////////////////////////
//���ܣ����Ӿ���ṹ��
//����˵����
//			hCom				�������Ӿ��
//			sockClient			�������Ӿ��
//////////////////////////////////////////////////////////////////////////
typedef struct RFID_STANDARDPROTOCOL_API hComSocket
{
	HANDLE hCom;
	SOCKET sockClient;
}hComSocket;

//////////////////////////////////////////////////////////////////////////
//���ܣ�EPC GEN2��ǩ�������ȡ�����ṹ��
//����˵����
//			MembankMask			��ǩ�������루Reserve 1�� Epc 2��Tid 4��User 8��
//			ReserveWordPtr		Reserve����ȡ��ʼ��ַ
//			ReserveWordCnt		Reserve��׼����ȡ�����ݳ��ȣ���λ���֣�	
//			EpcWordPtr			Epc����ȡ��ʼ��ַ
//			EpcWordCnt			Epc��׼����ȡ�����ݳ��ȣ���λ���֣�	
//			TidWordPtr			Tid����ȡ��ʼ��ַ
//			TidWordCnt			Tid��׼����ȡ�����ݳ��ȣ���λ���֣�	
//			UserWordPtr			User����ȡ��ʼ��ַ
//			UserWordCnt			User��׼����ȡ�����ݳ��ȣ���λ���֣�	
//////////////////////////////////////////////////////////////////////////
typedef struct RFID_STANDARDPROTOCOL_API WordptrAndLength
{
	int MembankMask;
	int ReserveWordPtr;
	int ReserveWordCnt;
	int EpcWordPtr;
	int EpcWordCnt;
	int TidWordPtr;
	int TidWordCnt;
	int UserWordPtr;
	int UserWordCnt;
}WordptrAndLength;

//////////////////////////////////////////////////////////////////////////
//���ܣ�EPC GEN2��ǩ�������
//����˵����
//			Len					���ݳ��ȣ�Ant�ĳ��� + Data�ĳ��ȣ�
//			Ant					���ߺţ�1�ֽڣ�
//			Data				���ݻ����� 
//////////////////////////////////////////////////////////////////////////
typedef struct RFID_STANDARDPROTOCOL_API BufferData
{
	int Len;
	int Ant;
	unsigned char Data[512];
}BufferData;

//////////////////////////////////////////////////////////////////////////
//���ܣ����ǩд�������ýṹ��
//����˵����
//			MemBank				��ǩд������Reserve 0�� Epc 1��Tid 2��User 3��
//			StartAddr			��д�����ݵ���ʼ��ַ
//			WriteLen			��д�����ݳ���
//			WriteValue			��д������
//////////////////////////////////////////////////////////////////////////
typedef struct RFID_STANDARDPROTOCOL_API MutiWriteParam
{
	int MemBank;				
	int StartAddr;
	int WriteLen;
	unsigned char WriteValue[20];
}MutiWriteParam;

//////////////////////////////////////////////////////////////////////////
//���ܣ�ʱ��ṹ��
//����˵����
//			YearH				����ֽڣ�(2014 >> 8 )& 0xFF��
//			YearL				����ֽڣ� 2014 & 0xFF��
//			Month				�·�	
//			Day					��
//			Hour				ʱ
//			Minute				��
//			Second				��
//////////////////////////////////////////////////////////////////////////
typedef struct RFID_STANDARDPROTOCOL_API ReaderTime
{
	unsigned char YearH;
	unsigned char YearL;
	unsigned char Month;
	unsigned char Day;
	unsigned char Hour;
	unsigned char Minute;
	unsigned char Second;
}ReaderTime;

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------DLL_����-------------------------------------------------------------*/
//ErrorCode		������붨��
#define SUCCESS 0					//�����ɹ�
#define SENDERROR 101				//���ʹ���
#define RECVERROR 201				//���ܴ���
#define DATAERROR 301				//���ݽ�������
#define CHECKERROR 401				//����У�����	
/************************************************DLL_ͨ�ŷ�ʽ******************************************************/
/************************TCP/IP************************/
//////////////////////////////////////////////////////////////////////////
//����:			ͨ�����������豸
//����:
//Socket:		���򿪵����ھ��
//IPAddress:	���򿪵�����IP��ַ��ep: 192.168.1.120��
//Port:			���򿪵����ڶ˿ڣ�100 ��д���ڲ��˿ڹ̶��Ķ˿�ֵ�����ɸ��ģ�
//����ֵ��		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Socket_ConnectSocket(SOCKET *Socket, char *IPAddress, int Port);

//////////////////////////////////////////////////////////////////////////
//����:			�ر���������
//����:
//Socket:		���رյ����ھ��
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Socket_CloseSocket(SOCKET Socket);

/*************************����************************/
//////////////////////////////////////////////////////////////////////////
//����:			ͨ�����������豸
//����:
//hCom:			���򿪵Ĵ��ھ��
//ComName:		���򿪵Ĵ��ںţ�ep: COM3��
//Baud:			���򿪵Ĵ��ڲ����ʣ�Ĭ�ϲ�����Ϊ115200��
//����ֵ��		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Serial_OpenSeries(HANDLE *hCom, char *ComName, int Baud);

//////////////////////////////////////////////////////////////////////////
//����:			�رմ�������
//����:
//hCom:			���رյĴ��ھ��
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Serial_CloseSeries(HANDLE hCom);

/************************************************DLL_ϵͳ����******************************************************/
//////////////////////////////////////////////////////////////////////////
//����:			��ȡ��д���汾��
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//major:		�̼���������汾
//minor:		�̼�����Ĵΰ汾
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ��		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_GetLocatorVersion(hComSocket CS, unsigned char &major, unsigned char &minor, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			���ö�д��������
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//Parameter:	�����õĲ����ʲ���,Ĭ�ϲ�����Ϊ115200,�Ҳ������޸Ĳ���������,��ϸ�����������£�ep: Parameter = 0x04��
//				0x00 9600bps
//				0x01 19200bps
//				0x02 38400bps
//				0x03 57600bps
//				0x04 115200bps
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ��		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_SetReaderBaud(hComSocket CS, unsigned char Parameter, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			��λ��д��
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ��		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_ResetReader(hComSocket CS, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			���ö�д�����߹���
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//Pwr:			�����õĹ���ֵ�����ڴ����Ʒ����Pwr��С:Pwr[4]�����뽫Pwr[0]����Ϊ����Ҫ�޸ĵĹ���ֵ��Pwr[1-3]�븳ֵΪ0
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ��		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_SetRfPower(hComSocket CS, unsigned char Pwr[], unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			��ѯ��д�����߹���
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//Pwr:			���߹��ʲ�ѯ�����������ڴ����Ʒ����Pwr��С:Pwr[4]����Pwr[0]Ϊ���ѯ�����߹���ֵ������ֵΪ��Чֵ
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ��		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_GetRfPower(hComSocket CS, unsigned char Pwr[], unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			���ö�д����Ƶ����
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//Freq_num:		Ƶ�ʵ�������Freq_num = 0/��0��
//Freq_points:	Ƶ��(0/1/2 ����Ϊ900~930MHz��Χ�ڣ���250kHzΪ������Ƶ�ʵ�����)
//				��ep: ���Freq_num = 0����Freq_points��ֵֻ��Ϊ0/1/2��
//					  ���Freq_num != 0����Freq_pointsΪ900~930MHz��Χ�ڣ���250kHzΪ������Ƶ�ʵ�����������Freq_pointsΪ��0- 120����
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ��		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_SetFreqPoint(hComSocket CS, int Freq_num, int Freq_points[], unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			��ѯ��д����Ƶ����
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//Freq_num:		��ѯ�󷵻ص�Ƶ�ʵ�������Freq_num = 0/��0��
//Freq_points:	��ѯ�󷵻ص�Ƶ��(0/1/2 ����Ϊ900~930MHz��Χ�ڣ���250kHzΪ������Ƶ�ʵ�����)
//				��ep: ���Freq_num = 0����Freq_points��ֵֻ��Ϊ0/1/2��
//					  ���Freq_num != 0����Freq_pointsΪ900~930MHz��Χ�ڣ���250kHzΪ������Ƶ�ʵ�����������Freq_pointsΪ��0- 120����
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ��		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_GetFreqPoint(hComSocket CS, int &Freq_num, int Freq_points[], unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			���ö�д�����߹���״̬
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//WorkAnt:		UHF��д��֧�ִ�����
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ��		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_SetAntenna(hComSocket CS, int WorkAnt, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			��ѯ��д�����߹���״̬
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//WorkAnt:		UHF��д��֧�ִ�����
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ��		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_GetAntenna(hComSocket CS, int &WorkAnt, int &AntStatus, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			��ѯ��д�����߹���״̬����16ͨ��
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//WorkAnt[]:	2���ֽڰ�λ��ʶ16������ͨ��(ep: 11111111 11111111)
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ��		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_SetAntenna16(hComSocket CS, unsigned char *WorkAnt, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			��ѯ��д�����߹���״̬����16ͨ��
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//WorkAnt[]:	2���ֽ�(����)��λ��ʶ16������ͨ��
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ��		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_GetAntenna16(hComSocket CS, int *WorkAnt, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			���ö�д���ز���������
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//Mode:			Mode = 0,����Ϊ�������������࿨������ģʽ   Mode != 0,Ϊ������ģʽ
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ��		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_SetSingleFastTagMode(hComSocket CS, unsigned char Mode, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			��ѯ��д���ز���������̬
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//Mode:			Mode = 0,����Ϊ�������������࿨������ģʽ   Mode != 0,Ϊ������ģʽ
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ��		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_GetSingleFastTagMode(hComSocket CS, unsigned char &Mode, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			���ö�д������ģʽ
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//TestMode:		������Χ��0x00 �򿪹��ţ�0x01 �رչ��ţ�0x02 ����У׼��
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ��		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_SetTestMode(hComSocket CS, unsigned char TestMode, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			���ö�д��IO�ڵ�ƽ״̬
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//Num:			IO����ţ���Χ��0��1��2������2Ϊ�̵�����
//Level:		�����ƽ������ֵ���壨1Ϊ�ߵ�ƽ��0Ϊ�͵�ƽ��
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ��		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_SetOutPort(hComSocket CS, unsigned char Num, unsigned char Level, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			��ȡ��д��IO�ڵ�ƽ״̬
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//Num:			IO����ţ���Χ��0��1��2������2Ϊ�̵�����
//Level:		�����ƽ������ֵ���壨1Ϊ�ߵ�ƽ��0Ϊ�͵�ƽ��
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ��		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_GetInPort(hComSocket CS, unsigned char InPortNum, unsigned char &InPortLevel, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			���ö�д�����ڲ���
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//IPAddr:		IP��ַ��192.168.1.120��
//MaskCode:		���루255.255.255.0��
//GateWay:		���أ�192.168.1.1��
//InternetPort:	�˿ڣ��̶�Ϊ100�������޸ģ�
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ��		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_SetIntrnetAccess(hComSocket CS, unsigned char IPAddr[], unsigned char MaskCode[], unsigned char GateWay[], unsigned char InternetPort[], unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			��ѯ��д�����ڲ���
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//IPAddr:		IP��ַ��192.168.1.120��
//MaskCode:		���루255.255.255.0��
//GateWay:		���أ�192.168.1.1��
//InternetPort:	�˿ڣ��̶�Ϊ100�������޸ģ�
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ��		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_GetIntrnetAccess(hComSocket CS, unsigned char IPAddr[], unsigned char MaskCode[], unsigned char GateWay[], unsigned char InternetPort[], unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			���ö�д����ʵʱʱ��
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//RTime:		��д��ʱ��ṹ�壬��ο�ǰ��ʱ��ṹ��ľ��嶨��
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ��		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_SetReaderTime(hComSocket CS, ReaderTime RTime, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			��ȡ��д����ʵʱʱ��
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//RTime:		��д��ʱ��ṹ�壬��ο�ǰ��ʱ��ṹ��ľ��嶨��
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ��		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_GetReaderTime(hComSocket CS, ReaderTime &RTime, unsigned char ReaderAddr);


/************************************************DLL_ISO18000-6B��ǩ����***********************************************/
//////////////////////////////////////////////////////////////////////////
//����:			Iso18000���ǩʶ��
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//TagCount:		��ǩʶ�������ɺ󷵻صı��γɹ�ʶ��ı�ǩ��������ǩ���ݴ����д����������
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall ISO_MultiTagIdentify(hComSocket CS, int &TagCount, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			Iso18000���ǩ��ȡ
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//RAddr:		����ȡ�ı�ǩ���ݵ���ʼ��ַ����ȡÿ�ű�ǩ����ʼ��ַ��ʼ��8�ֽ����ݣ�
//RCount:		��ȡ��ɺ󷵻ر��γɹ���ȡ���ı�ǩ��������ǩ���ݴ����д����������
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall ISO_MultiTagRead(hComSocket CS, int RAddr, int &RCount, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			����ǩ��ȡ
//����:			
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//RAddr:		����ȡ�ı�ǩ���ݵ���ʼ��ַ����ȡÿ�ű�ǩ����ʼ��ַ��ʼ��8�ֽ����ݣ�
//RData:		��ȡ��ɺ󷵻ر��γɹ���ȡ���ı�ǩ����
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall ISO_TagRead(hComSocket CS, unsigned char RAddr, unsigned char *RData, unsigned char ReaderAddr);
int RFID_STANDARDPROTOCOL_API __stdcall ISO_TagRead_MultiBytes(hComSocket CS, int RAddr, unsigned char *RData, int iLen, unsigned char ReaderAddr);
//////////////////////////////////////////////////////////////////////////
//����:			����ǩ���ֽ�д��
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//WAddr:		��д��ı�ǩ���ݵ���ʼ��ַ
//WData:		��д���ǩ������
//DataLen:		��д���ǩ�����ݳ��ȣ��ֽ�Ϊ��λ���˴�֧�ֶ��ֽ�д�룩
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall ISO_TagWrite(hComSocket CS, int WAddr, unsigned char *WData, int DataLen, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			����ǩͨ��UID��ȡ��ǩ����
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//UID:			��֪�ı�ǩ��ID�ţ�8���ֽڣ�
//RAddr:		����ȡ�ı�ǩ���ݵ���ʼ��ַ����ȡÿ�ű�ǩ����ʼ��ַ��ʼ��8�ֽ����ݣ�
//RData:		��ȡ��ɺ󷵻ر��γɹ���ȡ���ı�ǩ���ݣ���д������9���ֽڵ����ݣ���һ���ֽ�Ϊ���ߺţ�ʣ�°˸��ֽ�Ϊ���ݣ�
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall ISO_TagReadWithUID(hComSocket CS, unsigned char *UID, int RAddr, unsigned char *RData, unsigned char ReaderAddr);
int RFID_STANDARDPROTOCOL_API __stdcall ISO_TagReadWithUID_MultiBytes(hComSocket CS, unsigned char *UID, int RAddr, unsigned char *RData, int iLen, unsigned char ReaderAddr);
//////////////////////////////////////////////////////////////////////////
//����:			����ǩͨ��UIDд���ǩ����
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//UID:			��֪�ı�ǩ��ID�ţ�8���ֽڣ�
//WAddr:		��д��ı�ǩ���ݵ���ʼ��ַ
//WData:		��д���ǩ������
//DataLen:		��д���ǩ�����ݳ��ȣ��ֽ�Ϊ��λ���˴�֧�ֶ��ֽ�д�룩
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall ISO_TagWriteWithUID(hComSocket CS, unsigned char *UID, int WAddr, unsigned char *WData, int DataLen, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			����ǩ����������
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//LAddr:		�������ı�ǩ��ַ
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall ISO_SetTagLock(hComSocket CS, int LAddr, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			����ǩ��������ѯ
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//QAddr:		����ѯ�ı�ǩ��ַ
//LStatus:		����״̬��0Ϊδ������ 1Ϊ������
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall ISO_QueryTagLock(hComSocket CS, int QAddr, int &LStatus, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			����ǩͨ��UID����������
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//UID:			��֪�ı�ǩ��ID�ţ�8���ֽڣ�
//LAddr:		�������ı�ǩ��ַ
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall ISO_SetTagLockWithUID(hComSocket CS, unsigned char *UID, int LAddr, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			����ǩͨ��UID��������ѯ
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//UID:			��֪�ı�ǩ��ID�ţ�8���ֽڣ�
//QAddr:		����ѯ�ı�ǩ��ַ
//LStatus:		����״̬��0Ϊδ������ 1Ϊ������
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall ISO_QueryTagLockWithUID(hComSocket CS, unsigned char *UID, int QAddr, int &LStatus, unsigned char ReaderAddr);

/************************************************DLL_EPC GEN2��ǩ��������**********************************************/
//////////////////////////////////////////////////////////////////////////
//����:			���ǩ��ѯ
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//TagCount:		��ǩʶ�������ɺ󷵻صı��γɹ�ʶ��ı�ǩ��������ǩ���ݴ����д����������
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall GEN2_MultiTagInventory(hComSocket CS, int &TagCount, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			���ǩ������������Ⱥ��
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//WpALen:		WordptrAndLength�ṹ����󣬾�������ο�WordptrAndLength�ṹ��˵��
//RCount:		��ǩ�ɹ�ִ�б�ǩ��ȡ�����󷵻ض����ı�ǩ��������ǩ���ݴ����д����������
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall GEN2_MultiTagRead(hComSocket CS, WordptrAndLength WpALen, int &RCount, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			���ǩд��
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//MutiWP:		MutiWriteParam�ṹ����󣬾�������ο�MutiWriteParam�ṹ��˵��
//WCount:		��ǩ�ɹ�ִ�б�ǩд������󷵻�д��ı�ǩ��������ǩ���ݴ����д����������
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall GEN2_MultiTagWrite(hComSocket CS, MutiWriteParam MutiWP, int &WCount, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			����ǩ��ȫ����
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//KPassWord:	���ٱ�ǩ���루����Ϊ4���ֽڣ�
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall GEN2_KillTag(hComSocket CS, unsigned char *KPassWord, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			����ǩ��ȫ��ȡ
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//Membank:		��ȡ���ʵı�ǩ����Reserve 0x00, EPC 0x01, TID 0x02, USER 0x03��
//RPassWord:	��ȡ�������루����Ϊ4���ֽڣ������������Ϊ0�����������ִ����ͨ�ı�ǩ��ȡ��
//RAddr:		����ȡ��ǩ���׵�ַ
//RCnt:			����ȡ��������1���� == 2���ֽڣ�
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall GEN2_SecRead(hComSocket CS, int Membank, unsigned char *RPassWord, int RAddr, int RCnt, unsigned char *RData, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			����ǩ��ȫд��
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//Membank:		д����ʵı�ǩ����Reserve 0x00, EPC 0x01, TID 0x02, USER 0x03��
//WPassWord:	д��������루����Ϊ4���ֽڣ������������Ϊ0�����������ִ����ͨ�ı�ǩ��ȡ��
//WAddr:		��д���ǩ���ֵ�ַ��0 ~ 5��
//WCnt:			��д���������1���� == 2���ֽڣ�
//WData:		��д���ǩ�����ݣ���ָ���ĵ�ַ��д��һ���֣���֧�ֶ���д�룩
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall GEN2_SecWrite(hComSocket CS, int Membank, unsigned char *WPassWord, int WAddr, int WCnt, unsigned char *WData, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			����ǩ��ȫ��
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//Membank:		�������ı�ǩ����USER 0x00, TID 0x01, EPC 0x02, Access Pwd 0x03�� Kill Pwd 0x04��
//LPassWord:	�����������루����Ϊ4���ֽڣ������������Ϊ0�����������ִ����ͨ�ı�ǩ������
//LockLevel:	�����ȼ���0 Ϊ�������� 1 Ϊ���������� 2 Ϊ��ȫ������ 3 Ϊȫ������
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall GEN2_SecLock(hComSocket CS, int Membank, unsigned char *LPassWord, int LockLevel, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			���ñ�ǩɸѡ���ܲ���
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//Membank:		��ɸѡ�ı�ǩ����Reserve 0x00, EPC 0x01, TID 0x02, USER 0x03��
//CAciton:		ɸѡ���ͣ�0 ��ǩѡ��ƥ��ģ�1 ��ǩѡ��ƥ��ģ�
//CAddr:		ƥ���ַ��λ��ַ������EPC�ĵ�һ���ֽڵ�λ��ַΪ0x20��
//CLen:			�Ƚϵ����ݳ���
//CData:		�Ƚϵ�����
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall GEN2_SecSelectConfig(hComSocket CS, int Membank, int CAciton, int CAddr, int CLen, unsigned char *CData, unsigned char ReaderAddr);

/************************************************DLL_�������**********************************************************/
//////////////////////////////////////////////////////////////////////////
//����:			�ӻ�����ȡ����ǩ����
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//GetCount:		�ɹ�ȡ���ı�ǩ����
//BData:		BufferData�ṹ����󣬾�������ο�BufferData�ṹ��˵��
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall BufferM_GetTagData(hComSocket CS, int &GetCount, BufferData BData[], unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			��ѯ�������е���������
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//TagCount:		��ǰ��д���������ڵı�ǩ��������
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall BufferM_QueryIDCount(hComSocket CS, unsigned char &TagCount, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			��ջ�����
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall BufferM_ClearBuffer(hComSocket CS, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			����ⲿ�洢��
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall BufferM_ClearExternalBuffer(hComSocket CS, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			���ⲿ�洢����ȡ��ǩ����
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//ETagCount:	��ǰ��д���ⲿ�洢���ڵı�ǩ��������
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall BufferM_GetExternalBufferCount(hComSocket CS, unsigned char &ETagCount, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			���ⲿ�洢����ȡ��ǩ����
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//BData:		BufferData�ṹ����󣬾�������ο�BufferData�ṹ��˵��
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall BufferM_GetExternalBufferData(hComSocket CS, BufferData *BData, unsigned char ReaderAddr);

/************************************************DLL_��������**********************************************************/
//////////////////////////////////////////////////////////////////////////
//����:			ͨ����ַ����Ŀ���豸��flash			
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//PAddr:		Ŀ���豸��flash�Ĳ�����ַ
//PLen:			���ò��������ݳ���
//PSData:		���õĲ������ݣ�����ΪPLen��
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ��		���������붨��
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Parameter_SetReader(hComSocket CS, unsigned char PAddr, unsigned char PLen, unsigned char *PSData, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:			ͨ����ַ��ѯĿ���豸��flash			
//����:
//CS:			���д����ͨ�ž���ṹ�壨ep:������ô���ͨ�ŷ�ʽ���ṹ���ڵĴ��ھ��Ϊ�򿪵Ĵ��ھ�������ھ����Ϊ0����NULL��
//PAddr:		Ŀ���豸��flash�Ĳ�����ַ
//PLen:			��ѯ���������ݳ���
//PGData:		��ѯ�Ĳ������ݣ�����ΪPLen��
//ReaderAddr:	��Ϊ��д����ͨ�ŵ�ַ��Ĭ��Ϊ255����0xFF��
//����ֵ��		���������붨��
//////////////////////////////////////////////////////////////////////////
/*-----ͨ����ַ��ѯĿ���豸��flash-----*/
int RFID_STANDARDPROTOCOL_API __stdcall Parameter_GetReader(hComSocket CS, unsigned char PAddr, unsigned char PLen, unsigned char *PGData, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//����:�ر���������
//����:
//Socket:		socket�׽���
//����ֵ:		���������붨��
//////////////////////////////////////////////////////////////////////////
/*-----У���ǩ��֤��������-----*/
int RFID_STANDARDPROTOCOL_API __stdcall CheckManagePW(hComSocket CS, char *MPW, unsigned char ReaderAddr);

/*-----����ͨѶ-----*/
int RFID_STANDARDPROTOCOL_API __stdcall Serial_SendAndRecv(HANDLE hCom, unsigned char *SendBuf, unsigned char *RecvBuf, int send_len);

/*-----����ͨѶ-----*/
int RFID_STANDARDPROTOCOL_API __stdcall Socket_SendAndRecv(SOCKET Socket, unsigned char * SendBuf, unsigned char *RecvBuf, int send_len);
#ifdef __cplusplus
}
#endif
