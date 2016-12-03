name="$1"

rm -f $name

files="linkcutflowblocker.h linkcutflowblocker.cpp $name.cpp"

for i in linkcut/*.cpp
do
    files="$files $i"
done

for i in graph/*.cpp
do
    files="$files $i"
done

g++ -std=c++11 -O2 -Wall -Wno-unknown-pragmas -o $name $files

