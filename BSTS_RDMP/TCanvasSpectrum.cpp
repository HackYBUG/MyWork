//---------------------------------------------------------------------------

#pragma hdrstop

#include "TCanvasSpectrum.h"
#include "funs_Public.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma comment(lib,"gdiplus.lib")
using namespace Gdiplus;
TCanvasSpectrum::TCanvasSpectrum(int width,int height,int inMaxLen,int inSingleLen):k_Width(width),k_Height(height)
{
	//初始化GDI+
	Gdiplus::GdiplusStartupInput  m_gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken,&m_gdiplusStartupInput,NULL);

	bmpSpectrum = new TBitmap();
	bmpSpectrum->Width =k_Width;
	bmpSpectrum->Height = k_Height;

	ABSCISSASINGLE = inSingleLen;
	k_MaxLen = inMaxLen;
	k_count = (k_MaxLen*2/ABSCISSASINGLE) + 1;
}

//---------------------------------------------------------------------------
TBitmap* TCanvasSpectrum::GetBitmap(){
		return bmpSpectrum;
}
//---------------------------------------------------------------------------

void TCanvasSpectrum::DrawSpectrumData(const vector<T> &moreSpectrumData,
		vector<TSpectrumType> &spectrumData, TSpectrumType endSptData)
{
	InitFrame();
	for(int i=0;i< moreSpectrumData.size(); i++)
	{
		DrawData(moreSpectrumData[i],i+1);
	}

	int posEnd = spectrumData.size();
	//data
	if(posEnd > 0) {
		DrawBasicData(endSptData);
		if(posEnd > 1)
		{
			sort(spectrumData.begin(),spectrumData.end(),CompareOrder());
			//不重复迁移，erase去掉重复项
			spectrumData.erase(unique(spectrumData.begin(),spectrumData.end(),myfunc),spectrumData.end());
		}
		k_spectrumType.assign(spectrumData.begin(),spectrumData.end());
		DrawData(k_spectrumType,0);
	}


}
//---------------------------------------------------------------------------
void TCanvasSpectrum::InitFrame()
{
	Gdiplus::Graphics graphics(bmpSpectrum->Canvas->Handle);
	graphics.SetSmoothingMode(SmoothingModeHighQuality); //高画质、低速
   //画笔
	Pen penLine(Color::Color(PENLINE), 1);
	Pen penLineRed(Color::Color(211,85,0), 1);

	Pen pen_Dash(Color::Color(171, 171, 171), 1);
	pen_Dash.SetDashStyle(DashStyleDash);//虚线

	SolidBrush brushBackGround(Color::Color(BACKGOUNP_1));
	SolidBrush brushPoint(Color::Color(BRUSHPOINT));
	//字体
	FontFamily fontFamily(L"微软雅黑");
	Gdiplus::Font font(&fontFamily, FONTSIZE, FontStyleRegular,UnitPixel);
	Gdiplus::Font fontXY(&fontFamily,FONTSIZE*2,FontStyleRegular,UnitPixel);
	//颜色
	graphics.FillRectangle(&brushBackGround,Gdiplus::RectF(0, 0, k_Width, k_Height));

	Gdiplus::PointF vpt_top[2];
	vpt_top[0] =  Gdiplus::PointF(1, TOPHIHT);
	vpt_top[1] =  Gdiplus::PointF(k_Width, TOPHIHT);
	graphics.DrawLine(&penLine,vpt_top[0],vpt_top[1]);
	//画L字
	Gdiplus::PointF vpt_1(LEFTWIDE, TOPHIHT);
	Gdiplus::PointF vpt_2(LEFTWIDE, k_Height-BOTTOMWIDE);
	Gdiplus::PointF vpt_3(k_Width-RIGHTWIDE,k_Height-BOTTOMWIDE);
	graphics.DrawLine(&penLine,vpt_1,vpt_2);
	graphics.DrawLine(&penLine,vpt_2,vpt_3);




	graphics.DrawRectangle(&pen_Dash,Gdiplus::RectF(k_Width -150, (TOPHIHT/4)/2*1 - 5, 50, 10));
	graphics.DrawRectangle(&pen_Dash,Gdiplus::RectF(k_Width -150, (TOPHIHT/4)/2*3 - 5, 50, 10));
	graphics.DrawRectangle(&pen_Dash,Gdiplus::RectF(k_Width -150, (TOPHIHT/4)/2*5 - 5, 50, 10));
	graphics.DrawRectangle(&pen_Dash,Gdiplus::RectF(k_Width -150, (TOPHIHT/4)/2*7 - 5, 50, 10));

	//画标尺
	StringFormat *sf = new StringFormat();
	try
	{    //横线
		sf->SetAlignment( StringAlignmentCenter);    //水平居中
		sf->SetLineAlignment(StringAlignmentCenter); //垂直居中

		float tempWidthLen =  (k_Width- RIGHTWIDE - LEFTWIDE);
		//最小刻度
		if(k_count > 1)
			k_MinLen = tempWidthLen/(k_count-1);
		else
			k_MinLen = 0;
		for(int i=0 ;i< k_count && k_count > 1;i++)
		{
			vpt_Width.push_back(Gdiplus::PointF(LEFTWIDE + tempWidthLen*i/(k_count-1),k_Height-BOTTOMWIDE));

			if(i <= (k_count-1)/2)      //左边
			{
				if(i % 10 == 0 || i == (k_count-1)/2 )
				{
					String  strLen= IntToStr((-1)*k_MaxLen + ABSCISSASINGLE*i);
					graphics.DrawString(strLen.c_str(),-1,&font,Gdiplus::RectF(vpt_Width[i].X-FONTSIZE/2, vpt_Width[i].Y , 10, BOTTOMWIDE),sf,&brushPoint);
					graphics.DrawLine(&penLineRed,vpt_Width[i],Gdiplus::PointF(vpt_Width[i].X,vpt_Width[i].Y + 5));
					//虚线
					if(i != 0)
						graphics.DrawLine(&pen_Dash,vpt_Width[i],Gdiplus::PointF(vpt_Width[i].X,TOPHIHT));
				}
				else{
					  graphics.DrawLine(&penLine,vpt_Width[i],Gdiplus::PointF(vpt_Width[i].X,vpt_Width[i].Y + 3));
				}

			}
			else   //右边
			{
				if(0 == (i -  ((k_count-1)/2) % 10  - (k_count-1)/2)%10)
				{
					String  strLen= " " + IntToStr((-1)*k_MaxLen + ABSCISSASINGLE*i);
					graphics.DrawString(strLen.c_str(),-1,&font,Gdiplus::RectF(vpt_Width[i].X-FONTSIZE/2, vpt_Width[i].Y , 10, BOTTOMWIDE),sf,&brushPoint);
					graphics.DrawLine(&penLineRed,vpt_Width[i],Gdiplus::PointF(vpt_Width[i].X,vpt_Width[i].Y + 5));
					//虚线
					graphics.DrawLine(&pen_Dash,vpt_Width[i],Gdiplus::PointF(vpt_Width[i].X,TOPHIHT));
				}
				else{
					  graphics.DrawLine(&penLine,vpt_Width[i],Gdiplus::PointF(vpt_Width[i].X,vpt_Width[i].Y + 3));
				}
			}

		}


		//画标尺 竖线
		float tempHegihtLen =  (k_Height- TOPHIHT - BOTTOMWIDE)/14;

		for(int i=0 ;i< 14;i++)
		{
			vpt_High[i] = Gdiplus::PointF(LEFTWIDE,k_Height-BOTTOMWIDE -  tempHegihtLen*i);
			graphics.DrawLine(&penLine,vpt_High[i],Gdiplus::PointF(vpt_High[i].X - 3,vpt_High[i].Y ));



			String  strLen= IntToStr(-35 + VERTICALSINGLE*i);
//			if("-15" == strLen || "0" == strLen || "15" == strLen)
			if(i !=0)
				graphics.DrawLine(&pen_Dash,vpt_High[i],Gdiplus::PointF(vpt_3.X ,vpt_High[i].Y ));

			graphics.DrawString(strLen.c_str(),-1,&font,Gdiplus::RectF(vpt_High[i].X-30, vpt_High[i].Y - FONTSIZE/2, 30, 10),sf,&brushPoint);

		}
	}
	__finally
	{
	   delete sf;
	}

	String strCaption =  "X Y";
//	graphics.DrawString(strCaption.c_str(),-1,&font,Gdiplus::PointF(50,20),&brushPoint);
	strCaption = "aX：";
	graphics.DrawString(strCaption.c_str(),-1,&fontXY,Gdiplus::PointF(50,20),&brushPoint);
	strCaption =  "aY：";
	graphics.DrawString(strCaption.c_str(),-1,&fontXY,Gdiplus::PointF(50,40),&brushPoint);

	strCaption = "bX：";
	graphics.DrawString(strCaption.c_str(),-1,&fontXY,Gdiplus::PointF(200,20),&brushPoint);
	strCaption =  "bY：";
	graphics.DrawString(strCaption.c_str(),-1,&fontXY,Gdiplus::PointF(200,40),&brushPoint);

}
//-----------------------------------------------------------------------------

void TCanvasSpectrum::DrawData(const vector<TSpectrumType> &spectrumData, int orderLine)
{
	Gdiplus::Graphics graphics(bmpSpectrum->Canvas->Handle);
	graphics.SetSmoothingMode(SmoothingModeHighQuality); //高画质、低速
	//画笔
	Pen penLine(Color::Color(PENLINE), 1);
	SolidBrush brushPoint(Color::Color(BRUSHPOINT));

	switch(orderLine)
	{
	case 0:
		break;
	case 1:
		penLine.SetColor(Color::Color(254,214,80));
		brushPoint.SetColor(Color::Color(254,214,80));
		graphics.FillRectangle(&brushPoint,Gdiplus::RectF(k_Width -150, (TOPHIHT/4)/2*7 - 5, 50, 10));
		break;
	case 2:
		penLine.SetColor(Color::Color(118,129,73));
		brushPoint.SetColor(Color::Color(118,129,73));
		graphics.FillRectangle(&brushPoint,Gdiplus::RectF(k_Width -150, (TOPHIHT/4)/2*5 - 5, 50, 10));
		break;
	case 3:
		penLine.SetColor(Color::Color(0,153,204));
		brushPoint.SetColor(Color::Color(0,153,204));
		graphics.FillRectangle(&brushPoint,Gdiplus::RectF(k_Width -150, (TOPHIHT/4)/2*3 - 5, 50, 10));
		break;
	case 4:
		penLine.SetColor(Color::Color(218,123,13));
		brushPoint.SetColor(Color::Color(218,123,13));
		graphics.FillRectangle(&brushPoint,Gdiplus::RectF(k_Width -150, (TOPHIHT/4)/2*1 - 5, 50, 10));
		break;
    }



	vector<Gdiplus::PointF>  vptData;
	Gdiplus::PointF tempVpt;
	int index = 0;
	for(int k = 0;k < spectrumData.size();k++)
	{   //计算数值
		index = (k_count-1)/2 + spectrumData[k].postion / ABSCISSASINGLE;
		tempVpt.X =  vpt_Width[index].X;

		int tempLen =  vpt_High[0].Y - vpt_High[1].Y;
		float xiaoshu = int(spectrumData[k].power*100) % 500;
		float OnceLen = (xiaoshu * tempLen) / 500;

		if(spectrumData[k].power <= -35)
		{
			tempVpt.Y = vpt_High[0].Y;
        }
		else if(spectrumData[k].power <= -30)
		{
		   tempVpt.Y = vpt_High[1].Y  - OnceLen;                //
		}
		else if(spectrumData[k].power <= -25)
		{
			tempVpt.Y = vpt_High[2].Y  - OnceLen;
		}
		else if(spectrumData[k].power <= -20)
		{
			tempVpt.Y = vpt_High[3].Y  - OnceLen;
		}
		else if(spectrumData[k].power <= -15)
		{
			tempVpt.Y = vpt_High[4].Y  - OnceLen;
		}
		else if(spectrumData[k].power <= -10)
		{
			tempVpt.Y = vpt_High[5].Y  - OnceLen;
		}
		else if(spectrumData[k].power <= -5)
		{
			tempVpt.Y = vpt_High[6].Y  - OnceLen;
		}
		else if(spectrumData[k].power <= 0)
		{
			tempVpt.Y = vpt_High[7].Y  - OnceLen;
		}
		else if(spectrumData[k].power < 5)
		{
			tempVpt.Y = vpt_High[7].Y  - OnceLen;
		}
		else if(spectrumData[k].power < 10)
		{
			tempVpt.Y = vpt_High[8].Y  - OnceLen;
		}
		else if(spectrumData[k].power < 15)
		{
			tempVpt.Y = vpt_High[9].Y  - OnceLen;
		}
		else if(spectrumData[k].power < 20)
		{
			tempVpt.Y = vpt_High[10].Y  - OnceLen;
		}
		else if(spectrumData[k].power < 25)
		{
			tempVpt.Y = vpt_High[11].Y  - OnceLen;
		}
		else if(spectrumData[k].power < 30)
		{
			tempVpt.Y = vpt_High[12].Y  - OnceLen;
		}
		else if(spectrumData[k].power >= 30)
		{
			tempVpt.Y = vpt_High[13].Y;
		}

		vptData.push_back(tempVpt);
	}
	//绘图形
	Gdiplus::PointF*  vptArrayData = new  Gdiplus::PointF[vptData.size()];
	try{
		for(int i = 0;i< vptData.size() ;i++)
		{
			Gdiplus::PointF vptBox[4];
			vptBox[0] = Gdiplus::PointF(vptData[i].X,vptData[i].Y - SPOTSIZE);
			vptBox[1] = Gdiplus::PointF(vptData[i].X + SPOTSIZE,vptData[i].Y );
			vptBox[2] = Gdiplus::PointF(vptData[i].X ,vptData[i].Y + SPOTSIZE);
			vptBox[3] = Gdiplus::PointF(vptData[i].X - SPOTSIZE,vptData[i].Y);
			graphics.FillPolygon(&brushPoint,vptBox,4);

			vptArrayData[i] = Gdiplus::PointF(vptData[i].X,vptData[i].Y);
		}
		//曲线
		GraphicsPath *gPath = new GraphicsPath();
		try{
		gPath->AddCurve(vptArrayData,vptData.size(),0,vptData.size()-1,0.4f);
		graphics.DrawPath(&penLine,gPath);
		}
		__finally{
		delete gPath;
        }
	}
	__finally
	{
		delete[] vptArrayData;
    }
}
//-----------------------------------------------------------------------------
void TCanvasSpectrum::DrawBasicData(const TSpectrumType& spData)
{
	Gdiplus::Graphics graphics(bmpSpectrum->Canvas->Handle);
	graphics.SetSmoothingMode(SmoothingModeHighQuality); //高画质、低速
	//画笔
	Pen penLine(Color::Color(PENLINE), 1);
	SolidBrush brushPoint(Color::Color(BRUSHPOINT));
	//字体
	FontFamily fontFamily(L"微软雅黑");
	Gdiplus::Font font(&fontFamily,FONTSIZE*2,FontStyleRegular,UnitPixel);

	String strCaption =  "辐射图";
//	graphics.DrawString(strCaption.c_str(),-1,&font,Gdiplus::PointF(50,20),&brushPoint);
	strCaption =  IntToStr(spData.postion) + "mm";
	graphics.DrawString(strCaption.c_str(),-1,&font,Gdiplus::PointF(50+FONTSIZE*4,20),&brushPoint);
	strCaption =  FloatToStr(spData.power) + "dBm";
	graphics.DrawString(strCaption.c_str(),-1,&font,Gdiplus::PointF(50+FONTSIZE*4,40),&brushPoint);
}
//-----------------------------------------------------------------------------

void TCanvasSpectrum::MoreDrawSpectrumLine(const vector<T> &moreSpectrumData,const vector<TSpectrumType> &spectrumDataIn)
{
	for(int i=0;i< moreSpectrumData.size(); i++)
	{
		DrawData(moreSpectrumData[i],i+1);
	}
	DrawData(spectrumDataIn,0);

}
void __fastcall TCanvasSpectrum::MoveLine(TPoint posXY)
{
	if(LEFTWIDE > posXY.X || k_Width-RIGHTWIDE < posXY.X) return ;
	if(posXY.Y < TOPHIHT || posXY.Y > k_Height -  BOTTOMWIDE) return ;

	Gdiplus::Graphics graphics(bmpSpectrum->Canvas->Handle);
	graphics.SetSmoothingMode(SmoothingModeHighQuality); //高画质、低速
	//画笔
	Pen penLine(Color::Color(254,0,0), 1);
	SolidBrush brushPoint(Color::Color(BRUSHPOINT));
	//字体
	FontFamily fontFamily(L"微软雅黑");
	Gdiplus::Font font(&fontFamily,FONTSIZE*2,FontStyleRegular,UnitPixel);

	graphics.DrawLine(&penLine,Gdiplus::PointF(posXY.X,TOPHIHT),Gdiplus::PointF(posXY.X,k_Height -  BOTTOMWIDE));
	graphics.DrawLine(&penLine,Gdiplus::PointF(LEFTWIDE,posXY.Y),Gdiplus::PointF(k_Width - RIGHTWIDE,posXY.Y));

	int temPostion = 0;
	for(int i = 0;i < vpt_Width.size(); i++)
	{
		if(abs(vpt_Width[i].X - posXY.X) < k_MinLen/2){
			temPostion = (i -  (k_count-1)/2) * ABSCISSASINGLE;
			for(int k = 0; k < k_spectrumType.size();k++)
			{
				if(k_spectrumType[k].postion == temPostion)
				{
					String strCaption =  "标记位置信息";
					strCaption = IntToStr(k_spectrumType[k].postion) + "mm";
					graphics.DrawString(strCaption.c_str(),-1,&font,Gdiplus::PointF(200+FONTSIZE*4,20),&brushPoint);
					strCaption = FloatToStr(k_spectrumType[k].power) + "dBm";
					graphics.DrawString(strCaption.c_str(),-1,&font,Gdiplus::PointF(200+FONTSIZE*4,40),&brushPoint);
					return;
				}
			}
		}


	}

}


