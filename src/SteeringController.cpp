#include "SteeringController.h"

SteeringController::SteeringController(uint8_t dirPin, uint8_t stepPin, uint8_t endStopPin)
{
    this->dirPin = dirPin;
    this->stepPin = stepPin;
    this->endStopPin = endStopPin;

    this->currentPosition = 0;
    this->remainingStepCount = 0;
}

void SteeringController::init()
{
    Serial.begin(115200);
    pinMode(dirPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    pinMode(endStopPin, INPUT_PULLUP);
}

void SteeringController::home()
{
    if (digitalRead(endStopPin) == HIGH)
    {
        step(1, RIGHT);
    }
    else
    {
        this->currentPosition = 145;
        this->step(145, LEFT);
        this->homed = true;
    }
}

void SteeringController::step(uint16_t nrOfSteps, SteeringDirection dir)
{
    if (nrOfSteps == 0)
        return;

    digitalWrite(dirPin, (uint8_t)dir);
    this->direction = dir;
    this->remainingStepCount = nrOfSteps * 2;
}

bool SteeringController::isHomed()
{
    return this->homed;
}

void SteeringController::eventLoop()
{
    static unsigned long lastStepTime = 0;
    static bool stepPinState = LOW;
    static unsigned long period = speed2Period(steeringSpeed);

    if (!homed)
    {
        home();
    }

    if (remainingStepCount > 0)
    {
        if (micros() - lastStepTime >= period)
        {
            digitalWrite(stepPin, stepPinState);
            stepPinState = !stepPinState;
            remainingStepCount--;
            lastStepTime = micros();

            if (stepPinState == HIGH)
            {
                if (this->direction)
                    this->currentPosition++;
                else
                    this->currentPosition--;
            }
        }
    }

    else
    {
        digitalWrite(stepPin, LOW);
    }
}

void SteeringController::setPosition(int16_t position)
{
    step(abs(position - currentPosition), (position > currentPosition ? RIGHT : LEFT));
}

unsigned long SteeringController::speed2Period(uint8_t speed)
{
    return map(speed, 0, 100, periodMax, periodMin);
}
