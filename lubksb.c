#include "definitions_rbf.h"

double lubksb()
{
	int i,ii=0,ip,j, N;
	double sum;		

	N = (no_boundary_node + 3);

	for(i=1; i<=N; i++)
	{	b[i] = col[i];
		//cout<<b[i];
	}	
	for (i=1;i<=N;i++) 
	{
		ip=indx[i];
		sum=b[ip];
		b[ip]=b[i];
		if (ii)
			for (j=ii;j<=i-1;j++) 
				sum -= A[i][j]*b[j];
		else if (sum) 
			ii=i;
		b[i]=sum;
	}
	for (i=N;i>=1;i--) 
	{
		sum=b[i];
		for (j=i+1;j<=N;j++) 
			sum -= A[i][j]*b[j];
		b[i]=sum/A[i][i];
	}
	for(i=1; i<=N; i++)
	{	col[i] = b[i];
		//cout<<col[i]<<"\t";	
	}
}
