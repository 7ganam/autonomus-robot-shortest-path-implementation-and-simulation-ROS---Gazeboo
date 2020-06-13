//  c++ `Magick++-config --cxxflags --cppflags` -O2 -o im2arr im2arr.cpp   `Magick++-config --ldflags --libs` 

#include <Magick++.h>
#include <iostream>
#include <fstream>
const int m=50;
const int n=50;
int   maparray[m][n];
using namespace Magick;
using namespace std;
int counter =0;

float myarray[m][n];
int myarrayint[m][n];
int main(int argc, char **argv) {
   //read the pixel values of the red layer of image in the directory and store it in "myarray" int array
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n ;j++)
            {
                InitializeMagick(*argv);
                Image  img("/home/ganam/Desktop/binary factor/50 maps/image_50_9.jpg");
                ColorRGB rgb(img.pixelColor(i, j));  // ie. pixel at pos x=0, y=0
                cout<<i<<","<<j<<endl;
                myarray[i][j]=rgb.red();
            }            
        }
        
        // open myfile1.bin and delete it's content if it has any content
        fstream myfile0("binary_50_9.bin",ios::out  | ios::trunc | ios::binary|ios::in);
        myfile0.close();
        
        // open "myfile1.bin" in suitable writing mode
        fstream myfile("binary_50_9.bin",ios::out  | ios::app | ios::binary |ios::in);
        
        // scaning the pixel values in array "myarray" and producing array of 9 and 1 values. (1 for free space / 9 for obstacle)
        for(int i=0;i<m;i=i+1)
        {
            for(int j=0 ; j<n ; j=j+1)
            {
                if(myarray[i][j]<.5)
                {myarrayint[i][j]=9;}
                else
                {myarrayint[i][j]=1;}
                
            }
        }
        
        // write the values of the (9/1) array into the pinary file.
        myfile.seekp(0);
        for(int i=0; i<m; i=i+1)
        {
            for(int j=0 ; j<n ; j=j+1)
            {
                myfile.write((char*) &myarrayint[i][j], sizeof(int)); 
            }
        }
        
        
        //read the values of (9,1) array in "maparray" and display it in terminal
        // maparray is the final array we are going to work on 
        
        myfile.seekg(0);
        int out[m*n];
        for(int i=0;i<m*n;i=i+1)
        {
            myfile.read((char*) &out[i], sizeof(int));  
        } 
        int co=0;
        for(int i=0; i<m; i=i+1)
        {
            for(int j=0; j<n; j=j+1)
            {
                if(co%n==0) {cout<<endl;}
                maparray[i][j]=out[co];
                cout<< maparray[i][j];
                co=co+1;
            }
        }
 return 0;
}
 
