rm -rf coeff.dat coeff_fixed.dat filter.v
touch coeff_fixed.dat
g++ -o fir1 src/fir1.cpp
g++ -o filter_gen src/filter_gen.cpp
python fir_gui.py $1
mkdir temp
mv coeff.dat temp/coeff.dat
mv coeff_fixed.dat temp/coeff.dat
mv fir1 temp/fir1
mv filter_gen temp/filter_gen
mkdir solution
mv filter.v solution/filter.v
