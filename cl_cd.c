#include "definitions.h"



void cl_cd()
{

	int i,j,count, rtmstp;
		
	double uu1, uu2, uu3, uu4, vv1, vv2, vv3, vcv3, vv4, tt1,tt2,tt3,tt4;
	
	double dx1, dx2, dx3, dx4, dy1, dy2, dy3, dy4, dy13, dy24, dx13, dx24, areatemp;

	double ux,uy,vx,vy, tx,ty, areatot,theta;
	
	double du_n, du_t, dv_n, dv_t, drag, lift, theta_d, dx,dy;
	
	double cp,p_force,tau_xy,ss_force;
	
	
	boundary_conditions();
	
	rtmstp = rtstep;
	
	
	// find the average flow variable at a vertex		----  Boundary treatment not required 	
	for (i = 1; i <= no_point; i++)
	{
		vertex[i].un[0] = 0.0;
		vertex[i].un[1] = 0.0;
		vertex[i].un[2] = 0.0;
		vertex[i].un[3] = 0.0;

	}

	// area weighted average
	for (i = 1; i <= no_point; i++)
	{
		areatot = 0.0;
		for (j = 0; j < vertex[i].no_node_cell; j++)
		{
			vertex[i].un[0] = vertex[i].un[0] + cell[vertex[i].cell[j]].area * cell[vertex[i].cell[j]].u[0];
			vertex[i].un[1] = vertex[i].un[1] + cell[vertex[i].cell[j]].area * cell[vertex[i].cell[j]].u[1];
			vertex[i].un[2] = vertex[i].un[2] + cell[vertex[i].cell[j]].area * cell[vertex[i].cell[j]].u[2];
			vertex[i].un[3] = vertex[i].un[3] + cell[vertex[i].cell[j]].area * cell[vertex[i].cell[j]].u[3];

			areatot = areatot + cell[vertex[i].cell[j]].area;
		}
		vertex[i].un[0] = vertex[i].un[0] / areatot;
		vertex[i].un[1] = vertex[i].un[1] / areatot;
		vertex[i].un[2] = vertex[i].un[2] / areatot;
		vertex[i].un[3] = vertex[i].un[3] / areatot;
	}

//cp	
	
	FILE *f555;
	f555=fopen("Cp.dat","a");

	for(i=1;i<=no_edge;i++)
	{
	  theta = 0.0;
	  
	 if(edge[i].bc_type == 3 || edge[i].bc_type == 4 )	// top wall
	  {
	    //find Cp
		cp =( ((vertex[edge[i].node[0]].un[0] + vertex[edge[i].node[1]].un[0])/2.0) - p_initial)/0.5;
		
	/*	if(edge[i].cx<=0)
		{
		  theta=180.0/3.1415*asin((edge[i].cy/0.5));
		}
		else
		{
		  theta=180.0-(180.0/3.1415*asin(((gridy[edge[i].node[0]-1]+gridy[edge[i].node[1]-1])/(2.0*0.5))));
		}
	   */ 
		edge[i].cp = cp;
		
	//	fprintf(f555,"%f \t %f \t%d \n",theta, cp,rtstep);
	  }
	 else if(edge[i].bc_type == 5 || edge[i].bc_type == 6 )	// bot wall
	  {
	    //find Cp
		cp =( ((vertex[edge[i].node[0]].un[0] + vertex[edge[i].node[1]].un[0])/2.0) - p_initial)/0.5;
		
	/*	if(edge[i].cx<=0)
		{
		  theta=180.0/3.1415*asin((fabs(edge[i].cy)/0.5));
		}
		else
		{
		  theta=180.0-(180.0/3.1415*asin((fabs((gridy[edge[i].node[0]-1]+gridy[edge[i].node[1]-1]))/(2.0*0.5))));
		}
	    */
		edge[i].cp = cp;
		
	//	fprintf(f555,"%f \t %f \t%d \n",theta, cp,rtstep);
	  }
	}
	
//sf
      FILE *f666;
	f666=fopen("Sf.dat","a");

	for(i=1;i<=no_edge;i++)
	{
	  theta = 0.0;
	  
	  if(edge[i].bc_type == 3 || edge[i].bc_type == 4 )	// top wall
	  {
	    //find shear stress
		
		uu1= 0.5*(vertex[edge[i].node[0]].un[1] + cell[edge[i].adjacent_cell[1]].u[1]);
		uu2= 0.5*(cell[edge[i].adjacent_cell[1]].u[1] + vertex[edge[i].node[1]].un[1]);
		uu3= 0.5*(vertex[edge[i].node[1]].un[1] + cell[edge[i].adjacent_cell[0]].u[1]);
		uu4= 0.5*(cell[edge[i].adjacent_cell[0]].u[1] + vertex[edge[i].node[0]].un[1]);						

		vv1= 0.5*(vertex[edge[i].node[0]].un[2] + cell[edge[i].adjacent_cell[1]].u[2]);
		vv2= 0.5*(cell[edge[i].adjacent_cell[1]].u[2] + vertex[edge[i].node[1]].un[2]);
		vv3= 0.5*(vertex[edge[i].node[1]].un[2] + cell[edge[i].adjacent_cell[0]].u[2]);
		vv4= 0.5*(cell[edge[i].adjacent_cell[0]].u[2] + vertex[edge[i].node[0]].un[2]);	
		
		dy1= cell[edge[i].adjacent_cell[1]].yc-gridy[edge[i].node[0]-1];
		dy2= gridy[edge[i].node[1]-1]-cell[edge[i].adjacent_cell[1]].yc;
		dy3= cell[edge[i].adjacent_cell[0]].yc-gridy[edge[i].node[1]-1];
		dy4= gridy[edge[i].node[0]-1]-cell[edge[i].adjacent_cell[0]].yc;


		dx1= cell[edge[i].adjacent_cell[1]].xc-gridx[edge[i].node[0]-1];
		dx2= gridx[edge[i].node[1]-1]-cell[edge[i].adjacent_cell[1]].xc;
		dx3= cell[edge[i].adjacent_cell[0]].xc-gridx[edge[i].node[1]-1];
		dx4= gridx[edge[i].node[0]-1]-cell[edge[i].adjacent_cell[0]].xc;

		dy24=cell[edge[i].adjacent_cell[0]].yc-cell[edge[i].adjacent_cell[1]].yc;
		dx24=cell[edge[i].adjacent_cell[0]].xc-cell[edge[i].adjacent_cell[1]].xc;

		dy13=gridy[edge[i].node[1]-1]-gridy[edge[i].node[0]-1];
		dx13=gridx[edge[i].node[1]-1]-gridx[edge[i].node[0]-1];

		areatemp=0.5 * fabs((dx24*dy13)-(dx13*dy24));

					
		ux=(uu1*dy1+uu2*dy2+uu3*dy3+uu4*dy4)/areatemp;
		uy=-(uu1*dx1+uu2*dx2+uu3*dx3+uu4*dx4)/areatemp;
		vx=(vv1*dy1+vv2*dy2+vv3*dy3+vv4*dy4)/areatemp;
		vy=-(vv1*dx1+vv2*dx2+vv3*dx3+vv4*dx4)/areatemp;
		
	  //find normal and tangent derivatives
		
		du_n = ux*edge[i].nx + uy*edge[i].ny;
		du_t = -ux*edge[i].ny + uy*edge[i].nx;
				
		dv_n = vx*edge[i].nx + vy*edge[i].ny;
		dv_t = -vx*edge[i].ny + vy*edge[i].nx;
		
				
	//tau_xy = viscosity*(vx - uy);
		tau_xy = viscosity*(dv_t+du_n);
		
	/*	if(edge[i].cx<=0)
		{
		  theta=180.0/3.1415*asin((fabs(edge[i].cy)/0.5));
		}
		else
		{
		 theta=180.0-(180.0/3.1415*asin((fabs((gridy[edge[i].node[0]-1]+gridy[edge[i].node[1]-1]))/(2.0*0.5))));
		}
	    */
		edge[i].sf = tau_xy/0.5;
		
	//	fprintf(f666,"%f \t %f \t%d \n",theta, edge[i].sf,rtstep);
	  }
	 else if(edge[i].bc_type == 5 || edge[i].bc_type == 6 )	// bot wall
	  {
	    //find shear stress
		
		uu1= 0.5*(vertex[edge[i].node[0]].un[1] + cell[edge[i].adjacent_cell[1]].u[1]);
		uu2= 0.5*(cell[edge[i].adjacent_cell[1]].u[1] + vertex[edge[i].node[1]].un[1]);
		uu3= 0.5*(vertex[edge[i].node[1]].un[1] + cell[edge[i].adjacent_cell[0]].u[1]);
		uu4= 0.5*(cell[edge[i].adjacent_cell[0]].u[1] + vertex[edge[i].node[0]].un[1]);						

		vv1= 0.5*(vertex[edge[i].node[0]].un[2] + cell[edge[i].adjacent_cell[1]].u[2]);
		vv2= 0.5*(cell[edge[i].adjacent_cell[1]].u[2] + vertex[edge[i].node[1]].un[2]);
		vv3= 0.5*(vertex[edge[i].node[1]].un[2] + cell[edge[i].adjacent_cell[0]].u[2]);
		vv4= 0.5*(cell[edge[i].adjacent_cell[0]].u[2] + vertex[edge[i].node[0]].un[2]);	
		
		dy1= cell[edge[i].adjacent_cell[1]].yc-gridy[edge[i].node[0]-1];
		dy2= gridy[edge[i].node[1]-1]-cell[edge[i].adjacent_cell[1]].yc;
		dy3= cell[edge[i].adjacent_cell[0]].yc-gridy[edge[i].node[1]-1];
		dy4= gridy[edge[i].node[0]-1]-cell[edge[i].adjacent_cell[0]].yc;


		dx1= cell[edge[i].adjacent_cell[1]].xc-gridx[edge[i].node[0]-1];
		dx2= gridx[edge[i].node[1]-1]-cell[edge[i].adjacent_cell[1]].xc;
		dx3= cell[edge[i].adjacent_cell[0]].xc-gridx[edge[i].node[1]-1];
		dx4= gridx[edge[i].node[0]-1]-cell[edge[i].adjacent_cell[0]].xc;

		dy24=cell[edge[i].adjacent_cell[0]].yc-cell[edge[i].adjacent_cell[1]].yc;
		dx24=cell[edge[i].adjacent_cell[0]].xc-cell[edge[i].adjacent_cell[1]].xc;

		dy13=gridy[edge[i].node[1]-1]-gridy[edge[i].node[0]-1];
		dx13=gridx[edge[i].node[1]-1]-gridx[edge[i].node[0]-1];

		areatemp=0.5 * fabs((dx24*dy13)-(dx13*dy24));

					
		ux=(uu1*dy1+uu2*dy2+uu3*dy3+uu4*dy4)/areatemp;
		uy=-(uu1*dx1+uu2*dx2+uu3*dx3+uu4*dx4)/areatemp;
		vx=(vv1*dy1+vv2*dy2+vv3*dy3+vv4*dy4)/areatemp;
		vy=-(vv1*dx1+vv2*dx2+vv3*dx3+vv4*dx4)/areatemp;
		
	  //find normal and tangent derivatives
		
		du_n = ux*edge[i].nx + uy*edge[i].ny;
		du_t = -ux*edge[i].ny + uy*edge[i].nx;
				
		dv_n = vx*edge[i].nx + vy*edge[i].ny;
		dv_t = -vx*edge[i].ny + vy*edge[i].nx;
		
				
		//tau_xy = viscosity*(vx - uy);
		tau_xy = viscosity*(dv_t+du_n);
		
	/*	if(edge[i].cx<=0)
		{
		  theta=180.0/3.1415*asin((fabs(edge[i].cy)/0.5));
		}
		else
		{
		 theta=180.0-(180.0/3.1415*asin((fabs((gridy[edge[i].node[0]-1]+gridy[edge[i].node[1]-1]))/(2.0*0.5))));
		}
	   */ 
		edge[i].sf = tau_xy/0.5;
		
	//	fprintf(f666,"%f \t %f\t %d \n",theta, edge[i].sf,rtstep);
	  }
	}

//lift and drag

	FILE *f55;
	f55=fopen("lift.dat","a");
	
	FILE *f66;
	f66=fopen("drag.dat","a");
	
	FILE *f77;
	f77=fopen("total-force-data.dat","a");

	drag_T = 0.0;
	lift_T = 0.0;
	


	for(i=1;i<=no_edge;i++)
	{
	  if(edge[i].bc_type == 3 )	// top left wall
	  {
	    dx = fabs(edge[i].ny*edge[i].L);
	    dy = fabs(edge[i].nx*edge[i].L);
	    
	      lift = (-edge[i].cp*dx) + (-edge[i].sf*dy);     

                drag = (edge[i].cp*dy) + (-edge[i].sf*dx);
	
		lift_T = lift_T + lift;
	      drag_T = drag_T + drag;
	
	  }
	 if(edge[i].bc_type == 4 )	// top right wall
	  {
	    dx = fabs(edge[i].ny*edge[i].L);
	    dy = fabs(edge[i].nx*edge[i].L);
	    
	      
		lift = (-edge[i].cp*dx) + (edge[i].sf*dy);	
	
                    drag =  (-edge[i].cp*dy) + (-edge[i].sf*dx);
	     
	      lift_T = lift_T + lift;
	      drag_T = drag_T + drag;
		
	   //   fprintf(f55,"%f \t %f \t%d \n",edge[i].cx,lift,rtstep);//		 p_force);
	    //  fprintf(f66,"%f \t %f \t%d \n",edge[i].cx, drag,rtstep);//		ss_force); 
	  }
	  if(edge[i].bc_type == 5 )	// bot left wall
	  {
	     dx = fabs(edge[i].ny*edge[i].L);
	     dy = fabs(edge[i].nx*edge[i].L);
	
			lift = (edge[i].cp*dx) + (edge[i].sf*dy);

		    drag =  (edge[i].cp*dy) + (-edge[i].sf*dx);
		
	      lift_T = lift_T + lift;
	     drag_T = drag_T + drag;
		
	    //  fprintf(f55,"%f \t %f \t%d \n",edge[i].cx,lift,rtstep);//		 p_force);
	    //  fprintf(f66,"%f \t %f  \t%d\n",edge[i].cx, drag,rtstep);//		ss_force); 
	  }
	if(edge[i].bc_type ==  6 )	// bot right wall
	  {
	     dx = fabs(edge[i].ny*edge[i].L);
	     dy = fabs(edge[i].nx*edge[i].L);

		 lift = (edge[i].cp*dx) + (-edge[i].sf*dy);

                drag =  (-edge[i].cp*dy) + (-edge[i].sf*dx);

	      lift_T = lift_T + lift;
	     drag_T = drag_T + drag;
		
	    //  fprintf(f55,"%f \t %f \t%d \n",edge[i].cx,lift,rtstep);//		 p_force);
	    //  fprintf(f66,"%f \t %f  \t%d\n",edge[i].cx, drag,rtstep);//		ss_force); 
	  }
	}
	   
	//printf("rtstep = %d \t Lift force = %f \t Drag force = %f      \n",rtstep, lift_T, drag_T );   
	//fprintf(f77,"%f \t %f \t %f \t%d   \n",rtstep*rdt, lift_T, drag_T,rtstep );   

        
//Nu
	FILE *f88;
	f88=fopen("Nu.dat","a");
	
	FILE *f99;
	f99=fopen("Nu_average.dat","a");
        
         double Nu_avg, no_wall_edge;
	
	 Nu_avg = 0.0;





        no_wall_edge = 0.0;

        
	for(i=1;i<=no_edge;i++)
	{
	  theta = 0.0;
	  
	  if(edge[i].bc_type == 3 || edge[i].bc_type == 4 )	// top wall
	  {
	    //find Nusselt no
		
		
		
		tt1= 0.5*(vertex[edge[i].node[0]].un[3] + cell[edge[i].adjacent_cell[1]].u[3]);
		tt2= 0.5*(cell[edge[i].adjacent_cell[1]].u[3] + vertex[edge[i].node[1]].un[3]);
		tt3= 0.5*(vertex[edge[i].node[1]].un[3] + cell[edge[i].adjacent_cell[0]].u[3]);
		tt4= 0.5*(cell[edge[i].adjacent_cell[0]].u[3] + vertex[edge[i].node[0]].un[3]);	
		
		dy1= cell[edge[i].adjacent_cell[1]].yc-gridy[edge[i].node[0]-1];
		dy2= gridy[edge[i].node[1]-1]-cell[edge[i].adjacent_cell[1]].yc;
		dy3= cell[edge[i].adjacent_cell[0]].yc-gridy[edge[i].node[1]-1];
		dy4= gridy[edge[i].node[0]-1]-cell[edge[i].adjacent_cell[0]].yc;


		dx1= cell[edge[i].adjacent_cell[1]].xc-gridx[edge[i].node[0]-1];
		dx2= gridx[edge[i].node[1]-1]-cell[edge[i].adjacent_cell[1]].xc;
		dx3= cell[edge[i].adjacent_cell[0]].xc-gridx[edge[i].node[1]-1];
		dx4= gridx[edge[i].node[0]-1]-cell[edge[i].adjacent_cell[0]].xc;

		dy24=cell[edge[i].adjacent_cell[0]].yc-cell[edge[i].adjacent_cell[1]].yc;
		dx24=cell[edge[i].adjacent_cell[0]].xc-cell[edge[i].adjacent_cell[1]].xc;

		dy13=gridy[edge[i].node[1]-1]-gridy[edge[i].node[0]-1];
		dx13=gridx[edge[i].node[1]-1]-gridx[edge[i].node[0]-1];

		areatemp=0.5 * fabs((dx24*dy13)-(dx13*dy24));

					
		
		tx=(tt1*dy1+tt2*dy2+tt3*dy3+tt4*dy4)/areatemp;
	        ty=-(tt1*dx1+tt2*dx2+tt3*dx3+tt4*dx4)/areatemp;
		
		du_n = tx*edge[i].nx + ty*edge[i].ny;
		//du_t = -tx*edge[i].ny + ty*edge[i].nx;
				
		
	/*	if(edge[i].cx<=0)
		{
		  theta=180.0/3.1415*asin((fabs(edge[i].cy)/0.5));
		}
		else
		{
		 theta=180.0-(180.0/3.1415*asin((fabs((gridy[edge[i].node[0]-1]+gridy[edge[i].node[1]-1]))/(2.0*0.5))));
		}
	    */
	//	edge[i].nusselt = du_n;
		
		Nu = du_n;





                Nu_avg = Nu_avg + Nu;





                no_wall_edge = no_wall_edge + 1 ;
		
		//fprintf(f88,"%f \t %f \t%d \n",theta, edge[i].nusselt,rtstep);
	  }
	 else if(edge[i].bc_type == 5 || edge[i].bc_type == 6)	// bot wall
	  {
	    //find Nusselt no
		
		
		
		tt1= 0.5*(vertex[edge[i].node[0]].un[3] + cell[edge[i].adjacent_cell[1]].u[3]);
		tt2= 0.5*(cell[edge[i].adjacent_cell[1]].u[3] + vertex[edge[i].node[1]].un[3]);
		tt3= 0.5*(vertex[edge[i].node[1]].un[3] + cell[edge[i].adjacent_cell[0]].u[3]);
		tt4= 0.5*(cell[edge[i].adjacent_cell[0]].u[3] + vertex[edge[i].node[0]].un[3]);	
		
		dy1= cell[edge[i].adjacent_cell[1]].yc-gridy[edge[i].node[0]-1];
		dy2= gridy[edge[i].node[1]-1]-cell[edge[i].adjacent_cell[1]].yc;
		dy3= cell[edge[i].adjacent_cell[0]].yc-gridy[edge[i].node[1]-1];
		dy4= gridy[edge[i].node[0]-1]-cell[edge[i].adjacent_cell[0]].yc;


		dx1= cell[edge[i].adjacent_cell[1]].xc-gridx[edge[i].node[0]-1];
		dx2= gridx[edge[i].node[1]-1]-cell[edge[i].adjacent_cell[1]].xc;
		dx3= cell[edge[i].adjacent_cell[0]].xc-gridx[edge[i].node[1]-1];
		dx4= gridx[edge[i].node[0]-1]-cell[edge[i].adjacent_cell[0]].xc;

		dy24=cell[edge[i].adjacent_cell[0]].yc-cell[edge[i].adjacent_cell[1]].yc;
		dx24=cell[edge[i].adjacent_cell[0]].xc-cell[edge[i].adjacent_cell[1]].xc;

		dy13=gridy[edge[i].node[1]-1]-gridy[edge[i].node[0]-1];
		dx13=gridx[edge[i].node[1]-1]-gridx[edge[i].node[0]-1];

		areatemp=0.5 * fabs((dx24*dy13)-(dx13*dy24));

					
		
		tx=(tt1*dy1+tt2*dy2+tt3*dy3+tt4*dy4)/areatemp;
	        ty=-(tt1*dx1+tt2*dx2+tt3*dx3+tt4*dx4)/areatemp;
		
		du_n = tx*edge[i].nx + ty*edge[i].ny;
		//du_t = -tx*edge[i].ny + ty*edge[i].nx;
				
		
	/*	if(edge[i].cx<=0)
		{
		  theta=180.0/3.1415*asin((fabs(edge[i].cy)/0.5));
		}
		else
		{
		 theta=180.0-(180.0/3.1415*asin((fabs((gridy[edge[i].node[0]-1]+gridy[edge[i].node[1]-1]))/(2.0*0.5))));
		}
	    
		edge[i].nusselt = du_n;
		*/
		Nu = du_n;





                Nu_avg = Nu_avg + Nu;





                no_wall_edge = no_wall_edge + 1 ;
		
	//	fprintf(f88,"%f \t %f \t%d \n",theta, edge[i].nusselt,rtstep);
	  }
	}
	
	 // find average Nu


	Nu_avg = Nu_avg/no_wall_edge;





	fprintf(f77,"%f \t %f \t %f \t %f \t %d  \n",rtstep*rdt, lift_T, drag_T, Nu_avg, rtstep );
        
        
	fclose(f555);
	fclose(f666);
	fclose(f55);
	fclose(f66);
	fclose(f77);
	fclose(f88);
	fclose(f99);
}

	

	

	

	

	

	


    
