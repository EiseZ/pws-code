#!/bin/sh
for i in 1 2 
do
    pwd = $(pwd)
    echo "Generating #$i"
    echo "Compiling #$i"
    cd ../simulation
	gcc -Wall -Wextra -Iinc -lstdc++ -lm -O3 -o ../docker/a.out src/*.cpp
    cd ../docker
    echo "Compiling Complete! #$i"
    echo "Creating Docker Image #$i"
    docker build -t pws:0.0.$i .
    echo "Creating Docker Image Complete #$i"
    mkdir ./mounts/$i/
    echo "Creating Docker Container #$i"
    echo $pwd
    docker create -v /storage/Programming/pws-code/docker/mounts/$i/:/output/ pws:0.0.$i
    echo "Creating Docker Container Complete #$i"
    echo "Removing output"
    rm ./a.out
done
