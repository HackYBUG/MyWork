//---------------------------------------------------------------------------

#pragma hdrstop

#include "TComHan.h"
#include <string>
//---------------------------------------------------------------------------
#pragma package(smart_init)

TComIT8500::TComIT8500(int port)
{
	char c[8] = {0};
	itoa(port,c,10);
	std::string temport ="COM";
	temport.insert(3,c);
	c_SerialPort = new  TSerialPort();
	c_SerialPort->OpenEx(temport.c_str(),9600,8,1);
}

TComIT8500::~TComIT8500()
{
	if(c_SerialPort->m_bOpened)
		c_SerialPort->PortClose();
	delete c_SerialPort;
}


void __fastcall TComIT8500::SendEleDate(int eleValue)
{
	 char pSend[250] = {"VOLTage 43.00\n"}; //设定通道电压

	 c_SerialPort->SendData(pSend,MAX_DATA_LENGTH);
}
