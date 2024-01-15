/**
 * @file ui.c
 * @author Diego Felipe Mejia (dmejia@dsd.dev)
 * @brief Queue initialization.
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
 */

#include "ui.h"

static const char *TAG = TAG_UI;

extern QueueHandle_t Q_commands;

/**
 * @brief Led handle
 */
static led_strip_handle_t s_led_strip;

/**
 * @brief Led colors definition
 */
int16_t s_red = 0, s_green = 0, s_blue = 0;

uint32_t tempColor=0;
uint8_t countColor=0;
bool isRed, isGreen, isBlue, isYellow;

/**
 * @brief Light Driver Init
 */
void light_driver_init()
{
    led_strip_config_t led_strip_conf = {
        .max_leds = CONFIG_STRIP_LED_NUMBER,
        .strip_gpio_num = CONFIG_STRIP_LED_GPIO,
    };
    led_strip_rmt_config_t rmt_conf = {
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
    };
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&led_strip_conf, &rmt_conf, &s_led_strip));
}

/**
 * @brief UI task
 * 
 * @param pvParameters
 */
void UI_Task(void* pvParameters){ 
    command_color msg_color;
    ESP_LOGI("UI TASK", "UI task Started");
    light_driver_init();
    int index = 0;
    uint8_t matrix[4][16]; //matrix [enable][period]
    while(1){
        if(xQueueReceive(Q_commands, &msg_color , pdMS_TO_TICKS(1) ) == pdTRUE){
            msg_color.color = red;
            ESP_LOGW(TAG, "LED message received: %d, %d, %ld, %d, %d", msg_color.color, msg_color.enable, msg_color.time, msg_color.count, msg_color.coord);
            matrix[0][msg_color.coord]=msg_color.enable;
            matrix[1][msg_color.coord]=msg_color.time;
            matrix[2][msg_color.coord]= 0; //Counter blink
            matrix[3][msg_color.coord]= 1; //Temporal blink status
        }
        for(index=0;index<16;index++){
            if(matrix[2][index]){ //is enabled?
                matrix[2][index]++; //increase counter
                if(matrix[2][index]>matrix[1][index]){ //counter LED > LED period?
                    matrix[2][index]=0;
                    matrix[3][index]=~matrix[3][index]; //switch status if enabled
                }
            }
            else{
                matrix[3][index]=0;
            }
            ESP_ERROR_CHECK(led_strip_set_pixel(s_led_strip, index, 255*matrix[3][index], 0, 0));
            ESP_ERROR_CHECK(led_strip_refresh(s_led_strip)); 
        }
        vTaskDelay(pdMS_TO_TICKS(tempColor));
    }

}

/**
 * @brief UI init task function
 * 
 * @param arg 
 */
void UI_Init(void){
    ESP_LOGI(TAG, "creating UI Debugging task");
    isRed = isGreen = isBlue = false;
    tempColor = 500;
    countColor = 1;
    if(xTaskCreate(UI_Task,                //function pointer that creates the task
                   "UI Task",              //ASCII Task name, only for human recognition
                   MEM_UI_TASK,           //task size (WORD)
                   (void*)NULL,                     //init parameters
                   PRIOR_UI_TASK,       //task priority
                   NULL)!= pdPASS)   //task handler
    {
        for(;;){
            ESP_LOGE(TAG, "error starting UI task");
        } //should no enter here
    }  
}

