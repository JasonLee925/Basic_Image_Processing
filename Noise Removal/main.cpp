#include <iostream>
#include <stdlib.h>
#include "bmp.h"

//using namespace std;

int R[MaxBMPSizeX][MaxBMPSizeY]; 
int t[MaxBMPSizeX][MaxBMPSizeY];
int t2[MaxBMPSizeX][MaxBMPSizeY];
int t3[MaxBMPSizeX][MaxBMPSizeY];
int r[MaxBMPSizeX][MaxBMPSizeY];

//«I»k 
bool Erosion(int pixels[]){
	bool isMatch = false;
	int arraySize = sizeof(pixels);
	for(int i = 0; i < 5; i++){
		if(pixels[i] == 0){
			isMatch = true;
			break;
		}
	}
	
	return isMatch;
}

//¿±µÈ 
bool Dilation(int pixels){
	bool isMatch = false;
	if(pixels == 255){
		isMatch = true;
	}
	
	return isMatch;
}

int main(int argc, char *argv[])
{
	int width, height;
	int h, w;
	open_bmp("noise_remov_morph_gray.bmp", R, R, R, width, height); 

    for (h = 0; h < height; h++){
	    for (w = 0; w < width; w++){
	    	 int pixelsArray[5] = {			 R[h+1][w],
								  R[h][w-1], R[h][w], R[h][w+1],
								   			 R[h-1][w]};
								  
			 if(!Erosion(pixelsArray))
			 	t[h][w] = 255;
	       	}
       }
       
	for (h = 0; h < height; h++){
	    for (w = 0; w < width; w++){
	    	 int pixels = t[h][w];
								  
			 if(Dilation(pixels)){
			 	 r[h+3][w+3] = 255;
			 	 r[h+3][w+2] = 255;
			 	 r[h+3][w+1] = 255;
			 	 r[h+3][w] = 255;
			 	 r[h+2][w+3] = 255;
			 	 r[h+2][w+2] = 255;
			 	 r[h+2][w+1] = 255;
			 	 r[h+2][w] = 255;
			 	 r[h+1][w+3] = 255;
			 	 r[h+1][w+2] = 255;
			 	 r[h+1][w+1] = 255;
			 	 r[h+1][w] = 255;
			 	 r[h][w+3] = 255;
			 	 r[h][w+2] = 255;
			 	 r[h][w+1] = 255;
			 	 r[h][w] = 255;
			 	}
	       	}
       } 
    
    
	save_bmp("new1.bmp", r, r, r); 
	printf("Job Finished!\n");

	close_bmp();

	system("PAUSE");
	return 0;
}




