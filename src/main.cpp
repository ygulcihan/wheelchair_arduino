#include <Arduino.h>
#include "Pins.h"
#include "SteeringController.h"
#include "CommManager.h"

SteeringController steeringController(dirPin, stepPin);
CommManager commManager;

void setup()
{
    steeringController.init();
    commManager.init(&Serial, false);
}

void loop()
{
    steeringController.eventLoop();
    commManager.eventLoop();
}