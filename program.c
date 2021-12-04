#include "definitions.h"
#include "definitions_rbf.h"


int main()
{
	int i,j,itermax; 	double rss;
	
	FILE *conv;	
	conv = fopen("Convergence.dat","w");
	
	beta=1.0;
	
	rdt = 0.1;	// set real time step
	
	rtstep=0;
	
	readcgnsdata();
	
	readcgnsdata_rbf();
	
	extra_memory();

	initlize();
        
        // to check data structutre 
        //output();
         output_tecplot();
	
	transfer();
	
//re-start the code from previous solution
	
	for(rtstep = 0; rtstep < 4500; rtstep++)
	{
            if(rtstep <300)
            {
			rdt = 0.1;	// set real time step - time 100 
            }
            else
            {
			rdt = 0.1;	// set real time step 100 - 290
            }
		
	  int row, temp;
	  double *x,*y,*p,*u,*v,*T,*dv;
	  		
	 // read n-2 flie 
	  if(rtstep == 0)
	  {
	     // read file 0 - extract x y cordinates and data 
	    
	      x = malloc(no_point * sizeof(double));
	      y = malloc(no_point * sizeof(double));
	      p = malloc(no_point * sizeof(double));
	      u = malloc(no_point * sizeof(double));
	      v = malloc(no_point * sizeof(double));
	      T = malloc(no_point * sizeof(double));
	      dv = malloc(no_point * sizeof(double));
			
	      FILE *fp;
	      fp = fopen("restart1.dat","r");
	      //FILE *op = fopen("crosscheck-out-1","w");
	      
	      for(row=1;row<=no_point;row++)
	      {
		fscanf(fp,"%lf",&x[row]);
		fscanf(fp,"%lf",&y[row]);
		fscanf(fp,"%lf",&p[row]);
		fscanf(fp,"%lf",&u[row]);
		fscanf(fp,"%lf",&v[row]);
		fscanf(fp,"%lf",&T[row]);
		fscanf(fp,"%lf",&dv[row]);
	  
		// cross check data
		//fprintf(op,"%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",x[row], y[row], p[row], u[row],v[row], dv[row]);
	      }
	  
	      fclose(fp);
	      //fclose(op);
	      
	      // give cordinates as new
	      for(i=1; i<=vertex_max; i++)
	      {
		gridx_new[vertex[i].no -1] = x[i];
		
		gridy_new[vertex[i].no -1] = y[i];
	      }
	    		
	      readcgnsdata_1();
	      
	      //find variables at a cell center
	      int temp =0;
	      for(i=1; i<=no_cell; i++)
	      {
		cell[i].u[0] = (p[elementdata_fluid[temp]] + p[elementdata_fluid[temp+1]] + p[elementdata_fluid[temp+2]] + p[elementdata_fluid[temp+3]])/4 ;
		
		cell[i].u[1] = (u[elementdata_fluid[temp]] + u[elementdata_fluid[temp+1]] + u[elementdata_fluid[temp+2]] + u[elementdata_fluid[temp+3]])/4 ;
		
		cell[i].u[2] = (v[elementdata_fluid[temp]] + v[elementdata_fluid[temp+1]] + v[elementdata_fluid[temp+2]] + v[elementdata_fluid[temp+3]] )/4 ;
                
        cell[i].u[3] = (T[elementdata_fluid[temp]] + T[elementdata_fluid[temp+1]] + T[elementdata_fluid[temp+2]] + T[elementdata_fluid[temp+3]] )/4 ;               
                
		
		temp=temp+4;
	      }
	      
	      output_tecplot();
              
	      nodal_velo();
	      
	      transfer();
	      
	  //    free(x), free(y), free(p); free(u); free(v); free(dv);
	  }
	  else if(rtstep == 1)
	  {
	      // read file 1 - extract x y cordinates and data 
	    
	      FILE *fp;
	      fp = fopen("restart1.dat","r");
	      //FILE *op = fopen("out","w");
	      
	      for(row=1;row<=no_point;row++)
	      {
		fscanf(fp,"%lf",&x[row]);
		fscanf(fp,"%lf",&y[row]);
		fscanf(fp,"%lf",&p[row]);
		fscanf(fp,"%lf",&u[row]);
		fscanf(fp,"%lf",&v[row]);
		fscanf(fp,"%lf",&T[row]);
		fscanf(fp,"%lf",&dv[row]);
	  
		// cross check data
		//fprintf(op,"%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",x[row], y[row], p[row], u[row],v[row], vort[row]);
	      }
	  
	      fclose(fp);
	      //fclose(op);
	      
	      // give cordinates as new
	      for(i=1; i<=vertex_max; i++)
	      {
		gridx_new[vertex[i].no -1] = x[i];
		
		gridy_new[vertex[i].no -1] = y[i];
	      }
	    		
	      readcgnsdata_1();
	      
	      //find variables at a cell center
	      temp =0;
	      for(i=1; i<=no_cell; i++)
	      {
		cell[i].u[0] = (p[elementdata_fluid[temp]] + p[elementdata_fluid[temp+1]] + p[elementdata_fluid[temp+2]] + p[elementdata_fluid[temp+3]])/4 ;
		
		cell[i].u[1] = (u[elementdata_fluid[temp]] + u[elementdata_fluid[temp+1]] + u[elementdata_fluid[temp+2]] + u[elementdata_fluid[temp+3]])/4 ;
		
		cell[i].u[2] = (v[elementdata_fluid[temp]] + v[elementdata_fluid[temp+1]] + v[elementdata_fluid[temp+2]] + v[elementdata_fluid[temp+3]] )/4 ;
                
        cell[i].u[3] = (T[elementdata_fluid[temp]] + T[elementdata_fluid[temp+1]] + T[elementdata_fluid[temp+2]] + T[elementdata_fluid[temp+3]] )/4 ;               
                
		
		temp=temp+4;
	      }
	      
	     
	      output_tecplot();
              
			
	      nodal_velo();
	      
	      transfer();
	      
	    //  free(x), free(y), free(p); free(u); free(v); free(dv);
	  }
	  else
	  {
	// start iteration with moved mesh 
		readcgnsdata_1();
	
		initlize_1();	
			
		nodal_velo();
		
		for(i=1;i<=no_cell + no_boundaryedges;i++)
		{
		    cell[i].dv = 0.0;
		}
		
		face_vol_increment();

		for(i=1; i<=no_cell; i++)
		{
		    if(rtstep==1)
		    {
			cell[i].area = area1[i-1] + rdt*(cell[i].dv);
		    }
		    else
		    {
			cell[i].area = (4.0*area1[i-1] - area2[i-1] - 2.0*rdt*(cell[i].dv))/3.0;
		    }
		}

		//accuracy_1();
			
		rss = 1.0;
		
		iter = 0;
		
		if(rtstep<10)
		{	
		  itermax = 900;  
		}
		else
		{	
		  itermax = 240; 
		}	  
		      
		while(iter<itermax)
		{   
		    for(i=1;i<=no_cell;i++)
		    {
			    for(j=0;j<=3;j++)
			    {
				    cell[i].u_temp[j]=cell[i].u[j];
			    }
		    }
		    
		    boundary_conditions();
		    
		    time_step();
	
		    RUNGK(0.25);

		    RUNGK(0.16667);

		    RUNGK(0.375);

		    RUNGK(0.50);

		    RUNGK(1.0);
						    
		    iter++;
		    
		    convergence();
		    
		    printf("rss = %lf\t iter = %d\t time_step = %lf \t step=%d\n",log10(rss_t),iter,rdt,rtstep);
		    
		    fprintf(conv,"%d\t%lf \t%d\n",iter,log10(rss_t),rtstep);	
		}
		    
		// output();
		if(rtstep %10 == 0)
                {
                    output_tecplot();
                }
		    
		 cl_cd();
		 
		 VIV();		//find displacement of cylinder
		 
		 //mesh_movement();	// move the grid and creat new cgns file
		 
		  rbf_trans();            // move the grid points without changing whole domain
	    
		 transfer();
		 
	  }
		
	}
	
	free(vertex);
	
	free(cell);
	
	free(edge);
	
	free(node);
	
	free(side);
	
	fclose (conv);
	
}

