#include "CustomSerial.h"
#include "../../src/ui/ui.h"
#include <queue.h>
#include "QueueManager.h"

CustomSerial::CustomSerial() {}

void CustomSerial::serialTask(void *pvParameters)
{
    QueueManager queue_manager;
    CustomSerial *self = static_cast<CustomSerial *>(pvParameters); // ✅ Cast void* ke CustomSerial*
    char inputBuffer[32] = {0};                                     // Buffer untuk teks input
    int index = 0;

    while (1)
    {
        if (Serial.available())
        {
            char c = Serial.read(); // Baca karakter dari Serial

            if (c == '\n') // Jika tekan ENTER
            {
                inputBuffer[index] = '\0';                                        // Tambahkan null terminator
                xQueueSend(queue_manager.textQueue, &inputBuffer, portMAX_DELAY); // Kirim ke queue
                index = 0;                                                        // Reset index
            }
            else if (index < 31) // Simpan karakter selama belum penuh
            {
                inputBuffer[index++] = c;
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10)); // Hindari loop terus-menerus
    }
}