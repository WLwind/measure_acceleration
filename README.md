# measure_acceleration
A ROS package for measuring linear or angular acceleration of a robot via odom and imu sensors. If you want to use this package to get the max acceleration of you robot, make sure your robot is equipped with imu and odom sensors.
##Launch files
*measure_linear_acceleration.launch
Activate this file the robot will move foward untill it reaches its max speed and print the max linear acceleration on the screen.
*measure_angular_acceleration.launch
Activate this file the robot will rotate untill it reaches its max angular speed and print the max angular acceleration on the screen.
##Arguments
1.imu_topic
The topic published from imu sensor (sensor_msgs/Imu)
2.odom_topic
The topic published from odom sensor (nav_msgs/Odometry)
3.cmd_vel_topic
The topic published to the robot mobile base (geometry_msgs/Twist)
4.max_vel
Max velocity that the robot can accelerate to. Check the manual of the robot to acquire the official specification.
5.axis
The axis of the acceleration value you want to measure according to the frame of imu sensor.
__All the default argements are appropriate with Turtlebot3__