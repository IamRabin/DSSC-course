#!/bin/bash
cd ~/Rabin/Parallel_Programming

module load openmpi


N=100000000
reps=5

echo "Running MPI Pi approximation with N=${N}"
for np in 1 2 4 8 16 20 ; do
	for i in $(seq 1 $reps); do
		time =$((${time}+$(mpirun -np ${np} mpi_reduce ${N} | grep "Elapsed_time" ))
	done
	avg_time=${time}/5
	echo ${np} ${avg_time} >> result.txt
done

exit
