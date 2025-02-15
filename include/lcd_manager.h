#ifndef LCD_MANAGER__H__
#define LCD_MANAGER__H__

#include "esp_err.h"

esp_err_t lcd_manager_init(void);
void      lcd_manager_task(void *pvParameter);

#endif // LCD_MANAGER__H__
