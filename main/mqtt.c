
#include "mqtt.h"

static const char *TAG = "MQTT";

static char mqtt_status_buf[64];
static EventGroupHandle_t mqtt_event_group;

const int MQTT_STATUS_BIT = BIT1;

static int mqtt_online = 0;

static esp_mqtt_client_handle_t client;


static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client = event->client;
    memset(mqtt_status_buf, 0x00, sizeof(mqtt_status_buf));
    switch(event->event_id)
    {
        case MQTT_EVENT_BEFORE_CONNECT:
            break;
        case MQTT_EVENT_CONNECTED: 
            ESP_LOGI(TAG, "MQTT_EVENT_CONNECT");
            mqtt_online = 1;
            esp_mqtt_client_subscribe(client, "/esp8266/set", 0);
            strcpy(mqtt_status_buf, "MQTT CONNECTED");
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGD(TAG, "MQTT_EVENT_DISCONNECT");
            mqtt_online = 0;
            strcpy(mqtt_status_buf, "MQTT DISCONNECTED");
            break;
        case MQTT_EVENT_SUBSCRIBED:
            strcpy(mqtt_status_buf, "MQTT SUBSCRIBED");
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            strcpy(mqtt_status_buf, "MQTT UNSUBSCRIBED");
            break;
        case MQTT_EVENT_PUBLISHED:
            strcpy(mqtt_status_buf, "MQTT PUBLISH");
            break;
        case MQTT_EVENT_DATA:
            ESP_LOGI(TAG, "MQTT_EVENT_DATA");
            printf("TOPIC= %.*s\r\n", event->topic_len, event->topic);
            printf("DATA= %.*s\r\n", event->data_len, event->data);

            strcpy(mqtt_status_buf, "MQTT RECEIVE");
            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
            strcpy(mqtt_status_buf, "MQTT ERROR");
            break;
        default:
            break;
    }
    xEventGroupSetBits(mqtt_event_group, MQTT_STATUS_BIT);
    return ESP_OK;
}

void mqtt_app_start(void)
{
    mqtt_event_group = xEventGroupCreate();    
    esp_mqtt_client_config_t mqtt_cfg =
    {
        .host = HOST_ADDR,
        .port = 1883,
        .username = USER_NAME,
        .password = USER_PASSWD,
        .event_handle = mqtt_event_handler,
    };

    client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(client);

}