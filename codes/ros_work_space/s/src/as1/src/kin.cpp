#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/JointState.h"
#include "nav_msgs/Odometry.h"
#include <sstream>
#include "tf/transform_broadcaster.h"
#include <ros/ros.h>
#include "math.h"

//subto -> /catbot/joint_states
//msg->sensor_msgs/JointState
//pubto ->catbot/odom
//msg-> nav_msgs/Odometry.msg


using namespace std;


nav_msgs::Odometry odom;
ros::Time current_time, last_time;

double R=0.09*.95;
double D=0.2/1.05;
double x = 0.0;
double y = 0.0;
double th = 0.0;
double vx = 0.0;
double vy = 0.0;
double vth = 0.0;
double vl_a , vr_a , vl ,vr; 
double pr_last=0;
double pl_last=0;       
double pr_current=0;
double pl_current=0;
double pl=0;
double pr=0;
double rate;
double pl1=0;
double pr1=0;
double counter=0;
void sCallback(const sensor_msgs::JointState::ConstPtr & joint_msg)

{  
    pl=joint_msg->position[0];
    pr=joint_msg->position[1];
    if (counter==0)
    {pr1=pr;
     pl1=pl;
    counter=counter+1; //this condition to have the initial reading of the positoin as it's not always zero
    }
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "subpub1");
	ros::NodeHandle n;
        rate=100;
        ros::Publisher publisher = n.advertise<nav_msgs::Odometry>("catbot/odom",rate);   
	ros::Subscriber subscriber = n.subscribe("/catbot/joint_states", rate, sCallback);
        ros::Rate loop_rate(rate);
        while (ros::ok())
          { current_time = ros::Time::now();
          double dt = (current_time - last_time).toSec();  

          if (dt<.000001)
              dt=.000001;
          
            pr_current=pr-pr1;
            pl_current=pl-pl1;

            vl_a=  (pl_current-pl_last)/dt;
            vr_a=  (pr_current-pr_last)/dt;

            vl=vl_a*R;
            vr=vr_a*R ;       
             
        
            vx=.5*(vl+vr)*cos(th);
            x=x+.5*(vl+vr)*cos(th)*dt;//2.5;
            
            vy=.5*(vl+vr)*sin(th);
            y=y+.5*(vl+vr)*sin(th)*dt;//2.5;
            
            vth=(1/D)*(vr-vl);
            th=th+(.5)*(1/D)*(vr-vl)*dt;
            pr_last=pr_current;
            pl_last=pl_current;
            
     cout    <<"x= " << x<<"  "
             <<"        "
             <<"y = " <<y<<"  " 
             <<"        "
             <<"th = " <<th*180/3.14<<endl; //*

            if(abs(vx)<.0009)
                vx=0;
            if(abs(vy)<.0009)
               vy=0;

            geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);

            odom.header.stamp = current_time;
            odom.header.frame_id = "base_footprint";
            odom.pose.pose.position.x = x;
            odom.pose.pose.position.y = y;
            odom.pose.pose.position.z = 0.0;
            odom.pose.pose.orientation = odom_quat;
            odom.child_frame_id = "base_link";
            odom.twist.twist.linear.x = vx;
            odom.twist.twist.linear.y = vy;
            odom.twist.twist.angular.z = vth;


            last_time=current_time;
            publisher.publish(odom);
            ros::spinOnce();
            loop_rate.sleep();
          }
  return 0;

	

   return 0;
}



