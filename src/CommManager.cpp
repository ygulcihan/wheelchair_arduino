#include "CommManager.h"

CommManager::CommManager()
{
}

void CommManager::init(HardwareSerial *serial, bool echo)
{
    this->serial = serial;
    this->echo = echo;
    this->serial->begin(115200);
}

void CommManager::sendObstacleStatus(bool pObstacleDetected)
{
    this->drive = false;
    this->serial->println(pObstacleDetected ? F("OD") : F("OC"));
}

void CommManager::parseData(String &data)
{
    // S:100,P:-50,D:1
    this->speed = data.substring(data.indexOf(F("S:")) + 2).toInt();
    this->steeringPosition = data.substring(data.indexOf(F("P:")) + 2).toInt();
    this->drive = (bool)data.substring(data.indexOf(F("D:")) + 2).toInt();

    if (this->echo)
    {
        this->serial->print(F("Speed: "));
        this->serial->println(this->speed);
        this->serial->print(F("Steering position: "));
        this->serial->println(this->steeringPosition);
        this->serial->print(F("Drive: "));
        this->serial->println(this->drive ? F("Enabled") : F("Disabled"));
    }
}

void CommManager::eventLoop()
{
    String data = Serial.readStringUntil('\n');
    if (data.length() > 2) // if data is recieved
    {
        data.toUpperCase();

        if (data == "CHK")
        {
            for (uint8_t i = 0; i < 3; i++)
                Serial.print(F("OK\n"));
        }

        else
            this->parseData(data);
    }
}

int8_t CommManager::getSpeed()
{
    return this->speed;
}

int16_t CommManager::getSteeringPosition()
{
    return this->steeringPosition;
}

bool CommManager::getDrive()
{
    return this->drive;
}

