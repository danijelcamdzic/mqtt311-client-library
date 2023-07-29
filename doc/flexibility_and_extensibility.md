# Flexibility and Extendibility

While designing the MQTT 3.1.1 client library, special care was taken so that the library is easy to use and easy to incorporate into multiple architectures. This means that it is designed with decoupling in mind, in such a way that only the MQTT fundamentals are implemented and there is no dependency on any other library or mechanism other than the FreeRTOS library described in the previous section. The only requirement is for a device to have an internet connection and the ability to open TCP and/or SSL sockets in order to establish a connection to the MQTT brokers either via port number 1883 (TCP) or 8883 (TLS).

For these reasons, the users of the library are left with the ability to choose their own functions which play crucial roles throughout the system and they can choose to make those functions be more or less secure, resource heavy or time consuming by implementing their own solutions or using one of the many available ones.

### MQTT311Client_Utilities

`MQTT311Client_Utilities` is a component of the MQTT 3.1.1 client library which provides many helpful utility functions for the system to re-use but also provides various functions which require (some of them are optional and don't have to be implemented) external implementation. These functions vary depending on the system for which they are used and this makes the library highly re-usable because of its no-dependency postulate. The functions which are left for external implementation are:

1. **Connect Socket:** This function serves to establish a network connection between the client and broker by opening a socket over which the communication will be held. This socket can be a TCP socket or an SSL socket and the function need only be assigned without further configuration other than the specification of the broker domain name and a port number (valid certificate must be given in the SSL case).
2. **Close Socket:** This function serves to close the socket at the end of the communication.
3. **Send Data to Socket:** This function serves to send bytes to the socket, which will transfer it over to the broker over the cond protocol.
4. **Read From Socket:** This function servers to read data from the socket into a buffer.
5. **Print:** This is a debug function which serves to print debug messages in a way that the user finds convenient.
6. **Process Buffer Data:** This function can handle buffer processing after the bytes have been received from the socket. This function is the main key link between the components which use the MQTT data in some form.

An example of the library configuration to use external implementations of the functions is:

```c
MQTT311Client_SetConnectSocket(tcp_connect_socket);
MQTT311Client_SetSendToSocket(tcp_send_data);
MQTT311Client_SetReadFromSocket(tcp_receive_data);
MQTT311Client_SetPrint(debug_print);
MQTT311Client_SetProcessBufferData(mqtt_process_buffer_data);
```

Besides the external function setting features, the library also provides for an ability to configure some inside parameters which modify the system to the user's specifications. These parameters include:

1. **Redelivery Attempts**: Defines how many times to redeliver the message before announcing failed delivery.
2. **Pinging Time**: Defines the maximum time between two sending packets to occur before the sending task automatically sends the PINGREQ packet to keep the connection alive.
3. **Sending Task Delay**: Represents a value in miliseconds which defines how much time will the sending task be delayed.
4. **Receiving Task Delay**: Represents a value in miliseconds which defines how much time will the receiving task be delayed.

With this, the system can be fine-tuned to operate on any optimization level since the tasks can be set to check for messages sporadically or at a very fast pace.