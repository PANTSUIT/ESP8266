/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include "xwifi.h"
#include "xmqtt.h"
#include "xgpio.h"

static const char *TAG = "SmartHome";

void app_main()
{
    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is ESP8266 chip with %d CPU cores, WiFi silicon revision %d, %d MB %s flash\n", 
        chip_info.cores, chip_info.revision, spi_flash_get_chip_size() / (1024 * 1024)
        ,(chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    gpio_init(14 , GPIO_MODE_OUTPUT, GPIO_PULLUP_DISABLE, GPIO_PULLDOWN_ENABLE, GPIO_INTR_DISABLE);
    
    wifi_init();
    mqtt_app_start();  
}
