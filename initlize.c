#include "definitions.h"

void initlize()
{
	int i;
	
	// only for trial --for restarting from previous solution

/*	double *p,*u,*v,*T;

	char izone[33];

	p = malloc(no_cell * sizeof(double));
	u = malloc(no_cell * sizeof(double));
	v = malloc(no_cell * sizeof(double));
	T = malloc(no_cell * sizeof(double));
	
      int index_file, index_zone, index_flow,index_field,iset, range_min, range_max;
	
	index_zone = 1;
   
  	cg_open("grid_0.cgns",MODE_READ,&index_file);

	index_flow = 1;

	// cg_sol_info(index_file, 1, index_zone, index_flow,"FlowSolution",CellCenter);

	range_min = 1;
	range_max = no_cell;

	cg_field_read(index_file,1,index_zone,index_flow,"Pressure",RealDouble, &range_min, &range_max, p);

	cg_field_read(index_file,1,index_zone,index_flow,"U Velocity",RealDouble, &range_min, &range_max, u);

	cg_field_read(index_file,1,index_zone,index_flow,"V Velocity",RealDouble, &range_min, &range_max, v);
	
	cg_field_read(index_file,1,index_zone,index_flow,"Temperature",RealDouble, &range_min, &range_max, T);
	
	
	for(i=1;i<=no_cell;i++)
	{
		cell[i].u[0] = p[i-1];
		cell[i].u[1] = u[i-1];
		cell[i].u[2] = v[i-1];
		cell[i].u[3] = T[i-1];
		
	}

	cg_close(index_file);


free(p); 
free(u);	
free(v);
free(T);

	*/
	for(i=1;i<=no_cell;i++)
	{
		cell[i].u[0] = p_initial;	
		cell[i].u[1] = u_initial;	
		cell[i].u[2] = v_initial;
		cell[i].u[3] = T_initial/2.0;
		
		

		cell[i].up1[0] = p_initial;	
		cell[i].up1[1] = u_initial;	
		cell[i].up1[2] = v_initial;
		cell[i].up1[3] = T_initial/2.0;
		
		cell[i].up2[0] = p_initial;	
		cell[i].up2[1] = u_initial;	
		cell[i].up2[2] = v_initial;
		cell[i].up2[3] = T_initial/2.0;
			
		
			
	}
	
}
