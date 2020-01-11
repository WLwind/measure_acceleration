#include <measure_acceleration/MeasureAngularAcc.h>

MeasureAngularAcc::MeasureAngularAcc():MeasureAngularAcc(2.75)//delegating constructor
{
    last_moment=ros::Time::now();
}

void MeasureAngularAcc::imuCallback(const sensor_msgs::Imu::ConstPtr& imu_message)
{
    ros::Time current_moment(ros::Time::now());
    m_cmd_vel_mutex.lock();
    if(first_time)
    {
        first_time=false;
        cmd_vel_message.angular.z=getMaxVelocity();//start moving the robot
    }
    else
    {
        ros::Duration duration(current_moment-last_moment);
        if(accaxis=="z")
        {
            if(imu_message->angular_velocity.z>last_vel)
            {
                double ang_acc=(imu_message->angular_velocity.z-last_vel)/duration.toSec();//calculate the angular acceleration
                if(ang_acc>getMaxAcc())
                {
                    setMaxAcc(ang_acc);
                    ROS_INFO("Angular acceleration: %.3f",ang_acc);
                }
            }
            last_vel=imu_message->angular_velocity.z;
        }
        else if(accaxis=="-z")
        {
            if(-imu_message->angular_velocity.z>last_vel)
            {
                double ang_acc=(-imu_message->angular_velocity.z-last_vel)/duration.toSec();//calculate the angular acceleration
                if(ang_acc>getMaxAcc())
                {
                    setMaxAcc(ang_acc);
                    ROS_INFO("Angular acceleration: %.3f",ang_acc);
                }
            }
            last_vel=-imu_message->angular_velocity.z;
        }
        else if(accaxis=="x")
        {
            if(imu_message->angular_velocity.x>last_vel)
            {
                double ang_acc=(imu_message->angular_velocity.x-last_vel)/duration.toSec();//calculate the angular acceleration
                if(ang_acc>getMaxAcc())
                {
                    setMaxAcc(ang_acc);
                    ROS_INFO("Angular acceleration: %.3f",ang_acc);
                }
            }
            last_vel=imu_message->angular_velocity.x;
        }
        else if(accaxis=="-x")
        {
            if(-imu_message->angular_velocity.x>last_vel)
            {
                double ang_acc=(-imu_message->angular_velocity.x-last_vel)/duration.toSec();//calculate the angular acceleration
                if(ang_acc>getMaxAcc())
                {
                    setMaxAcc(ang_acc);
                    ROS_INFO("Angular acceleration: %.3f",ang_acc);
                }
            }
            last_vel=-imu_message->angular_velocity.x;
        }
        else if(accaxis=="y")
        {
            if(imu_message->angular_velocity.y>last_vel)
            {
                double ang_acc=(imu_message->angular_velocity.y-last_vel)/duration.toSec();//calculate the angular acceleration
                if(ang_acc>getMaxAcc())
                {
                    setMaxAcc(ang_acc);
                    ROS_INFO("Angular acceleration: %.3f",ang_acc);
                }
            }
            last_vel=imu_message->angular_velocity.y;
        }
        else if(accaxis=="-y")
        {
            if(-imu_message->angular_velocity.y>last_vel)
            {
                double ang_acc=(-imu_message->angular_velocity.y-last_vel)/duration.toSec();//calculate the angular acceleration
//                std::cout<<ang_acc<<std::endl;
                if(ang_acc>getMaxAcc())
                {
//                    ROS_INFO("duration=%f",duration.toSec());
//                    ROS_INFO("vel=%f,last_vel=%f",-imu_message->angular_velocity.y,last_vel);
                    setMaxAcc(ang_acc);
                    ROS_INFO("Angular acceleration: %.3f",ang_acc);
                }
            }
            last_vel=-imu_message->angular_velocity.y;
        }
    }
    vel_pub.publish(cmd_vel_message);
    m_cmd_vel_mutex.unlock();
    last_moment=current_moment;
//    ROS_INFO("vel=%f",-imu_message->angular_velocity.y);
    return;
}

void MeasureAngularAcc::odomCallback(const nav_msgs::Odometry::ConstPtr& odom_msg)
{
//    ros::Time current_moment(ros::Time::now());
    m_cmd_vel_mutex.lock();
    if(first_time)
    {
        first_time=false;
        cmd_vel_message.angular.z=getMaxVelocity();//start moving the robot
    }
    m_cmd_vel_mutex.unlock();
/*    ros::Duration duration(current_moment-last_moment);
    double ang_acc=(odom_msg->twist.twist.angular.z-last_vel)/duration.toSec();//calculate the angular acceleration
    if(ang_acc>getMaxAcc())
    {
        setMaxAcc(ang_acc);
        ROS_INFO("Angular acceleration: %.3f",ang_acc);
    }*/
    if(odom_msg->twist.twist.angular.z>getMaxVelocity()*0.9)
    {
        ROS_INFO("Stop!");
        m_cmd_vel_mutex.lock();
        cmd_vel_message.angular.z=0.0;//stop the robot
        vel_pub.publish(cmd_vel_message);
        m_cmd_vel_mutex.unlock();
        ROS_INFO("Max angular acceleration is %.3f.",getMaxAcc());//result
        ros::shutdown();
    }
//    last_moment=current_moment;
//    last_vel=odom_msg->twist.twist.angular.z;
    return;
}