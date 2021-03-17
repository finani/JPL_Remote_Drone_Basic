//#include<iostream>

//#include <tf2/LinearMath/Quaternion.h>

#include <stdio.h>
#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <string.h>
#include <geometry_msgs/PoseStamped.h>

#include <iostream>
#include <vector>
#include <unistd.h>
#include <math.h>
#include <termios.h>
#include <fcntl.h>

using namespace std;

geometry_msgs::PoseStamped     mocap, mocap_temp;

ros::Subscriber mocap_sub;
ros::Publisher  mocap_pub;


void callback_mocap(const geometry_msgs::PoseStamped::ConstPtr& msg_input)
{
    mocap_temp = *msg_input;
    mocap.header = mocap_temp.header;
    mocap.pose.position.x = mocap_temp.pose.position.x;
    mocap.pose.position.y = mocap_temp.pose.position.y;
    mocap.pose.position.z = mocap_temp.pose.position.z;
    mocap.pose.orientation = mocap_temp.pose.orientation;
    mocap_pub.publish(mocap);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "tf_mocap_node");
    ros::NodeHandle nh_sub;
    ros::NodeHandle nh_pub;

    // Subscribe Topic
    mocap_sub = nh_sub.subscribe ("/vrpn_client_node/JPLDrone/pose", 2,  &callback_mocap);

    // Publish Topic
    mocap_pub = nh_pub.advertise<geometry_msgs::PoseStamped>("/mavros/vision_pose/pose", 2);

    //the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(100.0);

    while(ros::ok())
    {
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
