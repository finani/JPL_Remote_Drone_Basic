//#include<iostream>

//#include <tf2/LinearMath/Quaternion.h>

#include <stdio.h>
#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <string.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>

#include <iostream>
#include <vector>
#include <unistd.h>
#include <math.h>
#include <termios.h>
#include <fcntl.h>

using namespace std;

geometry_msgs::PoseStamped     rs_pose;
nav_msgs::Odometry             rs_odom;

ros::Subscriber rs_sub;
ros::Publisher  rs_pub;


void callback_rs(const nav_msgs::Odometry::ConstPtr& msg_input)
{
    rs_odom = *msg_input;
    rs_pose.header = rs_odom.header;
    rs_pose.pose.position.x = rs_odom.pose.pose.position.x;
    rs_pose.pose.position.y = rs_odom.pose.pose.position.y;
    rs_pose.pose.position.z = rs_odom.pose.pose.position.z;
    rs_pose.pose.orientation = rs_odom.pose.pose.orientation;
    rs_pub.publish(rs_pose);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "tf_rs_node");
    ros::NodeHandle nh_sub;
    ros::NodeHandle nh_pub;

    // Subscribe Topic
    rs_sub = nh_sub.subscribe ("/camera/odom/sample", 2,  &callback_rs);

    // Publish Topic
    rs_pub = nh_pub.advertise<geometry_msgs::PoseStamped>("/mavros/vision_pose/pose", 2);

    //the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(100.0);

    while(ros::ok())
    {
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
