//---------------------------------------------------------------------------

#pragma hdrstop

#include "TMyExcel.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


//---------------------------------------------------------------------------
MyExcel::MyExcel()
{
	m_RowCount = 0;
	m_bAppRun=false;
}
MyExcel::~MyExcel()
{
	if(m_bAppRun)
	{
		m_ExcelApp.OleFunction ("Quit");
	}
}
//---------------------------------------------------------------------------
bool MyExcel::SetData(const TBasicData &basicDt,const vector<TSpectrumType> &spectrumType,String filePath)
{
	m_basicDt = basicDt;
	m_FilePath = filePath;
	m_spectrumType.assign(spectrumType.begin(),spectrumType.end());

	m_ColCount= 5;
	m_RowCount = m_spectrumType.size();

	return true;
}
//---------------------------------------------------------------------------
bool MyExcel::PrintRpt()
{
	if(!InitApp())      return false;
	if(!SetCellValue()) return false;
	if(!SetColWide())   return false;
	SetAppVisible(false);
	return true;
}
bool MyExcel::InitApp()
{
	if(!NewExcelApp()) return false;
	if(!NewWorkBook()) return false;

	return true;
}
bool MyExcel::NewExcelApp()
{
	try
	{
		m_ExcelApp = Variant::CreateObject("excel.application");
		m_bAppRun=true;
	}
	catch(...)
	{
		m_sError="不能初始化Excel应用程序对象！";
		return false;
	}
	return true;
}

bool MyExcel::NewWorkBook()
{
	Variant all_workbooks;
	//-- Get workbooks collection
	all_workbooks = m_ExcelApp.OlePropertyGet("Workbooks");
	//-- Set number of worksheets to 1
	m_ExcelApp.OlePropertySet("SheetsInNewWorkbook",(Variant)1);
	//-- Create a new workbook
	m_WorkBook = all_workbooks.OleFunction("Add");
	m_Sheet = m_WorkBook.OlePropertyGet("ActiveSheet");
	//my
	m_Sheet.OlePropertyGet("Cells").OlePropertySet("NumberFormatLocal",WideString("@"));
	m_ExcelApp.OlePropertySet("DisplayAlerts",false);      //屏蔽掉Excel的警告对话框
	return true;
}

bool MyExcel::SetCellValue()
{
 		if(m_RowCount <= 0)
		{
				m_sError="数据集为空";
				return false;
		}
		if(m_ColCount<=0)
		{
				m_sError="列数读取出错！";
				return false;
		}

		char ctemp = 'A';
		int iRow = 2;
		String str;
		Variant cell;

		SetHeadData(iRow, ctemp);
		for(int i = 0;i < m_RowCount;i++)
		{
			for(int k = 0; k < 2;k++)
			{
				ctemp='A'+k;
				str.sprintf(L"%c%d",ctemp,iRow);
				cell=m_Sheet.OlePropertyGet("Range",WideString(str));
				switch(k)
				{
				case 0: str = IntToStr(m_spectrumType[i].postion) ;break;
				case 1: str = FloatToStr(m_spectrumType[i].power); break;
				}
				cell.OlePropertySet("Value",WideString(str));
			}
			iRow++;
		}

		return true;
}

//表头
void MyExcel::SetHeadData(int &iRowOut,char inCol)
{
	int iRows = iRowOut;
	Variant cell;
	char ctemp=inCol;
	String str;
#ifdef my
	//jiacu
	m_ExcelApp.OlePropertyGet("Rows",iRows).OlePropertyGet("Font").OlePropertySet("FontStyle",WideString("加粗"));
	for(int k=0; k<3;k++)
	{
		ctemp = inCol + k;
		str.sprintf(L"%c%d",ctemp,iRows);
		cell=m_Sheet.OlePropertyGet("Range",WideString(str));
		switch(k)
		{
		case 0: str = "电压=" + IntToStr(m_basicDt.electric_DY) + "V"; break;
		case 1: str = "电流=" + FloatToStr(m_basicDt.electric_DL) + "A"; break;
		case 2: str = "电阻=" + IntToStr(m_basicDt.electric_DZ) + "Ω"; break;
		}
		cell.OlePropertySet("Value",WideString(str));
	}


	iRows++;
	m_ExcelApp.OlePropertyGet("Rows",iRows).OlePropertyGet("Font").OlePropertySet("FontStyle",WideString("加粗"));
	for(int k=0; k<3;k++)
	{
		ctemp=inCol+k;
		str.sprintf(L"%c%d",ctemp,iRows);
		cell=m_Sheet.OlePropertyGet("Range",WideString(str));
		switch(k)
		{
		case 0: str = "Z=" + IntToStr(m_basicDt.distance_Z) + "mm"; break;
		case 1: str = "Y=" + IntToStr(m_basicDt.distance_Y) + "mm"; break;
		case 2: str =  m_basicDt.Text;break;
		}
		cell.OlePropertySet("WrapText", true);   //单元格自动换行
		cell.OlePropertySet("Value",WideString(str));
	}
#endif
	iRows++;
	m_ExcelApp.OlePropertyGet("Rows",iRows).OlePropertyGet("Font").OlePropertySet("FontStyle",WideString("加粗"));
	for(int k=0; k<2;k++)
	{
		ctemp=inCol+k;
		str.sprintf(L"%c%d",ctemp,iRows);
		cell=m_Sheet.OlePropertyGet("Range",WideString(str));
		switch(k)
		{
		case 0: str = "距离"; break;
		case 1: str = "功率"; break;
		}
		cell.OlePropertySet("Value",WideString(str));
	}

	iRowOut =  ++iRows;
}

//---------------------------------------------------------------------------
//表宽
bool MyExcel::SetColWide()
{
	   //设置第一列的列宽为
	   m_ExcelApp.OlePropertyGet("Columns",1).OlePropertySet("ColumnWidth",20);
	   m_ExcelApp.OlePropertyGet("Columns",2).OlePropertySet("ColumnWidth",20);
	   m_ExcelApp.OlePropertyGet("Columns",3).OlePropertySet("ColumnWidth",20);

	   return true;
}
//---------------------------------------------------------------------------
bool MyExcel::SetAppVisible(bool bVisible)
{
		m_ExcelApp.OlePropertySet("Visible",(Variant)bVisible);
		m_ExcelApp.OlePropertyGet("ActiveWorkbook")
			.OleFunction("SaveAs",WideString(m_FilePath),-4143);    // FileFormat := xlNormal
		return true;
}
