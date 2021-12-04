#include "definitions.h"

void rtd()
{		
      int i,j;
      
      
      
      if (rtstep==0)
      {
	      for(i=1;i<=no_cell;i++)
	      {
		   cell[i].rtd[0]=0.0;
		   cell[i].rtd[1]=0.0;
		   cell[i].rtd[2]=0.0;
		   cell[i].rtd[3]=0.0;
	      }
      }
      else if(rtstep==1)
	{
	      for(i=1;i<=no_cell;i++)
	      {	
		    cell[i].rtd[0]=0.0;
		  
		    cell[i].rtd[1]=(cell[i].u[1]*cell[i].area - cell[i].up1[1]*cell[i].area1)/rdt;
		    
		    cell[i].rtd[2]=(cell[i].u[2]*cell[i].area - cell[i].up1[2]*cell[i].area1)/rdt;
		    
		    cell[i].rtd[3]=(cell[i].u[3]*cell[i].area - cell[i].up1[3]*cell[i].area1)/rdt;
		}
	}
	else if(rtstep>=2)
	{
		for(i=1;i<=no_cell;i++)
		{
		    cell[i].rtd[0]=0.0;
		    cell[i].rtd[1]=(3.0*cell[i].u[1]*cell[i].area - 4.0*cell[i].up1[1]*cell[i].area1 + cell[i].up2[1]*cell[i].area2)/ (2.0*rdt);
		    cell[i].rtd[2]=(3.0*cell[i].u[2]*cell[i].area - 4.0*cell[i].up1[2]*cell[i].area1 + cell[i].up2[2]*cell[i].area2)/ (2.0*rdt);
		    cell[i].rtd[3]=(3.0*cell[i].u[3]*cell[i].area - 4.0*cell[i].up1[3]*cell[i].area1 + cell[i].up2[3]*cell[i].area2)/ (2.0*rdt);
		}
	}


}
