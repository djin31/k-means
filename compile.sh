#!/bin/bash
if [[ $# -eq 0 ]]; then
	rm -f *.out
	g++ -fopenmp k_means_seq.cpp -o seq.out
	g++ -fopenmp k_means_openmp.cpp -o omp.out
	g++ -fopenmp k_means_pthreads.cpp -o pth.out
else
	if [[ $1 = "omp" ]]; then
		rm -f omp.out
		g++ -fopenmp -O3 k_means_openmp.cpp -o omp.out
	elif [[ $1 = "seq" ]]; then
		rm -f seq.out
		g++ -fopenmp -O3 k_means_seq.cpp -o seq.out
	elif [[ $1 = "pth" ]]; then
		rm -f pth.out
		g++ -fopenmp -O3 k_means_pthreads.cpp -o pth.out
	fi
fi

