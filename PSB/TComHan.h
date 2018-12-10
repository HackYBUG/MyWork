//---------------------------------------------------------------------------

#ifndef TComHanH
#define TComHanH
//---------------------------------------------------------------------------
#include "TSerialPort.h"
//---------------------------------------------------------------------------

struct PsbType
{
	double volt1;
	double volt2;
	double volt3;
	double volt4;
	double volt5;
	double volt6;
	double volt7;
	//24VµÁ—πÕ®µ¿

};

class TComIT8500
{
public:
	TComIT8500(int port);
	~TComIT8500();


	 void __fastcall SendEleDate(int eleValue);
private:
	TSerialPort *c_SerialPort;

};


#endif
