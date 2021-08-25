#include "ros/ros.h"
#include "ros_tutorials_topic_group/topic_launch.h"

int main(int argc,char** argv)
{
    ros::init(argc,argv,"topic_group_publisher");
    ros::NodeHandle nh;

    ros::Publisher ros_tutorials_pub = nh.advertise<ros_tutorials_topic_group::topic_launch>("topic_group_msg",100);
    ros::Rate r(10); // 10Hz

    ros_tutorials_topic_group::topic_launch msg;

    int count = 0;

    while (ros::ok())
    {
        msg.stamp = ros::Time::now();
        msg.count = count;
        ROS_INFO ( "send msg = %d" , msg.stamp.sec ); 	 // 显示 stamp . sec 消息
		ROS_INFO ( "send msg = %d" , msg.count ); 		 // 显示 data 消息
		ROS_INFO ( "send msg = %d" , msg.stamp.nsec ); 	
        count++;
        ros_tutorials_pub.publish<ros_tutorials_topic_group::topic_launch>(msg);
        r.sleep();
    }    


    return 0;
}