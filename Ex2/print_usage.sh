#!/bin/bash

cd ~/Rabin/Parallel_Programming



    export OMP_NUM_THREADS=10
    echo "−−−−−−−−−−−−−−−−−−"
    echo "Executed with 10 Threads"
    echo "−−−−−−−−−−−−−−−−−−"
    ./print_usage.x
