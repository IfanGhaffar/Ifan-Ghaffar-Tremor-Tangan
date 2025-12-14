/*
 * Copyright 2025 NXP
 * NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */
#ifndef LV_CONF_H
#define LV_CONF_H

/*====================
 * COLOR SETTINGS
 *====================*/

/*Maximal horizontal resolution*/
#define LV_HOR_RES_MAX (320)

/*Maximal vertical resolution*/
#define LV_VER_RES_MAX (170)

/*Color depth: 1 (I1), 8 (L8), 16 (RGB565), 24 (RGB888), 32 (XRGB8888)*/
#define LV_COLOR_DEPTH 16

/*=========================
 * STDLIB WRAPPER SETTINGS
 *=========================*/

/* Possible values:
 * - LV_STDLIB_BUILTIN:     LVGL's built in implementation
 * - LV_STDLIB_CLIB:        Standard C functions, like malloc, strlen, etc.
 * - LV_STDLIB_MICROPYTHON: MicroPython implementation
 * - LV_STDLIB_RTTHREAD:    RT-Thread implementation
 * - LV_STDLIB_CUSTOM:      Implement the functions externally
 */
#define LV_USE_STDLIB_MALLOC LV_STDLIB_BUILTIN
#define LV_USE_STDLIB_STRING LV_STDLIB_BUILTIN
#define LV_USE_STDLIB_SPRINTF LV_STDLIB_BUILTIN

#define LV_STDINT_INCLUDE <stdint.h>
#define LV_STDDEF_INCLUDE <stddef.h>
#define LV_STDBOOL_INCLUDE <stdbool.h>
#define LV_INTTYPES_INCLUDE <inttypes.h>
#define LV_LIMITS_INCLUDE <limits.h>
#define LV_STDARG_INCLUDE <stdarg.h>

#if LV_USE_STDLIB_MALLOC == LV_STDLIB_BUILTIN
/*Size of the memory available for `lv_malloc()` in bytes (>= 2kB)*/
#ifndef LV_MEM_SIZE
#define LV_MEM_SIZE (320U * 1024U)
#endif
/*Size of the memory expand for `lv_malloc()` in bytes*/
#define LV_MEM_POOL_EXPAND_SIZE 0
#endif /*LV_USE_STDLIB_MALLOC == LV_STDLIB_BUILTIN*/

/*====================
 * HAL SETTINGS
 *====================*/

/*Default display refresh, input device read and animation step period[ms].*/
#define LV_DEF_REFR_PERIOD 30

/*Default Dot Per Inch(px/inch). Used to initialize default sizes such as widgets, paddings, etc.*/
#define LV_DPI_DEF 130

/*====================
 * OPERATING SYSTEM
 *====================*/

/*Select an operating system to use. Possible options:
 * - LV_OS_NONE
 * - LV_OS_PTHREAD
 * - LV_OS_FREERTOS
 * - LV_OS_CMSIS_RTOS2
 * - LV_OS_RTTHREAD
 * - LV_OS_WINDOWS
 * - LV_OS_MQX
 * - LV_OS_CUSTOM
 */
#define LV_USE_OS LV_OS_NONE

#if LV_USE_OS == LV_OS_CUSTOM
#define LV_OS_CUSTOM_INCLUDE <stdint.h>
#endif

#if LV_USE_OS == LV_OS_FREERTOS
/*
 * Unblocking an RTOS task with a direct notification is 45% faster and uses less RAM
 * than unblocking a task using an intermediary object such as a binary semaphore.
 * RTOS task notifications can only be used when there is only one task that can be the recipient of the event.
 */
#define LV_USE_FREERTOS_TASK_NOTIFY 1
#endif

/*=======================
 * RENDERING CONFIGURATION
 *=======================*/

/*Align the stride of all layers and images to this many bytes*/
#define LV_DRAW_BUF_STRIDE_ALIGN 1

/*Align the start address of draw_buf addresses to this many bytes*/
#define LV_DRAW_BUF_ALIGN 4

/*Using matrix for transformations.
 *Requires: LV_USE_MATRIX = 1.
 *The rendering engine needs to support 3x3 matrix transformations.*/
#define LV_DRAW_TRANSFORM_USE_MATRIX 0

/* If a widget has `style_opa < 255` (bukan bg_opa, text_opa, dll) atau blend mode bukan NORMAL,
 * maka widget tersebut di-buffer ke dalam layer "simple" sebelum dirender.
 * Layer "transformed" (jika `transform_angle/zoom` di-set) menggunakan buffer yang lebih besar
 * dan tidak dapat dirender dalam potongan-potongan.
 */

/*Target buffer size [bytes] untuk simple layer chunks.*/
#define LV_DRAW_LAYER_SIMPLE_BUF_SIZE (24U * 1024U)

/*Stack size untuk drawing thread.
 *NOTE: Jika FreeType atau ThorVG diaktifkan, disarankan untuk mengaturnya setidaknya 32KB.
 */
#define LV_DRAW_THREAD_STACK_SIZE (8U * 1024U)

#define LV_USE_DRAW_SW 1
#if LV_USE_DRAW_SW

/*
 * Pilih untuk menonaktifkan dukungan format warna tertentu untuk mengurangi ukuran kode.
 * CATATAN: beberapa fitur menggunakan format warna tertentu secara internal, misalnya:
 * - gradien menggunakan RGB888
 * - bitmap dengan transparansi dapat menggunakan ARGB8888
 */
#define LV_DRAW_SW_SUPPORT_RGB565 1
#define LV_DRAW_SW_SUPPORT_RGB565A8 1
#define LV_DRAW_SW_SUPPORT_RGB888 1
#define LV_DRAW_SW_SUPPORT_XRGB8888 1
#define LV_DRAW_SW_SUPPORT_ARGB8888 1
#define LV_DRAW_SW_SUPPORT_L8 1
#define LV_DRAW_SW_SUPPORT_AL88 1
#define LV_DRAW_SW_SUPPORT_A8 1
#define LV_DRAW_SW_SUPPORT_I1 1

/*Jumlah unit draw.
 * > 1 membutuhkan OS (LV_USE_OS != LV_OS_NONE)
 * > 1 berarti rendering paralel dengan multi-thread.
 */
#define LV_DRAW_SW_DRAW_UNIT_CNT 1

/*Gunakan Arm-2D untuk mempercepat rendering software*/
#define LV_USE_DRAW_ARM2D_SYNC 0

/*Aktifkan assembly helium native (jika tersedia)*/
#define LV_USE_NATIVE_HELIUM_ASM 0

/*0: Gunakan renderer sederhana yang hanya mampu menggambar persegi panjang sederhana dengan gradien, gambar, teks, dan garis lurus.
 *1: Gunakan renderer kompleks yang mampu menggambar sudut membulat, bayangan, garis miring, dan busur.
 */
#define LV_DRAW_SW_COMPLEX 1
#if LV_DRAW_SW_COMPLEX
/*Izinkan buffering perhitungan bayangan.
 *LV_DRAW_SW_SHADOW_CACHE_SIZE adalah ukuran bayangan maksimum yang dapat di-buffer, di mana ukuran bayangan = shadow_width + radius.
 *Caching menggunakan biaya RAM sebesar (LV_DRAW_SW_SHADOW_CACHE_SIZE)^2 bytes.
 */
#define LV_DRAW_SW_SHADOW_CACHE_SIZE 0

/*Jumlah data lingkaran yang di-cache maksimal.
 *Perempat keliling lingkaran disimpan untuk anti-aliasing.
 *0: nonaktifkan caching.
 */
#define LV_DRAW_SW_CIRCLE_CACHE_SIZE 4
#endif

#define LV_USE_DRAW_SW_ASM LV_DRAW_SW_ASM_NONE
#if LV_USE_DRAW_SW_ASM == LV_DRAW_SW_ASM_CUSTOM
#define LV_DRAW_SW_ASM_CUSTOM_INCLUDE ""
#endif

/*Aktifkan gradien kompleks di software: linear pada sudut, radial, atau konikal.*/
#define LV_USE_DRAW_SW_COMPLEX_GRADIENTS 0
#endif /* LV_USE_DRAW_SW */

#if LV_USE_DRAW_VGLITE
/*Aktifkan workaround degradasi kualitas blit untuk dimensi layar > 352 px.*/
#define LV_USE_VGLITE_BLIT_SPLIT 0

#if LV_USE_OS
/*Gunakan thread tambahan untuk VG-Lite processing.*/
#define LV_USE_VGLITE_DRAW_THREAD 1

#if LV_USE_VGLITE_DRAW_THREAD
/*Aktifkan VG-Lite draw async. Antrean beberapa tugas dan flush sekaligus ke GPU.*/
#define LV_USE_VGLITE_DRAW_ASYNC 1
#endif
#endif

/*Aktifkan assert untuk VG-Lite.*/
#define LV_USE_VGLITE_ASSERT 0
#endif /* LV_USE_DRAW_VGLITE */

#if LV_USE_PXP
/*Gunakan PXP untuk rendering.*/
#define LV_USE_DRAW_PXP 1

/*Gunakan PXP untuk memutar tampilan.*/
#define LV_USE_ROTATE_PXP 0
#if LV_USE_DRAW_PXP && LV_USE_OS
/*Gunakan thread tambahan untuk PXP processing.*/
#define LV_USE_PXP_DRAW_THREAD 1
#endif

/*Aktifkan assert untuk PXP.*/
#define LV_USE_PXP_ASSERT 0
#endif /* LV_USE_PXP */

/*Gunakan Renesas Dave2D pada platform RA.*/
#define LV_USE_DRAW_DAVE2D 0

/*Gambar menggunakan cached SDL textures.*/
#define LV_USE_DRAW_SDL 0

/*Gunakan VG-Lite GPU.*/
#define LV_USE_DRAW_VG_LITE 0
#if LV_USE_DRAW_VG_LITE
/*Aktifkan fungsi eksternal 'gpu_init()' khusus VG-Lite*/
#define LV_VG_LITE_USE_GPU_INIT 0

/*Aktifkan assert untuk VG-Lite.*/
#define LV_VG_LITE_USE_ASSERT 0

/*Threshold flush commit VG-Lite. GPU akan mencoba batch sebanyak ini tugas render.*/
#define LV_VG_LITE_FLUSH_MAX_COUNT 8

/*Aktifkan border untuk mensimulasikan bayangan (biasanya meningkatkan performa, tetapi tidak menjamin kualitas render yang sama).*/
#define LV_VG_LITE_USE_BOX_SHADOW 0

/*Jumlah cache maksimum untuk gradien VG-Lite (satu gambar gradien memerlukan sekitar 4K bytes).*/
#define LV_VG_LITE_GRAD_CACHE_CNT 32

/*Jumlah cache maksimum untuk stroke VG-Lite.*/
#define LV_VG_LITE_STROKE_CACHE_CNT 32
#endif /* LV_USE_DRAW_VG_LITE */

/*=======================
 * FEATURE CONFIGURATION
 *=======================*/

/*-------------
 * Logging
 *-----------*/

/*Aktifkan modul log*/
#define LV_USE_LOG 0
#if LV_USE_LOG
/*Level log:
 * LV_LOG_LEVEL_TRACE: Informasi detail,
 * LV_LOG_LEVEL_INFO:  Event penting,
 * LV_LOG_LEVEL_WARN:  Peringatan,
 * LV_LOG_LEVEL_ERROR: Error kritis,
 * LV_LOG_LEVEL_USER:  Log yang ditambahkan user,
 * LV_LOG_LEVEL_NONE:  Nonaktifkan logging.
 */
#define LV_LOG_LEVEL LV_LOG_LEVEL_WARN

/*1: Print log menggunakan 'printf'; 0: User harus register callback dengan `lv_log_register_print_cb()`*/
#define LV_LOG_PRINTF 0

/*1: Aktifkan timestamp; 0: Nonaktifkan*/
#define LV_LOG_USE_TIMESTAMP 1

/*1: Cetak file dan nomor baris pada log; 0: Tidak dicetak*/
#define LV_LOG_USE_FILE_LINE 1

/*Aktifkan/Nonaktifkan LV_LOG_TRACE untuk modul yang menghasilkan banyak log*/
#define LV_LOG_TRACE_MEM 1
#define LV_LOG_TRACE_TIMER 1
#define LV_LOG_TRACE_INDEV 1
#define LV_LOG_TRACE_DISP_REFR 1
#define LV_LOG_TRACE_EVENT 1
#define LV_LOG_TRACE_OBJ_CREATE 1
#define LV_LOG_TRACE_LAYOUT 1
#define LV_LOG_TRACE_ANIM 1
#define LV_LOG_TRACE_CACHE 1
#endif /* LV_USE_LOG */

/*-------------
 * Asserts
 *-----------*/

/*Aktifkan assert jika terjadi operasi gagal atau data tidak valid.
 *Jika LV_USE_LOG diaktifkan, pesan error akan dicetak.
 */
#define LV_USE_ASSERT_NULL 1
#define LV_USE_ASSERT_MALLOC 1
#define LV_USE_ASSERT_STYLE 0
#define LV_USE_ASSERT_MEM_INTEGRITY 0
#define LV_USE_ASSERT_OBJ 0

/*Handler custom untuk assert (misalnya untuk merestart MCU)*/
#define LV_ASSERT_HANDLER_INCLUDE <stdint.h>
/*Secara default, berhenti jika terjadi assert*/
#define LV_ASSERT_HANDLER \
  while (1)               \
    ;

/*-------------
 * Debug
 *-----------*/

/*1: Gambar persegi panjang berwarna acak di area yang direfresh*/
#define LV_USE_REFR_DEBUG 0

/*1: Gambar overlay merah untuk layer ARGB dan hijau untuk layer RGB*/
#define LV_USE_LAYER_DEBUG 0

/*1: Gambar overlay dengan warna berbeda untuk setiap task draw_unit.
 *Juga tambahkan nomor indeks task pada latar belakang putih (atau hitam untuk layer).
 */
#define LV_USE_PARALLEL_DRAW_DEBUG 0

/*-------------
 * Others
 *-----------*/

#define LV_ENABLE_GLOBAL_CUSTOM 0
#if LV_ENABLE_GLOBAL_CUSTOM
#define LV_GLOBAL_CUSTOM_INCLUDE <stdint.h>
#endif

/*Ukuran cache default dalam bytes.
 *Digunakan oleh decoder gambar seperti `lv_lodepng`.
 */
#define LV_CACHE_DEF_SIZE 0

/*Jumlah cache entri header gambar default.*/
#define LV_IMAGE_HEADER_CACHE_DEF_CNT 0

/*Jumlah stop maksimal per gradien.
 *Penambahan stop menambah (sizeof(lv_color_t) + 1) bytes.
 */
#define LV_GRADIENT_MAX_STOPS 2

/*Penyesuaian pembulatan fungsi color mix.
 *0: pembulatan ke bawah, 64: pembulatan dari x.75, 128: pembulatan dari setengah, 192: pembulatan dari x.25, 254: pembulatan ke atas.
 */
#define LV_COLOR_MIX_ROUND_OFS 0

/*Tambahkan 2 variabel 32-bit ke setiap lv_obj_t untuk mempercepat akses properti style.*/
#define LV_OBJ_STYLE_CACHE 0

/*Tambahkan field `id` ke lv_obj_t.*/
#define LV_USE_OBJ_ID 0

/*Penugasan ID otomatis saat objek dibuat.*/
#define LV_OBJ_ID_AUTO_ASSIGN LV_USE_OBJ_ID

/*Gunakan fungsi built-in untuk penanganan ID objek.*/
#define LV_USE_OBJ_ID_BUILTIN 1

/*Gunakan API set/get properti objek.*/
#define LV_USE_OBJ_PROPERTY 0

/*Aktifkan dukungan nama properti.*/
#define LV_USE_OBJ_PROPERTY_NAME 0

/* VG-Lite Simulator */
/*Memerlukan: LV_USE_THORVG_INTERNAL atau LV_USE_THORVG_EXTERNAL*/
#define LV_USE_VG_LITE_THORVG 0
#if LV_USE_VG_LITE_THORVG
#define LV_VG_LITE_THORVG_LVGL_BLEND_SUPPORT 0
#define LV_VG_LITE_THORVG_YUV_SUPPORT 0
#define LV_VG_LITE_THORVG_LINEAR_GRADIENT_EXT_SUPPORT 0
#define LV_VG_LITE_THORVG_16PIXELS_ALIGN 1
#define LV_VG_LITE_THORVG_BUF_ADDR_ALIGN 64
#define LV_VG_LITE_THORVG_THREAD_RENDER 0
#endif

/*====================
 * COMPILER SETTINGS
 *====================*/

/*Untuk sistem big endian set ke 1*/
#define LV_BIG_ENDIAN_SYSTEM 0

/*Attribute custom untuk fungsi `lv_tick_inc`*/
#define LV_ATTRIBUTE_TICK_INC

/*Attribute custom untuk fungsi `lv_timer_handler`*/
#define LV_ATTRIBUTE_TIMER_HANDLER

/*Attribute custom untuk fungsi `lv_display_flush_ready`*/
#define LV_ATTRIBUTE_FLUSH_READY

/*Ukuran alignment yang dibutuhkan untuk buffer*/
#define LV_ATTRIBUTE_MEM_ALIGN_SIZE 1

/*Attribute untuk memastikan buffer ter-align (misalnya __attribute__((aligned(4))) )*/
#define LV_ATTRIBUTE_MEM_ALIGN

#ifndef LV_ATTRIBUTE_LARGE_CONST
#define LV_ATTRIBUTE_LARGE_CONST
#endif

/*Prefix deklarasi array besar di RAM*/
#define LV_ATTRIBUTE_LARGE_RAM_ARRAY

/*Tempatkan fungsi kritis ke dalam memori cepat (misalnya RAM)*/
#define LV_ATTRIBUTE_FAST_MEM

/*Export integer constant untuk binding (misalnya Micropython)*/
#define LV_EXPORT_CONST_INT(int_value) struct _silence_gcc_warning

/*Prefix semua data global extern*/
#define LV_ATTRIBUTE_EXTERN_DATA

/*Gunakan `float` sebagai `lv_value_precise_t`*/
#define LV_USE_FLOAT 0

/*Aktifkan dukungan matriks (memerlukan LV_USE_FLOAT = 1)*/
#define LV_USE_MATRIX 0

/*Sertakan `lvgl_private.h` dalam `lvgl.h` untuk akses internal*/
#define LV_USE_PRIVATE_API 1

/*====================
 * FONT USAGE
 *====================*/

/*Font Montserrat dengan range ASCII dan beberapa simbol (bpp = 4)*/
#define LV_FONT_MONTSERRAT_8 0
#define LV_FONT_MONTSERRAT_10 0
#define LV_FONT_MONTSERRAT_12 1
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_MONTSERRAT_16 0
#define LV_FONT_MONTSERRAT_18 0
#define LV_FONT_MONTSERRAT_20 0
#define LV_FONT_MONTSERRAT_22 0
#define LV_FONT_MONTSERRAT_24 0
#define LV_FONT_MONTSERRAT_26 0
#define LV_FONT_MONTSERRAT_28 0
#define LV_FONT_MONTSERRAT_30 0
#define LV_FONT_MONTSERRAT_32 0
#define LV_FONT_MONTSERRAT_34 0
#define LV_FONT_MONTSERRAT_36 0
#define LV_FONT_MONTSERRAT_38 0
#define LV_FONT_MONTSERRAT_40 0
#define LV_FONT_MONTSERRAT_42 0
#define LV_FONT_MONTSERRAT_44 0
#define LV_FONT_MONTSERRAT_46 0
#define LV_FONT_MONTSERRAT_48 0

/*Fitur khusus*/
/*bpp = 3*/
#define LV_FONT_MONTSERRAT_28_COMPRESSED 0
/*Font DejaVu untuk Bahasa Persia/Hebrew*/
#define LV_FONT_DEJAVU_16_PERSIAN_HEBREW 0
/*1000 radikal CJK paling umum*/
#define LV_FONT_SIMSUN_14_CJK 0
#define LV_FONT_SIMSUN_16_CJK 0

/*Font monospace pixel perfect*/
#define LV_FONT_UNSCII_8 0
#define LV_FONT_UNSCII_16 0

/*Deklarasi custom fonts (opsional)*/
#define LV_FONT_CUSTOM_DECLARE

/*Set font default*/
#define LV_FONT_DEFAULT &lv_font_montserrat_14

/*Dukungan font besar atau dengan banyak karakter*/
#define LV_FONT_FMT_TXT_LARGE 0

/*Dukungan font terkompres*/
#define LV_USE_FONT_COMPRESSED 0

/*Gambar placeholder jika glyph tidak ditemukan*/
#define LV_USE_FONT_PLACEHOLDER 1

/*====================
 * TEXT SETTINGS
 *====================*/

/*Encoding karakter string.
 * Pilihan: LV_TXT_ENC_UTF8, LV_TXT_ENC_ASCII.
 */
#define LV_TXT_ENC LV_TXT_ENC_UTF8

/*Karakter pemisah untuk break teks*/
#define LV_TXT_BREAK_CHARS " ,.;:-_)]}"

/*Panjang minimal kata untuk break secara otomatis (set <= 0 untuk nonaktifkan)*/
#define LV_TXT_LINE_BREAK_LONG_LEN 0

/*Minimal karakter sebelum break dalam kata panjang*/
#define LV_TXT_LINE_BREAK_LONG_PRE_MIN_LEN 3

/*Minimal karakter setelah break dalam kata panjang*/
#define LV_TXT_LINE_BREAK_LONG_POST_MIN_LEN 3

/*Dukungan teks bidirectional*/
#define LV_USE_BIDI 0
#if LV_USE_BIDI
#define LV_BIDI_BASE_DIR_DEF LV_BASE_DIR_AUTO
#endif

/*Dukungan pengolahan karakter Arab/Persia*/
#define LV_USE_ARABIC_PERSIAN_CHARS 0

/*====================
 * WIDGETS
 *====================*/

/*Dokumentasi widget: https://docs.lvgl.io/latest/en/html/widgets/index.html*/
#define LV_WIDGETS_HAS_DEFAULT_VALUE 1

#define LV_USE_ANIMIMG 1

#define LV_USE_ARC 1

#define LV_USE_BAR 1

#define LV_USE_BUTTON 1

#define LV_USE_BUTTONMATRIX 1

#define LV_USE_CALENDAR 1
#if LV_USE_CALENDAR
#define LV_CALENDAR_WEEK_STARTS_MONDAY 0
#if LV_CALENDAR_WEEK_STARTS_MONDAY
#define LV_CALENDAR_DEFAULT_DAY_NAMES {"Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"}
#else
#define LV_CALENDAR_DEFAULT_DAY_NAMES {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"}
#endif
#define LV_CALENDAR_DEFAULT_MONTH_NAMES {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"}
#define LV_USE_CALENDAR_HEADER_ARROW 1
#define LV_USE_CALENDAR_HEADER_DROPDOWN 1
#define LV_USE_CALENDAR_CHINESE 0
#endif

#define LV_USE_CANVAS 1

#define LV_USE_CAROUSEL 1

#define LV_USE_CHART 1

#define LV_USE_CHECKBOX 1

#define LV_USE_DROPDOWN 1

#define LV_USE_IMAGE 1

#define LV_USE_IMAGEBUTTON 1

#define LV_USE_KEYBOARD 0

#define LV_USE_LABEL 1
#if LV_USE_LABEL
#define LV_LABEL_TEXT_SELECTION 1
#define LV_LABEL_LONG_TXT_HINT 1
#define LV_LABEL_WAIT_CHAR_COUNT 3
#endif

#define LV_USE_LED 1

#define LV_USE_ANIMATION 1

#define LV_USE_LINE 1

#define LV_USE_LIST 1

#define LV_USE_LOTTIE 0

#define LV_USE_MENU 1

#define LV_USE_MSGBOX 1

#define LV_USE_ROLLER 1

#define LV_USE_SCALE 1

#define LV_USE_SLIDER 1

#define LV_USE_SPAN 1
#if LV_USE_SPAN
#define LV_SPAN_SNIPPET_STACK_SIZE 64
#endif

#define LV_USE_SPINBOX 1

#define LV_USE_SPINNER 1

#define LV_USE_SWITCH 1

#define LV_USE_TEXTAREA 1
#if LV_USE_TEXTAREA
#define LV_TEXTAREA_DEF_PWD_SHOW_TIME 1500
#endif

#define LV_USE_TABLE 1

#define LV_USE_TABVIEW 1

#define LV_USE_TILEVIEW 1

#define LV_USE_VIDEO 0

#define LV_USE_WIN 1

/*====================
 * THEMES
 *====================*/

/*A simple and complete theme*/
#define LV_USE_THEME_DEFAULT 1
#if LV_USE_THEME_DEFAULT
#define LV_THEME_DEFAULT_DARK 0
#define LV_THEME_DEFAULT_GROW 1
#define LV_THEME_DEFAULT_TRANSITION_TIME 80
#endif

/*Theme sederhana sebagai titik awal kustomisasi*/
#define LV_USE_THEME_SIMPLE 1

/*Theme untuk tampilan monokrom*/
#define LV_USE_THEME_MONO 1

/*====================
 * LAYOUTS
 *====================*/

/*Layout mirip Flexbox pada CSS*/
#define LV_USE_FLEX 1

/*Layout mirip Grid pada CSS*/
#define LV_USE_GRID 1

/*====================
 * 3RD PARTS LIBRARIES
 *====================*/

/*File system interfaces untuk API umum*/

/*Default driver letter untuk file system*/
#define LV_FS_DEFAULT_DRIVE_LETTER '\0'

/*API untuk fopen, fread, dll.*/
#define LV_USE_FS_STDIO 0
#if LV_USE_FS_STDIO
#define LV_FS_STDIO_LETTER 'C'
#define LV_FS_STDIO_PATH ""
#define LV_FS_STDIO_CACHE_SIZE 0
#endif

/*API untuk POSIX*/
#define LV_USE_FS_POSIX 0
#if LV_USE_FS_POSIX
#define LV_FS_POSIX_LETTER '\0'
#define LV_FS_POSIX_PATH ""
#define LV_FS_POSIX_CACHE_SIZE 0
#endif

/*API untuk WIN32*/
#define LV_USE_FS_WIN32 0
#if LV_USE_FS_WIN32
#define LV_FS_WIN32_LETTER '\0'
#define LV_FS_WIN32_PATH ""
#define LV_FS_WIN32_CACHE_SIZE 0
#endif

/*API untuk FATFS*/
#define LV_USE_FS_FATFS 0
#if LV_USE_FS_FATFS
#define LV_FS_FATFS_LETTER '\0'
#define LV_FS_FATFS_CACHE_SIZE 0
#endif

/*API untuk RAWFS*/
#define LV_USE_FS_RAWFS 0
#if LV_USE_FS_RAWFS
#define LV_FS_RAWFS_LETTER '\0'
#define LV_FS_RAWFS_XIP 0
#if LV_FS_RAWFS_XIP
#define LV_FS_RAWFS_XIP_BASE_ADDR
#endif
#endif

/*API untuk memory-mapped file access*/
#define LV_USE_FS_MEMFS 0
#if LV_USE_FS_MEMFS
#define LV_FS_MEMFS_LETTER '\0'
#endif

/*API untuk LittleFs*/
#define LV_USE_FS_LITTLEFS 0
#if LV_USE_FS_LITTLEFS
#define LV_FS_LITTLEFS_LETTER '\0'
#endif

/*API untuk Arduino LittleFs*/
#define LV_USE_FS_ARDUINO_ESP_LITTLEFS 0
#if LV_USE_FS_ARDUINO_ESP_LITTLEFS
#define LV_USE_FS_ARDUINO_ESP_LITTLEFS '\0'
#endif

/*API untuk Arduino SD*/
#define LV_USE_FS_ARDUINO_SD 0
#if LV_USE_FS_ARDUINO_SD
#define LV_FS_ARDUINO_SD_LETTER '\0'
#endif

/*LODEPNG decoder library*/
#define LV_USE_LODEPNG 0

/*PNG decoder (libpng) library*/
#define LV_USE_LIBPNG 0

/*BMP decoder library*/
#define LV_USE_BMP 0

/*JPG + split JPG decoder library*/
#define LV_USE_TJPGD 0

/*libjpeg-turbo decoder library*/
#define LV_USE_LIBJPEG_TURBO 0

/*GIF decoder library*/
#define LV_USE_GIF 0
#if LV_USE_GIF
#define LV_GIF_CACHE_DECODE_DATA 0
#endif

/*Decode bin images to RAM*/
#define LV_BIN_DECODER_RAM_LOAD 0

/*RLE decompress library*/
#define LV_USE_RLE 0

/*QR code library*/
#define LV_USE_QRCODE 1

/*Barcode library*/
#define LV_USE_BARCODE 1

/*FreeType library*/
#define LV_USE_FREETYPE 0
#if LV_USE_FREETYPE
#define LV_FREETYPE_USE_LVGL_PORT 0
#define LV_FREETYPE_CACHE_FT_GLYPH_CNT 256
#endif

/*Built-in TTF decoder*/
#define LV_USE_TINY_TTF 0
#if LV_USE_TINY_TTF
#define LV_TINY_TTF_FILE_SUPPORT 0
#define LV_TINY_TTF_CACHE_GLYPH_CNT 256
#endif

/*Rlottie library*/
#define LV_USE_RLOTTIE 0

/*Enable Vector Graphic APIs (memerlukan LV_USE_MATRIX = 1)*/
#define LV_USE_VECTOR_GRAPHIC 0

/*Enable ThorVG internal*/
#define LV_USE_THORVG_INTERNAL 0

/*Enable ThorVG eksternal*/
#define LV_USE_THORVG_EXTERNAL 0

/*Gunakan LZ4 internal bawaan LVGL*/
#define LV_USE_LZ4_INTERNAL 0

/*Gunakan LZ4 eksternal*/
#define LV_USE_LZ4_EXTERNAL 0

/*FFmpeg library untuk decoding gambar dan video*/
#define LV_USE_FFMPEG 0
#if LV_USE_FFMPEG
#define LV_FFMPEG_DUMP_FORMAT 0
#endif

/*====================
 * OTHERS
 *====================*/

/*Aktifkan API snapshot untuk objek*/
#define LV_USE_SNAPSHOT 0

/*Aktifkan komponen system monitor*/
#define LV_USE_SYSMON 1
#if LV_USE_SYSMON
#define LV_SYSMON_GET_IDLE lv_timer_get_idle
#define LV_USE_PERF_MONITOR 0
#if LV_USE_PERF_MONITOR
#define LV_USE_PERF_MONITOR_POS LV_ALIGN_BOTTOM_RIGHT
#define LV_USE_PERF_MONITOR_LOG_MODE 0
#endif
#define LV_USE_MEM_MONITOR 0
#if LV_USE_MEM_MONITOR
#define LV_USE_MEM_MONITOR_POS LV_ALIGN_BOTTOM_LEFT
#endif
#endif

/*Aktifkan runtime performance profiler*/
#define LV_USE_PROFILER 0
#if LV_USE_PROFILER
#define LV_USE_PROFILER_BUILTIN 1
#if LV_USE_PROFILER_BUILTIN
#define LV_PROFILER_BUILTIN_BUF_SIZE (16U * 1024U)
#endif
#define LV_PROFILER_INCLUDE lvgl / src / misc / lv_profiler_builtin.h
#define LV_PROFILER_BEGIN LV_PROFILER_BUILTIN_BEGIN
#define LV_PROFILER_END LV_PROFILER_BUILTIN_END
#define LV_PROFILER_BEGIN_TAG LV_PROFILER_BUILTIN_BEGIN_TAG
#define LV_PROFILER_END_TAG LV_PROFILER_BUILTIN_END_TAG
#endif

/*Aktifkan Monkey test*/
#define LV_USE_MONKEY 0

/*Aktifkan grid navigation*/
#define LV_USE_GRIDNAV 0

/*Aktifkan lv_obj fragment*/
#define LV_USE_FRAGMENT 0

/*Dukungan penggunaan gambar sebagai font pada label/span*/
#define LV_USE_IMGFONT 0

/*Aktifkan observer pattern*/
#define LV_USE_OBSERVER 1

/*Aktifkan metode input Pinyin (memerlukan lv_keyboard)*/
#define LV_USE_IME_PINYIN 0
#if LV_USE_IME_PINYIN
#define LV_IME_PINYIN_USE_DEFAULT_DICT 0
#define LV_IME_PINYIN_CAND_TEXT_NUM 6
#define LV_IME_PINYIN_USE_K9_MODE 1
#if LV_IME_PINYIN_USE_K9_MODE
#define LV_IME_PINYIN_K9_CAND_TEXT_NUM 3
#endif
#endif

/*Aktifkan file explorer (memerlukan lv_table)*/
#define LV_USE_FILE_EXPLORER 0
#if LV_USE_FILE_EXPLORER
#define LV_FILE_EXPLORER_PATH_MAX_LEN 128
#define LV_FILE_EXPLORER_QUICK_ACCESS 1
#endif

/*====================
 * DEVICES
 *====================*/

/*Gunakan SDL untuk membuka window pada PC dan menangani mouse/keyboard*/
// #define LV_USE_SDL 1
#if LV_USE_SDL
// #define LV_SDL_INCLUDE_PATH <SDL2/SDL.h>
#define LV_SDL_RENDER_MODE LV_DISPLAY_RENDER_MODE_DIRECT
#define LV_SDL_BUF_COUNT 1
#define LV_SDL_ACCELERATED 0
#define LV_SDL_FULLSCREEN 0
#define LV_SDL_DIRECT_EXIT 1
#define LV_SDL_MOUSEWHEEL_MODE LV_SDL_MOUSEWHEEL_MODE_ENCODER
#endif

/*Gunakan X11 pada Linux desktop*/
#define LV_USE_X11 0
#if LV_USE_X11
#define LV_X11_DIRECT_EXIT 1
#define LV_X11_DOUBLE_BUFFER 1
#define LV_X11_RENDER_MODE_PARTIAL 1
#define LV_X11_RENDER_MODE_DIRECT 0
#define LV_X11_RENDER_MODE_FULL 0
#endif

/*Gunakan Wayland pada Linux/BSD*/
#define LV_USE_WAYLAND 0
#if LV_USE_WAYLAND
#define LV_WAYLAND_WINDOW_DECORATIONS 0
#define LV_WAYLAND_WL_SHELL 0
#endif

/*Driver untuk /dev/fb*/
#define LV_USE_LINUX_FBDEV 0
#if LV_USE_LINUX_FBDEV
#define LV_LINUX_FBDEV_BSD 0
#define LV_LINUX_FBDEV_RENDER_MODE LV_DISPLAY_RENDER_MODE_PARTIAL
#define LV_LINUX_FBDEV_BUFFER_COUNT 0
#define LV_LINUX_FBDEV_BUFFER_SIZE 60
#endif

/*Nuttx (untuk touchscreen)*/
#define LV_USE_NUTTX 0
#if LV_USE_NUTTX
#define LV_USE_NUTTX_LIBUV 0
#define LV_USE_NUTTX_CUSTOM_INIT 0
#define LV_USE_NUTTX_LCD 0
#if LV_USE_NUTTX_LCD
#define LV_NUTTX_LCD_BUFFER_COUNT 0
#define LV_NUTTX_LCD_BUFFER_SIZE 60
#endif
#define LV_USE_NUTTX_TOUCHSCREEN 0
#endif

/*Driver untuk /dev/dri/card*/
#define LV_USE_LINUX_DRM 0
#if LV_USE_LINUX_DRM
#define LV_LINUX_DRM_CARD ""
#endif

/*Interface untuk TFT_eSPI*/
#define LV_USE_TFT_ESPI 0

/*Driver untuk evdev*/
#define LV_USE_EVDEV 0
#if LV_USE_EVDEV
#define LV_EVDEV_DEVICE ""
#endif

/*Driver untuk libinput*/
#define LV_USE_LIBINPUT 0
#if LV_USE_LIBINPUT
#define LV_LIBINPUT_BSD 0
#define LV_LIBINPUT_XKB 0
#if LV_LIBINPUT_XKB
#define LV_LIBINPUT_XKB_KEY_MAP {.rules = NULL, .model = "pc101", .layout = "us", .variant = NULL, .options = NULL}
#endif
#endif

/*Driver untuk LCD via SPI/parallel*/
#define LV_USE_ST7735 0
#define LV_USE_ST7789 0
#define LV_USE_ST7796 0
#define LV_USE_ILI9341 0
#define LV_USE_GENERIC_MIPI (LV_USE_ST7735 | LV_USE_ST7789 | LV_USE_ST7796 | LV_USE_ILI9341)

/*Driver untuk Renesas GLCD*/
#define LV_USE_RENESAS_GLCDC 0

/*Backend Windows LVGL*/
#define LV_USE_WINDOWS 0

/*Gunakan OpenGL untuk PC*/
#define LV_USE_OPENGLES 0
#if LV_USE_OPENGLES
#define LV_USE_OPENGLES_DEBUG 1
#endif

/*Driver untuk QNX*/
#define LV_USE_QNX 0
#if LV_USE_QNX
#define LV_QNX_BUF_COUNT 1
#endif

/*Gui Guider simulator*/
#define LV_USE_GUIDER_SIMULATOR 1
#if LV_USE_GUIDER_SIMULATOR
#define LV_GUIDER_SIMULATOR_WINDOW_ZOOM 1
#define LV_USE_FREEMASTER 0
#endif

#include "lv_conf_ext.h"

#endif
