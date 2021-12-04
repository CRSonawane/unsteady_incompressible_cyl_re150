#include "definitions_rbf.h"

void readcgnsdata_rbf()
{
	int file_index, no_base, no_zones, zone_size[3][3], no_nodes, node_min, nsections;
	
	int element_min, element_max, nbndry, parent_flag, iparentdata;
	
	//int *elementdata_topwall, *elementdata_botwall, *elementdata_inout;
	
	int ncells,temp,count,addside;

	int nneigh=4,temp1,temp2,addnode1,addnode2,no_present_node,ii,k2,repeat0,repeat1, *v_present;
	
	int i,j,k,kk,l,junk,cell1,cell2;
        
        int no_present_sides,no_present_cells,newside[4][2];
	
        int no_inlet_sides, no_outlet_sides, no_cyltopleft_sides, no_cyltopright_sides, no_cylbotleft_sides, no_cylbotright_sides, no_topside_sides, no_bottomside_sides;
         
	int v1,v2,left,right;

	int vn[4][10],ftemp,ftemp1;
	
	int n1,n2,n3,n4;
	
	double x1,x2,y1,y2,x3,y3;

	double diffx,diffy,diff1,diff2,diffx2,diffy2;
	
	double dx,dy,L;
	
	char zone_name[25],coordname1[25],coordname2[25],elementsection_name[25];
	
	DataType_t datatype1,datatype2;
	
	ElementType_t element_type;
	
	cg_open("grid.cgns",CG_MODE_READ,&file_index);


	cg_nbases(file_index,&no_base);
	
	cg_nzones(file_index,no_base,&no_zones);
	
	cg_zone_read(file_index,no_base,no_zones,zone_name,zone_size[0]);/*gets number of nodes and cells*/
	
	cg_coord_info(file_index,no_base,no_zones,1,&datatype1,coordname1);
	
	cg_coord_info(file_index,no_base,no_zones,2,&datatype2,coordname2);
	
	node_min = 1;
	
	node_max = zone_size[0][0];
	no_point = node_max;
	no_cell = zone_size[0][1];
	
	printf("node_max=%d\tno_point=%d\tno_cell=%d\n",node_max,no_point,no_cell);
	
	gridx = malloc((node_max+5) * sizeof(double));
	
	gridy = malloc((node_max+5) * sizeof(double));

	v_present = (int *)malloc((node_max+5) * sizeof(int));
	
	cg_coord_read(file_index,no_base,no_zones,coordname1,RealDouble,&node_min,&node_max,gridx);
	
	cg_coord_read(file_index,no_base,no_zones,coordname2,RealDouble,&node_min,&node_max,gridy);
	
	cg_nsections(file_index,no_base,no_zones,&nsections);
	
	printf("no of sections=%d\n",nsections);
	
	for(i=1;i<=nsections;i++)
	{
		cg_section_read(file_index,no_base,no_zones,i,elementsection_name,&element_type,&element_min,&element_max,&nbndry,&parent_flag);
	
				
		if(strcmp(elementsection_name,"fluid")==0)
		{
			ncells = element_max - element_min + 1 ;
			
			no_cell = ncells;
		
			printf("no of fluid cells=%d\n",no_cell);
			
			elementdata_fluid = malloc(ncells * 4 * sizeof(int));
			
			cg_elements_read(file_index,no_base,no_zones,i,elementdata_fluid,&iparentdata);
		}



		if(strcmp(elementsection_name,"inlet")==0)

		{



			ncells = element_max - element_min + 1 ;

        

			no_inlet_sides = ncells;



                        printf("Total no of inlet edges are:%d\n",no_inlet_sides);



			elementdata_inlet = malloc(ncells * 2 * sizeof(int));



			cg_elements_read(file_index,no_base,no_zones,i,elementdata_inlet,&iparentdata);



		}



		if(strcmp(elementsection_name,"outlet")==0)

		{



			ncells = element_max - element_min + 1 ;



			no_outlet_sides = ncells;



                        printf("Total no of outlet edges are:%d\n",no_outlet_sides);



			elementdata_outlet = malloc(ncells * 2 * sizeof(int));



			cg_elements_read(file_index,no_base,no_zones,i,elementdata_outlet,&iparentdata);



		}



		if(strcmp(elementsection_name,"cyltopleft")==0)

		{



			ncells = element_max - element_min + 1 ;



                        no_cyltopleft_sides = ncells;



                        printf("Total no of cyl_topleft edges are:%d\n",no_cyltopleft_sides);



			elementdata_cyltopleft = malloc(ncells * 2 * sizeof(int));



			cg_elements_read(file_index,no_base,no_zones,i,elementdata_cyltopleft,&iparentdata);



		}



		if(strcmp(elementsection_name,"cyltopright")==0)

		{



			ncells = element_max - element_min + 1 ;



			no_cyltopright_sides = ncells;



                        printf("Total no of cyl_topright edges are:%d\n",no_cyltopright_sides);



			elementdata_cyltopright = malloc(ncells * 2 * sizeof(int));



			cg_elements_read(file_index,no_base,no_zones,i,elementdata_cyltopright,&iparentdata);

		}



		if(strcmp(elementsection_name,"cylbotleft")==0)

		{



			ncells = element_max - element_min + 1 ;



			no_cylbotleft_sides = ncells;



                        printf("Total no of cyl_botleft edges are:%d\n",no_cylbotleft_sides);



			elementdata_cylbotleft = malloc(ncells * 2 * sizeof(int));



			cg_elements_read(file_index,no_base,no_zones,i,elementdata_cylbotleft,&iparentdata);


		}



		if(strcmp(elementsection_name,"cylbotright")==0)

		{



			ncells = element_max - element_min + 1 ;



			no_cylbotright_sides = ncells;



                        printf("Total no of cyl_botright edges are:%d\n",no_cylbotright_sides);



			elementdata_cylbotright = malloc(ncells * 2 * sizeof(int));



			cg_elements_read(file_index,no_base,no_zones,i,elementdata_cylbotright,&iparentdata);


		}

		
		if(strcmp(elementsection_name,"topside")==0)

		{



			ncells = element_max - element_min + 1 ;




			no_topside_sides = ncells;


                        printf("Total no of topside edges are:%d\n",no_topside_sides);


			elementdata_topside = malloc(ncells * 2 * sizeof(int));


			cg_elements_read(file_index,no_base,no_zones,i,elementdata_topside,&iparentdata);



		}



		if(strcmp(elementsection_name,"bottomside")==0)

		{



			ncells = element_max - element_min + 1 ;


			no_bottomside_sides = ncells;



                        printf("Total no of bottomside edges are:%d\n",no_bottomside_sides);



			elementdata_bottomside = malloc(ncells * 2 * sizeof(int));



			cg_elements_read(file_index,no_base,no_zones,i,elementdata_bottomside,&iparentdata);



		}

	


	}

	

	

	cg_close(file_index);

	

	/*Find the number of sides from the formula*/

	

	

	no_side = no_cell + node_max + 1;

	

	

	/*-----------------------------------------*/

	

	/*Allocate memory and initlise the data structures*/

	

	

	no_boundarysides = no_cyltopleft_sides + no_cyltopright_sides + no_cylbotleft_sides + no_cylbotright_sides + no_inlet_sides + no_outlet_sides + no_topside_sides + no_bottomside_sides;
	side = (struct side_data *)malloc((no_side + 1) * sizeof(struct side_data));
	
	//cell = (struct cell_data *)malloc((no_cell + no_boundaryedges +1) * sizeof(struct cell_data));
	
	node = (struct node_data *)malloc((node_max+5) * sizeof(struct node_data));


	
	/*-------------------------------------------------*/
	
	
	/*Initilse valules for sides and nodes*/
	
	for(i=1;i<=no_side;i++)
	{
		side[i].no_adjacent_cell = 0;
		
		side[i].bc_type = 0;
	}

	for(i=1;i<=node_max;i++)
	{
		node[i].no_adjacent_side = 0;
		
		node[i].bc_type = 0;

		node[i].no = 0;

	}
	
	/*-----------------------------------*/

	
		
	/*-------------------Create faces-------------------*/
	
	no_present_sides = 0;
	no_present_node = 0;
	
	for(i=1;i<=no_cell;i++)
	{
		temp=(i-1)*4;



		newside[0][0] = elementdata_fluid[temp];



		newside[0][1] = elementdata_fluid[temp+1];



		newside[1][0] = elementdata_fluid[temp+1];



		newside[1][1] = elementdata_fluid[temp+2];



		newside[2][0] = elementdata_fluid[temp+2];



		newside[2][1] = elementdata_fluid[temp+3];



		newside[3][0] = elementdata_fluid[temp+3];



		newside[3][1] = elementdata_fluid[temp];

		

				

		

		count = 0; /*no new sides added in this loop*/

		

		for(j=0;j<=3;j++)

		{

			addside = 1;

			

			/* Loop to check if the side is already present in the side list

			if present addside variable is set to 0*/

			

			for(k=1;k<=no_present_sides;k++)

			{	

				if(newside[j][0] == side[k].point[0] || newside[j][0] == side[k].point[1])

				{

					if(newside[j][1] == side[k].point[0] || newside[j][1] == side[k].point[1])

					{

						addside = 0;

					

						side[k].adjacent_cell[side[k].no_adjacent_cell] = i;

						

						side[k].no_adjacent_cell++;

					}

				}

			}

			/*-----------------------------------------------------------------*/

			

			/*If addside variable has not been set to 0 in the search loop

			add the newside to the side datastructure list*/

			

			if(addside==1)

			{

				count++;

					

				side[no_present_sides + count].point[0] = newside[j][0];

					

				side[no_present_sides + count].point[1] = newside[j][1];

					

				side[no_present_sides + count].adjacent_cell[0] = i;

					

				side[no_present_sides + count].no_adjacent_cell++;



// add node to database

				temp1 = temp+j;

				

				if(j==3)		temp2 = temp-j+3;

				else			temp2 = temp+j+1;



				addnode1=1;

				addnode2=1;

		

				for(k=1;k<=no_present_node;k++)

				{

					if(elementdata_fluid[temp1]==v_present[k])		

					{

						addnode1=0;

						node[v_present[k]].no_adjacent_side++;

						node[v_present[k]].adjacent_side[node[v_present[k]].no_adjacent_node] = no_present_sides + count;

					}

					if(elementdata_fluid[temp2]==v_present[k])		

					{

						addnode2=0;

						node[v_present[k]].no_adjacent_side++;

						node[v_present[k]].adjacent_side[node[v_present[k]].no_adjacent_side] = no_present_sides + count;

					}

				}

				

				if(addnode1==1)

				{

					no_present_node++;

					v_present[no_present_node] = elementdata_fluid[temp1];

					node[elementdata_fluid[temp1]].no = elementdata_fluid[temp1];

					node[elementdata_fluid[temp1]].no_adjacent_side++;

					node[elementdata_fluid[temp1]].adjacent_side[node[elementdata_fluid[temp1]].no_adjacent_side] = no_present_sides + count;

				}



				if(addnode2==1)

				{

					no_present_node++;

					v_present[no_present_node] = elementdata_fluid[temp2];

					node[elementdata_fluid[temp2]].no = elementdata_fluid[temp2];

					node[elementdata_fluid[temp2]].no_adjacent_node++;

					node[elementdata_fluid[temp2]].adjacent_side[node[elementdata_fluid[temp2]].no_adjacent_side] = no_present_sides + count;

				}

										

			}

			

			/*-----------------------------------------------------------------*/



				

		}

		

		no_present_sides = no_present_sides + count;

	}

	

	/*--------***---------End Create Faces-----------***--------*/

	

	

	no_present_cells = no_cell;



/*--------------------Find the boundary sides--------------------*/

	

	for(i=1;i<=no_side;i++)

	{

		/*Loop for testing whether the side is a wall edge*/


		for(j=1;j<=no_inlet_sides;j++)

		{



			temp = (j-1)*2;



			if(side[i].point[0] == elementdata_inlet[temp] || side[i].point[1] == elementdata_inlet[temp])

			{

				if(side[i].point[0] == elementdata_inlet[temp+1] || side[i].point[1] == elementdata_inlet[temp+1])

				{



					side[i].bc_type = 1;



					/* Apply boundary condition to the node*/



					node[side[i].point[0]].bc_type = 1;



					node[side[i].point[1]].bc_type = 1;



					//edge[i].adjacent_cell[edge[i].no_adjacent_cell] = no_present_cells + 1;



					//edge[i].no_adjacent_cell++;



					//no_present_cells++;



				}

			}

		}



		for(j=1;j<=no_outlet_sides;j++)

		{

			temp = (j-1)*2;



			if(side[i].point[0] == elementdata_outlet[temp] || side[i].point[1] == elementdata_outlet[temp])

			{

				if(side[i].point[0] == elementdata_outlet[temp+1] || side[i].point[1] == elementdata_outlet[temp+1])

				{

					side[i].bc_type = 2;



					/* Apply boundary condition to the node*/



					node[side[i].point[0]].bc_type = 2;



					node[side[i].point[1]].bc_type = 2;



					//edge[i].adjacent_cell[edge[i].no_adjacent_cell] = no_present_cells + 1;



					//edge[i].no_adjacent_cell++;



					//no_present_cells++;



				}

			}

		}



	/*Loop for testing whether the side is a inout edge*/


		for(j=1;j<=no_cyltopleft_sides;j++)

		{

			temp = (j-1)*2;



			if(side[i].point[0] == elementdata_cyltopleft[temp] || side[i].point[1] == elementdata_cyltopleft[temp])

			{

				if(side[i].point[0] == elementdata_cyltopleft[temp+1] || side[i].point[1] == elementdata_cyltopleft[temp+1])

				{


					side[i].bc_type = 3;



					/* Apply boundary condition to the node*/



					node[side[i].point[0]].bc_type = 3;



					node[side[i].point[1]].bc_type = 3;



					//edge[i].adjacent_cell[edge[i].no_adjacent_cell] = no_present_cells + 1;



					//edge[i].no_adjacent_cell++;



					//no_present_cells++;

				}

			}

		}



		for(j=1;j<=no_cyltopright_sides;j++)

		{

			temp = (j-1)*2;



			if(side[i].point[0] == elementdata_cyltopright[temp] || side[i].point[1] == elementdata_cyltopright[temp])

			{

				if(side[i].point[0] == elementdata_cyltopright[temp+1] || side[i].point[1] == elementdata_cyltopright[temp+1])

				{

					side[i].bc_type = 4;



					/* Apply boundary condition to the node*/



					node[side[i].point[0]].bc_type = 4;



					node[side[i].point[1]].bc_type = 4;



					//edge[i].adjacent_cell[edge[i].no_adjacent_cell] = no_present_cells + 1;



					//edge[i].no_adjacent_cell++;



					//no_present_cells++;

				}

			}

		}



		for(j=1;j<=no_cylbotleft_sides;j++)

		{

			temp = (j-1)*2;



			if(side[i].point[0] == elementdata_cylbotleft[temp] || side[i].point[1] == elementdata_cylbotleft[temp])

			{

				if(side[i].point[0] == elementdata_cylbotleft[temp+1] || side[i].point[1] == elementdata_cylbotleft[temp+1])

				{

					side[i].bc_type = 5;



					/* Apply boundary condition to the node*/



					node[side[i].point[0]].bc_type = 5;



					node[side[i].point[1]].bc_type = 5;



					//edge[i].adjacent_cell[edge[i].no_adjacent_cell] = no_present_cells + 1;



					//edge[i].no_adjacent_cell++;



					//no_present_cells++;

				}

			}

		}



		for(j=1;j<=no_cylbotright_sides;j++)

		{

			temp = (j-1)*2;



			if(side[i].point[0] == elementdata_cylbotright[temp] || side[i].point[1] == elementdata_cylbotright[temp])

			{

				if(side[i].point[0] == elementdata_cylbotright[temp+1] || side[i].point[1] == elementdata_cylbotright[temp+1])

				{

					side[i].bc_type = 6;



					/* Apply boundary condition to the node*/



					node[side[i].point[0]].bc_type = 6;



					node[side[i].point[1]].bc_type = 6;



					//edge[i].adjacent_cell[edge[i].no_adjacent_cell] = no_present_cells + 1;



					//edge[i].no_adjacent_cell++;



					//no_present_cells++;

				}

			}

		}



		

		for(j=1;j<=no_topside_sides;j++)

		{

			temp = (j-1)*2;



			if(side[i].point[0] == elementdata_topside[temp] || side[i].point[1] == elementdata_topside[temp])

			{

				if(side[i].point[0] == elementdata_topside[temp+1] || side[i].point[1] == elementdata_topside[temp+1])

				{



					side[i].bc_type = 7;



					/* Apply boundary condition to the node*/



					node[side[i].point[0]].bc_type = 7;



					node[side[i].point[1]].bc_type = 7;



					//edge[i].adjacent_cell[edge[i].no_adjacent_cell] = no_present_cells + 1;



					//edge[i].no_adjacent_cell++;

                                        
					//no_present_cells++;

				}

			}

		}



		

		for(j=1;j<=no_bottomside_sides;j++)

		{

			temp = (j-1)*2;



			if(side[i].point[0] == elementdata_bottomside[temp] || side[i].point[1] == elementdata_bottomside[temp])

			{

				if(side[i].point[0] == elementdata_bottomside[temp+1] || side[i].point[1] == elementdata_bottomside[temp+1])

				{

					side[i].bc_type = 8;



					/* Apply boundary condition to the node*/



					node[side[i].point[0]].bc_type = 8;



					node[side[i].point[1]].bc_type = 8;



					//edge[i].adjacent_cell[edge[i].no_adjacent_cell] = no_present_cells + 1;



					//edge[i].no_adjacent_cell++;



					//no_present_cells++;



				}



			}



		}



	}


	
	
	/*--------------------Generating Connectivity--------------------*/
	/*for(i=1;i<=node_max;i++)
	{
		node[i].jj[0] = 0;
		node[i].jj[1] = 0;
		node[i].jj[2] = 0;
		node[i].jj[3] = 0;
		node[i].no_neigh = 0;
	}		
	diff = 2;
	diffmin = del;
	for(i=1;i<=node_max;i++)
	{
		count = 0;
		for(j=1;j<=node_max;j++)
		{
                        /*if(node[i].jj[0]==nneigh && node[i].jj[1]==nneigh && node[i].jj[2]==nneigh && node[i].jj[3]==nneigh)
                        {
                                break;
                        }*/ // 0=leftbottom 1=lefttop 2=rightbottom 3=righttop
			/*if(j==i)	continue;
			else
			{
				diffx = gridx[j-1]-gridx[i-1];
				diffy = gridy[j-1]-gridy[i-1];
				diff1 = sqrt(diffx*diffx+diffy*diffy);

				if(diff1<=diff)
				{   
					ftemp1 = j;
                            	    	if(diffx<-diffmin)
                            	    	{	
						if(diffy<-diffmin)
                             			{	
							kk = 0;
							for(k=1;k<=(node[i].jj[0]+node[i].jj[1]+node[i].jj[2]+node[i].jj[3]);k++)
							{
								diffx2 = gridx[node[i].neighbour[k]-1]-gridx[i-1];
								diffy2 = gridy[node[i].neighbour[k]-1]-gridy[i-1];
								diff2 = sqrt(diffx2*diffx2+diffy2*diffy2);
								if(diffx2<-diffmin && diffy2<-diffmin)
								{
									kk++;
									if(diff2>diff1)
									{
										ftemp = node[i].neighbour[k];
										node[i].neighbour[k] = ftemp1;
										node[i].neighbourlb[kk] = ftemp1;
										ftemp1 = ftemp;
										diff1 = diff2;
									}
								}
							}// 0=leftbottom 1=lefttop 2=rightbottom 3=righttop

			                               	if(node[i].jj[0]<nneigh)
	                      		          	{
	                      		                 	node[i].jj[0]++;
	                       		                 	node[i].neighbour[node[i].jj[0]+node[i].jj[1]+node[i].jj[2]+node[i].jj[3]] = ftemp1;
								node[i].neighbourlb[node[i].jj[0]] = ftemp1;
	                        		       	} 
						}

						if(diffy>diffmin)
	                         	        {	
							kk = 0;
							for(k=1;k<=(node[i].jj[0]+node[i].jj[1]+node[i].jj[2]+node[i].jj[3]);k++)
							{
								diffx2 = gridx[node[i].neighbour[k]-1]-gridx[i-1];
								diffy2 = gridy[node[i].neighbour[k]-1]-gridy[i-1];
								diff2 = sqrt(diffx2*diffx2+diffy2*diffy2);
								if(diffx2<-diffmin && diffy2>diffmin)
								{	
									kk++;
									if(diff2>diff1)
									{
										ftemp = node[i].neighbour[k];
										node[i].neighbour[k] = ftemp1;
										node[i].neighbourlt[kk] = ftemp1;
										ftemp1 = ftemp;
										diff1 = diff2;
									}
								}
							}						
	
							if(node[i].jj[1]<nneigh)
	                                		{
	                                        		node[i].jj[1]++;
	                       		                 	node[i].neighbour[node[i].jj[0]+node[i].jj[1]+node[i].jj[2]+node[i].jj[3]] = ftemp1;
								node[i].neighbourlt[node[i].jj[1]] = ftemp1;
	                                		}
						}
					}

				  	if(diffx>diffmin)
                                  	{	
						if(diffy<-diffmin)
                             			{	
							kk = 0;
							for(k=1;k<=(node[i].jj[0]+node[i].jj[1]+node[i].jj[2]+node[i].jj[3]);k++)
							{
								diffx2 = gridx[node[i].neighbour[k]-1]-gridx[i-1];
								diffy2 = gridy[node[i].neighbour[k]-1]-gridy[i-1];
								diff2 = sqrt(diffx2*diffx2+diffy2*diffy2);
								if(diffx2>diffmin && diffy2<-diffmin)
								{
									kk++;
									if(diff2>diff1)
									{
										ftemp = node[i].neighbour[k];
										node[i].neighbour[k] = ftemp1;
										node[i].neighbourrb[kk] = ftemp1;
										ftemp1 = ftemp;
										diff1 = diff2;
									}
								}
							}

			                               	if(node[i].jj[2]<nneigh)
	                      		          	{
	                       		                 	node[i].jj[2]++;
	                       		                 	node[i].neighbour[node[i].jj[0]+node[i].jj[1]+node[i].jj[2]+node[i].jj[3]] = ftemp1;
								node[i].neighbourrb[node[i].jj[2]] = ftemp1;
	                        		       	}
						}

						if(diffy>diffmin)
	                         	        {	
							kk = 0;
							for(k=1;k<=(node[i].jj[0]+node[i].jj[1]+node[i].jj[2]+node[i].jj[3]);k++)
							{
								diffx2 = gridx[node[i].neighbour[k]-1]-gridx[i-1];
								diffy2 = gridy[node[i].neighbour[k]-1]-gridy[i-1];
								diff2 = sqrt(diffx2*diffx2+diffy2*diffy2);
								if(diffx2>diffmin && diffy2>diffmin)
								{	kk++;
									if(diff2>diff1)
									{
										ftemp = node[i].neighbour[k];
										node[i].neighbour[k] = ftemp1;
										node[i].neighbourrt[kk] = ftemp1;
										ftemp1 = ftemp;
										diff1 = diff2;
									}
								}
							}

							if(node[i].jj[3]<nneigh)
	                                		{
	                                        		node[i].jj[3]++;
	                       		                 	node[i].neighbour[node[i].jj[0]+node[i].jj[1]+node[i].jj[2]+node[i].jj[3]] = ftemp1;
								node[i].neighbourrt[node[i].jj[3]] = ftemp1;
	                                		}
						}
					}
					if(fabs(diffx)<diffmin || fabs(diffy)<diffmin)
					{
							node[i].neighbour[count+1] = ftemp1;				

					}

					count++;
				}
			}
			node[i].no_neigh = count;
			//printf("node[%d].no.neigh = %d \n", i, count);
		}
	}

/*	for(j=1;j<=node_max;j++)
	{
			
		printf("%d\t%d\t%d\t\n",j,node[j].no,node[j].bc_type);
	}	
*/

	
	
	

printf("readcgnsdata_rbf done\n");
}
	

















