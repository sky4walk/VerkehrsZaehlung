// (C) 2001 by Manfred Lippert und Andre Betz
// steht unter der Gnu Public Licence (GPL)

#include "bitmap.h"

class GaussFilter
{
public:
  GaussFilter(int width);
  ~GaussFilter();
  void set_width(int width);
  void filter(Bitmap& Src, Bitmap& Dst);
protected:
	int width;
	long *matrix;
	long sum;
};
