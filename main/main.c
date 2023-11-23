/**
 * @file main.c
 * @author Diego Felipe Mejia (dmejia@dsd.dev)
 * @brief SEOS node, act like remote point of energy measurement.
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
#include "common.h"
#include "ui.h"
#include "nvs_flash.h"
#include "nvs.h"


void app_main(void)
{
    
    ESP_ERROR_CHECK(nvs_flash_init());
    /* hardware related and device init */
    Queues_init();
    UI_Init(); 
    
}
