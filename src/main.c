#include <stdio.h>

#include "sdkconfig.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h" //< For LED toggling
#include "driver/i2c_master.h"

#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_log.h"

#include "ambient_sense.h"
#include "lcd_manager.h"

static const char *LOG_TAG = "main";

#ifdef CONFIG_BLINK_GPIO
    #define BLINK_GPIO (gpio_num_t) CONFIG_BLINK_GPIO
#else
    #define BLINK_GPIO (gpio_num_t)21 // LED_BUILT_IN
#endif

#define I2C_BUS_PORT    0

#define I2C_SDA_PIN_NUM GPIO_NUM_5 // SDA pin for XIAO ESP32S3 with Grove Base Expansion Board
#define I2C_SCL_PIN_NUM GPIO_NUM_6 // SCL pin for XIAO ESP32S3 with Grove Base Expansion Board

static i2c_master_bus_handle_t       s_i2c_bus = NULL;
static const i2c_master_bus_config_t s_i2c_bus_config = {
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .glitch_ignore_cnt = 7,
    .i2c_port = I2C_BUS_PORT,
    .sda_io_num = I2C_SDA_PIN_NUM,
    .scl_io_num = I2C_SCL_PIN_NUM,
    .flags.enable_internal_pullup = true,
};

void blink_task(void *pvParameter)
{
    // Set the GPIO as a push/pull output
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    while (1)
    {
        // Blink off (output low)
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(pdMS_TO_TICKS(1000));
        // Blink on (output high)
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void print_board_info(void)
{
    /* Print chip information */
    esp_chip_info_t chip_info;
    uint32_t        flash_size;
    esp_chip_info(&chip_info);
    ESP_LOGI(LOG_TAG,
             "  This is %s chip with %d CPU core(s), WiFi%s%s, ",
             CONFIG_IDF_TARGET,
             chip_info.cores,
             (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
             (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    unsigned major_rev = chip_info.revision / 100;
    unsigned minor_rev = chip_info.revision % 100;
    ESP_LOGI(LOG_TAG, "silicon revision v%d.%d, ", major_rev, minor_rev);
    if (esp_flash_get_size(NULL, &flash_size) != ESP_OK)
    {
        ESP_LOGE(LOG_TAG, "Get flash size failed!");
        return;
    }

    ESP_LOGI(LOG_TAG,
             "%ldMB %s flash",
             flash_size / (1024 * 1024),
             (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    ESP_LOGI(LOG_TAG, "Minimum free heap size: %ld bytes", esp_get_minimum_free_heap_size());
}

void app_main()
{
    // Set UART log level
    esp_log_level_set(LOG_TAG, ESP_LOG_INFO);

    ESP_LOGI(LOG_TAG, "-- XIAO ESP32S3 Meteo Station Exploration --");

    print_board_info();

    ESP_LOGI(LOG_TAG, "Starting program...");

    // Drivers Init
    ESP_LOGI(LOG_TAG, "Initialize I2C bus");
    ESP_ERROR_CHECK(i2c_new_master_bus(&s_i2c_bus_config, &s_i2c_bus));

    esp_err_t ambient_sense_ret = ambient_sense_init(s_i2c_bus);
    esp_err_t lcd_ret = lcd_manager_init(s_i2c_bus);

    // Tasks Init
    xTaskCreate(&blink_task, "blink_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);
    if (lcd_ret == ESP_OK)
    {
        xTaskCreate(&lcd_manager_task, "lcd_task", configMINIMAL_STACK_SIZE * 4, NULL, 4, NULL);
    }
    else
    {
        ESP_LOGE(LOG_TAG, "UI initialization failed!");
    }
    if (ambient_sense_ret == ESP_OK)
    {
        xTaskCreate(&ambient_sense_task, "ambient_sense_task", configMINIMAL_STACK_SIZE * 2, NULL, 5, NULL);
    }
    else
    {
        ESP_LOGE(LOG_TAG, "Ambient sense initialization failed!");
    }
}
