#include "ExecutorImpl.hpp"

void vehicle::initialize_vehicle(int x, int y, char heading)
{
    x_ = x;
    y_ = y;
    heading_ = heading;
}

void vehicle::vehicle_move(char mode)
{
    if (mode == 'M') {
        if (heading_ == 'N')
            ++y_;
        else if (heading_ == 'S')
            --y_;
        else if (heading_ == 'E')
            ++x_;
        else if (heading_ == 'W')
            --x_;
    } else if (mode == 'L') {
        // 左转 90 度
        if (heading_ == 'N')
            heading_ = 'W';
        else if (heading_ == 'W')
            heading_ = 'S';
        else if (heading_ == 'S')
            heading_ = 'E';
        else if (heading_ == 'E')
            heading_ = 'N';
    } else if (mode == 'R') {
        // 右转 90 度
        if (heading_ == 'N')
            heading_ = 'E';
        else if (heading_ == 'E')
            heading_ = 'S';
        else if (heading_ == 'S')
            heading_ = 'W';
        else if (heading_ == 'W')
            heading_ = 'N';
    }
}

std::string
vehicle::vehicle_location()
{
    return to_string(x_) + " " + to_string(y_) + " " + heading_;
}