file(GLOB MQTT_SOURCES "../../../../MQTT311Client/*.c")

idf_component_register(SRCS "main.c"
                            "tcp_functions.c"
                            "mqtt_functions.c"
                            ${MQTT_SOURCES}
                    INCLUDE_DIRS "." "../../../../MQTT311Client" "../../../../")


