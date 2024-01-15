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

extern QueueHandle_t Q_commands;

static const char *TASK_SERIAL = "SERIAL";
/**
 * @brief serial protocol recive data function
 * 
 * @param arg 
 */
void serialProtocol(){
    ESP_LOGI(TASK_SERIAL, "task_serial Started");
    const char delimiters[5] = {'[',']','\r','\n'};
    const char command[] = {"BLINK"};
    uint8_t* data = (uint8_t*) malloc(BUF_SIZE+1);
    uint8_t endString = pdFALSE;
    char* token = 0;
    char* pointer = 0;
    int index = 0;
    uint8_t row, column, period;
    command_color parameter;

    while (1) {
        
        if(endString==pdFALSE){
            int rxBytes = uart_read_bytes(PORT_UART, data, BUF_SIZE, 100 / portTICK_RATE_MS);
            if(rxBytes>0){
                data[rxBytes] = 0;
                uart_write_bytes(PORT_UART, (const char*)data, strlen((char*)data)); //echo
                for(index=0;index<BUF_SIZE;index++){
                    if( (data[index]=='\n') || (data[index]=='\r')){
                        endString = pdTRUE;
                        break;
                    }
                }
            }
        }
        else{
            //ESP_LOGI(TASK_SERIAL, "VALID STRING RECEIVED");
            pointer = strstr((char*)data, command); //find command in string entered
            if(pointer != NULL){
                //command found
                token = strtok((char*)data,delimiters);
                if(!strcmp(token,"BLINK ")){ //revalidation of command
                    token =strtok(NULL,delimiters); // find ] first row   
                    row = atoi(token);
                    token =strtok(NULL,delimiters); // find ] and column   
                    column = atoi(token);
                    token =strtok(NULL,delimiters); // find period
                    period = atoi(token);
                    parameter.coord = column+(row*4);
                    parameter.time = period;
                    parameter.enable = pdTRUE;
                    //ESP_LOGI(TASK_SERIAL, "Row %d Column %d Period %d", row, column, period);
                    xQueueSend(Q_commands, (void*)&parameter, pdMS_TO_TICKS(10));
                    ESP_LOGI(TASK_SERIAL, "OK");
                }
                else{
                    ESP_LOGI(TASK_SERIAL, "ERROR");
                }
            }
            else{
                ESP_LOGI(TASK_SERIAL, "BAD COMMAND");
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
