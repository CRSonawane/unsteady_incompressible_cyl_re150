#include "definitions.h"

void visc_flux()
{
	int i,j;
	
	double uu1, uu2, uu3, uu4, vv1, vv2, vv3, vcv3, vv4, tt1, tt2, tt3, tt4, dx1, dx2, dx3, dx4, dy1, dy2, dy3, dy4, dy13, dy24, dx13, dx24, areatemp;

	double ux,uy,vx,vy, tx,ty, areatot;
	
// find the average flow variable at a vertex		----  Boundary treatment not required 	

	for (i = 1; i <= no_point; i++)
	{
		vertex[i].un[0] = 0.0;
		vertex[i].un[1] = 0.0;
		vertex[i].un[2] = 0.0;
		vertex[i].un[3] = 0.0;

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

			areatot = areatot + cell[vertex[i].cell[j]].area;
		}
		vertex[i].un[0] = vertex[i].un[0] / areatot;
		vertex[i].un[1] = vertex[i].un[1] / areatot;
		vertex[i].un[2] = vertex[i].un[2] / areatot;
		vertex[i].un[3] = vertex[i].un[3] / areatot;
	}

//Viscous flux computation
	for(i=1;i<=no_edge;i++)
	{
	  /*  if(edge[i].bc_type == 2 || edge[i].bc_type == 3)//|| edge[i].bc_type == 4)	//wall
	    {
		uu1= 0.5*(0.0 + cell[edge[i].adjacent_cell[1]].u[1]);
		uu2= 0.5*(cell[edge[i].adjacent_cell[1]].u[1] + 0.0);
		uu3= 0.5*(0.0 + cell[edge[i].adjacent_cell[0]].u[1]);
		uu4= 0.5*(cell[edge[i].adjacent_cell[0]].u[1] + 0.0);						

		vv1= 0.5*(0.0 + cell[edge[i].adjacent_cell[1]].u[2]);
		vv2= 0.5*(cell[edge[i].adjacent_cell[1]].u[2] + 0.0);
		vv3= 0.5*(0.0 + cell[edge[i].adjacent_cell[0]].u[2]);
		vv4= 0.5*(cell[edge[i].adjacent_cell[0]].u[2] + 0.0);	

			
	    }
	    else
	    {*/
		uu1= 0.5*(vertex[edge[i].node[0]].un[1] + cell[edge[i].adjacent_cell[1]].u[1]);
		uu2= 0.5*(cell[edge[i].adjacent_cell[1]].u[1] + vertex[edge[i].node[1]].un[1]);
		uu3= 0.5*(vertex[edge[i].node[1]].un[1] + cell[edge[i].adjacent_cell[0]].u[1]);
		uu4= 0.5*(cell[edge[i].adjacent_cell[0]].u[1] + vertex[edge[i].node[0]].un[1]);						

		vv1= 0.5*(vertex[edge[i].node[0]].un[2] + cell[edge[i].adjacent_cell[1]].u[2]);
		vv2= 0.5*(cell[edge[i].adjacent_cell[1]].u[2] + vertex[edge[i].node[1]].un[2]);
		vv3= 0.5*(vertex[edge[i].node[1]].un[2] + cell[edge[i].adjacent_cell[0]].u[2]);
		vv4= 0.5*(cell[edge[i].adjacent_cell[0]].u[2] + vertex[edge[i].node[0]].un[2]);
		
		tt1= 0.5*(vertex[edge[i].node[0]].un[3] + cell[edge[i].adjacent_cell[1]].u[3]);
		tt2= 0.5*(cell[edge[i].adjacent_cell[1]].u[3] + vertex[edge[i].node[1]].un[3]);
		tt3= 0.5*(vertex[edge[i].node[1]].un[3] + cell[edge[i].adjacent_cell[0]].u[3]);
		tt4= 0.5*(cell[edge[i].adjacent_cell[0]].u[3] + vertex[edge[i].node[0]].un[3]);

		
	   // }

	    dy1= cell[edge[i].adjacent_cell[1]].yc-gridy[edge[i].node[0]-1];
	    dy2= gridy[edge[i].node[1]-1]-cell[edge[i].adjacent_cell[1]].yc;
	    dy3= cell[edge[i].adjacent_cell[0]].yc-gridy[edge[i].node[1]-1];
	    dy4= gridy[edge[i].node[0]-1]-cell[edge[i].adjacent_cell[0]].yc;


	    dx1= cell[edge[i].adjacent_cell[1]].xc-gridx[edge[i].node[0]-1];
	    dx2= gridx[edge[i].node[1]-1]-cell[edge[i].adjacent_cell[1]].xc;
	    dx3= cell[edge[i].adjacent_cell[0]].xc-gridx[edge[i].node[1]-1];
	    dx4= gridx[edge[i].node[0]-1]-cell[edge[i].adjacent_cell[0]].xc;

	    dy24=cell[edge[i].adjacent_cell[0]].yc-cell[edge[i].adjacent_cell[1]].yc;
	    dx24=cell[edge[i].adjacent_cell[0]].xc-cell[edge[i].adjacent_cell[1]].xc;

	    dy13=gridy[edge[i].node[1]-1]-gridy[edge[i].node[0]-1];
	    dx13=gridx[edge[i].node[1]-1]-gridx[edge[i].node[0]-1];

	    areatemp=0.5 * fabs((dx24*dy13)-(dx13*dy24));

	    
	    ux=(uu1*dy1+uu2*dy2+uu3*dy3+uu4*dy4)/areatemp;
	    uy=-(uu1*dx1+uu2*dx2+uu3*dx3+uu4*dx4)/areatemp;
	    vx=(vv1*dy1+vv2*dy2+vv3*dy3+vv4*dy4)/areatemp;
	    vy=-(vv1*dx1+vv2*dx2+vv3*dx3+vv4*dx4)/areatemp;
	    tx=(tt1*dy1+tt2*dy2+tt3*dy3+tt4*dy4)/areatemp;
	    ty=-(tt1*dx1+tt2*dx2+tt3*dx3+tt4*dx4)/areatemp;
	   
	       
	

	    edge[i].visflux[0]=0.0;
	    edge[i].visflux[1]=viscosity*((2.0*ux-2.0/3.0*(ux+vy))*edge[i].nx+(uy+vx)*edge[i].ny);
	    edge[i].visflux[2]=viscosity*((uy+vx)*edge[i].nx+(2.0*vy-2.0/3.0*(ux+vy))*edge[i].ny);
	    edge[i].visflux[3]=(viscosity/Pr)*(tx*edge[i].nx+ty*edge[i].ny);
	   

		
	}
	



}
		
		
		
		
		

