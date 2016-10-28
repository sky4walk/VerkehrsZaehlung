// (C) 2001 by Manfred Lippert und Andre Betz
// steht unter der Gnu Public Licence (GPL)

#include "bitmap.h"

class Motion
{
public:
  void GetDiffPic(Bitmap& PicOne,Bitmap& PicTwo,Bitmap& PicRes);
  void SetTreshHold(int iTreshHold);
protected:
  int m_iTreshHold;
};

