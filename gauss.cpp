// (C) 2001 by 
// Andre Betz andre.betz@gmx.de

#include "gauss.h"

GaussFilter::GaussFilter(int width) {
	this->width = 0;
	matrix = 0;
	set_width(width);
}

GaussFilter::~GaussFilter() {
	if (matrix) {
		delete matrix;
		matrix = 0;
	}
}

static int pascal_dreieck(int zeile, int x) {
	if (x > zeile) {
		return 0;
	}
	if (x == 0) {
		return 1;
	}
	return pascal_dreieck(zeile - 1, x - 1) + pascal_dreieck(zeile - 1, x);
}

void GaussFilter::set_width(int width) {
	width |= 1;	// nur ungerade Werte
	if (matrix) {
		delete matrix;
	}
	this->width = 0;
	matrix = new long[width*width];
	//(long *)malloc(width * (long)width * sizeof(long));
	if (matrix) {
		this->width = width;
		int x, y;
		for(x = 0; x < width; x++) {
			matrix[x] = pascal_dreieck(width - 1, x);
		}
		sum = 0;
		for(y = 0; y < width; y++) {
			for(x = 0; x < width; x++) {
				sum += (matrix[y * width + x] = matrix[x] * matrix[y]);
			}
		}
	}
}

void GaussFilter::filter(Bitmap& Src, Bitmap& Dst) {
	int x, y, mx, my, sx, sy;
	int half = width >> 1;
	long val;
	Dst.NeuesBild(Src.GetDimX(), Src.GetDimY());
	for(y = 0; y < Src.GetDimY(); y++) {
		for(x = 0; x < Src.GetDimX(); x++) {
			val = 0;
			for(my = 0; my < width; my++) {
				for(mx = 0; mx < width; mx++) {
					sx = x + mx - half;
					if (sx < 0) {
						sx = 0;
					}
					if (sx >= Src.GetDimX()) {
						sx = Src.GetDimX() - 1;
					}
					sy = y + my - half;
					if (sy < 0) {
						sy = 0;
					}
					if (sy >= Src.GetDimY()) {
						sy = Src.GetDimY() - 1;
					}
					val += Src.GetGreyColor(sx, sy) * matrix[my * width + mx];
				}
			}
			val = (val + (sum >> 1)) / sum;
			if (val < 0) {
				val = 0;
			}
			if (val > 255) {
				val = 255;
			}
			Dst.SetGreyColor(x, y, (unsigned char)val);
		}
	}
}
