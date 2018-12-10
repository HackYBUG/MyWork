//---------------------------------------------------------------------------

#pragma hdrstop

#include "TSerialPort.h"
#include <iostream>
//---------------------------------------------------------------------------
#pragma package(smart_init)


TSerialPort::TSerialPort()
{
	m_hIDComDev = NULL;
	m_bOpened = false;
}

TSerialPort::~TSerialPort()
{
	PortClose();
}

bool TSerialPort::Open( const char *pName, int nBaud )
{
	if( m_bOpened ) return( true );
	try
	{
	DCB dcb = {0};
	TCHAR szPort[255] = {0};
	swprintf(szPort,L"\\\\.\\%hs",pName);
	m_hIDComDev = CreateFile(szPort,
							GENERIC_READ | GENERIC_WRITE,
							0,
							NULL,
							OPEN_EXISTING,
							FILE_ATTRIBUTE_NORMAL,
							0);

	if( m_hIDComDev == INVALID_HANDLE_VALUE)
	{
//		DWORD dwError=GetLastError();
		//::MessageBox(0,_T("打开端口出错！请确定端口设备的使用情况后关闭重试."),_T("ERROR!"),MB_OK );
		return( false );
	}
	else
	{
		if (GetCommState(m_hIDComDev, &dcb))
		 {
			dcb.BaudRate = nBaud;
			dcb.ByteSize = 8;
			dcb.StopBits = ONESTOPBIT;
			dcb.Parity = NOPARITY;
			dcb.fDtrControl = DTR_CONTROL_ENABLE;

			if (SetCommState(m_hIDComDev, &dcb))
			{
				COMMTIMEOUTS cto = {0};
				cto.ReadIntervalTimeout = MAXDWORD;
				cto.ReadTotalTimeoutConstant = 0;
				cto.ReadTotalTimeoutMultiplier = 0;
				cto.WriteTotalTimeoutConstant = 2000;
				cto.WriteTotalTimeoutMultiplier = 50;
				SetCommTimeouts(m_hIDComDev,&cto);

				m_bOpened = true;
				PurgeComm(m_hIDComDev, PURGE_RXCLEAR | PURGE_TXCLEAR);
				Sleep(ARDUINO_WAIT_TIME);
			}
		}
	}
	}
    catch(...){}
	return( m_bOpened );
}

bool TSerialPort::OpenEx(const char *pName,int nBaud,int databits,float stopbits)
{
	if( m_bOpened ) return( true );
	try
	{
	DCB dcb = {0};
	TCHAR szPort[255] = {0};
	swprintf(szPort,L"\\\\.\\%hs",pName);
	m_hIDComDev = CreateFile(szPort,
							GENERIC_READ | GENERIC_WRITE,  /*允许读写模式*/
							0,
							NULL,
							OPEN_EXISTING,
							FILE_ATTRIBUTE_NORMAL,   /*|FILE_FLAG_OVERLAPPED同步异步模式均支持*/
							0);

	if( m_hIDComDev == INVALID_HANDLE_VALUE)
	{
//		DWORD dwError=GetLastError();
		//::MessageBox(0,_T("打开端口出错！请确定端口设备的使用情况后关闭重试."),_T("ERROR!"),MB_OK );
		return( false );
	}
	else
	{
		if (GetCommState(m_hIDComDev, &dcb))
		 {
			dcb.BaudRate = nBaud; 			//波特率
			dcb.ByteSize = databits&0x08; 	// 通信字节位数，4—8
			if(stopbits==1)
			{
				dcb.StopBits = ONESTOPBIT; //(ONESTOPBIT 1,ONE5STOPBITS 1.5, TWOSTOPBITS 2)
			}
			else if(stopbits ==1.5)
			{
				dcb.StopBits = ONE5STOPBITS;
			}
			else if(stopbits==2)
			{
				dcb.StopBits = TWOSTOPBITS;
			}
			dcb.Parity = NOPARITY;
			dcb.fDtrControl = DTR_CONTROL_ENABLE;

			if (SetCommState(m_hIDComDev, &dcb))
			{
				COMMTIMEOUTS cto = {0};
				cto.ReadIntervalTimeout = MAXDWORD; //读间隔超时
				cto.ReadTotalTimeoutConstant = 0;     //读时间系数
				cto.ReadTotalTimeoutMultiplier = 0;   //读时间常量
				cto.WriteTotalTimeoutConstant = 2000;  // 写时间系数
				cto.WriteTotalTimeoutMultiplier = 50;  //写时间常量
				SetCommTimeouts(m_hIDComDev,&cto);

				SetCommMask(m_hIDComDev,EV_RXCHAR);
				m_bOpened = true;
				PurgeComm(m_hIDComDev, PURGE_RXCLEAR | PURGE_TXCLEAR);
				Sleep(ARDUINO_WAIT_TIME);
			}
		}
	}
	 }
     catch(...){}
	return( m_bOpened );
}

//======================================
bool TSerialPort::PortClose (void)
{
	if (m_bOpened)
	{
		// Close the communication port.
		if (CloseHandle (m_hIDComDev))
		{
			//::MessageBox (NULL,_T("正常退出，谢谢使用!"),_T("RIGHT"),MB_OK);   }
			m_bOpened = false;
		}
	}
	else
	{
		return(false);
	}
	return( true );
}
bool TSerialPort::ClearData(int flag)
{
	bool result = false;
	Sleep(16);
	switch(flag)
	{
	case 0:
		result = PurgeComm(m_hIDComDev,PURGE_RXCLEAR | PURGE_TXCLEAR); //输入输出
		break;
	case 1:
		result = PurgeComm(m_hIDComDev,PURGE_RXCLEAR );//输入缓存
		break;
	case 2:
		result = PurgeComm(m_hIDComDev,PURGE_RXCLEAR );  //输出缓存
		break;
	}

	return result;
}
bool TSerialPort::SendData( const char *buffer, int size )
{
	DWORD dwNumByteWritten;
	bool result = false;
	try{
	result = WriteFile(m_hIDComDev,buffer,size,&dwNumByteWritten,NULL);
	}
	catch(...){
		DWORD dwError = GetLastError();
	}
	return result;
}

int TSerialPort::ReadData( char *data )
{
	try
	{
	DWORD dwBytesTransferred;
    COMSTAT dwCommModemStatus;
	int len = 0;

	ClearCommError(m_hIDComDev, &dwError, &dwCommModemStatus);

	if(dwCommModemStatus.cbInQue>0)
	{
		if(dwCommModemStatus.cbInQue > MAX_DATA_LENGTH)
		{
			len = MAX_DATA_LENGTH;
		}
		else
		{
			len = dwCommModemStatus.cbInQue;
		}
	}

	if (ReadFile(m_hIDComDev, data, len, &dwBytesTransferred, NULL)) return dwBytesTransferred;
	}
    catch(...){}

	return 0;
}

