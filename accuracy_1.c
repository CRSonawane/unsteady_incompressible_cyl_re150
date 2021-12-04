#include "definitions.h"

void accuracy_1()
{
	int i,j;

	double cp_cfd,cp_act,theta,temp,dn,pboun;
	
	FILE *f3;

	f3=fopen("bot_velo.dat","a");
	
	for(i=1;i<=no_edge;i++)
	{
		if(edge[i].bc_type == 2 || edge[i].bc_type == 3)
		{
			fprintf(f3,"%f\t %f \t %f \t %f \n",edge[i].cx, edge[i].cy, edge[i].xt, edge[i].yt);
		}
	}

	
	fclose(f3);
} 
   
