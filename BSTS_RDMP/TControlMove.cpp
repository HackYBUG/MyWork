//---------------------------------------------------------------------------

#pragma hdrstop

#include "TControlMove.h"
#include "funs_Public.h"
#include "CRC16.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
TControlMove::TControlMove()
{
	c_SerialPort = NULL;
}
bool __fastcall TControlMove::ConnectCom(char* port)
{
	c_SerialPort = new  TSerialPort();
	return c_SerialPort->OpenEx(port,115200,8,1);
}
/// <summary>
/// 发送移动命令
/// </summary>
/// <param name="lenIn">移动距离</param>
/// <param name="redeIn">频率</param>
/// <param name="aspectIn">方向</param>
bool __fastcall TControlMove::MovingCode(const MoveData &moveData)//(UINT16 lenIn, UINT16 radeIn, Byte aspectIn,UINT16 counterIn)
{
	if(!c_SerialPort) return false;
	memset(buf,0,MAX_DATA_LENGTH+1);
	buf[0] = 0xA5;
	buf[1] = 0xA5;
	buf[2] = 0x01;
	buf[3] = moveData.type&0xFF;
	buf[4] = 0x00;
	buf[5] = 0x07;
	buf[6] = (moveData.counter>>8)&0xFF;
	buf[7] =  moveData.counter&0xFF;
	buf[8] = moveData.aspect&0xFF;
	buf[9] = (moveData.rade>>8)&0xFF;
	buf[10] = moveData.rade&0xFF;
	buf[11] = (moveData.length>>8)&0xFF;
	buf[12] = moveData.length&0xFF;

	//计算CRC16
	Byte tempbuf[MAX_DATA_LENGTH-6] = {0};
	memmove(tempbuf,buf+2,MAX_DATA_LENGTH-6);
	UINT16 crc16 = HNLX_CRC16(tempbuf,MAX_DATA_LENGTH-6);
	buf[13] =  (Byte)((crc16>>8)&0xFF);  //大端模式
	buf[14] = (Byte)(crc16&0xFF);
	buf[15] = 0x5A;
	buf[16] = 0x5A;
	c_SerialPort->SendData(buf,MAX_DATA_LENGTH);
	Sleep(100);
	memset(buf,0,MAX_DATA_LENGTH+1);
	c_SerialPort->ReadData(buf);
	String str = (char*)buf;

	return ComprisonCRC16(buf,MAX_DATA_LENGTH,moveData);
}

//============================================================================

bool __fastcall TControlMove::ComprisonCRC16(Byte* bufIn,int lenIn,const MoveData &moveData)
{
	if(!bufIn) return false;
	if(bufIn[0] == 0xA5 && bufIn[1] == 0xA5  && bufIn[lenIn-2] == 0x5A && bufIn[lenIn-1] == 0x5A)
	{
		if((moveData.type^(0x8<<4)  == buf[3] && (buf[6]<<8)^buf[7] ==  moveData.counter)
		|| (moveData.type == 0x02 && buf[3] == 0x82)){
			UINT16 crc16 = (UINT16)(bufIn[lenIn-3]&0xFF|((bufIn[lenIn-4]&0xFF)<<8));
			UINT16 counter = (UINT16)(bufIn[7]&0xFF|((bufIn[6]&0xFF)<<8));
			Byte tempbuf[MAX_DATA_LENGTH-6] = {0};
			memmove(tempbuf,bufIn+2,MAX_DATA_LENGTH-6);
			UINT16 ccitt = HNLX_CRC16(tempbuf,MAX_DATA_LENGTH-6);

			if(crc16 == ccitt) //校验通过
			{
				return true;
			}
		}
	}
	return false;
}

bool __fastcall TControlMove::ReadSleepTime(int &countIn,const MoveData &moveData)
{
	Byte readBuf[MAX_DATA_LENGTH+1] = {0};

	while(countIn--){
		Sleep(1000);
		memset(readBuf,0,MAX_DATA_LENGTH+1);
		c_SerialPort->ReadData(readBuf);
		if(ComprisonCRC16(readBuf,MAX_DATA_LENGTH,moveData)) return true;
	}
	return false;
}

bool __fastcall TControlMove::ClearSerialIn()
{
	return c_SerialPort->ClearData(1);
}
bool __fastcall TControlMove::ClearSerialOut()
{
	return c_SerialPort->ClearData(2);
}
