/* ***************************************************************** */
/* File name:        adc.h                                           */
/* File description: File with useful functions for analog to digital*/
/* conversions                                                       */
/* Author name:      douglas_pedro_celso                             */
/* Creation date:    16jun2016                                       */
/* Revision date:    16jun2016                                       */
/* ***************************************************************** */

/* ************************************************** */
/* Method name: 	   adc_initADCModule              */
/* Method description: configure ADC module           */
/* Input params:	   n/a 							  */
/* Outpu params:	   n/a 							  */
/* ************************************************** */
void adc_initADCModule(void);

/* ************************************************** */
/* Method name: 	   adc_initConvertion             */
/* Method description: init a conversion from D to A  */
/* Input params:	   n/a 							  */
/* Outpu params:	   n/a 							  */
/* ************************************************** */
void adc_initConvertion(int iChanel);

/* ************************************************** */
/* Method name: 	   adc_isAdcDone                  */
/* Method description: check if conversion is done    */
/* Input params:	   n/a 							  */
/* Outpu params:	   n/a 							  */
/* ************************************************** */
int adc_isAdcDone(void);

/* ************************************************** */
/* Method name: 	   adc_getConvertionValue         */
/* Method description: retrieve converted value       */
/* Input params:	   n/a 							  */
/* Outpu params:	   n/a 							  */
/* ************************************************** */
int adc_getConvertionValue(int iChanel);

