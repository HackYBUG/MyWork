//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainFrm.h"
#include<time.h>
#include <process.h>
#include "TMyExcel.h"
#include "funs_Public.h"
#include "TMyThread.h"
#include "SetIniFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
TMyThread *mythread;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
	: TForm(Owner)
{
	m_ppyStatus = false;
	m_SerialStatus = false;


	 this->DoubleBuffered = true;

}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormShow(TObject *Sender)
{
//	HANDLE handle = (HANDLE)_beginthreadex(NULL,0,ServerFun,NULL,0,NULL);
	mythread = new TMyThread();

	ReadIniFile(strIp,strPort,strLen);
	ABSCISSASINGLE = StrToInt(strLen);

	MainDrawSpectrumData();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormResize(TObject *Sender)
{
	static int width = 0;
	if(0 != width && width != this->Width){
		MainDrawSpectrumData();
	}
	width = this->Width;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(mythread) mythread->Terminate();

	if(controlmove){
	delete controlmove;
	controlmove = NULL;
	}
	if(myClient){
	delete myClient;
	myClient = NULL;
	}
}
//***************************************************************************



//---------------------------------------------------------------------------

//打开
void __fastcall TfrmMain::mntmN6Click(TObject *Sender)
{//频谱仪
	//连接频谱仪
	if(!m_ppyStatus){
		myClient = new ClientSocket();
		if(!myClient->ConnectServer(((AnsiString)strIp).c_str()) ){
		   delete myClient;
		   myClient = NULL;
		   Application->MessageBoxW(L"频谱仪打开失败。",L"提示",0);
		   return;
		}
		myClient->Initialization();
		m_ppyStatus = true;
		if(m_SerialStatus)
			StatusBar1->Panels->Items[0]->Text = "频谱仪连接|串口连接";
		else
			StatusBar1->Panels->Items[0]->Text = "频谱仪连接";
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mntmN7Click(TObject *Sender)
{ //串口
	if(!m_SerialStatus)  {
		controlmove = new TControlMove();
		if( !controlmove->ConnectCom(((AnsiString)strPort).c_str())) {
			delete controlmove;
			controlmove = NULL;
			Application->MessageBoxW(L"串口打开失败。",L"提示",0);
			return;
		}
        m_SerialStatus = true;
		if(m_ppyStatus)
			StatusBar1->Panels->Items[0]->Text = "频谱仪连接|串口连接";
		else
			StatusBar1->Panels->Items[0]->Text = "串口连接";
	}
}
//---------------------------------------------------------------------------

//关闭
void __fastcall TfrmMain::N2Click(TObject *Sender)
{

	if(tmr_B->Enabled == true || mythread->flagRun == true) {
		Application->MessageBoxW(L"正在运行中。",L"提示",0);
		return;
	}
	if(m_ppyStatus){

		if(myClient){
		delete myClient;
		myClient = NULL;
		}
		mntmN4Click(this);
		m_ppyStatus = false;
	}

	if(m_SerialStatus){
		if(controlmove){
		delete controlmove;
		controlmove = NULL;
		}
		m_SerialStatus = false;
	}

	StatusBar1->Panels->Items[0]->Text = "关闭";
}
//---------------------------------------------------------------------------
//导出
void __fastcall TfrmMain::mntmN3Click(TObject *Sender)
{
	if(spectrumData.size() == 0) {
		Application->MessageBoxW(L"内容为空。",L"提示",0);
		return ;
    }
	TSaveDialog* psavedg = new TSaveDialog(this);

	if(psavedg->Execute())
	{
		String filePath = psavedg->FileName;

		TBasicData bData ;
		memset(&bData,0,sizeof(TBasicData));
		MyExcel *myExcel = new MyExcel();
		//排序
		sort(spectrumData.begin(),spectrumData.end(),CompareOrder());
		//不重复迁移，erase去掉重复项
		spectrumData.erase(unique(spectrumData.begin(),spectrumData.end(),myfunc),spectrumData.end());

		myExcel->SetData(bData,spectrumData,filePath);
		myExcel->PrintRpt();
		delete myExcel;

		Application->MessageBoxW(L"文件导出成功。",L"提示",0);
	}

	delete psavedg;
}
//---------------------------------------------------------------------------
//清空
void __fastcall TfrmMain::mntmN4Click(TObject *Sender)
{
	if(tmr_B->Enabled == true) {
		Application->MessageBoxW(L"正在运行中。",L"提示",0);
		return;
	}
	if(spectrumData.size() > 0 ){
		spectrumData.clear();

		m_MaxDistance = 0;
		m_timeLen = 0;
		flagCount = 0;

		MainDrawSpectrumData();
	}
}
//---------------------------------------------------------------------------
//从频谱仪获取测的值
void __fastcall TfrmMain::GetSpectrumData()
{
	if(m_Aspect)
		tempSpectrum.postion = (-1)*m_timeLen;
	else
		tempSpectrum.postion = m_timeLen;
	int Count = 3;
	double value = 0.00;
	while(Count--){
		Sleep(100);
		value += myClient->GetPointYValue();
	}
	tempSpectrum.power =  floor((value/3)*100.00f + 0.5)/100.00f;

	bool spflag = false;
	for(int i = 0; i < spectrumData.size();i++)
	{
		if(spectrumData[i].postion ==  tempSpectrum.postion)
		{
			spectrumData[i].power = tempSpectrum.power;
			spflag = true;
		}
	}
	if(!spflag)spectrumData.push_back(tempSpectrum);

}
//---------------------------------------------------------------------------
//命令滑台移动
void __fastcall TfrmMain::btn_SendClick(TObject *Sender)
{
	if(!GetMousePos(btn_Send)) return ;
	if(tmr_B->Enabled == true) {
		Application->MessageBoxW(L"正在运行中。",L"提示",0);
		return;
	}
	if(m_SerialStatus == false || edt_MoveDistance->Text == ""|| cbb_Rate->Text == "" || cbb_Aspect->Text == ""){
		Application->MessageBoxW(L"不满足执行条件。",L"提示",0);
		return ;
	}

	int aspect = 0;
	if(cbb_Aspect->Text == "左向")
	{
		aspect = 1;
	}
	else //if(cbb_Aspect->Text == "右向")
	{
		aspect = 0;
	}
	MoveData moveData;
	moveData.type = 0x03;
	moveData.counter =  1;
	moveData.aspect = aspect;
	moveData.rade =  StrToInt(cbb_Rate->Text);
	moveData.length = StrToInt(edt_MoveDistance->Text);
	controlmove->ClearSerialIn();  //清空输入缓存

	if(!controlmove-> MovingCode(moveData))
		Application->MessageBoxW(L"发送失败。",L"提示",0);


}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btn_stopClick(TObject *Sender)
{
	MoveData moveData;
	memset(&moveData,0x0,sizeof(MoveData));
	moveData.type = 0x02;
	controlmove->ClearSerialIn();  //清空输入缓存

	if(!controlmove-> MovingCode(moveData))
		Application->MessageBoxW(L"发送失败。",L"提示",0);
}
//---------------------------------------------------------------------------
//循环发送串口指令。
void __fastcall TfrmMain::tmr_BTimer(TObject *Sender)
{

	if(mythread->flagRun == false) {
        tmr_B->Enabled = false ;
    }
	MainDrawSpectrumData();
}
//---------------------------------------------------------------------------
bool __fastcall TfrmMain::GetMousePos(TButton *btn)
{
	TPoint MousePos;
	GetCursorPos(&MousePos);
	POINT MouseClient;
//	MouseClient = ScreenToClient(MousePos);

	MouseClient = btn->ScreenToClient(MousePos);//相对于button位置

	if( MouseClient.y <  btn->Height
	&  MouseClient.y > 0
	&  MouseClient.x > 0
	&  MouseClient.x <  btn->Width){
		 return true;
	}
	else {
		return false;
    }
}
//开启运行开关
void __fastcall TfrmMain::btn_StartClick(TObject *Sender)
{
	if(!GetMousePos(btn_Start)) return ;
	if(m_ppyStatus == false || m_SerialStatus == false
	|| edt_MaxDistance->Text == "" || cbb_bAspect->Text == "" || cbb_bRate->Text == "") {
		Application->MessageBoxW(L"不满足执行条件。",L"提示",0);
		return ;
	}
	//最大长度
	m_MaxDistance =   StrToInt(edt_MaxDistance->Text);
	if(m_MaxDistance % ABSCISSASINGLE != 0)
		m_MaxDistance = (m_MaxDistance / ABSCISSASINGLE) *ABSCISSASINGLE;
	//方向
	if(cbb_bAspect->Text == "左向"){
		m_Aspect = 1;
	}
	else {       // if(cbb_bAspect->Text == "右向")
		m_Aspect = 0;
	}
	//频率
	m_bRate = StrToInt(cbb_bRate->Text);
	//初始化数据
	m_timeLen = 0;
	flagCount = 0;
	//开启线程
	if(mythread) mythread->Resume();
	tmr_B->Enabled = true;

	btn_pause->Caption = "暂停";
}
//暂停
void __fastcall TfrmMain::btn_pauseClick(TObject *Sender)
{
	if(!GetMousePos(btn_pause)) return ;
	if(m_ppyStatus == false ||  m_SerialStatus == false) return ;

	if(btn_pause->Caption == "暂停" &&  tmr_B->Enabled == true){
		if(mythread) mythread->Suspend();
		tmr_B->Enabled = false;
		btn_pause->Caption = "继续";
	}
	else if(btn_pause->Caption == "继续" &&  tmr_B->Enabled == false){
		if(mythread) mythread->Resume();
		tmr_B->Enabled = true;
		btn_pause->Caption = "暂停";
	}
}

//---------------------------------------------------------------------------
//根据内容绘图
void __fastcall TfrmMain::MainDrawSpectrumData()
{
	TCanvasSpectrum* cSpectrum = new TCanvasSpectrum(img_Frame->Width,img_Frame->Height,m_MaxDistance,ABSCISSASINGLE);

	try{
		cSpectrum->DrawSpectrumData(moreSpectrumData,spectrumData,tempSpectrum);
		cSpectrum->MoveLine(posXY);
//		img_Frame->Canvas->Draw(0,0,cSpectrum->GetBitmap());       //不能自适应
		img_Frame->Picture->Bitmap->Assign(cSpectrum->GetBitmap());
	}
	__finally{
		delete cSpectrum;
	}
}
//---------------------------------------------------------------------------

//输入限制位数字
void __fastcall TfrmMain::edt_MaxDistanceKeyPress(TObject *Sender, System::WideChar &Key)
{
	TEdit *edt = dynamic_cast<TEdit *>(Sender);
	if((Key<='9'&&Key>='0')||Key=='.'||Key==0x08);
	else
	  Key=0;
	if(Key=='.'&&edt->Text.Pos("."))
	{
		Key=0;
	}
}
//---------------------------------------------------------------------------
//无法输入
void __fastcall TfrmMain::cbb_bAspectKeyPress(TObject *Sender, System::WideChar &Key)

{
	TComboBox *cbb = dynamic_cast<TComboBox *>(Sender);
	if(Key >= 0)Key = 0;
}
//---------------------------------------------------------------------------




void __fastcall TfrmMain::mntmN5Click(TObject *Sender)
{
	frmSetIni->ShowModal();
}
//---------------------------------------------------------------------------



//图线保存
void __fastcall TfrmMain::mntmN_AddClick(TObject *Sender)
{
//
	TMenuItem *myItem = dynamic_cast<TMenuItem *>(Sender);
	if(myItem->Name == "mntmN_Add"){
		if(moreSpectrumData.size() >= 4 ) return ;
		if(spectrumData.size() == 0) return;
		moreSpectrumData.push_back(spectrumData);
		spectrumData.clear();
	}
	else if(myItem->Name == "mntmN_Delete"){    //删除最后一条线
		if(moreSpectrumData.size() == 0) return ;
		moreSpectrumData.pop_back();
	}
	MainDrawSpectrumData();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::img_FrameMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
//
	if(Button == mbLeft) {
	m_MouseStaus = true;
	k_cSpectrum = new TCanvasSpectrum(img_Frame->Width,img_Frame->Height,m_MaxDistance,ABSCISSASINGLE);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::img_FrameMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
//
	if(Button == mbLeft){
	 m_MouseStaus = false;
	 delete k_cSpectrum;
	 k_cSpectrum = NULL;
	}
}
//---------------------------------------------------------------------------

//鼠标移动画图
void __fastcall TfrmMain::img_FrameMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{

	if( m_MouseStaus){
		try{
			k_cSpectrum->DrawSpectrumData(moreSpectrumData,spectrumData,tempSpectrum);
			k_cSpectrum->MoveLine(posXY);
			img_Frame->Picture->Bitmap->Assign(k_cSpectrum->GetBitmap());
			posXY.X = X;
			posXY.Y = Y;
		}
		__finally{
	//		delete cSpectrum;
		}
	}
//static posX = 0;
//// if (nFlags == MK_LBUTTON)
//{
//
//// 创建画笔RGB(0x00, 0x00, 0xFF)
//
//HPEN hPen = ::CreatePen(PS_SOLID, /*m_PenWidth*/1, RGB(0x00, 0x00, 0xFF));
//
//// 使用画笔
//
//::SelectObject(img_Frame->Canvas->Handle, hPen);
//
////设置系统色彩模式取反色
//
//int oldRop=::SetROP2(img_Frame->Canvas->Handle,R2_NOT);
//
//// 画线
//
//::MoveToEx(img_Frame->Canvas->Handle,X,0,NULL);//m_pOrigin.x, m_pOrigin.y, NULL);
//
//::LineTo(img_Frame->Canvas->Handle, X, 400);//m_pPrev.x,m_pPrev.y);
//
////恢复系统默认色彩模式
//
//::SetROP2(img_Frame->Canvas->Handle,oldRop);
//
//::MoveToEx(img_Frame->Canvas->Handle, X,100,NULL);//m_pOrigin.x, m_pOrigin.y, NULL);
//
//::LineTo(img_Frame->Canvas->Handle, posX, 300);//point.x, point.y);
//posX = X;
////m_pPrev = point;
//Invalidate();
//
//}
}
//---------------------------------------------------------------------------





