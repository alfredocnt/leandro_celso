/* ***************************************************************** */
/* File name:        timer_counter.c                                 */
/* File description: File with useful functions for the timer to be  */
/*                                           initialazed as a PWM     */
/* Author name:      douglas_pedro_celso                             */
/* Creation date:    03jun2016                                       */
/* Revision date:    09jun2016                                       */
/* ***************************************************************** */

#include "timer_counter.h"
#include "es670_peripheral_board.h"
#include "fsl_tpm_hal.h"

/* ************************************************** */
/* Method name: 	   timer_initTPM1AsPWM            */
/* Method description: configure Timer1 to act as PWM */
/* Input params:	   n/a                      	  */
/* Output params:	   n/a 							  */
/* ************************************************** */
void timer_initTPM1AsPWM(void)
{
	/* un-gate port clock*/
	SIM_SCGC6 |= SIM_SCGC6_TPM1(CGC_CLOCK_ENABLED); //Enable clock for TPM1
	TPM1_SC |= TPM_SC_CPWMS(0);   //up counting mode
	TPM1_SC |= TPM_SC_CMOD(1);   //LPTPM Counter increments on every LPTPM counter clock
	TPM1_SC |= TPM_SC_PS(0);   //Prescale 1:1
	TPM1_C1SC |= (TPM_CnSC_MSB(1) | TPM_CnSC_MSA(0) | TPM_CnSC_ELSB(1) | TPM_CnSC_ELSA(0) );
	TPM1_C0SC |= (TPM_CnSC_MSB(0b1) | TPM_CnSC_MSA(0b0) | TPM_CnSC_ELSB(0b1) | TPM_CnSC_ELSA(0b0));
	TPM1_C0V = 0x00; //PWM 00%
	TPM1_C1V = 0x00; //PWM 00%
	TPM1_CNT = 0;
	TPM1_MOD = 0x64;
}

/* ************************************************** */
/* Method name: 	   timer_setDutycycle             */
/* Method description: set duty cycle                 */
/* Input params:	   iDutycicle = duty cycle		  */
/* Output params:	   n/a 							  */
/* ************************************************** */
void timer_setDutycycle(int iDutyCycle, char cMotorSide){
	switch (cMotorSide)
	{
	    case 'E':
	    	TPM1_C1V = iDutyCycle;
	    	break;
	    case 'D':
	    	TPM1_C0V = iDutyCycle;
	    	break;
	    break;
	}
}

/* ************************************************ */
/* Method name:        timer_coolerfan_init         */
/* Method description: Initialize the cooler device */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void timer_coolerfan_init(void)
{
    /* un-gate port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTA(CGC_CLOCK_ENABLED);
    /* set pin as PWM */
    PORTA_PCR13 |= PORT_PCR_MUX(0x3u);
    PORTA_PCR12 |= PORT_PCR_MUX(0x03);
}

