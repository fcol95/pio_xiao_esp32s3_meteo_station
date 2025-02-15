#include "lcd_variables.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "vars.h"

#include <math.h>

// NOTE: Getter/Setter for EEZ Studio functions
static bool              s_is_station_connected = false;
static SemaphoreHandle_t s_is_station_connected_mutex = NULL;

bool get_var_is_station_connected()
{
    if (s_is_station_connected_mutex == NULL) return 0;
    xSemaphoreTake(s_is_station_connected_mutex, portMAX_DELAY);
    int32_t value = s_is_station_connected;
    xSemaphoreGive(s_is_station_connected_mutex);
    return value;
}
void set_var_is_station_connected(bool value)
{
    if (s_is_station_connected_mutex == NULL) return;
    xSemaphoreTake(s_is_station_connected_mutex, portMAX_DELAY);
    s_is_station_connected = value;
    xSemaphoreGive(s_is_station_connected_mutex);
}
static float             s_amb_temp_degc = NAN;
static SemaphoreHandle_t s_amb_temp_degc_mutex = NULL;

float get_var_amb_temp_degc()
{
    if (s_amb_temp_degc_mutex == NULL) return NAN;
    xSemaphoreTake(s_amb_temp_degc_mutex, portMAX_DELAY);
    float value = s_amb_temp_degc;
    xSemaphoreGive(s_amb_temp_degc_mutex);
    return value;
}

void set_var_amb_temp_degc(float value)
{
    if (s_amb_temp_degc_mutex == NULL) return;
    xSemaphoreTake(s_amb_temp_degc_mutex, portMAX_DELAY);
    s_amb_temp_degc = value;
    xSemaphoreGive(s_amb_temp_degc_mutex);
}

static float             s_amb_humid_pct = NAN;
static SemaphoreHandle_t s_amb_humid_pct_mutex = NULL;

float get_var_amb_humid_pct()
{
    if (s_amb_humid_pct_mutex == NULL) return NAN;
    xSemaphoreTake(s_amb_humid_pct_mutex, portMAX_DELAY);
    float value = s_amb_humid_pct;
    xSemaphoreGive(s_amb_humid_pct_mutex);
    return value;
}

void set_var_amb_humid_pct(float value)
{
    if (s_amb_humid_pct_mutex == NULL) return;
    xSemaphoreTake(s_amb_humid_pct_mutex, portMAX_DELAY);
    s_amb_humid_pct = value;
    xSemaphoreGive(s_amb_humid_pct_mutex);
}

static float             s_amb_press_kpa = NAN;
static SemaphoreHandle_t s_amb_press_kpa_mutex = NULL;

float get_var_amb_press_kpa()
{
    if (s_amb_press_kpa_mutex == NULL) return NAN;
    xSemaphoreTake(s_amb_press_kpa_mutex, portMAX_DELAY);
    float value = s_amb_press_kpa;
    xSemaphoreGive(s_amb_press_kpa_mutex);
    return value;
}

void set_var_amb_press_kpa(float value)
{
    if (s_amb_press_kpa_mutex == NULL) return;
    xSemaphoreTake(s_amb_press_kpa_mutex, portMAX_DELAY);
    s_amb_press_kpa = value;
    xSemaphoreGive(s_amb_press_kpa_mutex);
}

static bool              s_is_amb_temp_negative = false;
static SemaphoreHandle_t s_is_amb_temp_negative_mutex = NULL;

bool get_var_is_amb_temp_negative()
{
    if (s_is_amb_temp_negative_mutex == NULL) return false;
    xSemaphoreTake(s_is_amb_temp_negative_mutex, portMAX_DELAY);
    bool value = s_is_amb_temp_negative;
    xSemaphoreGive(s_is_amb_temp_negative_mutex);
    return value;
}

void set_var_is_amb_temp_negative(bool value)
{
    if (s_is_amb_temp_negative_mutex == NULL) return;
    xSemaphoreTake(s_is_amb_temp_negative_mutex, portMAX_DELAY);
    s_is_amb_temp_negative = value;
    xSemaphoreGive(s_is_amb_temp_negative_mutex);
}

esp_err_t lcd_variables_init(void)
{
    s_is_station_connected_mutex = xSemaphoreCreateMutex();
    if (s_is_station_connected_mutex == NULL) return ESP_FAIL;

    s_amb_temp_degc_mutex = xSemaphoreCreateMutex();
    if (s_amb_temp_degc_mutex == NULL) return ESP_FAIL;

    s_amb_humid_pct_mutex = xSemaphoreCreateMutex();
    if (s_amb_humid_pct_mutex == NULL) return ESP_FAIL;

    s_amb_press_kpa_mutex = xSemaphoreCreateMutex();
    if (s_amb_press_kpa_mutex == NULL) return ESP_FAIL;

    s_is_amb_temp_negative_mutex = xSemaphoreCreateMutex();
    if (s_is_amb_temp_negative_mutex == NULL) return ESP_FAIL;

    return ESP_OK;
}