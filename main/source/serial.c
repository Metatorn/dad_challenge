/**
 * @file serial.c
 * @author Diego Mejia
 * @brief serial driver.
 * @version 0.1
 * @date 2023-11-23
 * 
 * @copyright Copyright (c) 2023
 * 
 * Deepsea Developments 
 * https://www.deepseadev.com/en/
 * 974 Commercial St
 * Suite 108
 * Palo Alto, California 94303, US
 * 
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "freertos/semphr.h"
#include "serial.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "string.h"
#include "driver/gpio.h"
#include "common.h"

extern QueueHandle_t Q_Command;

static const char *TASK_SERIAL = "SERIAL";
/**
 * @brief serial protocol recive data function
 * 
 * @param arg 
 */
void serialProtocol(){
    ESP_LOGI(TASK_SERIAL, "task_serial Started");
    int index = 0;
    const char delimiters[6] = {' ','[',']','\r','\n'};
    uint8_t* data = (uint8_t*) malloc(BUF_SIZE+1);
    uint8_t endString = pdFALSE;
    char* token = 0;
    char* pointer = 0;

    while (1) {
        
        if(endString==pdFALSE){
            int rxBytes = uart_read_bytes(PORT_UART, data+index, BUF_SIZE, 100 / portTICK_RATE_MS);
            if(rxBytes>0){
                index += rxBytes;
                uart_write_bytes(PORT_UART, (const char*)data, index);
                pointer= strchr((const char*)data,'\n');
                /*if(*pointer == '\n'){
                    ESP_LOGI(TASK_SERIAL, "command received");
                    endString = pdTRUE;
                }*/
            }
            
        }
        else{
            token = strtok((char*)data,delimiters);
            if(!strcmp(token,"BLINK")){
                token =strtok(NULL,delimiters);

                ESP_LOGI(TASK_SERIAL, "OK");
            }
            else{
                ESP_LOGI(TASK_SERIAL, "ERROR");
            }
            endString = pdFALSE;
        }
        vTaskDelay(pdMS_TO_TICKS(10));        
    }
    free(data);

}

/**
 * @brief serial protocol init
 * 
 * @param arg 
 */
void Serial_Init(){
    /* Configura  los parametros para UART0 */
    uart_config_t uart_config = {
        .baud_rate=115200,
        .data_bits= UART_DATA_8_BITS,
        .parity=UART_PARITY_DISABLE,
        .stop_bits= UART_STOP_BITS_1,
        .flow_ctrl=UART_HW_FLOWCTRL_DISABLE,         
    };
    int intr_alloc_flags = 0;
    //uart1
    ESP_ERROR_CHECK(uart_param_config(PORT_UART, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(PORT_UART, PIN_TX, PIN_RX, PIN_RTS, PIN_CTS));
    ESP_ERROR_CHECK(uart_driver_install(PORT_UART, BUF_SIZE * 2, 0, 0, NULL, intr_alloc_flags));
 

    if(xTaskCreate(serialProtocol,                //function pointer that creates the task
                   "serialProtocol",              //ASCII Task name, only for human recognition
                   MEM_SERIAL_TASK,               //task size (WORD)
                   (void*)NULL,                   //init parameters
                   PRIOR_SERIAL_TASK,             //task priority
                   NULL)!= pdPASS)                //task handler
    {
        for(;;){
            ESP_LOGE(TASK_SERIAL, "error starting serialProtocol");
        } //should no enter here
    }
}
