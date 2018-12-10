//---------------------------------------------------------------------------

#ifndef SetIniFrmH
#define SetIniFrmH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TfrmSetIni : public TForm
{
__published:	// IDE-managed Components
	TEdit *edt_IP;
	TEdit *edt_Port;
	TLabel *lbl1;
	TLabel *lbl2;
	TButton *btn_OK;
	TButton *btn_Cancel;
	TLabel *lbl3;
	TComboBox *cbb_SingleLen;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btn_CancelClick(TObject *Sender);
	void __fastcall btn_OKClick(TObject *Sender);
	void __fastcall cbb_SingleLenKeyPress(TObject *Sender, System::WideChar &Key);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmSetIni(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSetIni *frmSetIni;
//---------------------------------------------------------------------------
#endif
