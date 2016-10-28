// (C) 2001 by 
// Andre Betz andre.betz@gmx.de

// spreizt den Farbraum

#include "spreiz.h"
#include <string.h>

SpreizFilter::SpreizFilter() 
{
}

SpreizFilter::~SpreizFilter() 
{
}

Bitmap SpreizFilter::filter(Bitmap& Src,int promille_schranke) 
{
	int x, y;
	int min_grey;
	int max_grey;
	long count;
	long pixel_count = Src.GetDimX() * (long)Src.GetDimY();
	Bitmap Dst;

	Dst.NeuesBild(Src.GetDimX(), Src.GetDimY());

	if (promille_schranke == 0) 
	{

		int grey;
		min_grey = max_grey = Src.GetGreyColor(0, 0);
		for(y = 0; y < Src.GetDimY(); y++) 
		{
			for(x = 0; x < Src.GetDimX(); x++) 
			{
				grey = Src.GetGreyColor(x, y);
				if (grey < min_grey) 
				{
					min_grey = grey;
				}
				if (grey > max_grey) 
				{
					max_grey = grey;
				}
			}
		}
	}
	else
	{
		memset(grey_count, 0, sizeof(grey_count));

		for(y = 0; y < Src.GetDimY(); y++) 
		{
			for(x = 0; x < Src.GetDimX(); x++) 
			{
				grey_count[Src.GetGreyColor(x, y)]++;
			}
		}

		count = 0;
		for(min_grey = 0; min_grey <= 255; min_grey++) 
		{
			count += grey_count[min_grey];
			if ((count * 1000 + (pixel_count >> 1)) / pixel_count >= promille_schranke) 
			{
				break;
			}
		}

		count = 0;
		for(max_grey = 255; max_grey >= 0; max_grey--) 
		{
			count += grey_count[max_grey];
			if ((count * 1000 + (pixel_count >> 1)) / pixel_count >= promille_schranke) 
			{
				break;
			}
		}
	}
	if (min_grey >= max_grey) {	// Sonderfall: es kommt nur ein ausschlaggebender Grauwert im Bild vor
		for(y = 0; y < Dst.GetDimY(); y++) 
		{
			for(x = 0; x < Dst.GetDimX(); x++) 
			{
				Dst.SetGreyColor(x, y, (unsigned char)min_grey);
			}
		}
	} 
	else 
	{								// allgemeiner Fall (Spreizung):

		int grey;
		int grey_width = (max_grey - min_grey);

		for(y = 0; y < Src.GetDimY(); y++) 
		{
			for(x = 0; x < Src.GetDimX(); x++) 
			{
				grey = Src.GetGreyColor(x, y);
				grey = ((grey - min_grey) * 255 + (grey_width >> 1)) / grey_width;
				if (grey < 0) 
				{
					grey = 0;
				}
				if (grey > 255) 
				{
					grey = 255;
				}
				Dst.SetGreyColor(x, y, (unsigned char)grey);
			}
		}
	}

	return Dst;
}
