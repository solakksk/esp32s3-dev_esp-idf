#include <stdio.h>
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_wifi.h"
void app_main(void)
{
    nvs_flash_init();
    esp_event_loop_delete_default();
    esp_netif_init();
    esp_netif_t* apnetif = esp_netif_create_default_wifi_ap();
    wifi_init_config_t apinitcfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&apinitcfg);
    esp_wifi_set_mode(WIFI_MODE_AP);
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
    esp_wifi_start();
}
