/* ***************************************************************** */
/* File name:        buzzer_hal.c                                    */
/* File description: File dedicated to the hardware abstraction layer*/
/*                   related buzzer from the peripheral board        */
/* Author name:      dloubach                                        */
/* Creation date:    12jan2016                                       */
/* Revision date:    25fev2016                                       */
/* ***************************************************************** */

#include "autoteste_hal.h"
#include "es670_peripheral_board.h"

/* ************************************************ */
/* Method name:        buzzer_init                  */
/* Method description: Initialize the buzzer device */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void autoteste_init(void)
{
    /* un-gate port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTE(CGC_CLOCK_ENABLED);

    /* set pin as gpio */
    PORTE_PCR2 |= PORT_PCR_MUX(LED_ALT);

    /* set pin as digital output */
    GPIOE_PDDR |= GPIO_PDDR_PDD(1 << LED_PIN);
}



/* ************************************************ */
/* Method name:        buzzer_clearBuzz             */
/* Method description: Clear the buzzer             */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void autoteste_clearAutoteste(void)
{
    /* clear desired led */
    GPIOE_PCOR = GPIO_PCOR_PTCO( (0x01U << LED_PIN) );
}



/* ************************************************ */
/* Method name:        buzzer_setBuz                */
/* Method description: Set the buzzer               */
/* Input params:       n/a                          */
/* Output params:       n/a                         */
/* ************************************************ */
void autoteste_setAutoteste(void)
{

	    GPIOE_PSOR = GPIO_PSOR_PTSO( (0x01U << LED_PIN) );
}
