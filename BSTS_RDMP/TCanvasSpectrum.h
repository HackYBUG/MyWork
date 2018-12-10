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
#define BACKGOUNP_1       255,255,255 //32,32,32           //背景颜色   64,64,64
#define BRUSHPOINT        32,32,32//255,255,255        //
#define PENLINE           32,32,32//255,255,255        //
#define TOPHIHT           100                 //顶部高度
#define BOTTOMWIDE        60                 //底部宽度
#define LEFTWIDE          50                 //左边宽度
#define RIGHTWIDE         20                 //右边宽度
#define VERTICALSINGLE    5                   //竖坐标单位
#define FONTSIZE          8                   //字体大小
#define SPOTSIZE          2                  //点的大小
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
		//卸载GDI+环境
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
	void MoreDrawSpectrumLine(const vector<T> &moreSpectrumData,const vector<TSpectrumType> &spectrumDataIn); //绘制多条曲线

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

//仿函式
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
