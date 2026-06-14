#include <stdio.h>
#include <string.h>
#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define UART_NUM UART_NUM_0
#define UART_TX_PIN 1
#define UART_RX_PIN 3
#define UART_BAUD_RATE 115200
#define BUF_SIZE 256

void app_main(void)
{
    // Configure UART
    uart_config_t uart_config = {
        .baud_rate = UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };

    // Install UART driver
    uart_driver_install(UART_NUM, BUF_SIZE, BUF_SIZE, 0, NULL, 0);
    uart_param_config(UART_NUM, &uart_config);
    uart_set_pin(UART_NUM, UART_TX_PIN, UART_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    printf("ESP32 UART Echo Firmware Started\n");
    printf("Ready to echo characters...\n");

    // Echo loop
    uint8_t data[BUF_SIZE];
    while (1) {
        // Read data from UART
        int len = uart_read_bytes(UART_NUM, data, BUF_SIZE - 1, pdMS_TO_TICKS(100));
        
        if (len > 0) {
            // Echo the received data back
            uart_write_bytes(UART_NUM, (const char *)data, len);
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
