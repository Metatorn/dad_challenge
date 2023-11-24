/**
 * @file serial.h
 * @author Diego Felipe Mejia (dmejia@dsd.dev)
 * @brief Serial driver to receive commands.
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
#ifndef SERIAL_H_
#define SERIAL_H_

#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "common.h"
#include "esp_log.h"


#define PIN_TX (GPIO_NUM_1)
#define PIN_RX (GPIO_NUM_3)
#define PIN_RTS (GPIO_NUM_22)
#define PIN_CTS (GPIO_NUM_19)
#define PORT_UART (0)
#define BUF_SIZE (1024)
#define portTICK_RATE_MS 10

void serialProtocol_Init();
/**
* @brief Serial_Init function, start the serial task
*
* @note:
*      The task init the serial driver and start the bidirectional communication with PC
*/
void Serial_Init();


#endif
