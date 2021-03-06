//---------------------------------------------------------------------------

#ifndef TMyVisaH
#define TMyVisaH
//---------------------------------------------------------------------------
#include "visa.h"

/*
*程控电源切换输出43V和160V电压。

*/
class MyVisa
{
public:
	MyVisa(){
		vi = NULL;
		defaultRM = NULL;
	}
	~MyVisa(){
		if(vi != NULL) viClose(vi); /*关闭仪器句柄和VISA资源管理器*/
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
