#include "QueueManager.h"

QueueHandle_t QueueManager::textQueue = nullptr;

void QueueManager::initQueues()
{
    textQueue = xQueueCreate(10, sizeof(char[32])); // Buat queue dengan 10 slot
}
