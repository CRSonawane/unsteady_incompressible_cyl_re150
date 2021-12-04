#include "definitions.h"

void time_step()
{
    int i,j, left,right,itermax;
	
    double rss,L,nx,ny,vdotn,c,x1,x2,x3,x4,y1,y2,y3,y4;
	
	for(i=1;i<=no_cell+no_boundaryedges;i++)
		{
		    cell[i].sum1=0.0;
		    cell[i].sum2=0.0;
		    cell[i].deltat=0.0;
		    cell[i].deltatinv=0.0;
		    cell[i].deltatvis=0.0;
		}
		
		
		
		for(i=1;i<=no_edge;i++)
		{
				
			left = edge[i].adjacent_cell[0];
		
			right = edge[i].adjacent_cell[1];
		
			L = edge[i].L;
		
			nx = edge[i].nx;
			
			ny = edge[i].ny;
		
			/*Time Step calculation:*****-----------------*****------------*****----------*/		
			vdotn=((cell[left].u[1]+cell[right].u[1])/2*nx+(cell[left].u[2]+cell[right].u[2])/2*ny);
			c=sqrt(pow(vdotn,2.0)+beta);
			
			cell[left].sum1=cell[left].sum1+((fabs(vdotn)*L)+(c*fabs(L)));
			cell[right].sum1=cell[right].sum1+((fabs(vdotn)*L)+(c*fabs(L)));
			
			cell[left].sum2=cell[left].sum2+(fabs(L)*fabs(L));
			cell[right].sum2=cell[right].sum2+(fabs(L)*fabs(L));
		
			/*--------*****------------*****----------*****----------*/
		}
		
		//dt=1.0;
		
		for(i=1;i<=no_cell;i++)
		{
			cell[i].deltatinv=2.0*cfl*cell[i].area/cell[i].sum1;
			cell[i].deltatvis=2.0*cfl*cell[i].area*cell[i].area/((8.0/3.0)*viscosity*cell[i].sum2);
			
			cell[i].deltat=cell[i].deltatinv*cell[i].deltatvis/(cell[i].deltatinv+cell[i].deltatvis);
			
			if (cell[i].deltat>(2.0/3.0*rdt))
			{
				cell[i].deltat = rdt;
			}
		}	
}
