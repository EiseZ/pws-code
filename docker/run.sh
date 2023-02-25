#!/bin/sh
for i in 1 2 3 4 5 6
do
    for j in 1 2 3 4 5 
    do
        pwd = $(pwd)
        echo "Generating PA: $i TS: $j"
        ln -fs /home/tim/Programming/pws-code/docker/constants/$i$j.hpp /home/tim/Programming/pws-code/simulation/inc/constants.hpp
        echo "Compiling PA: $i TS: $j"
        cd ../simulation
	    g++ -Wall -Wextra -Iinc -lstdc++ -lm -O3 -o ../docker/a.out src/*.cpp
        cd ../docker
        echo "Compiling Complete! PA: $i TS: $j"
        echo "Creating Docker Image PA: $i TS: $j"
        docker build -t pws:0.$i.$j .
        echo "Creating Docker Image Complete PA: $i TS: $j"
        mkdir -p ./mounts/$i/$j
        echo "Creating Docker Container PA: $i TS: $j"
        echo $pwd
        docker create -v /home/tim/Programming/pws-code/docker/mounts/$i/$j/:/output/ pws:0.$i.$j
        echo "Creating Docker Container Complete PA: $i TS: $j"
        echo "Removing output"
        rm ./a.out
    done
done
