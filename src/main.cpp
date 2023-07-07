#include <Arduino.h>
#include "Pins.h"
#include "SteeringController.h"
#include "CommManager.h"
#include "ThrottleController.h"

SteeringController steeringController(DIR_PIN, STEP_PIN);
CommManager commManager;
ThrottleController throttleController;

void setup()
{
    steeringController.init();
    commManager.init(&Serial, false);
    pinMode(LED_BUILTIN, OUTPUT);
    while (!throttleController.init())
    {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
    }
    //throttleController.testSweep();
    digitalWrite(LED_BUILTIN, HIGH);
}

void loop()
{
    steeringController.eventLoop();
    commManager.eventLoop();
    if (commManager.isConnected())
        throttleController.setThrottlePosition(commManager.getSpeed());
    else
    {
        throttleController.setThrottlePosition(0);
        digitalWrite(LED_BUILTIN, LOW);
    }
}