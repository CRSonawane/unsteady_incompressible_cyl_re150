#include "definitions_rbf.h"

void rbf_trans()
{	
	int i,j, iter, k,kk,kkk;
	

	double phi,dx,dy;
	
	


/*--------------------find the boundary nodes--------------------*/

	kk = 0;
	no_boundary_node = 0;
	for(i=1;i<=node_max;i++)
	{
		if((node[i].bc_type ==1) || (node[i].bc_type ==2) || (node[i].bc_type ==3)|| (node[i].bc_type ==4)|| (node[i].bc_type ==5)|| (node[i].bc_type ==6)|| (node[i].bc_type ==7)|| (node[i].bc_type ==8))
		{
			kk = kk + 1;
			no_boundary_node++;

			boundary_node[kk] = node[node[i].no].no;
			
			//printf("%d \t boundary_node[%d] = \t %d \n ",i, kk,boundary_node[kk]);

		}
	}
	printf("no of boundary node=%d \n", no_boundary_node);	

/*-----------------initialise  ---------------------*/

	for(i=1; i<=(no_boundary_node + 3); i++)
	{
		for(j=1; j<=(no_boundary_node +3) ; j++)
		{	
			R[i][j] = 0.0;
		}
		
		dx1[i] = 0.0;
		dy1[i] = 0.0;
	}
	
	//printf("initialization done\n");
/*---------------------------------------------------------------------------------------*/
	// move the outer nodes of the mesh in x, y direction
	for(i=1; i<=no_boundary_node; i++)
	{
		/*----------------------------- translate ------------------------*/

		if((node[boundary_node[i]].bc_type ==3) || (node[boundary_node[i]].bc_type ==4) || (node[boundary_node[i]].bc_type ==5)|| (node[boundary_node[i]].bc_type ==6))
		{

			gridx_new[node[boundary_node[i]].no-1] = gridx[node[boundary_node[i]].no -1];

			gridy_new[node[boundary_node[i]].no-1] = gridy[node[boundary_node[i]].no -1] + cyl_movement;

		//printf("%f \t %f \n", gridx_new[node[boundary_node[i]].no-1], gridy_new[node[boundary_node[i]].no-1]);

		/* ----------------- find displacement -----------------------*/

			node[i].dx = gridx_new[node[boundary_node[i]].no-1] - gridx[node[boundary_node[i]].no -1];
	
			node[i].dy = gridy_new[node[boundary_node[i]].no-1] - gridy[node[boundary_node[i]].no -1];


			dx1[i] = node[i].dx;
			dy1[i] = node[i].dy;

			//printf("%f \t %f \n ", dx1[i], dy1[i]);
		}
				
		//printf("translation of boundary done\n");

		/*----------------fixed the outer boundary -----------------------*/

		if((node[boundary_node[i]].bc_type ==1) || (node[boundary_node[i]].bc_type ==2) || (node[boundary_node[i]].bc_type ==7) || (node[boundary_node[i]].bc_type ==8))
		{

			gridx_new[node[boundary_node[i]].no-1] = gridx[node[boundary_node[i]].no -1];

			gridy_new[node[boundary_node[i]].no-1] = gridy[node[boundary_node[i]].no -1];

		//printf("%f \t %f \n", gridx_new[node[boundary_node[i]].no-1], gridy_new[node[boundary_node[i]].no-1]);

		/* ----------------- find displacement -----------------------*/

			node[i].dx = gridx_new[node[boundary_node[i]].no-1] - gridx[node[boundary_node[i]].no -1];
	
			node[i].dy = gridy_new[node[boundary_node[i]].no-1] - gridy[node[boundary_node[i]].no -1];


			dx1[i] = node[i].dx;
			dy1[i] = node[i].dy;

			//printf("%f \t %f \n ", dx1[i], dy1[i]);
		}
		
		//printf("outer boundary fixed\n");
	}


/*	apply the RBF to the outer nodes only to */
	
	for(i=1; i<=no_boundary_node; i++)
	{
		for(j=1; j<=no_boundary_node; j++)
		{
			if(i==j)
			{
				M[i][j] = 0.0;
			}
			else
			{
				M[i][j] = ( ((gridx[node[boundary_node[j]].no-1] - gridx[node[boundary_node[i]].no -1])*(gridx[node[boundary_node[j]].no-1] - gridx[node[boundary_node[i]].no -1])) + ((gridy[node[boundary_node[j]].no-1] - gridy[node[boundary_node[i]].no -1])*(gridy[node[boundary_node[j]].no-1] - gridy[node[boundary_node[i]].no -1])) )* ( log( (fabs(gridx[node[boundary_node[j]].no-1] - gridx[node[boundary_node[i]].no -1])+fabs(gridy[node[boundary_node[j]].no-1] - gridy[node[boundary_node[i]].no -1])) ) );
			}
			//printf("%f \t", M[i][j]);
		}
		//printf("\n");
	}

/*------------------ find the polynomial term -----------------------------------*/
	for(i=1; i<=no_boundary_node; i++)
	{
		P[i][1] = 1.0;
	
		P[i][2] = gridx[node[boundary_node[i]].no-1];

		P[i][3] = gridy[node[boundary_node[i]].no-1];

		/*------------------- P transpose -------------------------*/

		PT[1][i] = 1.0;
	
		PT[2][i] = gridx[node[boundary_node[i]].no-1];

		PT[3][i] = gridy[node[boundary_node[i]].no-1];
		
		//printf("%f \t %f \t \n", PT[2][i], PT[3][i]);
	}

/*-----------------create a block matrix ----------------------------*/
	
k = 0; kkk = 0;
	for(i=1; i<=(no_boundary_node + 3); i++)
	{
		for(j=1; j<=(no_boundary_node +3) ; j++)
		{
			if((i<=no_boundary_node) && (j<=no_boundary_node))
			{
				R[i][j] = M[i][j];
			}
			if((i<=no_boundary_node) &&(j>no_boundary_node) )
			{
				k = j-no_boundary_node;	//printf("\t\t%d \n",k);
				R[i][j] = P[i][k];
			}
			if((i>no_boundary_node) && (j<=no_boundary_node))
			{
				kkk = i-no_boundary_node;
				R[i][j] = PT[kkk][j];
			}
			//printf("%f \t ", R[i][j]);
		}
		//printf("\n");
	}
/*-----------------------solve block matrix by LU decomposition ----------------------------*/

/*-------------------- alpha_x--------------------------------*/
	for(i=1; i<=(no_boundary_node + 3); i++)
	{
		for(j=1; j<=(no_boundary_node +3) ; j++)
		{
			A[i][j] = R[i][j];
		}
	}
	
	for(i=1; i<=(no_boundary_node + 3); i++)
	{
		indx[i] = i;
	}

	ludcmp();
	
	for(i=1; i<=(no_boundary_node + 3); i++)
	{
		col[i]=dx1[i];	
	}

	lubksb();

	for(i=1; i<=(no_boundary_node + 3); i++)
	{	
		alpha_x[i]=col[i];
		//printf("alpha_x[%d] = \t %f \n", i, alpha_x[i]);
	}


/*-------------------------------alpha_y----------------------------------------*/
	for(i=1; i<=(no_boundary_node + 3); i++)
	{
		for(j=1; j<=(no_boundary_node +3) ; j++)
		{
			A[i][j] = R[i][j];
		}
	}
	
	for(i=1; i<=(no_boundary_node + 3); i++)
	{
		indx[i] = i;
	}

	ludcmp();
	
	for(i=1; i<=(no_boundary_node + 3); i++)
	{
		col[i]=dy1[i];	
	}

	lubksb();

	for(i=1; i<=(no_boundary_node + 3); i++)
	{	
		alpha_y[i]=col[i];
		//printf("alpha_y[%d] = \t %f \n", i, alpha_y[i]);
	}

/*------------------------end matrix solution-----------------------------*/

/*------------------------ find new cordinates -------------------------------*/

	for(i=1; i<=node_max; i++)
	{
		if(node[i].bc_type == 0)
		{
			node[i].dx = 0.0;
			node[i].dy = 0.0;

			for(j=1; j<=(no_boundary_node + 3); j++)
			{
				if(j <= no_boundary_node)
				{ 
					node[i].dx = node[i].dx  + alpha_x[j] * ( ((gridx[node[i].no-1] - gridx[node[boundary_node[j]].no -1]) *(gridx[node[i].no-1] - gridx[node[boundary_node[j]].no -1])) + ((gridy[node[i].no-1] - gridy[node[boundary_node[j]].no -1])*(gridy[node[i].no-1] - gridy[node[boundary_node[j]].no -1])) ) *  (log( (fabs(gridx[node[i].no-1] - gridx[node[boundary_node[j]].no -1]) + fabs(gridy[node[i].no-1] - gridy[node[boundary_node[j]].no -1])) )) ;

					node[i].dy = node[i].dy  + alpha_y[j] * ( ((gridx[node[i].no-1] - gridx[node[boundary_node[j]].no -1]) *(gridx[node[i].no-1] - gridx[node[boundary_node[j]].no -1])) + ((gridy[node[i].no-1] - gridy[node[boundary_node[j]].no -1])*(gridy[node[i].no-1] - gridy[node[boundary_node[j]].no -1])) ) *  (log( (fabs(gridx[node[i].no-1] - gridx[node[boundary_node[j]].no -1]) + fabs(gridy[node[i].no-1] - gridy[node[boundary_node[j]].no -1])) )) ;
					
					//printf("node[%d]=%f\n",i,node[i].dy);
				}
				if(j == (no_boundary_node +1))
				{
					node[i].dx = node[i].dx + alpha_x[no_boundary_node +1];

					node[i].dy = node[i].dy + alpha_y[no_boundary_node +1];
					
					//printf("node[%d]=%f\n",i,node[i].dy);
				}
				if(j == (no_boundary_node +2))
				{
					node[i].dx = node[i].dx + (alpha_x[no_boundary_node +2]*gridx[node[i].no-1]);

					node[i].dy = node[i].dy + (alpha_y[no_boundary_node +2]*gridx[node[i].no-1]);
				}
				if(j == (no_boundary_node +3))
				{
					node[i].dx = node[i].dx + (alpha_x[no_boundary_node +3]*gridy[node[i].no-1]);
			
					node[i].dy = node[i].dy + (alpha_y[no_boundary_node +3]*gridy[node[i].no-1]);
				}
			 
			}
		}
	}

// find new x and y position of interior mesh
	for(i=1; i<=node_max; i++)
	{
		if(node[i].bc_type ==0)
		{
			gridx_new[node[i].no - 1] = gridx[node[i].no -1] + node[i].dx;
	
			gridy_new[node[i].no - 1] = gridy[node[i].no -1] + node[i].dy;
		}
		/*if(node[i].bc_type ==1)
		{
			gridx_new[node[i].no - 1] = gridx[node[i].no -1] + node[i].dx;
	
			gridy_new[node[i].no - 1] = gridy[node[i].no -1] + node[i].dy;
		}
		if(node[i].bc_type ==2)
		{
			gridx_new[node[i].no - 1] = gridx[node[i].no -1] + node[i].dx;
	
			gridy_new[node[i].no - 1] = gridy[node[i].no -1] + node[i].dy;
		}
		if(node[i].bc_type ==3)
		{
			gridx_new[node[i].no - 1] = gridx[node[i].no -1];
	
			gridy_new[node[i].no - 1] = gridy[node[i].no -1];
		}*/
		
	}
	
	printf("rbf_trans done\n");
}


























	



