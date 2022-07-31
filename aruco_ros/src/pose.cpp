//Node to publish the aruco_result with the quad_odom
#include <iostream>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseWithCovariance.h>
#include <geometry_msgs/PoseStamped.h>
#include <ros/ros.h>
#include <aruco_msgs/Data.h>

geometry_msgs::Pose aruc;
geometry_msgs::Pose quad;
void sub_1(const geometry_msgs::PoseWithCovariance msg)
{   
    quad=msg.pose;
}
void sub_2(const geometry_msgs::PoseStamped msg)
{   
    aruc=msg.pose;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "talker");
    ros::NodeHandle n;
    ros::Publisher data_pub = n.advertise<aruco_msgs::Data>("pose_pose", 10);
    ros::Subscriber sub1 = n.subscribe("mavros/local_position/pose", 10, sub_1);
    ros::Subscriber sub2 = n.subscribe("aruco_single/pose", 10, sub_2);
    ros::Rate loop_rate(10);
    while (ros::ok())
    {
            aruco_msgs::Data pub_data;
            pub_data.aruco_pose=aruc;
            pub_data.quad_pose=quad;
            data_pub.publish(pub_data);
            ros::spinOnce();
            loop_rate.sleep();
    }
    return 0;
}