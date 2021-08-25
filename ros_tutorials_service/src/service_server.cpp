#include "ros/ros.h"
#include "ros_tutorials_service/RosService.h"
#include "ros_tutorials_service/RosServiceRequest.h" 	
#include "ros_tutorials_service/RosServiceResponse.h" 

bool calculation ( ros_tutorials_service::RosService::Request & req ,ros_tutorials_service::RosService::Response & res )
{
    
// 在收到服务请求时,将 a 和 b 的和保存在服务响应值中
    res.result = req.a + req.b ;
// 显示服务请求中用到的 a 和 b 的值以及服务响应 result 值
    ROS_INFO ( "request : x =% ld , y =%ld" , ( long int ) req.a , ( long int ) req.b );
    ROS_INFO ( "sending back response : %ld" , ( long int ) res.result );
    return true ;
}

int main ( int argc , char ** argv )
{
		
    ros::init ( argc , argv , "service_server" ); 	
    ros::NodeHandle nh ;
		
// 节点主函数
// 初始化节点名称
// 声明节点句柄
// 声明服务服务器
// 声明利用 ros _ tutorials _ service 功能包的 SrvTutorial 服务文件的
// 服务服务器 ros _ tutorials _ service _ server
// 服务名称是 ros _ tutorial _ srv ,且当有服务请求时,执行 calculation 函数。
    ros::ServiceServer ros_tutorials_service_server = nh.advertiseService ( "ros_tutorial_srv",calculation );
    ROS_INFO ( "ready srv server ! " );
    ros::spin (); // 等待服务请求
    return 0 ;
}