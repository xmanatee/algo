#!/bin/bash

name="maxflowtest"

files="$name.cpp"
files="$files linkcutflowblocker.h linkcutflowblocker.cpp"
for i in linkcut/*.cpp
do
    files="$files $i"
done
for i in graph/*.cpp
do
    files="$files $i"
done

g++ -std=c++11 -O3 $files -o q_dcflow
g++ -std=c++11 -O3 $files -DLINKCUTBLOCK -o q_lcflow


echo "COMPILED"


echo "lc : "
time ./q_lcflow < $1 > f_lc_out

echo ""
echo "dc : "
time ./q_dcflow < $1 > f_dc_out

if ["$(diff f_lc_out f_dc_out)" == ""]
then
    cat f_lc_out
    cat f_dc_out
    echo "$p identical "
    echo ""
else
    echo "found difference!!!"
    exit
fi
rm f_*

rm q_*
rm *~
