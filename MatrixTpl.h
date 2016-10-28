// (C) 2001 by Manfred Lippert und Andre Betz
// steht unter der Gnu Public Licence (GPL)

template <class TYPE> Matrix<TYPE>::Matrix()
{
	m_ulXDim = 0;
	m_ulYDim = 0;
//	m_xMaximum = 0;
	m_pxTwoDimArray = (TYPE*)0;
}

template <class TYPE> Matrix<TYPE>::Matrix(unsigned long ulX,unsigned long ulY)
{
	m_pxTwoDimArray = (TYPE*)0;
//	m_xMaximum = 0;
	SetSize(ulX,ulY);
}

template <class TYPE> Matrix<TYPE>::Matrix(const Matrix<TYPE>& Mat)
{
	m_pxTwoDimArray = (TYPE*)0;
	copy(Mat);
}

template <class TYPE> Matrix<TYPE>::~Matrix()
{
	delete m_pxTwoDimArray;
}

template <class TYPE> Matrix<TYPE>& Matrix<TYPE>::operator=(const Matrix<TYPE>& xObj)
{
	m_pxTwoDimArray = (TYPE*)0;
	if(&xObj==this) return *this;
	copy(xObj);
	return *this;
}

template <class TYPE> int Matrix<TYPE>::SetSize(unsigned long ulX,unsigned long ulY)
{
	m_ulXDim = ulX;
	m_ulYDim = ulY;
	if(m_pxTwoDimArray != (TYPE*)0) delete m_pxTwoDimArray;
    m_pxTwoDimArray = new TYPE[m_ulXDim*m_ulYDim];
	if(m_pxTwoDimArray != (TYPE*)0) return 1;
	return 0;
}

template <class TYPE> void Matrix<TYPE>::copy(const Matrix<TYPE>& Mat)
{
	TYPE xTemp = 0;
	m_xMaximum = 0;
	SetSize(Mat.GetDimX(),Mat.GetDimY());
    for(unsigned long ulYCount=0;ulYCount<GetDimY();ulYCount++)
	{
	    for(unsigned long ulXCount=0;ulXCount<GetDimX();ulXCount++)
		{
			xTemp = Mat.GetField(ulXCount,ulYCount);
			if(m_xMaximum<xTemp) m_xMaximum = xTemp;
			SetField(ulXCount,ulYCount,xTemp);
		}
	}
}

template <class TYPE> TYPE Matrix<TYPE>::GetField(unsigned long ulX,unsigned long ulY) const
{
 	unsigned long ulPos = GetPos(ulX,ulY);
	if(ulX < m_ulXDim && ulY < m_ulYDim)
		return m_pxTwoDimArray[ulPos];
	return m_xDummy;
}

template <class TYPE> int Matrix<TYPE>::SetField(unsigned long ulX,unsigned long ulY,TYPE xObj)
{
 	unsigned long ulPos; 
	if(ulX < m_ulXDim && ulY < m_ulYDim)
	{
		ulPos = GetPos(ulX,ulY);
//		if(m_xMaximum<xObj) m_xMaximum = xObj;
		m_pxTwoDimArray[ulPos] = xObj;
		return 1;
	}
	return 0;
}

template <class TYPE> unsigned long Matrix<TYPE>::GetPos(unsigned long ulX,unsigned long ulY) const
{
	return ulY*m_ulXDim+ulX;
}

template <class TYPE> unsigned long Matrix<TYPE>::GetDimX() const
{
	return m_ulXDim;
}

template <class TYPE> unsigned long Matrix<TYPE>::GetDimY() const
{
	return m_ulYDim;
}

template <class TYPE> void Matrix<TYPE>::Clear()
{
	TYPE xSet = 0;

	for(unsigned long ulCountY=0;ulCountY<m_ulYDim*m_ulXDim;ulCountY++)
	{
		m_pxTwoDimArray[ulCountY] = xSet;
	}

}

template <class TYPE> TYPE Matrix<TYPE>::GetMaximum()
{
	return m_xMaximum;
}

template <class TYPE> Vector<TYPE>::Vector() : Matrix<TYPE>()
{

}

template <class TYPE> int Vector<TYPE>::SetSize(unsigned long ulX)
{
	return Matrix<TYPE>::SetSize(ulX,1);
}

template <class TYPE> int Vector<TYPE>::SetField(unsigned long ulX,TYPE xObj)
{
	return Matrix<TYPE>::SetField(ulX,0,xObj);
}

template <class TYPE> TYPE Vector<TYPE>::GetField(unsigned long ulX)
{
	return Matrix<TYPE>::GetField(ulX,0);
}

template <class TYPE> void Vector<TYPE>::Clear()
{
	Matrix<TYPE>::Clear();
}

template <class TYPE> unsigned long Vector<TYPE>::GetDim() const
{
	return Matrix<TYPE>::GetDimX();
}