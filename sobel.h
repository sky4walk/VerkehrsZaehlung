// (C) 2001 by 
// Manfred Lippert mani@mani.de
// Andre Betz andre.betz@gmx.de

#include "bitmap.h"

#ifndef SOBEL
#define SOBEL

class SobelFilter
{
public:
  SobelFilter(int opt = 0);
  ~SobelFilter();
  void SetTreshHold(int iTreshHold);
  void GetEdges(Bitmap& xOrig,Bitmap& xEdgeX,Bitmap& xEdgeY);
protected:
	int m_Opt;
  int  m_iTreshHold;
  int* m_piXFilter;
  int* m_piYFilter;
  double  m_dMaxValue;
};

#endif