//---------------------------------------------------------------------------

#pragma hdrstop

#include "funs_Public.h"
#include <IniFiles.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)


/// <summary>
/// ∂¡»°≈‰÷√Œƒº˛
/// </summary>
void __fastcall ReadIniFile(String &ipOut, String &port,String &singleLen)
{
	TIniFile * m_pIniFile;
	try
	{
		m_pIniFile = new TIniFile(ExtractFilePath(Application->ExeName)+"Config.ini");

		ipOut = m_pIniFile->ReadString("SystemSet","PuIP","");
		port = m_pIniFile->ReadString("SystemSet","ComPort","");
		singleLen =  m_pIniFile->ReadString("SystemSet","SingleLen","");
	}
	__finally
	{
		delete m_pIniFile;
    }

}

void __fastcall WriteIniFile(String inIp, String inPort,String inSingleLen)
{
	TIniFile * m_pIniFile;
	try
	{
		m_pIniFile = new TIniFile(ExtractFilePath(Application->ExeName)+"Config.ini");
		m_pIniFile->WriteString("SystemSet","PuIP",inIp);
		m_pIniFile->WriteString("SystemSet","ComPort",inPort);
		m_pIniFile->WriteString("SystemSet","SingleLen",inSingleLen);
	}
	__finally
	{
		delete m_pIniFile;
    }

}


