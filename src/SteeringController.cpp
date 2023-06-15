#include "SteeringController.h"

SteeringController::SteeringController(uint8_t dirPin, uint8_t stepPin)
{
    this->dirPin = dirPin;
    this->stepPin = stepPin;

    this->currentPosition = 0;
    this->remainingStepCount = 0;
}

void SteeringController::init()
{
    pinMode(dirPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
}

void SteeringController::step(uint16_t nrOfSteps, SteeringDirection dir)
{
    if (nrOfSteps == 0)
        return;

    digitalWrite(dirPin, (uint8_t)dir);
    this->remainingStepCount = nrOfSteps * 2;
}

void SteeringController::eventLoop()
{
    static unsigned long lastStepTime = 0;
    static bool stepPinState = LOW;

    if (remainingStepCount > 0)
    {
        if (micros() - lastStepTime >= speed2Period(steeringSpeed))
        {
            digitalWrite(stepPin, stepPinState);
            stepPinState = !stepPinState;
            remainingStepCount--;
            lastStepTime = micros();
        }
    }
}

void SteeringController::setPosition(int16_t position)
{
    step(abs(position - currentPosition),
         (position > currentPosition ? RIGHT : LEFT));
}

uint16_t SteeringController::speed2Period(uint8_t speed)
{
    return map(speed, 0, 100, periodMax, periodMin);
}
