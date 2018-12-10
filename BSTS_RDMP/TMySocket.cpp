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
	//初始化DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//创建套接字
	 sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	 if(sock == -1 ) return false;
	 //设置超时
	 int nNetTimeout = 1000;//1秒
	 setsockopt(sock,SOL_SOCKET,SO_SNDTIMEO,(char*)&nNetTimeout,sizeof(int));
	 setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,(char*)&nNetTimeout,sizeof(int));
	//向服务器发起请求
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
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
	//接收服务器传回的数据
	char bufRecv[BUF_SIZE] = {0};
	recv(sock, bufRec, BUF_SIZE, 0);
}

void __fastcall ClientSocket::Initialization()
{
	char setBuf[50] = {0};
	AnsiString tempStr = "";
	//复位频谱分析仪
	ClientSetTerm("*RST\n",5);

	//设置、查询中心频率
	tempStr = ":FREQ:CENT 27.095MHz\n";
	ClientSetTerm(tempStr.c_str(),tempStr.Length());
	//设置频宽
	tempStr = ":FREQ:SPAN 5MHz\n";
	ClientSetTerm(tempStr.c_str(),tempStr.Length());
	//关闭所有频标
//	tempStr =		 ":CALCulate:MARKer:AOFF\n";
//	bool flag = ClientSetTerm(tempStr.c_str(),tempStr.Length());
	//激活频标
	tempStr = ":CALC:MARK1:STAT  ON \n";//":CALCulate:MARKer<1>:STATe ON|1\n";
	ClientSetTerm(tempStr.c_str(),tempStr.Length());
	//查询频标状态
	memset(setBuf,0,sizeof(setBuf));
	tempStr = ":CALCulate:MARKer1:FCOunt?\n";
	ClientQueryData(tempStr.c_str(),tempStr.Length(),setBuf);
	//设置频谱仪的参考电平
	tempStr = ":DISPlay:WINDow1:TRACe:Y:RLEVel 25dBm\n"; //[:SET]:RLEVel\n";
	ClientSetTerm(tempStr.c_str(),tempStr.Length());
	//设置扫描模式
	tempStr = ":INITiate:CONTinuous NO\n";
	ClientSetTerm(tempStr.c_str(),tempStr.Length());


}


double __fastcall ClientSocket::GetPointYValue()
{
	char tempBuf[50] = {0};
	AnsiString tempStr = "";
/*
	//手动触发一次
	tempStr = ":INITiate:IMMediate\n";
	ClientSetTerm(tempStr.c_str(),tempStr.Length());
	//获得频标计数值
	memset(tempBuf,0,sizeof(tempBuf));
	tempStr = ":CALCulate:MARKer1:FCOunt:X?\n";
	ClientQueryData(tempStr.c_str(),tempStr.Length(),tempBuf);
*/
	//设置仪器进行一次峰值的搜索
	tempStr = ":CALCulate:MARKer1:MAXimum\n";
	ClientSetTerm(tempStr.c_str(),tempStr.Length());
//	//设置参考电平等于频标的幅度值
//	tempStr = ":CALCulate:MARKer1:RLEVel\n"; //[:SET]:RLEVel\n";
//	ClientSetTerm(tempStr.c_str(),tempStr.Length());

	//仪器频标Y轴方向的值
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
	return result;//floor(result*100.00f + 0.5)/100.00f;      //保留2位小数
}













unsigned int __stdcall ServerFun(PVOID pM)
{
//	srand((int)time(0));
//	float value = rand()%65 -35;
//	itoa(value,buffer,16);
	WSADATA wsaData;
	WSAStartup( MAKEWORD(2, 2), &wsaData);
	//创建套接字
	SOCKET servSock = socket(AF_INET, SOCK_STREAM, 0);
	//绑定套接字
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
	sockAddr.sin_family = PF_INET;  //使用IPv4地址
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
	sockAddr.sin_port = htons(SOCKETPORT);  //端口
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	//进入监听状态
	listen(servSock, 20);
	//接收客户端请求
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);

	SOCKET clntSock = clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
	while(1){

	char buffer[BUF_SIZE] = {0};  //缓冲区
	int strLen = recv(clntSock, buffer, BUF_SIZE, 0);  //接收客户端发来的数据
	memset(buffer,0,BUF_SIZE);

	std::string tempStr = "-1.440349e+001";
	memmove(buffer,tempStr.c_str(),tempStr.length());

	send(clntSock, buffer, tempStr.length(), 0);  //将数据原样返回
    }
    //关闭套接字
	closesocket(clntSock);
	closesocket(servSock);
	//终止 DLL 的使用
	WSACleanup();

}


void ClientSocket()
{
		//初始化DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//创建套接字
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//向服务器发起请求
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(1234);
	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	//获取用户输入的字符串并发送给服务器
	char bufSend[BUF_SIZE] = {0};
//	printf("Input a string: ");
//	scanf("%s", bufSend);
	send(sock, bufSend, strlen(bufSend), 0);
	//接收服务器传回的数据
	char bufRecv[BUF_SIZE] = {0};
	recv(sock, bufRecv, BUF_SIZE, 0);

	//输出接收到的数据
//    printf("Message form server: %s\n", bufRecv);

	//关闭套接字
	closesocket(sock);

    //终止使用 DLL
	WSACleanup();

    system("pause");

}
