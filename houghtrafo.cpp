// (C) 2001 by 
// Manfred Lippert mani@mani.de
// Andre Betz andre.betz@gmx.de

#include <math.h>
#include "houghtrafo.h"
#include "globals.h"

//rundet eine Zahl
int HoughTrafo::Round(double dZ)
{
	return (int)(dZ + 0.5);
}

// erzeugt den Houghraum von Linien
Matrix<unsigned long> HoughTrafo::TransLine(Bitmap& Bmp,int iXSize,int iYSize)
{
	int    iP;
	int    iAlpha;
	double fDTheta;
	double dP;
	Matrix<unsigned long> Hgh;

	fDTheta = PI / (double)(iXSize);

    Hgh.SetSize(iXSize,iYSize);
    Hgh.Clear();

	for(int iCountY=0;iCountY<Bmp.GetDimY();iCountY++)
	{
		for(int iCountX=0;iCountX<Bmp.GetDimX();iCountX++)
		{
			if(Bmp.GetGreyColor(iCountX,iCountY)!=0) 
			{
				for(iAlpha=0;iAlpha<iXSize;iAlpha++)
				{
					// p = x * cos(a) + y * sin(a) Geradengleichung
					dP = (double)(iCountX     - iXSize/2) * cos(fDTheta*(double)iAlpha) +
					     (double)(iCountY +1 - iYSize/2) * sin(fDTheta*(double)iAlpha) + 
					     (double)(iYSize/2);

//					dP = iCountY - tan(fDTheta*(double)iAlpha-iXSize/2) * iCountX + iYSize/2;

					iP = Round(dP);
					if((iP>0)&&(iP<iYSize))
					{
						Hgh.SetField(iAlpha,iP,Hgh.GetField(iAlpha,iP)+1);
					}
				}
			}
		}
	}

	return Hgh;
}

// liefert den Maximalwert aus dem Houghraum und die Position und Winkel
unsigned long HoughTrafo::GetMax(Matrix<unsigned long>& xHough,int& iMaxAlpha,int& iMaxP)
{
	unsigned long ulAlpha;
	unsigned long ulP;
	unsigned long ulMax = 0;

	for(ulAlpha=0;ulAlpha<xHough.GetDimX();ulAlpha++)
	{
		for(ulP=0;ulP<xHough.GetDimY();ulP++)
		{
			unsigned long erg = xHough.GetField(ulAlpha,ulP);
			if(erg>ulMax) 
			{
				ulMax = erg;
				iMaxAlpha = ulAlpha;
				iMaxP = ulP;
			}
		}
	}

	return ulMax;
}

// liefert den Maximalwert aus dem Houghraum und die Position
unsigned long HoughTrafo::GetMax(Vector<unsigned long>& xHough,int& iMaxP)
{
	unsigned long ulP;
	unsigned long ulMax = 0;

	for(ulP=0;ulP<xHough.GetDim();ulP++)
	{
		unsigned long erg = xHough.GetField(ulP);
		if(erg>ulMax) 
		{
			ulMax = erg;
			iMaxP = ulP;
		}
	}

	return ulMax;
}

// löscht an einer Stelle im Houghraum einen Bereich
void HoughTrafo::DelMax(Matrix<unsigned long>& xHough,int iMaxAlpha,int iMaxP,int iDelSize)
{
	int iAlpha;
	int iP;
	int iDelSizeHalf = iDelSize / 2;

	for(iAlpha=0;iAlpha<iDelSize;iAlpha++)
	{
		for(iP=0;iP<iDelSize;iP++)
		{
			xHough.SetField(iMaxAlpha+iAlpha-iDelSizeHalf,iMaxP+iP-iDelSizeHalf,0);
		}
	}
}

// malt eine Linie in ein Bitmap hinein
void HoughTrafo::DrawLine(Bitmap& xOrig,int iMaxAlpha,int iMaxP,Matrix<unsigned long>& xHough)
{
	int iDimX  = xHough.GetDimX();
	int iDimY  = xHough.GetDimY();
	int iCount;
	double dy;
	double dMaxAlpha = (double)iMaxAlpha * PI / (double)(iDimX);

	if((dMaxAlpha>PI/4)&&(dMaxAlpha<PI*3/4))
	{
		for(iCount=0;iCount<xOrig.GetDimX();iCount++)
		{
			dy = ((double)iMaxP - (double)(iCount - iDimX/2) * cos(dMaxAlpha) - iDimY/2) /  
				sin(dMaxAlpha) -1 + iDimY/2;
			int y = Round(dy);
			if(y>0)
				xOrig.SetGreyColor(iCount,y,255);
		}
	}
	else
	{
		for(iCount=0;iCount<xOrig.GetDimY();iCount++)
		{
			dy = ((double)iMaxP - (double)(iCount +1 -iDimY) * sin(dMaxAlpha) - iDimY/2) / 
				cos(dMaxAlpha) + iDimX/2;
			int y = Round(dy);
			if(y>0)
				xOrig.SetGreyColor(y,iCount,255);
		}
	}
}

// wandelt Houghraum in ein Bitmap um
Bitmap HoughTrafo::DrawHough(Matrix<unsigned long>& xHough,unsigned long ulMax)
{
	int iDimX = xHough.GetDimX();
	int iDimY = xHough.GetDimY();
	int iAlpha;
	int iP;
	Bitmap xOrig;

	xOrig.NeuesBild(iDimX,iDimY);
	for(iAlpha=0;iAlpha<iDimX;iAlpha++)
	{
		for(iP=0;iP<iDimY;iP++)
		{
			unsigned long erg = xHough.GetField(iAlpha,iP);
			xOrig.SetGreyColor(iAlpha,iP,(unsigned char)(erg*255/ulMax));
		}
	}

	return xOrig;
}

// liefert den Houghraum zu Kreisen
Matrix<unsigned long> HoughTrafo::TransCircle(Bitmap& Bmp,int iRadius,int iXSize,int iYSize)
{
	int   iP;
	int   iLength;
	int   iAlpha;
	float fDTheta;
	int	  iMax = 0;
	Matrix<unsigned long> Hgh;

	if(Bmp.GetDimX()<Bmp.GetDimY()) iLength = Bmp.GetDimX();
	else                            iLength = Bmp.GetDimY();

	fDTheta = (float)PI / (float)iLength;

    Hgh.SetSize(iXSize,iYSize);
    Hgh.Clear();

	for(int iCountY=0;iCountY<iYSize;iCountY++)
	{
		for(int iCountX=0;iCountX<iXSize;iCountX++)
		{
			if(Bmp.GetGreyColor(iCountX,iCountY)!=0) 
			{
				for(iAlpha=0;iAlpha<iXSize;iAlpha+=1)
				{
					iP = (int)((float)iCountX - sqrt((float)(iRadius * iRadius -
							   (iCountY /*+1*/ - iAlpha) * (iCountY /*+1*/ - iAlpha))));

					if((iP>0)&&(iP<iYSize))
					{
						Hgh.SetField(iAlpha,iP,Hgh.GetField(iAlpha,iP)+1);
					}
				} 
			}
		}
	}

	return Hgh;
}

// findet den Mittelpunkt 
Matrix<unsigned long> HoughTrafo::CircleMiddle(Bitmap& xEdgeFrc,Bitmap& xEdgeAng,int iRadius,int iTolRad,int iTolAng,int iAngRes)
{
	int iAngle1;
	int iAngle2;
	int iCountX;
	int iCountY;
	int iAng;

	Matrix<unsigned long> Hgh;
    Hgh.SetSize(xEdgeFrc.GetDimX(),xEdgeFrc.GetDimY());
	Hgh.Clear();


	for(iCountY=0;iCountY<xEdgeFrc.GetDimY();iCountY++)
	{
		for(iCountX=0;iCountX<xEdgeFrc.GetDimX();iCountX++)
		{
			if(xEdgeFrc.GetGreyColor(iCountX,iCountY)!=0) 
			{
				iAngle1 = xEdgeAng.GetGreyColor(iCountX,iCountY);
				iAngle1 += 90;			    // Senkrechte Mittelachse
				iAngle2 = iAngle1 + 180;  // Gegenueberliegende Achse

			    for(iAng=0;iAng<=iTolAng;iAng++)
				{
					DrawLine(Hgh,iCountX,iCountY,iAngle1*iAngRes+iAng-iTolAng/2,iRadius,iTolRad,iAngRes);
					DrawLine(Hgh,iCountX,iCountY,iAngle2*iAngRes+iAng-iTolAng/2,iRadius,iTolRad,iAngRes);
				}
			}
		}
	}

	return Hgh;
}

//zeichnet eine Linie in den Houghraum 
void HoughTrafo::DrawLine(Matrix<unsigned long>& xOrig,int iXStart,int iYStart,int iGrad,int iBegin,int iLength,int AngRes)
{
	double dBogen = PI * (double)iGrad / (double)(180 * AngRes);
	int iCount;
	int iEnd;
	unsigned int y;
	unsigned int x;
	int dir = 1;

	iGrad %= (360*AngRes);

	if((iGrad>=0 && iGrad<(45*AngRes))||(iGrad>=(135*AngRes) && iGrad<(225*AngRes))||iGrad>=(315*AngRes))
	{
		iEnd = (int)((double)iLength * cos(dBogen));
		if(iEnd<0) 
		{
			iEnd *= -1;
			dir = -1;
		}

		for(iCount=0;iCount<iEnd;iCount++)
		{
			y = (int)((double)iCount * dir * sin(dBogen) / cos(dBogen));
			y = y + iYStart + (int)((double)iBegin * sin(dBogen));
			x = iCount * dir + iXStart + (int)((double)iBegin * cos(dBogen));

			if(y>=0 && y<xOrig.GetDimY())
			{
				xOrig.SetField(x,y,xOrig.GetField(x,y)+1);
			}
		}
	}
	else
	{
		iEnd = (int)((double)iLength * sin(dBogen));
		if(iEnd<0) 
		{
			iEnd *= -1;
			dir = -1;
		}

		for(iCount=0;iCount<iEnd;iCount++)
		{
			x = (int)((double)iCount * dir * cos(dBogen) / sin(dBogen));
			y = iCount * dir + iYStart + (int)((double)iBegin * sin(dBogen));
			x = x + iXStart + (int)((double)iBegin * cos(dBogen));

			if(y>=0 && y<xOrig.GetDimY())
			{
				xOrig.SetField(x,y,xOrig.GetField(x,y)+1);
			}
		}
	}
}

// zeichnet einen Kreis
void HoughTrafo::DrawCircle(Bitmap& xOrig,int iXPos,int iYPos,int iRad)
{
	int iCount;
	int AngRes = 1;
	int iXCPnt;
	int iYCPnt;
	double dBogen;

	for(iCount=0;iCount<360;iCount++)
	{
		dBogen = PI * (double)iCount / (double)(180 * AngRes);
		iXCPnt = iYPos + (int)(iRad * cos(dBogen));
		iYCPnt = iXPos + (int)(iRad * sin(dBogen));
		xOrig.SetGreyColor(iXCPnt,iYCPnt,255);
	}
}

// sucht nach Kreisen durch die Kreisformel
Vector<unsigned long> HoughTrafo::CircleRadius(Bitmap& xEdgeFrc,int iPosX,int iPosY)
{
	int len;
	int iCountX;
	int iCountY;

	Vector<unsigned long> Vec;
	
	if(xEdgeFrc.GetDimX()>xEdgeFrc.GetDimY())	len = xEdgeFrc.GetDimX();
	else										len = xEdgeFrc.GetDimY();
	Vec.SetSize(len);
	Vec.Clear();

	for(iCountY=0;iCountY<xEdgeFrc.GetDimY();iCountY++)
	{
		for(iCountX=0;iCountX<xEdgeFrc.GetDimX();iCountX++)
		{
			if(xEdgeFrc.GetGreyColor(iCountX,iCountY)!=0) 
			{
				int Dist = (int)sqrt((double)((iPosX - iCountX)*(iPosX - iCountX) + 
					(iPosY - iCountY)*(iPosY - iCountY)));

				if(Dist<len)
					Vec.SetField(Dist,Vec.GetField(Dist)+1);
			}
		}
	}

	return Vec;
}

// holt die Grauwerte aus einer Linie vom Quellbild von oben nach unten
// und speichert sie in an einer Position im Zielbild
void HoughTrafo::GetLine(Bitmap &dst,Vector<unsigned char>&Vec,int x1,int y1,int x2,int y2,int d)
{
	int x     = x1;
	int y     = y1;
	int xl    = x2 - x1;
	int yl    = y2 - y1;
	int stepx = 1;
	int stepy = 1;
	int	dy = (int)sqrt((y1-y2)*(y1-y2)+(x1-x2)*(x1-x2));

	Vec.SetSize(dy);

	if(xl<0)
	{ 
		stepx = -1; 
		xl    = -xl; 
	}
  
	if(yl<0) 
	{ 
		stepy = -1; 
		yl    = -yl; 
	}
  
	if(xl>=yl) 
	{ 
		draw_HN(dst,Vec,xl,yl,stepx,stepy,x,y,x,y,d); 
	} 
	else 
	{ 
		draw_HN(dst,Vec,yl,xl,stepy,stepx,y,x,x,y,d);
	}
}

void HoughTrafo::draw_HN(Bitmap &src,Vector<unsigned char> &Vec,int haupt,int neben,int h_delta,int n_delta,int &h,int &n,int &x,int &y,int d) 
{
	unsigned char Col;
	int i;
	int Zaehler = haupt / 2;

	Col = src.GetGreyColor(x,y);
	Vec.SetField(y,Col);
	if(d) src.SetGreyColor(x,y,d-1);

	for(i=0;i<haupt;i++) 
	{ 
		Zaehler += neben;
		if (Zaehler >= haupt) 
		{
			Zaehler -= haupt;
			n += n_delta;
		}
		h += h_delta;   
		
		Col = src.GetGreyColor(x,y);
		Vec.SetField(i,Col);
		if(d) src.SetGreyColor(x,y,d-1);
	}
}

double HoughTrafo::Distanz(Vector<unsigned char> &Vec1,Vector<unsigned char> &Vec2)
{
	unsigned int iCount;
	double temp = 0.0;

	for(iCount=0;iCount<Vec1.GetDim();iCount++)
	{
		temp += (Vec1.GetField(iCount)-Vec2.GetField(iCount))*(Vec1.GetField(iCount)-Vec2.GetField(iCount));
	}
	return sqrt(temp);
}

double HoughTrafo::Distanz(Bitmap &bmp1,Bitmap &bmp2)
{
	int iCountX;
	int iCountY;
	unsigned int a;
	unsigned int b;
	double temp = 0.0;

	for(iCountX=0;iCountX<bmp1.GetDimX();iCountX++)
	{
		for(iCountY=0;iCountY<bmp1.GetDimY();iCountY++)
		{
			a = (unsigned int)bmp1.GetGreyColor(iCountX,iCountY);
			b = (unsigned int)bmp2.GetGreyColor(iCountX,iCountY);

			temp += (a - b)*(a - b);
		}
	}
	return sqrt(temp);
}

double HoughTrafo::Eigen(Bitmap &bmp1)
{
	int iCountX;
	int iCountY;
	unsigned int a;
	double temp = 0.0;

	for(iCountX=0;iCountX<bmp1.GetDimX();iCountX++)
	{
		for(iCountY=0;iCountY<bmp1.GetDimY();iCountY++)
		{
			a = (unsigned int) bmp1.GetGreyColor(iCountX,iCountY);
			temp += (a * a);
		}
	}
	return sqrt(temp);
}

Bitmap HoughTrafo::Mittelwert(Bitmap &bmp1,Bitmap &bmp2)
{
	int iCountX;
	int iCountY;
	unsigned int mit;
	unsigned int a;
	unsigned int b;
	Bitmap ret(bmp1.GetDimX(),bmp1.GetDimY());

	for(iCountX=0;iCountX<bmp1.GetDimX();iCountX++)
	{
		for(iCountY=0;iCountY<bmp1.GetDimY();iCountY++)
		{
			a = (unsigned int)bmp1.GetGreyColor(iCountX,iCountY);
			b = (unsigned int)bmp2.GetGreyColor(iCountX,iCountY);
			mit = (unsigned int)((a + b) / 2);
			ret.SetGreyColor(iCountX,iCountY,(unsigned char)mit);
		}
	}
	return ret;
}

Bitmap HoughTrafo::Mittelwert(CHistogram &hist)
{
	int iCountX;
	int iCountY;
	unsigned long a;
	unsigned long b;
	Bitmap ret;
	Bitmap tmp;
	Matrix<unsigned long> mat;

	if(hist.GetAnz())
	{
		hist.Reset();
		while(hist.GetNext(tmp))
		{
			if(hist.GetPos()==1)
			{
				ret.NeuesBild(tmp.GetDimX(),tmp.GetDimY());
				mat.SetSize(tmp.GetDimX(),tmp.GetDimY());
				mat.Clear();
			}

			for(iCountX=0;iCountX<tmp.GetDimX();iCountX++)
			{
				for(iCountY=0;iCountY<tmp.GetDimY();iCountY++)
				{
					a = (unsigned long)tmp.GetGreyColor(iCountX,iCountY);
					b = (unsigned long)mat.GetField(iCountX,iCountY);
					mat.SetField(iCountX,iCountY,a+b);
				}
			}
		}

		for(iCountX=0;iCountX<tmp.GetDimX();iCountX++)
		{
			for(iCountY=0;iCountY<tmp.GetDimY();iCountY++)
			{
				a = (unsigned long)mat.GetField(iCountX,iCountY);
				b = (unsigned char)(a / hist.GetAnz());
				ret.SetGreyColor(iCountX,iCountY,(unsigned char)b);
			}
		}
	}

	return ret;
}