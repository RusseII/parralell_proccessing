#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void delay(int sec)
{
    clock_t goal_time=sec+clock();
    while (goal_time>clock());
}

int main( int argc, char *argv[] )
{
    srand(time(NULL));
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    bool throw=true;
    int potato=0;
    int temp;

    if (rank == 0)
    {
        potato = (rand() % 20) +5+ size;
        printf("Potato: %d\n\n", potato);
        temp = rand() % size;
        MPI_Send(&potato, 1, MPI_INT, temp, 0, MPI_COMM_WORLD);
        printf("Sending the potato to: %d \n\n", temp);
    }   
     while (throw) 
     {
        MPI_Recv(&potato, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE); 
        potato--;
        if (potato!=0)
        {
            temp= rand()%size;
            MPI_Send(&potato, 1, MPI_INT, temp, 0, MPI_COMM_WORLD);
            printf("Thrown to procces:%d with potato of: %d\n", temp, potato);
            delay(1000000);
        }

        else 
        {
            throw = false;
            printf("GAME OVER\n");
            
            MPI_Abort(MPI_COMM_WORLD, -1);
        }
    
        


    }

    MPI_Finalize();
    return 0;
}

