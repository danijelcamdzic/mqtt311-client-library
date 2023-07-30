# About

This repository contains a small embedded library called `mqtt311-client-library` for MQTT 3.1.1 clients, which fully supports all functionalities from the MQTT 3.1.1 standard. You can find the standard documentation at https://docs.oasis-open.org/mqtt/mqtt/v3.1.1/os/mqtt-v3.1.1-os.html.

This library can work on any microcontroller or system that has an internet connection and can open a TCP or TLS socket.

# Features

- Fully supports all MQTT 3.1.1 packet types (CONNECT, PUBLISH, etc.).
- Provides a number of external functions to set in order to connect to the MQTT broker, send, and receive data.
- Incorporates FreeRTOS to have separate send and receive tasks.
- Uses queues to send messages so nothing is ever blocked.

# Detailed Documentation
For more in-depth information, see the following documents:

- [FreeRTOS Incorporation](doc/freertos_incorporation.md)
- [Flixibility and Extensibility](doc/flexibility_and_extensibility.md)

# Usage

There are two complete examples on how to use this library to connect to an MQTT broker (test.moqsuitto.org).

## TCP Connection

For example usage with TCP socket, check out the [ESP32 TCP example](/examples/esp32/tcp/)

## SSL Connection

For example usage with SSL socket, check out the [ESP32 SSL example](/examples/esp32/ssl/)
