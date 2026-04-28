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



void setup_scr_menu(lv_ui *ui)
{
    //Write codes menu
    ui->menu = lv_obj_create(NULL);
    lv_obj_set_size(ui->menu, 320, 170);
    lv_obj_set_scrollbar_mode(ui->menu, LV_SCROLLBAR_MODE_OFF);

    //Write style for menu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->menu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_img_20
    ui->menu_img_20 = lv_image_create(ui->menu);
    lv_obj_set_pos(ui->menu_img_20, 100, 95);
    lv_obj_set_size(ui->menu_img_20, 120, 60);
    lv_obj_add_flag(ui->menu_img_20, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->menu_img_20, &_Kotak2_RGB565A8_120x60);
    lv_image_set_pivot(ui->menu_img_20, 50,50);
    lv_image_set_rotation(ui->menu_img_20, 0);

    //Write style for menu_img_20, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->menu_img_20, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_recolor(ui->menu_img_20, lv_color_hex(0x1B1C1F), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->menu_img_20, 199, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_img_18
    ui->menu_img_18 = lv_image_create(ui->menu);
    lv_obj_set_pos(ui->menu_img_18, 100, 20);
    lv_obj_set_size(ui->menu_img_18, 120, 60);
    lv_obj_add_flag(ui->menu_img_18, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->menu_img_18, &_Kotak2_RGB565A8_120x60);
    lv_image_set_pivot(ui->menu_img_18, 50,50);
    lv_image_set_rotation(ui->menu_img_18, 0);

    //Write style for menu_img_18, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->menu_img_18, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_recolor(ui->menu_img_18, lv_color_hex(0x1B1C1F), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->menu_img_18, 199, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_btn_2
    ui->menu_btn_2 = lv_button_create(ui->menu);
    lv_obj_set_pos(ui->menu_btn_2, 110, 100);
    lv_obj_set_size(ui->menu_btn_2, 100, 50);
    ui->menu_btn_2_label = lv_label_create(ui->menu_btn_2);
    lv_label_set_text(ui->menu_btn_2_label, "Timer");
    lv_label_set_long_mode(ui->menu_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->menu_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->menu_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->menu_btn_2_label, LV_PCT(100));

    //Write style for menu_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->menu_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_btn_2, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->menu_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_btn_2, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_btn_1
    ui->menu_btn_1 = lv_button_create(ui->menu);
    lv_obj_set_pos(ui->menu_btn_1, 110, 25);
    lv_obj_set_size(ui->menu_btn_1, 100, 50);
    ui->menu_btn_1_label = lv_label_create(ui->menu_btn_1);
    lv_label_set_text(ui->menu_btn_1_label, "Real Time");
    lv_label_set_long_mode(ui->menu_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->menu_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->menu_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->menu_btn_1_label, LV_PCT(100));

    //Write style for menu_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->menu_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_btn_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->menu_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_btn_1, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of menu.


    //Update current screen layout.
    lv_obj_update_layout(ui->menu);

    //Init events for screen.
    events_init_menu(ui);
}
