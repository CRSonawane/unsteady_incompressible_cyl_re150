#include "definitions.h"
/*
calculates the residual based on pressure u velocity and v velocity. For more details of the same read the manual.
*/
double convergence()
{
    int i,j;
    
    double error_dpdt,error_p,error_u,error_v, error_t;
	double error_actp, error_pp,error_uu,error_vv, error_tt;
    
    double error[12][no_cell];

	FILE *f30;
	f30=fopen("conv_history.dat","a");
	    
    error_p=0.0;		 error_pp=0.0;
    
    error_u=0.0;		 error_uu=0.0;
    
    error_v=0.0;		error_vv=0.0;

    error_t=0.0;		error_tt=0.0;

    error_dpdt =0.0;
    
    rss_t = 0.0;
    
    for(i=1;i<=no_cell;i++)
    {
		for(j=0;j<=6;j++)          
		{
			error[j][i]=0.0;
		}
    }
    
    for(i=1;i<=no_cell;i++)
    {  
	  //p
		error[0][i]=cell[i].u[0]- cell[i].u_temp[0];
		error_p=error_p+(error[0][i]*error[0][i]);
		
		error[1][i]=cell[i].u[0];
		error_pp=error_pp+(error[1][i]*error[1][i]);
		
	//actual dp/dt

		error[2][i]=(cell[i].u[0]- cell[i].u_temp[0])/(cell[i].deltat);
		error_dpdt=error_dpdt+(error[2][i]*error[2][i]);
		
		
	//u
		error[3][i]=cell[i].u[1]- cell[i].u_temp[1];  
		error_u=error_u+(error[3][i]*error[3][i]);
     
		error[4][i]=cell[i].u[1];  
		error_uu=error_uu+(error[4][i]*error[4][i]);
		
		
	//v		
		error[5][i]=cell[i].u[2]- cell[i].u_temp[2];
		error_v=error_v+(error[5][i]*error[5][i]);

		error[6][i]=cell[i].u[2];
		error_vv=error_vv+(error[6][i]*error[6][i]);
		
	/*//t	
		error[7][i]=cell[i].u[3]- cell[i].u_temp[3];
		error_t=error_t+(error[7][i]*error[7][i]);

		error[8][i]=cell[i].u[3];
		error_tt=error_tt+(error[8][i]*error[8][i]);
*/
		
    }

    error_p=log10(sqrt(error_p)/sqrt(error_pp));
    
    error_u=log10(sqrt(error_u)/sqrt(error_uu));
    
    error_v=log10(sqrt(error_v)/sqrt(error_vv));

    error_t=0.0;//log10(sqrt(error_t)/sqrt(error_tt));

	error_actp =error_dpdt/(no_cell);
	
//	fprintf(f30,"%d\t %1.15f\t %f \t %f \t %f \t \n",iter, error_actp, error_p, error_u, error_v);

	fprintf(f30," %d\t %1.15f\t %f \t %f \t %f \t %f \n",iter, error_actp, error_p, error_u, error_v, error_t);
	  
	fclose(f30);

	rss_t = error_actp;

	return rss_t;
  
}
    
    