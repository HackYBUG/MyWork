//---------------------------------------------------------------------------

#ifndef TCanvasSpectrumH
#define TCanvasSpectrumH
//---------------------------------------------------------------------------
#include <Vcl.Graphics.hpp>
#include <GdiPlus.h>
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
//COLOR
#define BACKGOUNP_1       255,255,255 //32,32,32           //������ɫ   64,64,64
#define BRUSHPOINT        32,32,32//255,255,255        //
#define PENLINE           32,32,32//255,255,255        //
#define TOPHIHT           100                 //�����߶�
#define BOTTOMWIDE        60                 //�ײ����
#define LEFTWIDE          50                 //��߿��
#define RIGHTWIDE         20                 //�ұ߿��
#define VERTICALSINGLE    5                   //�����굥λ
#define FONTSIZE          8                   //�����С
#define SPOTSIZE          2                  //��Ĵ�С
//---------------------------------------------------------------------------


struct TSpectrumType
{
	int    postion;
	double  power;
};

struct TBasicData
{
	int distance_Z;
	int distance_Y;
	int electric_DZ;
	int electric_DY;
	float electric_DL;
	String Text;
};

typedef  vector<TSpectrumType> T;

class TCanvasSpectrum
{
public:
	TCanvasSpectrum(int width,int height,int inMaxLen,int inSingleLen);
	~TCanvasSpectrum(){
		delete bmpSpectrum;
		//ж��GDI+����
		Gdiplus::GdiplusShutdown(m_gdiplusToken);
	}
	//
	TBitmap* GetBitmap();

	void DrawSpectrumData(const vector<T> &moreSpectrumData,vector<TSpectrumType> &spectrumData, TSpectrumType endSptData);
	void __fastcall MoveLine(TPoint posXY);
private:
	void InitFrame();
	void DrawData(const vector<TSpectrumType>& spectrumData, int orderLine);
	void DrawBasicData(const TSpectrumType& spData);
	void MoreDrawSpectrumLine(const vector<T> &moreSpectrumData,const vector<TSpectrumType> &spectrumDataIn); //���ƶ�������

private:
	vector<Gdiplus::PointF> vpt_Width;
	Gdiplus::PointF vpt_High[14];
private:
	int k_Height;
	int k_Width;
	int k_count;
	int k_MaxLen;
	int ABSCISSASINGLE;
	int k_MinLen;


	vector<TSpectrumType>  k_spectrumType;
	TBitmap *bmpSpectrum ;

	ULONG_PTR m_gdiplusToken;

};

//�º�ʽ
struct CompareOrder{
	bool operator()(const TSpectrumType& stt1, const TSpectrumType& stt2)const{
		if(stt1.postion <= stt2.postion) return true;
		else
			return false;
//		return  stt1.postion < stt2.postion ? true:false;
	}

};


static bool myfunc(const TSpectrumType& stt1, const TSpectrumType& stt2)
{
	return (stt1.postion == stt2.postion);
}


#endif
