#include "definitions.h"

void output()
{	

double *p,*u,*v,*T,*vort;
int i;
char iflow[33];
sprintf(iflow,"FlowSolution %d",rtstep);

p = malloc(no_cell * sizeof(double));
u = malloc(no_cell * sizeof(double));
v = malloc(no_cell * sizeof(double));
T = malloc(no_cell * sizeof(double));
vort = malloc(no_cell * sizeof(double));



	for(i=1;i<=no_cell;i++)
        {
                p[i-1] = cell[i].u[0];
                u[i-1] = cell[i].u[1];
                v[i-1] = cell[i].u[2];
		T[i-1] = cell[i].u[3];
              //  vort[i-1]= cell[i].derivatives[2][0]-cell[i].derivatives[1][1];

        }

	int rtmstp = rtstep;
	
    int index_file,index_base,index_zone,index_flow,index_field,iset;
   
	 if(rtmstp==0)
	 {	cg_open("grid_0.cgns",CG_MODE_MODIFY,&index_file);	}
	
	
	
	
	

        cg_sol_write(index_file,1,1,iflow,CellCenter,&index_flow);

        cg_field_write(index_file,1,1,index_flow,RealDouble,"Pressure",p,&index_field);

        cg_field_write(index_file,1,1,index_flow,RealDouble,"U Velocity",u,&index_field);

        cg_field_write(index_file,1,1,index_flow,RealDouble,"V Velocity",v,&index_field);
	
	cg_field_write(index_file,1,1,index_flow,RealDouble,"Temperature",T,&index_field);

        cg_field_write(index_file,1,1,index_flow,RealDouble,"Vorticity",vort,&index_field);



        cg_close(index_file);

	free(p); free(u); free(v); free(T);free(vort);
/*
	int wall_cell,temp1;
	
	int *node_count;
	
	double *v_cell,*u_cell,*p_cell;
	
	double temp;
	
	FILE *output;
		
	output = fopen("output.vtk","w");
	
	u_cell = (double *)malloc(no_point * sizeof(double));
	
	p_cell = (double *)malloc(no_point * sizeof(double));

	v_cell = (double *)malloc(no_point * sizeof(double));
	
	node_count = (int *)malloc(no_point * sizeof(int));
	
	fprintf(output,"# vtk DataFile Version 2.0\n");
	
	fprintf(output,"Inviscid Circular cylinder \n");
	
	fprintf(output,"ASCII\n");
	
	fprintf(output,"DATASET UNSTRUCTURED_GRID\n");
	
	fprintf(output,"POINTS %d float\n",no_point);
	
	
	for(i=0;i<=no_point;i++)
	{
		u_cell[i] =0;
		v_cell[i] =0;
		p_cell[i]=0;
		node_count[i]=0;
	}
	
		
	for(i=1;i<=no_cell;i++)
	{
		temp1 = (i-1)*4;
		
		p_cell[elementdata_fluid[temp1]-1]+= cell[i].u[0];
		
		u_cell[elementdata_fluid[temp1] - 1]+= cell[i].u[1];

		v_cell[elementdata_fluid[temp1] - 1]+= cell[i].u[2];

		node_count[elementdata_fluid[temp1] - 1]++;
		
		
		p_cell[elementdata_fluid[temp1+1]-1]+= cell[i].u[0];
		
		u_cell[elementdata_fluid[temp1+1] - 1]+= cell[i].u[1];

		v_cell[elementdata_fluid[temp1+1] - 1]+= cell[i].u[2];

		node_count[elementdata_fluid[temp1+1] - 1]++;
		
	
		
		p_cell[elementdata_fluid[temp1+2]-1]+= cell[i].u[0];
		
		u_cell[elementdata_fluid[temp1+2] - 1]+= cell[i].u[1];

		v_cell[elementdata_fluid[temp1+2] - 1]+= cell[i].u[2];

		node_count[elementdata_fluid[temp1+2] - 1]++;

	
		p_cell[elementdata_fluid[temp1+3]-1]+= cell[i].u[0];
		
		u_cell[elementdata_fluid[temp1+3] - 1]+= cell[i].u[1];

		v_cell[elementdata_fluid[temp1+3] - 1]+= cell[i].u[2];

		node_count[elementdata_fluid[temp1+3] - 1]++;
	}
	
	for(i=1;i<=no_point;i++)
	{
// 		fprintf(output,"%lf\t%lf\t%lf\n",gridx[i-1],gridy[i-1],p_cell[i-1]/node_count[i-1]);
		fprintf(output,"%lf\t%lf\t0.0\n",gridx[i-1],gridy[i-1]);

	}
	
	fprintf(output,"CELLS %d %d\n",no_cell,5*no_cell);
	
	for(i=1;i<=no_cell;i++)
	{
		temp1 = (i-1)*4;
		fprintf(output,"4 %d %d %d %d \n",elementdata_fluid[temp1]-1,elementdata_fluid[temp1+1]-1,elementdata_fluid[temp1+2]-1,elementdata_fluid[temp1+3]-1);
	}
	fprintf(output,"CELL_TYPES %d\n",no_cell);

	for(i=1;i<=no_cell;i++)
	{
		fprintf(output,"9\n");
	}
	
 	fprintf(output,"POINT_DATA %d\n",no_point);
	fprintf(output,"SCALARS pressure float \n");
	fprintf(output,"LOOKUP_TABLE default\n");
	

	for(i=1;i<=no_point;i++)
	{
		
		fprintf(output,"%lf\n",p_cell[i-1]/node_count[i-1]);
	}
 	fprintf(output,"SCALARS uvelocity float \n");
	fprintf(output,"LOOKUP_TABLE default\n");
	for(i=1;i<=no_point;i++)
	{
		fprintf(output,"%lf\n",u_cell[i-1]/node_count[i-1]);
// 		fprintf(output,"%lf\n",cell[i].u[0]);
	}
	fprintf(output,"SCALARS vvelocity float \n");
	fprintf(output,"LOOKUP_TABLE default\n");
	for(i=1;i<=no_point;i++)
	{
		fprintf(output,"%lf\n",v_cell[i-1]/node_count[i-1]);
// 		fprintf(output,"%lf\n",cell[i].u[0]);
	}
	/*for(i=1;i<=no_cell;i++)
	{
		temp1 = (i-1)*3;
		fprintf(output,"%d\t%d\t%d\n",elementdata_fluid[temp1],elementdata_fluid[temp1+1],elementdata_fluid[temp1+2]);
	}*/
	
	


	
	

}

	