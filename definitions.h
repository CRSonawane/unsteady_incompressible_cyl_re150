/*Edge numbering starts from 1
  Cell numbering starts from 1
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "cgnslib.h"
#include <string.h>

/*---------------------Define initial connditions here-------------------------------*/

#define u_initial	1.0
#define v_initial	0.0
#define p_initial	0.0                       //101325.0
#define T_initial       0.0                       //101325.0
#define Twall           1.0


//double viscosity;             
#define Re              150                     //Re = rho v D /mu = 150
#define Pr              0.7                    //Prandtl number
//#define Ri              0.0                 //Richardson no Ri = Gr/Re^2

#define density		1.0
#define viscosity 	0.006667		//re = 200
#define gbdt            0.0

#define mr              2.0             //mc ---> old way mass ratio:  mr = mc/(D^2 *rhof) --> mr = m*4/pi
#define fny             0.25        //natural frequency in y direction --fny = 1/Ur = 1/4
#define damp_ratio      0.0                       // damping ratio
/*--------------------------------------------------------------------------------*/

/*To prevent division by zero*/
#define del 	10.0e-12
#define TINY 	1.0e-20 
#define cfl 	0.499
#define pi	3.141593


double *gridx,*gridy,*gridx_1,*gridy_1,*gridx_2,*gridy_2,  *gridx_new,*gridy_new;

double beta,st_coeff,rdt,rss_t;

double  *up2_p, *up2_u, *up2_v,*up2_T,*up1_p, *up1_u, *up1_v, *up1_T, *area1, *area2, *dxp, *dyp, *nxp, *nyp, *Lp, *cxp, *cyp;

int  *elementdata_fluid;//,*elementdata_inout,*elementdata_topwall,*elementdata_botwall;

int *elementdata_inlet,*elementdata_outlet,*elementdata_topside,*elementdata_bottomside;
int *elementdata_cyltopleft, *elementdata_cyltopright, *elementdata_cylbotleft, *elementdata_cylbotright;

int element_fluid_max, element_fluid_min;
int element_inlet_max, element_inlet_min, element_outlet_max, element_outlet_min, element_topside_max, element_topside_min, element_bottomside_max, element_bottomside_min;
int element_cyltopleft_max, element_cyltopleft_min, element_cyltopright_max, element_cyltopright_min, element_cylbotleft_max, element_cylbotleft_min, element_cylbotright_max, element_cylbotright_min; 

int no_point,no_edge, no_cell, vertex_max,no_boundaryedges, no_node;

int iter,rtstep;

double drag_T, lift_T, Nu,Nu_avg,len;

double A_viv, B_viv;
  
double disp_viv, ds_viv, vel_viv, acc_viv;
  
double disp_viv_old, vel_viv_old, acc_viv_old;

struct vertex_data
{
	//int no,no_cells,*cell_list, bc_type;
	int no, no_node_cell, cell[15], bc_type;
	
	//int no_adjacent_edge,adjacent_edge[40];
	
	double xt, yt;
	
	double un[6],vort,area_avg;
}*vertex;

struct edge_data
{
	int no,no_adjacent_cell,adjacent_cell[2],bc_type,node[2];
	
	double nx,ny,cx,cy,L,delta_s, visflux[6];
		
	double xt, yt,dv;
	
	double deriv_x[6],deriv_y[6],u[6];

	double cp,sf,nusselt;

	double cos, sin, theta;
}*edge;


struct cell_data
{
	int no,no_adj_cell,adj_cell[12];
	
	//int *node_neigbs, no_node_cells,node_bc;	
	
	//double *node_neigbs_old, no_node_cells_old;
	
	double area,area1,area2,xc,yc;
	
	int edge[6], no_edge; 	double beta;
	
	double u[6],u_temp[6],netflux[6],up1[6],up2[6],rtd[6], dv;
	
	double deltat,deltatinv,deltatvis,sum1,sum2;
	
	//double derivatives[6][5], derivatives_p[6][5], vort;
	double limiter[6], deriv_x[6], deriv_y[6], vort;
	
}*cell;

void readcgnsdata();

void extra_memory();

void initlize();

void output();

void readcgnsdata_1();

void nodal_velo();

void transfer();

void initlize_1();	

int face_vol_increment();

void accuracy_1();

void boundary_conditions();

void time_step();

void visc_flux();

void RUNGK(double);

void derivatives();

void conv_flux();

void rtd();

void update(double);

double  convergence();

void output_tecplot();

void cl_cd();

void VIV();

double limiter(double, int, int);


//void rbf();

//double lubksb();

//double ludcmp();

//void output_meshmove();

