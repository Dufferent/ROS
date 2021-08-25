#include <ros/ros.h>					             // ROS 的基本头文件
#include <actionlib/client/terminal_state.h> 		 // 动作目标状态头文件
#include <actionlib/client/simple_action_client.h> 	
#include <ros_tutorials_action/TutorialsActAction.h> 	

// 动作库头文件
// FibonacciAction 动作头文件(构建后自动生成)
// 节点主函数
int main ( int argc , char ** argv ) 			
{
    ros::init( argc , argv , "action_client" ); 		

    // 初始化节点名称
    // 声明动作客户端(动作名称: ros _ tutorial _ action )
    actionlib::SimpleActionClient<ros_tutorials_action::TutorialsActAction>ac( "ros_tutorials_action" , true );
    ROS_INFO ( "Waiting for action server to start . " );
    ac.waitForServer (); 					
    ROS_INFO ( "Action server started , sending goal . " );
    // 等待动作服务器启动
    ros_tutorials_action::TutorialsActGoal goal ; 		 // 声明动作目标
    goal.order = 20; 	
    ac.sendGoal(goal);					 // 发送动作目标					
    // 指定动作目标(进行 20 次斐波那契运算)
    // 设置动作完成时间限制(这里设置为 30 秒)
    bool finished_before_timeout = ac.waitForResult ( ros::Duration( 30.0 ));
    // 在动作完成时限内收到动作结果值时
    if ( finished_before_timeout )
    {
        // 获取动作目标状态值并将其显示在屏幕上
        actionlib :: SimpleClientGoalState state = ac.getState();
        ROS_INFO ( "Action finished : %s" , state.toString().c_str());
        ros_tutorials_action::TutorialsActResultConstPtr res = ac.getResult();
        ROS_INFO ("ROS Result:[");
        for (int i=0;i<res->sequence.size();i++)
            ROS_INFO ( "%-2d",res->sequence[i]);
        ROS_INFO ("]");
    }
    else
        ROS_INFO ( "Action did not finish before the time out . " ); 	// 超过了动作完成时限的情况
    // exit
    return 0 ;
}