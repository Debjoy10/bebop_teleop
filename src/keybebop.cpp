#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include<iostream>

using namespace std;

int getch(void)
{
 int ch;
 struct termios oldt;
 struct termios newt;
 tcgetattr(STDIN_FILENO, &oldt); /*store old settings */
 newt = oldt; /* copy old settings to new settings */
 newt.c_lflag &= ~(ICANON | ECHO); /* make one change to old settings in new settings */
 tcsetattr(STDIN_FILENO, TCSANOW, &newt); /*apply the new settings immediatly */
 ch = getchar(); /* standard getchar call */
 tcsetattr(STDIN_FILENO, TCSANOW, &oldt); /*reapply the old settings */
 return ch; /*return received char */
}

int main(int argc, char **argv)
{
  
	ros::init(argc, argv, "talker");
	ros::NodeHandle n;

	ros::Publisher directions = n.advertise<std_msgs::String>("Arrow", 1);
	ros::Publisher cmd = n.advertise<geometry_msgs::Twist>("/bebop/cmd_vel",1);
	ros::Rate loop_rate(10);
	int count = 0;
 
	int x = ' ';
	int y = ' ';
	int z = ' ';

	while (ros::ok())
	{
  		std_msgs::String msg;
  		geometry_msgs::Twist com;
  		std::stringstream ss;
 
		x = getch();
		if(x == 44)
		{
			ss << "ccw";
			com.linear.x = 0;
      		com.linear.y = 0;
       		com.linear.z = 0;
       		com.angular.x = 0;
       		com.angular.y = 0;
       		com.angular.z = 0.01;
		}	
		if(x == 46)
		{
			ss << "cw";
			com.linear.x = 0;
      		com.linear.y = 0;
       		com.linear.z = 0;
       		com.angular.x = 0;
       		com.angular.y = 0;
       		com.angular.z = -0.01;
		}	
		if(x == 32)
		{
			ss << "hover";
			com.linear.x = 0;
      		com.linear.y = 0;
       		com.linear.z = 0;
       		com.angular.x = 0;
       		com.angular.y = 0;
       		com.angular.z = 0;
		}
		if(x == 97)
		{
			ss << "ascend";
			com.linear.x = 0;
      		com.linear.y = 0;
       		com.linear.z = 0.01;
       		com.angular.x = 0;
       		com.angular.y = 0;
       		com.angular.z = 0;
		}	
		if(x == 100)
		{
			ss << "descend";
			com.linear.x = 0;
      		com.linear.y = 0;
       		com.linear.z = -0.01;
       		com.angular.x = 0;
       		com.angular.y = 0;
       		com.angular.z = 0;
		}		
		if (x == 27)
 		{
  			y = getch();
  			z = getch();
 		}

 		if (x == 27 && y == 91)
 		{
  			switch (z)
  			{
   				case 65:
   				ss << "up";
   				com.linear.x = 0.01;
        		com.linear.y = 0;
        		com.linear.z = 0;
        		com.angular.x = 0;
        		com.angular.y = 0;
        		com.angular.z = 0;
  			 	break;
	
   				case 66:
   				ss << "down" ;
   				com.linear.x = -0.01;
        		com.linear.y = 0;
        		com.linear.z = 0;
        		com.angular.x = 0;
        		com.angular.y = 0;
        		com.angular.z = 0;
   				break;
	
   				case 67:
   				ss <<"right";
   				com.linear.x = 0;
        		com.linear.y = -0.01;
        		com.linear.z = 0;
        		com.angular.x = 0;
        		com.angular.y = 0;
        		com.angular.z = 0;
   				break;
   				
   				break;
	
   				case 68:
   				ss <<"left";
   				com.linear.x = 0;
        		com.linear.y = 0.01;
        		com.linear.z = 0;
        		com.angular.x = 0;
        		com.angular.y = 0;
        		com.angular.z = 0;
   				break;
  			}
 		}
  		msg.data = ss.str();
  		ROS_INFO("%s", msg.data.c_str());
  		directions.publish(msg);
  		cmd.publish(com);
  		ros::spinOnce();
	
  		loop_rate.sleep();
  		++count;
	}
	
  return 0;
}

