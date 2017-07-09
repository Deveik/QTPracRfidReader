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
//功能：连接句柄结构体
//参数说明：
//			hCom				串口连接句柄
//			sockClient			网口连接句柄
//////////////////////////////////////////////////////////////////////////
typedef struct RFID_STANDARDPROTOCOL_API hComSocket
{
	HANDLE hCom;
	SOCKET sockClient;
}hComSocket;

//////////////////////////////////////////////////////////////////////////
//功能：EPC GEN2标签多区域读取参数结构体
//参数说明：
//			MembankMask			标签区域掩码（Reserve 1， Epc 2，Tid 4，User 8）
//			ReserveWordPtr		Reserve区读取起始地址
//			ReserveWordCnt		Reserve区准备读取的数据长度（单位：字）	
//			EpcWordPtr			Epc区读取起始地址
//			EpcWordCnt			Epc区准备读取的数据长度（单位：字）	
//			TidWordPtr			Tid区读取起始地址
//			TidWordCnt			Tid区准备读取的数据长度（单位：字）	
//			UserWordPtr			User区读取起始地址
//			UserWordCnt			User区准备读取的数据长度（单位：字）	
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
//功能：EPC GEN2标签数据组成
//参数说明：
//			Len					数据长度（Ant的长度 + Data的长度）
//			Ant					天线号（1字节）
//			Data				数据缓冲区 
//////////////////////////////////////////////////////////////////////////
typedef struct RFID_STANDARDPROTOCOL_API BufferData
{
	int Len;
	int Ant;
	unsigned char Data[512];
}BufferData;

//////////////////////////////////////////////////////////////////////////
//功能：多标签写参数配置结构体
//参数说明：
//			MemBank				标签写入区域（Reserve 0， Epc 1，Tid 2，User 3）
//			StartAddr			待写入数据的起始地址
//			WriteLen			待写入数据长度
//			WriteValue			待写入数据
//////////////////////////////////////////////////////////////////////////
typedef struct RFID_STANDARDPROTOCOL_API MutiWriteParam
{
	int MemBank;				
	int StartAddr;
	int WriteLen;
	unsigned char WriteValue[20];
}MutiWriteParam;

//////////////////////////////////////////////////////////////////////////
//功能：时间结构体
//参数说明：
//			YearH				年高字节（(2014 >> 8 )& 0xFF）
//			YearL				年低字节（ 2014 & 0xFF）
//			Month				月份	
//			Day					日
//			Hour				时
//			Minute				分
//			Second				秒
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

/*-----------------------------------------------DLL_方法-------------------------------------------------------------*/
//ErrorCode		错误代码定义
#define SUCCESS 0					//操作成功
#define SENDERROR 101				//发送错误
#define RECVERROR 201				//接受错误
#define DATAERROR 301				//数据解析错误
#define CHECKERROR 401				//数据校验错误	
/************************************************DLL_通信方式******************************************************/
/************************TCP/IP************************/
//////////////////////////////////////////////////////////////////////////
//功能:			通过网口连接设备
//参数:
//Socket:		待打开的网口句柄
//IPAddress:	待打开的网口IP地址（ep: 192.168.1.120）
//Port:			待打开的网口端口（100 读写器内部端口固定的端口值，不可更改）
//返回值：		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Socket_ConnectSocket(SOCKET *Socket, char *IPAddress, int Port);

//////////////////////////////////////////////////////////////////////////
//功能:			关闭网口连接
//参数:
//Socket:		待关闭的网口句柄
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Socket_CloseSocket(SOCKET Socket);

/*************************串口************************/
//////////////////////////////////////////////////////////////////////////
//功能:			通过串口连接设备
//参数:
//hCom:			待打开的串口句柄
//ComName:		待打开的串口号（ep: COM3）
//Baud:			待打开的串口波特率（默认波特率为115200）
//返回值：		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Serial_OpenSeries(HANDLE *hCom, char *ComName, int Baud);

//////////////////////////////////////////////////////////////////////////
//功能:			关闭串口连接
//参数:
//hCom:			待关闭的串口句柄
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Serial_CloseSeries(HANDLE hCom);

/************************************************DLL_系统配置******************************************************/
//////////////////////////////////////////////////////////////////////////
//功能:			获取读写器版本号
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//major:		固件程序的主版本
//minor:		固件程序的次版本
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值：		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_GetLocatorVersion(hComSocket CS, unsigned char &major, unsigned char &minor, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			设置读写器波特率
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//Parameter:	待设置的波特率参数,默认波特率为115200,且不建议修改波特率设置,详细参数设置如下（ep: Parameter = 0x04）
//				0x00 9600bps
//				0x01 19200bps
//				0x02 38400bps
//				0x03 57600bps
//				0x04 115200bps
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值：		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_SetReaderBaud(hComSocket CS, unsigned char Parameter, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			复位读写器
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值：		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_ResetReader(hComSocket CS, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			设置读写器天线功率
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//Pwr:			待设置的功率值，对于此类产品，（Pwr大小:Pwr[4]），请将Pwr[0]设置为你需要修改的功率值，Pwr[1-3]请赋值为0
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值：		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_SetRfPower(hComSocket CS, unsigned char Pwr[], unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			查询读写器天线功率
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//Pwr:			天线功率查询缓冲区，对于此类产品，（Pwr大小:Pwr[4]），Pwr[0]为你查询的天线功率值，其他值为无效值
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值：		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_GetRfPower(hComSocket CS, unsigned char Pwr[], unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			设置读写器射频参数
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//Freq_num:		频率点数，（Freq_num = 0/非0）
//Freq_points:	频点(0/1/2 或者为900~930MHz范围内，以250kHz为步进的频率点索引)
//				（ep: 如果Freq_num = 0，则Freq_points的值只能为0/1/2，
//					  如果Freq_num != 0，则Freq_points为900~930MHz范围内，以250kHz为步进的频率点索引，参数Freq_points为（0- 120））
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值：		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_SetFreqPoint(hComSocket CS, int Freq_num, int Freq_points[], unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			查询读写器射频参数
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//Freq_num:		查询后返回的频率点数，（Freq_num = 0/非0）
//Freq_points:	查询后返回的频点(0/1/2 或者为900~930MHz范围内，以250kHz为步进的频率点索引)
//				（ep: 如果Freq_num = 0，则Freq_points的值只能为0/1/2，
//					  如果Freq_num != 0，则Freq_points为900~930MHz范围内，以250kHz为步进的频率点索引，参数Freq_points为（0- 120））
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值：		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_GetFreqPoint(hComSocket CS, int &Freq_num, int Freq_points[], unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			设置读写器天线工作状态
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//WorkAnt:		UHF读写器支持此命令
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值：		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_SetAntenna(hComSocket CS, int WorkAnt, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			查询读写器天线工作状态
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//WorkAnt:		UHF读写器支持此命令
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值：		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_GetAntenna(hComSocket CS, int &WorkAnt, int &AntStatus, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			查询读写器天线工作状态适用16通道
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//WorkAnt[]:	2个字节按位标识16个天线通道(ep: 11111111 11111111)
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值：		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_SetAntenna16(hComSocket CS, unsigned char *WorkAnt, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			查询读写器天线工作状态适用16通道
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//WorkAnt[]:	2个字节(整数)按位标识16个天线通道
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值：		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_GetAntenna16(hComSocket CS, int *WorkAnt, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			设置读写器载波抵消策略
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//Mode:			Mode = 0,策略为单卡（含少量多卡）快速模式   Mode != 0,为大量卡模式
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值：		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_SetSingleFastTagMode(hComSocket CS, unsigned char Mode, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			查询读写器载波抵消策略态
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//Mode:			Mode = 0,策略为单卡（含少量多卡）快速模式   Mode != 0,为大量卡模式
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值：		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_GetSingleFastTagMode(hComSocket CS, unsigned char &Mode, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			设置读写器测试模式
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//TestMode:		参数范围（0x00 打开功放，0x01 关闭功放，0x02 天线校准）
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值：		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_SetTestMode(hComSocket CS, unsigned char TestMode, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			设置读写器IO口电平状态
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//Num:			IO口序号，范围（0、1、2，其中2为继电器）
//Level:		输出电平，参数值意义（1为高电平，0为低电平）
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值：		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_SetOutPort(hComSocket CS, unsigned char Num, unsigned char Level, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			获取读写器IO口电平状态
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//Num:			IO口序号，范围（0、1、2，其中2为继电器）
//Level:		输出电平，参数值意义（1为高电平，0为低电平）
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值：		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_GetInPort(hComSocket CS, unsigned char InPortNum, unsigned char &InPortLevel, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			设置读写器网口参数
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//IPAddr:		IP地址（192.168.1.120）
//MaskCode:		掩码（255.255.255.0）
//GateWay:		网关（192.168.1.1）
//InternetPort:	端口（固定为100，不可修改）
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值：		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_SetIntrnetAccess(hComSocket CS, unsigned char IPAddr[], unsigned char MaskCode[], unsigned char GateWay[], unsigned char InternetPort[], unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			查询读写器网口参数
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//IPAddr:		IP地址（192.168.1.120）
//MaskCode:		掩码（255.255.255.0）
//GateWay:		网关（192.168.1.1）
//InternetPort:	端口（固定为100，不可修改）
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值：		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_GetIntrnetAccess(hComSocket CS, unsigned char IPAddr[], unsigned char MaskCode[], unsigned char GateWay[], unsigned char InternetPort[], unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			设置读写器的实时时钟
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//RTime:		读写器时间结构体，请参考前面时间结构体的具体定义
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值：		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_SetReaderTime(hComSocket CS, ReaderTime RTime, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			获取读写器的实时时钟
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//RTime:		读写器时间结构体，请参考前面时间结构体的具体定义
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值：		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Config_GetReaderTime(hComSocket CS, ReaderTime &RTime, unsigned char ReaderAddr);


/************************************************DLL_ISO18000-6B标签操作***********************************************/
//////////////////////////////////////////////////////////////////////////
//功能:			Iso18000多标签识别
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//TagCount:		标签识别操作完成后返回的本次成功识别的标签数量（标签数据存入读写器缓存区）
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall ISO_MultiTagIdentify(hComSocket CS, int &TagCount, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			Iso18000多标签读取
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//RAddr:		待读取的标签数据的起始地址（读取每张标签由起始地址开始的8字节数据）
//RCount:		读取完成后返回本次成功读取到的标签数量（标签数据存入读写器缓存区）
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall ISO_MultiTagRead(hComSocket CS, int RAddr, int &RCount, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			单标签读取
//参数:			
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//RAddr:		待读取的标签数据的起始地址（读取每张标签由起始地址开始的8字节数据）
//RData:		读取完成后返回本次成功读取到的标签数据
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall ISO_TagRead(hComSocket CS, unsigned char RAddr, unsigned char *RData, unsigned char ReaderAddr);
int RFID_STANDARDPROTOCOL_API __stdcall ISO_TagRead_MultiBytes(hComSocket CS, int RAddr, unsigned char *RData, int iLen, unsigned char ReaderAddr);
//////////////////////////////////////////////////////////////////////////
//功能:			单标签单字节写入
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//WAddr:		待写入的标签数据的起始地址
//WData:		待写入标签的数据
//DataLen:		待写入标签的数据长度（字节为单位，此处支持多字节写入）
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall ISO_TagWrite(hComSocket CS, int WAddr, unsigned char *WData, int DataLen, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			单标签通过UID读取标签数据
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//UID:			已知的标签的ID号（8个字节）
//RAddr:		待读取的标签数据的起始地址（读取每张标签由起始地址开始的8字节数据）
//RData:		读取完成后返回本次成功读取到的标签数据（读写器返回9个字节的数据，第一个字节为天线号，剩下八个字节为数据）
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall ISO_TagReadWithUID(hComSocket CS, unsigned char *UID, int RAddr, unsigned char *RData, unsigned char ReaderAddr);
int RFID_STANDARDPROTOCOL_API __stdcall ISO_TagReadWithUID_MultiBytes(hComSocket CS, unsigned char *UID, int RAddr, unsigned char *RData, int iLen, unsigned char ReaderAddr);
//////////////////////////////////////////////////////////////////////////
//功能:			单标签通过UID写入标签数据
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//UID:			已知的标签的ID号（8个字节）
//WAddr:		待写入的标签数据的起始地址
//WData:		待写入标签的数据
//DataLen:		待写入标签的数据长度（字节为单位，此处支持多字节写入）
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall ISO_TagWriteWithUID(hComSocket CS, unsigned char *UID, int WAddr, unsigned char *WData, int DataLen, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			单标签数据锁设置
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//LAddr:		待锁定的标签地址
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall ISO_SetTagLock(hComSocket CS, int LAddr, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			单标签数据锁查询
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//QAddr:		待查询的标签地址
//LStatus:		锁定状态（0为未锁定， 1为锁定）
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall ISO_QueryTagLock(hComSocket CS, int QAddr, int &LStatus, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			单标签通过UID数据锁设置
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//UID:			已知的标签的ID号（8个字节）
//LAddr:		待锁定的标签地址
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall ISO_SetTagLockWithUID(hComSocket CS, unsigned char *UID, int LAddr, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			单标签通过UID数据锁查询
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//UID:			已知的标签的ID号（8个字节）
//QAddr:		待查询的标签地址
//LStatus:		锁定状态（0为未锁定， 1为锁定）
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall ISO_QueryTagLockWithUID(hComSocket CS, unsigned char *UID, int QAddr, int &LStatus, unsigned char ReaderAddr);

/************************************************DLL_EPC GEN2标签操作命令**********************************************/
//////////////////////////////////////////////////////////////////////////
//功能:			多标签盘询
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//TagCount:		标签识别操作完成后返回的本次成功识别的标签数量（标签数据存入读写器缓存区）
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall GEN2_MultiTagInventory(hComSocket CS, int &TagCount, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			多标签任意区域数据群读
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//WpALen:		WordptrAndLength结构体对象，具体意义参考WordptrAndLength结构体说明
//RCount:		标签成功执行标签读取操作后返回读到的标签数量（标签数据存入读写器缓存区）
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall GEN2_MultiTagRead(hComSocket CS, WordptrAndLength WpALen, int &RCount, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			多标签写入
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//MutiWP:		MutiWriteParam结构体对象，具体意义参考MutiWriteParam结构体说明
//WCount:		标签成功执行标签写入操作后返回写入的标签数量（标签数据存入读写器缓存区）
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall GEN2_MultiTagWrite(hComSocket CS, MutiWriteParam MutiWP, int &WCount, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			单标签安全销毁
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//KPassWord:	销毁标签密码（长度为4个字节）
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall GEN2_KillTag(hComSocket CS, unsigned char *KPassWord, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			单标签安全读取
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//Membank:		读取访问的标签区域（Reserve 0x00, EPC 0x01, TID 0x02, USER 0x03）
//RPassWord:	读取操作密码（长度为4个字节，如果输入密码为0，则忽略密码执行普通的标签读取）
//RAddr:		待读取标签的首地址
//RCnt:			待读取的字数（1个字 == 2个字节）
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall GEN2_SecRead(hComSocket CS, int Membank, unsigned char *RPassWord, int RAddr, int RCnt, unsigned char *RData, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			单标签安全写入
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//Membank:		写入访问的标签区域（Reserve 0x00, EPC 0x01, TID 0x02, USER 0x03）
//WPassWord:	写入操作密码（长度为4个字节，如果输入密码为0，则忽略密码执行普通的标签读取）
//WAddr:		待写入标签的字地址（0 ~ 5）
//WCnt:			待写入的字数（1个字 == 2个字节）
//WData:		待写入标签的数据（在指定的地址下写入一个字，可支持多字写入）
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall GEN2_SecWrite(hComSocket CS, int Membank, unsigned char *WPassWord, int WAddr, int WCnt, unsigned char *WData, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			单标签安全锁
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//Membank:		待锁定的标签区域（USER 0x00, TID 0x01, EPC 0x02, Access Pwd 0x03， Kill Pwd 0x04）
//LPassWord:	锁定操作密码（长度为4个字节，如果输入密码为0，则忽略密码执行普通的标签锁定）
//LockLevel:	锁定等级（0 为不锁定， 1 为永久锁定， 2 为安全锁定， 3 为全锁定）
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall GEN2_SecLock(hComSocket CS, int Membank, unsigned char *LPassWord, int LockLevel, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			配置标签筛选功能参数
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//Membank:		待筛选的标签区域（Reserve 0x00, EPC 0x01, TID 0x02, USER 0x03）
//CAciton:		筛选类型（0 标签选择匹配的，1 标签选择不匹配的）
//CAddr:		匹配地址（位地址，比如EPC的第一个字节的位地址为0x20）
//CLen:			比较的数据长度
//CData:		比较的数据
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall GEN2_SecSelectConfig(hComSocket CS, int Membank, int CAciton, int CAddr, int CLen, unsigned char *CData, unsigned char ReaderAddr);

/************************************************DLL_缓存管理**********************************************************/
//////////////////////////////////////////////////////////////////////////
//功能:			从缓存中取出标签数据
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//GetCount:		成功取出的标签数量
//BData:		BufferData结构体对象，具体意义参考BufferData结构体说明
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall BufferM_GetTagData(hComSocket CS, int &GetCount, BufferData BData[], unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			查询缓存区中的数据组数
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//TagCount:		当前读写器缓存区内的标签数据条数
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall BufferM_QueryIDCount(hComSocket CS, unsigned char &TagCount, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			清空缓存区
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall BufferM_ClearBuffer(hComSocket CS, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			清空外部存储器
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall BufferM_ClearExternalBuffer(hComSocket CS, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			从外部存储器获取标签数量
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//ETagCount:	当前读写器外部存储器内的标签数据条数
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall BufferM_GetExternalBufferCount(hComSocket CS, unsigned char &ETagCount, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			从外部存储器获取标签数据
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//BData:		BufferData结构体对象，具体意义参考BufferData结构体说明
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall BufferM_GetExternalBufferData(hComSocket CS, BufferData *BData, unsigned char ReaderAddr);

/************************************************DLL_辅助函数**********************************************************/
//////////////////////////////////////////////////////////////////////////
//功能:			通过地址设置目标设备的flash			
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//PAddr:		目标设备的flash的参数地址
//PLen:			设置参数的数据长度
//PSData:		设置的参数数据（长度为PLen）
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值：		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
int RFID_STANDARDPROTOCOL_API __stdcall Parameter_SetReader(hComSocket CS, unsigned char PAddr, unsigned char PLen, unsigned char *PSData, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:			通过地址查询目标设备的flash			
//参数:
//CS:			与读写器的通信句柄结构体（ep:如果采用串口通信方式，结构体内的串口句柄为打开的串口句柄，网口句柄则为0或者NULL）
//PAddr:		目标设备的flash的参数地址
//PLen:			查询参数的数据长度
//PGData:		查询的参数数据（长度为PLen）
//ReaderAddr:	此为读写器的通信地址（默认为255或者0xFF）
//返回值：		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
/*-----通过地址查询目标设备的flash-----*/
int RFID_STANDARDPROTOCOL_API __stdcall Parameter_GetReader(hComSocket CS, unsigned char PAddr, unsigned char PLen, unsigned char *PGData, unsigned char ReaderAddr);

//////////////////////////////////////////////////////////////////////////
//功能:关闭网口连接
//参数:
//Socket:		socket套接字
//返回值:		详见错误代码定义
//////////////////////////////////////////////////////////////////////////
/*-----校验标签认证管理密码-----*/
int RFID_STANDARDPROTOCOL_API __stdcall CheckManagePW(hComSocket CS, char *MPW, unsigned char ReaderAddr);

/*-----串口通讯-----*/
int RFID_STANDARDPROTOCOL_API __stdcall Serial_SendAndRecv(HANDLE hCom, unsigned char *SendBuf, unsigned char *RecvBuf, int send_len);

/*-----网口通讯-----*/
int RFID_STANDARDPROTOCOL_API __stdcall Socket_SendAndRecv(SOCKET Socket, unsigned char * SendBuf, unsigned char *RecvBuf, int send_len);
#ifdef __cplusplus
}
#endif
