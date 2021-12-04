#include "definitions.h"

void initlize_1()
{
	int i;
	
	
// initlise th value from the previous value

	for(i=1; i<=no_cell; i++)
	{
		cell[i].u[0] = up1_p[i-1];
		cell[i].u[1] = up1_u[i-1];
		cell[i].u[2] = up1_v[i-1];
		cell[i].u[3] = up1_T[i-1];
		
		
	// assign previous values to cells
		cell[i].up1[0] = up1_p[i-1];
		cell[i].up1[1] = up1_u[i-1];
		cell[i].up1[2] = up1_v[i-1];
		cell[i].up1[3] = up1_T[i-1];

		cell[i].area1 = area1[i-1];

	// assign previous to previous values to cell
		if(rtstep>=2)
		{
			cell[i].up2[0] = up2_p[i-1];
			cell[i].up2[1] = up2_u[i-1];
			cell[i].up2[2] = up2_v[i-1];
			cell[i].up2[3] = up2_T[i-1];

			cell[i].area2 = area2[i-1];
		}


	}	
}
