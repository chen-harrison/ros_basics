#include <ros/ros.h>
#include <std_srvs/Empty.h>
#include <geometry_msgs/Twist.h>


bool forward = true;

bool toggleForward(std_srvs::Empty::Request &req,
                   std_srvs::Empty::Response &resp)
{
    forward = !forward;
    ROS_INFO_STREAM("Now sending " << (forward ? "foward" : "rotate") << "commands.");
    return true;
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "pubvel_toggle");
    ros::NodeHandle nh;

    // register service with master
    ros::ServiceServer server = nh.advertiseService("toggle_forward", &toggleForward);

    // publish commands using latest value for forward
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
    ros::Rate rate(2);
    while (ros::ok()) {
        geometry_msgs::Twist msg;
        msg.linear.x = forward ? 1.0 : 0.0;
        msg.angular.z = forward ? 0.0 : 1.0;
        pub.publish(msg);

        ros::spinOnce();
        rate.sleep();
    }
}