#include "definitions.h"

double limiter(double antidiff,int i,int j)
{

	int cell1,cell2,cell3;
	
	double u0,u1,u2,u3,u4;
	
	double max,min,limiter;
	
		u1 = cell[cell[i].adj_cell[0]].u[j];
	
		u2 = cell[cell[i].adj_cell[1]].u[j];
	
		u3 = cell[cell[i].adj_cell[2]].u[j];

		u4 = cell[cell[i].adj_cell[3]].u[j];

		u0 = cell[i].u[j];
	
		if(antidiff >0)
		{
			if(u1>=u2)	
			{ max = u1;}
			else
			{ max = u2;}
		
			if(u3>max)
			{ max = u3;}

			if(u4>max)
			{ max = u4;}

			if(u0>max)
			{ max = u0;}
	
			limiter = (max - u0)/antidiff;
		
			if(limiter > 1)
			{ limiter = 1;
			}
		

		}
		else
		{
			if(u1<=u2)	
			{ min = u1;}
			else
			{ min = u2;}
			
			if(u3<min)
			{ min = u3;}
			
			if(u4<min)
			{ min = u4;}
	
			if(u0<min)
			{ min = u0;}
	
			limiter = (min - u0)/antidiff;
			if(limiter > 1)
			{limiter = 1;
			}
		
		}
		return limiter;
	
}	
	
	
		
			
		
	
