#include "definitions.h"

void nodal_velo()
{		
	int i,v1,v2;
	
	// find velocity of each vertex
	for(i=1;i<=no_point;i++)
	{
	    vertex[i].xt = (gridx[vertex[i].no -1] - gridx_1[vertex[i].no -1])/rdt;
	    vertex[i].yt = (gridy[vertex[i].no -1] - gridy_1[vertex[i].no -1])/rdt;
	}
	
	//find velocity of each edge due to mesh movement
	
	for(i=1; i<=no_edge; i++)
	{
	 //   v1 = edge[i].node[0];
	  //  v2 = edge[i].node[1];

		edge[i].xt = (vertex[edge[i].node[0]].xt + vertex[edge[i].node[1]].xt)/2.0;

		edge[i].yt = (vertex[edge[i].node[0]].yt + vertex[edge[i].node[1]].yt)/2.0;
	}
		
}


/*
 	for(i=1; i<=no_edge; i++)
	{
	    v1 = edge[i].node[0];
	    v2 = edge[i].node[1];
		
	    if(rtstep>1)
	    {
	
	// node 1	
		edge[i].Wx_12 = (gridx_1[v1-1] - gridx_2[v1-1])/rdt;
		edge[i].Wy_12 = (gridy_1[v1-1] - gridy_2[v1-1])/rdt;
	//node 2
		edge[i].Wx_22 = (gridx_1[v2-1] - gridx_2[v2-1])/rdt;	
		edge[i].Wy_22 = (gridy_1[v2-1] - gridy_2[v2-1])/rdt;
	    }
	    
	    // node 1	
		edge[i].Wx_11 = (gridx[v1-1] - gridx_1[v1-1])/rdt;
		edge[i].Wy_11 = (gridy[v1-1] - gridy_1[v1-1])/rdt;
	  //node 2
		edge[i].Wx_21 = (gridx[v2-1] - gridx_1[v2-1])/rdt;	
		edge[i].Wy_21 = (gridy[v2-1] - gridy_1[v2-1])/rdt;
	    
//		edge[i].W0 = sqrt((edge[i].Wx_0*edge[i].Wx_0) + (edge[i].Wy_0*edge[i].Wy_0)) ;

//		edge[i].W1 = sqrt((edge[i].Wx_1*edge[i].Wx_1) + (edge[i].Wy_1*edge[i].Wy_1)) ;

		edge[i].xt = (edge[i].Wx_11 + edge[i].Wx_21)/2.0;

		edge[i].yt = (edge[i].Wy_11 + edge[i].Wy_21)/2.0;
	}
	*/














