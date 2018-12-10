//---------------------------------------------------------------------------

#ifndef TMySocketH
#define TMySocketH
//---------------------------------------------------------------------------
#include <winsock2.h>

//---------------------------------------------------------------------------
#define BUF_SIZE 255
#define SOCKETPORT 5000

class ClientSocket
{
public:
	ClientSocket(){}
	~ClientSocket(){
		//关闭套接字
		closesocket(sock);
		//终止使用 DLL
		WSACleanup();
	}

	bool __fastcall ConnectServer(char* hostIp);
	void __fastcall Initialization();
	double __fastcall GetPointYValue();
private:
	bool __fastcall ClientSetTerm(char *bufSend,int len);
	void __fastcall ClientQueryData(char *bufSend,int len,char *bufRec);
private:
	SOCKET sock;

};



//测试调用


unsigned int __stdcall ServerFun(PVOID pM);

#endif
