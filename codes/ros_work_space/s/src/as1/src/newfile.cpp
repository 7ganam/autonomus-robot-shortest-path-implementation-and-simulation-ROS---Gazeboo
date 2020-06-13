#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/Imu.h"
#include "nav_msgs/Odometry.h"
#include <sstream>
#include "tf/transform_broadcaster.h"
#include <ros/ros.h>
#include "math.h"
using namespace std;
//subto -> /catbot/imu_data
//msg->sensor_msgs/Imu

//pubto ->catbot/odom
//msg-> nav_msgs/Odometry.msg

ros::Publisher publisher;
ros::Subscriber subscriber;

nav_msgs::Odometry odom;
ros::Time current_time, last_time;
double th ; 
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
//        vel.angular = roll;
          aa=imu_msg->linear_acceleration.x;
          th= yaw;
          //ax= imu_msg->linear_acceleration.x;
//          ay=imu_msg->linear_acceleration.y;
          //ax=aa*cos(th);
          //ay=aa*sin(th);
          if(abs(ax)<.00005)
                ax=0;
          if(abs(ay)<.00005)
                ay=0;
          if(abs(aa)<.00005)
                ax=0;
          if(abs(aa)<.00005)
                aa=0;
  
//    vl_a=joint_msg->velocity[0];
//    vr_a=joint_msg->velocity[1];
  
}

int main(int argc, char **argv)
{
        
	ros::init(argc, argv, "imu");
	ros::NodeHandle n;
        double rate=1000;
        ros::Publisher publisher = n.advertise<nav_msgs::Odometry>("catbot/odom", rate);
        
	ros::Subscriber subscriber = n.subscribe("/catbot/imu_data",rate, sCallback);
	ros::Rate loop_rate(rate);
        while (ros::ok())
          { current_time = ros::Time::now();
//            double ax_current=ax;
//            double ay_current=ay;
            double aa_current=aa;
            double dt = (current_time - last_time).toSec();
            if(aa_current==0 && aa_last==0  )
                va=0;
                vx=0;
                vy=0;
//            if(ax_current==0 && ax_last==0  )
//                vx=0;
//            if(  ay_current==0 && ay_last )    
//                vy=0;
            va=va+aa*dt;
            double d=va*dt;
            double D=D+d;
            //vx=vx+va*cos(th)*dt;
            //vx=va*cos(th);
            //x=x+ vx*dt;
            //vy=vy+va*sin(th)*dt;
            //vy=vy+ax*sin(th)*dt;
            //vy=va*sin(th);
            //y=y+ vy*dt;
            x=x+d*cos(th);
            y=y+d*sin(th);
            ax_last=ax_current;
            ay_last=ay_current;
            aa_last=ay_current;
            cout<< "x= " << x<<setw(17)
                    <<"y = " <<y<<"  " <<setw(17)<<endl;


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
            odom.twist.twist.angular.z = th;


            last_time=current_time;
            publisher.publish(odom);
            ros::spinOnce();
            loop_rate.sleep();
          }
  return 0;

	

   return 0;
}



