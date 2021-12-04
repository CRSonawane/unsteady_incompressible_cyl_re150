#include "definitions.h"

void RUNGK(double st_coeff)
{		
	int i,j;
	
	boundary_conditions();
	
	derivatives();

	visc_flux();
	
	conv_flux();
	
	rtd();
	
	update(st_coeff);
	
	for(i=1;i<=no_cell + no_boundaryedges;i++)
	{
		for(j=0;j<=3;j++)
		{
			cell[i].netflux[j]=0;

			cell[i].limiter[j] = 1.0;
			
		}
	}
	
	
}
