# MQTT311-Client-Library

This repository contains a small embedded library called `mqtt311-client-library` for MQTT 3.1.1 clients, which fully supports all functionalities from the MQTT 3.1.1 standard. You can find the standard documentation at https://docs.oasis-open.org/mqtt/mqtt/v3.1.1/os/mqtt-v3.1.1-os.html.

This library can work on any microcontroller or system that has an internet connection and can open a TCP or TLS socket.

# Features

- Fully supports all MQTT 3.1.1 packet types (CONNECT, PUBLISH, etc.).
- Provides a number of external functions to set in order to connect to the MQTT broker, send, and receive data.
- Incorporates FreeRTOS to have separate send and receive tasks.
- Uses queues to send messages so nothing is ever blocked.

# Example Usage (ESP32)

Navigate to the [examples/esp32](examples/esp32/) folder to find the usage example usage for the ESP32 series of microcontrollers. There, you will see how the ESP32 is used to connect to the internet and how the library is used to connect to the MQTT broker (mqtt.eclipseprojects.io) on port 1883 (TCP port) and publish/subscribe to some topics, ping the broker and at the end, disconnect.

## Setting Up the Enviroment

To set up the hardware nodes, follow the steps to set up the ESP32 build environment as described in the official [documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html) of the esp32.

## Build the project using `idf.py`:

1. Navigate to the `hardware_node` directory:

```bash
cd secure-distributed-password-storage/hardware_node
```

2. Export necessary tools:

```bash
 . $HOME/esp/esp-idf/export.sh
```

3. Edit the `menuconfig` to edit your Wi-Fi credentials:

```bash
idf.py menuconfig
```

4. Build the project

```bash
idf.py build
```

4. Flash the project

```bash
idf.py flash
```

## The Results

You can see the commands in the `main` file in the `app_main` function:

```c
    /* Initialize Wi-Fi */
    ESP_LOGI(TAG, "Initializing device as station and connecting to wifi...");
    wifi_init_sta();

    /* Set external functions for MQTT library */
    MQTT311Client_SetConnectTCPSocket(tcp_connect_socket);
    MQTT311Client_SetSendToTCPSocket(tcp_send_data);
    MQTT311Client_SetReadFromTCPSocket(tcp_receive_data);
    MQTT311Client_SetPrint(debug_print);
    MQTT311Client_SetProcessBufferData(mqtt_process_buffer_data);

    /* Start FreeRTOS tasks for sending and receiving MQTT messages */
    MQTT311Client_CreateMQTTFreeRTOSTasks();

    /* Connect to MQTT broker */
    MQTT311Client_CreateClient(CLIENT_ID);
    MQTT311Client_EstablishConnectionToMQTTBroker(BROKER_ADDRESS, BROKER_PORT_TCP);
    MQTT311Client_SetUsernameAndPassword("", "");
    MQTT311Client_Connect(0xC2, KEEP_ALIVE, "", "");
   
    /* ----- Publish some messages ------*/
    MQTT311Client_Publish(0x00, "/topic/topic1", 0x00, "test1", sizeof("test1"));
    vTaskDelay(pdMS_TO_TICKS(1000));
    MQTT311Client_Publish(0x00, "/topic/topic2", 0x00, "test2", sizeof("test2"));
    vTaskDelay(pdMS_TO_TICKS(1000));
   
    /* ------ Subscribe to some topic ------ */
    MQTT311Client_Subscribe(0x02, "/topic/topic3", 0x00);
    vTaskDelay(pdMS_TO_TICKS(1000));
    MQTT311Client_Subscribe(0x02, "/topic/topic4", 0x00);
    vTaskDelay(pdMS_TO_TICKS(1000));

    /* ----- Unsubscribe from some topic ----- */
    MQTT311Client_Unsubscribe(0x02, "/topic/topic4");
    vTaskDelay(pdMS_TO_TICKS(1000));

    /* ----- Test pinging ------ */
    MQTT311Client_Pingreq();
    vTaskDelay(pdMS_TO_TICKS(1000));

    /* ---- Test disconnecting ---- */
    MQTT311Client_Disconnect();
    vTaskDelay(pdMS_TO_TICKS(1000));
```

And you can follow the results of the command on the terminal, which, if you flashed the exact same example, will look like this:

![Monitoring MQTT Connection](/assets/monitoring_mqtt.png)