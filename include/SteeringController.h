#ifndef STEERING_CONTROLLER_H
#define STEERING_CONTROLLER_H

#include <Arduino.h>

//TODO: determine step angle
//TODO: determine max/min steering position
//TODO: implement homing procedure

typedef enum
{
    LEFT,
    RIGHT
} SteeringDirection;

class SteeringController
{
private:
    int16_t currentPosition;
    uint16_t remainingStepCount;

    uint8_t dirPin, stepPin;
    uint16_t periodMin = 250, periodMax = 3000;
    uint8_t steeringSpeed = 15;

    uint16_t speed2Period(uint8_t speed);

    void step(uint16_t nrOfSteps, SteeringDirection dir);

public:
    SteeringController(uint8_t dirPin, uint8_t stepPin);
    void init();
    void setPosition(int16_t position);
    void eventLoop();
};

#endif // STEERING_CONTROLLER_H