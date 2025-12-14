#ifndef CUSTOM_TIME_H
#define CUSTOM_TIME_H

#include <Arduino.h>
#include <esp_sntp.h>

class CustomTime
{
public:
    CustomTime();
    void syncTime();
    static void clockTask(void *pvParameters);
    char timeStampString[80];
    uint32_t timeStampMillisecondsSinceEpoch;

private:
    void updateClock();
    static void timeSyncCallback(struct timeval *tv);
};

#endif
