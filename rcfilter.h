#include "Bitmap.h"
#include "Matrix.h"

#ifndef RCFILTER
#define RCFILTER

class RCFilter
{
public:
	RCFilter(Matrix<int> &Stimuli);
	void SetValues(float deltaT,float synapticResistance,float jonctionResistance,float membranarResistance,float membranarCapacity);
	Bitmap GetRC(Bitmap &bmp);
protected:
	Matrix<int> m_Stimuli;
	float m_deltaT;
	float m_synapticResistance;
	float m_jonctionResistance;
	float m_membranarResistance;
	float m_membranarCapacity;
};

#endif
