#include "definitions.h"


void readcgnsdata_1()
{
      int i,j,temp,cell1,cell2, cell3, cell4; 
      
      int v1,v2,n1,n2,n3,left,right;
      
      double dx,dy,L,nx,ny,temp1, dx1, dx2, dx3, dx4, dy1, dy2, dy3, dy4;
      
      double x1,x2,y1,y2,x3,y3,x4,y4;
  
  // clear old grid
	for(i=1; i<=vertex_max; i++)
	{
		gridx[vertex[i].no - 1] = 0.0;
		gridy[vertex[i].no - 1] = 0.0;
	}
  
	

// use new x y coordinates for the grid	
	for(i=1; i<=vertex_max; i++)
	{
		gridx[vertex[i].no - 1] = gridx_new[vertex[i].no -1];
		
		gridy[vertex[i].no - 1] = gridy_new[vertex[i].no -1]; 
	}
	
/*	FILE *f2;	
	f2=fopen("xy.dat","w");
	
	for(i=1;i<=vertex_max;i++)
	{
	  fprintf(f2,"%f\t%f\n",*(gridx+i),*(gridy+i));
	}
*/	
	/*-------------------------------------------------*/
	/*-------------------------------------------------*/
	/*-------------------------------------------------*/
	/*-------------------------------------------------*/
	/*-------------------------------------------------*/
	// Old datastructure is still same  -- only change in x and y cordinates and related parameters
	
	/*Initilse valules for cells and edges*/
	
	for(i=1;i<=no_cell + no_boundaryedges ;i++)
	{
		for(j=0;j<=3;j++)
		{
			cell[i].netflux[j] = 0;

		}		
	}
	
	
	temp=0;
	for(i=1;i<=no_cell;i++)
	{
	 /*Find Area*/
		x1 = gridx[elementdata_fluid[temp] - 1];
		x2 = gridx[elementdata_fluid[temp +1] - 1]; 
		x3 = gridx[elementdata_fluid[temp +2] - 1]; 
		x4 = gridx[elementdata_fluid[temp +3] - 1]; 
		
		
		y1 = gridy[elementdata_fluid[temp] - 1];
		y2 = gridy[elementdata_fluid[temp +1] - 1]; 
		y3 = gridy[elementdata_fluid[temp +2] - 1]; 
		y4 = gridy[elementdata_fluid[temp +3] - 1]; 
		
	// find area by applying GCL
		//cell[i].area = 0.5 * fabs(((x2-x4)*(y3-y1))-((x3-x1)*(y2-y4)));
			
		/*End Find Area*/
	//printf("%d\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n",i,x1,x2,x3,x4,y1,y2,y3,y4);
		
				
		/*Find Centroid*/
		cell[i].xc = (x1 + x2 + x3 +x4)/4.0;
		
		cell[i].yc = (y1 + y2 + y3 +y4)/4.0;
		
		temp=temp+4;
		/*End Find Centroid*/
		
	}
	
	
// find new cordinates for boundary ghost cells 
		
	for(i=1;i<=no_edge;i++)
	{
		if(edge[i].bc_type != 0)
		{
			cell[edge[i].adjacent_cell[1]].xc = (gridx[edge[i].node[0] - 1] + gridx[edge[i].node[1] - 1]) - cell[edge[i].adjacent_cell[0]].xc;
			
			cell[edge[i].adjacent_cell[1]].yc = (gridy[edge[i].node[0] - 1] + gridy[edge[i].node[1] - 1]) - cell[edge[i].adjacent_cell[0]].yc;
		}
			
	}
	
	
//find normal		
	for(i=1;i<=no_edge;i++)
	{
				
		left = edge[i].adjacent_cell[0];
		
		right = edge[i].adjacent_cell[1];
		
		
		/*Calculate the edge normal*/
		
		v1 = edge[i].node[0];
		
		v2 = edge[i].node[1];
		
		x1 = gridx[v1 - 1];
		
		y1 = gridy[v1 - 1];
		
		x2 = gridx[v2 - 1];
		
		y2 = gridy[v2 - 1];
		
		dx = x2 - x1;
		
		dy = y2 - y1;
		
		L = sqrt(dx * dx + dy * dy);
		
		edge[i].nx = dy/L;
		
		edge[i].ny = -dx/L;
		
		temp1 = (cell[left].xc - x1) * edge[i].nx + (cell[left].yc - y1) * edge[i].ny;
		
		if(temp1>0)
		{
			edge[i].nx = -edge[i].nx;
			
			edge[i].ny = -edge[i].ny;
			
		}
		
		/*--------*****------------*****----------*****----------*/
		
		
		edge[i].cx = (x1 + x2)/2;
		
		edge[i].cy = (y1 + y2)/2;
		
		edge[i].L = L;
		
	}
	
	
// find center to centre distance
	for(i=1;i<=no_edge;i++)
	{
		cell1 = edge[i].adjacent_cell[0];
		
		cell2 = edge[i].adjacent_cell[1];
		
		dx1 = cell[cell1].xc - cell[cell2].xc;

		dy1 =  cell[cell1].yc - cell[cell2].yc;

		edge[i].delta_s = sqrt((dx1*dx1) + (dy1*dy1));
	}

  printf("\n readcgnsdata-1 done \n");
}