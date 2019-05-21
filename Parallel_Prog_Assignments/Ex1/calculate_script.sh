#!/bin/bash

cd ~/Rabin/Parallel_Programming

make OMP_Exercise_1.c

for thread in 1 2 4 8 16 20
do
    export OMP_NUM_THREADS=${thread}
    echo "−−−−−−−−−−−−−−−−−−"
    echo "Threads = ${thread}"
    echo "−−−−−−−−−−−−−−−−−−"
    ./calcu_pi.x 1000000000
done

exit
