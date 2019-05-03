/*===========================================================================
  This demonstrative example is provided by the teaching assistant,
  Mr. Shih-Hung Liao (廖世宏), and modified by the instructor, Prof. Lan.

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
//int G[MaxBMPSizeX][MaxBMPSizeY];
//int B[MaxBMPSizeX][MaxBMPSizeY];
int r[MaxBMPSizeX][MaxBMPSizeY];
//int g[MaxBMPSizeX][MaxBMPSizeY];
//int b[MaxBMPSizeX][MaxBMPSizeY];

int main(int argc, char *argv[])
{
	int width, height;
	int h, w;
	
	// 開啟並讀取全彩(24bits)bmp 影像圖檔
	// RGB 三個 channel 的值存入 R, G, B 三個自訂的陣列中
	// 陣列大小不得大於 1024x1024
	//open_bmp("original.bmp", R, G, B, width, height); // for true color images
	 open_bmp("boat.bmp", R, R, R, width, height); // for gray images


    /*----------------------------------------------------------------------------
	      範例：產生數位負片（請將主程式放在此處）
    ----------------------------------------------------------------------------*/
    for (h = 0; h < height; h++){
       for (w = 0; w < width; w++){
		
		r[h][w] = (R[h-1][w-1] + R[h-1][w] + R[h-1][w+1] + R[h][w-1] + 
					R[h][w+1] + R[h+1][w-1] + R[h+1][w] + R[h+1][w+1]) * (-1) / 9 + R[h][w] * 8 / 9; //HPF

		r[h][w] = r[h][w] + R[h][w];
		
       }
    }

    
	// 儲存處理結果至新的圖檔中
	save_bmp("new1.bmp", r, r, r); // for true color images
	//save_bmp("lena_new.bmp", r, r, r); // for gray images
	printf("Job Finished!\n");

	// 關閉 bmp 影像圖檔
	close_bmp();

	system("PAUSE"); /* so that the command window holds a while */
	return 0;
}




