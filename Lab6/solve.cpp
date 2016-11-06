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
using namespace std;
class position
{
	public:
	 double x,y,v,m,ax,ay; 
	 position()
	 {
	 	x,y,v,ax,ay=0;
    m=1;
	 }
};

position find_distance(position node_i, position node_j)
{
  position distance;
  distance.x=node_j.x-node_i.x;
  distance.y=node_j.y-node_i.y;
  return distance;
}

position *fill_class(position xy[],int SIZE)
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
  return xy;
}

position *find_accel(position xy[],int SIZE)
{
  for (int j=0; j<SIZE; j++)
  {
    position accel;
    position temp;
    double accel_num_x,accel_num_y,accel_den_y=0;
    double accel_den_x=0;
    double num_x,num_y=0;
    for (int i=0; i<SIZE; i++)
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
          num_x+=(accel_num_x/accel_den_x);
          num_y+=(accel_num_y/accel_den_y);
        //cout<<num<<endl;
        }
      }
    }
    //return accel.a;
   // cout<<num;
    xy[j].ax=num_x;
    xy[j].ay=num_y;
  }
  return xy;
}

void new_position(position xy[],int SIZE)
{
  position next[SIZE];  
  double t=.01
  double new_vy,new_vx,new_x,new_y=0;
  for (int i=0; i<SIZE; i++)
  {
    new_vx=(xy[i].v)+.t*(xy[i].ax);
    new_vy=(xy[i].v)+.t*(xy[i].ay);
    new_x=(xy[i].x+.t*(new_vx));
    new_y=(xy[i].y+.t*(new_vy));
  }
}


int main()
{
  int SIZE=1000;
	// position dog;
	// //dog.x=3;
	// std::cout<<dog.y;
	
  double G=1;
  position xy[SIZE];
  
  fill_class(xy,SIZE);

  //cout<<find_distance(xy[0],xy[1]).y;

find_accel(xy,SIZE);
new_position(xy,SIZE);
cout<<xy[0].ax;


}