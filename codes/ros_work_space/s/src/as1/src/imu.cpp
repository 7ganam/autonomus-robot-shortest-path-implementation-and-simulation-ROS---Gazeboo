#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/Imu.h"
#include "nav_msgs/Odometry.h"
#include <sstream>
#include "tf/transform_broadcaster.h"
#include <ros/ros.h>
#include "math.h"
#include "as1/PP.h"
using namespace std;
//subto -> /catbot/imu_data
//msg->sensor_msgs/Imu

//pubto ->catbot/odom
//msg-> nav_msgs/Odometry.msg

ros::Publisher publisher;
ros::Subscriber subscriber;

as1::PP o;
ros::Time current_time, last_time;
double th=0; 
double ax=0;
double ay=0;
double vy=0;
double aa=0;
double vx=0;
double x=0;
double y=0;
double va=0;
double ax_current=0;
double ax_last=0;
double ay_last=0;
double ay_current=0;
double aa_current=0;
double aa_last=0;
//void sCallback(const turtlesim::Pose::ConstPtr & pose_message);
void sCallback(const sensor_msgs::Imu::ConstPtr & imu_msg)
{  

        tf::Quaternion bq(imu_msg->orientation.x, imu_msg->orientation.y, imu_msg ->orientation.z, imu_msg->orientation.w);
        double roll, pitch, yaw;
        tf::Matrix3x3(bq).getRPY(roll, pitch, yaw);
          aa=imu_msg->linear_acceleration.x;
          th= yaw;
          ax=aa*cos(th);
          ay=aa*sin(th);
          
          if(abs(ax)<.00005)
                ax=0;
          if(abs(ay)<.00005)
                ay=0;
          if(abs(aa)<.00005)
                ax=0;
          if(abs(aa)<.00005)
                aa=0;
  
}

int main(int argc, char **argv)
{
        
	ros::init(argc, argv, "imu");
	ros::NodeHandle n;
        double rate=10;
        ros::Publisher publisher = n.advertise<as1::PP>("catbot/dom", rate);
	ros::Subscriber subscriber = n.subscribe("/catbot/imu_data",rate, sCallback);
	ros::Rate loop_rate(rate);
        while (ros::ok())
          { current_time = ros::Time::now();
            double ax_current=ax;
            double ay_current=ay;
            double dt = (current_time - last_time).toSec();
         
            //to make sure the robot stops when no readings are sent
            if(ax_current==0 && ax_last==0  )
                vx=0;
            if(  ay_current==0 && ay_last==0 )    
                vy=0;
                
            vx=vx+ax*dt;
            x=x+ vx*dt;
            
            vy=vy+ay*dt;
            y=y+ vy*dt;
            
            
            ax_last=ax_current; ay_last=ay_current;


            cout<< "x= " << x<<setw(15)
                <<"y = " <<y<<"  " <<setw(15)
                <<"th = " <<th*180/3.141592<<"  " <<endl;
//            cout<< "x = " <<x<<endl;
//            cout<< "y = " <<y<<endl;
//            cout<< "vx = " <<vx<<endl; //8
//            cout<< "vy = " <<vy<<endl; //8
//            cout<< "ax = " <<ax<<endl; //*
//            cout<< "ay = " <<ay<<endl; //*
            //cout<< "th = " << th*180/3.141592 <<endl; //*

//            geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);
//            odom.header.stamp = current_time;
//            odom.header.frame_id = "base_footprint";
//            odom.pose.pose.position.x = x;
//            odom.pose.pose.position.y = y;
//            odom.pose.pose.position.z = 0.0;
//            odom.pose.pose.orientation = odom_quat;
//            odom.child_frame_id = "base_link";
//            odom.twist.twist.linear.x = vx;
//            odom.twist.twist.linear.y = vy;
//            odom.twist.twist.angular.z = th;
            o.velx=vx;
            o.vely=vy;
            o.posx=x;
            o.posy=y;
            last_time=current_time;
            publisher.publish(o);
            ros::spinOnce();
            loop_rate.sleep();
          }
  return 0;

	

   return 0;
}



