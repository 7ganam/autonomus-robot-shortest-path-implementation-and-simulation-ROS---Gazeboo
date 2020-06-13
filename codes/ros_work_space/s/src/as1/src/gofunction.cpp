
#include "tf/transform_broadcaster.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "gazebo_msgs/ModelStates.h"
#include "sensor_msgs/JointState.h"
#include <math.h>  


///gazebo/catbot/joint_states
//sensor_msgs/JointState



double x=0.00005;double y=.0005;double th=0;
double thg=0;double xg;double yg;
double thdiff=0;double angsped=0;
double dist;
int marchoutput=0;
using namespace std;
int rotateto(int xg,int yg);
int march(int xg, int yg);
ros::Publisher publisher;
ros::Subscriber sub;
void chatterCallback(const gazebo_msgs::ModelStates::ConstPtr & modmsg)

{
    tf::Quaternion bq(modmsg->pose[1].orientation.x, modmsg->pose[1].orientation.y, modmsg ->pose[1].orientation.z, modmsg->pose[1].orientation.w );
    double roll, pitch, yaw;
    tf::Matrix3x3(bq).getRPY(roll, pitch, yaw);
    modmsg->pose[1].orientation.w;
    th= yaw/3.14*180;
    
    while(th>=360){th=th-360;}
    while(th<0){th=th+360;}

    x=modmsg->pose[1].position.x;
    x=x+10;
    
    y=modmsg->pose[1].position.y;
    y=y+10;
    
}

geometry_msgs::Twist geom;
int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  sub = n.subscribe("/gazebo/model_states", 1000, chatterCallback);
  publisher = n.advertise<geometry_msgs::Twist>("/gazebo/catbot/velocity_command", 10);
  

  xg=0;  yg=10;

    ros::Rate loop_rate(10);
    while (ros::ok() ) 

        { 
          //cout<<00000<<endl;
          if( marchoutput==0){ marchoutput=march(xg,yg); cout<<1.555<<endl;}
          //cout<<a<<endl;
          ros::spinOnce();
          loop_rate.sleep();
        }

  return 0;
}


int rotateto(int xg,int yg)
{   int rotateflag=1;
    ros::Rate loop_rate(10);
    while (rotateflag==1 && ros::ok()) 
    { 
        //finding the angel between current postion and goal postition
        thg=  atan ((yg-y)/(xg-x)) * 180 / 3.14;

        if(thg <0 && yg>y)  {thg=180+thg;  }
        else if(thg <0 && yg<y)  {thg=360+thg;}

        else if(thg >0 && yg>y)  {thg=thg; }
        else if(thg >0 && yg<y)  {thg=180+thg; }
       // while(thg>360){thg=thg-360;}
       // while(thg<0){thg=thg+360;}
        // calcuating the direction the robot must rotate in  "angsped" 
        thdiff=thg-th;
        if(th<90 && thdiff<360 && thdiff>270){thdiff=thg-360-th; cout<<"i'm innnnnnnnnnnn"<<endl;}
        if(thdiff<90 && th<360 && th>270){thdiff=thg+360-th; cout<<"i'm innnnnnnnnnnn"<<endl;}
        //cout<<"rotate diff = "<<thdiff<<endl;
        //cout<<"xg="<<xg<<"        "<<"yg="<<yg<<endl;
        //cout<<"x ="<<x<< "   "<<"y ="<<y<<"   " <<"th="<<th<<"   "<<"thg="<<thg<<endl;

        if (thdiff>0 && thdiff<180)
        {angsped=1;}
        else if (thdiff>0 && thdiff>180)
         {angsped=-1;}

        else if (thdiff<0 && thdiff>-180)
        {angsped=-1;}
        else if (thdiff<0 && thdiff<-180)
        {angsped=1;}
        

        //start change velocity gradualy relative to the difference between the current and goal angle 
        if (th != thg && abs(thdiff)>50 )
        {
          geom.linear.x=0;  geom.linear.y=0; geom.linear.z=0;  geom.angular.x=0; geom.angular.y=0; 
          geom.angular.z=angsped*10;
          publisher.publish(geom);
             //cout<<"xg="<<xg<<endl;cout<<"yg="<<yg<<endl;
         // cout<<"x="<<x<<"   "<<"y="<<y<<"   " <<"th="<<th<<"   "<<"thg="<<thg<<endl;
        }
        else if (th != thg && abs(thdiff)<50  && abs(thdiff)>5)
        {
          geom.linear.x=0;  geom.linear.y=0; geom.linear.z=0;  geom.angular.x=0; geom.angular.y=0; 
          geom.angular.z=angsped*2;
          publisher.publish(geom);
           //cout<<"xg="<<xg<<endl;cout<<"yg="<<yg<<endl;
          //cout<<"x="<<x<<"   "<<"y="<<y<<"   " <<"th="<<th<<"   "<<"thg="<<thg<<endl;
        }
        else if (th != thg && abs(thdiff)<5)
        {
          geom.linear.x=0;  geom.linear.y=0; geom.linear.z=0;  geom.angular.x=0; geom.angular.y=0; 
          geom.angular.z=angsped*.5;
          publisher.publish(geom);
         //  cout<<"xg="<<xg<<endl;cout<<"yg="<<yg<<endl;
          //cout<<"x="<<x<<"   "<<"y="<<y<<"   " <<"th="<<th<<"   "<<"thg="<<thg<<endl;
        }
       
        if (th<=thg+1 && th>= thg-1  )
        { int counter=0;
              while(counter<30000 && ros::ok())
              {
              geom.linear.x=0;  geom.linear.y=0; geom.linear.z=0;  geom.angular.x=0; geom.angular.y=0; 
              geom.angular.z=angsped*0;
              publisher.publish(geom);

              //cout<<"xg="<<xg<<endl;cout<<"yg="<<yg<<endl;
              // cout<<"x="<<x<<"   "<<"y="<<y<<"   " <<"th="<<th<<"   "<<"thg="<<thg<<endl;
              counter=counter+1;
//cout<<counter<<endl;
              }
              rotateflag=0;
cout<<"rotateflag"<<rotateflag<<endl;
              return 1;
        }
          
          ros::spinOnce();
          loop_rate.sleep();
     }
  
}

int march(int xg, int yg)
{int marchflag=1; 
 ros::Rate loop_rate(10);
 int rotationcomplete=0;
 rotationcomplete= rotateto( xg,yg);
//cout<<"start march"<<endl;
cout<<1<<endl;
  while(marchflag==1 && ros::ok())
   {  
cout<<2<<endl;
        thg=  atan ((yg-y)/(xg-x)) * 180 / 3.14;

         if(thg <0 && yg>y)  {thg=180+thg;}
         else if(thg <0 && yg<y)  {thg=360+thg;}

         else if(thg >0 && yg>y)  {thg=thg;}
         else if(thg >0 && yg<y)  {thg=180+thg;} 

        //while(thg>360){thg=thg-360;}
        //while(thg<0){thg=thg+360;}
        
         thdiff=thg-th;
          if(th<90 && thdiff<360 && thdiff>270){thdiff=thg-360-th;}
        if(thdiff<90 && th<360 && th>270){thdiff=thg+360-th; }
         dist=sqrt(pow( (x-xg) , 2 )+pow( (y-yg), 2 ));
cout<<thdiff<<"      "<<dist<<endl;
        
         if(rotationcomplete==1)
          {
             if(dist > 6)
             {
               geom.linear.x=10;  geom.linear.y=0; geom.linear.z=0;  geom.angular.x=0; geom.angular.y=0; 
               geom.angular.z=angsped*0;
               publisher.publish(geom);
             }
            else if(dist < 6 && dist > 2)
             {
               geom.linear.x=5;  geom.linear.y=0; geom.linear.z=0;  geom.angular.x=0; geom.angular.y=0; 
               geom.angular.z=angsped*0;
               publisher.publish(geom);
             }
             else if(dist < 2&& dist > .5)
             {
               geom.linear.x=2;  geom.linear.y=0; geom.linear.z=0;  geom.angular.x=0; geom.angular.y=0; 
               geom.angular.z=angsped*0;
               publisher.publish(geom);
             }
             else if(dist < .5 && dist > .1)
             {
               geom.linear.x=1;  geom.linear.y=0; geom.linear.z=0;  geom.angular.x=0; geom.angular.y=0; 
               geom.angular.z=angsped*0;
               publisher.publish(geom);
             }
              else if(dist < .1 && dist > 0)
             {
               geom.linear.x=0;  geom.linear.y=0; geom.linear.z=0;  geom.angular.x=0; geom.angular.y=0; 
               geom.angular.z=angsped*0;
               publisher.publish(geom);
               marchflag=0;
cout<<"marchflag= "<<marchflag<<endl;
               return 1;
               break;

             }

          }
        if ( abs(thdiff)>10)
          {
//cout<<"stop march"<<endl;
          geom.linear.x=0;  geom.linear.y=0; geom.linear.z=0;  geom.angular.x=0; geom.angular.y=0; 
           geom.angular.z=angsped*0;
           publisher.publish(geom);
           rotationcomplete==0;
          march(xg,yg);
          }
          ros::spinOnce();
          loop_rate.sleep();
   }
return 0;
}