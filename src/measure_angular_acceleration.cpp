#include <measure_acceleration/MeasureAngularAcc.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "measure_angular_acceleration");
    MeasureAngularAcc mlacc(atof(argv[1]));
    ros::MultiThreadedSpinner spinner(2);
    spinner.spin();
    return 0;
}