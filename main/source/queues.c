/**
 * @file queues.c
 * @author Diego Felipe Mejia (dmejia@dsd.dev)
 * @brief Queue initialization.
 * @version 0.1
 * @date 2022-11-24
 * 
 * @copyright Copyright (c) 2023
 * 
 * Deepsea Developments 
 * https://www.deepseadev.com/en/
 * 974 Commercial St
 * Suite 108
 * Palo Alto, California 94303, US
 */

/* 

*/

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/sdmmc_host.h"
#include "sdmmc_cmd.h"
#include "esp_vfs_fat.h"
#include <sys/unistd.h>
#include <dirent.h>
#include "queues.h"
#include "common.h"

QueueHandle_t Q_commands;

/**
 * @brief Queues creation function
 * 
 */
void Queues_init()
{
    Q_commands = xQueueCreate( 2, sizeof( comand_color) );
    if(Q_commands == NULL) ESP_LOGE("QUEUES", "Error creating commands queue");
}
