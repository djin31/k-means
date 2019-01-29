#!/bin/bash
if [[ $1 = "omp" ]]; then
	rm -f omp.out
	g++ -fopenmp  k_means_openmp.cpp -o omp.out
elif [[ $1 = "seq" ]]; then
	rm -f seq.out
	g++ k_means_seq.cpp  -o seq.out
fi