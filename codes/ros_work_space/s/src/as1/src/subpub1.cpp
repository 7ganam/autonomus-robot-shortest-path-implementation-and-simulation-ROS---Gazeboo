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
void sCallback(const sensor_msgs::JointState::ConstPtr & joint_msg)
{  
    vl_a=joint_msg->velocity[0];
    vr_a=joint_msg->velocity[1];
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "subpub1");
	ros::NodeHandle n;
        ros::Publisher publisher = n.advertise<nav_msgs::Odometry>("catbot/odom", 1000);
        
	ros::Subscriber subscriber = n.subscribe("/catbot/joint_states", 10, sCallback);
	ros::Rate loop_rate(10);
        while (ros::ok())
          { current_time = ros::Time::now();
            vl=vl_a*R;
            vr=vr_a*R ;       
            double dt = (current_time - last_time).toSec();   
        
            vx=.5*(vl+vr)*cos(th);
            x=x+.5*(vl+vr)*cos(th)*dt;//2.5;
            
            vy=.5*(vl+vr)*sin(th);
            y=y+.5*(vl+vr)*sin(th)*dt;//2.5;
           
            vth=(1/D)*(vr-vl);
            th=th+(.5)*(1/D)*(vr-vl)*dt;
            cout<< "x= " << x<<"  " <<"vx = " <<vx<<"    "<<"y = " <<y<<"  " <<"vy = " <<vy<<endl; //*

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
}


