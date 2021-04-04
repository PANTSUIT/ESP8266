
#include "xmqtt.h"

static const char *TAG = "MQTT";

static char mqtt_status_buf[64];
static EventGroupHandle_t mqtt_event_group;

const int MQTT_STATUS_BIT = BIT1;

static int mqtt_online = 0;

static esp_mqtt_client_handle_t client;

static void mqtt_data_handler(esp_mqtt_event_handle_t event)
{
    uint32_t value;
    cJSON *cJson = NULL, *cJson_value = NULL;
    printf("TOPIC: %.*s\r\n", event->topic_len, event->topic);
    printf("Message: %.*s\r\n", event->data_len, event->data);
    
    cJson = cJSON_Parse(event->data);

    if(strstr(event->topic, "bedroom"))
    {
        if(strstr(event->topic, "lamp"))
        {
            cJson_value = cJSON_GetObjectItem(cJson, "lamp");
            value = cJSON_GetNumberValue(cJson_value);
            printf("GetValue: %d\n", value);
            gpio_set_level(14, value);
        }
        else if(strstr(event->topic, "fan"))
        {
            cJson_value = cJSON_GetObjectItem(cJson, "fan");
            value = cJSON_GetNumberValue(cJson_value);
            printf("GetValue: %d\n", value);
            gpio_set_level(14, value);
        }
        else if(strstr(event->topic, "curtain"))
        {
            cJson_value = cJSON_GetObjectItem(cJson, "curtain");
            value = cJSON_GetNumberValue(cJson_value);
            printf("GetValue: %d\n", value);
            gpio_set_level(14, value);            
        }
    }
    else if(strstr(event->topic, "livingroom"))
    {
        if(strstr(event->topic, "lamp"))
        {
            cJson_value = cJSON_GetObjectItem(cJson, "lamp");
            value = cJSON_GetNumberValue(cJson_value);
            printf("GetValue: %d\n", value);
            gpio_set_level(14, value);
        }
        else if(strstr(event->topic, "fan"))
        {
            cJson_value = cJSON_GetObjectItem(cJson, "fan");
            value = cJSON_GetNumberValue(cJson_value);
            printf("GetValue: %d\n", value);
            gpio_set_level(14, value);
        }
        else if(strstr(event->topic, "curtain"))
        {
            cJson_value = cJSON_GetObjectItem(cJson, "curtain");
            value = cJSON_GetNumberValue(cJson_value);
            printf("GetValue: %d\n", value);
            gpio_set_level(14, value);            
        }
    }
    else if(strstr(event->topic, "kitchen"))
    {
        if(strstr(event->topic, "lamp"))
        {
            cJson_value = cJSON_GetObjectItem(cJson, "lamp");
            value = cJSON_GetNumberValue(cJson_value);
            printf("GetValue: %d\n", value);
            gpio_set_level(14, value);
        }
    }
    else if(strstr(event->topic, "toilet"))
    {
        if(strstr(event->topic, "lamp"))
        {
            cJson_value = cJSON_GetObjectItem(cJson, "lamp");
            value = cJSON_GetNumberValue(cJson_value);
            printf("GetValue: %d\n", value);
            gpio_set_level(14, value);
        }
    }


    if(strstr(event->topic, TOPIC_BEDROOM_LAMP))
    {
        uint32_t value = 0;
        cJson_value = cJSON_GetObjectItem(cJson, "lamp");
        value = cJSON_GetNumberValue(cJson_value);
        
        printf("%d\n", value);
        gpio_set_level(14, value);
    }
    else if(strstr(event->topic, TOPIC_BEDROOM_FAN))
    {
        uint32_t value = 0;
        cJson_value = cJSON_GetObjectItem(cJson, "fan");
        value = cJSON_GetNumberValue(cJson_value);
        printf("%d\n", value);
        gpio_set_level(14, (value ? 1 : 0));
    }
    else if(strstr(event->topic, TOPIC_BEDROOM_CURTAIN))
    {
        uint32_t value = 0;
        cJson_value = cJSON_GetObjectItem(cJson, "curtain");
        value = cJSON_GetNumberValue(cJson_value);
        printf("%d\n", value);
        gpio_set_level(14, (value ? 1 : 0));
    }
    else if(strstr(event->topic, TOPIC_BEDROOM_TEMPERATURE))
    {
        double value = 0.0;
        cJson_value = cJSON_GetObjectItem(cJson, "temperature");
        value = cJSON_GetNumberValue(cJson_value);
        cJSON *cJson_publish = cJSON_CreateObject();
        cJSON_AddNumberToObject(cJson_publish, "temperature", value);
        printf("%s\n", cJSON_Print(cJson_publish));   

        esp_mqtt_client_publish(client, TOPIC_BEDROOM_TEMPERATURE, cJson_publish->string, 0, 0, 0);

    }
    else if(strstr(event->topic, TOPIC_BEDROOM_HUMIDITY))
    {
        double value = 0.0;
        cJson_value = cJSON_GetObjectItem(cJson, "humidity");
        value = cJSON_GetNumberValue(cJson_value);

        cJSON *cJson_publish = cJSON_CreateObject();
        cJSON_AddNumberToObject(cJson_publish, "humidity", value);
        printf("%s\n", cJSON_Print(cJson_publish));        
        esp_mqtt_client_publish(client, TOPIC_BEDROOM_HUMIDITY, cJson_publish->string, 0, 0, 0);
    }
}

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
            esp_mqtt_client_subscribe(client, TOPIC_BEDROOM_LAMP, 0);
            esp_mqtt_client_subscribe(client, TOPIC_BEDROOM_FAN, 0);
            esp_mqtt_client_subscribe(client, TOPIC_BEDROOM_CURTAIN, 0);
            esp_mqtt_client_subscribe(client, TOPIC_BEDROOM_TEMPERATURE, 0);
            esp_mqtt_client_subscribe(client, TOPIC_BEDROOM_HUMIDITY, 0);

            esp_mqtt_client_subscribe(client, TOPIC_LIVINGROOM_LAMP, 0);
            esp_mqtt_client_subscribe(client, TOPIC_LIVINGROOM_FAN, 0);
            esp_mqtt_client_subscribe(client, TOPIC_LIVINGROOM_CURTAIN, 0);
            esp_mqtt_client_subscribe(client, TOPIC_LIVINGROOM_TEMPERATURE, 0);
            esp_mqtt_client_subscribe(client, TOPIC_LIVINGROOM_HUMIDITY, 0);

            esp_mqtt_client_subscribe(client, TOPIC_KITCHEN_LAMP, 0);
            esp_mqtt_client_subscribe(client, TOPIC_KITCHEN_TEMPERATURE, 0);
            esp_mqtt_client_subscribe(client, TOPIC_KITCHEN_HUMIDIRTY, 0);

            esp_mqtt_client_subscribe(client, TOPIC_TOILET_LAMP, 0);

            strcpy(mqtt_status_buf, "MQTT CONNECTED");
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGD(TAG, "MQTT_EVENT_DISCONNECT");
            mqtt_online = 0;
            strcpy(mqtt_status_buf, "MQTT DISCONNECTED");
       
            esp_mqtt_client_unsubscribe(client, TOPIC_BEDROOM_LAMP);
            esp_mqtt_client_unsubscribe(client, TOPIC_BEDROOM_FAN);
            esp_mqtt_client_unsubscribe(client, TOPIC_BEDROOM_CURTAIN);
            esp_mqtt_client_unsubscribe(client, TOPIC_BEDROOM_TEMPERATURE);
            esp_mqtt_client_unsubscribe(client, TOPIC_BEDROOM_HUMIDITY);

            esp_mqtt_client_unsubscribe(client, TOPIC_LIVINGROOM_LAMP);
            esp_mqtt_client_unsubscribe(client, TOPIC_LIVINGROOM_FAN);
            esp_mqtt_client_unsubscribe(client, TOPIC_LIVINGROOM_CURTAIN);
            esp_mqtt_client_unsubscribe(client, TOPIC_LIVINGROOM_TEMPERATURE);
            esp_mqtt_client_unsubscribe(client, TOPIC_LIVINGROOM_HUMIDITY);

            esp_mqtt_client_unsubscribe(client, TOPIC_KITCHEN_LAMP);
            esp_mqtt_client_unsubscribe(client, TOPIC_KITCHEN_TEMPERATURE);
            esp_mqtt_client_unsubscribe(client, TOPIC_KITCHEN_HUMIDIRTY);

            esp_mqtt_client_unsubscribe(client, TOPIC_TOILET_LAMP);

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

            mqtt_data_handler(event);            

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
        .host = HOST_NAME,
        .port = 1883,
        .username = USER_NAME,
        .password = USER_PASSWD,
        .event_handle = mqtt_event_handler,
    };

    client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(client);

}