#include "ringpuffer.h"

CRingPuffer::CRingPuffer(int iAnz)
{
	m_iAnz = iAnz;
	m_iPosIn = 0;
	m_iPosOut = 0;
	m_iVal = 0;
	Puffer = new Bitmap[m_iAnz];
}

void CRingPuffer::PutBitmap(Bitmap& bmp)
{
	Puffer[m_iPosIn] = bmp;
	m_iPosIn++;
	m_iPosIn %= m_iAnz;
	m_iVal++;
}

Bitmap CRingPuffer::GetBitmap()
{
	int iPosTmp = m_iPosOut;
	m_iPosOut++;
	m_iPosOut %= m_iAnz;
	m_iVal--;
	return Puffer[iPosTmp];
}

int CRingPuffer::GetLevel()
{
	return m_iVal;
}

int CRingPuffer::IsFull()
{
	if(m_iVal == m_iAnz)	return 1;
	else					return 0;
}


CHistogram::CHistogram()
{
	First  = NULL;
	Last   = NULL;
	Actuel = NULL;
	iAnz = 0;
	iPos = 0;
}

CHistogram::~CHistogram()
{
	Clear();
}

void CHistogram::Clear()
{
	Actuel = First;
	while(Actuel)
	{
		First = Actuel->next;
		if(Actuel!=NULL) delete Actuel;
		Actuel = First;
	}
	iAnz = 0;
	iPos = 0;
	First = NULL;
}

void CHistogram::Reset()
{
	Actuel = First;
	iPos = 0;
}

void CHistogram::Input(Bitmap &bmp1)
{
	pbldbuf temp;
	temp = new bldbuf;
	temp->next = NULL;
	temp->bmp = bmp1;
	
	if(First==NULL)
	{
		First  = temp;
		Actuel = First;
		Last   = First;
	}
	else
	{
		Last->next = temp;
		Last = Last->next;
	}
	iAnz++;
}

int CHistogram::GetNext(Bitmap &bmp1)
{
	if(Actuel!=NULL)
	{
		bmp1 = Actuel->bmp;
		Actuel = Actuel->next;
		iPos++;
		return 1;
	}
	return 0;
}

int CHistogram::GetAnz()
{
	return iAnz;
}

int CHistogram::GetPos()
{
	return iPos;
}
