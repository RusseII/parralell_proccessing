  //Russell Ratcliffe
    #include <mpi.h>
    #include <stdio.h>
    #include <stdlib.h>

    int SIZE=40;
    int PROCESSORS=9;
    int GAMES=10;
    int STATS=4;

    void split_arrays(int team, int scores[SIZE][STATS], int teams_score[GAMES][STATS]) 
    {
       int i,j,count=0;
       
       for(i = 0; i<SIZE; i++) 
       {
            if(scores[i][0]==team || scores[i][1]==team  ) 
            {
                for(j=0; j<STATS; j++) 
                {
                    teams_score[count][j]=scores[i][j];
                }
                count++;
            }  
       }
    }

    void init_array(float master_array[PROCESSORS])
    {
        int i=0;
        for (i=0; i<PROCESSORS; i++)
            master_array[i]=100;
    }

    int main(int argc,char *argv[]) 
    {
       
        int score[GAMES][STATS],teams_score[GAMES][STATS],scores[SIZE][STATS];
        int i,rank,size,j;
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        float power_rank,num,sum=0;
        float master_array[PROCESSORS];
        init_array(master_array);
        int opponent=0;
        FILE *fp;

        if (rank==0) //init
        {
            fp = fopen("xfl.dat","r");
            for(i = 0; i<SIZE; i++) 
            {
                fscanf(fp,"%d %d %d %d",&scores[i][0],&scores[i][1],&scores[i][2],&scores[i][3]);       
            }
            fclose(fp);

            for(i=1; i<PROCESSORS;i++)
            {
                split_arrays(i,scores,teams_score);  
                MPI_Send(teams_score,SIZE,MPI_INT,i,i,MPI_COMM_WORLD);
            }
        }
        
        else //init
        {
            MPI_Recv(score,SIZE,MPI_INT,0,rank,MPI_COMM_WORLD,MPI_STATUS_IGNORE); 

            for(i=0; i<GAMES; i++) 
            {
                if (score[i][1] == rank) 
                {
                    opponent = score[i][0];
                    num += master_array[opponent];
                    sum = sum + score[i][3] - score[i][2];
                }
                else
                {
                    opponent = score[i][1];
                    num+=master_array[opponent];
                    sum = sum + score[i][2] - score[i][3];
                    
                }
            }
            power_rank=(sum+num)/GAMES;
            num+=master_array[opponent];
            MPI_Gather(&power_rank,1,MPI_FLOAT,master_array,1,MPI_FLOAT,0,MPI_COMM_WORLD);
        }
        
        

        for (j=0; j<GAMES; j++)
        {
            if (rank==0)
            {
                for(i = 0; i<PROCESSORS; i++)
                {
                    printf("%.2f        ", master_array[i]);
                }
                printf("\n");
                MPI_Gather(&power_rank,1,MPI_FLOAT,master_array,1,MPI_FLOAT,0,MPI_COMM_WORLD);
                MPI_Bcast(master_array,PROCESSORS,MPI_FLOAT,0,MPI_COMM_WORLD);
            }

            else 
            {
                sum = 0;
                num = 0;
                MPI_Bcast(master_array,PROCESSORS,MPI_FLOAT,0,MPI_COMM_WORLD);
                for(i=0; i<GAMES; i++) 
                {
                    if (score[i][0]==rank) 
                    {
                        opponent=score[i][1];
                        num+=master_array[opponent];
                        sum+=score[i][2]-score[i][3];
                    }
                    else 
                    {
                        opponent=score[i][0];
                        num+=master_array[opponent];
                        sum+=score[i][3]-score[i][2];
                    }
                }
                power_rank=(num+sum)/GAMES;
                MPI_Gather(&power_rank,1,MPI_FLOAT,master_array,1,MPI_FLOAT,0,MPI_COMM_WORLD);
            }
            
        }
        MPI_Finalize();
        return 0;
    }
