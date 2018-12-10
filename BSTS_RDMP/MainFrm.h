//---------------------------------------------------------------------------

#ifndef MainFrmH
#define MainFrmH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "TMySocket.h"
#include "TCanvasSpectrum.h"
#include "TControlMove.h"
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------



class TfrmMain : public TForm
{
__published:	// IDE-managed Components
	TPanel *pnl_Canves;
	TImage *img_Frame;
	TPanel *pnl_Domain;
	TGroupBox *grpbx1;
	TLabel *lbl_MaxDistance;
	TGroupBox *grpbx2;
	TLabel *lbl_MoveDistance;
	TLabel *lbl_Rate;
	TEdit *edt_MoveDistance;
	TEdit *edt_MaxDistance;
	TComboBox *cbb_Rate;
	TButton *btn_Send;
	TButton *btn_Start;
	TLabel *lbl_Aspect;
	TComboBox *cbb_Aspect;
	TLabel *lbl_bAspect;
	TComboBox *cbb_bAspect;
	TTimer *tmr_B;
	TMainMenu *mnmn1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *mntmN3;
	TStatusBar *StatusBar1;
	TMenuItem *mntmN4;
	TButton *btn_pause;
	TMenuItem *mntmN5;
	TButton *btn_stop;
	TLabel *lbl1;
	TComboBox *cbb_bRate;
	TMenuItem *mntmN6;
	TMenuItem *mntmN7;
	TMenuItem *N3;
	TMenuItem *mntmN_Add;
	TMenuItem *mntmN_Delete;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btn_SendClick(TObject *Sender);
	void __fastcall tmr_BTimer(TObject *Sender);
	void __fastcall btn_StartClick(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall mntmN3Click(TObject *Sender);

	void __fastcall GetSpectrumData();
	void __fastcall MainDrawSpectrumData();
	void __fastcall edt_MaxDistanceKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall cbb_bAspectKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall mntmN4Click(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall btn_pauseClick(TObject *Sender);
	void __fastcall mntmN5Click(TObject *Sender);
	void __fastcall btn_stopClick(TObject *Sender);
	void __fastcall mntmN6Click(TObject *Sender);
	void __fastcall mntmN7Click(TObject *Sender);
	void __fastcall mntmN_AddClick(TObject *Sender);
	void __fastcall img_FrameMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall img_FrameMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall img_FrameMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);

private:
	bool __fastcall GetMousePos(TButton *btn);
private:	// User declarations
	ClientSocket *myClient;
	vector<TSpectrumType> spectrumData;
	TSpectrumType tempSpectrum;
	vector<T> moreSpectrumData;
public:
	TControlMove *controlmove;
private:
	String strIp ;
	String strPort;
	String strLen;
	int m_Rate;
	bool m_ppyStatus;     //ÆµÆ×ÒÇ×´Ì¬
	bool m_SerialStatus;  //´®¿Ú×´Ì¬

	bool m_MouseStaus; //Êó±ê°´ÏÂµÄ×´Ì¬
	TCanvasSpectrum* k_cSpectrum ;//Êó±ê»¬¶¯ÊÇ»­Í¼
	TPoint posXY;
public:
	int m_MaxDistance;
	int m_Aspect;
	int m_bRate;
	int m_timeLen;
	int  flagCount;
	int ABSCISSASINGLE ;
public:		// User declarations
	__fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
