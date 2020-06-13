
#include "tf/transform_broadcaster.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "gazebo_msgs/ModelStates.h"
#include "sensor_msgs/JointState.h"
#include <math.h>  
#include <fstream>
#include<iostream>
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;


double x=0.00005;double y=.0005;double th=0;
double thg=0;    double xg;     double yg;
double thdiff=0; double angsped=0;
double dist;
int whilecounter=0;
int marchoutput=0; // this would be one when the robot reach its destination
geometry_msgs::Twist geom;

int readarray[10000];
string line;
int m;
float scale=3;
int arraysize=0;


int rotateto(float xg,float yg);
int march(float xg, float yg);
ros::Publisher publisher;
ros::Subscriber sub;

void chatterCallback(const gazebo_msgs::ModelStates::ConstPtr & modmsg)
{
    tf::Quaternion bq(modmsg->pose[1].orientation.x, modmsg->pose[1].orientation.y, modmsg ->pose[1].orientation.z, modmsg->pose[1].orientation.w );
    double roll, pitch, yaw;
    tf::Matrix3x3(bq).getRPY(roll, pitch, yaw);
    modmsg->pose[1].orientation.w;
    th= yaw/3.14*180; // this is the angle with relative to x axis



    // making sure th is between 0 & 360 
    while(th>=360){th=th-360;}
    while(th<0){th=th+360;}

    // passing the message to global variable x to be read anywhere in the code
    x=modmsg->pose[1].position.x;
    x=(x+10); // adding buffer value to make the upper corenr in gazebo point (0,0)
    y=modmsg->pose[1].position.y;
    y=(y+10); // adding buffer value to make the upper corenr in gazebo point (0,0)
    
}
int main(int argc, char **argv)
{

// read the nodes from the nodes.txt file
  ifstream fin;
	fin.open("/home/ganam/Desktop/imreadtest/astar/astar_finished/nodes.TXT");
        //fin.open("/home/ganam/Desktop/imreadtest/rrt/magic++tests/rnodes.TXT");

        for( std::string line; getline( fin, line ); )
        {
            m= atoi(line.c_str());
            readarray[arraysize]=m;
            arraysize=arraysize+1;
        }

	fin.close();
        
// sorting the postions of the nodes in x and y array 
          int xarray[arraysize/2];
          int yarray[arraysize/2];
          
        int counter2=0;
        for(int i=0 ; i<arraysize ; i=i+2)
        {
            xarray[counter2]=readarray[i];
            yarray[counter2]=readarray[i+1];
            counter2=counter2+1;
        }
       
// filtering the array to keep only the edge points 
        int xmark;
        int ymark;
        int marksarray[arraysize/2];
        marksarray[0]=0;
        for(int i=1 ; i<arraysize/2 ; i=i+1)
        {
         xmark=xarray[i]-xarray[i-1];
         ymark=yarray[i]-yarray[i-1]; 
         if     (xmark==-1 && ymark==-1){ marksarray[i]=1;}
         else if(xmark==-1 && ymark==0) { marksarray[i]=2;}
         else if(xmark==-1 && ymark==1) { marksarray[i]=3;}
         else if(xmark==0 && ymark==-1) { marksarray[i]=4;}
         else if(xmark==0 && ymark==1)  { marksarray[i]=6;}
         else if(xmark==1 && ymark==-1) { marksarray[i]=7;}
         else if(xmark==1 && ymark==0)  { marksarray[i]=8;}
         else if(xmark==1 && ymark==1)  { marksarray[i]=9;}

        }
        
        int xDestContainer[1000];
        int yDestContainer[1000];
        int DestSize=0;
        for(int i=1 ; i<arraysize/2 ; i=i+1)
        {
         if (marksarray[i]-marksarray[i-1]!=0  || i==arraysize/2-1 )
            {   
                xDestContainer[DestSize]=xarray[i-1];
                yDestContainer[DestSize]=yarray[i-1];
                DestSize=DestSize+1;
            }
        }
        
//creating scaled x and y array from the image to truth scale
        float xDestarray[DestSize];
        float yDestarray[DestSize];
         for(int i=0 ; i<DestSize ; i=i+1)
        {
           xDestarray[i]=xDestContainer[i]/scale;
           yDestarray[i]=yDestContainer[i]/scale;
           cout<<xDestarray[i]<<"  "<<yDestarray[i]<<endl;
        }    

// initializing subscriber and publisher.
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  sub = n.subscribe("/gazebo/model_states", 1000, chatterCallback);
  publisher = n.advertise<geometry_msgs::Twist>("/gazebo/catbot/velocity_command", 1000);

//start sending x and y arrays to gazebo for the robot to start moving.
    ros::Rate loop_rate(1000);
    while (ros::ok() && whilecounter<DestSize) 
        { 
          for(int i=0; i<DestSize ; i=i+1)
          {
               marchoutput=march(xDestarray[i],yDestarray[i]);
               whilecounter=whilecounter+1;
          } 

          ros::spinOnce();
          loop_rate.sleep();
        }

  return 0;
}


int rotateto(float xg,float yg)
{  
    int rotateflag=1; // rotete flage will equale zero when goal angle is reached
    ros::Rate loop_rate(1000);
    while (rotateflag==1 && ros::ok()) 
    { 
        //finding the angel between current postion and goal postition with refrence to x axis
        thg=  atan ((yg-y)/(xg-x)) * 180 / 3.14;
          //atan have the same value for each two quarters ..to know exactly which quarter we are in ...
        if      (thg <0 && yg>y)  {thg=180+thg;}
        else if (thg <0 && yg<y)  {thg=360+thg;}
        else if (thg >0 && yg>y)  {thg=thg;    }
        else if (thg >0 && yg<y)  {thg=180+thg;}

        // calcuating the direction the robot must rotate in  "angsped" 
        thdiff=thg-th;
        if(th<90 &&  thg<360 && thdiff>270) {thdiff=thg-360-th; } // those two lines to  get over the transitioin between 
        if(thg<90 && th<360 && th>270     ) {thdiff=thg+360-th; }//  angels less than 360 and more than 0 


cout<<"xg="<<xg*scale<<"        "<<"yg="<<yg*scale<<endl;
cout<<"x ="<<x<< "   "<<"y ="<<y<<"   " <<"th="<<th<<"   "<<"thg="<<thg<<endl;
//cout<<"rotate diff = "<<thdiff<<endl;

        if (thdiff>0 && thdiff<180)
        {angsped=1;}
        else if (thdiff>0 && thdiff>180)
         {angsped=-1;}

        else if (thdiff<0 && thdiff>-180)
        {angsped=-1;}
        else if (thdiff<0 && thdiff<-180)
        {angsped=1;}
         
         dist=sqrt(pow( (x-xg) , 2 )+pow( (y-yg), 2 ));
        //start change velocity gradualy relative to the difference between the current and goal angle 
        if (th != thg && abs(thdiff)>50 && dist>.1)
        {
          geom.linear.x=0;  geom.linear.y=0; geom.linear.z=0;  geom.angular.x=0; geom.angular.y=0; 
          geom.angular.z=angsped*10;
          publisher.publish(geom);
        }

        else if (th != thg && abs(thdiff)<50  && abs(thdiff)>5 && dist>.1)
        {
          geom.linear.x=0;  geom.linear.y=0; geom.linear.z=0;  geom.angular.x=0; geom.angular.y=0; 
          geom.angular.z=angsped*2;
          publisher.publish(geom);
        }

        else if (th != thg && abs(thdiff)<5 && dist>.1)
        {
          geom.linear.x=0;  geom.linear.y=0; geom.linear.z=0;  geom.angular.x=0; geom.angular.y=0; 
          geom.angular.z=angsped*.3;
          publisher.publish(geom);
        }
       
        if (th<=thg+.2 && th>= thg-.2 || dist<.1)
        { int counter=0;
          while(counter<30000 && ros::ok()) // this works as a timer to make sure the robot is still before moving again
            {
              geom.linear.x=0;  geom.linear.y=0; geom.linear.z=0;  geom.angular.x=0; geom.angular.y=0; 
              geom.angular.z=angsped*0;
              publisher.publish(geom);
              counter=counter+1;

            }
         rotateflag=0;
         return 1;
        }
          
          ros::spinOnce();  // this is important to make the reading of the subscriber available in rotate funciton scope 
          loop_rate.sleep();
     }
  
}

int march(float xg, float yg)
{
 int marchflag=1; //marchflage would be set zero when distination is reached
 ros::Rate loop_rate(1000);
 int rotationcomplete=0;
 rotationcomplete= rotateto( xg,yg); //rotate first to the right directoin..the rotate function is defiend below.
 
 while(marchflag==1 && ros::ok())
   {  
        // calculating the goal angel again...will be needed to check if the robot deviated from the right direction
        thg=  atan ((yg-y)/(xg-x)) * 180 / 3.14;
         if     (thg <0 && yg>y)  {thg=180+thg;}
         else if(thg <0 && yg<y)  {thg=360+thg;}
         else if(thg >0 && yg>y)  {thg=thg;    }
         else if(thg >0 && yg<y)  {thg=180+thg;} 
         thdiff=thg-th;
         if(th<90 && thg<360 && thdiff>270){thdiff=thg-360-th;}
         if(thg<90 && th<360 && th>270){thdiff=thg+360-th; }


        //calculating the distance from the goal to the robot. 
        dist=sqrt(pow( (x-xg) , 2 )+pow( (y-yg), 2 ));
  cout<<" dist = "<< dist<<endl;      
         //start marching with different speeds relative to the distance to the goal
         if(rotationcomplete==1) // rotation complete would be set zero if the angle deviated from the goal
          {
             if(dist > 6)
             {
               geom.linear.x=15;  geom.linear.y=0; geom.linear.z=0;  geom.angular.x=0; geom.angular.y=0; 
               geom.angular.z=angsped*0;
               publisher.publish(geom);
             }

            else if(dist < 6 && dist > 2)
             {
               geom.linear.x=6;  geom.linear.y=0; geom.linear.z=0;  geom.angular.x=0; geom.angular.y=0; 
               geom.angular.z=angsped*0;
               publisher.publish(geom);
             }

             else if(dist < 2&& dist > .5)
             {
               geom.linear.x=4;  geom.linear.y=0; geom.linear.z=0;  geom.angular.x=0; geom.angular.y=0; 
               geom.angular.z=angsped*0;
               publisher.publish(geom);
             }
             else if(dist < .5 && dist > .1)
             {
               geom.linear.x=2;  geom.linear.y=0; geom.linear.z=0;  geom.angular.x=0; geom.angular.y=0; 
               geom.angular.z=angsped*0;
               publisher.publish(geom);
             }
              else if(dist < .1 && dist > 0)
             {
               geom.linear.x=0;  geom.linear.y=0; geom.linear.z=0;  geom.angular.x=0; geom.angular.y=0; 
               geom.angular.z=angsped*0;
               publisher.publish(geom);
               marchflag=0;
               return 1;
               break;

             }

          }
        if ( abs(thdiff)>10) // checking the angel is still near the right direction 
          {
           geom.linear.x=0;  geom.linear.y=0; geom.linear.z=0;  geom.angular.x=0; geom.angular.y=0; 
           geom.angular.z=angsped*0;
           publisher.publish(geom);
           rotationcomplete==0;
           march(xg,yg); // recursive funciton to start march from the begining so rotation is included to fix angle 
          }

        ros::spinOnce();
        loop_rate.sleep();
   }
return 0;
}
