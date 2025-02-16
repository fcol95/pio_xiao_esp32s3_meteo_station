#ifndef LCD_MANAGER__H__
#define LCD_MANAGER__H__

#include "driver/i2c_master.h"
#include "esp_err.h"

esp_err_t lcd_manager_init(i2c_master_bus_handle_t s_i2c_bus);
void      lcd_manager_task(void *pvParameter);

#endif // LCD_MANAGER__H__
