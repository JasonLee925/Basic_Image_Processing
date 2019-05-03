/*===========================================================================
  This demonstrative example is provided by the teaching assistant,
  Mr. Shih-Hung Liao (���@��), and modified by the instructor, Prof. Lan.

  (1) It can be compiled and executed correctly under the DEV-C++, and Visual C++
      environments.
  (2) In order to run this program, you should also have the "bmp.h" and
      "bmp.cpp" files installed in your current directory or whichever directory
      the C++ compiler is directed to search for.
  (3) The DEV-C++ is a free C++ development environment that is recommended for
      this course. Refer to http://www.bloodshed.net/dev/devcpp.html.

                             Apr. 3, 2006
============================================================================*/
#include <iostream>
#include <stdlib.h>
#include "bmp.h"

using namespace std;

int R[MaxBMPSizeX][MaxBMPSizeY]; // MaxBMPSizeX and MaxBMPSizeY are defined in "bmp.h"
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];
int r[MaxBMPSizeX][MaxBMPSizeY];
int g[MaxBMPSizeX][MaxBMPSizeY];
int b[MaxBMPSizeX][MaxBMPSizeY];

int main(int argc, char *argv[])
{
	int width, height;	//���פμe�� 
	int h, w;	//�p��� 
	int er, eg, eb;		//�~�t�� 

	// �}�Ҩ�Ū�����m(24bits)bmp �v������
	// RGB �T�� channel ���Ȧs�J R, G, B �T�Ӧۭq���}�C��
	// �}�C�j�p���o�j�� 1024x1024
	open_bmp("original.bmp", R, G, B, width, height); // for true color images
	// open_bmp("lena.bmp", R, R, R, width, height); // for gray images


    /*----------------------------------------------------------------------------
	      �d�ҡG���ͼƦ�t���]�бN�D�{����b���B�^
    ----------------------------------------------------------------------------*/
    
    for (h = 0; h <= height; h++){
       for (w = 0; w <= width; w++){
       	
       		if(R[h][w] >= 128){
    			r[h][w] = 255;
				er = R[h][w] - 255;
			} else{
    			r[h][w] = 0;
    			er = R[h][w];
			}
    			
       	 	if(G[h][w] >= 128){
    			g[h][w] = 255;
       			eg = G[h][w] - 255;
			} else{
    			g[h][w] = 0;
    			eg = G[h][w];
			}
    			
       		if(B[h][w] >= 128){
    			b[h][w] = 255;
    			eb = B[h][w] - 255;
			} else{
    			b[h][w] = 0;
    			eb = B[h][w];
			}
       	
       		if(w+1 <= width)
       			R[h][w+1] = er * 7 / 16 + R[h][w+1]; //�k 
       		if(h+1 <= height){
				R[h+1][w-1] = er * 3 / 16 + R[h+1][w-1]; //���U 
		       	R[h+1][w] = er * 5 / 16 + R[h+1][w]; //�U
		       	if(w+1 <= width)
					R[h+1][w+1] = er * 1 / 16 + R[h+1][w+1]; //�k�U 
			   }
			   
         	if(w+1 <= width)
       			G[h][w+1] = eg * 7 / 16 + G[h][w+1]; //�k 
       		if(h+1 <= height){
				G[h+1][w-1] = eg * 3 / 16 + G[h+1][w-1]; //���U 
		       	G[h+1][w] = eg * 5 / 16 + G[h+1][w]; //�U
		       	if(w+1 <= width)
					G[h+1][w+1] = eg * 1 / 16 + G[h+1][w+1]; //�k�U 
			   }
			   
			if(w+1 <= width)
       			B[h][w+1] = eb * 7 / 16 + B[h][w+1]; //�k 
       		if(h+1 <= height){
				B[h+1][w-1] = eb * 3 / 16 + B[h+1][w-1]; //���U 
		       	B[h+1][w] = eb * 5 / 16 + B[h+1][w]; //�U
		       	if(w+1 <= width)
					B[h+1][w+1] = eb * 1 / 16 + B[h+1][w+1]; //�k�U 
			   }
       }
    }

    
	// �x�s�B�z���G�ܷs�����ɤ�
	save_bmp("new1.bmp", r, g, b); // for true color images
	//save_bmp("lena_new.bmp", r, r, r); // for gray images
	printf("Job Finished!\n");

	// ���� bmp �v������
	close_bmp();

	system("PAUSE"); /* so that the command window holds a while */
	return 0;
}

