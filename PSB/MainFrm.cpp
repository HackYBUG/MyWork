//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainFrm.h"
#include "TMyVisa.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
	: TForm(Owner)
{
	ReadIniFile(p_IniData);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btn1Click(TObject *Sender)
{
	MyVisa *myVisa = new MyVisa();
	myVisa->InitializationRS232(p_IniData.i_IPD);
//	myVisa->InitializationUSB();
	myVisa->SetIPDVOLTage(100);

	delete myVisa;
}
//---------------------------------------------------------------------------
#include "TComHan.h"
void __fastcall TfrmMain::btn2Click(TObject *Sender)
{
	TComIT8500 *comit8500 = new TComIT8500(p_IniData.i_IPD);
	comit8500 ->SendEleDate(0);
	delete comit8500;
}
//---------------------------------------------------------------------------

