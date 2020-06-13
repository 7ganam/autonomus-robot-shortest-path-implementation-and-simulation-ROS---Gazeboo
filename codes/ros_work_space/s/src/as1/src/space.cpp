#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "gazebo_msgs/ModelState.h"
#include "nav_msgs/Odometry.h"
#include <sstream>
#include "tf/transform_broadcaster.h"
#include <ros/ros.h>
#include "math.h"


//subto -> / gazebo / set_model_state
//msg->gazebo_msgs/ModelState

//pub to-> /cmd_vel 
//msg->geometry_msgs/Twist

double x=0;
double y=0;
double th=0;
using namespace std;
void chatterCallback(const gazebo_msgs::ModelStates::ConstPtr & modmsg)

{
    
    tf::Quaternion bq(modmsg->pose[1].orientation.x, modmsg->pose[1].orientation.y, modmsg ->pose[1].orientation.z, modmsg->pose[1].orientation.w );
        double roll, pitch, yaw;
        tf::Matrix3x3(bq).getRPY(roll, pitch, yaw);
        modmsg->pose[1].orientation.w;
        th= yaw;
        x=modmsg->pose[1].position.x;
        cout<<"x="<<x<<endl;
        y=modmsg->pose[1].position.y;
        cout<<"y="<<y<<endl;
}

geometry_msgs::Twist geom;
int main(int argc, char **argv)
{
	ros::init(argc, argv, "goto");
	ros::NodeHandle n;
        ros::Publisher publisher = n.advertise<geometry_msgs::Twist>("states", 10);
        ros::Subscriber subscriber = n.subscribe("/gazebo/model_states", 10, sCallback);
//      ros::Subscriber subscriber = n.subscribe("/catbot/imu_data",rate, sCallback);
	ros::Rate loop_rate(10);
        
          while (ros::ok()) 
          { 
          geom.linear.x=x;
          geom.linear.y=y;
          geom.linear.z=0;
          geom.angular.x=0;
          geom.angular.y=0;
          geom.angular.z=th;
          
//          cout<<"x="<<x<<endl;
//          cout<<"y="<<y<<endl;
          publisher.publish(geom);         
          ros::spinOnce();
          loop_rate.sleep();
      
          
          }
   return 0;
}




