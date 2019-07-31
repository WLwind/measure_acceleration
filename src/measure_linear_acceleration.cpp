#include <measure_acceleration/MeasureLinearAcc.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "measure_linear_acceleration");
    MeasureLinearAcc mlacc(atof(argv[1]));
    ros::MultiThreadedSpinner spinner(2);
    spinner.spin();
    return 0;
}