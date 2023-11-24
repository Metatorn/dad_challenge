/**
 * @file ui.h
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

#pragma once
#ifndef LED_DEBUG_H_
#define LED_DEBUG_H_

#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "common.h"
#include "esp_log.h"
#include "led_strip.h"

/**
* @brief Definitions of LED's pin and number of LEDs
*/
#define CONFIG_STRIP_LED_GPIO   17
#define CONFIG_STRIP_LED_NUMBER 16

/**
* @brief LED Intervals to change the colors
*/
#define POWER       0xFF


/**
* @brief UI_Init function, start the UI task
*
* @note:
*      The task init the LED RGB strip driver and start the rainbow effect automatically
*/
void UI_Init();

/**
* @brief LED_Set_Colour, set the colour of the RGB led.
* @param[in] color RGB LED that will be chosen to light.
* @param[in] time time to flash.
* @param[in] count times it will flash. 
* @param[in] type type notification error=1, warning=0. 
* @return void
*/
void UI_Set_Colour(uint8_t _color, bool enable, uint32_t _time, uint8_t _count);


#endif
