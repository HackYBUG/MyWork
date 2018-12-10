//---------------------------------------------------------------------------

#ifndef TSerialPortH
#define TSerialPortH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <tchar.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

//---------------------------------------------------------------------------
#define ARDUINO_WAIT_TIME 2000
#define MAX_DATA_LENGTH 17
//#define FC_DTRDSR       0x01
//#define FC_RTSCTS       0x02
//#define FC_XONXOFF      0x04
//#define ASCII_BEL       0x07
//#define ASCII_BS        0x08
//#define ASCII_LF        0x0A
//#define ASCII_CR        0x0D
//#define ASCII_XON       0x11
//#define ASCII_XOFF      0x13
//---------------------------------------------------------------------------


class TSerialPort
{
public:
	TSerialPort();
	~TSerialPort();

	bool Open(const char *pName,int nBaud);
	bool OpenEx(const char *pName,int nBaud,int databits,float stopbits);
	bool PortClose (void);
	bool SendData( const char *buffer, int size );
	int ReadData(char *data);
    bool ClearData(int flag);
	bool m_bOpened;
	HANDLE m_hIDComDev;
	DWORD dwError;
	DWORD dwThreadID;

};

#endif
