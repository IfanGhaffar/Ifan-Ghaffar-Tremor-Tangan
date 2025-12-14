// ========== Header dan Library ==========
#include <Arduino.h>
#include <lvgl.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"
#include "button_callbacks.h"
#include "Arduino_GFX_Library.h"
// #include "CustomButton.h"
// #include <LittleFS.h>
// #include <WiFiClientSecure.h>
// #include <PubSubClient.h>
// #include <WiFi.h>
#include <ArduinoJson.h>
// #include "CustomTime.h"
// #include <HTTPClient.h>
#include <Update.h>
#include "touch.h"
#include <MutexManager.h>
#include <semphr.h>
#include <Wire.h>
#include <SPI.h>

//========== PIN SENSOR ICM ==========
#define PIN_SCLK 18
#define PIN_MISO 16 //SDO
#define PIN_MOSI 17 //SDI
#define PIN_CS   15 //NCS
//========== PIN & UKURAN LAYAR ==========
#define TFT_MOSI 35
#define TFT_SCLK 36
#define TFT_CS 40
#define TFT_DC 41
#define TFT_RST 42
#define TFT_BL 38

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 170


SPIClass SPI_2(HSPI);

// =====================================================
// DISPLAY & LVGL
// =====================================================
Arduino_DataBus *bus = new Arduino_ESP32SPI(11, 10, 12, 13, GFX_NOT_DEFINED);
Arduino_GFX *gfx = new Arduino_GC9A01(bus, 1, 1, true, SCREEN_HEIGHT, SCREEN_WIDTH, 35, 0, 35, 0);

static lv_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf1;
static lv_display_t *disp_drv;
lv_ui guider_ui;

char buf[30];

// ====================== COUNTDOWN TIMER ======================
static int countdown_seconds = 30;      // 1 menit
static bool countdown_enabled = false;  // aktif saat screen telegram
SemaphoreHandle_t countdown_mutex;      // untuk aman update dari task & button

// Untuk menyimpan screen aktif sebelumnya
lv_obj_t *last_active_screen = NULL;

// Data dari ICM (replaced tilt/trend with tremor metrics)
// We'll compute: peak frequency (Hz) and RMS amplitude (g)

// Flag untuk mendeteksi apakah screen monitor atau telegram aktif
volatile bool sensor_active_screen = false;
volatile bool telegram_screen_active = false;



// =====================================================
// CALLBACK DISPLAY LVGL
// =====================================================
void lvgl_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *color_p) {
    gfx->draw16bitRGBBitmap(
        area->x1, area->y1,
        (uint16_t *)color_p,
        area->x2 - area->x1 + 1,
        area->y2 - area->y1 + 1);

    lv_display_flush_ready(disp);
}

// =====================================================
// INISIALISASI DISPLAY
// =====================================================
void init_display() {
    gfx->begin();
    gfx->fillScreen(BLACK);
    gfx->invertDisplay(true);

    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);

    lv_init();
    disp_draw_buf1 = (lv_color_t *)heap_caps_malloc(
        sizeof(lv_color_t) * SCREEN_WIDTH * 100,
        MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);

    lv_draw_buf_init(&draw_buf, SCREEN_WIDTH, SCREEN_HEIGHT,
                     LV_COLOR_FORMAT_RGB565,
                     SCREEN_WIDTH, disp_draw_buf1, SCREEN_WIDTH * 100);

    disp_drv = lv_display_create(SCREEN_WIDTH, SCREEN_HEIGHT);
    lv_display_set_flush_cb(disp_drv, lvgl_disp_flush);
    lv_display_set_buffers(
        disp_drv, disp_draw_buf1, NULL,
        SCREEN_WIDTH * 100,
        LV_DISPLAY_RENDER_MODE_PARTIAL);
}


// =====================================================
// SENSOR DATA
// =====================================================
// Sensor-derived tremor metrics
static float current_freq = 0.0f;   // peak frequency in Hz
static float current_rms = 0.0f;    // RMS amplitude in g
// Buffering for simple frequency estimation (zero-crossing) and RMS
static const int ICM_SAMPLE_RATE_HZ = 100; // sampling at 100 Hz for tremor
static const int ICM_SAMPLE_PERIOD_MS = 1000 / ICM_SAMPLE_RATE_HZ;
static const int ICM_BUFFER_SIZE = 256; // window for analysis (~2.56 s)
static float icm_mag_buffer[ICM_BUFFER_SIZE];
static int icm_buf_idx = 0;
static int icm_samples = 0;
static volatile bool sensor_updated = false;
static SemaphoreHandle_t sensor_mutex;
volatile bool monitor_screen_active = false;

// ===== TELEGRAM SAMPLES STORAGE =====
// store raw dynamic_g samples while the 30s countdown is running
static const int TELEGRAM_RECORD_SECONDS = 30;
static const int TELEGRAM_MAX_SAMPLES = ICM_SAMPLE_RATE_HZ * TELEGRAM_RECORD_SECONDS; // e.g., 100 * 30 = 3000
static float telegram_samples[TELEGRAM_MAX_SAMPLES];
static int telegram_samples_count = 0;
static SemaphoreHandle_t telegram_samples_mutex;

// =====================================================
// TOUCH
// =====================================================
uint16_t touch_x, touch_y;

void my_touchpad_read(lv_indev_t *indev, lv_indev_data_t *data) {
    int st = CHSC6540_Scan(&touch_x, &touch_y);
    if (st == 1) {
        data->state = LV_INDEV_STATE_PRESSED;
        data->point.x = touch_x;
        data->point.y = touch_y;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

void touchTask(void *pv) {
    while (1) {
        CHSC6540_Scan(&touch_x, &touch_y);
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void init_touch() {
    CHSC6540_init();
    lv_indev_t *indev_touch = lv_indev_create();
    lv_indev_set_type(indev_touch, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev_touch, my_touchpad_read);
}

// =====================================================
// ICM20948 FUNCTIONS (SPI)
// =====================================================
uint8_t icm_read(uint8_t reg) {
    SPI_2.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    digitalWrite(PIN_CS, LOW);
    SPI_2.transfer(reg | 0x80);
    uint8_t val = SPI_2.transfer(0x00);
    digitalWrite(PIN_CS, HIGH);
    SPI_2.endTransaction();
    return val;
}

void icm_write(uint8_t reg, uint8_t val) {
    SPI_2.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    digitalWrite(PIN_CS, LOW);
    SPI_2.transfer(reg & 0x7F);
    SPI_2.transfer(val);
    digitalWrite(PIN_CS, HIGH);
    SPI_2.endTransaction();
}

void on_btn_1_clicked()
{
    xSemaphoreTake(countdown_mutex, portMAX_DELAY);

    countdown_seconds = 30;     // reset ke 1 menit
    countdown_enabled = true;   // mulai lagi
    lv_label_set_text(guider_ui.telegram_label_8, "00:00:30");

    // Also clear any previously recorded telegram samples so new session starts fresh
    if (xSemaphoreTake(telegram_samples_mutex, pdMS_TO_TICKS(100)) == pdTRUE) {
        telegram_samples_count = 0;
        xSemaphoreGive(telegram_samples_mutex);
    } else {
        Serial.println("⚠ Unable to clear telegram samples (mutex)");
    }

    xSemaphoreGive(countdown_mutex);

    Serial.println("⏳ Timer reset oleh btn_1");
}

// C-callable wrapper so generated C event code can trigger the reset
extern "C" void telegram_reset_timer(void)
{
    // Reuse existing C++ handler to keep behavior consistent
    on_btn_1_clicked();
}

// C-callable function to compute and print stored telegram samples statistics
extern "C" void telegram_send_data(void)
{
    // Acquire samples mutex and snapshot
    if (xSemaphoreTake(telegram_samples_mutex, pdMS_TO_TICKS(100)) != pdTRUE) {
        Serial.println("⚠ Unable to access telegram samples (mutex)");
        return;
    }

    int n = telegram_samples_count;
    if (n == 0) {
        Serial.println("ℹ No telegram samples recorded.");
        xSemaphoreGive(telegram_samples_mutex);
        return;
    }
    // Compute simple stats: min, max, mean, RMS
    float sum = 0.0f;
    float sumsq = 0.0f;
    float minv = telegram_samples[0];
    float maxv = telegram_samples[0];
    for (int i = 0; i < n; ++i) {
        float v = telegram_samples[i];
        sum += v;
        sumsq += v * v;
        if (v < minv) minv = v;
        if (v > maxv) maxv = v;
    }
    float mean = sum / (float)n;
    float rms = (n > 0) ? sqrtf(sumsq / (float)n) : 0.0f;

    // Determine qualitative conclusion based on RMS thresholds used elsewhere
    const float RMS_GOOD = 0.025f;
    const float RMS_MODERATE = 0.10f;
    const char *conclusion = "";
    uint32_t color_hex = 0x7f8c8d; // default gray (idle)
    if (rms < RMS_GOOD) {
        conclusion = "Good";
        color_hex = 0x00ff39;
    } else if (rms < RMS_MODERATE) {
        conclusion = "Moderate";
        color_hex = 0xffd200;
    } else {
        conclusion = "Not Good";
        color_hex = 0xff3b30;
    }

    Serial.println("--- Telegram Sensor Summary ---");
    Serial.printf("Samples: %d\n", n);
    Serial.printf("Mean dynamic_g: %.6f g\n", mean);
    Serial.printf("RMS dynamic_g:  %.6f g\n", rms);
    Serial.printf("Min dynamic_g:  %.6f g\n", minv);
    Serial.printf("Max dynamic_g:  %.6f g\n", maxv);
    Serial.printf("Conclusion: %s\n", conclusion);

    // Update on-screen status label to reflect conclusion
    lv_label_set_text(guider_ui.telegram_status, conclusion);
    lv_obj_set_style_text_color(guider_ui.telegram_status, lv_color_hex(color_hex), LV_PART_MAIN|LV_STATE_DEFAULT);

    // Optionally print a few representative samples (every Nth)
    int step = (n > 20) ? (n / 10) : 1;
    Serial.println("Sample preview:");
    for (int i = 0; i < n; i += step) {
        Serial.printf("[%4d] %.6f g\n", i, telegram_samples[i]);
    }

    // Keep data after sending (or reset if desired)
    // If you want to clear after send, uncomment below:
    // telegram_samples_count = 0;

    xSemaphoreGive(telegram_samples_mutex);
}
// =====================================================
// MONITOR TASK
// =====================================================
void taskScreenMonitor(void *pv) {
    TickType_t last = xTaskGetTickCount();

    while (1) {
        lv_obj_t *active_scr = lv_scr_act();  

        // Jika screen berubah, cetak namanya
        if (active_scr != last_active_screen) {
            last_active_screen = active_scr;

            if (active_scr == guider_ui.screen_1) {
                Serial.println("📌 Active Screen: screen_1 (Home)");
            }
            else if (active_scr == guider_ui.menu) {
                Serial.println("📌 Active Screen: menu");
            }
            else if (active_scr == guider_ui.monitor) {
                Serial.println("📌 Active Screen: MONITOR");
            }
            else if (active_scr == guider_ui.bar_tele) {
                Serial.println("📌 Active Screen: MONITOR");
            }
            else if (active_scr == guider_ui.telegram) {
                Serial.println("📌 Active Screen: telegram");
                xSemaphoreTake(countdown_mutex, portMAX_DELAY);
                countdown_enabled = true;   // hidupkan hitungan mundur
                xSemaphoreGive(countdown_mutex);
            }
            else if (active_scr == guider_ui.info) {
                Serial.println("📌 Active Screen: info");
            }
            else {
                Serial.println("📌 Active Screen: UNKNOWN SCREEN");
                xSemaphoreTake(countdown_mutex, portMAX_DELAY);
                countdown_enabled = false;  // matikan ketika keluar screen
                xSemaphoreGive(countdown_mutex);
            }
        }

        vTaskDelayUntil(&last, pdMS_TO_TICKS(200));   // Cek tiap 200 ms
    }
}

// =====================================================
// ICM SENSOR TASK - MONITOR SCREEN
// =====================================================
void taskICMMonitor(void *pv) {
    TickType_t last = xTaskGetTickCount();
    while (1) {
        // Only sample when monitor screen is active; otherwise sample slowly
        if (!monitor_screen_active) {
            vTaskDelayUntil(&last, pdMS_TO_TICKS(200));
            continue;
        }

        // Read accelerometer
        int16_t ax = ((int16_t)(icm_read(0x2D) << 8)) | icm_read(0x2E);
        int16_t ay = ((int16_t)(icm_read(0x2F) << 8)) | icm_read(0x30);
        int16_t az = ((int16_t)(icm_read(0x31) << 8)) | icm_read(0x32);

        // Quick validity check: if all zero, sensor likely not responding
        if (ax == 0 && ay == 0 && az == 0) {
            static uint8_t err_counter = 0;
            if (err_counter++ == 0) {
                // Print raw register reads to help debugging
                uint8_t b2d = icm_read(0x2D);
                uint8_t b2e = icm_read(0x2E);
                uint8_t b2f = icm_read(0x2F);
                uint8_t b30 = icm_read(0x30);
                uint8_t b31 = icm_read(0x31);
                uint8_t b32 = icm_read(0x32);
                uint8_t who = icm_read(0x00);
                Serial.printf("⚠ ICM zero-reads detected. WHO_AM_I=0x%02X | regs: 2D=0x%02X 2E=0x%02X 2F=0x%02X 30=0x%02X 31=0x%02X 32=0x%02X\n",
                              who, b2d, b2e, b2f, b30, b31, b32);
            }
            // small delay and continue without updating buffers to avoid spurious RMS=1.0
            vTaskDelayUntil(&last, pdMS_TO_TICKS(100));
            continue;
        }

        // Compute magnitude in g, remove gravity (~1 g) to get dynamic component
        float accel_g = sqrt((float)ax * (float)ax + (float)ay * (float)ay + (float)az * (float)az) / 16384.0f;
        float dynamic_g = accel_g - 1.0f;
        // If accel_g is unrealistically small, skip (already handled above), clamp tiny values
        if (fabsf(dynamic_g) < 1e-6f) dynamic_g = 0.0f;

        // Store into circular buffer
        icm_mag_buffer[icm_buf_idx] = dynamic_g;
        icm_buf_idx = (icm_buf_idx + 1) % ICM_BUFFER_SIZE;
        if (icm_samples < ICM_BUFFER_SIZE) icm_samples++;

        // Compute RMS over available samples
        float sumsq = 0.0f;
        for (int i = 0; i < icm_samples; ++i) {
            float v = icm_mag_buffer[i];
            sumsq += v * v;
        }
        float rms = (icm_samples > 0) ? sqrt(sumsq / icm_samples) : 0.0f;

        // Estimate dominant frequency using zero-crossing count
        int zero_crossings = 0;
        if (icm_samples >= 2) {
            float prev = icm_mag_buffer[0];
            const float zc_threshold = 0.02f; // avoid counting tiny noise crossings
            for (int i = 1; i < icm_samples; ++i) {
                float cur = icm_mag_buffer[i];
                if (((prev <= 0.0f && cur > 0.0f) || (prev >= 0.0f && cur < 0.0f)) && (fabsf(cur - prev) > zc_threshold)) {
                    zero_crossings++;
                }
                prev = cur;
            }
        }

        float freq_hz = 0.0f;
        if (icm_samples >= 2 && zero_crossings > 0) {
            float window_time = (float)icm_samples / (float)ICM_SAMPLE_RATE_HZ;
            // zero crossings per second = zero_crossings / window_time, and for a sine wave
            // crossings_per_second = 2 * frequency, so frequency = crossings_per_second / 2
            freq_hz = ((float)zero_crossings / window_time) / 2.0f;
        }

        // Publish the computed metrics safely
        if (xSemaphoreTake(sensor_mutex, pdMS_TO_TICKS(10)) == pdTRUE) {
            current_freq = freq_hz;
            current_rms = rms;
            sensor_updated = true;
            xSemaphoreGive(sensor_mutex);
        }

        // Debug output (less frequent)
        static uint8_t debug_counter = 0;
        if (debug_counter++ >= 10) {
            Serial.printf("📊 ICM Monitor: ax=%d, ay=%d, az=%d | Freq=%.2fHz, RMS=%.4fg\n",
                          ax, ay, az, freq_hz, rms);
            debug_counter = 0;
        }

        vTaskDelayUntil(&last, pdMS_TO_TICKS(ICM_SAMPLE_PERIOD_MS));
    }
}

// =====================================================
// ICM SENSOR TASK - TELEGRAM SCREEN
// =====================================================
void taskICMTelegram(void *pv) {
    TickType_t last = xTaskGetTickCount();
    while (1) {
        // Only sample when telegram screen is active AND timer is running
        xSemaphoreTake(countdown_mutex, portMAX_DELAY);
        bool timer_running = countdown_enabled;
        xSemaphoreGive(countdown_mutex);

        if (!telegram_screen_active || !timer_running) {
            vTaskDelayUntil(&last, pdMS_TO_TICKS(200));
            continue;
        }

        // Read accelerometer
        int16_t ax = ((int16_t)(icm_read(0x2D) << 8)) | icm_read(0x2E);
        int16_t ay = ((int16_t)(icm_read(0x2F) << 8)) | icm_read(0x30);
        int16_t az = ((int16_t)(icm_read(0x31) << 8)) | icm_read(0x32);

        // Quick validity check: if all zero, sensor likely not responding
        if (ax == 0 && ay == 0 && az == 0) {
            static uint8_t err_counter = 0;
            if (err_counter++ == 0) {
                uint8_t who = icm_read(0x00);
                Serial.printf("⚠ ICM Telegram: zero-reads detected. WHO_AM_I=0x%02X\n", who);
            }
            vTaskDelayUntil(&last, pdMS_TO_TICKS(100));
            continue;
        }

        // Compute magnitude in g, remove gravity (~1 g) to get dynamic component
        float accel_g = sqrt((float)ax * (float)ax + (float)ay * (float)ay + (float)az * (float)az) / 16384.0f;
        float dynamic_g = accel_g - 1.0f;
        if (fabsf(dynamic_g) < 1e-6f) dynamic_g = 0.0f;

        // Store into circular buffer (same buffer as monitor)
        icm_mag_buffer[icm_buf_idx] = dynamic_g;
        icm_buf_idx = (icm_buf_idx + 1) % ICM_BUFFER_SIZE;
        if (icm_samples < ICM_BUFFER_SIZE) icm_samples++;

        // Also append into telegram_samples while timer is running
        if (timer_running) {
            if (xSemaphoreTake(telegram_samples_mutex, pdMS_TO_TICKS(10)) == pdTRUE) {
                if (telegram_samples_count < TELEGRAM_MAX_SAMPLES) {
                    telegram_samples[telegram_samples_count++] = dynamic_g;
                }
                xSemaphoreGive(telegram_samples_mutex);
            }
        }

        // Compute RMS over available samples
        float sumsq = 0.0f;
        for (int i = 0; i < icm_samples; ++i) {
            float v = icm_mag_buffer[i];
            sumsq += v * v;
        }
        float rms = (icm_samples > 0) ? sqrt(sumsq / icm_samples) : 0.0f;

        // Estimate dominant frequency using zero-crossing count
        int zero_crossings = 0;
        if (icm_samples >= 2) {
            float prev = icm_mag_buffer[0];
            const float zc_threshold = 0.02f;
            for (int i = 1; i < icm_samples; ++i) {
                float cur = icm_mag_buffer[i];
                if (((prev <= 0.0f && cur > 0.0f) || (prev >= 0.0f && cur < 0.0f)) && (fabsf(cur - prev) > zc_threshold)) {
                    zero_crossings++;
                }
                prev = cur;
            }
        }

        float freq_hz = 0.0f;
        if (icm_samples >= 2 && zero_crossings > 0) {
            float window_time = (float)icm_samples / (float)ICM_SAMPLE_RATE_HZ;
            freq_hz = ((float)zero_crossings / window_time) / 2.0f;
        }

        // Publish the computed metrics safely
        if (xSemaphoreTake(sensor_mutex, pdMS_TO_TICKS(10)) == pdTRUE) {
            current_freq = freq_hz;
            current_rms = rms;
            sensor_updated = true;
            xSemaphoreGive(sensor_mutex);
        }

        // Debug output (less frequent)
        static uint8_t debug_counter = 0;
        if (debug_counter++ >= 10) {
            Serial.printf("📊 ICM Telegram: ax=%d, ay=%d, az=%d | Freq=%.2fHz, RMS=%.4fg\n",
                          ax, ay, az, freq_hz, rms);
            debug_counter = 0;
        }

        vTaskDelayUntil(&last, pdMS_TO_TICKS(ICM_SAMPLE_PERIOD_MS));
    }
}

void taskCountdown(void *pv)
{
    TickType_t last = xTaskGetTickCount();

    while(1)
    {
        // hanya berjalan kalau telegram layar aktif
        if (countdown_enabled)
        {
            xSemaphoreTake(countdown_mutex, portMAX_DELAY);

            if (countdown_seconds > 0)
            {
                countdown_seconds--;

                int hh = countdown_seconds / 3600;
                int mm = (countdown_seconds % 3600) / 60;
                int ss = countdown_seconds % 60;

                char buf[20];
                sprintf(buf, "%02d:%02d:%02d", hh, mm, ss);

                lv_label_set_text(guider_ui.telegram_label_8, buf);
            }
            else
            {
                // Jika waktu habis → otomatis berhenti
                countdown_enabled = false;
            }

            xSemaphoreGive(countdown_mutex);
        }

        vTaskDelayUntil(&last, pdMS_TO_TICKS(1000)); // 1 detik update
    }
}

// =====================================================
// LVGL TASK
// =====================================================
//========== LVGL & UI TASK ==========
// =====================================================
void lvglTask(void *pvParameters)
{
    TickType_t lastWakeTime = xTaskGetTickCount();
    static float icmDataDisplay_tilt = 0.0f;
    static float icmDataDisplay_trend = 0.0f;
    
    while (1)
    {
            lv_obj_t *scr = lv_scr_act();
            monitor_screen_active = (scr == guider_ui.monitor);
            telegram_screen_active = (scr == guider_ui.telegram);

            // Update sensor UI berdasarkan screen mana yang aktif
            if (sensor_updated) {
                if (xSemaphoreTake(sensor_mutex, pdMS_TO_TICKS(10)) == pdTRUE) {
                    float freq = current_freq;
                    float rms = current_rms;
                    sensor_updated = false;
                    xSemaphoreGive(sensor_mutex);

                    // ===== MONITOR SCREEN =====
                    if (monitor_screen_active) {
                        // Update label: frequency (Hz) and RMS amplitude (g)
                        snprintf(buf, sizeof(buf), "%.2f Hz", freq);
                        lv_label_set_text(guider_ui.monitor_label_3, buf);
                        snprintf(buf, sizeof(buf), "%.4f g", rms);
                        lv_label_set_text(guider_ui.monitor_label_5, buf);

                        // Update condition label based on RMS amplitude
                        // Thresholds chosen for tremor/RMS display: adjust if needed
                        const float RMS_GOOD = 0.025f;     // < 0.02 g considered good
                        const float RMS_MODERATE = 0.10f; // 0.02 - 0.10 g considered moderate

                        if (rms < RMS_GOOD) {
                            lv_label_set_text(guider_ui.monitor_label_7, "Good");
                            lv_obj_set_style_text_color(guider_ui.monitor_label_7, lv_color_hex(0x00ff39), LV_PART_MAIN|LV_STATE_DEFAULT);
                        } else if (rms < RMS_MODERATE) {
                            lv_label_set_text(guider_ui.monitor_label_7, "Moderate");
                            lv_obj_set_style_text_color(guider_ui.monitor_label_7, lv_color_hex(0xffd200), LV_PART_MAIN|LV_STATE_DEFAULT);
                        } else {
                            lv_label_set_text(guider_ui.monitor_label_7, "Not Good");
                            lv_obj_set_style_text_color(guider_ui.monitor_label_7, lv_color_hex(0xff3b30), LV_PART_MAIN|LV_STATE_DEFAULT);
                        }

                        // Debug output
                        static uint8_t debug_counter_monitor = 0;
                        if (debug_counter_monitor++ >= 4) {
                            Serial.printf("✓ Monitor - Freq: %.2f Hz, RMS: %.4f g\n", freq, rms);
                            debug_counter_monitor = 0;
                        }
                    }

                    // ===== TELEGRAM SCREEN =====
                    if (telegram_screen_active) {
                        // Cek apakah timer masih aktif
                        xSemaphoreTake(countdown_mutex, portMAX_DELAY);
                        bool timer_running = countdown_enabled;
                        xSemaphoreGive(countdown_mutex);

                        // Hanya update sensor data jika timer sedang aktif
                        if (timer_running) {
                            // Update label: frequency (Hz) and RMS amplitude (g)
                            snprintf(buf, sizeof(buf), "%.2f Hz", freq);
                            lv_label_set_text(guider_ui.telegram_label_9, buf);
                            snprintf(buf, sizeof(buf), "%.4f g", rms);
                            lv_label_set_text(guider_ui.telegram_label_10, buf);
                            
                            // Update condition label based on RMS amplitude
                            // Thresholds chosen for tremor/RMS display: adjust if needed
                            const float RMS_GOOD = 0.025f;     // < 0.02 g considered good
                            const float RMS_MODERATE = 0.10f; // 0.02 - 0.10 g considered moderate

                            if (rms < RMS_GOOD) {
                                lv_label_set_text(guider_ui.telegram_status, "Good");
                                lv_obj_set_style_text_color(guider_ui.telegram_status, lv_color_hex(0x00ff39), LV_PART_MAIN|LV_STATE_DEFAULT);
                            } else if (rms < RMS_MODERATE) {
                                lv_label_set_text(guider_ui.telegram_status, "Moderate");
                                lv_obj_set_style_text_color(guider_ui.telegram_status, lv_color_hex(0xffd200), LV_PART_MAIN|LV_STATE_DEFAULT);
                            } else {
                                lv_label_set_text(guider_ui.telegram_status, "Not Good");
                                lv_obj_set_style_text_color(guider_ui.telegram_status, lv_color_hex(0xff3b30), LV_PART_MAIN|LV_STATE_DEFAULT);
                            }

                            // Debug output
                            static uint8_t debug_counter_telegram = 0;
                            if (debug_counter_telegram++ >= 4) {
                                Serial.printf("✓ Telegram - Freq: %.2f Hz, RMS: %.4f g\n", freq, rms);
                                debug_counter_telegram = 0;
                            }
                        } else {
                            // Timer sudah habis - reset tampilan
                            lv_label_set_text(guider_ui.telegram_label_9, "--.- Hz");
                            lv_label_set_text(guider_ui.telegram_label_10, "--.----- g");
                            lv_label_set_text(guider_ui.telegram_status, "Idle");
                            lv_obj_set_style_text_color(guider_ui.telegram_status, lv_color_hex(0x7f8c8d), LV_PART_MAIN|LV_STATE_DEFAULT);
                        }
                    }

                    icmDataDisplay_tilt = freq; // reusing variable name for brief display smoothing
                    icmDataDisplay_trend = rms;
                }
            }

        lv_timer_handler();
        vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(10));
    }
}

// =====================================================
// SETUP
// =====================================================
void setup() {
    Serial.begin(115200);

    // Create mutex untuk sensor data protection
    sensor_mutex = xSemaphoreCreateMutex();
    telegram_samples_mutex = xSemaphoreCreateMutex();
    countdown_mutex = xSemaphoreCreateMutex();

    // Display & UI
    init_display();
    init_touch();
    setup_ui(&guider_ui);
    events_init(&guider_ui);
    custom_init(&guider_ui);  // Register custom event handlers
    lv_scr_load(guider_ui.screen_1);

    // LVGL Tick
    TimerHandle_t lvTimer = xTimerCreate(
        "lv_tick", pdMS_TO_TICKS(1), pdTRUE,
        NULL, [](TimerHandle_t) { lv_tick_inc(1); });

    xTimerStart(lvTimer, 0);

    // SPI SENSOR INIT
    SPI_2.begin(PIN_SCLK, PIN_MISO, PIN_MOSI, PIN_CS);
    pinMode(PIN_CS, OUTPUT);
    digitalWrite(PIN_CS, HIGH);

    delay(50);

    // WHO_AM_I
    uint8_t whoami = icm_read(0x00);
    Serial.print("WHO_AM_I = 0x");
    Serial.println(whoami, HEX);

    if (whoami == 0xEA) Serial.println("✔ ICM20948 terdeteksi!");
    else Serial.println("❌ Sensor tidak terdeteksi!");

    icm_write(0x06, 0x01);  // power-up

    // TASKS
    xTaskCreatePinnedToCore(taskScreenMonitor,   "ScreenMonitor", 4096, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(touchTask,           "TouchTask", 4096, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(lvglTask,            "LVGLTask",  8192, NULL, 3, NULL, 1);
    xTaskCreatePinnedToCore(taskICMMonitor,      "ICMMonitor", 4096, NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(taskICMTelegram,     "ICMTelegram", 4096, NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(taskCountdown,       "CountdownTask", 2048, NULL, 2, NULL, 1);
}

void loop() {
    // FreeRTOS → loop kosong
}