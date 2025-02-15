#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations



// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_NONE
};

// Native global variables

extern bool get_var_is_station_connected();
extern void set_var_is_station_connected(bool value);
extern float get_var_amb_temp_degc();
extern void set_var_amb_temp_degc(float value);
extern float get_var_amb_humid_pct();
extern void set_var_amb_humid_pct(float value);
extern float get_var_amb_press_kpa();
extern void set_var_amb_press_kpa(float value);
extern bool get_var_is_amb_temp_negative();
extern void set_var_is_amb_temp_negative(bool value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/