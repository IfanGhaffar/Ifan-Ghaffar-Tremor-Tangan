/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"


typedef struct
{
  
	lv_obj_t *screen_1;
	bool screen_1_del;
	lv_obj_t *screen_1_img_1;
	lv_obj_t *menu;
	bool menu_del;
	lv_obj_t *menu_img_20;
	lv_obj_t *menu_img_18;
	lv_obj_t *menu_btn_2;
	lv_obj_t *menu_btn_2_label;
	lv_obj_t *menu_btn_1;
	lv_obj_t *menu_btn_1_label;
	lv_obj_t *realtime;
	bool realtime_del;
	lv_obj_t *realtime_Gyroscope;
	lv_obj_t *realtime_label_2;
	lv_obj_t *realtime_img_8;
	lv_obj_t *realtime_label_4;
	lv_obj_t *realtime_label_6;
	lv_obj_t *realtime_label_5;
	lv_obj_t *realtime_label_3;
	lv_obj_t *realtime_img_6;
	lv_obj_t *realtime_img_7;
	lv_obj_t *realtime_IR_sensor;
	lv_obj_t *realtime_label_8;
	lv_obj_t *realtime_label_7;
	lv_obj_t *realtime_img_9;
	lv_obj_t *realtime_information;
	lv_obj_t *realtime_label_11;
	lv_obj_t *realtime_label_12;
	lv_obj_t *realtime_label_10;
	lv_obj_t *realtime_calibrate;
	lv_obj_t *realtime_header_calibrate;
	lv_obj_t *realtime_label_19;
	lv_obj_t *realtime_btn_2;
	lv_obj_t *realtime_btn_2_label;
	lv_obj_t *realtime_calibrate_done;
	lv_obj_t *realtime_label_21;
	lv_obj_t *realtime_img_14;
	lv_obj_t *realtime_calibrate_start;
	lv_obj_t *realtime_label_20;
	lv_obj_t *realtime_btn_3;
	lv_obj_t *realtime_btn_3_label;
	lv_obj_t *realtime_line_1;
	lv_obj_t *realtime_label_1;
	lv_obj_t *timer;
	bool timer_del;
	lv_obj_t *timer_cont_1;
	lv_obj_t *timer_label_7;
	lv_obj_t *timer_label_8;
	lv_obj_t *timer_line_1;
	lv_obj_t *timer_label_1;
	lv_obj_t *timer_btn_1;
	lv_obj_t *timer_btn_1_label;
	lv_obj_t *timer_status;
	lv_obj_t *timer_cont_2;
	lv_obj_t *timer_label_13;
	lv_obj_t *timer_img_3;
	lv_obj_t *timer_label_12;
	lv_obj_t *timer_label_11;
	lv_obj_t *timer_label_10;
	lv_obj_t *timer_label_9;
	lv_obj_t *timer_img_2;
	lv_obj_t *timer_img_1;
	lv_obj_t *info;
	bool info_del;
	lv_obj_t *info_line_1;
	lv_obj_t *info_label_1;
	lv_obj_t *info_btn_1;
	lv_obj_t *info_btn_1_label;
	lv_obj_t *info_bar_info;
	lv_obj_t *info_qrcode_1;
	lv_obj_t *info_btn_2;
	lv_obj_t *info_btn_2_label;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_screen_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, uint32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                  uint32_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                  lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_completed_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_bottom_layer(void);

void setup_ui(lv_ui *ui);

void video_play(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_screen_1(lv_ui *ui);
void setup_scr_menu(lv_ui *ui);
void setup_scr_realtime(lv_ui *ui);
void setup_scr_timer(lv_ui *ui);
void setup_scr_info(lv_ui *ui);
LV_IMAGE_DECLARE(_logouny_RGB565A8_147x137);
LV_IMAGE_DECLARE(_Kotak2_RGB565A8_120x60);
LV_IMAGE_DECLARE(_rms_RGB565A8_40x35);
LV_IMAGE_DECLARE(_Gyro_RGB565A8_30x30);
LV_IMAGE_DECLARE(_peak_RGB565A8_21x18);
LV_IMAGE_DECLARE(_tremor_RGB565A8_41x29);
LV_IMAGE_DECLARE(_DoneDL_RGB565A8_35x35);

LV_FONT_DECLARE(lv_font_montserratMedium_14)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_MonaSans_Variable_16)
LV_FONT_DECLARE(lv_font_MonaSans_Variable_12)
LV_FONT_DECLARE(lv_font_MonaSans_Variable_9)
LV_FONT_DECLARE(lv_font_MonaSans_Variable_14)
LV_FONT_DECLARE(lv_font_MonaSans_Variable_10)
LV_FONT_DECLARE(lv_font_MonaSans_Variable_18)
LV_FONT_DECLARE(lv_font_montserratMedium_22)


#ifdef __cplusplus
}
#endif
#endif
