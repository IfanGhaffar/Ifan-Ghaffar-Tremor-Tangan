#ifndef CUSTOM_SERIAL_H
#define CUSTOM_SERIAL_H

#include <Arduino.h>

class CustomSerial
{
public:
    CustomSerial();
    static void serialTask(void *pvParameters);

private:
};

#endif
