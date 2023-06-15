#ifndef COMM_MANAGER_H
#define COMM_MANAGER_H

#include <Arduino.h>

class CommManager
{
private:
    HardwareSerial *serial;
    bool drive = false, echo = false;
    int16_t steeringPosition = 0;
    int8_t speed = 0;

    void parseData(String &data);

public:
    CommManager();
    void init(HardwareSerial *serial, bool echo = false);

    int8_t getSpeed();
    int16_t getSteeringPosition();
    bool getDrive();

    void sendObstacleStatus(bool pObstacleDetected);
    void eventLoop();
};

#endif // COMM_MANAGER_H