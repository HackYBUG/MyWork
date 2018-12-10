//---------------------------------------------------------------------------

#ifndef TMyExcelH
#define TMyExcelH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "TCanvasSpectrum.h"
//---------------------------------------------------------------------------


class MyExcel
{
public:
	MyExcel();
	~MyExcel();

	bool SetData(const TBasicData &basicDt,const vector<TSpectrumType> &spectrumType,String filePath);
	bool PrintRpt();
private:
	bool InitApp();
	bool NewExcelApp();
	bool NewWorkBook();

	bool SetCellValue();
	void SetHeadData(int &iRowOut,char inCol);
	bool SetColWide();
	bool SetAppVisible(bool bVisible);
private:
	Variant         m_ExcelApp;
	bool            m_bAppRun;
	Variant         m_WorkBook;
	Variant         m_Sheet;

	String          m_sError;
	unsigned int    m_RowCount;
	unsigned int    m_ColCount;
	String          m_FilePath;
private:
	vector<TSpectrumType> m_spectrumType;
	TBasicData            m_basicDt;

};


#endif
