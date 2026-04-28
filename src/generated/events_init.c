/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

// Forward declaration for C-callable reset function implemented in main.cpp
extern void timer_reset_timer(void);
// Forward declaration for C-callable send function implemented in main.cpp
extern void timer_send_data(void);

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


static void screen_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_active());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_active());
            ui_load_scr_animation(&guider_ui, &guider_ui.menu, guider_ui.menu_del, &guider_ui.screen_1_del, setup_scr_menu, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, true, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

void events_init_screen_1 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_1, screen_1_event_handler, LV_EVENT_ALL, ui);
}

static void menu_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_active());
        switch(dir) {
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_active());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_1, guider_ui.screen_1_del, &guider_ui.menu_del, setup_scr_screen_1, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void menu_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.timer, guider_ui.timer_del, &guider_ui.menu_del, setup_scr_timer, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void menu_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.realtime, guider_ui.realtime_del, &guider_ui.menu_del, setup_scr_realtime, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_menu (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->menu, menu_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_btn_2, menu_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_btn_1, menu_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void realtime_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_active());
        switch(dir) {
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_active());
            ui_load_scr_animation(&guider_ui, &guider_ui.menu, guider_ui.menu_del, &guider_ui.realtime_del, setup_scr_menu, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, true, true);
            break;
        }
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_active());
            ui_load_scr_animation(&guider_ui, &guider_ui.info, guider_ui.info_del, &guider_ui.realtime_del, setup_scr_info, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, true, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void realtime_label_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_LONG_PRESSED:
    {
        lv_obj_remove_flag(guider_ui.realtime_calibrate, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void realtime_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_add_flag(guider_ui.realtime_calibrate, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void realtime_calibrate_done_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_add_flag(guider_ui.realtime_calibrate_done, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(guider_ui.realtime_calibrate_start, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void realtime_btn_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_add_flag(guider_ui.realtime_calibrate_start, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(guider_ui.realtime_calibrate_done, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

void events_init_realtime (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->realtime, realtime_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->realtime_label_2, realtime_label_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->realtime_btn_2, realtime_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->realtime_calibrate_done, realtime_calibrate_done_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->realtime_btn_3, realtime_btn_3_event_handler, LV_EVENT_ALL, ui);
}

static void timer_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_active());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_active());
            ui_load_scr_animation(&guider_ui, &guider_ui.info, guider_ui.info_del, &guider_ui.timer_del, setup_scr_info, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, true, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_active());
            ui_load_scr_animation(&guider_ui, &guider_ui.menu, guider_ui.menu_del, &guider_ui.timer_del, setup_scr_menu, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, true, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void timer_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        // Simple software debounce: ignore clicks that occur within
        // 300 ms of the previous accepted click. This mitigates
        // noisy touch inputs or multiple LVGL click events for
        // a single physical touch.
        static uint32_t last_click_ms = 0;
        uint32_t now = lv_tick_get();
        if (lv_tick_elaps(last_click_ms) < 300) {
            break; // ignore as bounce
        }
        last_click_ms = now;

        // Call C-accessible wrapper to reset timer
        timer_reset_timer();
        break;
    }
    default:
        break;
    }
}

void events_init_timer (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->timer, timer_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->timer_btn_1, timer_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void info_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_active());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_active());
            ui_load_scr_animation(&guider_ui, &guider_ui.menu, guider_ui.menu_del, &guider_ui.info_del, setup_scr_menu, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, true, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_active());
            ui_load_scr_animation(&guider_ui, &guider_ui.menu, guider_ui.menu_del, &guider_ui.info_del, setup_scr_menu, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, true, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void info_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_remove_flag(guider_ui.info_bar_info, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void info_bar_info_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_add_flag(guider_ui.info_bar_info, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void info_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_add_flag(guider_ui.info_bar_info, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

void events_init_info (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->info, info_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->info_btn_1, info_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->info_bar_info, info_bar_info_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->info_btn_2, info_btn_2_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
