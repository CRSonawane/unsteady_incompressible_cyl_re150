#include "definitions_rbf.h"


double ludcmp()
{
	int i,imax,j,k, N;
	double big,dum,sum,temp,d;
	
	d=1.0;

	N = (no_boundary_node + 3);

	for (i=1;i<=N;i++) 
	{	
    		big=0.0;
    		for (j=1;j<=N;j++)
        	{
			if ((temp=fabs(A[i][j])) > big) 
				big=temp;
		}			
		if (big == 0.0) 
		{
			printf("Singular matrix in routine ludcmp");	
		}
    		vv[i]=1.0/big;	
	}
	
	for (j=1;j<=N;j++) 
	{    	
		for (i=1;i<j;i++) 
		{
        		sum=A[i][j];
        		for (k=1;k<i;k++) 
				sum -= A[i][k]*A[k][j];
        		A[i][j]=sum;
    		}
 		big=0.0;
   		for (i=j;i<=N;i++) 
		{
        		sum=A[i][j];
        		for (k=1;k<j;k++)
				sum -= A[i][k]*A[k][j];
			A[i][j]=sum;
  			if ( (dum=vv[i]*fabs(sum)) >= big) 
			{
       				big=dum;
       				imax=i;
  			}
		}
		if (j != imax) 
		{
    			for (k=1;k<=N;k++) 
			{
        			dum=A[imax][k];
        			A[imax][k]=A[j][k];
        			A[j][k]=dum;
    			}
    			d = -1.0 * d;
    			vv[imax]=vv[j];
		}
	      	indx[j]=imax;
      		if (A[j][j] == 0.0) 
			A[j][j]=TINY;
    		if (j != N) 
		{
           		dum=1.0/(A[j][j]);
           		for (i=j+1;i<=N;i++) 
				A[i][j] *= dum;
      		}
  	}
}

