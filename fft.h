// (C) 2001 by Manfred Lippert und Andre Betz
// steht unter der Gnu Public Licence (GPL)

#ifndef __FASTFOURIER_H__
#define __FASTFOURIER_H__

extern bool fft_1d(double *data, int nn, int isign);
extern bool fft_2d(double data[], int nn, int mm, int isign);

#endif
