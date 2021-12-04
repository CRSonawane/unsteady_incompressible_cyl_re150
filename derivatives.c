#include "definitions.h"

void derivatives()
{
	int i, j, cell1, cell2, cell3, cell4;

	int left, right;

	double dx1, dx2, dx3, dx4, dy1, dy2, dy3, dy4, w1, w2, w3, w4, a11, a12, a22, det, b1, b2, du1, du2, du3, du4, du1_o, du2_o, du3_o, du4_o;

	double edge_center_x, edge_center_y, deltax_left, deltay_left, deltax_right, deltay_right;

	double antidiff, limit;

	for (i = 1; i <= no_cell; i++)
	{

		cell1 = cell[i].adj_cell[0];

		cell2 = cell[i].adj_cell[1];

		cell3 = cell[i].adj_cell[2];

		cell4 = cell[i].adj_cell[3];



		dx1 = cell[cell1].xc - cell[i].xc;		dy1 = cell[cell1].yc - cell[i].yc;

		dx2 = cell[cell2].xc - cell[i].xc;		dy2 = cell[cell2].yc - cell[i].yc;

		dx3 = cell[cell3].xc - cell[i].xc;		dy3 = cell[cell3].yc - cell[i].yc;

		dx4 = cell[cell4].xc - cell[i].xc;		dy4 = cell[cell4].yc - cell[i].yc;


		for (j = 0; j <= 3; j++)
		{
			du1 = cell[cell1].u[j] - cell[i].u[j];

			du2 = cell[cell2].u[j] - cell[i].u[j];

			du3 = cell[cell3].u[j] - cell[i].u[j];

			du4 = cell[cell4].u[j] - cell[i].u[j];

			w1 = 1;

			w2 = 1;

			w3 = 1;

			w4 = 1;



			a11 = w1 * dx1 * dx1 + w2 * dx2 * dx2 + w3 * dx3 * dx3 + w4 * dx4 * dx4;

			a12 = w1 * dx1 * dy1 + w2 * dx2 * dy2 + w3 * dx3 * dy3 + w4 * dx4 * dy4;

			a22 = w1 * dy1 * dy1 + w2 * dy2 * dy2 + w3 * dy3 * dy3 + w4 * dy4 * dy4;

			det = a11 * a22 - a12 * a12;

			b1 = w1 * dx1 * du1 + w2 * dx2 * du2 + w3 * dx3 * du3 + w4 * dx4 * du4;

			b2 = w1 * dy1 * du1 + w2 * dy2 * du2 + w3 * dy3 * du3 + w4 * dy4 * du4;


			cell[i].deriv_x[j] = (a22 * b1 - a12 * b2) / (det + del);

			cell[i].deriv_y[j] = (a11 * b2 - a12 * b1) / (det + del);



		}


	}

	for (i = no_cell + 1; i <= no_cell + no_boundaryedges; i++)
	{
		for (j = 0; j <= 3; j++)
		{


			cell[i].deriv_x[j] = 0;

			cell[i].deriv_y[j] = 0;
		}
	}

	/*------------------------------------------------------------------------------------------
	--------------------------------------------------------------------------------------------
	--------------------------------------------------------------------------------------------
	/*------------------------------------------------------------------------------------------*/


	for (i = 1; i <= no_edge; i++)
	{

		left = edge[i].adjacent_cell[0];

		right = edge[i].adjacent_cell[1];


		edge_center_x = edge[i].cx;

		edge_center_y = edge[i].cy;

		deltax_left = edge_center_x - cell[left].xc;

		deltay_left = edge_center_y - cell[left].yc;

		deltax_right = edge_center_x - cell[right].xc;

		deltay_right = edge_center_y - cell[right].yc;


		for (j = 0; j <= 3; j++)
		{
			antidiff = cell[left].deriv_x[j] * deltax_left + cell[left].deriv_y[j] * deltay_left;
			if (antidiff == 0)
			{
				limit = 1;
			}
			else
			{
				limit = limiter(antidiff, left, j);
			}

			if (limit < cell[left].limiter[j])
			{
				cell[left].limiter[j] = limit;
			}

			antidiff = cell[right].deriv_x[j] * deltax_right + cell[right].deriv_y[j] * deltay_right;
			if (antidiff == 0)
			{
				limit = 1;
			}
			else
			{
				limit = limiter(antidiff, right, j);
			}
			if (limit < cell[right].limiter[j])
			{
				cell[right].limiter[j] = limit;
			}
		}

	}



}





