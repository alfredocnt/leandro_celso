/* ***************************************************************** */
/* File name:        buzzer_hal.c                                    */
/* File description: File dedicated to the hardware abstraction layer*/
/*                   related buzzer from the peripheral board        */
/* Author name:      dloubach                                        */
/* Creation date:    12jan2016                                       */
/* Revision date:    25fev2016                                       */
/* ***************************************************************** */



void infrared_init(void);
void infrared_clear(int );
void infrared_set(int );
int infrared_getON(int );
int infrared_getOFF(int );
int infrared_test(void);
void infrared_calibration(int* , int* , int* );
float infradred_getPosition(int *, int *, int *);
float infradred_doSpline(float, float *, int);
