/**
 * @file nvs_functions.c
 * @brief Contains necessary defines, variables definitions
 * and function definitions for using the NVS in esp32
 *
 * @author Danijel Camdzic
 * @date 1 May 2023
 */

#include "nvs_functions.h"

/* ------------------------- FUNCTION DEFINITIONS ------------------------------------ */

/**
 * @brief Initialize the NVS flash.
 *
 * @return esp_err_t Error code indicating the result of the operation.
 */
esp_err_t nvs_init() 
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    return err;
}