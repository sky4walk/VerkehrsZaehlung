// (C) 2001 by 
// Manfred Lippert mani@mani.de
// Andre Betz andre.betz@gmx.de

#include "Matrix.h"
#include "bitmap.h"

#ifndef GAUSS
#define GAUSS

class Gauss
{
public:
	Gauss(int iKSize = 5);
	Bitmap GetBlur(Bitmap& xBmp);
protected:
	void PascalDreieck(int iTiefe);
	void GaussOperator();
	unsigned char GetValue(Bitmap& xAoi);
	Vector<int> m_xPascal;
	Matrix<unsigned long> m_xGaussOP;
	int m_iSum;
};

#endif GAUSS