// (C) 2001 by 
// Manfred Lippert mani@mani.de
// Andre Betz andre.betz@gmx.de

#ifndef VECTOR
#define VECTOR

template <class TYPE> 
class Matrix
{
public:
	Matrix();
	Matrix(unsigned long ulX,unsigned long ulY);
	Matrix(const Matrix<TYPE>& Mat);
	~Matrix();
	Matrix<TYPE>& operator=(const Matrix<TYPE>& xObj);
	unsigned long GetDimX() const;
	unsigned long GetDimY() const;
	int SetSize(unsigned long ulX,unsigned long ulY);
	TYPE GetField(unsigned long ulX,unsigned long ulY) const;
	int SetField(unsigned long ulX,unsigned long ulY,TYPE xObj);
	void Clear();
	TYPE GetMaximum();
protected:
	TYPE* m_pxTwoDimArray;
	TYPE  m_xDummy;
	TYPE  m_xMaximum;
	void copy(const Matrix<TYPE>& xObj);
	unsigned long GetPos(unsigned long ulX,unsigned long ulY) const;
	unsigned long m_ulXDim;
	unsigned long m_ulYDim;
};

template <class TYPE> 
class Vector : Matrix<TYPE>
{
public:
	Vector();
	int SetSize(unsigned long ulX);
	TYPE GetField(unsigned long ulX);
	int SetField(unsigned long ulX,TYPE xObj);
    void Clear();
	unsigned long GetDim() const;
protected:
};

#include "MatrixTpl.h"
#endif

