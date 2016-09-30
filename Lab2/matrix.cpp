#include <iostream>
#include <array>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

short** make_array(unsigned size)
{
	short** array=0;
	array= new short*[size];
	for (int i=0; i<size; i++)
		{
			array[i]=new short[size];
		for (int j=0; j<size; j++)
			array[i][j]=1;
		}
	return array;
}

int main()
{
	int matrix_size=1024;
	short** A=make_array(matrix_size);
	short** B=make_array(matrix_size);
	short** C=make_array(matrix_size);
	int block_size=2048;

struct timeval start, end;

gettimeofday(&start,NULL);

for (int k = 0; k < matrix_size; k += block_size)
	for (int j = 0; j < matrix_size; j += block_size)
		for (int i = 0; i < matrix_size; i++)
			for (int jj = j; jj < min(j + block_size, matrix_size); jj++)
				for (int kk = k; kk < min(k + block_size, matrix_size); kk++)
					C[i][jj] = C[i][jj] + A[i][kk] * B[kk][jj];

gettimeofday(&end,NULL);

  cout<<("%ld\n", ((end.tv_sec * 1000000 + end.tv_usec)
		  - (start.tv_sec * 1000000 + start.tv_usec)));
}