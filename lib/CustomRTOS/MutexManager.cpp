#include "MutexManager.h"

SemaphoreHandle_t MutexManager::myMutex = nullptr;

void MutexManager::initMutex()
{
    myMutex = xSemaphoreCreateMutex(); // Buat mutex
}

void MutexManager::lock()
{
    if (myMutex)
    {
        xSemaphoreTake(myMutex, portMAX_DELAY); // Kunci mutex
    }
}

void MutexManager::unlock()
{
    if (myMutex)
    {
        xSemaphoreGive(myMutex); // Lepas mutex
    }
}
