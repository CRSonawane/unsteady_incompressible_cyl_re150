#include "definitions.h"
#include "definitions_rbf.h"

void VIV()
{
  
  //.......... Calculate  Coefficients..................................
  
  A_viv = 4.0*pi*damp_ratio*fny;
  
  B_viv = 4.0*pi*pi*fny*fny;
  
  //..............Initialization to zero...........................
  
  if(rtstep<=2)
  {
      disp_viv = 0.0;
  
      vel_viv = 0.0;
  
      acc_viv = 0.0;
  
      disp_viv_old = 0.0;
  
      vel_viv_old = 0.0;
  
      acc_viv_old = 0.0;
  }
 
  //......................VIV SOLVER...................................
  

      acc_viv = (lift_T)/(2.0*mr) - B_viv*disp_viv_old; //- A_viv*vel_viv_old
      
      vel_viv = vel_viv_old + acc_viv*rdt;
      
      //......displacement in one time step....................
      
      ds_viv = rdt*0.5*(vel_viv + vel_viv_old);
      
      //.........displacement from equilibrium position........
      
      disp_viv = disp_viv_old + ds_viv;
      
      //move the cylinder in each time step w.r.t local discplacement
           
      cyl_movement = 0.0;   //ds_viv;  -----> unsteady ONLY
      
      FILE *f123;
      
      f123=fopen("acc_vel.dat","a");
      
      //fprintf(f123,"%f\t%f\n",acc_viv,vel_viv);
      
		

	
      //write disp vs real time

	FILE *f124;
	
        f124=fopen("cylinder_dis.dat","a");
      
	fprintf(f124,"%f\t%d\t%f\t%f\n",rtstep*rdt,rtstep,cyl_movement,disp_viv);
	 	
// for initial stability - do not move grid till t = 0.01 * 10 = 0.1 sec
	/*if(rtstep < 10)
	{
		 cyl_movement = 0.5;
	}*/
  

  //................Transfer velocity and displacemnt..................?????
  
  vel_viv_old = vel_viv;
  
  disp_viv_old = disp_viv;
  
  FILE *f125;
      
  f125=fopen("disp_vel_old.dat","a");
  
 // fprintf(f125,"%f\t%f\n",vel_viv_old,disp_viv_old);
	    
	 
	
  fclose(f123);
  fclose(f124);
  fclose(f125);
}
  
  
