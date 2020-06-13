#include "std_msgs/Float32.h"
#include "std_msgs/Float64.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/JointState.h"
#include "sensor_msgs/LaserScan.h"
#include <sstream>
#include "tf/transform_broadcaster.h"
#include <ros/ros.h>
#include "math.h"

//  /catbot/laser/scan
//  sensor_msgs/LaserScan

using namespace std;
float msg[179];
float M;
float maxof( float b[], int sizeOfArray )
{
  float temp = 0;
    for(int i=0;i<sizeOfArray ;i++)
    {
        if(b[i]>temp)
        temp=b[i];
    }
    return temp;
}

void sCallback(const sensor_msgs::LaserScan::ConstPtr & l_msg);

int main(int argc, char **argv)
{
        ros::init(argc, argv, "laser");
	ros::NodeHandle n;
        ros::Publisher publisher = n.advertise<std_msgs::Float64>("catbot/laser", 1000);
      	ros::Subscriber subscriber = n.subscribe("/catbot/laser/scan", 10, sCallback);
	ros::Rate loop_rate(10);
        while (ros::ok())
          {
            
            M= maxof(msg,179);
            std_msgs::Float64 MM ;
            MM.data=M;
            publisher.publish(MM);
            ros::spinOnce();
            loop_rate.sleep();
          }
  
   return 0;
}

void sCallback(const sensor_msgs::LaserScan::ConstPtr & l_msg)
{  
    

    for(int i=0;i<180 ;i++)
    {
        msg[i]=l_msg->ranges[i];
    }
}

