//---------------------------------------------------------------------------

#ifndef TControlMoveH
#define TControlMoveH
//---------------------------------------------------------------------------
#include "TSerialPort.h"
#include <System.Classes.hpp>


struct MoveData
{
UINT8  type;        //��������
UINT16 counter;   //������
UINT8  aspect;    //����
UINT16 rade;      //Ƶ��
UINT16 length;    //�ƶ�����
};


class TControlMove
{
public:
	TControlMove();
	~TControlMove(){
		if(c_SerialPort->m_bOpened) c_SerialPort->PortClose();
		delete c_SerialPort;
	}
	bool __fastcall ConnectCom(char* port);
	bool __fastcall MovingCode(const MoveData &moveData);
	bool __fastcall ReadSleepTime(int &countIn,const MoveData &moveData);
	bool __fastcall ClearSerialIn();
	bool __fastcall ClearSerialOut();
private:
	bool __fastcall ComprisonCRC16(Byte* bufIn,int lenIn,const MoveData &moveData);
private:
	Byte buf[MAX_DATA_LENGTH+1];
public:
	TSerialPort *c_SerialPort;
};


//�����߳�
class ListenThread:public TThread
{
public:
	ListenThread();

	void __fastcall Execute();

	__property TSerialPort *ObjectPointer = {write =  SetObjectPointer, nodefault};
	__property bool GetReadResult = {read = readBl };
private:
	TSerialPort *serialPort;
	bool readBl;
	void __fastcall SetObjectPointer(TSerialPort *pointerIn)
	{
		serialPort = pointerIn;
    }
};


#endif
