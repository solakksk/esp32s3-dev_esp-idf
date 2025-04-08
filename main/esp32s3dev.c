#include <stdio.h>
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_log.h"

static const char *TAG = "wifi_bridge";

void app_main(void)
{
    //初始化nvs分区
    nvs_flash_init();
    //创建默认事件循环
    esp_event_loop_create_default();
    //初始化网卡
    esp_netif_init();
    //创建sta,ap网卡
    esp_netif_t* stanetif = esp_netif_create_default_wifi_sta();
    esp_netif_t* apnetif = esp_netif_create_default_wifi_ap();
    //初始化wifi协议栈
    wifi_init_config_t wifi_init_cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&wifi_init_cfg);
    //设置wifi模式
    esp_wifi_set_mode(WIFI_MODE_APSTA);
    //配置sta模式wifi参数
    wifi_config_t stacfg = {
        .sta = {
            .ssid = "TP-LINK_KAKA",
            .password = "1002337174",
            .threshold.authmode = WIFI_AUTH_WPA_WPA2_PSK
        }
    };
    esp_wifi_set_config(WIFI_IF_STA,&stacfg);
    //配置ap模式wifi参数
    wifi_config_t apcfg = {
        .ap = {
            .ssid = "esp32-s3",
            .ssid_len = 8,
            .password = "123456789",
            .channel = 12,
            .max_connection = 4,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        }
    };
    esp_wifi_set_config(WIFI_IF_AP,&apcfg);
    //启动wifi
    esp_wifi_start();
    //sta连接目标
    ESP_ERROR_CHECK(esp_wifi_connect());
    //nat地址转换
    esp_netif_napt_enable(apnetif);
    esp_netif_napt_enable(stanetif);
    ESP_LOGI(TAG, "WiFi bridge is running. STA connected to target WiFi, AP sharing internet.");
}
