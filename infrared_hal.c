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
	int iValue=0;
	for(int i=0; i<30;i++)
	{
		if(i>9)
		iValue =iValue+ adc_getConvertionValue(iSensor);
	}

	infrared_clear(iSensor);
	return iValue/20;
}

int infrared_getOFF(int iSensor)
{
	infrared_clear(iSensor);
	int iValue=0;
	for(int i=0; i<30;i++)
	{
		if(i>9)
		iValue =iValue+ adc_getConvertionValue(iSensor);
	}
	return iValue/20;
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

	if((value1_OFF*2>value1_ON)||(value2_OFF*2>value2_ON)||(value3_OFF*2>value3_ON)||(value4_OFF*2>value4_ON)||(value5_OFF*2>value5_ON)||(value6_OFF*2>value6_ON))
		return 0;
	return 1 ;
}

void infrared_calibration(int *iSensorMax, int *iSensorMin, int *iSensorOffstet)
{
	int i=1, j=0, k;
	while(i<=6){
		iSensorOffstet[i-1]=infrared_getOFF(i);
		i++;
	}

	i=1;
	for(i=1; i<=6; i++){
		k=infrared_getON(i);
		iSensorMax[i-1] = k;
		iSensorMin[i-1] = k;
	}

	while(j<10000){
		for(i=1; i<=6; i++){
			k=infrared_getON(i);
			if(k>iSensorMax[i-1])
				iSensorMax[i-1]=k;
			if(k<iSensorMin[i-1])
				iSensorMin[i-1]=k;
		}
		j++;
	}
	return;
}

float infradred_doSpline(float t, float *fMeasure, int iSensorPosition)
{
	float p0, p1, p2, p3;
	switch (iSensorPosition)
	{
	    case 1:
	    	p0 = fMeasure[0];
	    	p1 = fMeasure[0];
	    	p2 = fMeasure[1];
	    	p3 = fMeasure[2];
	    	break;
	    case 2:
	    	p0 = fMeasure[0];
	    	p1 = fMeasure[1];
	    	p2 = fMeasure[2];
	    	p3 = fMeasure[3];
	    	break;
	    case 3:
	    	p0 = fMeasure[1];
	    	p1 = fMeasure[2];
	    	p2 = fMeasure[3];
	    	p3 = fMeasure[4];
	    	break;
	    case 4:
	    	p0 = fMeasure[2];
	    	p1 = fMeasure[3];
	    	p2 = fMeasure[4];
	    	p3 = fMeasure[5];
	    	break;
	    case 5:
	    	p0 = fMeasure[3];
	    	p1 = fMeasure[4];
	    	p2 = fMeasure[5];
	    	p3 = fMeasure[5];
	    	break;
	}

	return 0.5f * ((2 * p1) +
		                      (p2 - p0) * t +
		                      (2*p0 - 5*p1 + 4*p2 - p3) * t * t +
		                      (3*p1 -p0 - 3 * p2 + p3) * t * t * t);
}

float infradred_getPosition(int *iSensorMax, int *iSensorMin, int *iSensorOffstet)
{
	char linefound=0;
	float fMeasure[6], t, t2, fsignal1, fsignal2=100;
	int i=1, iSensorPosition, min=1, iIntervalos=2;
	while(i<=6){
		fMeasure[i-1]=(float) (infrared_getON(i) - iSensorOffstet[i-1])/(iSensorMax[i-1]-iSensorMin[i-1]);
		if((i!=1)&&(fMeasure[i-1]<fMeasure[min-1]))
			min=i;
		if(fMeasure[i-1]<0.7)
			linefound=1;
		i++;

	}

	if(min==1||min==6) //mínimo nos cantos
		iIntervalos=1;
	if(linefound==1)
	{
		for(; iIntervalos>0; iIntervalos--) //numero de intervalos onde se procurará o mínimo (1 ou 2)
		{
			t=0;
			while(t<=1)
			{
				fsignal1 = infradred_doSpline( t, fMeasure, min);
				if(fsignal1<fsignal2){
					fsignal2=fsignal1;
					t2 = t;
					iSensorPosition = min;
				}
				t=t+0.05;
			}
			min--;
		}
		return (iSensorPosition-1)+t2;
	}
	else
		return -1;
}
