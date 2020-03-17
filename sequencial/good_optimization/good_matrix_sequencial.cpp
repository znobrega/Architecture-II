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

void Sequencial()
{

  static double a[10000][10000], b[10000][10000], c[10000][10000];

  clock_t start = clock();
  double timeTotal;

  int i, j, k;
  for (i = 0; i < matrixLength; i++)
  {
    for (j = 0; j < matrixLength; j++){
      a[i][j] = pow(i, j) / (sin(i) + cos(j));
      b[i][j] = sqrt(i + j);
    }
  }

  for(k =0; k < force; k++)
  for (i = 0; i < matrixLength; i++){
    for (j = 0; j < matrixLength; j++){
      c[i][j] = sin(a[i][j] * b[i][j]) / (i + j);
    }
  }

  clock_t stop = clock();
  double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
    finalTime = elapsed;
  std::cout << elapsed << std::endl;
}

void clearCache()
{
  unsigned long cls[6144];

  for (long i = 0; i < 6144; i++)
  {
    cls[i] = 0;
  }
}

int main()
{
	std::cout << "Good Sequencial: ";
	Sequencial();

  std::fstream fs;
  fs.open ("good_matrix_sequencial.csv", std::fstream::in | std::fstream::out | std::fstream::app);

  if (fs.is_open())
  {
    fs << finalTime << "\n";
  }else
  {
    cout << "Was not possible find the file.";
  }
	clearCache();
}
