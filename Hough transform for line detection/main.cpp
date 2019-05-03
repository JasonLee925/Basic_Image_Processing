#include <iostream>
#include <stdlib.h>
#include "bmp.h"
#include <cmath>
#include <string>

using namespace std;

int R[MaxBMPSizeX][MaxBMPSizeY];
int r[MaxBMPSizeX][MaxBMPSizeY];
int g[MaxBMPSizeX][MaxBMPSizeY];
int b[MaxBMPSizeX][MaxBMPSizeY];
int e[MaxBMPSizeX][MaxBMPSizeY];
int ht[MaxBMPSizeX][MaxBMPSizeY];
int g1[MaxBMPSizeX][MaxBMPSizeY];
int g2[MaxBMPSizeX][MaxBMPSizeY];
unsigned int pt = 0; //p�B�⤸ 
int width = 0, height = 0;
int x, y;
int h, w;
unsigned int d; //d:���׹B�⤸
unsigned int c;
int countS[180] = {0};
unsigned int countmax[180] = {0};

int s[180][MaxBMPSizeX*MaxBMPSizeY]; //�����b�C���I,�C�Ө��פ��p�⪺�� s[����(0~180)][�����I]
int p[MaxBMPSizeX][MaxBMPSizeY];

int voteCount[10];
int voteD[10];
int voteS[10];

//��t���� 
void basicEdgeDet(){
	open_bmp("house24.bmp", R, R, R, width, height); 
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
	       		e[w][h]= 255;
	       	else
	       		e[w][h]= 0;
	    }
    }
    
//	save_bmp("edge.bmp", e, e, e); 
}

//�M�䨤��d�b�C�Ӧ�mpt���As[d][pt]�X�{������ 
int count(int d, int w, int h, int fh, int fw) {
	int c = 0;
	int cmax = 0;
	
	for (fh = 0; fh < height; fh++){
		for(fw = 0; fw < width; fw+=1){
			if(e[fw][fh]==0)
				continue;
				
			if(s[d][p[w][h]] == s[d][p[fw][fh]] && p[w][h]!=p[fw][fh])
    			c++;
    
    		if(c>cmax)
    			cmax = c;
		}
	}
	
	return cmax;
}

// sin(����) 
float sinc(double degree){
	double dd = degree*3.14159/180;
  	return sin(dd);
}

// cos(����)
float cosc(double degree){
	double dd = degree*3.14159/180;
  	return cos(dd);
}

int main(int argc, char *argv[])
{
	//��t���� 
	basicEdgeDet();
	
	//�إ�s�� 
	cout << "�ت�...."; 
    for (h = 0; h < height; h++){
		for (w = 0; w < width; w++){
			for(d = 0; d <= 180; d++){
				if(e[w][h] == 255){
					x = w*cosc(d);
					y = h*sinc(d);
					s[d][pt] = x+y;
				}
			}
	
			pt++;
	    }
    }
    
    //  ����pt�A�ت��O��p[][]�����C����ƪ���m 
    int i = 0;
    for (h = 0; h < height; h++){
		for (w = 0; w < width; w++){
			p[w][h] = 0; 
			p[w][h] +=i;
    		i++;
		}
	}
	
    cout << "(�ت���)"<<endl; 
    
    //1. �j�M�C�Ө��ץX�{S�Ȫ��̰����Ƥ�s��
	//2. �벼 
    cout << "�벼��...."<<endl; 
    for(d = 0; d <= 180; d+=1){
    	countmax[d] = 0;
    	countS[d] = 0;
    	
    	for (h = 0; h < height; h++){
			for (w = 0; w < width; w+=1){
				if(e[w][h] == 0)
					continue;
						
				c = count(d, w, h, 0, 0);
	    		if(c > countmax[d]){
	    			countmax[d] = c;
	    			countS[d] = s[d][p[w][h]];
				}
			}
		}
    	
		cout << "����:" << d <<", �X�{�̦h����s��:" << countS[d] << ", �X�{����:" << countmax[d]<< endl;
		
		for(int i=0; i<10; i++){
			if(countmax[d] < voteCount[i])
				continue;
			
			if(countmax[d] > voteCount[i]){
				for(int ii = 9; ii>=i; ii--){
					voteCount[ii+1] = voteCount[ii];
					voteD[ii+1] = voteD[ii];
					voteS[ii+1] = voteS[ii];
				}
				
				voteCount[i] = countmax[d];
				voteD[i] = d;
				voteS[i] = countS[d];
				break;
			}
			
		}
	}

	
    cout << "(�벼����)"<<endl; 
    
    cout << "�벼���G�G"<<endl;
	for(int i=0; i<10; i++){
		cout<<"����:"<<voteD[i]<<", S��:"<<voteS[i]<<" => �X�{����:"<<voteCount[i]<<endl; 
	}
	
	//�e�u 
	for (h = 0; h < height; h++){
		for (w = 0; w < width; w++){
			if(e[w][h]==0)
				continue;
			
			for(int i=0; i<10; i++){
				for(d = 0; d<180; d+=1){
					if(voteD[i] != d)
						continue;
					if(voteS[i] != s[d][p[w][h]])
						continue;
						
					ht[w][h]= 255;
				}
			}
		}
	}

	for (h = 0; h < height; h++){
		for (w = 0; w < width; w++){
			if(ht[w][h] == 255){
				r[w][h] = 0;
				g[w][h] = 255;
				b[w][h] = 0;
			}
			else{
				r[w][h] = R[w][h];
				g[w][h] = R[w][h];
				b[w][h] = R[w][h];
			}
		}
	}
	

	// �x�s�B�z���G�ܷs�����ɤ�
	save_bmp("new1.bmp", r, g, b); 
	printf("�n�F�աI\n");

	// ���� bmp �v������
	close_bmp();

	system("PAUSE"); 
	return 0;
}


