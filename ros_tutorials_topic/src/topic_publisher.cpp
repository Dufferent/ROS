# include "ros/ros.h" 					 				 // ROS 默认头文件
# include "ros_tutorials_topic/MsgTutorial.h" 	         // MsgTutorial 消息头文件( 构建后自动生成)
int main ( int argc , char ** argv )			         // 节点主函数
{
	ros::init ( argc , argv , "topic_publisher" );		
	ros::NodeHandle nh;					

// 初始化节点名称
// 声明一个节点句柄来与 ROS 系统进行通信
// 声明发布者,创建一个使用 ros _ tutorials _ topic 功能包的 MsgTutorial 消息文件的
// 发布者 ros _ tutorial _ pub 。话题名称是 "ros _ tutorial _ msg" ,
// 消息文件发布者队列( queue )的大小设置为 100
	ros::Publisher ros_tutorial_pub = nh.advertise<ros_tutorials_topic::MsgTutorial>( "ros_tutorial_msg" , 100 );
// 设定循环周期。 "10" 是指 10Hz ,是以 0 . 1 秒间隔重复
	ros::Rate loop_rate ( 10 );
	ros_tutorials_topic::MsgTutorial msg;	 // 以 MsgTutorial 消息文件格式声明一个 叫做 msg 的消息
	int count = 0 ; // 声明要在消息中使用的变量
			
	while ( ros::ok())
	{
		msg.stamp = ros::Time::now();			
		msg.data = count ; 				
// 把当前时间传给 msg 的下级消息 stamp
// 将变量 count 的值传给下级消息 data
		ROS_INFO ( "send msg = %d" , msg.stamp.sec ); 	 // 显示 stamp . sec 消息
		ROS_INFO ( "send msg = %d" , msg.data ); 		 // 显示 data 消息
		ROS_INFO ( "send msg = %d" , msg.stamp.nsec ); 	
	
	
// 显示 stamp . nsec 消息
		ros_tutorial_pub.publish ( msg );		 // 发布消息。
		loop_rate.sleep ();						 // 按照上面定义的循环周期进行暂歇
		++count;								 // 变量 count 增加 1
	}
	return 0;
}
