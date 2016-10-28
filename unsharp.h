// (C) 2001 by Manfred Lippert und Andre Betz
// steht unter der Gnu Public Licence (GPL)

#include "bitmap.h"

class UnsharpFilter
{
public:
  UnsharpFilter();
  ~UnsharpFilter();
  void filter(Bitmap& Src, Bitmap& Dst);
protected:
};
