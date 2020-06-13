#include <ros/ros.h>
#include <tf/transform_datatypes.h>
#include "gazebo_msgs/ModelStates.h"
#include "sensor_msgs/JointState.h"
#include <sstream>
#include "math.h"




using namespace std;


double x_pos;
double y_pos;
double xnew;
double ynew;
double theta;
double vx;
double vy;
double vth;
double t0=0;
double yold=10;
double xold=0;
double theta_old=0;

double kp_p = M_PI/3, kp_a =18/2, kp_b = -0.05;
double kd_p = 0 ,kd_a = 0 ,kd_b = 0;
double kI_p = 0, kI_a = 0, kI_b = 0;
double prev_alpha = 0.00, prev_beta = 0.00, prev_rho = 0.00;

ros::Time current_time, last_time;
geometry_msgs::Twist geom;
geometry_msgs::TransformStamped tf_s;

void sCallback(const gazebo_msgs::ModelStates::ConstPtr& receivedMsg)

{
    geometry_msgs::PoseStamped poseMsg;

    for(size_t i = 0; i < receivedMsg->name.size(); ++i)
    {
      if (receivedMsg->name[i]=="catbot")
      {
        poseMsg.pose  = receivedMsg->pose [i];
      }
    }
    x_pos = poseMsg.pose.position.x;
    y_pos = poseMsg.pose.position.y;

    tf::Quaternion bq(poseMsg.pose.orientation.x, poseMsg.pose.orientation.y, poseMsg.pose.orientation.z, poseMsg.pose.orientation.w);
    double roll, pitch, yaw;
    tf::Matrix3x3(bq).getRPY(roll, pitch, yaw);

      theta= yaw;




}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "assignment");
	ros::NodeHandle n;
    double rate=100 ;
    ros::Publisher publisher = n.advertise<geometry_msgs::Twist>("/gazebo/catbot/velocity_command", 10);
    ros::Subscriber subscriber = n.subscribe("/gazebo/model_states", rate, sCallback);
    ros::Rate loop_rate(rate);
    double theta_new;
    double flag=0;
    while (ros::ok())
    {
        double dt = M_PI/5;

            ynew=(10*cos(t0+dt));
             xnew=(10*sin(t0+dt));
             theta_new=-(t0+dt);

        double dy=(ynew-y_pos);
        double dx=(xnew-x_pos);
        double dtheta=(theta_new-theta);
        //theta=theta+M_PI;

          double rho = sqrt(dy*dy + dx*dx);
          double alpha	= (-theta + atan2(dy, dx));
          double beta= ((-theta - alpha));

          double  drho	= rho	- prev_rho;
          double dbeta	= beta	- prev_beta;
          double dalpha	= alpha - prev_alpha;


          double rho_p	= rho	+ prev_rho;
          double beta_p	= beta	+ prev_beta;
          double alpha_p= alpha + prev_alpha;



          double v		= ((alpha < M_PI/2) && (alpha > -M_PI/2))? (kp_p * rho + kd_p * drho) :
                                                             -(kp_p * rho + kd_p * drho);
          double w		= -((kp_a * alpha + kd_a * dalpha)+ (kp_b * beta + kd_a * dbeta));


          if (fabs(theta)>=3.05)
          {

              v=0;
              w=1;
          }

          if ((abs(dx)<0.3) && (abs(dy)<0.3) )
          {

          t0=t0+dt;}


          geom.linear.x  = v;
          geom.linear.y  = 0;
          geom.linear.z  = 0;

          geom.angular.x = 0;
          geom.angular.y = 0;
          geom.angular.z = w;

          cout<<  dx <<"s"<< dy  <<"ss"<<dalpha<<"sss"<<theta<<";;"<<theta_new<<endl;
          publisher.publish(geom);

           yold=ynew;
           xold=xnew;
           theta_old=theta_new;
           ros::spinOnce();
           loop_rate.sleep();




}

}



