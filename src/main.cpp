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
#define PIN_SCLK 18 //kuning
#define PIN_MISO 16 //SDO // biru
#define PIN_MOSI 17 //SDI // hijau
#define PIN_CS   15 //NCS // ungu
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
static bool countdown_enabled = false;  // aktif saat screen timer
SemaphoreHandle_t countdown_mutex;      // untuk aman update dari task & button
SemaphoreHandle_t timer_done_sem = NULL;
static volatile bool timer_summary_shown = false;

// Untuk menyimpan screen aktif sebelumnya
lv_obj_t *last_active_screen = NULL;

// Data dari ICM (replaced tilt/trend with tremor metrics)
// We'll compute: peak frequency (Hz) and RMS amplitude (g)

// Flag untuk mendeteksi apakah screen monitor atau timer aktif
volatile bool sensor_active_screen = false;
volatile bool timer_screen_active = false;

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
static float fuzzy_evaluate(float freq, float rms);
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

// ===== TIMER SAMPLES STORAGE =====
// store raw dynamic_g samples while the 30s countdown is running
static const int TIMER_RECORD_SECONDS = 30;
static const int TIMER_MAX_SAMPLES = ICM_SAMPLE_RATE_HZ * TIMER_RECORD_SECONDS; // e.g., 100 * 30 = 3000
static float timer_samples[TIMER_MAX_SAMPLES];
static int timer_samples_count = 0;
static SemaphoreHandle_t timer_samples_mutex;

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
    timer_summary_shown = false;
    lv_label_set_text(guider_ui.timer_label_8, "00:00:30");

    // Also clear any previously recorded timer samples so new session starts fresh
    if (xSemaphoreTake(timer_samples_mutex, pdMS_TO_TICKS(100)) == pdTRUE) {
        timer_samples_count = 0;
        xSemaphoreGive(timer_samples_mutex);
    } else {
        Serial.println("⚠ Unable to clear timer samples (mutex)");
    }

    xSemaphoreGive(countdown_mutex);

    Serial.println("⏳ Timer reset oleh btn_1");
}

// C-callable wrapper so generated C event code can trigger the reset
extern "C" void timer_reset_timer(void)
{
    // Reuse existing C++ handler to keep behavior consistent
    on_btn_1_clicked();
}

// C-callable function to compute and print stored timer samples statistics
extern "C" void timer_send_data(void)
{
    // Acquire samples mutex and snapshot
    if (xSemaphoreTake(timer_samples_mutex, pdMS_TO_TICKS(100)) != pdTRUE) {
        Serial.println("⚠ Unable to access timer samples (mutex)");
        return;
    }

    int n = timer_samples_count;
    if (n == 0) {
        Serial.println("ℹ No timer samples recorded.");
        xSemaphoreGive(timer_samples_mutex);
        return;
    }
    // Compute simple stats: min, max, mean, RMS
    float sum = 0.0f;
    float sumsq = 0.0f;
    float minv = timer_samples[0];
    float maxv = timer_samples[0];
    for (int i = 0; i < n; ++i) {
        float v = timer_samples[i];
        sum += v;
        sumsq += v * v;
        if (v < minv) minv = v;
        if (v > maxv) maxv = v;
    }
    float mean = sum / (float)n;
    float rms = (n > 0) ? sqrtf(sumsq / (float)n) : 0.0f;

   // Ambil freq terakhir yang tercatat lebih dulu supaya bisa dipakai fuzzy_evaluate
    float last_freq_for_fuzzy = 0.0f;
    if (xSemaphoreTake(sensor_mutex, pdMS_TO_TICKS(100)) == pdTRUE) {
        last_freq_for_fuzzy = current_freq;
        xSemaphoreGive(sensor_mutex);
    }
 
    // Determine qualitative conclusion via fuzzy system (freq & rms), sesuai Bab 3 laporan
    float fuzzy_score = fuzzy_evaluate(last_freq_for_fuzzy, rms);
    const char *conclusion = "";
    uint32_t color_hex = 0x7f8c8d; // default gray (idle)
    if (fuzzy_score < 33.0f) {
        conclusion = "Normal";
        color_hex = 0x00ff39;
    } else if (fuzzy_score < 66.0f) {
        conclusion = "Tremor Ringan";
        color_hex = 0xffd200;
    } else {
        conclusion = "Tremor Tinggi";
        color_hex = 0xff3b30;
    }

    Serial.println("--- Timer Sensor Summary ---");
    Serial.printf("Samples: %d\n", n);
    Serial.printf("Mean dynamic_g: %.6f g\n", mean);
    Serial.printf("RMS dynamic_g:  %.6f g\n", rms);
    Serial.printf("Min dynamic_g:  %.6f g\n", minv);
    Serial.printf("Max dynamic_g:  %.6f g\n", maxv);
    Serial.printf("Conclusion: %s\n", conclusion);

    // Update on-screen status label to reflect conclusion
    lv_label_set_text(guider_ui.timer_status, conclusion);
    lv_obj_set_style_text_color(guider_ui.timer_status, lv_color_hex(color_hex), LV_PART_MAIN|LV_STATE_DEFAULT);

    char lbuf[30];
    snprintf(lbuf, sizeof(lbuf), "%.2f Hz", last_freq_for_fuzzy);
    lv_label_set_text(guider_ui.timer_label_9, lbuf);

    snprintf(lbuf, sizeof(lbuf), "%.4f g", rms);
    lv_label_set_text(guider_ui.timer_label_10, lbuf);

    // Optionally print a few representative samples (every Nth)
    int step = (n > 20) ? (n / 10) : 1;
    Serial.println("Sample preview:");
    for (int i = 0; i < n; i += step) {
        Serial.printf("[%4d] %.6f g\n", i, timer_samples[i]);
    }

    timer_summary_shown = true;

    // Keep data after sending (or reset if desired)
    // If you want to clear after send, uncomment below:
    // timer_samples_count = 0;

    xSemaphoreGive(timer_samples_mutex);
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
            else if (active_scr == guider_ui.realtime) {
                Serial.println("📌 Active Screen: REAL-TIME");
            }
            else if (active_scr == guider_ui.info) {
                Serial.println("📌 Active Screen: MONITOR");
            }
            else if (active_scr == guider_ui.timer) {
                Serial.println("📌 Active Screen: timer");
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
// ICM SENSOR TASK - TIMER SCREEN
// =====================================================
void taskICMTimer(void *pv) {
    TickType_t last = xTaskGetTickCount();
    while (1) {
        // Only sample when timer screen is active AND timer is running
        xSemaphoreTake(countdown_mutex, portMAX_DELAY);
        bool timer_running = countdown_enabled;
        xSemaphoreGive(countdown_mutex);

        if (!timer_screen_active || !timer_running) {
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
                Serial.printf("⚠ ICM Timer: zero-reads detected. WHO_AM_I=0x%02X\n", who);
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

        // Also append into timer_samples while timer is running
        if (timer_running) {
            if (xSemaphoreTake(timer_samples_mutex, pdMS_TO_TICKS(10)) == pdTRUE) {
                if (timer_samples_count < TIMER_MAX_SAMPLES) {
                    timer_samples[timer_samples_count++] = dynamic_g;
                }
                xSemaphoreGive(timer_samples_mutex);
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
            Serial.printf("📊 ICM Timer: ax=%d, ay=%d, az=%d | Freq=%.2fHz, RMS=%.4fg\n",
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
        // hanya berjalan kalau timer layar aktif
        if (countdown_enabled)
        {
            xSemaphoreTake(countdown_mutex, portMAX_DELAY);

            bool just_expired = false;
            if (countdown_seconds > 0)
            {
                countdown_seconds--;

                int hh = countdown_seconds / 3600;
                int mm = (countdown_seconds % 3600) / 60;
                int ss = countdown_seconds % 60;

                char buf[20];
                sprintf(buf, "%02d:%02d:%02d", hh, mm, ss);
                lv_label_set_text(guider_ui.timer_label_8, buf);
            }
            else
            {
                countdown_enabled = false;
                just_expired = true;        // ← tandai expired
            }
            xSemaphoreGive(countdown_mutex);

            if (just_expired)
            {
                xSemaphoreGive(timer_done_sem);          // ← otomatis dipanggil saat waktu habis
            }
        }

        vTaskDelayUntil(&last, pdMS_TO_TICKS(1000)); // 1 detik update
    }
}

// ================= FUZZY LOGIC =====================
// Simple fuzzy inference using RMS (tremor amplitude) and frequency
// Produces a score in 0..100 where lower is better (Good) and higher is worse (Not Good)
static float tri(float x, float a, float b, float c) {
    if (x <= a) return 0.0f;
    if (x == b) return 1.0f;
    if (x < b) return (x - a) / (b - a);
    if (x > b && x < c) return (c - x) / (c - b);
    return 0.0f;
}
static float left_shoulder(float x, float a, float b) {
    if (x <= a) return 1.0f;
    if (x >= b) return 0.0f;
    return (b - x) / (b - a);
}
static float right_shoulder(float x, float a, float b) {
    if (x <= a) return 0.0f;
    if (x >= b) return 1.0f;
    return (x - a) / (b - a);
}

static float fuzzy_evaluate(float freq, float rms) {
    // Frequency membership (Hz) - Tabel 3.4
    float freq_verylow      = left_shoulder(freq, 3.0f, 5.0f);
    float freq_pathological = tri(freq, 3.0f, 6.0f, 9.0f);
    float freq_physio       = right_shoulder(freq, 7.0f, 10.0f);
 
    // Amplitude RMS membership (g) - Tabel 3.5
    float rms_low  = left_shoulder(rms, 0.02f, 0.06f);
    float rms_med  = tri(rms, 0.04f, 0.08f, 0.12f);
    float rms_high = right_shoulder(rms, 0.10f, 0.16f);
 
    // Rule base (Tabel 3.6) - AND pakai operator minimum
    float R1 = fminf(freq_verylow,      rms_low);   // Normal
    float R2 = fminf(freq_verylow,      rms_med);   // Tremor Ringan
    float R3 = fminf(freq_verylow,      rms_high);  // Tremor Tinggi
    float R4 = fminf(freq_pathological, rms_low);   // Tremor Ringan
    float R5 = fminf(freq_pathological, rms_med);   // Tremor Tinggi
    float R6 = fminf(freq_pathological, rms_high);  // Tremor Tinggi
    float R7 = fminf(freq_physio,       rms_low);   // Normal
    float R8 = fminf(freq_physio,       rms_med);   // Tremor Ringan
    float R9 = fminf(freq_physio,       rms_high);  // Tremor Tinggi
 
    // Agregasi rule dengan konsekuen sama pakai operator maksimum
    float alpha_normal = fmaxf(R1, R7);
    float alpha_ringan = fmaxf(R2, fmaxf(R4, R8));
    float alpha_tinggi = fmaxf(R3, fmaxf(R5, fmaxf(R6, R9)));
 
    const float C_NORMAL = 15.0f;
    const float C_RINGAN = 50.0f;
    const float C_TINGGI = 85.0f;
 
    float denom = alpha_normal + alpha_ringan + alpha_tinggi;
    float score = 0.0f;
    if (denom > 0.0f) {
        score = (alpha_normal * C_NORMAL + alpha_ringan * C_RINGAN + alpha_tinggi * C_TINGGI) / denom;
    }
 
    // small temporal smoothing to reduce jitter
    static float last_score = 0.0f;
    const float alpha_smooth = 0.4f; // new weight
    score = alpha_smooth * score + (1.0f - alpha_smooth) * last_score;
    last_score = score;
    return score;
}

// =====================================================
// LVGL TASK
void lvglTask(void *pvParameters)
{
    TickType_t lastWakeTime = xTaskGetTickCount();
    static float icmDataDisplay_tilt = 0.0f;
    static float icmDataDisplay_trend = 0.0f;
    
    while (1)
    {
        if (timer_done_sem != NULL && xSemaphoreTake(timer_done_sem, 0) == pdTRUE)
        {
            timer_send_data();
        }
        lv_obj_t *scr = lv_scr_act();
        monitor_screen_active = (scr == guider_ui.realtime);
        timer_screen_active = (scr == guider_ui.timer);

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
                    lv_label_set_text(guider_ui.realtime_label_3, buf);
                    snprintf(buf, sizeof(buf), "%.4f g", rms);
                    lv_label_set_text(guider_ui.realtime_label_5, buf);

                    // Fuzzy assessment based on freq & rms
                    float fuzzy_score = fuzzy_evaluate(freq, rms);
                    const char *status_str;
                    uint32_t status_color;
                    if (fuzzy_score < 33.0f) {
                        status_str = "Normal";
                        status_color = 0x00ff39;
                    } else if (fuzzy_score < 66.0f) {
                        status_str = "Tremor Ringan";
                        status_color = 0xffd200;
                    } else {
                        status_str = "Tremor Tinggi";
                        status_color = 0xff3b30;
                    }
                    lv_label_set_text(guider_ui.realtime_label_7, status_str);
                    lv_obj_set_style_text_color(guider_ui.realtime_label_7, lv_color_hex(status_color), LV_PART_MAIN|LV_STATE_DEFAULT);
                    Serial.printf("🔍 Fuzzy Real-time: Score=%.1f -> %s\n", fuzzy_score, status_str);

                    // Debug output
                    static uint8_t debug_counter_monitor = 0;
                    if (debug_counter_monitor++ >= 4) {
                        Serial.printf("✓ Real-time - Freq: %.2f Hz, RMS: %.4f g\n", freq, rms);
                        debug_counter_monitor = 0;
                    }
                }

                // ===== TIMER SCREEN =====
                if (timer_screen_active) {
                    // Cek apakah timer masih aktif
                    xSemaphoreTake(countdown_mutex, portMAX_DELAY);
                    bool timer_running = countdown_enabled;
                    xSemaphoreGive(countdown_mutex);

                    // Hanya update sensor data jika timer sedang aktif
                    if (timer_running) {
                        // Update label: frequency (Hz) and RMS amplitude (g)
                        snprintf(buf, sizeof(buf), "%.2f Hz", freq);
                        lv_label_set_text(guider_ui.timer_label_9, buf);
                        snprintf(buf, sizeof(buf), "%.4f g", rms);
                        lv_label_set_text(guider_ui.timer_label_10, buf);
                        
                        // Fuzzy assessment based on freq & rms
                        float fuzzy_score = fuzzy_evaluate(freq, rms);
                        const char *status_str;
                        uint32_t status_color;
                        if (fuzzy_score < 33.0f) {
                            status_str = "Normal";
                            status_color = 0x00ff39;
                        } else if (fuzzy_score < 66.0f) {
                            status_str = "Tremor Ringan";
                            status_color = 0xffd200;
                        } else {
                            status_str = "Tremor Tinggi";
                            status_color = 0xff3b30;
                        }
                        lv_label_set_text(guider_ui.timer_status, status_str);
                        lv_obj_set_style_text_color(guider_ui.timer_status, lv_color_hex(status_color), LV_PART_MAIN|LV_STATE_DEFAULT);
                        Serial.printf("🔍 Fuzzy Timer: Score=%.1f -> %s\n", fuzzy_score, status_str);

                        // Debug output
                        static uint8_t debug_counter_timer = 0;
                        if (debug_counter_timer++ >= 4) {
                            Serial.printf("✓ Timer - Freq: %.2f Hz, RMS: %.4f g\n", freq, rms);
                            debug_counter_timer = 0;
                        }
                    } else if (!timer_summary_shown) {
                        // Hanya reset ke Idle sebelum summary tampil
                        lv_label_set_text(guider_ui.timer_label_9, "--.- Hz");
                        lv_label_set_text(guider_ui.timer_label_10, "--.----- g");
                        lv_label_set_text(guider_ui.timer_status, "Idle");
                        lv_obj_set_style_text_color(guider_ui.timer_status, lv_color_hex(0x7f8c8d), LV_PART_MAIN|LV_STATE_DEFAULT);
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
    timer_samples_mutex = xSemaphoreCreateMutex();
    countdown_mutex = xSemaphoreCreateMutex();
    timer_done_sem = xSemaphoreCreateBinary();

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
    xTaskCreatePinnedToCore(taskICMTimer,        "ICMTimer", 4096, NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(taskCountdown,       "CountdownTask", 4096, NULL, 2, NULL, 1);
}

void loop() {
    // FreeRTOS → loop kosong
}