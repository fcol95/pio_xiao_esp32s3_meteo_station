#ifndef LCD_VARIABLES__H__
#define LCD_VARIABLES__H__

#include <stdbool.h>
#include <stdint.h>

#include "esp_err.h"

esp_err_t lcd_variables_init(void);

bool  get_var_is_station_connected();
void  set_var_is_station_connected(bool value);
float get_var_amb_temp_degc();
void  set_var_amb_temp_degc(float value);
float get_var_amb_humid_pct();
void  set_var_amb_humid_pct(float value);
float get_var_amb_press_kpa();
void  set_var_amb_press_kpa(float value);
bool  get_var_is_amb_temp_negative();
void  set_var_is_amb_temp_negative(bool value);

#endif // LCD_VARIABLES__H__