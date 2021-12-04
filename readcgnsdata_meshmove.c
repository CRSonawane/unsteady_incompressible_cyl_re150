#include "definitions_1.h"

void readcgnsdata_meshmove()
{
	int file_index, no_base, no_zones, zone_size[3][3], no_vertices, vertex_min, nsections;
	
	int element_min, element_max, nbndry, parent_flag, iparentdata;
	
	//int *elementdata_wall,*elementdata_inout;
	
	int ncells,temp,count,addedge;

	int nneigh=1,temp1,temp2,addvertex1,addvertex2,no_present_vertex,ii,k2,repeat0,repeat1, *v_present;
	
	int i,j,k,kk,l,junk,cell1,cell2;
	
	int no_present_edges,no_present_cells,newedge[4][2];

	int no_inout_edges,no_topwall_edges, no_botwall_edges,no_bottom_edges;
	
	int v1,v2,left,right;

	int vn[4][10],ftemp,ftemp1;
	
	int n1,n2,n3,n4;
	
	double x1,x2,y1,y2,x3,y3;

	double diffx,diffy,diff1,diff2,diffx2,diffy2;
	
	double dx,dy,L;
	
	char zone_name[25],coordname1[25],coordname2[25],elementsection_name[25];
	
	DataType_t datatype1,datatype2;
	
	ElementType_t element_type;
	
	cg_open("grid_0.cgns",MODE_READ,&file_index);



	cg_nbases(file_index,&no_base);
	
	cg_nzones(file_index,no_base,&no_zones);
	
	cg_zone_read(file_index,no_base,no_zones,zone_name,zone_size[0]);/*gets number of vertex and cells*/
	
	cg_coord_info(file_index,no_base,no_zones,1,&datatype1,coordname1);
	
	cg_coord_info(file_index,no_base,no_zones,2,&datatype2,coordname2);
	
	vertex_min = 1;
	
	vertex_max = zone_size[0][0];
	no_point = vertex_max;
	no_cell = zone_size[0][1];
	
	gridx = malloc((vertex_max+5) * sizeof(double));
	
	gridy = malloc((vertex_max+5) * sizeof(double));

	v_present = (int *)malloc((vertex_max+5) * sizeof(int));
	
	cg_coord_read(file_index,no_base,no_zones,coordname1,RealDouble,&vertex_min,&vertex_max,gridx);
	
	cg_coord_read(file_index,no_base,no_zones,coordname2,RealDouble,&vertex_min,&vertex_max,gridy);
	
	cg_nsections(file_index,no_base,no_zones,&nsections);
	
	for(i=1;i<=nsections;i++)
	{
		cg_section_read(file_index,no_base,no_zones,i,elementsection_name,&element_type,&element_min,&element_max,&nbndry,&parent_flag);
			
		if(strcmp(elementsection_name,"fluid")==0)
		{
			ncells = element_max - element_min + 1 ;
			
			no_cell = ncells;
			
			printf("Total no of fluid cells are:%d\n",no_cell);
			
			elementdata_fluid = malloc(ncells * 4 * sizeof(int));
			
			cg_elements_read(file_index,no_base,no_zones,i,elementdata_fluid,&iparentdata);
		}
		
		
		if(strcmp(elementsection_name,"inout")==0)
		{
			ncells = element_max - element_min + 1 ;
			
			no_inout_edges = ncells;
			
			printf("Total no of inout edges are:%d\n",no_inout_edges);
			
			elementdata_inout = malloc(ncells * 2 * sizeof(int));
			
			cg_elements_read(file_index,no_base,no_zones,i,elementdata_inout,&iparentdata);
			
		}
		
		
		
		if(strcmp(elementsection_name,"topwall")==0)
		{
			ncells = element_max - element_min + 1 ;
			
			no_topwall_edges = ncells;
			
			 printf("Total no of topwall edges are:%d\n",no_topwall_edges);
			
			elementdata_topwall = malloc(ncells * 2 * sizeof(int));
			
			cg_elements_read(file_index,no_base,no_zones,i,elementdata_topwall,&iparentdata);
			
		}
		
		if(strcmp(elementsection_name,"botwall")==0)
		{
			ncells = element_max - element_min + 1 ;
			
			no_botwall_edges = ncells;
			
			printf("Total no of botwall edges are:%d\n",no_botwall_edges);
			
			elementdata_botwall = malloc(ncells * 2 * sizeof(int));
			
			cg_elements_read(file_index,no_base,no_zones,i,elementdata_botwall,&iparentdata);
		}
		

	
	}
	
	
	cg_close(file_index);
	
	/*Find the number of edges from the formula*/
	
	
	no_edge = no_cell + vertex_max - 1;
	
	
	/*-----------------------------------------*/
	
	/*Allocate memory and initlise the data structures*/
	
	
	no_boundaryedges = no_botwall_edges + no_topwall_edges + no_inout_edges;
	
	edge = (struct edge_data *)malloc((no_edge + 1) * sizeof(struct edge_data));
	
	//cell = (struct cell_data *)malloc((no_cell + no_boundaryedges +1) * sizeof(struct cell_data));
	
	vertex = (struct vertex_data *)malloc((vertex_max+5) * sizeof(struct vertex_data));


	
	/*-------------------------------------------------*/
	
	
	/*Initilse valules for edges and vertices*/
	
	for(i=1;i<=no_edge;i++)
	{
		edge[i].no_adjacent_cell = 0;
		
		edge[i].bc_type = 0;
	}

	for(i=1;i<=vertex_max;i++)
	{
		vertex[i].no_adjacent_edge = 0;
		
		vertex[i].bc_type = 0;

		vertex[i].no = 0;

	}
	
	/*-----------------------------------*/

	
		
	/*-------------------Create faces-------------------*/
	
	no_present_edges = 0;
	no_present_vertex = 0;
	
	for(i=1;i<=no_cell;i++)
	{
		temp=(i-1)*4;
		
		newedge[0][0] = elementdata_fluid[temp];
		newedge[0][1] = elementdata_fluid[temp+1];
		newedge[1][0] = elementdata_fluid[temp+1];
		newedge[1][1] = elementdata_fluid[temp+2];
		newedge[2][0] = elementdata_fluid[temp+2];
		newedge[2][1] = elementdata_fluid[temp+3];
		newedge[3][0] = elementdata_fluid[temp+3];
		newedge[3][1] = elementdata_fluid[temp];
				
		
		count = 0; /*no new edges added in this loop*/
		
		for(j=0;j<=3;j++)
		{
			addedge = 1;
			
			/* Loop to check if the edge is already present in the edge list
			if present addedge variable is set to 0*/
			
			for(k=1;k<=no_present_edges;k++)
			{	
				if(newedge[j][0] == edge[k].node[0] || newedge[j][0] == edge[k].node[1])
				{
					if(newedge[j][1] == edge[k].node[0] || newedge[j][1] == edge[k].node[1])
					{
						addedge = 0;
					
						edge[k].adjacent_cell[edge[k].no_adjacent_cell] = i;
						
						edge[k].no_adjacent_cell++;
					}
				}
			}
			/*-----------------------------------------------------------------*/
			
			/*If addedge variable has not been set to 0 in the search loop
			add the newedge to the edge datastructure list*/
			
			if(addedge==1)
			{
				count++;
					
				edge[no_present_edges + count].node[0] = newedge[j][0];
					
				edge[no_present_edges + count].node[1] = newedge[j][1];
					
				edge[no_present_edges + count].adjacent_cell[0] = i;
					
				edge[no_present_edges + count].no_adjacent_cell++;

// add vertex to database
				temp1 = temp+j;
				
				if(j==3)		temp2 = temp-j+3;
				else			temp2 = temp+j+1;

				addvertex1=1;
				addvertex2=1;
		
				for(k=1;k<=no_present_vertex;k++)
				{
					if(elementdata_fluid[temp1]==v_present[k])		
					{
						addvertex1=0;
						vertex[v_present[k]].no_adjacent_edge++;
						vertex[v_present[k]].adjacent_edge[vertex[v_present[k]].no_adjacent_edge] = no_present_edges + count;
					}
					if(elementdata_fluid[temp2]==v_present[k])		
					{
						addvertex2=0;
						vertex[v_present[k]].no_adjacent_edge++;
						vertex[v_present[k]].adjacent_edge[vertex[v_present[k]].no_adjacent_edge] = no_present_edges + count;
					}
				}
				
				if(addvertex1==1)
				{
					no_present_vertex++;
					v_present[no_present_vertex] = elementdata_fluid[temp1];
					vertex[elementdata_fluid[temp1]].no = elementdata_fluid[temp1];
					vertex[elementdata_fluid[temp1]].no_adjacent_edge++;
					vertex[elementdata_fluid[temp1]].adjacent_edge[vertex[elementdata_fluid[temp1]].no_adjacent_edge] = no_present_edges + count;
				}

				if(addvertex2==1)
				{
					no_present_vertex++;
					v_present[no_present_vertex] = elementdata_fluid[temp2];
					vertex[elementdata_fluid[temp2]].no = elementdata_fluid[temp2];
					vertex[elementdata_fluid[temp2]].no_adjacent_edge++;
					vertex[elementdata_fluid[temp2]].adjacent_edge[vertex[elementdata_fluid[temp2]].no_adjacent_edge] = no_present_edges + count;
				}
										
			}
			
			/*-----------------------------------------------------------------*/

				
		}
		
		no_present_edges = no_present_edges + count;
	}
	
	/*--------***---------End Create Faces-----------***--------*/
	
	
	no_present_cells = no_cell;

/*--------------------Find the boundary Edges--------------------*/
	
	for(i=1;i<=no_edge;i++)
	{
		
		/*Loop for testing weather the edge is a wall edge*/
		
		
		for(j=1;j<=no_inout_edges;j++)
		{
			temp = (j-1)*2;
			
			if(edge[i].node[0] == elementdata_inout[temp] || edge[i].node[1] == elementdata_inout[temp])
			{
				if(edge[i].node[0] == elementdata_inout[temp+1] || edge[i].node[1] == elementdata_inout[temp+1])
				{
					edge[i].bc_type = 1;
					
					/* Apply boundary condition to the vertex*/

					vertex[edge[i].node[0]].bc_type = 1;

					vertex[edge[i].node[1]].bc_type = 1;
					
					//edge[i].adjacent_cell[edge[i].no_adjacent_cell] = no_present_cells + 1;
					
					//edge[i].no_adjacent_cell++;
					
					//no_present_cells++;
				
				}
			}
		}

		for(j=1;j<=no_topwall_edges;j++)
		{
			temp = (j-1)*2;
			
			if(edge[i].node[0] == elementdata_topwall[temp] || edge[i].node[1] == elementdata_topwall[temp])
			{
				if(edge[i].node[0] == elementdata_topwall[temp+1] || edge[i].node[1] == elementdata_topwall[temp+1])
				{
					edge[i].bc_type = 2;
					
					/* Apply boundary condition to the vertex*/

					vertex[edge[i].node[0]].bc_type = 2;

					vertex[edge[i].node[1]].bc_type = 2;
					
					//edge[i].adjacent_cell[edge[i].no_adjacent_cell] = no_present_cells + 1;
					
					//edge[i].no_adjacent_cell++;
					
					//no_present_cells++;
				
				}
			}
		}

		
		for(j=1;j<=no_botwall_edges;j++)
		{
			temp = (j-1)*2;
			
			if(edge[i].node[0] == elementdata_botwall[temp] || edge[i].node[1] == elementdata_botwall[temp])
			{
				if(edge[i].node[0] == elementdata_botwall[temp+1] || edge[i].node[1] == elementdata_botwall[temp+1])
				{
					edge[i].bc_type = 3;
					
					/* Apply boundary condition to the vertex*/

					vertex[edge[i].node[0]].bc_type = 3;

					vertex[edge[i].node[1]].bc_type = 3;
					
					//edge[i].adjacent_cell[edge[i].no_adjacent_cell] = no_present_cells + 1;
					
					//edge[i].no_adjacent_cell++;
					
					//no_present_cells++;
				
				}
			}
		}

	}

	/*--------------------Generating Connectivity--------------------*/
	for(i=1;i<=vertex_max;i++)
	{
		vertex[i].jj[0] = 0;			// l
		vertex[i].jj[1] = 0;			// r
		vertex[i].jj[2] = 0;			// t
		vertex[i].jj[3] = 0;			// b
		vertex[i].jj[4] = 0;			// lt
		vertex[i].jj[5] = 0;			// lb
		vertex[i].jj[6] = 0;			// rt
		vertex[i].jj[7] = 0;			// rb
		vertex[i].no_neigh = 0;
	}		
	diff = 15.0;
	
	diffmin = 0.0;	

	for(i=1;i<=vertex_max;i++)
	{	
		for(j=1;j<=vertex_max;j++)
		{
			if(j==i)	continue;
			else
			{
				diffx = gridx[j-1]-gridx[i-1];
				diffy = gridy[j-1]-gridy[i-1];
				diff1 = sqrt(diffx*diffx+diffy*diffy);

				if(diff1<=diff)
				{   
					ftemp1 = j;
					
					if(diffx == diffmin)
					{
						if(diffy < diffmin)	// on -ve y axis
						{
							kk = 0;
							for(k=1;k<=(vertex[i].jj[0]+vertex[i].jj[1]+vertex[i].jj[2]+vertex[i].jj[3]+vertex[i].jj[4]+vertex[i].jj[5]+vertex[i].jj[6]+vertex[i].jj[7]);k++)
							{
								diffx2 = gridx[vertex[i].neighbour[k]-1]-gridx[i-1];
								diffy2 = gridy[vertex[i].neighbour[k]-1]-gridy[i-1];
								diff2 = sqrt(diffx2*diffx2+diffy2*diffy2);
	
								if((diffx2 == diffmin) && (diffy2 < diffmin))
								{	
									kk++;
									if(diff2>diff1)
									{
										ftemp = vertex[i].neighbour[k];
										vertex[i].neighbour[k] = ftemp1;
										vertex[i].neighbour_b[kk] = ftemp1;
										ftemp1 = ftemp;
										diff1 = diff2;
									}
								}
							}
			                               	if(vertex[i].jj[3]<nneigh)
	                      		          	{
	                      		                 	vertex[i].jj[3]++;
	                       		                 	vertex[i].neighbour[vertex[i].jj[0]+vertex[i].jj[1]+vertex[i].jj[2]+vertex[i].jj[3]+vertex[i].jj[4]+vertex[i].jj[5]+vertex[i].jj[6]+vertex[i].jj[7]] = ftemp1;
								vertex[i].neighbour_b[vertex[i].jj[3]] = ftemp1;
	                        		       	}
						}

						if(diffy > diffmin)	// on +ve y axis
						{
							kk = 0;
							for(k=1;k<=(vertex[i].jj[0]+vertex[i].jj[1]+vertex[i].jj[2]+vertex[i].jj[3]+vertex[i].jj[4]+vertex[i].jj[5]+vertex[i].jj[6]+vertex[i].jj[7]);k++)
							{
								diffx2 = gridx[vertex[i].neighbour[k]-1]-gridx[i-1];
								diffy2 = gridy[vertex[i].neighbour[k]-1]-gridy[i-1];
								diff2 = sqrt(diffx2*diffx2+diffy2*diffy2);
	
								if((diffx2 == diffmin) && (diffy2 > diffmin))
								{	
									kk++;
									if(diff2>diff1)
									{
										ftemp = vertex[i].neighbour[k];
										vertex[i].neighbour[k] = ftemp1;
										vertex[i].neighbour_t[kk] = ftemp1;
										ftemp1 = ftemp;
										diff1 = diff2;
									}
								}
							}
			                               	if(vertex[i].jj[2]<nneigh)
	                      		          	{
	                      		                 	vertex[i].jj[2]++;
	                       		                 	vertex[i].neighbour[vertex[i].jj[0]+vertex[i].jj[1]+vertex[i].jj[2]+vertex[i].jj[3]+vertex[i].jj[4]+vertex[i].jj[5]+vertex[i].jj[6]+vertex[i].jj[7]] = ftemp1;
								vertex[i].neighbour_t[vertex[i].jj[2]] = ftemp1;
	                        		       	}				

						}
					}

					if(diffx < diffmin)
                            	    	{	
						if(diffy < diffmin)		// III quad
                             			{	
						       kk = 0;
							for(k=1;k<=(vertex[i].jj[0]+vertex[i].jj[1]+vertex[i].jj[2]+vertex[i].jj[3]+vertex[i].jj[4]+vertex[i].jj[5]+vertex[i].jj[6]+vertex[i].jj[7]);k++)
							{
								diffx2 = gridx[vertex[i].neighbour[k]-1]-gridx[i-1];
								diffy2 = gridy[vertex[i].neighbour[k]-1]-gridy[i-1];
								diff2 = sqrt(diffx2*diffx2+diffy2*diffy2);
	
								if((diffx2 < diffmin) && (diffy2 < diffmin))
								{	
									kk++;
									if(diff2>diff1)
									{
										ftemp = vertex[i].neighbour[k];
										vertex[i].neighbour[k] = ftemp1;
										vertex[i].neighbour_lb[kk] = ftemp1;
										ftemp1 = ftemp;
										diff1 = diff2;
									}
								}
							}
			                               	if(vertex[i].jj[5]<nneigh)
	                      		          	{
	                      		                 	vertex[i].jj[5]++;
	                       		                 	vertex[i].neighbour[vertex[i].jj[0]+vertex[i].jj[1]+vertex[i].jj[2]+vertex[i].jj[3]+vertex[i].jj[4]+vertex[i].jj[5]+vertex[i].jj[6]+vertex[i].jj[7]] = ftemp1;
								vertex[i].neighbour_lb[vertex[i].jj[5]] = ftemp1;
	                        		       	}	
						}

						if(diffy > diffmin)		// II quad
	                         	        {	
							kk = 0;
							for(k=1;k<=(vertex[i].jj[0]+vertex[i].jj[1]+vertex[i].jj[2]+vertex[i].jj[3]+vertex[i].jj[4]+vertex[i].jj[5]+vertex[i].jj[6]+vertex[i].jj[7]);k++)
							{
								diffx2 = gridx[vertex[i].neighbour[k]-1]-gridx[i-1];
								diffy2 = gridy[vertex[i].neighbour[k]-1]-gridy[i-1];
								diff2 = sqrt(diffx2*diffx2+diffy2*diffy2);
	
								if((diffx2 < diffmin) && (diffy2 > diffmin))
								{	
									kk++;
									if(diff2>diff1)
									{
										ftemp = vertex[i].neighbour[k];
										vertex[i].neighbour[k] = ftemp1;
										vertex[i].neighbour_lt[kk] = ftemp1;
										ftemp1 = ftemp;
										diff1 = diff2;
									}
								}
							}
			                               	if(vertex[i].jj[4]<nneigh)
	                      		          	{
	                      		                 	vertex[i].jj[4]++;
	                       		                 	vertex[i].neighbour[vertex[i].jj[0]+vertex[i].jj[1]+vertex[i].jj[2]+vertex[i].jj[3]+vertex[i].jj[4]+vertex[i].jj[5]+vertex[i].jj[6]+vertex[i].jj[7]] = ftemp1;
								vertex[i].neighbour_lt[vertex[i].jj[4]] = ftemp1;
	                        		       	}	
						}
						
						if(diffy == diffmin)	// on -ve x axis
						{
							kk = 0;
							for(k=1;k<=(vertex[i].jj[0]+vertex[i].jj[1]+vertex[i].jj[2]+vertex[i].jj[3]+vertex[i].jj[4]+vertex[i].jj[5]+vertex[i].jj[6]+vertex[i].jj[7]);k++)
							{
								diffx2 = gridx[vertex[i].neighbour[k]-1]-gridx[i-1];
								diffy2 = gridy[vertex[i].neighbour[k]-1]-gridy[i-1];
								diff2 = sqrt(diffx2*diffx2+diffy2*diffy2);
	
								if((diffx2 == diffmin) && (diffy2 > diffmin))
								{	
									kk++;
									if(diff2>diff1)
									{
										ftemp = vertex[i].neighbour[k];
										vertex[i].neighbour[k] = ftemp1;
										vertex[i].neighbour_l[kk] = ftemp1;
										ftemp1 = ftemp;
										diff1 = diff2;
									}
								}
							}
			                               	if(vertex[i].jj[0]<nneigh)
	                      		          	{
	                      		                 	vertex[i].jj[0]++;
	                       		                 	vertex[i].neighbour[vertex[i].jj[0]+vertex[i].jj[1]+vertex[i].jj[2]+vertex[i].jj[3]+vertex[i].jj[4]+vertex[i].jj[5]+vertex[i].jj[6]+vertex[i].jj[7]] = ftemp1;
								vertex[i].neighbour_l[vertex[i].jj[0]] = ftemp1;
	                        		       	}				

						}

					}

				  	if(diffx > diffmin)
                                  	{	
						if(diffy < diffmin)		// IV quad
                             			{	
							kk = 0;
							for(k=1;k<=(vertex[i].jj[0]+vertex[i].jj[1]+vertex[i].jj[2]+vertex[i].jj[3]+vertex[i].jj[4]+vertex[i].jj[5]+vertex[i].jj[6]+vertex[i].jj[7]);k++)
							{
								diffx2 = gridx[vertex[i].neighbour[k]-1]-gridx[i-1];
								diffy2 = gridy[vertex[i].neighbour[k]-1]-gridy[i-1];
								diff2 = sqrt(diffx2*diffx2+diffy2*diffy2);
	
								if((diffx2 > diffmin) && (diffy2 < diffmin))
								{	
									kk++;
									if(diff2>diff1)
									{
										ftemp = vertex[i].neighbour[k];
										vertex[i].neighbour[k] = ftemp1;
										vertex[i].neighbour_rb[kk] = ftemp1;
										ftemp1 = ftemp;
										diff1 = diff2;
									}
								}
							}
			                               	if(vertex[i].jj[7]<nneigh)
	                      		          	{
	                      		                 	vertex[i].jj[7]++;
	                       		                 	vertex[i].neighbour[vertex[i].jj[0]+vertex[i].jj[1]+vertex[i].jj[2]+vertex[i].jj[3]+vertex[i].jj[4]+vertex[i].jj[5]+vertex[i].jj[6]+vertex[i].jj[7]] = ftemp1;
								vertex[i].neighbour_rb[vertex[i].jj[7]] = ftemp1;
	                        		       	}	
						}

						if(diffy > diffmin)	// I quad
	                         	        {	
							kk = 0;
							for(k=1;k<=(vertex[i].jj[0]+vertex[i].jj[1]+vertex[i].jj[2]+vertex[i].jj[3]+vertex[i].jj[4]+vertex[i].jj[5]+vertex[i].jj[6]+vertex[i].jj[7]);k++)
							{
								diffx2 = gridx[vertex[i].neighbour[k]-1]-gridx[i-1];
								diffy2 = gridy[vertex[i].neighbour[k]-1]-gridy[i-1];
								diff2 = sqrt(diffx2*diffx2+diffy2*diffy2);
	
								if((diffx2 > diffmin) && (diffy2 > diffmin))
								{	
									kk++;
									if(diff2>diff1)
									{
										ftemp = vertex[i].neighbour[k];
										vertex[i].neighbour[k] = ftemp1;
										vertex[i].neighbour_rt[kk] = ftemp1;
										ftemp1 = ftemp;
										diff1 = diff2;
									}
								}
							}
			                               	if(vertex[i].jj[6]<nneigh)
	                      		          	{
	                      		                 	vertex[i].jj[6]++;
	                       		                 	vertex[i].neighbour[vertex[i].jj[0]+vertex[i].jj[1]+vertex[i].jj[2]+vertex[i].jj[3]+vertex[i].jj[4]+vertex[i].jj[5]+vertex[i].jj[6]+vertex[i].jj[7]] = ftemp1;
								vertex[i].neighbour_rt[vertex[i].jj[6]] = ftemp1;
	                        		       	}	
						}
						
						if(diffy == diffmin)	// on +ve x axis
						{
							kk = 0;
							for(k=1;k<=(vertex[i].jj[0]+vertex[i].jj[1]+vertex[i].jj[2]+vertex[i].jj[3]+vertex[i].jj[4]+vertex[i].jj[5]+vertex[i].jj[6]+vertex[i].jj[7]);k++)
							{
								diffx2 = gridx[vertex[i].neighbour[k]-1]-gridx[i-1];
								diffy2 = gridy[vertex[i].neighbour[k]-1]-gridy[i-1];
								diff2 = sqrt(diffx2*diffx2+diffy2*diffy2);
	
								if((diffx2 == diffmin) && (diffy2 > diffmin))
								{	
									kk++;
									if(diff2>diff1)
									{
										ftemp = vertex[i].neighbour[k];
										vertex[i].neighbour[k] = ftemp1;
										vertex[i].neighbour_r[kk] = ftemp1;
										ftemp1 = ftemp;
										diff1 = diff2;
									}
								}
							}
			                               	if(vertex[i].jj[1]<nneigh)
	                      		          	{
	                      		                 	vertex[i].jj[1]++;
	                       		                 	vertex[i].neighbour[vertex[i].jj[0]+vertex[i].jj[1]+vertex[i].jj[2]+vertex[i].jj[3]+vertex[i].jj[4]+vertex[i].jj[5]+vertex[i].jj[6]+vertex[i].jj[7]] = ftemp1;
								vertex[i].neighbour_r[vertex[i].jj[1]] = ftemp1;
	                        		       	}					

						}
					}
				}
			}	
		}
		vertex[i].no_neigh = vertex[i].jj[0]+vertex[i].jj[1]+vertex[i].jj[2]+vertex[i].jj[3]+vertex[i].jj[4]+vertex[i].jj[5]+vertex[i].jj[6]+vertex[i].jj[7];
		printf("vertex[%d].no.neigh = %d \n", i, vertex[i].no_neigh);
		
	}
	
	
	printf("\n readcgnsdata_meshmove done \n");

}
	
















