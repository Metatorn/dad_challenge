/**
 * @file queues.h
 * @author Diego Felipe Mejia (dmejia@dsd.dev)
 * @brief Queue management header.
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
 * 1) Always configure a QueueHandle to manage the queues. That´s made with the following line: xQueueHandle NAME_OF_QUEUE
 * 2) To create a Queue develop the next code inside Queues_init() function: NAME_OF_QUEUE = xQueueCreate(Lenght of queue, sizeof(STRUCT_OF_QUEUE OR DATA TYPE));
 * 
 */

#pragma once
#include <string.h>
#include <ctype.h>

void Queues_init();
