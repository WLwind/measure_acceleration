#pragma once

#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Imu.h>
#include <nav_msgs/Odometry.h>
#include <string>
#include <mutex>

class MeasureAcceleration
{
public:
    MeasureAcceleration(double);
    double getMaxAcc();//get max_acc
    void setMaxAcc(double);//set max_acc
    double getMaxVelocity() const;//get max_velocity
    virtual void imuCallback(const sensor_msgs::Imu::ConstPtr&)=0;//Callback for imu subscriber,calculate the max acceleration
    virtual void odomCallback(const nav_msgs::Odometry::ConstPtr&)=0;//measure the velocity to decide whether to stop or not
    virtual ~MeasureAcceleration(){}
private:
    ros::NodeHandle nh;//node handle
    double max_velocity{0.0};//the goal velocity you want your robot to move
    double max_acc{0.0};//the result of max acceleration
    std::mutex m_acc_mutex;
protected:
    bool first_time{true};//first time runing callback function mark
    ros::Subscriber imu_sub{nh.subscribe<sensor_msgs::Imu>("imu",1,boost::bind(&MeasureAcceleration::imuCallback,this,_1))};//subscriber to imu topic
    ros::Publisher vel_pub{nh.advertise<geometry_msgs::Twist>("cmd_vel",1)};//publisher to velocity topic, controls the robot moving
    ros::Subscriber odom_sub{nh.subscribe<nav_msgs::Odometry>("odom",1,boost::bind(&MeasureAcceleration::odomCallback,this,_1))};//subscriber to odometry topic
    geometry_msgs::Twist cmd_vel_message;//message for vel_pub to publish
    std::mutex m_cmd_vel_mutex;//mutex for cmd_vel_message
    std::string accaxis;
};