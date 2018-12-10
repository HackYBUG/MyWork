//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SetIniFrm.h"
#include "funs_Public.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmSetIni *frmSetIni;
//---------------------------------------------------------------------------
__fastcall TfrmSetIni::TfrmSetIni(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetIni::FormShow(TObject *Sender)
{
	String strIp = "";
	String strPort = "";
	String strLen = "";
	ReadIniFile(strIp,strPort,strLen);

	edt_IP->Text =  strIp;
	edt_Port->Text = strPort;
	cbb_SingleLen->Text = strLen;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetIni::btn_CancelClick(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSetIni::btn_OKClick(TObject *Sender)
{
	String strIp = edt_IP->Text;
	String strPort = edt_Port->Text;
	String strLen = cbb_SingleLen->Text;
	WriteIniFile(strIp,strPort,strLen);
    this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetIni::cbb_SingleLenKeyPress(TObject *Sender, System::WideChar &Key)

{
	TComboBox *cbb = dynamic_cast<TComboBox *>(Sender);
	if(Key >= 0)Key = 0;
}
//---------------------------------------------------------------------------
