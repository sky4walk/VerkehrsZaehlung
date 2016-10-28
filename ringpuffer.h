// (C) 2001 by 
// Andre Betz andre.betz@gmx.de

#include "bitmap.h"

#ifndef RINGPUFFER
#define RINGPUFFER

class CRingPuffer
{
public:
	CRingPuffer(int iAnz);
	void PutBitmap(Bitmap& bmp);
	Bitmap GetBitmap();
	int GetLevel();
	int IsFull();
protected:
	int m_iAnz;
	int m_iPosIn;
	int m_iPosOut;
	int m_iVal;
	Bitmap* Puffer;
};

typedef struct bldbuf_tp
{
	Bitmap bmp;
	struct bldbuf_tp *next;
}bldbuf,*pbldbuf;

class CHistogram
{
public:
	CHistogram();
	~CHistogram();
	void Clear();
	void Reset();
	void Input(Bitmap& bmp1);
	int GetNext(Bitmap& bmp1);
	int GetAnz();
	int GetPos();
protected:
	pbldbuf First;
	pbldbuf Actuel;
	pbldbuf Last;
	int iAnz;
	int iPos;
};

#endif