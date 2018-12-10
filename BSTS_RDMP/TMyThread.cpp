//---------------------------------------------------------------------------

#pragma hdrstop

#include "TMyThread.h"
#include "MainFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
__fastcall TMyThread::TMyThread():TThread(true)
{
	FreeOnTerminate = true;   //�Զ��ͷ�
//	Resume(); //�����̼߳���ִ��
	flagRun = false;
}
void __fastcall TMyThread::Execute()
{
	//do something
	while(!Terminated)
	{
		try{
			MainCanvasTime();
		}
		catch(...){
		}
	}

}

void __fastcall TMyThread::MainCanvasTime()
{
	static bool flagBl = false;

	if(frmMain->m_timeLen < frmMain->m_MaxDistance && frmMain->flagCount < 3){
		flagRun = true;
		if(frmMain->m_timeLen == 0 && 0 == frmMain->flagCount)
		{
			frmMain->GetSpectrumData();
		}
		MoveData moveData;
		moveData.type = 0x01;
		moveData.counter = frmMain->m_timeLen/frmMain->ABSCISSASINGLE + 1;
		moveData.aspect = frmMain->m_Aspect;
		moveData.rade =  frmMain->m_bRate;// MAINRATE;
		moveData.length = frmMain->ABSCISSASINGLE;
		flagBl = frmMain->controlmove->MovingCode(moveData);
		if(flagBl )
		{
			frmMain->m_timeLen = frmMain->m_timeLen + frmMain->ABSCISSASINGLE;
			frmMain->flagCount = 0;
			int timeLen = 15;
			if(frmMain->controlmove->ReadSleepTime(timeLen,moveData)){ //ѭ����ȡ �����ڼ������ӳ�����
//				int sleepTimeLen = (frmMain->ABSCISSASINGLE *100/frmMain->m_bRate) - (15 - timeLen);
//				Sleep( *1000);
				Sleep(2000);
				frmMain->GetSpectrumData();
			}
			else{
				frmMain->flagCount = 3;
			}
		}
		else
			frmMain->flagCount++;
	}
	else{
//		Terminate(); //��Terminate��������ΪTrue����ֹ�̵߳�ִ�С�
		flagRun = false;
		Suspend();  //�����߳�

	}
}
