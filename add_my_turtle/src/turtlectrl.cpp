#include "ros/ros.h" 			 // ROS 的基本头文件
#include <cstdlib> 			     // 使用 atoll 函数所需的库
#include <turtlesim/Spawn.h>
#include <turtlesim/Pose.h>
#include <geometry_msgs/Twist.h>

void posecallback ( const turtlesim::Pose::ConstPtr& msg)
{
	ROS_INFO ( "recieve msg = %0.2f" , msg->x );	
	ROS_INFO ( "recieve msg = %0.2f" , msg->y );		
	ROS_INFO ( "recieve msg = %0.2f" , msg->theta );		
    ROS_INFO ( "recieve msg = %0.2f" , msg->angular_velocity );		
	ROS_INFO ( "recieve msg = %0.2f" , msg->linear_velocity );        
}


int main ( int argc , char ** argv )
{
    ros::init ( argc , argv , "turtlectrl" );		     // 初始化节点名称
    ros::NodeHandle nh ;
    // 服务客户端 turtlectrl_client 。
    // 服务名称是 "spawn"
    ros::service::waitForService("spawn");
    ros::ServiceClient turtlectrl_client = nh.serviceClient < turtlesim::Spawn >( "spawn" );

    turtlesim::Spawn srv;
    srv.request.x = 5;
    srv.request.y = 5;
    srv.request.name = "turtle2";
    srv.request.theta = 0;
    // 请求增加海龟
    int ret = turtlectrl_client.call( srv );
    if (!ret)
    {
        ROS_INFO ("Request Failed!~~~");
        return -1;
    }
    else
        ROS_INFO ("Request Successed!~~~");
    // 订阅我创建的乌龟的信息
    ros::Subscriber sub = nh.subscribe( "turtle2/pose" , 10 , posecallback );
    // 定义乌龟轨迹的发布器
    ros::Publisher turtle_vel = nh.advertise<geometry_msgs::Twist>( "turtle2/cmd_vel", 10);
    // 创建要发布的信息
    geometry_msgs::Twist vel;
    ros::Rate r(10); // 10Hz的间隔 delay 100ms
    int count = 0;

    while(true)
    {
        if (count == 10)
        {
            vel.linear.x = 0;
            vel.angular.z = 0;
            turtle_vel.publish( vel );
        }
        else
        {
            vel.linear.x = 3;
            vel.angular.z = 3.14;
            turtle_vel.publish( vel );
            count++;
        }
        r.sleep();
    }

    return 0 ;
}