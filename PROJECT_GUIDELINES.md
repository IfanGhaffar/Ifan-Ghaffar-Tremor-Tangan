# Poject Guidelines

## 📁 Struktur Folder

Berikut adalah struktur direktori standar dalam proyek ini:

```bash
/project-root
│── src/                # Source code utama
│   ├── main.cpp        # Entry point utama
│   ├── ui/             # File UI dari SquareLine Studio
│   ├── lvgl_port/      # Porting LVGL ke ESP32
│   ├── tasks/          # Task berbasis FreeRTOS
│── lib/                # Library eksternal
│── include/            # Header files (.h)
│── platformio.ini      # Konfigurasi PlatformIO
│── README.md           # Dokumentasi proyek
```

## 📜 Standar Penamaan

- **File source code**: `snake_case.cpp` (contoh: `display_manager.cpp`)
- **File header**: `snake_case.h` (contoh: `touch_driver.h`)
- **Nama class**: `PascalCase` (contoh: `TouchController`)
- **Variabel**: `snake_case` (contoh: `button_state`)
- **Konstanta**: `UPPER_CASE` (contoh: `MAX_BUFFER_SIZE`)
- **Fungsi**: `snake_case` (contoh: `update_display()`)

## 🔥 Coding Style

- Gunakan **2 spasi** untuk indentasi
- Selalu gunakan **`const`** jika memungkinkan
- Gunakan **doxygen-style comments** untuk dokumentasi fungsi
- Pisahkan **deklarasi** dan **implementasi** di `.h` dan `.cpp`

Contoh:

```cpp
/**
 * @brief Inisialisasi layar LCD
 * @return true jika berhasil, false jika gagal
 */
bool init_display();
```

## ⏳ FreeRTOS Task Standard

- Semua task harus memiliki stack size yang cukup (`4096` atau lebih)
- Gunakan **`xTaskCreatePinnedToCore`** untuk menentukan core
- Gunakan **mutex** untuk akses variabel global antar task

Contoh task:

```cpp
void lvgl_task(void *pvParameters) {
    while (1) {
        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
```

## 🕒 Real-Time Clock (RTC) & NTP

- Gunakan **NTP** untuk sinkronisasi waktu
- Simpan waktu ke **RTC** jika perangkat offline

## 🖥️ SquareLine Studio UI Standard

- Semua objek UI disimpan di `ui/`
- Gunakan nama **`ui_ElementName`** (contoh: `ui_Label_Clock`)
- UI diperbarui di **loop** atau FreeRTOS task

## 🛠️ Debugging & Logging

- Gunakan **Serial Monitor** untuk debug (`Serial.println()`)
- Tambahkan **log level** (INFO, WARNING, ERROR)

Contoh:

```cpp
#define LOG_INFO(msg) Serial.println("[INFO] " + String(msg))
LOG_INFO("Display Initialized");
```

## 📦 PlatformIO Dependency Management

- Semua dependensi harus ditambahkan ke `platformio.ini`

Contoh:

```ini
lib_deps =
    https://github.com/lvgl/lvgl.git#release/v8.3
    https://github.com/arduino-libraries/Arduino_GFX.git
```

## 📌 Git & Commit Convention

Gunakan format commit berikut:

```md
<type>(<scope>): <message>
```

### 📌 Tipe Commit

| Tipe       | Deskripsi                                    |
| ---------- | -------------------------------------------- |
| `feat`     | Menambahkan fitur baru                       |
| `fix`      | Memperbaiki bug                              |
| `docs`     | Perubahan dokumentasi                        |
| `style`    | Perbaikan format, tidak mempengaruhi kode    |
| `refactor` | Refactor kode tanpa mengubah fungsionalitas  |
| `perf`     | Peningkatan performa                         |
| `test`     | Menambahkan atau memperbaiki test            |
| `chore`    | Perubahan minor (misal: update dependencies) |

### 📌 Contoh Commit

```bash
feat(display): menambahkan fitur animasi transisi
fix(touch): memperbaiki bug respons sentuhan di panel
refactor(lvgl): merapikan struktur kode untuk lebih modular
```

### 📌 Branching Strategy

Gunakan konvensi berikut untuk nama branch:

```md
<type>/<deskripsi-singkat>
```

| Tipe Branch | Deskripsi                     |
| ----------- | ----------------------------- |
| `feature/`  | Branch untuk fitur baru       |
| `bugfix/`   | Perbaikan bug                 |
| `hotfix/`   | Patch cepat untuk bug darurat |
| `release/`  | Branch untuk persiapan rilis  |

### 📌 Contoh Nama Branch

```bash
feature/display-animations
bugfix/touch-response-delay
hotfix/crash-on-startup
```

### 🔁 Pull Request (PR) Guidelines

- Pastikan kode sudah diuji sebelum membuat PR.
- Beri deskripsi yang jelas tentang perubahan yang dilakukan.
- Gunakan template PR standar berikut:

```md
## Ringkasan Perubahan

- Menambahkan fitur X
- Memperbaiki bug Y

## Perubahan Utama

- [x] Modul A diupdate
- [x] Perbaikan di modul B

## Cara Uji

1. Jalankan `pio run -t upload`
2. Periksa tampilan UI
3. Pastikan tidak ada error di serial monitor
```

---

🔥 **Pastikan semua kode mengikuti standar ini!** 🚀
