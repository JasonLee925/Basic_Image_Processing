#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include "bmp.h"

using namespace std;

int R[MaxBMPSizeX][MaxBMPSizeY]; 
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];
int r[MaxBMPSizeX][MaxBMPSizeY];
int g[MaxBMPSizeX][MaxBMPSizeY];
int b[MaxBMPSizeX][MaxBMPSizeY];

//―程 
double getMaxPixal(int cR, int cG, int cB){
	int compareArray[] = {cR, cG, cB};
	return *max_element(compareArray,compareArray+3);
}

//―程 
double getMinPixal(int cR, int cG, int cB){
	int compareArray[] = {cR, cG, cB};
	return *min_element(compareArray,compareArray+3);
}

int main(int argc, char *argv[])
{
	int Xaxis, Yaxis;
	int x, y;
	
	double max, min, V, z, S, H, Rc, Gc, Bc;
	open_bmp("skin_det_1.bmp", R, G, B, Yaxis, Xaxis); 
					
    for (y = 0; y < Yaxis; y++){
	    for (x = 0; x < Xaxis; x++){
		    	//程 
	    		max = getMaxPixal(R[y][x], G[y][x], B[y][x]);
	    		//程 
	    		min = getMinPixal(R[y][x], G[y][x], B[y][x]);
	    		//R,G,B /255 笲衡 
		    	Rc = (double)R[y][x] / 255;
		    	Gc = (double)G[y][x] / 255;
		    	Bc = (double)B[y][x] / 255;
		    	
				V = max/255;
				z = (max/255 - min/255); //畉 
		    	S = z / (max/255);
		    	
		    	//耞V 
		    	if(V == Rc)
		    		H = ((Gc - Bc) / z) / 6;
		    	if(V == Gc)
		    		H = (2 + (Bc - Rc) / z) / 6;
		    	if(V == Bc)
		    		H = (4 + (Rc - Gc) / z) / 6;
		    	
		    	//狦H璽计,玥+1 
		    	if(H < 0)
		    		H += 1;
		    		
		    	//锣à 
		    	H = H * 360;
		    	
		    	
		    	
		    	//耞絛瞅 
		    	if(13<H && H<42 && 0.15<S && S<0.4){
//		    	if(6<H && H<38 && 0.23<S && S<0.68){
		    		r[y][x] = 255;
		    		g[y][x] = 255;
		    		b[y][x] = 255;
				} else {
		    		r[y][x] = 0;
		    		g[y][x] = 0;
		    		b[y][x] = 0;
				}
	       	}
       }
    

    
	save_bmp("result_1.bmp", r, g, b);
	printf("Job Finished!\n");

	close_bmp();

	system("PAUSE");
	return 0;
}




