#include "rcfilter.h"

RCFilter::RCFilter(Matrix<int> &Stimuli)
{
	m_Stimuli = Stimuli;
	m_deltaT = 0;
	m_synapticResistance = 0;
	m_jonctionResistance = 0;
	m_membranarResistance = 0;
	m_membranarCapacity = 0;	
}

void RCFilter::SetValues(float deltaT,float synapticResistance,float jonctionResistance,float membranarResistance,float membranarCapacity)
{
	m_deltaT = deltaT;
	m_synapticResistance = synapticResistance;
	m_jonctionResistance = jonctionResistance;
	m_membranarResistance = membranarResistance;
	m_membranarCapacity = membranarCapacity;	
}

Bitmap RCFilter::GetRC(Bitmap &bmp)
{
	int iCountX;
	int iCountY;
	int result = 0;
	Bitmap ret(bmp.GetDimX(),bmp.GetDimY());
	float alpha = m_synapticResistance / m_jonctionResistance;
	float beta  = m_synapticResistance / m_membranarResistance;
	float tau   = m_synapticResistance * m_membranarCapacity;	    

	if((1+beta+4*alpha) == 0.0f) 
	{
		for(iCountY=0;iCountY<ret.GetDimY();iCountY++)
			for(iCountX=0;iCountX<ret.GetDimX();iCountX++)
				ret.SetGreyColor(iCountX,iCountY,255);
			
		return ret;

	}
	
	for(iCountY=0;iCountY<ret.GetDimY();iCountY++)
	{
		for(iCountX=0;iCountX<ret.GetDimX();iCountX++)
		{
				/* Ränder sind 255
				result = (int)(
				   (deltaT/tau)*this.grayComponent(input[(y*this.width)+x]) + 
				   alpha*(deltaT/tau)*(
						       this.grayComponent(output[(y*this.width)+x-1]) +
						       this.grayComponent(output[(y*this.width)+x+1]) +
						       this.grayComponent(output[((y-1)*this.width)+x]) +
						       this.grayComponent(output[((y+1)*this.width)+x])) -
				   (1+beta+4*alpha)*(deltaT/tau)*this.grayComponent(output[(y*this.width)+x]) +
				   this.grayComponent(output[(y*this.width)+x])
				   );		  		
				*/
			if(result >255)	result = 255;
			if(result < 0)	result = 0;
			
			ret.SetGreyColor(iCountX,iCountY,result);
		}
	}

	return ret;
}
