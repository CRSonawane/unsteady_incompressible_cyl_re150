#include "definitions.h"

void transfer()
{		
	int i,j, v1, v2;
	double dx, dy;

		
	for(i=1;i<=vertex_max;i++)
	{
	    if(rtstep >=1)
	    {
		gridx_2[vertex[i].no-1] = gridx_1[vertex[i].no-1];
		gridy_2[vertex[i].no-1] = gridy_1[vertex[i].no-1];
	    }
	    
	    gridx_1[vertex[i].no-1] = gridx[vertex[i].no-1];
	    gridy_1[vertex[i].no-1] = gridy[vertex[i].no-1];
	}
	    


	for(i=1;i<=no_cell;i++)
	{
		if(rtstep >=1)
		{
			up2_p[i-1] = up1_p[i-1];
			up2_u[i-1] = up1_u[i-1];
			up2_v[i-1] = up1_v[i-1];
			up2_T[i-1] = up1_T[i-1];
			area2[i-1] = area1[i-1];
		}
								
		up1_p[i-1] = cell[i].u[0];
		up1_u[i-1] = cell[i].u[1];
		up1_v[i-1] = cell[i].u[2];
		up1_T[i-1] = cell[i].u[3];
		area1[i-1] = cell[i].area;	
	}

	for(i=1;i<=no_edge;i++)
	{
		/*v1 = edge[i].node[0];		
		v2 = edge[i].node[1];

		dx = gridx[v2 -1] - gridx[v1 -1];
		dy = gridy[v2 -1] - gridy[v1 -1];*/

		dxp[i-1] = edge[i].nx*edge[i].L;
		dyp[i-1] = edge[i].ny*edge[i].L;

		
		/*nxp[i-1] = edge[i].nx;

		nyp[i-1] = edge[i].ny;

		Lp[i-1] = edge[i].L;

		cxp[i-1] = edge[i].cx;

		cyp[i-1] = edge[i].cy;	*/
	}

	printf("\n transfer done \n");	
}