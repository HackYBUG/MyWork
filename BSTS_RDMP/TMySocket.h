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
		//�ر��׽���
		closesocket(sock);
		//��ֹʹ�� DLL
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



//���Ե���


unsigned int __stdcall ServerFun(PVOID pM);

#endif
