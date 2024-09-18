/*
 * Copyright 2016-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    01_antirebote.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

#define USER_BUTTON 4
#define TransAno1 8
#define TransAno2 9

int pines [6] = {11, 10, 6, 14, 0};



/*
 * @brief   Application entry point.
 */
int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    gpio_pin_config_t config_segments = {kGPIO_DigitalOutput, 1};
    gpio_pin_config_t config_button = {kGPIO_DigitalInput, 0};

    GPIO_PortInit(GPIO, 0);
    GPIO_PinInit(GPIO, 0, USER_BUTTON, &config_button);
    GPIO_PinInit(GPIO, 0, TransAno1, &config_segments);
    GPIO_PinInit(GPIO, 0, TransAno2, &config_segments);
    for(int i= 0 ; i<=6; i++){

        GPIO_PinInit(GPIO, 0, pines[i], &config_segments);

    }
    

    while (1)
    {

        GPIO_PinWrite(GPIO, 0, TransAno1, 0);
        GPIO_PinWrite(GPIO, 0, TransAno2, 0);

        if(!GPIO_PinRead(GPIO, 0, USER_BUTTON))
        {
            for (int a = 0; a <=6; a++)
            {
                GPIO_PinWrite(GPIO, 0, pines[a], 0);
                for (int b =0 ; b < 500000 ; b++){};
                
            }
            
        }
        else
        {
            for (int a = 0; a <=6; a++)
            {
                GPIO_PinWrite(GPIO, 0, pines[a], 1);
            }
        }

    }


    return 0 ;
}
