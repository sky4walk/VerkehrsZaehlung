// (C) 2001 by 
// Andre Betz andre.betz@gmx.de

// Sobelfilter

#include <math.h>
#include "sobel.h"
#include "globals.h"
#define  XFLTSIZE 3
#define  YFLTSIZE 3

SobelFilter::SobelFilter(int opt)
{  
	m_Opt = opt;
  int iTmpXOpt[XFLTSIZE*YFLTSIZE] = {	+3,+10,+3,
			    						 0,  0, 0,
				    					-3,-10,-3};

  int iTmpYOpt[XFLTSIZE*YFLTSIZE] = {	 +3,0, -3,
					    				+10,0,-10,
						    			 +3,0, -3};

  int iTmpX[XFLTSIZE*YFLTSIZE] = {	+1,+2,+1,
									 0, 0, 0,
									-1,-2,-1};

  int iTmpY[XFLTSIZE*YFLTSIZE] = {	+1,0,-1,
									+2,0,-2,
									+1,0,-1};

  m_iTreshHold = 0;
  m_piXFilter  = new int[XFLTSIZE*YFLTSIZE];
  m_piYFilter  = new int[XFLTSIZE*YFLTSIZE];

  for(int iCount=0;iCount<XFLTSIZE*YFLTSIZE;iCount++)
  {
	  if(opt)
	  {
		m_piXFilter[iCount] = iTmpXOpt[iCount]; 
		m_piYFilter[iCount] = iTmpYOpt[iCount]; 
	  }
	  else
	  {
		m_piXFilter[iCount] = iTmpX[iCount]; 
		m_piYFilter[iCount] = iTmpY[iCount]; 
	  }
  }

  m_dMaxValue = 0.0;
}

SobelFilter::~SobelFilter()
{
  delete m_piXFilter;
  delete m_piYFilter;
}

void SobelFilter::SetTreshHold(int iTreshHold)
{
  m_iTreshHold = iTreshHold;
}

void SobelFilter::GetEdges(Bitmap& xOrig,Bitmap& xEdgeX,Bitmap& xEdgeY)
{
  int iXPos;
  int iYPos;
  int iFltField[XFLTSIZE*YFLTSIZE];
  int iXEdge;
  int iYEdge;
  double dEdgeForce;
  double dEdgeDegree;

  xEdgeX.NeuesBild(xOrig.GetDimX()-2,xOrig.GetDimY()-2);
  xEdgeY.NeuesBild(xOrig.GetDimX()-2,xOrig.GetDimY()-2);

  for(iYPos=1;iYPos<xOrig.GetDimY()-1;iYPos++)
  {
    for(iXPos=1;iXPos<xOrig.GetDimX()-1;iXPos++)
	{
	  iFltField[0] = (int)xOrig.GetGreyColor(iXPos-1,iYPos-1);
	  iFltField[1] = (int)xOrig.GetGreyColor(iXPos  ,iYPos-1);
	  iFltField[2] = (int)xOrig.GetGreyColor(iXPos+1,iYPos-1);
	  iFltField[3] = (int)xOrig.GetGreyColor(iXPos-1,iYPos);
	  iFltField[4] = (int)xOrig.GetGreyColor(iXPos  ,iYPos);
	  iFltField[5] = (int)xOrig.GetGreyColor(iXPos+1,iYPos);
	  iFltField[6] = (int)xOrig.GetGreyColor(iXPos-1,iYPos+1);
	  iFltField[7] = (int)xOrig.GetGreyColor(iXPos  ,iYPos+1);
	  iFltField[8] = (int)xOrig.GetGreyColor(iXPos+1,iYPos+1);

	  iXEdge = 0;
	  iYEdge = 0;

	  for(int iCount=0;iCount<XFLTSIZE*YFLTSIZE;iCount++)
	  {
	    iXEdge += iFltField[iCount]*m_piXFilter[iCount];
	    iYEdge += iFltField[iCount]*m_piYFilter[iCount];
	  }

		if(m_Opt)
		{
			iXEdge /= 32; // ????
			iYEdge /= 32; // ????
		}
		else
		{
			iXEdge /= 8;
			iYEdge /= 8;
		}

  	  dEdgeForce  = sqrt(double(iXEdge*iXEdge + iYEdge*iYEdge));

	  if(dEdgeForce>0)
	  {
		dEdgeDegree = acos((double)iXEdge / dEdgeForce);
		dEdgeDegree = 180.0 * dEdgeDegree / PI;
	  }
	  else
		  dEdgeDegree = 0.0;

	  if(dEdgeForce<(double)m_iTreshHold) 
	  {
		  dEdgeForce = 0.0;
		  dEdgeDegree = 0.0;
	  }

	  xEdgeX.SetGreyColor(iXPos-1,iYPos-1,(unsigned char)dEdgeForce);
	  xEdgeY.SetGreyColor(iXPos-1,iYPos-1,(unsigned char)dEdgeDegree);
	}
  }
}