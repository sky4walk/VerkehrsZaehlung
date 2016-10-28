// (C) 2001 by 
// Manfred Lippert mani@mani.de
// Andre Betz andre.betz@gmx.de

#include "bitmap.h"
#ifndef LAPLACE
#define LAPLACE

class LaplaceFilter
{
public:
  LaplaceFilter();
  ~LaplaceFilter();
  Bitmap Filter(Bitmap& Src);
protected:
};

#endif