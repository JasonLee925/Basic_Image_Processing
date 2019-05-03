#include <iostream>
#include <stdlib.h>
#include <math.h> 
#include "bmp.h"
#include "fft1.c"
#include "fft2.c"
#define PI 3.14159265358979323846

using namespace std;

int R[MaxBMPSizeX][MaxBMPSizeY]; 
int real[MaxBMPSizeX][MaxBMPSizeY]; 
int image[MaxBMPSizeX][MaxBMPSizeY];
int r[MaxBMPSizeX][MaxBMPSizeY];
float data[256*256*2] = {0};

void spectrumShifting(int hh, int ww){
	int u, v;
	float rt = 0;
	float it = 0;
	for (u = -128; u < 128; u++){
	    for (v = -128; v < 128; v++){
		    	if(u<0 && v<0){
			    	rt = real[u][v];
			    	real[u][v] = real[u+hh][v+ww];
			    	real[u+hh][v+ww] = rt;
			    	
			    	it = image[u][v];
			    	image[u][v] = image[u+hh][v+ww];
			    	image[u+hh][v+ww] = it;
				} else if(u<0 && v>=0){
			    	rt = real[u][v];
			    	real[u][v] = real[u+hh][v-ww];
			    	real[u+hh][v-ww] = rt;
			    	
			    	it = image[u][v];
			    	image[u][v] = image[u+hh][v-ww];
			    	image[u+hh][v-ww] = it;
				} else{
					break;	
				}
	       	}
       }
}


int main(int argc, char *argv[])
{
	int width, height;
	int h, w;
	open_bmp("test.bmp", R, R, R, width, height); 
	int hh = height/2;  
	int ww = width/2;

	//將像素質陣列化 
	int tmp = 0; 
	for (h = 0; h < height; h++){
	    for (w = 0; w < width; w++){
	    	 data[tmp] = R[h][w];
	       	 tmp+=2;
	       	}
       }

    fft2(data, 256, 1); //正轉
    
    //把值塞回座標 
    tmp = 0;
	for (h = -128; h < 128; h++){
	    for (w = -128; w < 128; w++){
	       	 tmp+=1;
	    	 image[h][w] = data[tmp];
	       	 tmp+=1;
	    	 real[h][w] = data[tmp];
	       	}
       }
       
    spectrumShifting(hh, ww); //頻譜交換 
    
    //*H  
	float H; //H(u,v)
	float D = 0; //測試 
	float D0 = 20;
	for (h = -128; h < 128; h++){
	    for (w = -128; w < 128; w++){
//	    	 H = (sqrt(h*h + w*w) <= 10)?1:0; //理想低通 

			 D = pow(h*h + w*w, 0.5)/D0;
//			 D = D0/pow(h*h + w*w, 0.5);
			 H = 1 / (1 + pow(D, 4)); // 奶油價值

//			 float x = -(h*h + w*w) / 200 ; 
//	    	 H = exp(x); //高斯 
	    	 
	    	 tmp+=1;
	    	 image[h][w] = image[h][w] * H;
	       	 tmp+=1;
			 real[h][w] = real[h][w] * H;
	       	}
       }
       
    
    spectrumShifting(hh, ww); //頻譜交換 
       
    //將像素質陣列化 
    tmp = 0;
	for (h = -128; h < 128; h++){
	    for (w = -128; w < 128; w++){
	       	 tmp+=1;
	    	 data[tmp] = image[h][w];
	       	 tmp+=1;
	    	 data[tmp] = real[h][w];
	       	}
       }
	
    fft2(data, 256, -1); //反轉 
    
    //把值塞回座標 
	tmp = 0;
	for (h = 0; h < height; h++){
	    for (w = 0; w < width; w++){
	    	 r[h][w] = (int)data[tmp];
	       	 tmp+=2;
	       	}
       }
       
	save_bmp("Result1.bmp", r, r, r);
	printf("Job Finished!\n");

	close_bmp();

	system("PAUSE");
	
	return 0;
}
