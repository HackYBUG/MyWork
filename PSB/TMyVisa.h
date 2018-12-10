//---------------------------------------------------------------------------

#ifndef TMyVisaH
#define TMyVisaH
//---------------------------------------------------------------------------
#include "visa.h"

/*
*�̿ص�Դ�л����43V��160V��ѹ��

*/
class MyVisa
{
public:
	MyVisa(){
		vi = NULL;
		defaultRM = NULL;
	}
	~MyVisa(){
		if(vi != NULL) viClose(vi); /*�ر����������VISA��Դ������*/
		if(defaultRM != NULL) viClose(defaultRM);
	}
	void __fastcall InitializationUSB();
	bool __fastcall InitializationRS232(int viPort);

	void __fastcall SetIPDVOLTage(int value);
	void __fastcall SetIT8500(int value);

private:
	void __fastcall SendAndRec();
	void __fastcall Send(char *senBuf);
	void __fastcall Receive(char *recBuf);

private:
	ViSession vi;
	ViSession  defaultRM;
};





#endif