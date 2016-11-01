/* ***************************************************************** */
/* File name:        es670.c                                         */
/* File description: File dedicated to the ES670 prototype projects  */
/*                   involving the FRDM-KL25Z board together with is */
/*                   daughter board containing more peripherals      */
/*                                                                   */
/*                   Processor MKL25Z128VLK4 characteristics         */
/*                   48 MHz ARM Cortex-M0+ core                      */
/*                   128 KB program flash memory                     */
/*                   16 KB SRAM                                      */
/*                   Voltage range: 1.71 to 3.6 V                    */
/*                                                                   */
/* Author name:      douglas_pedro_celso                              */
/* Creation date:    13may2015                                       */
/* Revision date:    09jun2016                                       */
/* ***************************************************************** */

/* our includes */
#include "es670_peripheral_board.h"
#include "motor_hal.h"
//#include "ledrgb_hal.h"
#include "mcg_hal.h"
#include "tc_hal.h"
#include "debugUart.h"
#include "util.h"
#include "timer_counter.h"
#include "tachometer_hal.h"
#include "infrared_hal.h"


/* system includes */
#include "fsl_debug_console.h"

// defines *
#define CYCLIC_EXECUTIVE_PERIOD         100 * 10000 /* 10 seconds */
//#define CYCLIC_EXECUTIVE_PERIOD         100 * 10000 /* 1000000 micro seconds */


/* globals */
volatile unsigned int uiFlagNextPeriod = 0;         /* cyclic executive flag */

char speed[100];

char temperature[100];

/* ************************************************ */
/* Method name:        main_boardInit()             */
/* Method description: system entry point           */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void main_boardInit(){
 	infrared_init();
 	autoteste_init();
	mcg_clockInit();
	motor_init();
	tachometer_init();
	timer_initTPM1AsPWM();
    timer_coolerfan_init();
    adc_initADCModule();
}

/* ************************************************ */
/* Method name:        main_cyclicExecuteIsr        */
/* Method description: cyclic executive interrupt   */
/*                     service routine              */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void main_cyclicExecuteIsr(void)
{
    /* set the cyclic executive flag */
    uiFlagNextPeriod = 1;
}
//void main_cyclicExecuteIsr(void)
//{
//    /* set the cyclic executive flag */
//    uiFlagNextPeriod = 1;
//   tachometer_getSpeed(speed);
//    // clear LCD
//    lcd_sendCommand(CMD_CLEAR);
//    // set the cursor line 0, column 1
//    lcd_setCursor(0,1);
//    // send string
//    lcd_writeString("The speed is:");
//    // set the cursor line 1, column 0
//    lcd_setCursor(1,0);
//    // write the speed
//   // lcd_writeString(speed);
//    tachometer_resetCounter();
////
////    if(adc_isAdcDone()){
////        	sprintf(temperature,"%d",adc_getConvertionValue(10));
////    }
//    lcd_writeString(speed);
//   // adc_initConvertion(4);
//}


/* ************************************************ */
/* Method name:        main                         */
/* Method description: system entry point           */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
int main(void)
{
	long int liSpeedD, liSpeedE;
	int i=0,iSensorMax[6], iSensorMin[6], iSensorOffstet[6];
	float fPosition;

    /* board initializations */
    main_boardInit();

   	infrared_calibration(iSensorMax,iSensorMin,iSensorOffstet);

    while(i<100)
    {
    	fPosition = infradred_getPosition(iSensorMax,iSensorMin,iSensorOffstet);
    	i++;
    }

    if(motor_test()==0 || infrared_test()==0 )
		autoteste_setAutoteste();


    tc_installLptmr0(CYCLIC_EXECUTIVE_PERIOD, main_cyclicExecuteIsr);
    while(1U){

    	liSpeedD = tachometer_getSpeed('D');
    	liSpeedE = tachometer_getSpeed('E');
    	 /* WAIT FOR CYCLIC EXECUTIVE PERIOD */
    	while(!uiFlagNextPeriod) {
    	}
    	uiFlagNextPeriod = 0;
    }

    /* Never leave main */
    return 0;
}
