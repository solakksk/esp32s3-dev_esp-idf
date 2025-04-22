idf_component_register(SRCS "esp32s3dev.c"
                    INCLUDE_DIRS "."
                    REQUIRES app_update nvs_flash esp_event esp_wifi esp_netif ble_ota)
