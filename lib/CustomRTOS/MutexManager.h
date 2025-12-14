#ifndef MUTEX_MANAGER_H
#define MUTEX_MANAGER_H

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

class MutexManager
{
public:
    static SemaphoreHandle_t myMutex; // Deklarasi mutex

    static void initMutex(); // Inisialisasi mutex
    static void lock();      // Mengunci mutex
    static void unlock();    // Melepas mutex
};

#endif
