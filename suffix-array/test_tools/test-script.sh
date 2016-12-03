#!/bin/bash

g++ -std=c++11 -O2 strgen.cpp -o q_g
g++ -DFOR_TESTS -std=c++11 -O2 main.cpp -o q_a
g++ -std=c++11 -O2 copicat.cpp -o q_b

echo "Just compiled =)"
for p in {1..1000000}
do
	./q_g $1 $p > f_test
	echo "generated test"

	time ./q_a < f_test > f_a_out
    echo "performed a"

	time ./q_b < f_test > f_b_out
	echo "performed b"



	if ["$(diff f_a_out f_b_out)" == ""]
	then
		wc f_a_out
        #cat f_a_out
        #cat f_b_out
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
