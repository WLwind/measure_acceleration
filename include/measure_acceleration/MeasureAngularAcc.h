#pragma once

#include "MeasureAcceleration.h"

class MeasureAngularAcc:public MeasureAcceleration
{
public:
    using MeasureAcceleration::MeasureAcceleration;//inheritance constructor from base class
    MeasureAngularAcc();//constructor without arguments
    void imuCallback(const sensor_msgs::Imu::ConstPtr&) override;
    void odomCallback(const nav_msgs::Odometry::ConstPtr& odom_msg) override;
    virtual ~MeasureAngularAcc(){}
private:
    double last_vel{0.0};//the velocity data got last time
    ros::Time last_moment;
};