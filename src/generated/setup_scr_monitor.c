/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_monitor(lv_ui *ui)
{
    //Write codes monitor
    ui->monitor = lv_obj_create(NULL);
    lv_obj_set_size(ui->monitor, 320, 170);
    lv_obj_set_scrollbar_mode(ui->monitor, LV_SCROLLBAR_MODE_OFF);

    //Write style for monitor, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->monitor, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->monitor, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->monitor, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_Gyroscope
    ui->monitor_Gyroscope = lv_obj_create(ui->monitor);
    lv_obj_set_pos(ui->monitor_Gyroscope, 12, 44);
    lv_obj_set_size(ui->monitor_Gyroscope, 165, 115);
    lv_obj_set_scrollbar_mode(ui->monitor_Gyroscope, LV_SCROLLBAR_MODE_OFF);

    //Write style for monitor_Gyroscope, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->monitor_Gyroscope, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->monitor_Gyroscope, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->monitor_Gyroscope, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->monitor_Gyroscope, lv_color_hex(0x1B1C1F), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->monitor_Gyroscope, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->monitor_Gyroscope, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->monitor_Gyroscope, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->monitor_Gyroscope, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->monitor_Gyroscope, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->monitor_Gyroscope, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_label_2
    ui->monitor_label_2 = lv_label_create(ui->monitor_Gyroscope);
    lv_obj_set_pos(ui->monitor_label_2, 38, 11);
    lv_obj_set_size(ui->monitor_label_2, 123, 20);
    lv_obj_add_flag(ui->monitor_label_2, LV_OBJ_FLAG_CLICKABLE);
    lv_label_set_text(ui->monitor_label_2, "Tremor Analysis");
    lv_label_set_long_mode(ui->monitor_label_2, LV_LABEL_LONG_WRAP);

    //Write style for monitor_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->monitor_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->monitor_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->monitor_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->monitor_label_2, &lv_font_MonaSans_Variable_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->monitor_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->monitor_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->monitor_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->monitor_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->monitor_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->monitor_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->monitor_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->monitor_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->monitor_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->monitor_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_img_8
    ui->monitor_img_8 = lv_image_create(ui->monitor_Gyroscope);
    lv_obj_set_pos(ui->monitor_img_8, 108, 56);
    lv_obj_set_size(ui->monitor_img_8, 40, 35);
    lv_obj_add_flag(ui->monitor_img_8, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->monitor_img_8, &_rms_RGB565A8_40x35);
    lv_image_set_pivot(ui->monitor_img_8, 50,50);
    lv_image_set_rotation(ui->monitor_img_8, 0);

    //Write style for monitor_img_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->monitor_img_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_recolor(ui->monitor_img_8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->monitor_img_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_label_4
    ui->monitor_label_4 = lv_label_create(ui->monitor_Gyroscope);
    lv_obj_set_pos(ui->monitor_label_4, 5, 46);
    lv_obj_set_size(ui->monitor_label_4, 83, 15);
    lv_label_set_text(ui->monitor_label_4, "Peak Freq (Hz)");
    lv_label_set_long_mode(ui->monitor_label_4, LV_LABEL_LONG_WRAP);

    //Write style for monitor_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->monitor_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->monitor_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->monitor_label_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->monitor_label_4, &lv_font_MonaSans_Variable_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->monitor_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->monitor_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->monitor_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->monitor_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->monitor_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->monitor_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->monitor_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->monitor_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->monitor_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->monitor_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_label_6
    ui->monitor_label_6 = lv_label_create(ui->monitor_Gyroscope);
    lv_obj_set_pos(ui->monitor_label_6, 99, 46);
    lv_obj_set_size(ui->monitor_label_6, 61, 15);
    lv_label_set_text(ui->monitor_label_6, "RMS Amp");
    lv_label_set_long_mode(ui->monitor_label_6, LV_LABEL_LONG_WRAP);

    //Write style for monitor_label_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->monitor_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->monitor_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->monitor_label_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->monitor_label_6, &lv_font_MonaSans_Variable_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->monitor_label_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->monitor_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->monitor_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->monitor_label_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->monitor_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->monitor_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->monitor_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->monitor_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->monitor_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->monitor_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_label_5
    ui->monitor_label_5 = lv_label_create(ui->monitor_Gyroscope);
    lv_obj_set_pos(ui->monitor_label_5, 96, 89);
    lv_obj_set_size(ui->monitor_label_5, 64, 20);
    lv_label_set_text(ui->monitor_label_5, "0.0182g");
    lv_label_set_long_mode(ui->monitor_label_5, LV_LABEL_LONG_WRAP);

    //Write style for monitor_label_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->monitor_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->monitor_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->monitor_label_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->monitor_label_5, &lv_font_MonaSans_Variable_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->monitor_label_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->monitor_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->monitor_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->monitor_label_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->monitor_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->monitor_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->monitor_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->monitor_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->monitor_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->monitor_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_label_3
    ui->monitor_label_3 = lv_label_create(ui->monitor_Gyroscope);
    lv_obj_set_pos(ui->monitor_label_3, 11, 89);
    lv_obj_set_size(ui->monitor_label_3, 74, 20);
    lv_label_set_text(ui->monitor_label_3, "0.00 Hz");
    lv_label_set_long_mode(ui->monitor_label_3, LV_LABEL_LONG_WRAP);

    //Write style for monitor_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->monitor_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->monitor_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->monitor_label_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->monitor_label_3, &lv_font_MonaSans_Variable_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->monitor_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->monitor_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->monitor_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->monitor_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->monitor_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->monitor_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->monitor_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->monitor_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->monitor_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->monitor_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_img_6
    ui->monitor_img_6 = lv_image_create(ui->monitor_Gyroscope);
    lv_obj_set_pos(ui->monitor_img_6, 6, 5);
    lv_obj_set_size(ui->monitor_img_6, 30, 30);
    lv_obj_add_flag(ui->monitor_img_6, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->monitor_img_6, &_Gyro_RGB565A8_30x30);
    lv_image_set_pivot(ui->monitor_img_6, 50,50);
    lv_image_set_rotation(ui->monitor_img_6, 0);

    //Write style for monitor_img_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->monitor_img_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_recolor(ui->monitor_img_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->monitor_img_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_img_7
    ui->monitor_img_7 = lv_image_create(ui->monitor_Gyroscope);
    lv_obj_set_pos(ui->monitor_img_7, 33, 64);
    lv_obj_set_size(ui->monitor_img_7, 21, 18);
    lv_obj_add_flag(ui->monitor_img_7, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->monitor_img_7, &_peak_RGB565A8_21x18);
    lv_image_set_pivot(ui->monitor_img_7, 50,50);
    lv_image_set_rotation(ui->monitor_img_7, 0);

    //Write style for monitor_img_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->monitor_img_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_recolor(ui->monitor_img_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->monitor_img_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_IR_sensor
    ui->monitor_IR_sensor = lv_obj_create(ui->monitor);
    lv_obj_set_pos(ui->monitor_IR_sensor, 180, 44);
    lv_obj_set_size(ui->monitor_IR_sensor, 124, 44);
    lv_obj_set_scrollbar_mode(ui->monitor_IR_sensor, LV_SCROLLBAR_MODE_OFF);

    //Write style for monitor_IR_sensor, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->monitor_IR_sensor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->monitor_IR_sensor, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->monitor_IR_sensor, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->monitor_IR_sensor, lv_color_hex(0x1B1C1F), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->monitor_IR_sensor, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->monitor_IR_sensor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->monitor_IR_sensor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->monitor_IR_sensor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->monitor_IR_sensor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->monitor_IR_sensor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_label_8
    ui->monitor_label_8 = lv_label_create(ui->monitor_IR_sensor);
    lv_obj_set_pos(ui->monitor_label_8, 60, 27);
    lv_obj_set_size(ui->monitor_label_8, 45, 15);
    lv_label_set_text(ui->monitor_label_8, "Condition");
    lv_label_set_long_mode(ui->monitor_label_8, LV_LABEL_LONG_WRAP);

    //Write style for monitor_label_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->monitor_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->monitor_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->monitor_label_8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->monitor_label_8, &lv_font_MonaSans_Variable_9, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->monitor_label_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->monitor_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->monitor_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->monitor_label_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->monitor_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->monitor_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->monitor_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->monitor_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->monitor_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->monitor_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_label_7
    ui->monitor_label_7 = lv_label_create(ui->monitor_IR_sensor);
    lv_obj_set_pos(ui->monitor_label_7, 51, 9);
    lv_obj_set_size(ui->monitor_label_7, 65, 20);
    lv_label_set_text(ui->monitor_label_7, "Good");
    lv_label_set_long_mode(ui->monitor_label_7, LV_LABEL_LONG_WRAP);

    //Write style for monitor_label_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->monitor_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->monitor_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->monitor_label_7, lv_color_hex(0x00ff39), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->monitor_label_7, &lv_font_MonaSans_Variable_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->monitor_label_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->monitor_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->monitor_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->monitor_label_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->monitor_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->monitor_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->monitor_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->monitor_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->monitor_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->monitor_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_img_9
    ui->monitor_img_9 = lv_image_create(ui->monitor_IR_sensor);
    lv_obj_set_pos(ui->monitor_img_9, 10, 8);
    lv_obj_set_size(ui->monitor_img_9, 41, 29);
    lv_obj_add_flag(ui->monitor_img_9, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->monitor_img_9, &_tremor_RGB565A8_41x29);
    lv_image_set_pivot(ui->monitor_img_9, 50,50);
    lv_image_set_rotation(ui->monitor_img_9, 0);

    //Write style for monitor_img_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->monitor_img_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_recolor(ui->monitor_img_9, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->monitor_img_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_information
    ui->monitor_information = lv_obj_create(ui->monitor);
    lv_obj_set_pos(ui->monitor_information, 180, 92);
    lv_obj_set_size(ui->monitor_information, 124, 67);
    lv_obj_set_scrollbar_mode(ui->monitor_information, LV_SCROLLBAR_MODE_OFF);

    //Write style for monitor_information, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->monitor_information, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->monitor_information, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->monitor_information, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->monitor_information, lv_color_hex(0x1B1C1F), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->monitor_information, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->monitor_information, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->monitor_information, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->monitor_information, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->monitor_information, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->monitor_information, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_label_11
    ui->monitor_label_11 = lv_label_create(ui->monitor_information);
    lv_obj_set_pos(ui->monitor_label_11, 8, 32);
    lv_obj_set_size(ui->monitor_label_11, 145, 15);
    lv_label_set_text(ui->monitor_label_11, "Wifi     :  Connected to UNY");
    lv_label_set_long_mode(ui->monitor_label_11, LV_LABEL_LONG_WRAP);

    //Write style for monitor_label_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->monitor_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->monitor_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->monitor_label_11, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->monitor_label_11, &lv_font_MonaSans_Variable_9, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->monitor_label_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->monitor_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->monitor_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->monitor_label_11, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->monitor_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->monitor_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->monitor_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->monitor_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->monitor_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->monitor_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_label_12
    ui->monitor_label_12 = lv_label_create(ui->monitor_information);
    lv_obj_set_pos(ui->monitor_label_12, 8, 49);
    lv_obj_set_size(ui->monitor_label_12, 145, 15);
    lv_label_set_text(ui->monitor_label_12, "Software Version  :  01.2025");
    lv_label_set_long_mode(ui->monitor_label_12, LV_LABEL_LONG_WRAP);

    //Write style for monitor_label_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->monitor_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->monitor_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->monitor_label_12, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->monitor_label_12, &lv_font_MonaSans_Variable_9, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->monitor_label_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->monitor_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->monitor_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->monitor_label_12, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->monitor_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->monitor_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->monitor_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->monitor_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->monitor_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->monitor_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_label_10
    ui->monitor_label_10 = lv_label_create(ui->monitor_information);
    lv_obj_set_pos(ui->monitor_label_10, 2, 6);
    lv_obj_set_size(ui->monitor_label_10, 98, 20);
    lv_label_set_text(ui->monitor_label_10, "Information");
    lv_label_set_long_mode(ui->monitor_label_10, LV_LABEL_LONG_WRAP);

    //Write style for monitor_label_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->monitor_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->monitor_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->monitor_label_10, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->monitor_label_10, &lv_font_MonaSans_Variable_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->monitor_label_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->monitor_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->monitor_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->monitor_label_10, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->monitor_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->monitor_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->monitor_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->monitor_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->monitor_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->monitor_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_calibrate
    ui->monitor_calibrate = lv_obj_create(ui->monitor);
    lv_obj_set_pos(ui->monitor_calibrate, 85, 57);
    lv_obj_set_size(ui->monitor_calibrate, 161, 83);
    lv_obj_set_scrollbar_mode(ui->monitor_calibrate, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->monitor_calibrate, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->monitor_calibrate, LV_OBJ_FLAG_HIDDEN);

    //Write style for monitor_calibrate, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->monitor_calibrate, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->monitor_calibrate, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->monitor_calibrate, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->monitor_calibrate, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->monitor_calibrate, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->monitor_calibrate, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->monitor_calibrate, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->monitor_calibrate, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->monitor_calibrate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->monitor_calibrate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->monitor_calibrate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->monitor_calibrate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->monitor_calibrate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_header_calibrate
    ui->monitor_header_calibrate = lv_obj_create(ui->monitor_calibrate);
    lv_obj_set_pos(ui->monitor_header_calibrate, 0, -1);
    lv_obj_set_size(ui->monitor_header_calibrate, 159, 27);
    lv_obj_set_scrollbar_mode(ui->monitor_header_calibrate, LV_SCROLLBAR_MODE_OFF);

    //Write style for monitor_header_calibrate, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->monitor_header_calibrate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->monitor_header_calibrate, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->monitor_header_calibrate, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->monitor_header_calibrate, lv_color_hex(0xe4e4e4), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->monitor_header_calibrate, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->monitor_header_calibrate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->monitor_header_calibrate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->monitor_header_calibrate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->monitor_header_calibrate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->monitor_header_calibrate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_label_19
    ui->monitor_label_19 = lv_label_create(ui->monitor_header_calibrate);
    lv_obj_set_pos(ui->monitor_label_19, 47, 82);
    lv_obj_set_size(ui->monitor_label_19, 102, 13);
    lv_label_set_text(ui->monitor_label_19, "Calibrate");
    lv_label_set_long_mode(ui->monitor_label_19, LV_LABEL_LONG_WRAP);

    //Write style for monitor_label_19, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->monitor_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->monitor_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->monitor_label_19, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->monitor_label_19, &lv_font_MonaSans_Variable_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->monitor_label_19, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->monitor_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->monitor_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->monitor_label_19, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->monitor_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->monitor_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->monitor_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->monitor_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->monitor_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->monitor_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_btn_2
    ui->monitor_btn_2 = lv_button_create(ui->monitor_header_calibrate);
    lv_obj_set_pos(ui->monitor_btn_2, 137, 5);
    lv_obj_set_size(ui->monitor_btn_2, 16, 16);
    ui->monitor_btn_2_label = lv_label_create(ui->monitor_btn_2);
    lv_label_set_text(ui->monitor_btn_2_label, "" LV_SYMBOL_CLOSE "");
    lv_label_set_long_mode(ui->monitor_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->monitor_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->monitor_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->monitor_btn_2_label, LV_PCT(100));

    //Write style for monitor_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->monitor_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->monitor_btn_2, lv_color_hex(0x818181), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->monitor_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->monitor_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->monitor_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->monitor_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->monitor_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->monitor_btn_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->monitor_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->monitor_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_calibrate_done
    ui->monitor_calibrate_done = lv_obj_create(ui->monitor_calibrate);
    lv_obj_set_pos(ui->monitor_calibrate_done, 3, 29);
    lv_obj_set_size(ui->monitor_calibrate_done, 152, 52);
    lv_obj_set_scrollbar_mode(ui->monitor_calibrate_done, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->monitor_calibrate_done, LV_OBJ_FLAG_HIDDEN);

    //Write style for monitor_calibrate_done, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->monitor_calibrate_done, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->monitor_calibrate_done, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->monitor_calibrate_done, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->monitor_calibrate_done, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->monitor_calibrate_done, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->monitor_calibrate_done, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->monitor_calibrate_done, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->monitor_calibrate_done, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->monitor_calibrate_done, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->monitor_calibrate_done, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_label_21
    ui->monitor_label_21 = lv_label_create(ui->monitor_calibrate_done);
    lv_obj_set_pos(ui->monitor_label_21, 52, 16);
    lv_obj_set_size(ui->monitor_label_21, 83, 16);
    lv_label_set_text(ui->monitor_label_21, "Calibrate Done");
    lv_label_set_long_mode(ui->monitor_label_21, LV_LABEL_LONG_WRAP);

    //Write style for monitor_label_21, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->monitor_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->monitor_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->monitor_label_21, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->monitor_label_21, &lv_font_MonaSans_Variable_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->monitor_label_21, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->monitor_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->monitor_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->monitor_label_21, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->monitor_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->monitor_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->monitor_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->monitor_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->monitor_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->monitor_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_img_14
    ui->monitor_img_14 = lv_image_create(ui->monitor_calibrate_done);
    lv_obj_set_pos(ui->monitor_img_14, 13, 6);
    lv_obj_set_size(ui->monitor_img_14, 35, 35);
    lv_obj_add_flag(ui->monitor_img_14, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->monitor_img_14, &_DoneDL_RGB565A8_35x35);
    lv_image_set_pivot(ui->monitor_img_14, 50,50);
    lv_image_set_rotation(ui->monitor_img_14, 0);

    //Write style for monitor_img_14, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->monitor_img_14, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_recolor(ui->monitor_img_14, lv_color_hex(0x2200ff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->monitor_img_14, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_calibrate_start
    ui->monitor_calibrate_start = lv_obj_create(ui->monitor_calibrate);
    lv_obj_set_pos(ui->monitor_calibrate_start, 4, 29);
    lv_obj_set_size(ui->monitor_calibrate_start, 152, 52);
    lv_obj_set_scrollbar_mode(ui->monitor_calibrate_start, LV_SCROLLBAR_MODE_OFF);

    //Write style for monitor_calibrate_start, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->monitor_calibrate_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->monitor_calibrate_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->monitor_calibrate_start, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->monitor_calibrate_start, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->monitor_calibrate_start, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->monitor_calibrate_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->monitor_calibrate_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->monitor_calibrate_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->monitor_calibrate_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->monitor_calibrate_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_label_20
    ui->monitor_label_20 = lv_label_create(ui->monitor_calibrate_start);
    lv_obj_set_pos(ui->monitor_label_20, -6, 6);
    lv_obj_set_size(ui->monitor_label_20, 164, 16);
    lv_label_set_text(ui->monitor_label_20, "Ensure Table is Completely Flat");
    lv_label_set_long_mode(ui->monitor_label_20, LV_LABEL_LONG_WRAP);

    //Write style for monitor_label_20, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->monitor_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->monitor_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->monitor_label_20, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->monitor_label_20, &lv_font_MonaSans_Variable_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->monitor_label_20, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->monitor_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->monitor_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->monitor_label_20, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->monitor_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->monitor_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->monitor_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->monitor_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->monitor_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->monitor_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_btn_3
    ui->monitor_btn_3 = lv_button_create(ui->monitor_calibrate_start);
    lv_obj_set_pos(ui->monitor_btn_3, 36, 24);
    lv_obj_set_size(ui->monitor_btn_3, 80, 20);
    lv_obj_add_flag(ui->monitor_btn_3, LV_OBJ_FLAG_CLICKABLE);
    ui->monitor_btn_3_label = lv_label_create(ui->monitor_btn_3);
    lv_label_set_text(ui->monitor_btn_3_label, "Calibrate");
    lv_label_set_long_mode(ui->monitor_btn_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->monitor_btn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->monitor_btn_3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->monitor_btn_3_label, LV_PCT(100));

    //Write style for monitor_btn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->monitor_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->monitor_btn_3, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->monitor_btn_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->monitor_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->monitor_btn_3, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->monitor_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->monitor_btn_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->monitor_btn_3, &lv_font_MonaSans_Variable_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->monitor_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->monitor_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_line_1
    ui->monitor_line_1 = lv_line_create(ui->monitor);
    lv_obj_set_pos(ui->monitor_line_1, 12, 37);
    lv_obj_set_size(ui->monitor_line_1, 294, 3);
    static lv_point_precise_t monitor_line_1[] = {{300, 0},{0, 0}};
    lv_line_set_points(ui->monitor_line_1, monitor_line_1, 2);

    //Write style for monitor_line_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->monitor_line_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->monitor_line_1, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->monitor_line_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->monitor_line_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes monitor_label_1
    ui->monitor_label_1 = lv_label_create(ui->monitor);
    lv_obj_set_pos(ui->monitor_label_1, 11, 11);
    lv_obj_set_size(ui->monitor_label_1, 189, 20);
    lv_label_set_text(ui->monitor_label_1, "Sensors & Information");
    lv_label_set_long_mode(ui->monitor_label_1, LV_LABEL_LONG_WRAP);

    //Write style for monitor_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->monitor_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->monitor_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->monitor_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->monitor_label_1, &lv_font_MonaSans_Variable_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->monitor_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->monitor_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->monitor_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->monitor_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->monitor_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->monitor_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->monitor_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->monitor_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->monitor_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->monitor_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of monitor.


    //Update current screen layout.
    lv_obj_update_layout(ui->monitor);

    //Init events for screen.
    events_init_monitor(ui);
}
