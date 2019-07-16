#include <measure_acceleration/MeasureLinearAcc.h>

MeasureLinearAcc::MeasureLinearAcc():MeasureLinearAcc(0.22)//delegating constructor
{}

void MeasureLinearAcc::imuCallback(const sensor_msgs::Imu::ConstPtr& imu_message)
{
    if(first_time)
    {
        setMaxAcc(imu_message->linear_acceleration.x);
        first_time=false;
        ROS_INFO("Start moving.");
        cmd_vel_message.linear.x=getMaxVelocity();//start moving the robot
    }
    else
    {
        if(accaxis=="x")
        {
            if(imu_message->linear_acceleration.x>getMaxAcc())
            {
                setMaxAcc(imu_message->linear_acceleration.x);
                ROS_INFO("Linear acceleration x: %.3f.",imu_message->linear_acceleration.x);
            }
        }
        else if(accaxis=="-x")
        {
            if(-imu_message->linear_acceleration.x>getMaxAcc())
            {
                setMaxAcc(-imu_message->linear_acceleration.x);
                ROS_INFO("Linear acceleration -x: %.3f.",-imu_message->linear_acceleration.y);
            }
        }
        else if(accaxis=="y")
        {
            if(imu_message->linear_acceleration.y>getMaxAcc())
            {
                setMaxAcc(imu_message->linear_acceleration.y);
                ROS_INFO("Linear acceleration y: %.3f.",imu_message->linear_acceleration.y);
            }
        }
        else if(accaxis=="-y")
        {
            if(-imu_message->linear_acceleration.y>getMaxAcc())
            {
                setMaxAcc(-imu_message->linear_acceleration.y);
                ROS_INFO("Linear acceleration -y: %.3f.",-imu_message->linear_acceleration.y);
            }
        }
        else if(accaxis=="z")
        {
            if(imu_message->linear_acceleration.z>getMaxAcc())
            {
                setMaxAcc(imu_message->linear_acceleration.z);
                ROS_INFO("Linear acceleration z: %.3f.",imu_message->linear_acceleration.z);
            }
        }
        else if(accaxis=="-z")
        {
            if(-imu_message->linear_acceleration.z>getMaxAcc())
            {
                setMaxAcc(-imu_message->linear_acceleration.z);
                ROS_INFO("Linear acceleration -z: %.3f.",-imu_message->linear_acceleration.z);
            }
        }
        else
        {
            ROS_WARN("accaxis is not a proper value.");
            std::cout<<accaxis<<std::endl;
        }        
    }
/*    else if(imu_message->linear_acceleration.x<getMaxAcc()/10.0&&getMaxAcc()>1.2)
    {
        cmd_vel_message.linear.x=0.0;//stop the robot
        vel_pub.publish(cmd_vel_message);
        ROS_INFO("Max linear acceleration is %.3f.",getMaxAcc());//result
        ros::shutdown();
    }*/
    vel_pub.publish(cmd_vel_message);
    return;
}


void MeasureLinearAcc::odomCallback(const nav_msgs::Odometry::ConstPtr& odom_msg)
{
    if(odom_msg->twist.twist.linear.x>getMaxVelocity()*0.9)
    {
        ROS_INFO("Stop!");
        cmd_vel_message.linear.x=0.0;//stop the robot
        vel_pub.publish(cmd_vel_message);
        ROS_INFO("Max linear acceleration is %.3f.",getMaxAcc());//result
        ros::shutdown();
    }
}