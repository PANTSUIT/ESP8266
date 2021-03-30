

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

#define HOST_ADDR "111.230.206.15"
#define USER_NAME "panda"
#define USER_PASSWD "panda"

void mqtt_app_start(void);


#endif /* _MQTT_H */

