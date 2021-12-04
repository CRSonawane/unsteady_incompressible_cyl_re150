#include "definitions.h"

void extra_memory()	
{

//reqired during time steeping
  // previous step
	gridx_1 = malloc((no_point+5) * sizeof(double));

	gridy_1 = malloc((no_point+5) * sizeof(double));
	
	up1_p = malloc((no_cell+5) * sizeof(double));

	up1_u = malloc((no_cell+5) * sizeof(double));

	up1_v = malloc((no_cell+5) * sizeof(double));
	
	up1_T = malloc((no_cell+5) * sizeof(double));
	
	area2 = malloc((no_cell+5) * sizeof(double));
	
  // previous to previous step
	gridx_2 = malloc((no_point+5) * sizeof(double));

	gridy_2 = malloc((no_point+5) * sizeof(double));

	up2_p = malloc((no_cell+5) * sizeof(double));

	up2_u = malloc((no_cell+5) * sizeof(double));

	up2_v = malloc((no_cell+5) * sizeof(double));
	
	up2_T = malloc((no_cell+5) * sizeof(double));

	area1 = malloc((no_cell+5) * sizeof(double));

	

	dxp = malloc((no_edge+5) * sizeof(double));

	dyp = malloc((no_edge+5) * sizeof(double));
	
/*	nxp = malloc((no_edge+5) * sizeof(double));

	nyp = malloc((no_edge+5) * sizeof(double));

	Lp = malloc((no_edge+5) * sizeof(double));

	cxp = malloc((no_edge+5) * sizeof(double));
	
	cyp = malloc((no_edge+5) * sizeof(double));
*/	
// new mesh obtained after mesh movement
	gridx_new = malloc((vertex_max+5) * sizeof(double));
	
	gridy_new = malloc((vertex_max+5) * sizeof(double));
}
