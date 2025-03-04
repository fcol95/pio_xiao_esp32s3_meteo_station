#include "lcd_manager.h"

#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_err.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_log.h"
#include "esp_lvgl_port.h"

#include "lvgl.h"
#include "ui.h" //< For EEZ Studio functions
#include "vars.h"

#include "lcd_variables.h"

static const char *LOG_TAG = "lcd";

#define LVGL_LOCK_TIMEOUT_MS 1000U
#define UI_TASK_PERIOD_MS    10U

#define LCD_PIXEL_CLOCK_HZ   (400 * 1000)
#define LCD_RESET_PIN_NUM    -1 // No LCD reset pin on XIAO Expansion Base Board -  -1 for unused
#define LCD_I2C_HW_ADDR      0x3C

// The pixel number in horizontal and vertical
#define SSD1306_LCD_H_RES 128
#define SSD1306_LCD_V_RES 64

// Bit number used to represent command and parameter
#define SSD1306_LCD_CMD_BITS   8
#define SSD1306_LCD_PARAM_BITS 8

static lv_display_t *s_disp = NULL;

// LCD I2C Variables
static esp_lcd_panel_io_handle_t s_lcd_io_handle = NULL;

static const esp_lcd_panel_io_i2c_config_t io_config = {
    .dev_addr = LCD_I2C_HW_ADDR,
    .scl_speed_hz = LCD_PIXEL_CLOCK_HZ,
    .control_phase_bytes = 1,               // According to SSD1306 datasheet
    .lcd_cmd_bits = SSD1306_LCD_CMD_BITS,   // According to SSD1306 datasheet
    .lcd_param_bits = SSD1306_LCD_CMD_BITS, // According to SSD1306 datasheet
    .dc_bit_offset = 6,                     // According to SSD1306 datasheet
};

static esp_lcd_panel_handle_t         s_lcd_panel_handle = NULL;
static esp_lcd_panel_ssd1306_config_t s_ssd1306_config = {
    .height = SSD1306_LCD_V_RES,
};
static const esp_lcd_panel_dev_config_t s_panel_config = {
    .bits_per_pixel = 1,
    .reset_gpio_num = LCD_RESET_PIN_NUM,
    .vendor_config = &s_ssd1306_config,
};

static const lvgl_port_cfg_t s_lvgl_port_cfg = ESP_LVGL_PORT_INIT_CONFIG();

esp_err_t lcd_manager_init(i2c_master_bus_handle_t s_i2c_bus)
{
    if (s_i2c_bus == NULL) return ESP_FAIL;

    ESP_LOGI(LOG_TAG, "Install panel IO");
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c(s_i2c_bus, &io_config, &s_lcd_io_handle));
    if (s_lcd_io_handle == NULL) return ESP_FAIL;

    ESP_LOGI(LOG_TAG, "Install SSD1306 panel driver");

    ESP_ERROR_CHECK(esp_lcd_new_panel_ssd1306(s_lcd_io_handle, &s_panel_config, &s_lcd_panel_handle));
    if (s_lcd_panel_handle == NULL) return ESP_FAIL;

    ESP_ERROR_CHECK(esp_lcd_panel_reset(s_lcd_panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(s_lcd_panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(s_lcd_panel_handle, true));

    ESP_LOGI(LOG_TAG, "Initialize LVGL");
    ESP_ERROR_CHECK(lvgl_port_init(&s_lvgl_port_cfg));

    const lvgl_port_display_cfg_t lvgl_port_display_cfg = {.io_handle = s_lcd_io_handle,
                                                           .panel_handle = s_lcd_panel_handle,
                                                           .buffer_size = SSD1306_LCD_H_RES * SSD1306_LCD_V_RES,
                                                           .double_buffer = true,
                                                           .hres = SSD1306_LCD_H_RES,
                                                           .vres = SSD1306_LCD_V_RES,
                                                           .monochrome = true,
                                                            /* Rotation values must be same as used in esp_lcd for initial settings of the screen */
                                                           .rotation = {
                                                               .swap_xy = false,
                                                               .mirror_x = false,
                                                               .mirror_y = false,
                                                           },
                                                           .flags = 
                                                           {
                                                            .sw_rotate = true,
                                                           },
                                                           };
    s_disp = lvgl_port_add_disp(&lvgl_port_display_cfg);
    if (s_disp == NULL) return ESP_FAIL;

    /* Rotation of the screen */
    lv_display_set_rotation(s_disp, LV_DISPLAY_ROTATION_0);

    // Init EEZ UI Variables
    esp_err_t var_ret = lcd_variables_init();
    if (var_ret == ESP_FAIL)
    {
        ESP_LOGE(LOG_TAG, "Failed to init EEZ variables handles!");
        return ESP_FAIL;
    }

    // Lock the mutex due to the LVGL APIs are not thread-safe
    if (!!!lvgl_port_lock(LVGL_LOCK_TIMEOUT_MS))
    {
        ESP_LOGE(LOG_TAG, "Failed to lock LVGL mutex!");
        return ESP_FAIL;
    }
    esp_lcd_panel_invert_color(s_lcd_panel_handle,
                               true); // Invert colors to fit with EEZ Studio visual
    ui_init();
    lvgl_port_unlock(); // Release the mutex

    return ESP_OK;
}

void lcd_manager_task(void *pvParameter)
{
    // NOTE: This is the old example lvgl demo from espressif before integrating EEZ studio
    // example_lvgl_demo_ui(s_disp);
    while (1)
    {
        // Lock the mutex due to the LVGL APIs are not thread-safe
        if (!!!lvgl_port_lock(LVGL_LOCK_TIMEOUT_MS))
        {
            ESP_LOGE(LOG_TAG, "Failed to lock LVGL mutex!");
        }
        else
        {
            ui_tick();
            lvgl_port_unlock(); // Release the mutex
        }

        // NOTE: This is an example of an EEZ Studio simple screen, toggle the variable here shpould toggle the onscreen
        // "LED"
        static TickType_t last_toggle_time = 0;
        TickType_t        current_time = xTaskGetTickCount();
        if ((current_time - last_toggle_time) >= pdMS_TO_TICKS(1000))
        {
            int32_t current_state = get_var_is_station_connected();
            set_var_is_station_connected(!current_state);
            last_toggle_time = current_time;
        }
        vTaskDelay(pdMS_TO_TICKS(UI_TASK_PERIOD_MS));
    }
    ESP_ERROR_CHECK(lvgl_port_remove_disp(s_disp));
}
