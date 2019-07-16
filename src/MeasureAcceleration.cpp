#include <measure_acceleration/MeasureAcceleration.h>

MeasureAcceleration::MeasureAcceleration(double velocity):max_velocity(velocity)
{
    ROS_INFO("The max velocity is set to %.3f",velocity);
    if(ros::param::get("~acc_axis", accaxis))
    {
        std::cout<<"acc_axis="<<accaxis<<std::endl;
    }
    else
    {
        ROS_ERROR("Axis of measurement is not set! Please confirm that the launch file is correct.");
    }
}

double MeasureAcceleration::getMaxAcc() const
{
    return max_acc;
}

void MeasureAcceleration::setMaxAcc(double x)
{
    max_acc=x;
    return;
}

double MeasureAcceleration::getMaxVelocity() const
{
    return max_velocity;
}