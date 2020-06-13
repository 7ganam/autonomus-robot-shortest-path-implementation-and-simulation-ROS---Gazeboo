#include <ros/ros.h>
#include <geometry_msgs/PointStamped.h>
#include <tf/transform_listener.h>

void transformPoint(const tf::TransformListener& listener)
{
  //we'll create a point in the base_laser frame that we'd like to transform to the base_link frame
  geometry_msgs::PointStamped localpoint;
  localpoint.header.frame_id = "base_link";

  //we'll just use the most recent transform available for our simple example
  localpoint.header.stamp = ros::Time();

  //just an arbitrary point in space
 localpoint.point.x = 1.0;
  localpoint.point.y = 0.2;
  localpoint.point.z = 0.0;

  try{
    geometry_msgs::PointStamped map_point;
    listener.transformPoint("base_link",localpoint, map_point);

    ROS_INFO("base_link: (%.2f, %.2f. %.2f) -----> map: (%.2f, %.2f, %.2f) at time %.2f",
        localpoint.point.x, localpoint.point.y, localpoint.point.z,
        map_point.point.x, map_point.point.y, map_point.point.z, map_point.header.stamp.toSec());
  }
  catch(tf::TransformException& ex){
    ROS_ERROR("Received an exception trying to transform a point from \"base_link\" to \"map\": %s", ex.what());
  }
}

int main(int argc, char** argv){
  ros::init(argc, argv, "listner");
  ros::NodeHandle n;

  tf::TransformListener listener(ros::Duration(10));
  //we'll transform a point once every second
  ros::Timer timer = n.createTimer(ros::Duration(1.0), boost::bind(&transformPoint, boost::ref(listener)));

  ros::spin();

}
