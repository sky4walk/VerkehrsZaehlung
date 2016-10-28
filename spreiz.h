// (C) 2001 by 
// Manfred Lippert mani@mani.de
// Andre Betz andre.betz@gmx.de

#include "bitmap.h"

#ifndef SPREIZ
#define SPREIZ

class SpreizFilter
{
public:
  SpreizFilter();
  ~SpreizFilter();
  Bitmap filter(Bitmap& Src,int promille_schranke = 10);
protected:
	long grey_count[256];
};

#endif