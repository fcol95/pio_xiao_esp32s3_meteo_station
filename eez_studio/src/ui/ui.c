#if defined(EEZ_FOR_LVGL)
#include <eez/core/vars.h>
#endif

#include "ui.h"
#include "screens.h"
#include "images.h"
#include "actions.h"
#include "vars.h"

// ASSETS DEFINITION
const uint8_t assets[860] = {
    0x7E, 0x45, 0x45, 0x5A, 0x03, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00,
    0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x40, 0x00, 0x01, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    0xE4, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xFF, 0xFF, 0x10, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x40, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x4D, 0x6F, 0x6E, 0x6F, 0x63, 0x68, 0x72, 0x6F, 0x6D, 0x65, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00,
    0x7C, 0x00, 0x00, 0x00, 0x98, 0x00, 0x00, 0x00, 0xB4, 0x00, 0x00, 0x00, 0xD0, 0x00, 0x00, 0x00,
    0xEC, 0x00, 0x00, 0x00, 0x08, 0x01, 0x00, 0x00, 0x24, 0x01, 0x00, 0x00, 0x20, 0x4E, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x30, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x21, 0x4E, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x1C, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x22, 0x4E, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x23, 0x4E, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x23, 0x4E, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x23, 0x4E, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xD4, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x23, 0x4E, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0xC4, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x23, 0x4E, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xB0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x23, 0x4E, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x23, 0x4E, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00,
    0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00,
    0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00,
    0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00,
    0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00,
    0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00,
    0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00,
    0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00,
    0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00,
    0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00,
    0x00, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00,
    0x00, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x60, 0x00, 0xE0,
    0x00, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x01, 0x60, 0x00, 0xE0,
    0x00, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00,
    0x00, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x02, 0x60, 0x00, 0xE0, 0x00, 0xE0, 0x00, 0x00,
    0x00, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00,
    0x00, 0xE0, 0x00, 0x00, 0x04, 0x60, 0x00, 0xE0, 0x00, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00,
    0x00, 0xE0, 0x00, 0x00, 0x03, 0x60, 0x00, 0xE0, 0x00, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00,
    0x00, 0xE0, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

native_var_t native_vars[] = {
    { NATIVE_VAR_TYPE_NONE, 0, 0 },
    { NATIVE_VAR_TYPE_BOOLEAN, get_var_is_station_connected, set_var_is_station_connected }, 
    { NATIVE_VAR_TYPE_FLOAT, get_var_amb_temp_degc, set_var_amb_temp_degc }, 
    { NATIVE_VAR_TYPE_FLOAT, get_var_amb_humid_pct, set_var_amb_humid_pct }, 
    { NATIVE_VAR_TYPE_FLOAT, get_var_amb_press_kpa, set_var_amb_press_kpa }, 
    { NATIVE_VAR_TYPE_BOOLEAN, get_var_is_amb_temp_negative, set_var_is_amb_temp_negative }, 
};


ActionExecFunc actions[] = {
    0
};


#if defined(EEZ_FOR_LVGL)

void ui_init() {
    eez_flow_init(assets, sizeof(assets), (lv_obj_t **)&objects, sizeof(objects), images, sizeof(images), actions);
}

void ui_tick() {
    eez_flow_tick();
    tick_screen(g_currentScreen);
}

#else

#include <string.h>

static int16_t currentScreen = -1;

static lv_obj_t *getLvglObjectFromIndex(int32_t index) {
    if (index == -1) {
        return 0;
    }
    return ((lv_obj_t **)&objects)[index];
}

void loadScreen(enum ScreensEnum screenId) {
    currentScreen = screenId - 1;
    lv_obj_t *screen = getLvglObjectFromIndex(currentScreen);
    lv_scr_load_anim(screen, LV_SCR_LOAD_ANIM_FADE_IN, 200, 0, false);
}

void ui_init() {
    create_screens();
    loadScreen(SCREEN_ID_MAIN);
}

void ui_tick() {
    tick_screen(currentScreen);
}

#endif
