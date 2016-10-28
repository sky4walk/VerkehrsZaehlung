// (C) 2001 by 
// Andre Betz andre.betz@gmx.de

// Laplacefilter

#include <math.h>
#include "laplace.h"

LaplaceFilter::LaplaceFilter() 
{
}

LaplaceFilter::~LaplaceFilter() 
{
}

//eigentlicher Filter
Bitmap LaplaceFilter::Filter(Bitmap& Src) 
{
	int x, y;
	int val;
	Bitmap Dst(Src.GetDimX() - 2, Src.GetDimY() - 2);

	for(y = 1; y < Src.GetDimY() - 1; y++) {
		for(x = 1; x < Src.GetDimX() - 1; x++) {
			val = Src.GetGreyColor(x, y);
			val <<= 2;	// * 4
			val -= Src.GetGreyColor(x - 1, y);
			val -= Src.GetGreyColor(x + 1, y);
			val -= Src.GetGreyColor(x, y - 1);
			val -= Src.GetGreyColor(x, y + 1);
			if (val > 255) {
				val = 255;
			}
			if (val < 0) {
				val = 0;
			}
			Dst.SetGreyColor(x - 1, y - 1, (unsigned char)val);
		}
	}
	return Dst;
}
