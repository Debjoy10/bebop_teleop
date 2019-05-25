#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"

using namespace std;

void call_back_func(const geometry_msgs::Twist::ConstPtr& msg)
{
	ROS_INFO("You pressed [%f]", msg->linear.x );
}

int main(int argc, char **argv)
{

	ros::init(argc, argv, "listener");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("cmd_vel",1000,call_back_func);
	ros::spin();
	return 0;
}

