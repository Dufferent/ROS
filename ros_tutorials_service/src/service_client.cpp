#include "ros/ros.h" 			 // ROS 的基本头文件
#include <cstdlib> 			     // 使用 atoll 函数所需的库
#include "ros_tutorials_service/RosService.h"
#include "ros_tutorials_service/RosServiceRequest.h" 	
#include "ros_tutorials_service/RosServiceResponse.h" 	
int main ( int argc , char ** argv )
{
			
// SrvTutorial 服务头文件(构建后自动生成)
// 节点主函数
    ros::init ( argc , argv , "service_client" );		 // 初始化节点名称
    if ( argc != 3 ) 						             // 处理输入值错误
    {
        ROS_INFO ( "cmd : rosrun ros_tutorials_service service_client arg0 arg1" );
        ROS_INFO ( "arg0 : double number , arg1 : double number" );
        return 1 ;
    }
    
    ros::NodeHandle nh ;
// 声明与 ROS 系统通信的节点句柄
// 声明客户端,声明利用 ros _ tutorials _ service 功能包的 SrvTutorial 服务文件的
// 服务客户端 ros _ tutorials _ service _ client 。
// 服务名称是 "ros _ tutorial _ srv"
    ros::ServiceClient ros_tutorials_service_client = nh.serviceClient < ros_tutorials_service::RosService>( "ros_tutorial_srv" );
// 声明一个使用 SrvTutorial 服务文件的叫做 srv 的服务
    ros_tutorials_service::RosService srv ;
// 在执行服务客户端节点时用作输入的参数分别保存在 a 和 b 中
    srv.request.a = atoll ( argv[1]);
    srv.request.b = atoll ( argv[2]);

// 请求服务,如果请求被接受,则显示响应值
    if ( ros_tutorials_service_client.call( srv ))
    {
        ROS_INFO ( "send srv , srv . Request . a and b : %ld , %ld" , ( long int ) srv.request.a , ( long int ) srv.request.b );
        ROS_INFO ( "receive srv , srv . Response . result : %ld" , ( long int ) srv.response.result );
    }
    else
    {
        ROS_ERROR ( "Failed to call service ros _ tutorial _ srv" );
        return 1 ;
    }

    return 0 ;
}