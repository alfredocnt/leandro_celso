/* ***************************************************************** */
/* File name:        buzzer_hal.c                                    */
/* File description: File dedicated to the hardware abstraction layer*/
/*                   related buzzer from the peripheral board        */
/* Author name:      dloubach                                        */
/* Creation date:    12jan2016                                       */
/* Revision date:    25fev2016                                       */
/* ***************************************************************** */

#include "infrared_hal.h"
#include "es670_peripheral_board.h"
#include "adc.h"

/* ************************************************ */
/* Method name:        buzzer_init                  */
/* Method description: Initialize the buzzer device */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void infrared_init(void)
{
    /* un-gate port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTC(CGC_CLOCK_ENABLED);

    /* set pin as gpio */
    PORTC_PCR6 |= PORT_PCR_MUX(INFRARED_ALT1);
    PORTC_PCR5 |= PORT_PCR_MUX(INFRARED_ALT2);
    PORTC_PCR4 |= PORT_PCR_MUX(INFRARED_ALT3);
    PORTC_PCR3 |= PORT_PCR_MUX(INFRARED_ALT4);
    PORTC_PCR0 |= PORT_PCR_MUX(INFRARED_ALT5);
    PORTC_PCR7 |= PORT_PCR_MUX(INFRARED_ALT6);

    GPIOC_PDDR |= GPIO_PDDR_PDD(1 << INFRARED_PIN1);
    GPIOC_PDDR |= GPIO_PDDR_PDD(1 << INFRARED_PIN2);
    GPIOC_PDDR |= GPIO_PDDR_PDD(1 << INFRARED_PIN3);
    GPIOC_PDDR |= GPIO_PDDR_PDD(1 << INFRARED_PIN4);
    GPIOC_PDDR |= GPIO_PDDR_PDD(1 << INFRARED_PIN5);
    GPIOC_PDDR |= GPIO_PDDR_PDD(1 << INFRARED_PIN6);

    /* set pin PTB0 and PTB1 as digital outputs */
   // GPIOB_PDDR |= GPIO_PDDR_PDD(3);
    infrared_clear(1);
    infrared_clear(2);
    infrared_clear(3);
    infrared_clear(4);
    infrared_clear(5);
    infrared_clear(6);

}

void infrared_clear(int iSensor)
{
	switch (iSensor)
	{
	    case 1:
	    	GPIOC_PSOR |= 0b1000000;
	    	break;
	    case 2:
	    	GPIOC_PSOR |= 0b100000;
	    	break;
	    case 3:
	    	GPIOC_PSOR |= 0b10000;
	    	break;
	    case 4:
	    	GPIOC_PSOR |= 0b1000;
		    break;
	    case 5:
	    	GPIOC_PSOR |= 0b1;
		    break;
	    case 6:
	    	GPIOC_PSOR |= 0b10000000;
		    break;
	    break;
	}
    /* clear desired led */

}

void infrared_set(int iSensor)
{
	switch (iSensor)
	{
	    case 1:
	    	GPIOC_PCOR |= 0b1000000;
	    	break;
	    case 2:
	    	GPIOC_PCOR |= 0b100000;
	    	break;
	    case 3:
	    	GPIOC_PCOR |= 0b10000;
	    	break;
	    case 4:
	    	GPIOC_PCOR |= 0b1000;
	    	break;
	    case 5:
	    	GPIOC_PCOR |= 0b1;
	    	break;
	    case 6:
	    	GPIOC_PCOR |= 0b10000000;
	    break;
	}
}

int infrared_getON(int iSensor)
{
	infrared_set(iSensor);
	int iValue;
	for(int i=0; i<10000;i++)
		iValue = adc_getConvertionValue(iSensor);
	infrared_clear(iSensor);
	return iValue;
}

int infrared_getOFF(int iSensor)
{
	infrared_clear(iSensor);
	int iValue;
	for(int i=0; i<100;i++)
		iValue = adc_getConvertionValue(iSensor);
	return adc_getConvertionValue(iSensor);
}

int infrared_test()
{
	int value1_ON, value1_OFF, value2_ON, value2_OFF, value3_ON, value3_OFF, value4_ON, value4_OFF, value5_ON, value5_OFF, value6_ON, value6_OFF;
//	int value1_OFF;

	value6_OFF = infrared_getOFF(6);
	value6_ON = infrared_getON(6);

	value1_OFF = infrared_getOFF(1);
	value1_ON = infrared_getON(1);

	value5_OFF = infrared_getOFF(5);
	value5_ON = infrared_getON(5);

	value2_OFF = infrared_getOFF(2);
	value2_ON = infrared_getON(2);

	value4_OFF = infrared_getOFF(4);
	value4_ON = infrared_getON(4);

	value3_OFF = infrared_getOFF(3);
	value3_ON = infrared_getON(3);

	if((value1_OFF*5>value1_OFF)||(value2_OFF*5>value2_OFF)||(value3_OFF*5>value3_OFF)||(value4_OFF*5>value4_OFF)||(value5_OFF*5>value5_OFF)||(value6_OFF*5>value6_OFF))
		return 0;
		return 1 ;
}


