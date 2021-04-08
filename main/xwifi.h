

#ifndef _XWIFI_H
#define _XWIFI_H

#include "freertos/FreeRTOS.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include "esp_log.h"
#include "esp_err.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_spi_flash.h"

#define WIFI_STA_SSID   "three cobblers"
#define WIFI_STA_PASSWD "BRS17101"


void wifi_init(void);


#endif /* _XWIFI_H */
