#include "definitions.h"


void readcgnsdata()
{
	int file_index, no_base, no_zones, zone_size[3][3], no_vertices, vertex_min, nsections;

	int element_min, element_max, nbndry, parent_flag, iparentdata;

	//	int *elementdata_top,*elementdata_bottom,*elementdata_side;
//	int* elementdata_inlet, * elementdata_outlet, * elementdata_topside, * elementdata_bottomside;
//	int* elementdata_cyltopleft, * elementdata_cyltopright, * elementdata_cylbotleft, * elementdata_cylbotright;


	int ncells, temp, count, addedge;

	int i, j, k, junk, cell1, cell2;

	int no_present_edges, no_present_cells, newedge[4][2];
	//int no_top_edges,no_bottom_edges,no_side_edges;
	int no_inlet_edges, no_outlet_edges, no_cyltopleft_edges, no_cyltopright_edges, no_cylbotleft_edges, no_cylbotright_edges, no_topside_edges, no_bottomside_edges;

	int v1, v2, left, right;

	double x1, x2, y1, y2, x3, y3, x4, y4;

	double dx, dy, L, temp1;

	char zone_name[25], coordname1[25], coordname2[25], elementsection_name[25];

	DataType_t datatype1, datatype2;

	ElementType_t element_type;

	cg_open("grid.cgns", CG_MODE_READ, &file_index);

	cg_nbases(file_index, &no_base);

	cg_nzones(file_index, no_base, &no_zones);

	cg_zone_read(file_index, no_base, no_zones, zone_name, zone_size[0]);/*gets number of vertex and cells*/

	printf("number of vertices:%d \n", zone_size[0][0]);

	printf("number of cells:%d \n", zone_size[0][1]);

	cg_coord_info(file_index, no_base, no_zones, 1, &datatype1, coordname1);

	cg_coord_info(file_index, no_base, no_zones, 2, &datatype2, coordname2);

	vertex_min = 1;

	vertex_max = zone_size[0][0];
	no_point = vertex_max;
	no_cell = zone_size[0][1];

	gridx = malloc(vertex_max * sizeof(double));

	gridy = malloc(vertex_max * sizeof(double));

	cg_coord_read(file_index, no_base, no_zones, coordname1, RealDouble, &vertex_min, &vertex_max, gridx);

	cg_coord_read(file_index, no_base, no_zones, coordname2, RealDouble, &vertex_min, &vertex_max, gridy);

	cg_nsections(file_index, no_base, no_zones, &nsections);

	printf("Total no of sections are:%d\n", nsections);

	for (i = 1; i <= nsections; i++)
	{
		cg_section_read(file_index, no_base, no_zones, i, elementsection_name, &element_type, &element_min, &element_max, &nbndry, &parent_flag);

		if (strcmp(elementsection_name, "fluid") == 0)
		{
			ncells = element_max - element_min + 1;

			no_cell = ncells;

			elementdata_fluid = malloc(ncells * 4 * sizeof(int));

			cg_elements_read(file_index, no_base, no_zones, i, elementdata_fluid, &iparentdata);
		}


		if (strcmp(elementsection_name, "inlet") == 0)
		{
			ncells = element_max - element_min + 1;

			no_inlet_edges = ncells;

			printf("Total no of inlet edges are:%d\n", no_inlet_edges);

			elementdata_inlet = malloc(ncells * 2 * sizeof(int));

			cg_elements_read(file_index, no_base, no_zones, i, elementdata_inlet, &iparentdata);

		}

		if (strcmp(elementsection_name, "outlet") == 0)
		{
			ncells = element_max - element_min + 1;

			no_outlet_edges = ncells;

			printf("Total no of outlet edges are:%d\n", no_outlet_edges);

			elementdata_outlet = malloc(ncells * 2 * sizeof(int));

			cg_elements_read(file_index, no_base, no_zones, i, elementdata_outlet, &iparentdata);

		}

		if (strcmp(elementsection_name, "cyltopleft") == 0)
		{
			ncells = element_max - element_min + 1;

			no_cyltopleft_edges = ncells;

			printf("Total no of cyltopleft edges are:%d\n", no_cyltopleft_edges);

			elementdata_cyltopleft = malloc(ncells * 2 * sizeof(int));

			cg_elements_read(file_index, no_base, no_zones, i, elementdata_cyltopleft, &iparentdata);

		}


		if (strcmp(elementsection_name, "cyltopright") == 0)
		{
			ncells = element_max - element_min + 1;

			no_cyltopright_edges = ncells;

			printf("Total no of cyl_top_right edges are:%d\n", no_cyltopright_edges);

			elementdata_cyltopright = malloc(ncells * 2 * sizeof(int));

			cg_elements_read(file_index, no_base, no_zones, i, elementdata_cyltopright, &iparentdata);
		}

		if (strcmp(elementsection_name, "cylbotleft") == 0)
		{
			ncells = element_max - element_min + 1;

			no_cylbotleft_edges = ncells;

			printf("Total no of cyl_bot_left edges are:%d\n", no_cylbotleft_edges);

			elementdata_cylbotleft = malloc(ncells * 2 * sizeof(int));

			cg_elements_read(file_index, no_base, no_zones, i, elementdata_cylbotleft, &iparentdata);

		}


		if (strcmp(elementsection_name, "cylbotright") == 0)
		{
			ncells = element_max - element_min + 1;

			no_cylbotright_edges = ncells;

			printf("Total no of cyl_bot_right edges are:%d\n", no_cylbotright_edges);

			elementdata_cylbotright = malloc(ncells * 2 * sizeof(int));

			cg_elements_read(file_index, no_base, no_zones, i, elementdata_cylbotright, &iparentdata);
		}

		if (strcmp(elementsection_name, "topside") == 0)
		{
			ncells = element_max - element_min + 1;

			no_topside_edges = ncells;

			printf("Total no of top edges are:%d\n", no_topside_edges);

			elementdata_topside = malloc(ncells * 2 * sizeof(int));

			cg_elements_read(file_index, no_base, no_zones, i, elementdata_topside, &iparentdata);

		}

		if (strcmp(elementsection_name, "bottomside") == 0)
		{
			ncells = element_max - element_min + 1;

			no_bottomside_edges = ncells;

			printf("Total no of bottom edges are:%d\n", no_bottomside_edges);

			elementdata_bottomside = malloc(ncells * 2 * sizeof(int));

			cg_elements_read(file_index, no_base, no_zones, i, elementdata_bottomside, &iparentdata);

		}
	}


	cg_close(file_index);






	/*Find the number of edges from the formula*/


	no_edge = no_cell + vertex_max + 1;


	/*-----------------------------------------*/

	/*Allocate memory and initlise the data structures*/


	no_boundaryedges = no_inlet_edges + no_outlet_edges + no_cyltopleft_edges + no_cyltopright_edges + no_cylbotleft_edges + no_cylbotright_edges + no_topside_edges + no_bottomside_edges;

	edge = (struct edge_data*)malloc((no_edge + 1) * sizeof(struct edge_data));

	vertex = (struct vertex_data*)malloc((vertex_max + 1) * sizeof(struct vertex_data));

	cell = (struct cell_data*)malloc((no_cell + no_boundaryedges + 1) * sizeof(struct cell_data));


	/*-------------------------------------------------*/


	/*Initilse valules for cells and edges*/

	for (i = 1; i <= no_cell + no_boundaryedges; i++)
	{
		for (j = 0; j <= 3; j++)
		{
			cell[i].netflux[j] = 0;

			cell[i].limiter[j] = 1.0;

		}

		cell[i].no_adj_cell = 0;

	}

	for (i = 1; i <= no_edge; i++)
	{
		edge[i].no_adjacent_cell = 0;

		edge[i].bc_type = 0;
	}

	/*-----------------------------------*/

	no_present_edges = 0;
	temp = 0;
	for (i = 1; i <= no_cell; i++)
	{

		newedge[0][0] = elementdata_fluid[temp];
		newedge[0][1] = elementdata_fluid[temp + 1];
		newedge[1][0] = elementdata_fluid[temp + 1];
		newedge[1][1] = elementdata_fluid[temp + 2];
		newedge[2][0] = elementdata_fluid[temp + 2];
		newedge[2][1] = elementdata_fluid[temp + 3];
		newedge[3][0] = elementdata_fluid[temp + 3];
		newedge[3][1] = elementdata_fluid[temp];


		count = 0; /*no new edges added in this loop*/

		for (j = 0; j <= 3; j++)
		{
			addedge = 1;

			/* Loop to check if the edge is already present in the edge list
			if present addedge variable is set to 0*/

			for (k = 1; k <= no_present_edges; k++)
			{
				if (newedge[j][0] == edge[k].node[0] || newedge[j][0] == edge[k].node[1])
				{
					if (newedge[j][1] == edge[k].node[0] || newedge[j][1] == edge[k].node[1])
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

			if (addedge == 1)
			{
				count++;

				edge[no_present_edges + count].node[0] = newedge[j][0];

				edge[no_present_edges + count].node[1] = newedge[j][1];

				edge[no_present_edges + count].adjacent_cell[0] = i;

				edge[no_present_edges + count].no_adjacent_cell++;

			}

			/*-----------------------------------------------------------------*/


		}
		temp = temp + 4;

		no_present_edges = no_present_edges + count;

	}



	/*--------***---------End Create Faces-----------***--------*/


	no_present_cells = no_cell;


	/*--------------------Find the boundary Edges--------------------*/

	for (i = 1; i <= no_edge; i++)
	{

		/*Loop for testing weather the edge is a inlet edge*/

		for (j = 1; j <= no_inlet_edges; j++)
		{
			temp = (j - 1) * 2;

			if (edge[i].node[0] == elementdata_inlet[temp] || edge[i].node[1] == elementdata_inlet[temp])
			{
				if (edge[i].node[0] == elementdata_inlet[temp + 1] || edge[i].node[1] == elementdata_inlet[temp + 1])
				{
					edge[i].bc_type = 1;

					edge[i].adjacent_cell[edge[i].no_adjacent_cell] = no_present_cells + 1;

					edge[i].no_adjacent_cell++;

					no_present_cells++;

				}
			}
		}

		for (j = 1; j <= no_outlet_edges; j++)
		{
			temp = (j - 1) * 2;

			if (edge[i].node[0] == elementdata_outlet[temp] || edge[i].node[1] == elementdata_outlet[temp])
			{
				if (edge[i].node[0] == elementdata_outlet[temp + 1] || edge[i].node[1] == elementdata_outlet[temp + 1])
				{
					edge[i].bc_type = 2;

					edge[i].adjacent_cell[edge[i].no_adjacent_cell] = no_present_cells + 1;

					edge[i].no_adjacent_cell++;

					no_present_cells++;

				}
			}
		}

		for (j = 1; j <= no_cyltopleft_edges; j++)
		{
			temp = (j - 1) * 2;

			if (edge[i].node[0] == elementdata_cyltopleft[temp] || edge[i].node[1] == elementdata_cyltopleft[temp])
			{
				if (edge[i].node[0] == elementdata_cyltopleft[temp + 1] || edge[i].node[1] == elementdata_cyltopleft[temp + 1])
				{
					edge[i].bc_type = 3;

					edge[i].adjacent_cell[edge[i].no_adjacent_cell] = no_present_cells + 1;

					edge[i].no_adjacent_cell++;

					no_present_cells++;

				}
			}
		}

		for (j = 1; j <= no_cyltopright_edges; j++)
		{
			temp = (j - 1) * 2;

			if (edge[i].node[0] == elementdata_cyltopright[temp] || edge[i].node[1] == elementdata_cyltopright[temp])
			{
				if (edge[i].node[0] == elementdata_cyltopright[temp + 1] || edge[i].node[1] == elementdata_cyltopright[temp + 1])
				{
					edge[i].bc_type = 4;

					edge[i].adjacent_cell[edge[i].no_adjacent_cell] = no_present_cells + 1;

					edge[i].no_adjacent_cell++;

					no_present_cells++;

				}
			}
		}

		for (j = 1; j <= no_cylbotleft_edges; j++)
		{
			temp = (j - 1) * 2;

			if (edge[i].node[0] == elementdata_cylbotleft[temp] || edge[i].node[1] == elementdata_cylbotleft[temp])
			{
				if (edge[i].node[0] == elementdata_cylbotleft[temp + 1] || edge[i].node[1] == elementdata_cylbotleft[temp + 1])
				{
					edge[i].bc_type = 5;

					edge[i].adjacent_cell[edge[i].no_adjacent_cell] = no_present_cells + 1;

					edge[i].no_adjacent_cell++;

					no_present_cells++;

				}
			}
		}


		for (j = 1; j <= no_cylbotright_edges; j++)
		{
			temp = (j - 1) * 2;

			if (edge[i].node[0] == elementdata_cylbotright[temp] || edge[i].node[1] == elementdata_cylbotright[temp])
			{
				if (edge[i].node[0] == elementdata_cylbotright[temp + 1] || edge[i].node[1] == elementdata_cylbotright[temp + 1])
				{
					edge[i].bc_type = 6;

					edge[i].adjacent_cell[edge[i].no_adjacent_cell] = no_present_cells + 1;

					edge[i].no_adjacent_cell++;

					no_present_cells++;

				}
			}
		}

		for (j = 1; j <= no_topside_edges; j++)
		{
			temp = (j - 1) * 2;

			if (edge[i].node[0] == elementdata_topside[temp] || edge[i].node[1] == elementdata_topside[temp])
			{
				if (edge[i].node[0] == elementdata_topside[temp + 1] || edge[i].node[1] == elementdata_topside[temp + 1])
				{
					edge[i].bc_type = 7;

					edge[i].adjacent_cell[edge[i].no_adjacent_cell] = no_present_cells + 1;

					edge[i].no_adjacent_cell++;

					no_present_cells++;

				}
			}
		}


		for (j = 1; j <= no_bottomside_edges; j++)
		{
			temp = (j - 1) * 2;

			if (edge[i].node[0] == elementdata_bottomside[temp] || edge[i].node[1] == elementdata_bottomside[temp])
			{
				if (edge[i].node[0] == elementdata_bottomside[temp + 1] || edge[i].node[1] == elementdata_bottomside[temp + 1])
				{
					edge[i].bc_type = 8;

					edge[i].adjacent_cell[edge[i].no_adjacent_cell] = no_present_cells + 1;

					edge[i].no_adjacent_cell++;

					no_present_cells++;

				}
			}
		}


	}



	/*for(i=1;i<=no_edge;i++)
	{
		printf("%d \t %d \t %d\n",i,edge[i].node[0],edge[i].node[1]);
}*/

//number the cells
	for (i = 1; i <= no_present_cells; i++)
	{
		cell[i].no = i;
	}

	temp = 0;
	for (i = 1; i <= no_cell; i++)
	{
		/*Find Area*/
		x1 = gridx[elementdata_fluid[temp] - 1];
		x2 = gridx[elementdata_fluid[temp + 1] - 1];
		x3 = gridx[elementdata_fluid[temp + 2] - 1];
		x4 = gridx[elementdata_fluid[temp + 3] - 1];


		y1 = gridy[elementdata_fluid[temp] - 1];
		y2 = gridy[elementdata_fluid[temp + 1] - 1];
		y3 = gridy[elementdata_fluid[temp + 2] - 1];
		y4 = gridy[elementdata_fluid[temp + 3] - 1];


		cell[i].area = 0.5 * fabs(((x2 - x4) * (y3 - y1)) - ((x3 - x1) * (y2 - y4)));

		/*End Find Area*/
	//printf("%d\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n",i,x1,x2,x3,x4,y1,y2,y3,y4);


		/*Find Centroid*/
		cell[i].xc = (x1 + x2 + x3 + x4) / 4.0;

		cell[i].yc = (y1 + y2 + y3 + y4) / 4.0;

		temp = temp + 4;
		/*End Find Centroid*/

	}

	for (i = 1; i <= no_edge; i++)
	{
		cell1 = edge[i].adjacent_cell[0];

		cell2 = edge[i].adjacent_cell[1];

		cell[cell1].adj_cell[cell[cell1].no_adj_cell] = cell2;

		cell[cell1].no_adj_cell++;

		cell[cell2].adj_cell[cell[cell2].no_adj_cell] = cell1;

		cell[cell2].no_adj_cell++;
	}

	for (i = 1; i <= no_edge; i++)
	{
		if (edge[i].bc_type != 0)
		{
			cell[edge[i].adjacent_cell[1]].xc = (gridx[edge[i].node[0] - 1] + gridx[edge[i].node[1] - 1]) - cell[edge[i].adjacent_cell[0]].xc;

			cell[edge[i].adjacent_cell[1]].yc = (gridy[edge[i].node[0] - 1] + gridy[edge[i].node[1] - 1]) - cell[edge[i].adjacent_cell[0]].yc;
		}

	}

	//find normal			
	for (i = 1; i <= no_edge; i++)
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

		edge[i].nx = dy / L;

		edge[i].ny = -dx / L;

		temp1 = (cell[left].xc - x1) * edge[i].nx + (cell[left].yc - y1) * edge[i].ny;

		if (temp1 > 0)
		{
			edge[i].nx = -edge[i].nx;

			edge[i].ny = -edge[i].ny;

		}

		/*--------*****------------*****----------*****----------*/


		edge[i].cx = (x1 + x2) / 2;

		edge[i].cy = (y1 + y2) / 2;

		edge[i].L = L;

	}
	for (i = 1; i <= no_point; i++)
	{
		vertex[i].no_node_cell = 0;
		for (j = 0; j < 15; j++)
		{
			vertex[i].cell[j] = 0;
		}
		for (j = 0; j <= 3; j++)
		{
			vertex[i].un[j] = 0.0;
		}
	}
	temp = 0;
	for (i = 1; i <= no_cell; i++)
	{
		vertex[elementdata_fluid[temp]].cell[vertex[elementdata_fluid[temp]].no_node_cell] = i;
		vertex[elementdata_fluid[temp]].no_node_cell++;

		vertex[elementdata_fluid[temp + 1]].cell[vertex[elementdata_fluid[temp + 1]].no_node_cell] = i;
		vertex[elementdata_fluid[temp + 1]].no_node_cell++;

		vertex[elementdata_fluid[temp + 2]].cell[vertex[elementdata_fluid[temp + 2]].no_node_cell] = i;
		vertex[elementdata_fluid[temp + 2]].no_node_cell++;

		vertex[elementdata_fluid[temp + 3]].cell[vertex[elementdata_fluid[temp + 3]].no_node_cell] = i;
		vertex[elementdata_fluid[temp + 3]].no_node_cell++;

		temp = temp + 4;

	}

	printf("\n readcgnsdata done \n");
}
