//---------------------------------------------------------------------------

#ifndef TControlMoveH
#define TControlMoveH
//---------------------------------------------------------------------------
#include "TSerialPort.h"
#include <System.Classes.hpp>


struct MoveData
{
UINT8  type;        //命令类型
UINT16 counter;   //计数器
UINT8  aspect;    //方向
UINT16 rade;      //频率
UINT16 length;    //移动长度
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


//监听线程
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
