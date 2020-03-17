#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <ctime>
#include <chrono>
#include <iostream>
#include <fstream>
using namespace std;

static int matrixLength = 10000;
static int force = 10;
float finalTime;

void Parallel() {

  static double a[10000][10000], b[10000][10000], c[10000][10000];
	int i, j, k;

	auto t1 = std::chrono::high_resolution_clock::now();

	#pragma omp parallel default(none) shared(matrixLength, a, b, c, force) private(i, j, k)
	{
		#pragma omp for
		for (i=0; i<matrixLength; i++){
			for(j = 0; j < matrixLength; j++){
				a[i][j] = pow(i, j)/(sin(i)+cos(j));
				b[i][j]	= sqrt(i+j);
      }
		}

		#pragma omp for nowait
    for(k =0; k < force; k++)
		for (i = 0; i < matrixLength; i++)
			for (j = 0; j < matrixLength; j++){
				c[i][j] = sin(a[i][j] * b[i][j])/(i+j);
      }
	}

	  auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = (std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count());

    float time = (float)duration/1000000;
    finalTime = time;

    std::cout << time << " SECONDS." << std::endl;
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

  std::fstream fs;
  fs.open ("good_matrix_parallel.csv", std::fstream::in | std::fstream::out | std::fstream::app);

  if (fs.is_open())
  {
    fs << finalTime << "\n";
  }else
  {
    cout << "Was not possible find the file.";
  }
	clearCache();
}
