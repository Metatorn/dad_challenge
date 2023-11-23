/**
 * @file common.h
 * @author Diego Felipe Mejia (dmejia@dsd.dev)
 * @brief common file for Types definitions and common includes.
 * @version 0.1
 * @date 2023-07-31
 * 
 * @copyright Copyright (c) 2023
 * 
 * Deepsea Developments 
 * https://www.deepseadev.com/en/
 * 974 Commercial St
 * Suite 108
 * Palo Alto, California 94303, US
 */

#ifndef COMMON_H
#define COMMON_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include <esp_ota_ops.h>
#include "esp_timer.h"
#include "driver/i2c.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "esp_mac.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include <esp_http_server.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h> 
#include <sys/param.h>

#include "queues.h"
#include "semaphores.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#include <unistd.h>

/**
* @brief Definitions of LED's pin and number of LEDs
*/
#define GPIO_STRIP_LED                      GPIO_NUM_17


/**
 * @brief  task memory size definition
 */
#define MEM_UI_TASK                 1024*4 
#define MEM_SERIAL_TASK             512*8

/**
 * @brief  task priority definition
 */
#define PRIOR_UI_TASK				3
#define PRIOR_SERIAL_TASK           4


/**
 * @brief  Debugging Tags definition
 */
#define TAG_UI                      "UI TASK"
#define TAG_SERIAL                  "SERIAL TASK"               


typedef enum
{
    red = 1,
    green,
    blue,
} colour_set;

typedef struct 
{
    colour_set color;
    bool enable;
    uint32_t time;
    uint8_t count;
    uint8_t coord;
}comand_color;

/**
 * @brief  frecuency  enum to set atm90
 * 
 * 50Hz = 0
 * 60Hz  = 1
 */
typedef enum
{
    _50Hz = 0,
    _60Hz   
} frec_set;

#endif