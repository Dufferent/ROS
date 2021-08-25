#include "ros/ros.h"
#include "ros_tutorials_topic_group/topic_launch.h"

void msgcallback(const ros_tutorials_topic_group::topic_launch::ConstPtr &msg)
{
    ROS_INFO ( "recieve msg = %d" , msg->stamp.sec );		     // 显示 stamp.sec 消息
	ROS_INFO ( "recieve msg = %d" , msg->stamp.nsec );		
	ROS_INFO ( "recieve msg = %d" , msg->count );		         // 显示 data 消息
}

int main(int argc,char** argv)
{
    ros::init(argc,argv,"topic_group_subscriber");
    ros::NodeHandle nh;

    ros::Subscriber ros_tutorials_sub = nh.subscribe("topic_group_msg",100,msgcallback);
    ros::spin();

    return 0;
}