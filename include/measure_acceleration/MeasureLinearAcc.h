#pragma once

#include "MeasureAcceleration.h"

class MeasureLinearAcc:public MeasureAcceleration
{
public:
    using MeasureAcceleration::MeasureAcceleration;//inheritance constructor from base class
    MeasureLinearAcc();//constructor without arguments
    void imuCallback(const sensor_msgs::Imu::ConstPtr&) override;
    void odomCallback(const nav_msgs::Odometry::ConstPtr& odom_msg) override;
    virtual ~MeasureLinearAcc(){}
private:
    /* data */
};
