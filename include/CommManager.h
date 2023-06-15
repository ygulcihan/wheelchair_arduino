#ifndef COMM_MANAGER_H
#define COMM_MANAGER_H

#include <Arduino.h>

class CommManager
{
private:
    bool obstacleDetected = false, obstacleDetectedPrev = false;
    int8_t steeringPosition = 0;
    

public:
    CommManager();
    void eventLoop();
};

#endif // COMM_MANAGER_H