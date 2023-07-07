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
    this->serial->println(pObstacleDetected ? F("OD") : F("OC"));
}

void CommManager::parseData(String &data)
{
    // S:100,P:-50,D:1
    this->speed = data.substring(data.indexOf(F("S:")) + 2).toInt();
    this->steeringPosition = data.substring(data.indexOf(F("P:")) + 2).toInt();

    if (this->echo)
    {
        this->serial->print(F("Speed: "));
        this->serial->println(this->speed);
        this->serial->print(F("Steering position: "));
        this->serial->println(this->steeringPosition);
    }
}

void CommManager::eventLoop()
{
    if (millis() - this->messageLastRecieved >= 1000)
    {
        this->speed = 0;
        this->steeringPosition = 0;
    }

    String data = Serial.readStringUntil('\n');
    if (data.length() > 2) // if data is recieved
    {
        this->messageLastRecieved = millis();
        this->connected = true;
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

uint8_t CommManager::getSpeed()
{
    return this->speed;
}

int16_t CommManager::getSteeringPosition()
{
    return this->steeringPosition;
}

bool CommManager::isConnected()
{
    return this->connected;
}
