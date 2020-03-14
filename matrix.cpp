#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <ctime>
#include <chrono>
#include <iostream>



static long N = 500;
static int K = 10000;

double step;

void Sequencial(){

	double a[N][N], b[N][N];	

	clock_t start = clock();
  	double timeTotal;
	
	int i, j, k;
	for (i=0; i<N; i++){
		for(j = 0; j< N; j++)
			a[i][j] = i;
			b[i][j]	= j;		
	}

	for(k =0; k<K; k++)
	for (i = 0; i < N-2; i++)
		for (j = 0; j < N-2; j++)
			b[i][j] = cos(a[i][j]);
	

	clock_t stop = clock();
  	double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
  	std::cout << elapsed << std::endl;
	
}

void SlowSequencial(){

	double a[N][N], b[N][N];	

	clock_t start = clock();
  	double timeTotal;
	
	int i, j, k;
	for (i=0; i<N; i++){
		for(j = 0; j< N; j++)
			a[i][j] = i;
			b[i][j]	= j;		
	}

	for(k =0; k<K; k++)
	for (i = 0; i < N-2; i++)
		for (j = 0; j < N-2; j++)
			b[j][i] = cos(a[j][i]);
	

	clock_t stop = clock();
  	double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
  	std::cout << elapsed << std::endl;
	
}

void Parallel() {
		double a[N][N], b[N][N];	
	
	int i, j, k;
	
	auto t1 = std::chrono::high_resolution_clock::now();
    

	#pragma omp parallel default(none) shared(N,a,b, K) private(i, j, k)
	{
		#pragma omp for
		for (i=0; i<N; i++){
			for(j = 0; j< N; j++)
				a[i][j] = i;
				b[i][j]	= j;		
		}

		#pragma omp for nowait
		for(k =0; k<K; k++)
		for (i = 0; i < N-2; i++)
			for (j = 0; j < N-2; j++)
				b[i][j] = cos(a[i][j]);
	}
	

	auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = (std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count());

    float time = (float)duration/1000000;

    std::cout << time << " segundos." << std::endl;
}

void SlowParallel() {
	double a[N][N], b[N][N];	
	
	int i, j, k;
	
	auto t1 = std::chrono::high_resolution_clock::now();
    

	#pragma omp parallel default(none) shared(N,a,b, K) private(i, j, k)
	{
		#pragma omp for
		for (i=0; i<N; i++){
			for(j = 0; j< N; j++)
				a[i][j] = i;
				b[i][j]	= j;		
		}

		#pragma omp for nowait
		for(k =0; k<K; k++)
		for (i = 0; i < N-2; i++)
			for (j = 0; j < N-2; j++)
				b[j][i] = cos(a[j][i]);
	
	} 
	

	auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = (std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count());

    float time = (float)duration/1000000;

    std::cout << time << " segundos." << std::endl;

}

void clearCache() {
	unsigned long cls[6144];

	for (long i = 0; i<6144; i++) {
		cls[i] = 0;
	}
}

int main (){

	std::cout << "Parallel: ";
	Parallel();
	
	clearCache();

	std::cout << "SlowParallel: ";
	SlowParallel();

	clearCache();

	std::cout << "Sequencial: ";
    Sequencial();

	clearCache();

	std::cout << "SlowSequencial: ";
    SlowSequencial();

	std::cout << "fim: \n";
	
}