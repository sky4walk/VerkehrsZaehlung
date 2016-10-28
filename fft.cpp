// (C) 2001 by 
// Andre Betz andre.betz@gmx.de

#include <math.h>
#include "fft.h"

#define SWAP(a,b) tempr=(a); (a)=(b); (b)=tempr
#define TWOPI 6.28318530717959

/*---------------------------------------------------------------------------*/
/* Purpose:  This routine replaces DATA by its one-dimensional discrete      */
/*           transform if ISIGN=1 or replaces DATA by its inverse transform  */
/*           if ISIGN=-1.  DATA is a complex array of length NN which is     */
/*           input as a real array of length 2*NN.  NN must be an integer    */
/*           power of 2 or the routine will abort and return FALSE.          */
/*---------------------------------------------------------------------------*/
char fft_1d(double *data, int nn, int isign) 
{
	int n, mmax, m, j, istep, i;
	double wtemp, wr, wi, wpr, wpi, theta;
	double tempr, tempi;

	/* Fix indexing problems (code is a translation of fortran with 1-based indexing) */
	data = data - 1;

	/* Error checking section */
	i = 1;
	j = nn;
	while (j > 1) {
		i = i << 1;
		j = j >> 1;
	}
	if (nn != i) {
		return false;
	}

	/* Bit reversal section */
	n = nn << 1;
	j = 1;
	for (i = 1; i < n; i += 2) {
		if (j > i) {
			SWAP(data[j], data[i]);
			SWAP(data[j + 1], data[i + 1]);
		}
		m = n >> 1;
		while (m >= 2 && j > m) {
			j -= m;
			m = m >> 1;
		}
		j += m;
	}

	/* Danielson-Lanczos section */
	mmax = 2;
	while (n > mmax) {
		istep = 2 * mmax;
		theta = TWOPI / (isign * mmax);
		wtemp = sin(0.5 * theta);
		wpr = -2.0 * wtemp * wtemp;
		wpi = sin(theta);
		wr = 1.0;
		wi = 0.0;
		for (m = 1; m < mmax; m += 2) {
			for (i = m; i <= n; i += istep) {
				j = i + mmax;
				tempr = (double) (wr * data[j] - wi * data[j + 1]);
				tempi = (double) (wr * data[j + 1] + wi * data[j]);
				data[j] = data[i] - tempr;
				data[j + 1] = data[i + 1] - tempi;
				data[i] += tempr;
				data[i + 1] += tempi;
			}
			wtemp = wr;
			wr += wr * wpr - wi * wpi;
			wi += wi * wpr + wtemp * wpi;
		}
		mmax = istep;
	}

	/* Normalizing section */
	if (isign == 1) {
		n = nn << 1;
		for (i = 1; i <= n; i++) {
			data[i] = data[i] / nn;
		}
	}

	return true;
}

/*---------------------------------------------------------------------------*/
/* Purpose:  This routine replaces DATA by its two-dimensional discrete      */
/*           transform if ISIGN=1 or replaces DATA by its inverse transform  */
/*           if ISIGN=-1.  DATA is a complex array with NN columns and MM    */
/*           rows.  NN and MM must both be integer powers of 2 or the        */
/*           routine will abort and return FALSE.                            */
/*---------------------------------------------------------------------------*/
bool fft_2d(double data[], int nn, int mm, int isign) 
{
	int i, j, index1, index2;
	double *copy;

	/* Error checking section */
	i = 1;
	j = nn;
	while (j > 1) {
		i = i << 1;
		j = j >> 1;
	}
	if (nn != i) {
		return false;
	}
	i = 1;
	j = mm;
	while (j > 1) {
		i = i << 1;
		j = j >> 1;
	}
	if (mm != i) {
		return false;
	}

	/* Transform by ROWS for forward transform */
	if (isign == 1) {
		index1 = 0;
		for (i = 0; i < mm; i++) {
			fft_1d(&(data[index1]), nn, isign);
			index1 += (nn << 1);
		}
	}

	/* Allocate space for temporary array */
	copy = (double *) malloc((unsigned) (sizeof(double) * mm * 2));
	if (copy == NULL) {
		return false;
	}

	/* Transform by COLUMNS */
	for (j = 0; j < nn; j++) {
		/* Copy pixels into temp array */
		index1 = (j << 1);
		index2 = 0;
		for (i = 0; i < mm; i++) {
			copy[index2++] = data[index1];
			copy[index2++] = data[index1 + 1];
			index1 += (nn << 1);
		}

		/* Perform transform */
		fft_1d(copy, mm, isign);

		/* Copy pixels back into data array */
		index1 = (j << 1);
		index2 = 0;
		for (i = 0; i < mm; i++) {
			data[index1] = copy[index2++];
			data[index1 + 1] = copy[index2++];
			index1 += (nn << 1);
		}
	}

	/* Free temporary space */
	free((char *) copy);

	/* Transform by ROWS for inverse transform */
	if (isign == -1) {
		index1 = 0;
		for (i = 0; i < mm; i++) {
			fft_1d(&(data[index1]), nn, isign);
			index1 += (nn << 1);
		}
	}

	return true;
}
