
/**
 * @file mqtt_functions.h
 * @brief Contains necessary defines, variables declarations
 * and function protypes for using the MQTT311Client library 
 * and processing the data that has been received
 *
 * @author Danijel Camdzic
 * @date 1 May 2023
 */

#ifndef MQTT_FUNCTIONS_H
#define MQTT_FUNCTIONS_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "esp_log.h"

/* MQTT connection specific defines */
#define BROKER_ADDRESS              "mqtt.eclipseprojects.io"
#define BROKER_PORT_TCP             1883
#define KEEP_ALIVE                  600
#define CLIENT_ID                   "client_id"

/* MQTT utility function prototypes */
void mqtt_process_buffer_data(void);

#endif /* MQTT_FUNCTIONS_H */