#include "definitions.h"

int face_vol_increment()
{		
	int i,j;
	
	int v1, v2, left, right;

	double dx, dy;	

	
	for(i=1;i<=no_edge;i++)
	{
		left = edge[i].adjacent_cell[0];		
		right = edge[i].adjacent_cell[1];


		edge[i].dv = rdt * 0.5 * ( (vertex[edge[i].node[0]].xt*dyp[i-1]) + (vertex[edge[i].node[0]].yt*dxp[i-1]) + vertex[edge[i].node[1]].xt*(dyp[i-1] - rdt*vertex[edge[i].node[0]].yt) + vertex[edge[i].node[1]].yt*(dxp[i-1] + rdt*vertex[edge[i].node[0]].xt) );


		// find the volumetric increment of cell by + left and -right 

			cell[left].dv = cell[left].dv + (edge[i].dv);
			
			cell[right].dv = cell[right].dv - (edge[i].dv);

	}


	
		
}















