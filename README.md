# k-means

Parallelized k-means implementation in C++ using OpenMP and pthreads. 

k-means is an important unsupervised clustering algorithm with significant scope for parallelization. This implementation tries to exploit this parallelism using OpenMP and pthreads, and also compare their performances.

## How to setup the test
* Use `gen_data.py` to generate a testcase for the k-means algorithm. The script accepts number of clusters as input and produces files test(number of clusters).txt, solution(number of clusters).txt and a visual plot of data points.
	Different parameters such as number of points per cluster, range of coordinates, range of deviation of points from cluster centroid can be modified in the script.
* Compile all the implementation versions using `compile.sh` to get `seq.out`,`omp.out` and `pth.out` for sequential, openmp and pthread versions.
* Run the different binaries as
	```
	./[executable] testfile.txt > outfile.txt
	```
* Run `python graphing.py outfile.txt` to visualise the outputs.

#### Note
All the implementations shall produce the same output results since randomization seed and code has been setup in such a way.

## Observations
With 2 threads for OpenMP and Pthreads:
Runtime OpenMP < Runtime Pthreads ≤	Runtime Sequential