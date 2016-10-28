// (C) 2001 by Manfred Lippert und Andre Betz
// steht unter der Gnu Public Licence (GPL)
#include <math.h>
#include "unsharp.h"

UnsharpFilter::UnsharpFilter() 
{
}

UnsharpFilter::~UnsharpFilter() 
{
}

void UnsharpFilter::filter(Bitmap& Src, Bitmap& Dst) 
{
	int x, y;
	int val;

	Dst.NeuesBild(Src.GetDimX() - 2, Src.GetDimY() - 2);

	for(y = 1; y < Src.GetDimY() - 1; y++) {
		for(x = 1; x < Src.GetDimX() - 1; x++) {
			val = Src.GetGreyColor(x, y);
			val += Src.GetGreyColor(x - 1, y);
			val += Src.GetGreyColor(x + 1, y);
			val += Src.GetGreyColor(x, y - 1);
			val += Src.GetGreyColor(x, y + 1);
			val += Src.GetGreyColor(x - 1, y - 1);
			val += Src.GetGreyColor(x + 1, y - 1);
			val += Src.GetGreyColor(x - 1, y + 1);
			val += Src.GetGreyColor(x + 1, y + 1);
			val /= 9;
			Dst.SetGreyColor(x - 1, y - 1, (unsigned char)val);
		}
	}
}
