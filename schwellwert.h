// (C) 2001 by 
// Manfred Lippert mani@mani.de
// Andre Betz andre.betz@gmx.de

#include "bitmap.h"

class SchwellwertFilter
{
public:
  SchwellwertFilter();
  ~SchwellwertFilter();
  Bitmap filter(Bitmap& Src,int threshold = 128);
  Bitmap filter_average(Bitmap& Src);
};
