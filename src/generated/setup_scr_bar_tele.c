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



void setup_scr_bar_tele(lv_ui *ui)
{
    //Write codes bar_tele
    ui->bar_tele = lv_obj_create(NULL);
    lv_obj_set_size(ui->bar_tele, 320, 170);
    lv_obj_set_scrollbar_mode(ui->bar_tele, LV_SCROLLBAR_MODE_OFF);

    //Write style for bar_tele, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->bar_tele, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->bar_tele, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->bar_tele, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes bar_tele_line_1
    ui->bar_tele_line_1 = lv_line_create(ui->bar_tele);
    lv_obj_set_pos(ui->bar_tele_line_1, 12, 37);
    lv_obj_set_size(ui->bar_tele_line_1, 294, 3);
    static lv_point_precise_t bar_tele_line_1[] = {{300, 0},{0, 0}};
    lv_line_set_points(ui->bar_tele_line_1, bar_tele_line_1, 2);

    //Write style for bar_tele_line_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->bar_tele_line_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->bar_tele_line_1, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->bar_tele_line_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->bar_tele_line_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes bar_tele_label_1
    ui->bar_tele_label_1 = lv_label_create(ui->bar_tele);
    lv_obj_set_pos(ui->bar_tele_label_1, 12, 11);
    lv_obj_set_size(ui->bar_tele_label_1, 126, 20);
    lv_label_set_text(ui->bar_tele_label_1, "Scan Telegram");
    lv_label_set_long_mode(ui->bar_tele_label_1, LV_LABEL_LONG_WRAP);

    //Write style for bar_tele_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->bar_tele_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->bar_tele_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->bar_tele_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->bar_tele_label_1, &lv_font_MonaSans_Variable_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->bar_tele_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->bar_tele_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->bar_tele_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->bar_tele_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->bar_tele_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->bar_tele_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->bar_tele_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->bar_tele_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->bar_tele_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->bar_tele_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes bar_tele_qrcode_1
    ui->bar_tele_qrcode_1 = lv_qrcode_create(ui->bar_tele);
    lv_obj_set_pos(ui->bar_tele_qrcode_1, 100, 45);
    lv_obj_set_size(ui->bar_tele_qrcode_1, 120, 120);
    lv_qrcode_set_size(ui->bar_tele_qrcode_1, 120);
    lv_qrcode_set_dark_color(ui->bar_tele_qrcode_1, lv_color_hex(0x2C3224));
    lv_qrcode_set_light_color(ui->bar_tele_qrcode_1, lv_color_hex(0xffffff));
    const char * bar_tele_qrcode_1_data = "https://www.nxp.com/";
    lv_qrcode_update(ui->bar_tele_qrcode_1, bar_tele_qrcode_1_data, 20);

    //The custom code of bar_tele.


    //Update current screen layout.
    lv_obj_update_layout(ui->bar_tele);

    //Init events for screen.
    events_init_bar_tele(ui);
}
