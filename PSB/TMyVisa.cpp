//---------------------------------------------------------------------------

#pragma hdrstop

#include "TMyVisa.h"
#include "visa.h"
#include <System.Classes.hpp>
#include<string>
//---------------------------------------------------------------------------
#pragma package(smart_init)




void __fastcall MyVisa::InitializationUSB()
{
	ViChar buffer[VI_FIND_BUFLEN];
	memset(buffer , 0 ,VI_FIND_BUFLEN);
	ViRsrc matches = buffer;
	ViUInt32 nmatches;

	ViStatus error;
	ViFindList list;

	 /*��VISA��Դ������*///defaultRMΪ�õ���VISA��Դ���������
	 error =  viOpenDefaultRM(&defaultRM);
	if(error != VI_SUCCESS)
	{
		//MessagePopup("Error","Open VISA Resource Manager Error!");
		return ;
	}
	viFindRsrc(defaultRM , "USB?*" , &list , &nmatches , matches);
	error = viOpen(defaultRM , matches , VI_NULL , VI_NULL , &vi);//����
	if(error != VI_SUCCESS){
//		"Open Instrument Error!"
		return  ;
	}
//	 /*��ȡ����ģ����룬��������������ʱʱ��Ϊ2000����*/
//	int moduleID = 0;
//	viGetAttribute (vi, VI_ATTR_MODEL_CODE, &moduleID);
//	viSetAttribute (vi, VI_ATTR_TMO_VALUE, 2000);
}

bool __fastcall MyVisa::InitializationRS232(int viPort)
{
	char c[8] = {0};
	itoa(viPort,c,10);
	std::string Viname ="ASRL::INSTR";
	Viname.insert(4,c);
	ViConstRsrc name =  Viname.c_str();

	ViStatus error;
	error = viOpenDefaultRM(&defaultRM);
	error = viOpen(defaultRM , name , VI_NULL , VI_NULL , &vi);
	if(error != VI_SUCCESS){
		return false ;
	}
	return true;
}


void __fastcall MyVisa::Send(char *senBuf)
{
	viPrintf(vi , senBuf);
}
void __fastcall MyVisa::Receive(char *recBuf)
{
	viScanf(vi,"%t\n",&recBuf);
}

void __fastcall MyVisa::SetIPDVOLTage(int value)
{
	char c[8] = {0};
	itoa(value,c,10);
	std::string tempstr =  "VOLT:IMM  \n";//"VOLTage 43.00\n"
	tempstr.insert(9,c);
	char pSend[250] = {0} ;
	//���õ�ѹ
	memcpy(pSend,tempstr.c_str(),tempstr.length());
	Send(pSend);
	//���õ���
	Sleep(100);
	memcpy(pSend,"CURR 1\n",sizeof("CURR 1\n"));
	Send(pSend);
}

void __fastcall MyVisa::SetIT8500(int value)
{
//	ѡ���ص�����ģʽ
	char pSend[250] = {"MODE CURRent\n"};
	Send(pSend);
	//���� CC ģʽ�µ��趨������
	memcpy(pSend,"CURR 4\n",sizeof("CURR 4\n"));
	Send(pSend);
}

void __fastcall MyVisa::SendAndRec()
{
	char pSend[250] = {"*IDN?\n"};

	viPrintf(vi , pSend);
	Sleep(100);
	char pReceive[250] = {0};
	viScanf(vi,"%t\n",&pReceive);
}
