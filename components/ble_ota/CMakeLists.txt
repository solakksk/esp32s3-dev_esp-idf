file(GLOB_RECURSE srcs "ble_ota.c" "src/*.c")
idf_component_register(SRCS "${srcs}" INCLUDE_DIRS "." "./inc" REQUIRES bt esp_ringbuf app_update)