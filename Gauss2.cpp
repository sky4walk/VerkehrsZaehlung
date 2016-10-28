// (C) 2001 by 
// Andre Betz andre.betz@gmx.de

// Gauss-Filter
#include "Gauss2.h"
#include <iostream.h>

//Konstruktor erzeugt Gausskernal
Gauss::Gauss(int iKSize)
{
	m_iSum = 0;
	PascalDreieck(iKSize);
	GaussOperator();
}

//konstruiert aus pascalschem Dreieck den 2D-Faltungsoperator
void Gauss::GaussOperator()
{
	int iCount1;
	int iCount2;
	unsigned long iTmp;
	int iTiefe = m_xPascal.GetDim();
	m_xGaussOP.SetSize(iTiefe,iTiefe);

	for(iCount1=0;iCount1<iTiefe;iCount1++)
	{
		for(iCount2=0;iCount2<iTiefe;iCount2++)
		{
			iTmp = m_xPascal.GetField(iCount1) * m_xPascal.GetField(iCount2);
			m_xGaussOP.SetField(iCount1,iCount2,iTmp);
			m_iSum += iTmp;
		}
	}
}

// erzeugt das Pascal-Dreieck mit in der angegebenen Tiefe
void Gauss::PascalDreieck(int iTiefe)
{
	int iCount1;
	int iCount2;
	int iTmp1;
	int iTmp2;

	m_xPascal.SetSize(iTiefe);

	for(iCount1=1;iCount1<=iTiefe;iCount1++)
	{
		for(iCount2=0;iCount2<iCount1;iCount2++)
		{
			if((iCount2==0)||(iCount2==iCount1-1))
			{
				iTmp2 = 1;
				m_xPascal.SetField(iCount2,iTmp2);
			}
			else
			{
				iTmp1 = m_xPascal.GetField(iCount2) + iTmp2;
				iTmp2 = m_xPascal.GetField(iCount2);
				m_xPascal.SetField(iCount2,iTmp1);
			}
		}
	}
}

// wendet den Filter auf das Bild an
Bitmap Gauss::GetBlur(Bitmap& xBmp)
{
	Bitmap xResult;
	Bitmap xArea;
	int iOpSize = m_xPascal.GetDim();
	int iSizeX = xBmp.GetDimX();
	int iSizeY = xBmp.GetDimY();
	int iCenterPos = iOpSize / 2;
	int iCountX;
	int iCountY;
	unsigned char ulTmp;

	xResult.NeuesBild(iSizeX,iSizeY);

	for(iCountY=0;iCountY<iSizeY;iCountY++) 
	{
		for(iCountX=0;iCountX<iSizeX;iCountX++) 
		{
			xArea = xBmp.GetGreyAoi(iCountX-iCenterPos,iCountY-iCenterPos,iOpSize,iOpSize);
			ulTmp = GetValue(xArea);
			xResult.SetGreyColor(iCountX,iCountY,ulTmp);
		}
	}

	return xResult;
}

// bearbeitet den Ausschnitt
unsigned char Gauss::GetValue(Bitmap& xAoi)
{
	int iSizeX = xAoi.GetDimX();
	int iSizeY = xAoi.GetDimY();
	int iCountX;
	int iCountY;
	unsigned long ulSum = 0;
	unsigned char ucRes = 0;

	for(iCountY=0;iCountY<iSizeY;iCountY++) 
	{
		for(iCountX=0;iCountX<iSizeX;iCountX++) 
		{
			ulSum += xAoi.GetGreyColor(iCountX,iCountY) * m_xGaussOP.GetField(iCountX,iCountY);
		}
	}
	
	ucRes = (unsigned char)(ulSum / m_iSum);
	return ucRes;
}
