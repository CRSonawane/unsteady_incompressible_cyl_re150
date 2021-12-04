/*Edge numbering starts from 1
  Cell numbering starts from 1
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "cgnslib.h"
#include <string.h>


/*To prevent division by zero*/
#define del 	10.0e-12
#define TINY 	1.0e-20 
#define pi	3.141593
int step;


double *gridx,*gridy,*gridx_new,*gridy_new, *gridx_temp, *gridy_temp;

double*err_x, *err_y, *err, *gridx_act,*gridy_act;

int  *elementdata_fluid;//,*elementdata_wall

int element_fluid_max, element_fluid_min, *elementdata_inlet,*elementdata_outlet,*elementdata_topside,*elementdata_bottomside, *elementdata_cyltopleft, *elementdata_cyltopright, *elementdata_cylbotleft, *elementdata_cylbotright;

int no_point,no_cell,node_max,no_side,no_boundarysides,ij1,ij2,ij3,ij4,ji;

int boundary_node[2000];	int no_boundary_node;

double M[2000][2000], P[2000][2000], PT[2000][2000], R[2000][2000];
double t,cyl_movement;
/*------------LU decomposition -------------------*/
double A[2000][2000], b[2000], BOUN[2000];		double c[2000], col[2000], vv[2000];
int indx[2000];
double dx1[2000],dy1[2000],df1[36],FI[5][36],F0[5][36],dFI[5][36];
/*------------------------------------------------------------------------*/

double alpha_x[2000], alpha_y[2000];

double deltat,diff,diffmin;

struct side_data
{
	int no_adjacent_cell,adjacent_cell[2],bc_type,point[2];
	
	double nx,ny,cx,cy,L;
	/* variables to be initialized
	
	   no_adjacent_cell = 0
	   bc_type          = 0
	
	*/


}*side;

struct node_data
{
	int no_adjacent_node,no_adjacent_side,adjacent_side[40],bc_type,no,neighbourlb[9],neighbourlt[9],neighbourrb[9],neighbourrt[9],neighbour[36],no_neigh,jj[4];
	
	double u[6], K[15], sigmaK, dx, dy;

	//double deriv_x[4],deriv_y[4];
	//double deriv_Gx_plus_y[4],deriv_Gx_minus_y[4],deriv_Gy_plus_y[4],deriv_Gy_minus_y[4];
//	double deriv_plus_x[4],deriv_plus_y[4],deriv_minus_x[4],deriv_minus_y[4];

}*node;

void readcgnsdata_rbf();

void VIV();

void rbf_trans();

//double LU();

double ludcmp();

double lubksb();




