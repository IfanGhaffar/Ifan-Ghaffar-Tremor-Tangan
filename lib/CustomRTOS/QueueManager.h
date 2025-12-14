#ifndef QUEUE_MANAGER_H
#define QUEUE_MANAGER_H

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

class QueueManager
{
public:
    static QueueHandle_t textQueue; // Queue global

    static void initQueues(); // Fungsi untuk inisialisasi semua queue
};

#endif
