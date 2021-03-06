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

struct IniType
{
	int i_IPD;
	int i_IT8500;
};

void __fastcall ReadIniFile(IniType &iniData);
void __fastcall WriteIniFile(IniType iniData);



struct TPSBData
{

};


#endif
