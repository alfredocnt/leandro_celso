/* ***************************************************************** */
/* File name:        tachometer_hal.c                                */
/* File description: File with useful functions for the cooler       */
/* Author name:      douglas_pedro                                   */
/* Creation date:    13may2016                                       */
/* Revision date:    20may2016                                       */
/* ***************************************************************** */


#include "tachometer_hal.h"
#include "es670_peripheral_board.h"



/* ************************************************ */
/* Method name:        tachometer_init               */
/* Method description: Initialize the tachometer    */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void tachometer_init(void){

    SIM_SCGC5 |= SIM_SCGC5_PORTA(CGC_CLOCK_ENABLED);
	SIM_SCGC6 |= SIM_SCGC6_TPM0(CGC_CLOCK_ENABLED);
	SIM_SCGC6 |= SIM_SCGC6_TPM2(CGC_CLOCK_ENABLED);
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(0x02); //10 OSCERCLK clock
	SIM_SOPT4 |= SIM_SOPT4_TPM0CLKSEL(0); //0 TPM0 external clock driven by TPM_CLKIN0 pin, 1 TPM0 external clock driven by TPM_CLKIN1 pin.

	SIM_SOPT4 |= SIM_SOPT4_TPM2CLKSEL(0); //0 TPM2 external clock driven by TPM_CLKIN0 pin.

	//SIM_SCGC6 |= SIM_SCGC6_RTC(1);
	TPM0_SC |= TPM_SC_CMOD(0x2);//10 LPTPM counter increments on rising edge of LPTPM_EXTCLK synchronized to the LPTPM counter clock
	TPM0_SC |= TPM_SC_PS(0); //000 Divide by 1

	TPM2_SC |= TPM_SC_CMOD(0x2);//10 LPTPM counter increments on rising edge of LPTPM_EXTCLK synchronized to the LPTPM counter clock
	TPM2_SC |= TPM_SC_PS(0); //000 Divide by 1

	SIM_SCGC5 |= SIM_SCGC5_PORTE(CGC_CLOCK_ENABLED); // Tacometro
	PORTE_PCR29 |= PORT_PCR_MUX(TACHOMETER_ALT);
	PORTE_PCR30 |= PORT_PCR_MUX(TACHOMETER_ALT);

	//initiate emitters
    PORTA_PCR16 = PORT_PCR_MUX(ENCODER_ALT);
    PORTA_PCR17 = PORT_PCR_MUX(ENCODER_ALT);
    GPIOA_PDDR |= GPIO_PDDR_PDD(1<<ENCODERD_PIN);
    GPIOA_PDDR |= GPIO_PDDR_PDD(1<<ENCODERE_PIN);

    GPIOA_PCOR = GPIO_PCOR_PTCO( (0x01U << ENCODERD_PIN) ); //Deixa a porta em nível baixo,fazendo o emissor emitir
    GPIOA_PCOR = GPIO_PCOR_PTCO( (0x01U << ENCODERE_PIN) );

//	TPM0_CONF |= TPM0_CONF_DBGMODE(0b11); //11 LPTPM counter continues in debug mode.
//	TPM2_CONF |= TPM0_CONF_DBGMODE(0b11);

}

/* ***************************************************/
/* Method name:        tachometer_getSpeed            */
/* Method description: count the number of           */
//		       interruptions and divide by 7 */
/* Input params:       n/a                           */
/* Output params:       n/a                          */
/* ***************************************************/
//Considering cyclic executive period equal 1 second, the number of
// interruptions divided by 7 is the speed in rps 
long int tachometer_getSpeed(char cSide){
	long int liCounterValue;
	switch (cSide)
	{
	    case 'D':
	    	liCounterValue = TPM2_CNT;
	    	TPM2_CNT=0;
	    	break;
	    case 'E':
	    	liCounterValue = TPM0_CNT;
	    	TPM0_CNT=0;
	    	break;
	}
	return liCounterValue; //Verificar quatidade de furos
}

