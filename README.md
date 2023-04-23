# MQTT311-Client-Library

This repository contains a small embedded library called `mqtt311-client-library` for MQTT 3.1.1 clients, which fully supports all functionalities from the MQTT 3.1.1 standard. You can find the standard documentation at https://docs.oasis-open.org/mqtt/mqtt/v3.1.1/os/mqtt-v3.1.1-os.html.

This library can work on any microcontroller or system that has an internet connection and can open a TCP or TLS socket.

## Features

- Fully supports all MQTT 3.1.1 packet types (CONNECT, PUBLISH, etc.).
- Provides a number of external functions to set in order to connect to the MQTT broker, send, and receive data.
- Incorporates FreeRTOS to have separate send and receive tasks.
- Uses queues to send messages so nothing is ever blocked.

## Example Usage

The following example demonstrates how to use this library with an ESP32 device:

```c
#include "MQTT311Client.h"

void app_main(void)
{
    char* TAG = "app_main";  // Declare and initialize TAG for logging purposes

    /* ------ Initialize NVS ------- */
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    /* ------ Initialize Wifi ------- */
    ESP_LOGI(TAG, "Initializing device as station and connecting to wifi...");
    wifi_init_sta();

    /* --- Set External Functions --- */
    MQTT311Client_SetConnectTCPSocket(connect_tcp_socket);
    MQTT311Client_SetSendToTCPSocket(send_tcp_data);
    MQTT311Client_SetReadFromTCPSocket(receive_tcp_data);
    MQTT311Client_SetPrint(debug_print);
    MQTT311Client_SetProcessBufferData(process_buffer_data);
    RSA_SetPrint(debug_print);

    /* ---- Start FreeRTOS Tasks ---- */
    MQTT311Client_CreateMQTTFreeRTOSTasks();

    /* ---- Connect to MQTT Broker ---- */
    MQTT311Client_CreateClient("client_id");
    MQTT311Client_EstablishConnectionToMQTTBroker("mqtt.eclipseprojects.io", 1883);
    MQTT311Client_SetUsernameAndPassword("", "");
    MQTT311Client_Connect(0xC2, 600, "", "");

    /* ----- Publish some messages ------*/
    MQTT311Client_Publish(0x00, "/topic/topic1", 0x00, "test1");
    vTaskDelay(pdMS_TO_TICKS(1000));
    MQTT311Client_Publish(0x00, "/topic/topic2", 0x00, "test2");
    vTaskDelay(pdMS_TO_TICKS(1000));
   
    /* ------ Subscribe to some topic ------ */
    MQTT311Client_Subscribe(0x02, "/topic/topic3", 0x00);
    MQTT311Client_Subscribe(0x02, "/topic/topic4", 0x00);

    /* ----- Unsubscribe to some topic ----- */
    vTaskDelay(pdMS_TO_TICKS(1000));
    MQTT311Client_Unsubscribe(0x02, "/topic/topic4");

    /* ----- Test pinging ------ */
    MQTT311Client_Pingreq();

    /* ---- Test disconnecting ---- */
    MQTT311Client_Disconnect();
}
