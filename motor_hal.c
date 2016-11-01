/* ***************************************************************** */
/* File name:        buzzer_hal.c                                    */
/* File description: File dedicated to the hardware abstraction layer*/
/*                   related buzzer from the peripheral board        */
/* Author name:      dloubach                                        */
/* Creation date:    12jan2016                                       */
/* Revision date:    25fev2016                                       */
/* ***************************************************************** */

#include "motor_hal.h"
#include "util.h"
#include "timer_counter.h"
#include "es670_peripheral_board.h"

/* ************************************************ */
/* Method name:        buzzer_init                  */
/* Method description: Initialize the buzzer device */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void motor_init(void)
{
    /* un-gate port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTB(CGC_CLOCK_ENABLED);

    /* set pin as gpio */
    PORTB_PCR8 |= PORT_PCR_MUX(ENABLEDH_ALT);
    PORTB_PCR9 |= PORT_PCR_MUX(ENABLEDAH_ALT);
    PORTB_PCR10 |= PORT_PCR_MUX(ENABLEEH_ALT);
    PORTB_PCR11 |= PORT_PCR_MUX(ENABLEEAH_ALT);


    /* set pin as digital output */
    GPIOB_PDDR |= GPIO_PDDR_PDD(1 << ENABLEDH_PIN);
    GPIOB_PDDR |= GPIO_PDDR_PDD(1 << ENABLEDAH_PIN);
    GPIOB_PDDR |= GPIO_PDDR_PDD(1 << ENABLEEH_PIN);
    GPIOB_PDDR |= GPIO_PDDR_PDD(1 << ENABLEEAH_PIN);
}



/* ************************************************ */
/* Method name:        buzzer_clearBuzz             */
/* Method description: Clear the buzzer             */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void motor_clearBuzz(void)
{
    /* clear desired led */
    GPIOB_PCOR = GPIO_PCOR_PTCO( (0x01U << ENABLEDH_PIN) );
    GPIOB_PCOR = GPIO_PCOR_PTCO( (0x01U << ENABLEDAH_PIN) );
    GPIOB_PCOR = GPIO_PCOR_PTCO( (0x01U << ENABLEEH_PIN) );
    GPIOB_PCOR = GPIO_PCOR_PTCO( (0x01U << ENABLEEAH_PIN) );

}



/* ************************************************ */
/* Method name:        buzzer_setBuz                */
/* Method description: Set the buzzer               */
/* Input params:       n/a                          */
/* Output params:       n/a                         */
/* ************************************************ */
void motor_setBuzz(char cSentido)
{
	switch (cSentido)
	{
	    case 'H':
	    	GPIOB_PSOR = GPIO_PSOR_PTSO( (0x01U << ENABLEDH_PIN) );
	    	GPIOB_PSOR = GPIO_PSOR_PTSO( (0x01U << ENABLEEH_PIN) );
	    	break;
	    case 'A':
	    	GPIOB_PSOR = GPIO_PSOR_PTSO( (0x01U << ENABLEDAH_PIN) );
	    	GPIOB_PSOR = GPIO_PSOR_PTSO( (0x01U << ENABLEEAH_PIN) );
	    	break;
	}

}

int motor_test(void){
	   motor_setBuzz('H');
	   int i=0;
	   int long MD_OFF, MD_ON, ME_OFF, ME_ON;
	   TPM2_CNT=0;
	   TPM0_CNT=0;


	   for(i=0; i<50; i++)
	   util_genDelay10ms();
	   MD_OFF = TPM2_CNT;
	   ME_OFF = TPM0_CNT;

	   TPM2_CNT=0;
	   TPM0_CNT=0;


		timer_setDutycycle(100, 'D');
	    timer_setDutycycle(100, 'E');

		   for(i=0; i<50; i++)
		   util_genDelay10ms();
		   MD_ON = TPM2_CNT;
		   ME_ON = TPM0_CNT;

		   TPM2_CNT=0;
		   TPM0_CNT=0;
		   timer_setDutycycle(0, 'D');
		   timer_setDutycycle(0, 'E');
		   if((MD_ON>MD_OFF)&&(ME_ON>ME_OFF))
			   	  return 1;
		   return 0;
}
