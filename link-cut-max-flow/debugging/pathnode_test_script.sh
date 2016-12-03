#!/bin/bash

name="pathnodetest"

files="$name.cpp"
files="$files"

for i in linkcut/*.cpp
do
    files="$files $i"
done

g++ -std=c++11 -O3 tests/pathnodetestgen.cpp -o q_g
g++ -std=c++11 -O3 $files -o q_pn


echo "COMPILED"


echo "gen : "
time ./q_g $1 $2 $3 > f_pn_test

echo ""
echo "pn : "
time ./q_pn< f_pn_test > f_pn_out

rm f_*

#rm q_*
rm *~
