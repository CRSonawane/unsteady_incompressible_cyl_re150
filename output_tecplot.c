#include "definitions.h"

void output_tecplot()
{
	int i,j, temp1;
	
	
	double areatot;
	
	    FILE *files[rtstep];    
	    char filename[30];
	    sprintf(filename, "output%d.dat",rtstep);
	    files[rtstep] = fopen(filename,"a");	
	
	    fprintf(files[rtstep],"TITLE = \" FLOW CYLINDER \" \n");
	    fprintf(files[rtstep],"VARIABLES = \"X\" \"Y\" \"Pressure\" \"U\" \"V\" \"Temperature\" \"Vorticity\" \n");
	    fprintf(files[rtstep],"ZONE N=%d, E=%d,DATAPACKING=POINT, ZONETYPE=FEQUADRILATERAL\n",no_point,no_cell);
                       
	
	// find vortivcity
	    for(i=1;i<=no_cell;i++)
	    {
              //  cell[i].vort= cell[i].derivatives[2][0]-cell[i].derivatives[1][1];
			cell[i].vort = cell[i].deriv_x[2] - cell[i].deriv_y[1];
	    }

		// find the average flow variable at a vertex		----  Boundary treatment not required 	
		for (i = 1; i <= no_point; i++)
		{
			vertex[i].un[0] = 0.0;
			vertex[i].un[1] = 0.0;
			vertex[i].un[2] = 0.0;
			vertex[i].un[3] = 0.0;
			vertex[i].vort = 0.0;

		}

		// area weighted average
		for (i = 1; i <= no_point; i++)
		{
			areatot = 0.0;
			for (j = 0; j < vertex[i].no_node_cell; j++)
			{
				vertex[i].un[0] = vertex[i].un[0] + cell[vertex[i].cell[j]].area * cell[vertex[i].cell[j]].u[0];
				vertex[i].un[1] = vertex[i].un[1] + cell[vertex[i].cell[j]].area * cell[vertex[i].cell[j]].u[1];
				vertex[i].un[2] = vertex[i].un[2] + cell[vertex[i].cell[j]].area * cell[vertex[i].cell[j]].u[2];
				vertex[i].un[3] = vertex[i].un[3] + cell[vertex[i].cell[j]].area * cell[vertex[i].cell[j]].u[3];

				vertex[i].vort = vertex[i].vort + cell[vertex[i].cell[j]].area * cell[vertex[i].cell[j]].vort;

				areatot = areatot + cell[vertex[i].cell[j]].area;
			}
			vertex[i].un[0] = vertex[i].un[0] / areatot;
			vertex[i].un[1] = vertex[i].un[1] / areatot;
			vertex[i].un[2] = vertex[i].un[2] / areatot;
			vertex[i].un[3] = vertex[i].un[3] / areatot;

			vertex[i].vort = vertex[i].vort / areatot;
		
			fprintf(files[rtstep],"%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",gridx[i-1],gridy[i-1],vertex[i].un[0],vertex[i].un[1],vertex[i].un[2], vertex[i].un[3], vertex[i].vort);
	    }
	    
	    temp1= 0;
	    for(i=1;i<=no_cell;i++)
	    {
		temp1 = (i-1)*4;
		
		fprintf(files[rtstep],"%d %d %d %d \n", elementdata_fluid[temp1], elementdata_fluid[temp1+1], elementdata_fluid[temp1+2], elementdata_fluid[temp1+3]);
	    }
		
	    fclose(files[rtstep]);
	
	
			
}













