






#include "tf/transform_broadcaster.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "gazebo_msgs/ModelStates.h"
#include "sensor_msgs/JointState.h"

///gazebo/catbot/joint_states
//sensor_msgs/JointState



double x=0;
double y=0;
double t=0;
using namespace std;

void chatterCallback(const gazebo_msgs::ModelStates::ConstPtr & modmsg)
//void chatterCallback(const sensor_msgs::JointState::ConstPtr & modmsg)
{
    
//modmsg->pose.orientation.w
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

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/gazebo/model_states", 1000, chatterCallback);
  ros::spin();

  return 0;
}


//
//#include "ros/ros.h"
//#include "geometry_msgs/Twist.h"
//#include "gazebo_msgs/ModelState.h"
//#include "nav_msgs/Odometry.h"
//#include <sstream>
//#include "tf/transform_broadcaster.h"
//#include <ros/ros.h>
//#include "math.h"
//
//using namespace std;
////subto -> /catbot/imu_data
////msg->sensor_msgs/Imu
//
////pubto ->catbot/odom
////msg-> nav_msgs/Odometry.msg
//
//ros::Publisher publisher;
//ros::Subscriber subscriber;
//double x=0;
//double y=0;
//double th=0;
////void sCallback(const turtlesim::Pose::ConstPtr & pose_message);
//void sCallback(const gazebo_msgs::ModelState::ConstPtr & modmsg)
//{  
//        cout<<"x="<<endl;
//}
//
//int main(int argc, char **argv)
//{       
//	ros::init(argc, argv, "ttt");
//	ros::NodeHandle n;
//        double rate=10;
//	ros::Subscriber subscriber = n.subscribe("/gazebo/model_states",rate, sCallback);
//	ros::Rate loop_rate(rate);
//        while (ros::ok())
//          { 
//           ros::spinOnce();
//           loop_rate.sleep();
//          }
//        
//  return 0;
//
//	
//
//   return 0;
//}
//
//
//

