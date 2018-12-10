//---------------------------------------------------------------------------

#ifndef funs_PublicH
#define funs_PublicH
//---------------------------------------------------------------------------
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include <iostream>
#include <sstream>
#include <string>

template<typename T>
T sciToDub(const std::string& str)
{
	std::stringstream ss(str);
	  T d = 0;
	  ss >> d;
	  if(ss.fail())
	 {
		   std::string s = "Unable to format";
		   s += str;
		   s += "as s number!";
		   throw(s);
	  }
	  return(d);
}


void __fastcall ReadIniFile(String &ipOut, String &port,String &singleLen);
void __fastcall WriteIniFile(String inIp, String inPort,String inSingleLen);
#endif
