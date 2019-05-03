#include <iostream>
#include <stdlib.h>
#include "bmp.h"

using namespace std;

int R[MaxBMPSizeX][MaxBMPSizeY]; 
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];
int r[MaxBMPSizeX][MaxBMPSizeY];
int g[MaxBMPSizeX][MaxBMPSizeY];
int b[MaxBMPSizeX][MaxBMPSizeY];
int ro[MaxBMPSizeX][MaxBMPSizeY];
int go[MaxBMPSizeX][MaxBMPSizeY];
int bo[MaxBMPSizeX][MaxBMPSizeY];

string inputValue;

int main(int argc, char *argv[])
{
	int width, height;
	int h, w;
	open_bmp("framed_airplane.bmp", R, G, B, width, height); 
	int p1h = 0, p1w = 0, p4h = 0, p4w = 0; 

	//�p���Ϥ��|�I�y�� 
    for (h = 0; h < height; h++){
    	if(p4h != 0 && p4w != 0)
    		break;
		
	    for (w = 0; w < width; w++){ 
	    	if(R[w][h] != 0 || G[w][h] != 0 || B[w][h] != 0){
	    		
				if(R[w-1][h-1] == 0 && G[w-1][h-1] == 0 && B[w-1][h-1] == 0){
					if(R[w][h-1] == 0 && G[w][h-1] == 0 && B[w][h-1] == 0){
						if(R[w-1][h] == 0 && G[w-1][h] == 0 && B[w-1][h] == 0){	
							p1h = h;
							p1w = w;
						}
					}
				}
				
				if(R[w+1][h+1] == 0 && G[w+1][h+1] == 0 && B[w+1][h+1] == 0){
					if(R[w][h+1] == 0 && G[w][h+1] == 0 && B[w][h+1] == 0){
						if(R[w+1][h] == 0 && G[w+1][h] == 0 && B[w+1][h] == 0){
							p4h = h;
							p4w = w;
						}
					}
				}
			}
		} 
	} 
	
	
	//��J�r��B�z 
	int enlarge = 4; 
	int shrink = 3;
	
    cout << "��" << endl; 
    cout << p1w << ", ";
    cout << p1h << endl;
    
    cout << p4w << ", ";
    cout << p4h << endl;
    
    //�p���Ϥ����e 
    int imageW = p4w - p1w + 1; 
    int imageH = p4h - p1h + 1;
    
    //�p��s�ϩ�j��|�I�y�� 
    int new_p1h = p1h - (imageH * enlarge - imageH) / 2;
    int new_p1w = p1w - (imageW * enlarge - imageW) / 2;
    int new_p4h = p4h + (imageH * enlarge - imageH) / 2;
    int new_p4w = p4w + (imageW * enlarge - imageW) / 2;
    
    
    int calw = enlarge;  //�e�׭p��� 
    int calh = enlarge;  //���׭p��� 
    int setp1w = p1w;
    
    //��j 
    for (h = new_p1h; h <= new_p4h; h++){
	    for (w = new_p1w; w <= new_p4w; w++){
	    	//�P�_�ӹ��I�O�_�n�ɤW��Ϭ۹������I�������� 
	    	if(calw == enlarge && calh == enlarge){
				r[w][h] = R[p1w][p1h];
		    	g[w][h] = G[p1w][p1h];
		    	b[w][h] = B[p1w][p1h];	
			}
			
			if(calw == 1)
				calw = enlarge;
			else
				calw--;
			
			//�ɭ�Ϲ�����p��(�e) 
			if(calw == enlarge && p1w <= p4w)
				p1w++;
				
		}
		
		p1w = setp1w;
		
		if(calh == 1)
			calh = enlarge;
		else
			calh--;
			
		//�ɭ�Ϲ�����p��(��)
		if(calh == enlarge && p1h <= p4h)
			p1h++;
	
	}
    
	//���u�ʤ��� 
	for (h = new_p1h; h <= new_p4h; h++){
	    for (w = new_p1w; w <= new_p4w; w++){
			if(calw == enlarge && calh == enlarge){	
				
			}else{
				if(calw != enlarge && calh != enlarge){	
					r[w][h] = r[w-(enlarge-calw)][h-(enlarge-calh)] * calw/enlarge * calh/enlarge +
								r[w-(enlarge-calw)][h+calh] * calw/enlarge * (enlarge-calh)/enlarge +
								r[w+calw][h-(enlarge-calh)] * (enlarge-calw)/enlarge * calh/enlarge +
								r[w+calw][h+calh] * (enlarge-calw)/enlarge * (enlarge-calh)/enlarge ;
					g[w][h] = g[w-(enlarge-calw)][h-(enlarge-calh)] * calw/enlarge * calh/enlarge +
								g[w-(enlarge-calw)][h+calh] * calw/enlarge * (enlarge-calh)/enlarge +
								g[w+calw][h-(enlarge-calh)] * (enlarge-calw)/enlarge * calh/enlarge +
								g[w+calw][h+calh] * (enlarge-calw)/enlarge * (enlarge-calh)/enlarge ;
					b[w][h] = b[w-(enlarge-calw)][h-(enlarge-calh)] * calw/enlarge * calh/enlarge +
								b[w-(enlarge-calw)][h+calh] * calw/enlarge * (enlarge-calh)/enlarge +
								b[w+calw][h-(enlarge-calh)] * (enlarge-calw)/enlarge * calh/enlarge +
								b[w+calw][h+calh] * (enlarge-calw)/enlarge * (enlarge-calh)/enlarge ;
				}
													                                                     
				if(calw == enlarge){                               
					r[w][h] = r[w-(enlarge-calw)][h-(enlarge-calh)] * calw/enlarge * calh/enlarge +
								r[w-(enlarge-calw)][h+calh] * calw/enlarge * (enlarge-calh)/enlarge ;
					g[w][h] = g[w-(enlarge-calw)][h-(enlarge-calh)] * calw/enlarge * calh/enlarge +
								g[w-(enlarge-calw)][h+calh] * calw/enlarge * (enlarge-calh)/enlarge ;
					b[w][h] = b[w-(enlarge-calw)][h-(enlarge-calh)] * calw/enlarge * calh/enlarge +
								b[w-(enlarge-calw)][h+calh] * calw/enlarge * (enlarge-calh)/enlarge ;
				}
				
				if(calh == enlarge){
					r[w][h] = r[w-(enlarge-calw)][h-(enlarge-calh)] * calw/enlarge * calh/enlarge +
								r[w+calw][h-(enlarge-calh)] * (enlarge-calw)/enlarge * calh/enlarge ;
					g[w][h] = g[w-(enlarge-calw)][h-(enlarge-calh)] * calw/enlarge * calh/enlarge  +
								g[w+calw][h-(enlarge-calh)] * (enlarge-calw)/enlarge * calh/enlarge ;
					b[w][h] = b[w-(enlarge-calw)][h-(enlarge-calh)] * calw/enlarge * calh/enlarge +
								b[w+calw][h-(enlarge-calh)] * (enlarge-calw)/enlarge * calh/enlarge ;
				} 
			}
			
			if(calw == 1)
				calw = enlarge;
			else
				calw--;
		}
		
		if(calh == 1)
			calh = enlarge;
		else
			calh--;
	}
	
	
		//���Y�p��y�� 
	int shrinkp1h = 128-((abs(new_p1h)+(128+383)/2)/shrink-128);
	int shrinkp1w = 128-((abs(new_p1w)+(128+383)/2)/shrink-128);
//	int shrinkp4h = new_p4h / shrink;
//	int shrinkp4w = new_p4w / shrink;
	if(shrink > 1){
		//LPF
		for (h = new_p1h; h <= new_p4h; h++){
	    	for (w = new_p1w; w <= new_p4w; w++){
		    	 r[h][w] = (r[h-1][w-1] + r[h-1][w] + r[h-1][w+1] +
							r[h][w-1] + r[h][w] + r[h][w+1] +
							r[h+1][w-1] + r[h+1][w] + r[h+1][w+1]) / 9; 
				
				 g[h][w] = (g[h-1][w-1] + g[h-1][w] + g[h-1][w+1] +
							g[h][w-1] + g[h][w] + g[h][w+1] +
							g[h+1][w-1] + g[h+1][w] + g[h+1][w+1]) / 9; 
							
				 b[h][w] = (b[h-1][w-1] + b[h-1][w] + b[h-1][w+1] +
							b[h][w-1] + b[h][w] + b[h][w+1] +
							b[h+1][w-1] + b[h+1][w] + b[h+1][w+1]) / 9; 
			}
		}
		
		int tmph = shrinkp1h;
		int tmpw = shrinkp1w;
		//�Y�p 
		for (h = new_p1h; h <= new_p4h; h+=shrink){
	    	for (w = new_p1w; w <= new_p4w; w+=shrink){
	    		if(w == new_p1w){
			    	ro[tmpw][tmph] = r[w][h];
			    	go[tmpw][tmph] = g[w][h];
			    	bo[tmpw][tmph] = b[w][h];
				}
			    else{
			    	ro[tmpw][tmph] = r[w][h];
			    	go[tmpw][tmph] = g[w][h];
			    	bo[tmpw][tmph] = b[w][h];
				}
	    		tmpw ++;
			}
			tmpw = shrinkp1w;
			tmph ++;
		}
	}
	else{
		for (h = 0; h < height; h++){
	    	for (w = 0; w < width; w++){
				ro[w][h] = r[w][h];
			    go[w][h] = g[w][h];
			    bo[w][h] = b[w][h];
			}
		}
	}
	
	
	/////////////////////////////////////
	cout << "��j" << endl; 
    cout << new_p1w << ", ";
    cout << new_p1h << endl;
    
    cout << new_p4w << ", ";
    cout << new_p4h << endl;
    
	cout << "�Y�p" << endl; 
    cout << shrinkp1h << ", ";
    cout << shrinkp1w << endl;
    
    
	save_bmp("new1.bmp", ro, go, bo); 
	printf("Job Finished!\n");

	close_bmp();

	system("PAUSE");
	return 0;
}

