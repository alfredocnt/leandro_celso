/* ***************************************************************** */
/* File name:        adc.c                                 */
/* File description: File with useful functions for analog to digital*/
/* conversions                                                       */
/* Author name:      douglas_pedro_celso                             */
/* Creation date:    16jun2016                                       */
/* Revision date:    16jun2016                                       */
/* ***************************************************************** */

#include "es670_peripheral_board.h"

#define ADC0_SC1A_COCO (ADC0_SC1A >> 7)

/* ************************************************** */
/* Method name: 	   adc_initADCModule              */
/* Method description: configure ADC module           */
/* Input params:	   n/a 							  */
/* Outpu params:	   n/a 							  */
/* ************************************************** */
void adc_initADCModule(void)
{
	/* un-gate port clock*/
	SIM_SCGC6 |= SIM_SCGC6_ADC0(CGC_CLOCK_ENABLED);	//Enable clock for ADC

    /* un-gate port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTB(CGC_CLOCK_ENABLED);
    SIM_SCGC5 |= SIM_SCGC5_PORTC(CGC_CLOCK_ENABLED);
    SIM_SCGC5 |= SIM_SCGC5_PORTE(CGC_CLOCK_ENABLED);


//    /* set pin as ADC In */
//    PORTE_PCR20 |= PORT_PCR_MUX(0);   //Voltage Sensor
    PORTE_PCR21 |= PORT_PCR_MUX(0);   //Temperature Sensor

    PORTB_PCR0 |= PORT_PCR_MUX(0); //receptor 1
    PORTB_PCR1 |= PORT_PCR_MUX(0); //receptor 2
    PORTB_PCR2 |= PORT_PCR_MUX(0); //receptor 3
    PORTB_PCR3 |= PORT_PCR_MUX(0); //receptor 4
    PORTC_PCR1 |= PORT_PCR_MUX(0); //receptor 5
    PORTC_PCR2 |= PORT_PCR_MUX(0); //receptor 6


    ADC0_CFG1 |= (ADC_CFG1_ADICLK(1) | ADC_CFG1_MODE(3) | ADC_CFG1_ADLSMP(0) | ADC_CFG1_ADIV(0) | ADC_CFG1_ADLPC(0));

	/*
	ADC_CFG1_ADICLK(x)// bus/2 clock selection
	ADC_CFG1_MODE(x)  // 16-bit Conversion mode selection
	ADC_CFG1_ADLSMP(x)// Short sample time configuration
	ADC_CFG1_ADIV(x)  // Clock Divide Select (Divide by 1)
	ADC_CFG1_ADLPC(x) // Normal power Configuration
	*/

	ADC0_SC2 |= (ADC_SC2_REFSEL(0) | ADC_SC2_DMAEN(0) | ADC_SC2_ACFE(0) | ADC_SC2_ADTRG(0));

	/*
	ADC_SC2_REFSEL(x)// reference voltage selection - external pins
	ADC_SC2_DMAEN(x) // dma disabled
	ADC_SC2_ACREN(x) // dont care - range function
	ADC_SC2_ACFGT(x) // dont care - 0 -> Less than, 1 -> Greater Than
	ADC_SC2_ACFE(x)  // compare function disabled
	ADC_SC2_ADTRG(x) // When software trigger is selected, a conversion is initiated following a write to SC1A
	ADC_SC2_ADACT(x) // HW-set indicates if a conversion is being held, is cleared when conversion is done
	*/

	ADC0_CFG2 |= (ADC_CFG2_ADLSTS(0) | ADC_CFG2_ADHSC(0) | ADC_CFG2_ADACKEN(0) | ADC_CFG2_MUXSEL(0));

	/*
	ADC_CFG2_ADLSTS(x)  // default time
	ADC_CFG2_ADHSC(x)   // normal conversion sequence
	ADC_CFG2_ADACKEN(x) // disable adack clock
	ADC_CFG2_MUXSEL(x)  // select 'a' channels
	*/

	}


/* ************************************************** */
/* Method name: 	   adc_initConvertion             */
/* Method description: init a conversion from D to A  */
/* Input params:	   n/a 							  */
/* Outpu params:	   n/a 							  */
/* ************************************************** */
void adc_initConvertion(int iChanel) //selecionar canal
{
	ADC0_SC1A = (ADC_SC1_ADCH(iChanel) | ADC_SC1_DIFF(0) | ADC_SC1_AIEN(0));

    /*
    ADC_SC1_COCO(x) // conversion complete flag HW-set
    ADC_SC1_AIEN(x) // conversion complete interrupt disables	
	ADC_SC1_DIFF(x) // selects single-ended convertion
	ADC_SC1_ADCH(x) // selects channel, view 3.7.1.3.1 ADC0 Channel Assignment ADC0_SE4a from datasheet
	*/
}

/* ************************************************** */
/* Method name: 	   adc_isAdcDone                  */
/* Method description: check if conversion is done    */
/* Input params:	   n/a 							  */
/* Outpu params:	   n/a 							  */
/* ************************************************** */
int adc_isAdcDone(void)
{
	if(1 == ADC0_SC1A_COCO) // watch complete convertion flag
	{
		return 1; // if the conversion is complete, return 1
	}
	else
		return 0; // if the conversion is still taking place, return 0

}

/* ************************************************** */
/* Method name: 	   adc_getConvertionValue         */
/* Method description: retrieve converted value       */
/* Input params:	   n/a 							  */
/* Outpu params:	   n/a 							  */
/* ************************************************** */
int adc_getConvertionValue(int iChanel) //mudar para selecionar o canal
{
	switch (iChanel)
	{
	    case 1:
	    	iChanel = 8;
	    	break;
	    case 2:
	    	iChanel = 9;
	    	break;
	    case 3:
	    	iChanel = 12;
	    	break;
	    case 4:
	    	iChanel = 13;
	    	break;
	    case 5:
	    	iChanel = 11;
	    	break;
	    case 6:
	    	iChanel = 15;
//	    case 10:
//	    	 iChanel = 4;
//	    break;
	}
//	if(iChanel!=4)
		adc_initConvertion(iChanel);
	while (!adc_isAdcDone());

	return ADC0_RA; // return the register value that keeps the result of convertion
}
