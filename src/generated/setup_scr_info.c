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



void setup_scr_info(lv_ui *ui)
{
    //Write codes info
    ui->info = lv_obj_create(NULL);
    lv_obj_set_size(ui->info, 320, 170);
    lv_obj_set_scrollbar_mode(ui->info, LV_SCROLLBAR_MODE_OFF);

    //Write style for info, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->info, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->info, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->info, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes info_line_1
    ui->info_line_1 = lv_line_create(ui->info);
    lv_obj_set_pos(ui->info_line_1, 12, 37);
    lv_obj_set_size(ui->info_line_1, 294, 3);
    static lv_point_precise_t info_line_1[] = {{300, 0},{0, 0}};
    lv_line_set_points(ui->info_line_1, info_line_1, 2);

    //Write style for info_line_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->info_line_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->info_line_1, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->info_line_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->info_line_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes info_label_1
    ui->info_label_1 = lv_label_create(ui->info);
    lv_obj_set_pos(ui->info_label_1, 12, 11);
    lv_obj_set_size(ui->info_label_1, 126, 20);
    lv_label_set_text(ui->info_label_1, "Information");
    lv_label_set_long_mode(ui->info_label_1, LV_LABEL_LONG_WRAP);

    //Write style for info_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->info_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->info_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->info_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->info_label_1, &lv_font_MonaSans_Variable_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->info_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->info_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->info_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->info_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->info_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->info_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->info_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->info_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->info_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->info_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes info_btn_1
    ui->info_btn_1 = lv_button_create(ui->info);
    lv_obj_set_pos(ui->info_btn_1, 95, 60);
    lv_obj_set_size(ui->info_btn_1, 130, 75);
    ui->info_btn_1_label = lv_label_create(ui->info_btn_1);
    lv_label_set_text(ui->info_btn_1_label, "CLICK");
    lv_label_set_long_mode(ui->info_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->info_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->info_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->info_btn_1_label, LV_PCT(100));

    //Write style for info_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->info_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->info_btn_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->info_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->info_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->info_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->info_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->info_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->info_btn_1, &lv_font_montserratMedium_22, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->info_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->info_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes info_bar_info
    ui->info_bar_info = lv_obj_create(ui->info);
    lv_obj_set_pos(ui->info_bar_info, 76, 31);
    lv_obj_set_size(ui->info_bar_info, 172, 127);
    lv_obj_set_scrollbar_mode(ui->info_bar_info, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->info_bar_info, LV_OBJ_FLAG_HIDDEN);

    //Write style for info_bar_info, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->info_bar_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->info_bar_info, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->info_bar_info, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->info_bar_info, lv_color_hex(0x1B1C1F), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->info_bar_info, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->info_bar_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->info_bar_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->info_bar_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->info_bar_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->info_bar_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes info_qrcode_1
    ui->info_qrcode_1 = lv_qrcode_create(ui->info_bar_info);
    lv_obj_set_pos(ui->info_qrcode_1, 14, 12);
    lv_obj_set_size(ui->info_qrcode_1, 105, 105);
    lv_qrcode_set_size(ui->info_qrcode_1, 105);
    lv_qrcode_set_dark_color(ui->info_qrcode_1, lv_color_hex(0x2C3224));
    lv_qrcode_set_light_color(ui->info_qrcode_1, lv_color_hex(0xffffff));
    const char * info_qrcode_1_data = "www.linkedin.com/in/muhammad-ifan-ghaffar-a2515a193";
    lv_qrcode_update(ui->info_qrcode_1, info_qrcode_1_data, 51);

    //Write codes info_btn_2
    ui->info_btn_2 = lv_button_create(ui->info_bar_info);
    lv_obj_set_pos(ui->info_btn_2, 130, 8);
    lv_obj_set_size(ui->info_btn_2, 30, 25);
    ui->info_btn_2_label = lv_label_create(ui->info_btn_2);
    lv_label_set_text(ui->info_btn_2_label, "" LV_SYMBOL_CLOSE "");
    lv_label_set_long_mode(ui->info_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->info_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->info_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->info_btn_2_label, LV_PCT(100));

    //Write style for info_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->info_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->info_btn_2, lv_color_hex(0x818181), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->info_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->info_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->info_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->info_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->info_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->info_btn_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->info_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->info_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of info.


    //Update current screen layout.
    lv_obj_update_layout(ui->info);

    //Init events for screen.
    events_init_info(ui);
}
