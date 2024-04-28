#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <nav_msgs/Odometry.h>

void odometryCallback(const nav_msgs::Odometry::ConstPtr& msg) {
  static ros::NodeHandle nh;
  static ros::Publisher pub = nh.advertise<geometry_msgs::TransformStamped>("transform", 1, true);

  geometry_msgs::TransformStamped transformStamped;
  transformStamped.header = msg->header;
    transformStamped.header.frame_id = "camera_init";
  transformStamped.child_frame_id = "body";
  
  // 将位置信息从Point类型赋值给Vector3类型
  transformStamped.transform.translation.x = msg->pose.pose.position.x;
  transformStamped.transform.translation.y = msg->pose.pose.position.y;
  transformStamped.transform.translation.z = msg->pose.pose.position.z;

  transformStamped.transform.rotation = msg->pose.pose.orientation;

  // 将变换后的消息发布出去
  pub.publish(transformStamped);
  ROS_INFO("successfully transformed");
  
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "odometry_to_transform");
  ros::NodeHandle nh;

  // 订阅Odometry消息
  ros::Subscriber sub = nh.subscribe<nav_msgs::Odometry>("Odometry", 1, odometryCallback);

  ros::spin();

  return 0;
}