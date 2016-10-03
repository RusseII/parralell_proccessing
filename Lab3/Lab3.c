#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main( int argc, char *argv[] )
{
    srand(time(NULL));
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
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

     while (potato!=-1) 
     {
        MPI_Recv(&potato, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE); //reciev 
        if (potato==-1)
            break;
        potato--;
        if (potato>0)
        {
            temp= rand()%size;
            MPI_Send(&potato, 1, MPI_INT, temp, 0, MPI_COMM_WORLD);//send to random proccess 
            printf("Thrown to procces:%d with potato of: %d\n", temp, potato);
        }
        
        else if(potato==0)
        {
            int stop=(-1);
            potato=-1;
            int i;
            printf("GAME OVER\n");
            for (i=0; i<size; i++)//for loop to end all the processes 
            MPI_Send(&stop, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
    return 0;
}

