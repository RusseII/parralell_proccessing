#include <typeinfo> 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
using namespace std;



int main(int argc, char *argv[]) 
{
  int rank, size;
  int i=1;
  int cities=1;

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
      cout<<sLine<<endl;
    }
    infile.close();
  }

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

