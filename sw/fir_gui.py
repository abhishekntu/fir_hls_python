import os
import math
import sys
#-----------------------------------------------------
#function to convert hex from decimal
#-----------------------------------------------------
def tohex(val, nbits):
	return ((val + (1 << nbits))%(1 << nbits))
#-----------------------------------------------------
#command to generate coefficient file for n tap filter 
#-----------------------------------------------------
command = r'''./fir1 %s > coeff.dat''' % sys.argv[1]
os.system(command)
#-----------------------------------------------------
#converting coefficients to Q1.15 fixed point format  
#from floating point data stored in coeff.dat
#-----------------------------------------------------
inputfile = open('coeff.dat', 'r+')
coeff = inputfile.readlines()
coeff_hex = []
for data in coeff:
	temp_hex = "%x" % (tohex(int(round(float(data)*(2**15),0)),16)) 
	padded = temp_hex.zfill(4)
	coeff_hex.append(padded)	
inputfile.close()
#-----------------------------------------------------
#writing fixed point coefficients to coeff_fixed.dat 
#-----------------------------------------------------
outputfile = open('coeff_fixed.dat', 'r+')
for item in coeff_hex:
        outputfile.write("%s\n" % item)  
outputfile.close()
#-----------------------------------------------------
#generating filter RTL code 
#-----------------------------------------------------
command = r'''./filter_gen %s''' % sys.argv[1]
os.system(command)

