
#include "xwifi.h"

static const char *TAG = "xWifi";

const int CONNECTED_BIT = BIT0;
static EventGroupHandle_t wifi_event_group;

static esp_err_t wifi_event_handler(void *ctx, system_event_t *event)
{
    system_event_info_t *info = &event->event_info;
    switch(event->event_id)
    {
        case SYSTEM_EVENT_STA_START:
            esp_wifi_connect(); // 根据 wifi 配置，连接 wifi
            break;
        case SYSTEM_EVENT_STA_GOT_IP: // 成功获取到 IP， 表示联网成功
            xEventGroupSetBits(wifi_event_group, CONNECTED_BIT); 
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED: // station 已经断开了，重新连接 wifi
            ESP_LOGE(TAG, "Disconnect reason: %d", info->disconnected.reason);
            if(info->disconnected.reason == WIFI_REASON_BASIC_RATE_NOT_SUPPORT)
            {
                esp_wifi_set_protocol(ESP_IF_WIFI_STA, WIFI_PROTOCOL_11B | WIFI_PROTOCOL_11G | WIFI_PROTOCOL_11N);
            }
            esp_wifi_connect();
            xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
            break;
        default:
            break;
    }
    return ESP_OK;
}


void wifi_init(void)
{
    tcpip_adapter_init();   // tcpio 协议栈初始化， 使用网络时必须调用此函数
    
    // 创建一个 freeRTOS　的事件标志组，用于当 wifi 没有连接时将程序停息，只有 wifi 连接成功了才能运行程序
    wifi_event_group = xEventGroupCreate();

    /* 
        配置 wifi 的回调函数，用于连接 wifi, 
        ESP_ERROR_CHECK 检查函数返回值
    */
    ESP_ERROR_CHECK(esp_event_loop_init(wifi_event_handler, NULL));
    
    // wifi 配置
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    wifi_config_t wifi_config =
    {
        .sta={
            .ssid = WIFI_STA_SSID,
            .password = WIFI_STA_PASSWD
        },
    };

    ESP_LOGI(TAG, "WIFI SSID: [%s] ...", wifi_config.sta.ssid);
    
    // 将 wifi 设置为 sta 模式
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
    
    // 开始运行 wifi
    ESP_ERROR_CHECK(esp_wifi_start());

    // 等待事件标志，成功获取到时间标志位后才继续执行，否则一直等在这里
    xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT, false, true, portMAX_DELAY);
}