#include "definitions.h"

void boundary_conditions()
{
	int i,bound_cell,adja_cell,vdotn;
	double ytemp;
	

	for(i=1;i<=no_edge;i++)
	{	
		bound_cell = edge[i].adjacent_cell[1];
		adja_cell = edge[i].adjacent_cell[0];

		
		if(edge[i].bc_type == 1)		//inout
		{
                    cell[bound_cell].u[0] = cell[adja_cell].u[0];
                    cell[bound_cell].u[1] = u_initial;
                    cell[bound_cell].u[2] = v_initial;
                    cell[bound_cell].u[3] = T_initial;
                }
                else if(edge[i].bc_type == 2) //outlet
                {
                    cell[bound_cell].u[0] = p_initial;
                    cell[bound_cell].u[1] = cell[adja_cell].u[1];
                    cell[bound_cell].u[2] = cell[adja_cell].u[2];
                    cell[bound_cell].u[3] = cell[adja_cell].u[3];
                }
		
		else if(edge[i].bc_type == 3 || edge[i].bc_type == 4 || edge[i].bc_type == 5 || edge[i].bc_type == 6)//cylinder wall
		{
                    cell[bound_cell].u[0] = cell[adja_cell].u[0];
			
                    cell[bound_cell].u[2] = -cell[adja_cell].u[2];
				
                    if(rtstep == 0)
                    {	
			  cell[bound_cell].u[1] =  -cell[adja_cell].u[1];	
                    }
                    else
                    {	
                        cell[bound_cell].u[1] = edge[i].yt;
                    }
			
                    cell[bound_cell].u[3] = Twall;
                    
		}	
		else if(edge[i].bc_type == 7 || edge[i].bc_type == 8) //topside and bottomside
		{
			cell[bound_cell].u[0] = cell[adja_cell].u[0];
			cell[bound_cell].u[1] = cell[adja_cell].u[1];
			cell[bound_cell].u[2] = -cell[adja_cell].u[2];
                        cell[bound_cell].u[3] = cell[adja_cell].u[3];

		}	
		
	}
}
