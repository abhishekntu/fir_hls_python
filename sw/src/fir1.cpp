#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#define pi 3.141592653589793

using namespace std;

//Function for generating floating point coefficients
float* fir1(int N, float *w){
       int alpha=(N-1)/2; 
       float *arr1,*arr2,*arr,*wind,*h;
       arr1=(float*)calloc(N+1,4);
       arr2=(float*)calloc(N+1,4);
       arr=(float*)calloc(N+1,4);
       wind=(float*)calloc(N+1,4);
       h=(float*)calloc(N+1,4);
       for(int i=-alpha;i<=alpha;i++){
         if(i!=0){   
                     arr1[i+alpha]=sin(w[0]*pi*i)/(pi*i);
                     arr2[i+alpha]=sin(w[1]*pi*i)/(pi*i);
         }else{
                     arr1[i+alpha]=w[0];
                     arr2[i+alpha]=w[1];
         }            
       }
        
        for(int j=0;j<N;j++){
                arr[j]=arr2[j]-arr1[j];
        }
        for(int k=0;k<N;k++){
                wind[k]=(54 - 46*cos(2*pi*k/(N-1)))/100;   
        }
        float y1=0,y2=0,y,x=0.0;
        float val=(w[0]+w[1])/4;
        for(int i=0;i<N;i++){
            h[i]=arr[i]*wind[i]; 
            y1+=cos(2*pi*i*val)*h[i];
            y2+=sin(-2*pi*i*val)*h[i];
        }
        y=sqrt(y1*y1+y2*y2);
        for(int i=0;i<N;i++){
            h[i]=(h[i]/y);            
        }
        return(h);

}

int main (int argc, char *argv[]) {	
	int N = atoi(argv[1]) + 1;	
	float *h;
    	h=(float*)malloc(N+1);
    
    	float *w;
    	w=(float*)malloc(2);
    
	//Fixed cut off frequency
	w[0]=0.39;  
	w[1]=0.41;

	h = fir1(N,w);
	
	for(int i=0;i<N;i++){
		cout<<h[i]<<endl;
	}	
	
	return 0;
}
    
    
