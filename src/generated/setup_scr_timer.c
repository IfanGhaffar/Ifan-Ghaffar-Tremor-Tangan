/*
* Copyright 2026 NXP
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



void setup_scr_timer(lv_ui *ui)
{
    //Write codes timer
    ui->timer = lv_obj_create(NULL);
    lv_obj_set_size(ui->timer, 320, 170);
    lv_obj_set_scrollbar_mode(ui->timer, LV_SCROLLBAR_MODE_OFF);

    //Write style for timer, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->timer, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->timer, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->timer, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes timer_cont_1
    ui->timer_cont_1 = lv_obj_create(ui->timer);
    lv_obj_set_pos(ui->timer_cont_1, 183, 44);
    lv_obj_set_size(ui->timer_cont_1, 123, 43);
    lv_obj_set_scrollbar_mode(ui->timer_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for timer_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->timer_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->timer_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->timer_cont_1, lv_color_hex(0x1B1C1F), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->timer_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->timer_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->timer_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->timer_cont_1, lv_color_hex(0x1B1C1F), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->timer_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->timer_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->timer_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->timer_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->timer_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->timer_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes timer_label_7
    ui->timer_label_7 = lv_label_create(ui->timer_cont_1);
    lv_obj_set_pos(ui->timer_label_7, 0, 3);
    lv_obj_set_size(ui->timer_label_7, 117, 15);
    lv_label_set_text(ui->timer_label_7, "Remaining Time");
    lv_label_set_long_mode(ui->timer_label_7, LV_LABEL_LONG_WRAP);

    //Write style for timer_label_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->timer_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->timer_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->timer_label_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->timer_label_7, &lv_font_MonaSans_Variable_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->timer_label_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->timer_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->timer_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->timer_label_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->timer_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->timer_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->timer_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->timer_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->timer_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->timer_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes timer_label_8
    ui->timer_label_8 = lv_label_create(ui->timer_cont_1);
    lv_obj_set_pos(ui->timer_label_8, 20, 23);
    lv_obj_set_size(ui->timer_label_8, 81, 20);
    lv_label_set_text(ui->timer_label_8, "00:00:00");
    lv_label_set_long_mode(ui->timer_label_8, LV_LABEL_LONG_WRAP);

    //Write style for timer_label_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->timer_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->timer_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->timer_label_8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->timer_label_8, &lv_font_MonaSans_Variable_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->timer_label_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->timer_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->timer_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->timer_label_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->timer_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->timer_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->timer_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->timer_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->timer_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->timer_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes timer_line_1
    ui->timer_line_1 = lv_line_create(ui->timer);
    lv_obj_set_pos(ui->timer_line_1, 12, 37);
    lv_obj_set_size(ui->timer_line_1, 294, 3);
    static lv_point_precise_t timer_line_1[] = {{300, 0},{0, 0}};
    lv_line_set_points(ui->timer_line_1, timer_line_1, 2);

    //Write style for timer_line_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->timer_line_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->timer_line_1, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->timer_line_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->timer_line_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes timer_label_1
    ui->timer_label_1 = lv_label_create(ui->timer);
    lv_obj_set_pos(ui->timer_label_1, 12, 11);
    lv_obj_set_size(ui->timer_label_1, 190, 20);
    lv_label_set_text(ui->timer_label_1, "Sensors & Information");
    lv_label_set_long_mode(ui->timer_label_1, LV_LABEL_LONG_WRAP);

    //Write style for timer_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->timer_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->timer_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->timer_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->timer_label_1, &lv_font_MonaSans_Variable_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->timer_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->timer_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->timer_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->timer_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->timer_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->timer_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->timer_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->timer_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->timer_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->timer_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes timer_btn_1
    ui->timer_btn_1 = lv_button_create(ui->timer);
    lv_obj_set_pos(ui->timer_btn_1, 183, 104);
    lv_obj_set_size(ui->timer_btn_1, 123, 50);
    ui->timer_btn_1_label = lv_label_create(ui->timer_btn_1);
    lv_label_set_text(ui->timer_btn_1_label, "RESET");
    lv_label_set_long_mode(ui->timer_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->timer_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->timer_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->timer_btn_1_label, LV_PCT(100));

    //Write style for timer_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->timer_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->timer_btn_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->timer_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->timer_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->timer_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->timer_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->timer_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->timer_btn_1, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->timer_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->timer_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes timer_status
    ui->timer_status = lv_label_create(ui->timer);
    lv_obj_set_pos(ui->timer_status, 207, 17);
    lv_obj_set_size(ui->timer_status, 100, 17);
    lv_label_set_text(ui->timer_status, "NORMAL");
    lv_label_set_long_mode(ui->timer_status, LV_LABEL_LONG_WRAP);

    //Write style for timer_status, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->timer_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->timer_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->timer_status, lv_color_hex(0x00ff71), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->timer_status, &lv_font_MonaSans_Variable_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->timer_status, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->timer_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->timer_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->timer_status, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->timer_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->timer_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->timer_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->timer_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->timer_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->timer_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes timer_cont_2
    ui->timer_cont_2 = lv_obj_create(ui->timer);
    lv_obj_set_pos(ui->timer_cont_2, 12, 44);
    lv_obj_set_size(ui->timer_cont_2, 165, 115);
    lv_obj_set_scrollbar_mode(ui->timer_cont_2, LV_SCROLLBAR_MODE_OFF);

    //Write style for timer_cont_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->timer_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->timer_cont_2, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->timer_cont_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->timer_cont_2, lv_color_hex(0x1B1C1F), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->timer_cont_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->timer_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->timer_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->timer_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->timer_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->timer_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes timer_label_13
    ui->timer_label_13 = lv_label_create(ui->timer_cont_2);
    lv_obj_set_pos(ui->timer_label_13, 38, 11);
    lv_obj_set_size(ui->timer_label_13, 123, 20);
    lv_obj_add_flag(ui->timer_label_13, LV_OBJ_FLAG_CLICKABLE);
    lv_label_set_text(ui->timer_label_13, "Tremor Analysis");
    lv_label_set_long_mode(ui->timer_label_13, LV_LABEL_LONG_WRAP);

    //Write style for timer_label_13, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->timer_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->timer_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->timer_label_13, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->timer_label_13, &lv_font_MonaSans_Variable_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->timer_label_13, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->timer_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->timer_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->timer_label_13, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->timer_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->timer_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->timer_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->timer_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->timer_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->timer_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes timer_img_3
    ui->timer_img_3 = lv_image_create(ui->timer_cont_2);
    lv_obj_set_pos(ui->timer_img_3, 108, 56);
    lv_obj_set_size(ui->timer_img_3, 40, 35);
    lv_obj_add_flag(ui->timer_img_3, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->timer_img_3, &_rms_RGB565A8_40x35);
    lv_image_set_pivot(ui->timer_img_3, 50,50);
    lv_image_set_rotation(ui->timer_img_3, 0);

    //Write style for timer_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->timer_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_recolor(ui->timer_img_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->timer_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes timer_label_12
    ui->timer_label_12 = lv_label_create(ui->timer_cont_2);
    lv_obj_set_pos(ui->timer_label_12, 5, 46);
    lv_obj_set_size(ui->timer_label_12, 83, 15);
    lv_label_set_text(ui->timer_label_12, "Peak Freq (Hz)");
    lv_label_set_long_mode(ui->timer_label_12, LV_LABEL_LONG_WRAP);

    //Write style for timer_label_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->timer_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->timer_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->timer_label_12, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->timer_label_12, &lv_font_MonaSans_Variable_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->timer_label_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->timer_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->timer_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->timer_label_12, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->timer_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->timer_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->timer_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->timer_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->timer_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->timer_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes timer_label_11
    ui->timer_label_11 = lv_label_create(ui->timer_cont_2);
    lv_obj_set_pos(ui->timer_label_11, 99, 46);
    lv_obj_set_size(ui->timer_label_11, 61, 15);
    lv_label_set_text(ui->timer_label_11, "RMS Amp");
    lv_label_set_long_mode(ui->timer_label_11, LV_LABEL_LONG_WRAP);

    //Write style for timer_label_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->timer_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->timer_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->timer_label_11, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->timer_label_11, &lv_font_MonaSans_Variable_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->timer_label_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->timer_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->timer_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->timer_label_11, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->timer_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->timer_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->timer_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->timer_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->timer_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->timer_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes timer_label_10
    ui->timer_label_10 = lv_label_create(ui->timer_cont_2);
    lv_obj_set_pos(ui->timer_label_10, 96, 89);
    lv_obj_set_size(ui->timer_label_10, 64, 20);
    lv_label_set_text(ui->timer_label_10, "0.0182g");
    lv_label_set_long_mode(ui->timer_label_10, LV_LABEL_LONG_WRAP);

    //Write style for timer_label_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->timer_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->timer_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->timer_label_10, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->timer_label_10, &lv_font_MonaSans_Variable_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->timer_label_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->timer_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->timer_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->timer_label_10, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->timer_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->timer_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->timer_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->timer_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->timer_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->timer_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes timer_label_9
    ui->timer_label_9 = lv_label_create(ui->timer_cont_2);
    lv_obj_set_pos(ui->timer_label_9, 11, 89);
    lv_obj_set_size(ui->timer_label_9, 74, 20);
    lv_label_set_text(ui->timer_label_9, "0.00 Hz");
    lv_label_set_long_mode(ui->timer_label_9, LV_LABEL_LONG_WRAP);

    //Write style for timer_label_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->timer_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->timer_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->timer_label_9, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->timer_label_9, &lv_font_MonaSans_Variable_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->timer_label_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->timer_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->timer_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->timer_label_9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->timer_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->timer_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->timer_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->timer_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->timer_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->timer_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes timer_img_2
    ui->timer_img_2 = lv_image_create(ui->timer_cont_2);
    lv_obj_set_pos(ui->timer_img_2, 6, 5);
    lv_obj_set_size(ui->timer_img_2, 30, 30);
    lv_obj_add_flag(ui->timer_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->timer_img_2, &_Gyro_RGB565A8_30x30);
    lv_image_set_pivot(ui->timer_img_2, 50,50);
    lv_image_set_rotation(ui->timer_img_2, 0);

    //Write style for timer_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->timer_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_recolor(ui->timer_img_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->timer_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes timer_img_1
    ui->timer_img_1 = lv_image_create(ui->timer_cont_2);
    lv_obj_set_pos(ui->timer_img_1, 33, 64);
    lv_obj_set_size(ui->timer_img_1, 21, 18);
    lv_obj_add_flag(ui->timer_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->timer_img_1, &_peak_RGB565A8_21x18);
    lv_image_set_pivot(ui->timer_img_1, 50,50);
    lv_image_set_rotation(ui->timer_img_1, 0);

    //Write style for timer_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->timer_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_recolor(ui->timer_img_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->timer_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of timer.


    //Update current screen layout.
    lv_obj_update_layout(ui->timer);

    //Init events for screen.
    events_init_timer(ui);
}
