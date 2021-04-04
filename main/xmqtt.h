

#ifndef _MQTT_H
#define _MQTT_H

#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "esp_log.h"
#include "esp_err.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_spi_flash.h"
#include "mqtt_client.h"

#include "driver/gpio.h"

#include "cJSON.h"

#define HOST_NAME "111.230.206.15"
#define USER_NAME "panda"
#define USER_PASSWD "panda"

#define TOPIC_BEDROOM_LAMP          "/bedroom/lamp"
#define TOPIC_BEDROOM_CURTAIN       "/bedroom/curtain"
#define TOPIC_BEDROOM_FAN           "/bedroom/fan"
#define TOPIC_BEDROOM_TEMPERATURE   "/bedroom/temperature"
#define TOPIC_BEDROOM_HUMIDITY      "/bedroom/humidity"

#define TOPIC_LIVINGROOM_LAMP           "/livingroom/lamp"
#define TOPIC_LIVINGROOM_CURTAIN        "/livingroom/curtain"
#define TOPIC_LIVINGROOM_FAN            "/livingroom/fan"
#define TOPIC_LIVINGROOM_TEMPERATURE    "/livingroom/temperature"
#define TOPIC_LIVINGROOM_HUMIDITY       "/livingroom/humidity"

#define TOPIC_KITCHEN_LAMP          "/kitchen/lamp"
#define TOPIC_KITCHEN_TEMPERATURE   "/kitchen/temperature"
#define TOPIC_KITCHEN_HUMIDIRTY     "/kitchen/humidity"

#define TOPIC_TOILET_LAMP          "/toilet/lamp"


void mqtt_app_start(void);


#endif /* _MQTT_H */

