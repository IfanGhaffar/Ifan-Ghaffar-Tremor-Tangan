/*
* Copyright 2024 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/


/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
extern void on_btn_1_clicked(void);

/**********************
 *  STATIC VARIABLES
 **********************/
extern lv_ui guider_ui;

/**
 * Custom event handler untuk btn_1 (reset timer)
 */
static void telegram_btn_1_custom_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
        on_btn_1_clicked();  // Panggil timer reset
    }
}

/**
 * Create a demo application
 */

void custom_init(lv_ui *ui)
{
    /* Add custom event handlers here */
    if (ui && ui->telegram_btn_1) {
        lv_obj_add_event_cb(ui->telegram_btn_1, telegram_btn_1_custom_handler, LV_EVENT_CLICKED, NULL);
    }
}


