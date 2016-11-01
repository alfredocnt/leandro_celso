/* ***************************************************************** */
/* File name:        buzzer_hal.c                                    */
/* File description: File dedicated to the hardware abstraction layer*/
/*                   related buzzer from the peripheral board        */
/* Author name:      dloubach                                        */
/* Creation date:    12jan2016                                       */
/* Revision date:    25fev2016                                       */
/* ***************************************************************** */



void infrared_init(void);
void infrared_clear(int iSensor);
void infrared_set(int iSensor);
int infrared_getON(int iSensor);
int infrared_getOFF(int iSensor);
