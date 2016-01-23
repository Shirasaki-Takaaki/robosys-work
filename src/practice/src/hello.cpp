#include "ros/ros.h"
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>
using namespace std;

#define PAI atan2(0.0, -1.0)
//#define deg(r) ((r)/PAI*180.0)
//#define rad(d) ((d)/180.0*PAI)

class turtleSim{
public:
	turtleSim();
	~turtleSim();
	void poseCallback(const turtlesim::PoseConstPtr& pose);
	void move(double speed, double distance, bool isForward);
	void rotate(double ang_speed, double angule, bool cw);
	void timerCallback(const ros::TimerEvent&);

private:
	ros::Publisher twist_pub;
	ros::Subscriber pose_sub;
	ros::Timer timer;
	ros::NodeHandle nh;

	int point_num;
	double po_x, po_y, po_theta;
};

turtleSim::turtleSim(){
	twist_pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel",1000);
	pose_sub = nh.subscribe<turtlesim::Pose>("turtle1/pose", 1, &turtleSim::poseCallback, this);
	timer = nh.createTimer(ros::Duration(0,1), &turtleSim::timerCallback, this);

	geometry_msgs::Twist twist;
	twist.linear.x = 0.0;
	twist.linear.y = 0.0;
	twist.linear.z = 0.0;
	twist.angular.x = 0.0;
	twist.angular.y = 0.0;
	twist.angular.z = 0.0;
	twist_pub.publish(twist);

	point_num = 0;
}

turtleSim::~turtleSim(){

}

void turtleSim::poseCallback(const turtlesim::PoseConstPtr& pose){
	//ROS_INFO("x:%f, y:%f, theta:%f", pose->x, pose->y, pose->theta);

}

void turtleSim::timerCallback(const ros::TimerEvent&){

}

void turtleSim::move(double speed, double distance, bool isForward){
	geometry_msgs::Twist twist;

	if(isForward)
		twist.linear.x = abs(speed);
	else
		twist.linear.x = -abs(speed);

	double t0 = ros::Time::now().toSec();
	double current_dis = 0.0;

	ros::Rate loop_rate(100);
	do{
		twist_pub.publish(twist);
	double t1 = ros::Time::now().toSec();
	current_dis = speed * (t1 - t0);
	ros::spinOnce();
	loop_rate.sleep();
	}while(current_dis < distance);

	twist.linear.x = 0;
	twist_pub.publish(twist);
}

void turtleSim::rotate(double ang_speed, double angule, bool cw){
	geometry_msgs::Twist twist;

	if(cw)
		twist.angular.z = -abs(ang_speed);
	else
		twist.angular.z = abs(ang_speed);

	double t0 = ros::Time::now().toSec();
	double current_ang = 0.0;

	ros::Rate loop_rate(100);
	do{
		twist_pub.publish(twist);
	double t1 = ros::Time::now().toSec();
	current_ang = ang_speed * (t1 - t0);
	ros::spinOnce();
	loop_rate.sleep();
	}while(current_ang < angule);

	twist.angular.z = 0;
	twist_pub.publish(twist);
}

int main(int argc, char **argv){
	double speed, distance;
	double ang_speed, angule;
	bool isForward;
	bool cw;

	ros::init(argc, argv, "hello");
	turtleSim turtlesim;

	cout << "enter speed: ";
	cout << "enter distance: ";
	cout << "isForward?: ";
	turtlesim.move(1, 2, 1);	//速度,距離,方向

	cout << "enter ang_speed(deg/sec): ";
	cout << "enter angule(deg): ";
	cout << "clockwise?: ";
	turtlesim.rotate(5, 120*PAI/180, 0);	//角速度，角度，回転方向

	cout << "enter speed: ";
	cout << "enter distance: ";
	cout << "isForward?: ";
	turtlesim.move(1, 4, 1);	//速度,距離,方向

	cout << "enter ang_speed(deg/sec): ";
	cout << "enter angule(deg): ";
	cout << "clockwise?: ";
	turtlesim.rotate(5, 120*PAI/180, 0);	//角速度，角度，回転方向

	cout << "enter speed: ";
	cout << "enter distance: ";
	cout << "isForward?: ";
	turtlesim.move(1, 4, 1);	//速度,距離,方向

	cout << "enter ang_speed(deg/sec): ";
	cout << "enter angule(deg): ";
	cout << "clockwise?: ";
	turtlesim.rotate(5, 120*PAI/180, 0);	//角速度，角度，回転方向

	cout << "enter speed: ";
	cout << "enter distance: ";
	cout << "isForward?: ";
	turtlesim.move(1, 2, 1);	//速度,距離,方向

	ros::spin();
	return 0;

}

