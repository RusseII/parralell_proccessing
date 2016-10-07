#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int factorial(int n)
{
    int result = 1;
    for(int i = 2; i<=n; ++i) 
        result *= i;
    return result;
}

int main(int argc,char *argv[])//must pass argument or you get seg fault
{
    int rank,size,x;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    x = atoi(argv[1]); //converts string to int
    double sum,part_sum,final_value;
    part_sum = (pow(x,rank+2)/factorial(rank+2));
    MPI_Reduce(&part_sum,&sum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    if (rank==0)//master
    {
        final_value=1+x+sum;//exp(x)
        printf("Answer:%.5f",final_value);
    }
    MPI_Finalize();
    return 0;

}