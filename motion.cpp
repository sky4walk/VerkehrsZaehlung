// (C) 2001 by 
// Andre Betz andre.betz@gmx.de

#include "motion.h"

void Motion::SetTreshHold(int iTreshHold)
{
  m_iTreshHold = iTreshHold;
}

void Motion::GetDiffPic(Bitmap& PicOne,Bitmap& PicTwo,Bitmap& PicRes)
{
  if((PicOne.GetDimX()!=PicTwo.GetDimX())&&(PicOne.GetDimY()!=PicTwo.GetDimY()))
    return;
  
  PicRes.NeuesBild(PicOne.GetDimX(),PicOne.GetDimY());
  for(int iCountY=0;iCountY<PicOne.GetDimY();iCountY++)
  {
    for(int iCountX=0;iCountX<PicOne.GetDimX();iCountX++)
	{
	  int iDiff = PicOne.GetGreyColor(iCountX,iCountY) - PicTwo.GetGreyColor(iCountX,iCountY);
	  if(iDiff<0) iDiff *= -1;

	  if(iDiff < m_iTreshHold) iDiff = 0;
	  PicRes.SetGreyColor(iCountX,iCountY,(unsigned char)iDiff);
	}
  }
}
