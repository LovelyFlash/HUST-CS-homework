#pragma once
#include <bits/stdc++.h>

using namespace std;

class vehicle {
private:
    int x_ = 0;













    
    int y_ = 0;
    char heading_ = 'N';

public:
    void initialize_vehicle(int x, int y, char heading);
    /***
     * x,y对应地点位置
     * heading对应N、S、E、W四个方向
     */

    void vehicle_move(char mode);
    /***
     * M：表示前进，一次一格
     * L：左转90度，位置不变
     * R：右转90度，位置不变
     */

    string vehicle_location();
};