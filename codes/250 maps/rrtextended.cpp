
 //c++ `Magick++-config --cxxflags --cppflags` -O2 -o rrtextended rrtextended.cpp   `Magick++-config --ldflags --libs`
#include <Magick++.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h> 

using namespace Magick;
using namespace std;





// map information
string input_type="binary";   //define the input type either (image or binary)
const int m=800;    // map rows
const int n=800;    // map coloms

int x_start=400;        //  start x poistion 
int y_start=66;        //  start y postion 
int x_goal=390;         //  goal  x postion
int y_goal=356;         //  goal  y postion

int threshold=5000;     // the minimum distace for node to join the tree
int tree_max_nodes=1000; //maximum number of nodes in the tree
int path_max=1000;       //maximum number of path nodes
int exit_conditon=60;   //distance to goal if achived tree building would stop (not used in this version)

//global variables
int total_dist=0;
int edges=0;
int counter =0;
int globalx=0;
int globaly=0;
int searched_nodes=0;
float myarray[m][n];
int   myarrayint[m][n];
int   maparray[m][n];
int go_to_flag=0;
// my defined functoin decleration

int* suggestXY() ; // function to suggest an x and y postions in the free space
int checkpath(float x1,float y1,float x2,float y2,int maparray[m][n]); // function to check if the path between 2 points in the map is free or not

float minof (float x1, float x2); 
float maxof (float x1, float x2);

//defining what ctrl+c would do
volatile sig_atomic_t flag = 0;

void my_function(int sig)
{ 
    go_to_flag=1;
}




class node 
{
public:
    int x; 
    int y;
    int id;
    int dist;
    int path;
    int parent;
    
    node(){x=-1; y=-1;dist=100000;}
    node(int X,int Y){x=X; y=Y;dist=10000;}
    node(int X,int Y,string type)
       {x=X; y=Y;
        if(type == "start"){id=0; parent=-1; dist=10000;}
       }
    
    int parent_id;
    
};

float findDist(int x,int y,node point);

//////////////////////////////////////////// the main function //////////////////////////////////////////////////////////

int main(int argc, char **argv)

{   
    signal(SIGINT, my_function); 
    // preparation for using random numbers in c++
    srand (static_cast <unsigned> (time(0))); 
      
    // open a new file named rnodes.txt if it exists open it and delete its content
    ofstream fout;
    fout.open("rnodes.TXT",ios::trunc); 
    fout.close();
        
    if(input_type=="image")
    {
        //read the pixel values of the red layer of image in the directory and store it in "myarray" int array
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n ;j++)
            {
                InitializeMagick(*argv);
                Image  img("/home/ganam/Desktop/binary factor/image6.jpg");
                ColorRGB rgb(img.pixelColor(i, j));  // ie. pixel at pos x=0, y=0
                cout<<i<<","<<j<<endl;
                myarray[i][j]=rgb.red();
            }            
        }
        
        // open myfile1.bin and delete it's content if it has any content
        fstream myfile0("myfile6.bin",ios::out  | ios::trunc | ios::binary|ios::in);
        myfile0.close();
        
        // open "myfile1.bin" in suitable writing mode
        fstream myfile("myfile6.bin",ios::out  | ios::app | ios::binary |ios::in);
        
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
                myfile.write((char*) &myarrayint[j][i], sizeof(int)); 
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
    }
     
    else if(input_type=="binary")
    {    InitializeMagick(*argv);
         // open "myfile1.bin" in suitable writing mode
        fstream myfile("paris.bin",ios::out  | ios::app | ios::binary |ios::in);
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
        
    }
     
    ////////////////////////////////////////// /// start of rrtcode /////////////////////////////////////////////////////////////
    
     clock_t begin = clock(); //start calculating time
     
     //initializeing goal and start nodes
     
    int distToGoal=1000; //random big number
    int pathToGoal=0;    
    node start( x_start,y_start,"start");
    node goal(x_goal,y_goal);
     
    //diplay goal and start star in green , goal in yellow ;
             Image disimage("/home/ganam/Desktop/binary factor/paris.jpg");    
             disimage.pixelColor(start.y, start.x, "green" ); 
             disimage.pixelColor(goal.y,goal.x , "yellow" ); 
             disimage.scale(Geometry(1000,1000, 1000, 1000) );
             disimage.display();
             disimage.scale(Geometry(m,n, m, n) );
             
    // allocating space for the tree in (dynamic_tree) array of maximum size of (tree_max_nodes) 
    // and adding the start node as the first node in the tree
    node dynamic_tree[tree_max_nodes];
    dynamic_tree[0]=start;
    int tree_size =1;

    //do the while loop whiile 
    while(/*distToGoal>=exit_conditon ||*/ pathToGoal==0)
    {
        
        //suggesting random (globalx,globaly) in the free space
        int* sug;
        sug=suggestXY();
        globalx=sug[0];
        globaly=sug[1];
        cout<<"sugestedx="<<globalx<<" sugestedy="<<globaly<<endl;

        //display suggested point (uncomment if you want to see where the suggested point are)
                disimage.pixelColor( globaly,globalx, "blue" ); 
//                 disimage.scale(Geometry(500,500, 500, 500) );
//                 disimage.display();
//                 disimage.scale(Geometry(m,n, m, n) );
             
        //store in each node in the tree its distance to suggested point and whether it has open paht or not
        for (int i=0; i<tree_size; i=i+1)
            { 
             dynamic_tree[i].dist= findDist (sug[0],sug[1],dynamic_tree[i]);
             dynamic_tree[i].path= checkpath(sug[0],sug[1],dynamic_tree[i].x,dynamic_tree[i].y, maparray);
             dynamic_tree[i].id=i;
            } 
 
        //find all nodes that have both suitable distance and clear path and store them in "suitable_array"

        node suitable_array[tree_size]; 
        int suitable_array_size=0;
        for (int i=0; i<tree_size; i=i+1)
        {                
            if(dynamic_tree[i].dist<= threshold && dynamic_tree[i].path==1)
            {                    
                suitable_array[suitable_array_size]=dynamic_tree[i];
                suitable_array_size=suitable_array_size+1;
            }
        } 

        
        //find the node that has the shortest distance and store it in "minimum" and adding suggested point to the tree
        int minimum_flag=0;
        if (suitable_array_size>0)
            { 
                node minimum = suitable_array[0];
                 for (int i=0; i<suitable_array_size; i=i+1)
                {               
                    if(suitable_array[i].dist<= minimum.dist )
                    {
                        minimum=suitable_array[i];
                        minimum_flag=1;
                    }
                }

                 //adding point to the tree in case flag is 1 (minimum is found)
                node newTreeNode;
                if (minimum_flag==1)
                {  
                    newTreeNode.x=sug[0];
                    newTreeNode.y=sug[1];
                    newTreeNode.id=tree_size;
                    newTreeNode.parent=minimum.id;
                    dynamic_tree[tree_size]=newTreeNode;
                    tree_size=tree_size+1;
                    
                    distToGoal=findDist(globalx,globaly,goal);
                    pathToGoal=checkpath(globalx,globaly,goal.x,goal.y, maparray);
                    
                    cout<<"new node added to the tree with"<<endl;
                    cout<<"distToGoal="<<distToGoal<<endl;
                    
                    //display new added point to the tree
                            disimage.pixelColor(sug[1],sug[0],  "red" ); 
                            disimage.strokeColor("yellow"); // Outline color 
                            disimage.fillColor("yellow"); // Fill color 
                            disimage.strokeWidth(1);
                            disimage.draw(DrawableLine(globaly,globalx,minimum.y,minimum.x) );
                            disimage.pixelColor(globaly,globalx,  "red" );
//                           disimage.scale(Geometry(500,500, 500, 500) );
//                           disimage.display(); 
//                           disimage.scale(Geometry(m,n, m, n) );
                            for (int i=0; i<tree_size; i=i+1)
                            { 
                                disimage.pixelColor(dynamic_tree[i].y,dynamic_tree[i].x,  "red" );
                            } 
            

                } //end of  if minimum flag
           

            //check if the new suggested point can see the goal and (has a distance <exit_conditon) 
            //if so add the goal point as a child for this node
            if(/*distToGoal<=100 &&*/ pathToGoal==1)
            {
                dynamic_tree[tree_size]=goal;
                goal.parent=newTreeNode.id;
            }
          
        } //end of if (suitable_array_size>0)
        
        else // if there is no suitable points to connect to in the tree clear suggested point form display
        {                 
             disimage.pixelColor(sug[1],sug[0],  "white" ); 
        }
         if(go_to_flag==1)
        {
    disimage.pixelColor(globaly,globalx,  "red" );
    disimage.pixelColor(y_start, x_start, "orange" ); 
    disimage.pixelColor(y_goal,x_goal , "orange" ); 
    disimage.scale(Geometry(1000,1000, 1000, 1000) );
    disimage.display();
    disimage.scale(Geometry(m,n, m, n) );    
    exit (EXIT_FAILURE);
 
        }
    }
//////////////////////////////////////   end of while loop  /////////////////////////////////////////////////////////////////////
//////////////////////////////////////    tree is built     /////////////////////////////////////////////////////////////////////

    clock_t end = clock();
    for(int i=0;i<25;i++){ cout<<"     goal is reached   " <<endl;}   

//finding the path points connecting the goal to the start
    int id=-2; //random value to enter while
    node current_node=goal;
    
    //allocate space for path nodes in array "path_nodes" and adding the goal node as first element
    node path_nodes[path_max]; 
    path_nodes[0]=goal;
    int path_nodes_size=1;
    while(id!=0) 
    {
        current_node=dynamic_tree[current_node.parent];
        path_nodes[path_nodes_size]=current_node;
        id=current_node.id;
        path_nodes_size=path_nodes_size+1;
    }


    // construct new array "Spath_nodes" of right order from start to goal and writing the positoin in a text file 
    node Spath_nodes[path_nodes_size];
    for(int i =1; i<=path_nodes_size; i=i+1)
    {
        Spath_nodes[i-1]=path_nodes[path_nodes_size-i];
        cout<<"node "<<i<<" ("<<Spath_nodes[i-1].x<< ","<< Spath_nodes[i-1].y<<")"<<endl;
        
        //writing the path nodes postition in a text file "rnodes.TXT"
             ofstream fout;
	     fout.open("rnodes.TXT",ios::app);
             fout<<Spath_nodes[i-1].x<<endl;
             fout<<Spath_nodes[i-1].y<<endl;
             fout.close();
    }
    
    for(int i =0; i<path_nodes_size-1; i=i+1)
    {
                disimage.strokeColor("blue"); // Outline color 
                disimage.fillColor("blue"); // Fill color 
                disimage.strokeWidth(2);
                disimage.draw(DrawableLine(Spath_nodes[i].y,Spath_nodes[i].x,Spath_nodes[i+1].y,Spath_nodes[i+1].x) );
                disimage.pixelColor(Spath_nodes[i].y, Spath_nodes[i].x, "black" ); 
                disimage.pixelColor(globaly,globalx,  "red" );
//              disimage.scale(Geometry(500,500, 500, 500) );
//              disimage.display( ); 
//              disimage.scale(Geometry(m,n, m, n));
    }
   

///////////////////////////////////////////////extended rrt///////////////////////////////////////////
// rrt extended refines the path found getting rid of any non useful node in the path

    // allocate space for the extended node "ex_array" and adding the fisrst node in Spath_nodes(start point) to it
    node ex_array[path_nodes_size];
    ex_array[0]=Spath_nodes[0];
    int horizon;
    
    // label any non usefule node with id=-1;
    for(int i =0; i<path_nodes_size; i=i+1)
    {
        for(int j =i; j<path_nodes_size; j=j+1)
        {
            if(checkpath(Spath_nodes[i].x,Spath_nodes[i].y,Spath_nodes[j].x,Spath_nodes[j].y, maparray)==1 && Spath_nodes[i].id !=-1)
            {
                horizon=j;
            }
        }
        for(int k =i+1; k<horizon; k=k+1)
        {
            Spath_nodes[k].id=-1;
        }
    }
    
    //adding any node not labeled with id=-1 to the extended path
    int ex_array_size=1;
    for(int i =0; i<path_nodes_size; i=i+1)
    {
        if(Spath_nodes[i].id !=-1)
        {
            ex_array[ex_array_size]=Spath_nodes[i];
            ex_array_size=ex_array_size+1;
        }
    }

    // open a new file named rnodes.txt if it exists open it and delete its content
    ofstream fout2;
    fout2.open("exrnodes.TXT",ios::trunc); 
    fout2.close();
    
    //writing the extended path postion to text file "exrnodes.TXT" and displaying the path
    for(int i =0; i<ex_array_size-1; i=i+1)
    {

        ofstream fout2;
	fout2.open("exrnodes.TXT",ios::app);
        fout2<<ex_array[i].x<<endl;
        fout2<<ex_array[i].y<<endl;
	fout2.close();
                    //dispaly  extended path in red
                    disimage.strokeColor("red"); // Outline color 
                    disimage.fillColor("red"); // Fill color 
                    disimage.strokeWidth(1);
                    disimage.draw(DrawableLine(ex_array[i].y,ex_array[i].x,ex_array[i+1].y,ex_array[i+1].x) );
                    total_dist=total_dist+sqrt(pow( (ex_array[i].x-ex_array[i+1].x) , 2 ) + pow( (ex_array[i].y-ex_array[i+1].y), 2 ));;
                    disimage.pixelColor(ex_array[i].y, ex_array[i].x, "green" ); 
//                  disimage.scale(Geometry(500,500, 500, 500) );
//                  disimage.display( ); 
//                  disimage.scale(Geometry(m,n, m, n));
    }

    // display the results
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    cout<<"searchSteps= "<<searched_nodes<<endl;
    cout<<"tree_size= "<<tree_size<<endl;
    cout<<"time_spent="<<time_spent<< endl;
    cout<<"total_dist= "<<total_dist<<endl;
    cout<<"edges= "<<ex_array_size-1<<endl;

// dipalay all the tree picture
   LOOP:
    disimage.pixelColor(globaly,globalx,  "red" );
    disimage.pixelColor(start.y, start.x, "orange" ); 
    disimage.pixelColor(goal.y,goal.x , "orange" ); 
    disimage.scale(Geometry(1000,1000, 1000, 1000) );
    disimage.display();
    disimage.scale(Geometry(m,n, m, n) );
  
     return 0;
}
//////////////////////////////////////////end of code///////////////////////////////////////////////////////

///////////////////////////////////////////////////suggestfunciton/////////////////////////////////////////


int* suggestXY() //suggestXY is afunciton that suggests x and y vlaues that are in the free space
{

  int suggested_x=-1;
  int suggested_y=-1;
  int xxx=49;
  int yyy=49;
  while(suggested_x==-1 || maparray[suggested_x][suggested_y]==9)
    {
      float LO = 1; float HI=m-2;
      suggested_x = LO + static_cast <float> (rand()) /( static_cast <float>(RAND_MAX/(HI-LO)));
       LO = 1;  HI=n-2;
      suggested_y = LO + static_cast <float> (rand()) /( static_cast <float>(RAND_MAX/(HI-LO)));
      
      
    }
if (maparray[suggested_x][suggested_y]!=9){xxx=suggested_x;yyy=suggested_y;}
 int* returnArray;
 searched_nodes=searched_nodes+1;
 returnArray= new int[2];
 returnArray[0]=xxx;
 returnArray[1]=yyy;
 return returnArray;

}
/////////////////////////////////////chekcfuncition//////////////////////////////////////////////////////////////////////

int checkpath(float x1,float y1,float x2,float y2,int maparray[m][n])
{

    int number_points =200;

    float X[number_points+1];
    float Y[number_points+1];
    int* pointsx;
    pointsx= new int[100000];
    int* pointsy;
    pointsy= new int[100000];

    float xminim;
    float xmaxim;
    float yminim;
    float ymaxim;
    if (x1==x2)
       {
           xminim=x1;
           xmaxim=x1;
           yminim=minof(y1,y2);
           ymaxim=maxof(y1,y2);
           float intervalsize=(ymaxim-yminim)/number_points;
           for (int i=1; i<=number_points; i=i+1)
            {
              Y[0]=yminim;
              Y[i]=Y[i-1]+intervalsize;
              X[0]=xminim;
              X[i]=xminim;
            }
       }
    else
       {float slope=(y2-y1)/(x2-x1);
        xminim=minof(x1,x2);
        xmaxim=maxof(x1,x2);
        float intervalsize=(xmaxim-xminim)/number_points;
        float yi=slope*(xminim-x1)+y1;
        float yii=slope*(xmaxim-x1)+y1;
         ymaxim=maxof(yi,yii);
         yminim=minof(yi,yii);
         for (int i=1; i<=number_points; i=i+1)
            {
              X[0]=xminim;
              X[i]=X[i-1]+intervalsize;
              Y[0]=yminim;
              Y[i]=slope*(X[i]-x1)+y1;


            }
       }


        
int counter2=0;
float dist;
int flag=1;
//Image disimage("/home/ganam/Desktop/imreadtest/astar/rrt/image1.jpg");
 for (int i=xminim; i<=xmaxim ; i=i+1)
 {
     for (int j=yminim; j<=ymaxim ; j=j+1)
     {
         for (int k=1; k<=number_points ; k=k+1)
         {
            dist=sqrt(pow( (i-X[k]) , 2 )+pow( (j-Y[k]), 2 ));

            if (dist<1)
             {

              pointsx[counter2]=i;
              pointsy[counter2]=j;
              if (pointsx[counter2]!=pointsx[counter2-1] || pointsy[counter2]!=pointsy[counter2-1] )
              {
                if ( pointsx[counter2]<=xmaxim && pointsy[counter2]<=ymaxim)
                {
                   int xx=pointsx[counter2];
                   int yy=pointsy[counter2];
                   if (maparray[xx][yy]==9)
                          {flag=0;}
                   
                   if (i>=0 && i<=m && j>=0 && j<=n)
                   {
               //    disimage.pixelColor(j,i,  "blue" ); 

                   }
                   
                    counter2=counter2+1;
                }
              }
            }
         }
    }
 }
         // disimage.scale(Geometry(500,500, 500, 500) );
         // disimage.display();
          //disimage.scale(Geometry(m,n, m, n) );

return flag;
}

float minof (float x1, float x2)
{
if (x1<x2)
  {return x1;}
else
  {return x2;}
}
float maxof (float x1, float x2)
{
if (x1>x2)
  {return x1;}
else
  {return x2;}
}
float findDist(int x,int y,node point)
{
    float dist;
    
    dist=sqrt(pow( (point.x-x) , 2 )+pow( (point.y-y), 2 ));
    return dist;
}