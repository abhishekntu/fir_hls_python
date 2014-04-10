#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#define pi 3.141592653589793

using namespace std;

int main (int argc, char *argv[]) 
{	
	   
	int N=atoi(argv[1])+1;		//N = Filter Order + 1 			   
        						
	ifstream infile;
  	infile.open ("coeff_fixed.dat");//Opening Coeff.txt file to get fixed point coefficients
  	string coeff[500];
  	int i=0, j=0;	
  	while (infile.good())		//Storing these coefficients into an array "coeff"
  	{
		string c;
    		getline(infile,c);
    		coeff[i++]=c;
  	}   
    	infile.close();
	         
    
    	ofstream outfile;	
    	outfile.open ("filter.v");	//Generating verilog code for FIR filter
    
    	outfile<<"`timescale 1ns / 1ps"<<"\n";
    	outfile<<"module filter(input clk,input signed[15:0] in,output signed[15:0] yn0);"<<"\n"<<"\n";
    	outfile<<"reg signed[15:0] cobank[0:"<<N-1<<"];"<<"\n";
    	outfile<<"initial"<<"\n";
    	outfile<<"begin"<<"\n";  
    	cout<<"Generating filter coefficient bank for the filter......"<<"\n";
    	//Read character by character and coefficient bank generation
    
    	for(i=0;i<=N-1;i++){
        	outfile <<"cobank["<<i<<"]=16'h"<<coeff[i]<<";\n";
    	}
   
    	outfile<<"end"<<"\n"<<"\n";
    	//delay line declaration
    	outfile <<"reg signed[15:0] ";
    	for(int i=0;i<N;i++){  
            if(i!=10 && i%10==0){
            outfile <<"xn"<<i;                                 
            outfile <<";"<<"\n"<<"reg signed[15:0] ";
           
            }else if(i==N-1){
            outfile <<"xn"<<i<<";";
            }else{
            outfile <<"xn"<<i<<",";
            }                                  
    	} 
  
    	outfile <<"\n"<<"\n"<<"initial"<<"\n"<<"begin"<<"\n";
    	for(int i=0;i<N;i++){ 
            if(i!=10 && i%10==0){
            outfile <<"xn"<<i<<"=0;"<<"\n";
           
            }else{
            outfile <<"xn"<<i<<"=0;";
            }     
    	} 
    	cout<<"Generating delay line for the filter......"<<"\n";
    
    	outfile<<"\n"<<"end"<<"\n";
    	outfile <<"\n"<<"\n"<<"always@(posedge clk)"<<"\n"<<"begin"<<"\n"; 
    	outfile <<"xn0<=in;xn1<=xn0;";
    	for(int i=1;i<N-1;i++){  
            outfile <<"xn"<<i+1<<"<=xn"<<i<<";";
            if(i!=10 && i%10==0){
            outfile <<"\n";
            }                                  
    	}
    	outfile <<"\nend\n"; 
  
  
  	cout<<"Generating final output of the filter......"<<"\n";
    
  	outfile <<"\n"<<"\n"<<"wire signed[39:0] "<<"yn;"; 
  	outfile <<"\n"; 
  	outfile <<"\n"<<"assign yn"<<"=";
  	for(int j=N-1;j>=1;j--){
         	outfile <<"(xn"<<j<<"*cobank["<<j<<"])+";		 
  	}
  	outfile <<"(xn"<<j<<"*cobank["<<j<<"]);";  
  
  	outfile <<"\n"<<"assign yn0 = yn[30:15];";
  
  	cout<<"Verilog code generated......"<<"\n";
    
  	outfile <<"\n";
  	outfile <<"endmodule"<<"\n";
  	outfile.close();
            
    
    	return 0;
}
    
    
