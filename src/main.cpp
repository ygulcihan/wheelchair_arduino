#include <Arduino.h>
#include "SoftwareSerial.h"
#include "SteeringController.h"

#define dir A1
#define step A2

SteeringController steeringController(dir, step);

void setup()
{
    steeringController.init();
    steeringController.setPosition(-350);
}

void loop()
{
    steeringController.eventLoop();

}