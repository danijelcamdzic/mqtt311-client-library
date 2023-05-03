/**
 * @file mqtt_functions.c
 * @brief Contains necessary defines, variables defintions
 * and function definitions for using the MQTT311Client library 
 * and processing the data that has been received
 *
 * @author Danijel Camdzic
 * @date 1 May 2023
 */

/* Utility headers for MQTT and NVS */
#include "mqtt_functions.h"

/* MQTT311Client library header */
#include "MQTT311Client/MQTT311Client.h"
#include "MQTT311Client/MQTT311Client_Publish.h"

/**
 * @brief Example buffer processor
 *
 * @param None
 */
void mqtt_process_buffer_data(void) 
{
    char* TAG = "mqtt_process_buffer_data";                             /**< Declare and initialize TAG for logging purposes */   

    for (int i = 0; i < MQTT311_RECEIVED_BYTES; i++)
    {
        ESP_LOGI(TAG, "%c", MQTT311_RECEIVE_BUFFER[i]);
    }
}
