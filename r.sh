#!/bin/bash

#Delete some un-needed files
rm *.o
rm result.txt output.txt

echo "Compile producer.cpp"
g++ -o producer.o producer.cpp -lrt

echo "Compile and link consumer.cpp Process.hpp Process.cpp"
g++ -o consumer.o Process.hpp Process.cpp consumer.cpp -lrt -lpthread

echo "Run producer object"
./producer.o 

echo "Run consumer object:"
./consumer.o
