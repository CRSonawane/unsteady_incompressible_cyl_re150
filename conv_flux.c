#include "definitions.h"

void conv_flux()
{
	int i,j,left,right,v1,v2 ;
	
	double u_l[6],u_r[6],x1,y1,x2,y2,L,dx,dy,nx,ny,temp,temp1,temp2;
	
	double uu1,uu2,uu3,uu4,vv1,vv2,vv3,vv4,dx1,dx2,dx3,dx4,dy1,dy2,dy3,dy4,dy13,dy24,dx13,dx24,areatemp;

	double rhol,rhor,ul,ur,vl,vr,tl,tr,el,er,pl,pr,hl,hr,al,ar,c;
	
	double r,sl,sm,sr,fluxtrans[6],flux[6],u1hllc,u2hllc,u3hllc,u4hllc,ux,uy,vx,vy,visflux[6];
	
	double tempx,mintime,vdotn;
	
	double deltax_left,deltay_left,deltax_right,deltay_right,edge_center_x,edge_center_y;
	
	double rho_temp,u_temp,v_temp,e_temp,p_temp;
	
	double du_dn_left,du_dn_right;

	double limit,antidiff;

	mintime = 10;


	
	
	for(i=1;i<=no_edge;i++)
	{
				
		left = edge[i].adjacent_cell[0];
		
		right = edge[i].adjacent_cell[1];
		
		
		
		L = edge[i].L;
		
		nx = edge[i].nx;
			
		ny = edge[i].ny;
		
		edge_center_x = edge[i].cx;
		
		edge_center_y = edge[i].cy;
		

		
		deltax_left =  edge_center_x - cell[left].xc;
		
		deltay_left =  edge_center_y - cell[left].yc;
		
		deltax_right =  edge_center_x - cell[right].xc;
		
		deltay_right =  edge_center_y - cell[right].yc;

			
		if(edge[i].bc_type == 3 || edge[i].bc_type == 4 || edge[i].bc_type == 5|| edge[i].bc_type == 6)
		{
		      for(j=0;j<=3;j++)
			{
			    u_l[j] = cell[left].u[j];

			    u_r[j] = cell[right].u[j];	
			}
		}
		else
		{	
		    for(j=0;j<=3;j++)
		    {
				u_l[j] = cell[left].u[j] + cell[left].limiter[j] * (cell[left].deriv_x[j] * deltax_left + cell[left].deriv_y[j] * deltay_left);

				u_r[j] = cell[right].u[j] + cell[right].limiter[j] * (cell[right].deriv_x[j] * deltax_right + cell[right].deriv_y[j] * deltay_right);
			}
		}
		
		
		
		
		/*----Transform the variables normal to the edge----*/
		
		pl = u_l[0];							pr = u_r[0];
		
		ul = (nx * u_l[1] + ny * u_l[2]);				ur = (nx * u_r[1] + ny * u_r[2]);
		
		vl = (-ny * u_l[1] + nx * u_l[2]);				vr = (-ny * u_r[1] + nx * u_r[2]);
		
		tl = u_l[3];                                                    tr = u_r[3];
		
		al = sqrt(ul*ul+beta);						ar = sqrt(ur*ur+beta);
		/*--------*****------------*****----------*****----------*/
		if(rtstep==0)
		{
		    if(edge[i].bc_type == 3 || edge[i].bc_type == 4 || edge[i].bc_type == 5|| edge[i].bc_type == 6) //wall
		    {
			ul = 0.0;				ur = 0.0;
		
			vl = 0.0;				vr = 0.0;
			
			tl = Twall;                             tr = Twall;
		  
			al = del;	ar = del;
		    }
		}
		else
		{
		    if(edge[i].bc_type == 3 || edge[i].bc_type == 4 || edge[i].bc_type == 5|| edge[i].bc_type == 6)
		    {
			ul = (nx*edge[i].xt + ny*edge[i].yt);			ur = (nx*edge[i].xt + ny*edge[i].yt);
		
			vl = (-ny*edge[i].xt + nx*edge[i].yt);			vr = (-ny*edge[i].xt + nx*edge[i].yt);
			
			tl = Twall;                                             tr = Twall;
		  
			al = del;	ar = del;
		    }
		}
		
		
		
		/*----solve the riemann problem in transformed variables----*/
		
		/*Step 1: Calculate the averages*/
		
				
		
		temp1 = ul - al;
		
		temp2 = ur - ar;
		
		if(temp1<temp2)
		{
			sl = temp1;
		}
		else
		{
			sl = temp2;
		}
		
		temp1 = ul + al;
		
		temp2 = ur + ar;
		
		if(temp1>temp2)
		{
			sr = temp1;
		}
		else
		{
			sr = temp2;
		}
		
		
		
		sm = (pr - pl +  ul * (sl - ul) - ur * (sr - ur) ) / (sl - sr);

		
		
		/*End Step 1*****------------*****----------*****----------*/

		
		/*Step2:Calculate HLLC Flux based on roe wave speeds----*/
		
		if(sl>=0)
		{
			fluxtrans[0] =  beta*ul;
			
			fluxtrans[1] =  ul * ul + pl;
			
			fluxtrans[2] = ul * vl;
			
			fluxtrans[3] = ul * tl;
			
		
		}
		
		if(sl<0 && sm>0)
		{
			
			
			u1hllc = (sr*pr-sl*pl+beta*(ul-ur))/(sr-sl);
			
			u2hllc = sm;
			
			u3hllc = vl*(sl-ul)/(sl-sm);
			
			u4hllc = tl*(sl-ul)/(sl-sm);
			
			fluxtrans[0] =  (beta*ul)+sl*(u1hllc-pl);
			
			fluxtrans[1] =  (ul * ul + pl) + sl * (u2hllc - ul);
			
			fluxtrans[2] = ul * vl + sl * (u3hllc -  vl);
			
			fluxtrans[3] = ul * tl + sl * (u4hllc -  tl);
			
		}
		
		if(sr>0 && sm<=0)
		{
			
			u1hllc = (sr*pr-sl*pl+beta*(ul-ur))/(sr-sl);
			
			u2hllc = sm;
			
			u3hllc = vr*(sr-ur)/(sr-sm);
			
			u4hllc = tr*(sr-ur)/(sr-sm);
			
			fluxtrans[0] = (beta*ur) + sr * (u1hllc - pr);
			
			fluxtrans[1] = (ur * ur + pr) + sr * (u2hllc -  ur);
			
			fluxtrans[2] = ur * vr + sr * (u3hllc - vr);
			
			fluxtrans[3] = ur * tr + sr * (u4hllc - tr);
			
		}
		
		
		if(sr<=0)
		{
			fluxtrans[0] =  beta*ur;
			
			fluxtrans[1] =  ur * ur + pr;
			
			fluxtrans[2] =  ur * vr;
			
			fluxtrans[3] =  ur * tr;
			
		}
		
		/*End Step2:*****------------*****----------*****----------*/

		/*Step 3:Transform the fluxes----*/
		
		/*flux[0] = fluxtrans[0];
		
		flux[1] = nx * fluxtrans[1] - ny *  fluxtrans[2];
		
		flux[2] = ny * fluxtrans[1] + nx *  fluxtrans[2];*/
		
		if(rtstep ==0)
		{
		    flux[0] = fluxtrans[0]*L;
		
		    flux[1] = (nx*fluxtrans[1] - ny*fluxtrans[2]) * L;
		
		    flux[2] = (ny*fluxtrans[1] + nx*fluxtrans[2]) * L;
		    
		    flux[3] = fluxtrans[3]*L;
		}
		else
		{
		    flux[0] = fluxtrans[0]*L - (beta* edge[i].dv);
		
		    flux[1] = (nx * fluxtrans[1] - ny *  fluxtrans[2])*L -(((u_l[1] + u_r[1])/2.0)*edge[i].dv);
		
		    flux[2] = (ny * fluxtrans[1] + nx *  fluxtrans[2])*L - (((u_l[2] + u_r[2])/2.0)*edge[i].dv);
		    
		    flux[3] = fluxtrans[3]*L - (((u_l[3] + u_r[3])/2.0)*edge[i].dv);
		}
		
				
		/*End Step3:*****------------*****----------*****----------*/
		

		/*Step 5: Add the flux to the left cell and subbtract if from the right cell*/
		
		for(j=0;j<=3;j++)
		{
			cell[left].netflux[j] = cell[left].netflux[j] + (flux[j]-edge[i].visflux[j] * L);
			
			cell[right].netflux[j] = cell[right].netflux[j] - (flux[j]-edge[i].visflux[j]*L);
		}

	}


}

		
		
		
		
		
