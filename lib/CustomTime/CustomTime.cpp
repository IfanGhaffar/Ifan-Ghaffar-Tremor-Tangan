#include "CustomTime.h"
// #include "config.h"
// #include "../../src/ui/ui.h"

// **NTP Server & Zona Waktu**
const char *ntpServer1 = "pool.ntp.org";
const char *ntpServer2 = "time.nist.gov";
const long gmtOffset_sec = 7 * 3600; // GMT+7 (WIB)
const int daylightOffset_sec = 0;    // Tidak ada DST di Indonesia

// **Variabel RTC**
struct tm timeinfo;

// **Variabel jam**
// char timeStampString[80];

CustomTime::CustomTime() {}

void CustomTime::syncTime()
{
    Serial.println("=================== Start sinkronisasi waktu...");
    // Atur callback jika waktu berhasil disinkronisasi
    sntp_set_time_sync_notification_cb(timeSyncCallback);
    Serial.println("Callback waktu diset!");

    Serial.println("Sinkronisasi waktu...");
    // Sinkronisasi waktu dari NTP Server
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
    Serial.println("Waktu disinkronisasi!");
    Serial.println("=================== End sinkronisasi waktu...");
}

// **Callback ketika NTP berhasil sinkronisasi waktu**
void CustomTime::timeSyncCallback(struct timeval *tv)
{
    Serial.println("Waktu berhasil disinkronisasi dengan NTP!");
}

// **Update jam setiap detik dan ditampilkan di UI**
void CustomTime::updateClock()
{

    if (getLocalTime(&timeinfo))
    {
        time_t timestamp = mktime(&timeinfo); // Unix timestamp dalam detik
        timeStampMillisecondsSinceEpoch = (uint32_t)timestamp;
        // Format: YYYY-MM-DD HH:MM:SS
        strftime(timeStampString, sizeof(timeStampString), "%Y-%m-%d %H:%M:%S", &timeinfo);
        // printf("Timestamp: %s\n", timeStampString);
        // strftime(timeString, sizeof(timeString), "%H:%M:%S", &timeinfo);
        // if (ui_Label_Clock != nullptr)
        // {
        //     lv_label_set_text(ui_Label_Clock, timeString);
        // }
        // else
        // {
        //     Serial.println(timeString);
        // }
    }
}

// **Task untuk update jam setiap detik**
void CustomTime::clockTask(void *pvParameters)
{
    CustomTime *self = static_cast<CustomTime *>(pvParameters); // ✅ Cast void* ke CustomTime*

    while (1)
    {
        self->updateClock();
        vTaskDelay(pdMS_TO_TICKS(1000)); // Update tiap 1 detik
    }
}
