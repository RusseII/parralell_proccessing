#include <typeinfo> 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <sstream>
using namespace std;










 
// Number of vertices in the graph
#define V 8
 
/* Define Infinite as a large enough value. This value will be used
  for vertices not connected to each other */
#define INF 99999
 
// A function to print the solution matrix
void printSolution(int dist[][V]);
 
// Solves the all-pairs shortest path problem using Floyd Warshall algorithm
void floydWarshall (int graph[][V])
{
    /* dist[][] will be the output matrix that will finally have the shortest 
      distances between every pair of vertices */
    int dist[V][V], i, j, k;
 
    /* Initialize the solution matrix same as input graph matrix. Or 
       we can say the initial values of shortest distances are based
       on shortest paths considering no intermediate vertex. */
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];
 
    /* Add all vertices one by one to the set of intermediate vertices.
      ---> Before start of a iteration, we have shortest distances between all
      pairs of vertices such that the shortest distances consider only the
      vertices in set {0, 1, 2, .. k-1} as intermediate vertices.
      ----> After the end of a iteration, vertex no. k is added to the set of
      intermediate vertices and the set becomes {0, 1, 2, .. k} */
    #pragma omp parallel 
    for (k = 0; k < V; k++)
    {
        // Pick all vertices as source one by one
        for (i = 0; i < V; i++)
        {
            // Pick all vertices as destination for the
            // above picked source
            for (j = 0; j < V; j++)
            {
                // If vertex k is on the shortest path from
                // i to j, then update the value of dist[i][j]
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
 
    // Print the shortest distance matrix
    printSolution(dist);
}
 
/* A utility function to print solution */
void printSolution(int dist[][V])
{
    printf ("Following matrix shows the shortest distances"
            " between every pair of vertices \n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf ("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

























int main(int argc, char *argv[]) 
{
  int rank, size;
  int i=1;
  int cities=1;
  int city_matrix[V][V];
//#pragma omp parallel for
 for (int i = 0; i < V; ++i)
    { 
        for (int j = 0; j < V; ++j)
        {
            city_matrix[i][j]=INF;
            if (i==j)
              city_matrix[i][j]=0;          
            std::cout << city_matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }
   // int cities=1;

    
 ifstream infile("nqmqSmall.dat");


  if (infile.good())
  {
    string sLine;
    getline(infile, sLine);
    int cities=atoi(sLine.c_str());   
    string city_refrence[cities+1];

    while (i<cities+1)
    {
      if (infile.good())
      {
        getline(infile, sLine);
        city_refrence[i]=sLine;
        cout <<i<<" "<< city_refrence[i] << endl;
        i++;
      }
    }
    while (i<100)
    {

      i++;
      getline(infile,sLine);
        istringstream iss(sLine);
      int j=0;
      int temp_string[3];
      while (iss) 
      { 
        string subs; 
        iss >> subs; 
       
        if (j<3)
        {
          temp_string[j]=atoi(subs.c_str());
           cout << "Substring: " << subs << endl;
        }
        j++;
      }
      
      if(city_matrix[temp_string[0]][temp_string[1]]==INF)
      {
        city_matrix[temp_string[0]][temp_string[1]]=temp_string[2];
        city_matrix[temp_string[1]][temp_string[0]]=temp_string[2];
      }
      else
        cout<<  "############################################################yacity_matrix[temp_string[0]][temp_string[1]]";
      //cout<<temp_string[0]<<"##################";
      if (infile.eof())
        break;
     // cout<<sLine<<endl;
    }
    infile.close();
  }
 for (int i = 0; i < V; ++i)
    {
        for (int j = 0; j < V; ++j)
        {
            std::cout << city_matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }
floydWarshall(city_matrix);
    return 0;
}


    //FILE *fp;
    //char buff[255];

        // //Read the team names and save them
        // int cities = 0;
        // //fp = fopen("nqmqSmall.dat", "r");
        // //fscanf(fp, "%d", &cities);
        // string citiesNames[cities];
        
        // ifstream file ("nqmqSmall.dat"); 
        // string temp;
        // i=0;
        // while(getline(file, temp)) {
        //     //cout<<typeid(temp).name()<<"          "<<typeid("wowwtf").name()<<endl;
        // if (typeid(temp).name()==typeid("string").name()){
        // citiesNames[i]=temp;
        // //cout<<citiesNames[i];
        // i++;
    //}
    //  }     
    	// for(i = 0; i <= cities+1; i++) {
     //            fgets(buff, 255, (FILE*)fp);
                
     //            if (i!=0)
     //            {
     //                citiesNames[i]=buff;
     //                cout<<i<<" "<<citiesNames[i]<<endl;
     //        }   }


        //fclose(fp);

      //  for(i = 1; i<= cities; i++) {
      //      cout<<(citiesNames[i]);
        //}

