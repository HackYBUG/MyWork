//---------------------------------------------------------------------------

#pragma hdrstop

#include "funs_Public.h"
#include <IniFiles.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)


/// <summary>
/// ∂¡»°≈‰÷√Œƒº˛
/// </summary>
void __fastcall ReadIniFile(IniType &iniData)
{
	TIniFile * m_pIniFile;
	try
	{
		m_pIniFile = new TIniFile(ExtractFilePath(Application->ExeName)+"config.ini");

		iniData.i_IPD = m_pIniFile->ReadInteger("DeviceSet","IPD",0);
		iniData.i_IT8500 = m_pIniFile->ReadInteger("DeviceSet","IT8500",0);
	}
	__finally
	{
		delete m_pIniFile;
	}

}

void __fastcall WriteIniFile(IniType iniData)
{
	TIniFile * m_pIniFile;
	try
	{
		m_pIniFile = new TIniFile(ExtractFilePath(Application->ExeName)+"config.ini");
		m_pIniFile->WriteInteger("DeviceSet","IPD",iniData.i_IPD);
		m_pIniFile->WriteInteger("DeviceSet","IT8500",iniData.i_IT8500);
	}
	__finally
	{
		delete m_pIniFile;
    }

}


