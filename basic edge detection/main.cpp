#include <iostream>
#include <stdlib.h>
#include "bmp.h"

using namespace std;

int R[MaxBMPSizeX][MaxBMPSizeY];
int r[MaxBMPSizeX][MaxBMPSizeY];
int g1[MaxBMPSizeX][MaxBMPSizeY];
int g2[MaxBMPSizeX][MaxBMPSizeY];

int main(int argc, char *argv[])
{
	int width, height;
	int h, w;
	open_bmp("house.bmp", R, R, R, width, height); 

	//�p��g1, g2 
    for (h = 0; h < height; h++){
		for (w = 0; w < width; w++){
	       	g1[w][h] = R[w-1][h-1]*(-1) + R[w-1][h]*0 + R[w-1][h+1] +
						R[w][h-1]*(-2) + R[w][h]*0 + R[w][h+1]*2 +
						R[w+1][h-1]*(-1) + R[w+1][h]*0 + R[w+1][h+1]; 
			g2[h][w] = R[h-1][w-1]*(-1) + R[h-1][w]*(-2) + R[h-1][w+1]*(-1) +
						R[h][w-1]*0 + R[h][w]*0 + R[h][w+1]*0 +
						R[h+1][w-1] + R[h+1][w]*2 + R[h+1][w+1]; 
	    }
    }	
    
    //g1, g2������Ȭۥ[ ,�Y������>=255,��X255;��l��0
	for (h = 0; h < height; h++){
		for (w = 0; w < width; w++){
			if(abs(g1[w][h]) + abs(g2[w][h]) >= 255)
	       		r[w][h]= 255;
	       	else
	       		r[w][h]= 0;
	    }
    }	
    
	// �x�s�B�z���G�ܷs�����ɤ�
	save_bmp("new1.bmp", r, r, r); 
	printf("Job Finished!\n");

	// ���� bmp �v������
	close_bmp();

	system("PAUSE"); 
	return 0;
}
