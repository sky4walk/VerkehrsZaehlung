// (C) 2001 by 
// Andre Betz andre.betz@gmx.de

// Schwellwertfilter

#include "schwellwert.h"

SchwellwertFilter::SchwellwertFilter() 
{
}

SchwellwertFilter::~SchwellwertFilter() 
{
}

Bitmap SchwellwertFilter::filter(Bitmap& Src,int threshold) 
{
	int x, y;
	Bitmap Dst;

	Dst.NeuesBild(Src.GetDimX(), Src.GetDimY());

	for(y = 0; y < Src.GetDimY(); y++) 
	{
		for(x = 0; x < Src.GetDimX(); x++) 
		{
			Dst.SetGreyColor(x, y, (unsigned char)(Src.GetGreyColor(x, y) >= threshold ? 255 : 0));
		}
	}
	return Dst;
}

Bitmap SchwellwertFilter::filter_average(Bitmap& Src) 
{
	Bitmap Dst;
	long average = 0;
	int x, y;
	for(y = 0; y < Src.GetDimY(); y++) 
	{
		for(x = 0; x < Src.GetDimX(); x++) 
		{
			average += Src.GetGreyColor(x, y);
		}
	}
	average /= Src.GetDimX();
	average /= Src.GetDimY();
	Dst = filter(Src,average);
	return Dst;
}
