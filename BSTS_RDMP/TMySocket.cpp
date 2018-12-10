//---------------------------------------------------------------------------

#pragma hdrstop

#include "TMySocket.h"
#include <System.Classes.hpp>
#include "funs_Public.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma comment (lib, "ws2_32.lib")




bool __fastcall ClientSocket::ConnectServer(char* hostIp)
{
	//��ʼ��DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//�����׽���
	 sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	 if(sock == -1 ) return false;
	 //���ó�ʱ
	 int nNetTimeout = 1000;//1��
	 setsockopt(sock,SOL_SOCKET,SO_SNDTIMEO,(char*)&nNetTimeout,sizeof(int));
	 setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,(char*)&nNetTimeout,sizeof(int));
	//���������������
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr((char*)hostIp);
	sockAddr.sin_port = htons(SOCKETPORT);
	int result = connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	return result == 0 ? true:false;
}

bool __fastcall ClientSocket::ClientSetTerm(char *bufSend,int len)
{
	return send(sock, bufSend, len, 0);
}

void __fastcall ClientSocket::ClientQueryData(char *bufSend,int len,char *bufRec)
{
	if(!ClientSetTerm(bufSend, len)) return ;
	//���շ��������ص�����
	char bufRecv[BUF_SIZE] = {0};
	recv(sock, bufRec, BUF_SIZE, 0);
}

void __fastcall ClientSocket::Initialization()
{
	char setBuf[50] = {0};
	AnsiString tempStr = "";
	//��λƵ�׷�����
	ClientSetTerm("*RST\n",5);

	//���á���ѯ����Ƶ��
	tempStr = ":FREQ:CENT 27.095MHz\n";
	ClientSetTerm(tempStr.c_str(),tempStr.Length());
	//����Ƶ��
	tempStr = ":FREQ:SPAN 5MHz\n";
	ClientSetTerm(tempStr.c_str(),tempStr.Length());
	//�ر�����Ƶ��
//	tempStr =		 ":CALCulate:MARKer:AOFF\n";
//	bool flag = ClientSetTerm(tempStr.c_str(),tempStr.Length());
	//����Ƶ��
	tempStr = ":CALC:MARK1:STAT  ON \n";//":CALCulate:MARKer<1>:STATe ON|1\n";
	ClientSetTerm(tempStr.c_str(),tempStr.Length());
	//��ѯƵ��״̬
	memset(setBuf,0,sizeof(setBuf));
	tempStr = ":CALCulate:MARKer1:FCOunt?\n";
	ClientQueryData(tempStr.c_str(),tempStr.Length(),setBuf);
	//����Ƶ���ǵĲο���ƽ
	tempStr = ":DISPlay:WINDow1:TRACe:Y:RLEVel 25dBm\n"; //[:SET]:RLEVel\n";
	ClientSetTerm(tempStr.c_str(),tempStr.Length());
	//����ɨ��ģʽ
	tempStr = ":INITiate:CONTinuous NO\n";
	ClientSetTerm(tempStr.c_str(),tempStr.Length());


}


double __fastcall ClientSocket::GetPointYValue()
{
	char tempBuf[50] = {0};
	AnsiString tempStr = "";
/*
	//�ֶ�����һ��
	tempStr = ":INITiate:IMMediate\n";
	ClientSetTerm(tempStr.c_str(),tempStr.Length());
	//���Ƶ�����ֵ
	memset(tempBuf,0,sizeof(tempBuf));
	tempStr = ":CALCulate:MARKer1:FCOunt:X?\n";
	ClientQueryData(tempStr.c_str(),tempStr.Length(),tempBuf);
*/
	//������������һ�η�ֵ������
	tempStr = ":CALCulate:MARKer1:MAXimum\n";
	ClientSetTerm(tempStr.c_str(),tempStr.Length());
//	//���òο���ƽ����Ƶ��ķ���ֵ
//	tempStr = ":CALCulate:MARKer1:RLEVel\n"; //[:SET]:RLEVel\n";
//	ClientSetTerm(tempStr.c_str(),tempStr.Length());

	//����Ƶ��Y�᷽���ֵ
	memset(tempBuf,0,sizeof(tempBuf));
	tempStr = ":CALCulate:MARKer1:Y?\n";
	ClientQueryData(tempStr.c_str(),tempStr.Length(),tempBuf);

	double result = 0;
	try{
	 result = sciToDub<double>((std::string)tempBuf);
	}
	catch(...){
		result = 0;
	}
	return result;//floor(result*100.00f + 0.5)/100.00f;      //����2λС��
}













unsigned int __stdcall ServerFun(PVOID pM)
{
//	srand((int)time(0));
//	float value = rand()%65 -35;
//	itoa(value,buffer,16);
	WSADATA wsaData;
	WSAStartup( MAKEWORD(2, 2), &wsaData);
	//�����׽���
	SOCKET servSock = socket(AF_INET, SOCK_STREAM, 0);
	//���׽���
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //�����IP��ַ
	sockAddr.sin_port = htons(SOCKETPORT);  //�˿�
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	//�������״̬
	listen(servSock, 20);
	//���տͻ�������
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);

	SOCKET clntSock = clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
	while(1){

	char buffer[BUF_SIZE] = {0};  //������
	int strLen = recv(clntSock, buffer, BUF_SIZE, 0);  //���տͻ��˷���������
	memset(buffer,0,BUF_SIZE);

	std::string tempStr = "-1.440349e+001";
	memmove(buffer,tempStr.c_str(),tempStr.length());

	send(clntSock, buffer, tempStr.length(), 0);  //������ԭ������
    }
    //�ر��׽���
	closesocket(clntSock);
	closesocket(servSock);
	//��ֹ DLL ��ʹ��
	WSACleanup();

}


void ClientSocket()
{
		//��ʼ��DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//�����׽���
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//���������������
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(1234);
	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	//��ȡ�û�������ַ��������͸�������
	char bufSend[BUF_SIZE] = {0};
//	printf("Input a string: ");
//	scanf("%s", bufSend);
	send(sock, bufSend, strlen(bufSend), 0);
	//���շ��������ص�����
	char bufRecv[BUF_SIZE] = {0};
	recv(sock, bufRecv, BUF_SIZE, 0);

	//������յ�������
//    printf("Message form server: %s\n", bufRecv);

	//�ر��׽���
	closesocket(sock);

    //��ֹʹ�� DLL
	WSACleanup();

    system("pause");

}
