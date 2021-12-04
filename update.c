#include "definitions.h"

void update(double st_coeff)
{
	int i,j;
	
	for(i=1;i<=no_cell;i++)
	{
             cell[i].u[0] = cell[i].u_temp[0] -((cell[i].deltat/cell[i].area) *st_coeff * (cell[i].netflux[0] + cell[i].rtd[0] ));
             
	    cell[i].u[1] = cell[i].u_temp[1] -((cell[i].deltat/cell[i].area) *st_coeff * (cell[i].netflux[1] + cell[i].rtd[1] - (((cell[i].u[3]-T_initial)/(-1.0))*gbdt*(cell[i].u_temp[3]-0.5)*cell[i].area) ));
            
	    cell[i].u[2] = cell[i].u_temp[2] -((cell[i].deltat/cell[i].area) *st_coeff * (cell[i].netflux[2] + cell[i].rtd[2] ));
            
	    cell[i].u[3] = cell[i].u_temp[3] -((cell[i].deltat/cell[i].area) *st_coeff * (cell[i].netflux[3] + cell[i].rtd[3] ));
            
            
		
	}
}