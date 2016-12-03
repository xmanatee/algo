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

#g++ -std=c++11 -O2 -Wall -Wno-unknown-pragmas -o $name $files

g++ -std=c++11 -O2 tests/maxflowtestgen.cpp -o q_gen
g++ -std=c++11 -O2 $files -DINICBLOCK -o q_dcflow
g++ -std=c++11 -O2 $files -o q_lcflow

echo "Just compiled =)"
for p in {1..1000000}
do
	./q_gen $1 $2 $p > f_test
	echo "generated test"

	time ./q_lcflow < f_test > f_lc_out
    echo "performed lc"

	time ./q_dcflow < f_test > f_dc_out
	echo "performed dc"



	if ["$(diff f_lc_out f_dc_out)" == ""]
	then
        cat f_lc_out
        cat f_dc_out
		echo "$p identical "
        echo ""
	else
		echo "found difference!!!"
		break
	fi
    rm f_*

done

rm q_*
rm *~
