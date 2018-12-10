//---------------------------------------------------------------------------

#ifndef TMyThreadH
#define TMyThreadH
//---------------------------------------------------------------------------
#include<System.classes.hpp>
//---------------------------------------------------------------------------
#define  MAINRATE    1000    //¹Ì¶¨ÆµÂÊ

class TMyThread : public TThread
{
public:
	__fastcall TMyThread();

	bool flagRun;
private:
	void __fastcall Execute();

	void __fastcall MainCanvasTime();

};



#endif
