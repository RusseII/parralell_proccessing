//Russell Ratcliffe
//Lab6

#include <typeinfo> 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string>
#include <iostream>     // cout
#include <fstream>      // ifstream
#include <sstream>
#include <sys/time.h>
#include <math.h>
#include <omp.h>
//#include <fopenmp>
using namespace std;
class position
{
	public:
	 double x,y,vx,vy,m,ax,ay; 
	 position()
	 {
	 	x,y,vx,vy,ax,ay=0;
    m=1;
	 }
  void operator = (const position &other)
  {
    x=other.x;
    y=other.y;
    vx=other.vx;
    vy=other.vy;
    y=other.y;
    m=other.m;
    ax=other.ax;
    ay=other.ay;
  }
};

position find_distance(position node_i, position node_j)
{
  position distance;
  distance.x=node_j.x-node_i.x;
  distance.y=node_j.y-node_i.y;
  return distance;
}

position fill_class(position xy[],int SIZE)
{
  int i=0;
  ifstream infile("nbodies.dat");
  if (infile.good())
  {
  
    string sLine;
    getline(infile, sLine);
    //position temp;
    int temp=atoi(sLine.c_str());

    //string city_refrence[cities+1];

    position temp2;
    double cord;
    while (i<SIZE)
    {

      
      getline(infile,sLine);
        istringstream iss(sLine);
      int j=0;
      int temp_string[3];
      while (iss) 
      { 
        string subs; 
        iss >> subs; 
       
        if (j==0)
        {

        cord=stod(subs.c_str());
      temp2.x=cord;
          //temp_string[j]=atoi(subs.c_str());
            //cout << "Substring x: " << subs << endl;
        }
        if (j==1)
        {
          cord=stod(subs.c_str());
          temp2.y=cord;
          //cout << "Substring y: " << subs << endl;  
        } 

        xy[i]=temp2;
        j++;
      }
      i++;
    }
  }
  //return xy;
}

void find_accel(position xy[],int SIZE)
{
  int j,i;
// #pragma omp parallel for private(i)
  for (j=0; j<SIZE; j++)
  {
    //Start a loop for 100 times to do each calulateion
      //syn
      //do the new calulcatio for all of accelleration and 
      //  position and velocity
      
    position accel;
    position temp;
    double accel_num_x,accel_num_y,accel_den_y=0;
    double accel_den_x=0;
    double num_x,num_y=0;
    for (i=0; i<SIZE; i++)
    {
      if (j!=i)
      {
        temp=find_distance(xy[j],xy[i]);
        if (abs(temp.x)>.1 || abs(temp.y)>1)
        {
          accel_num_x=(xy[i].m*temp.x);
          accel_num_y=(xy[i].m*temp.y);
          accel_den_x=pow(abs(temp.x),3.0);
          accel_den_y=pow(abs(temp.y),3.0); 
            cout<<accel_num_x<<" NUM"<<endl;
                    cout<<accel_den_x<<" DENOM"<<endl;
 
          num_x=(accel_num_x/accel_den_x)+num_x;
          num_y=(accel_num_y/accel_den_y+num_y);
          //cout<<num_x<<endl;
        }
      }



    }

    //return accel.a;
   // cout<<num;
   // cout<<num_x<<endl;
    xy[j].ax=num_x; //#TODO MULTIPLY BY m1####
    xy[j].ay=num_y;//#@#@##@##@##
  }
  //return xy;
}

void new_position(position xy[],int SIZE, position new_array[])
{


  double t=.01;
  double new_vy,new_vx,new_x,new_y=0;
 // 
  for (int i=0; i<SIZE; i++)
  {
    //cout<<xy[i].ax<<endl;
    new_vx=(xy[i].vx)+t*(xy[i].ax);
    new_vy=(xy[i].vy)+t*(xy[i].ay);
    new_x=(xy[i].x+t*(new_vx));
    new_y=(xy[i].y+t*(new_vy));
    //TODO STORE THIS IS NEW ARRAY OF POSITIONS
    for (int k=0; k<SIZE; k++)
    {
      new_array[k]=xy[k];
    }
    new_array[i].vx=new_vx;
    new_array[i].vy=new_vy;
    new_array[i].x=new_x;
    if (i==0)
    cout<<new_x<<"FUCK        ";
    //cout<<new_x<<endl;
    new_array[i].y=new_y;

    //cpy(xy,new)

   
  }
  for (int k=0; k<SIZE; k++)
    {
      xy[k]=new_array[k];
    }
    cout<<xy[0].x<<"        ";
    cout<<new_array[0].x<<"   ";
  find_accel(xy,SIZE);
}

// void cpy(position new_array[],position new_array[])
// {

// }


int main()
{

  struct timeval start, end;

gettimeofday(&start,NULL);
  int SIZE=5;
	
  double G=1;
  position xy[SIZE];
  position new_array[SIZE];
  fill_class(xy,SIZE);


find_accel(xy,SIZE);


for (int k=0; k<1; k++)
{
 // cout<<xy[0].y<<endl;
   //cout<<xy[1].y<<endl;

  new_position(xy,SIZE,new_array);
}
  for (int k=0; k<20; k++)
  {
   // cout<<xy[k].y<<endl;
  }


gettimeofday(&end,NULL);

  cout<<endl<<("%ld\n", ((end.tv_sec * 1000000 + end.tv_usec)
      - (start.tv_sec * 1000000 + start.tv_usec)));

}