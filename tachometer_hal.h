/* ***************************************************************** */
/* File name:        tachometer_hal.c                                */
/* File description: File with useful functions for the cooler       */
/* Author name:      douglas_pedro                                   */
/* Creation date:    13may2016                                       */
/* Revision date:    20may2016                                       */
/* ***************************************************************** */

#ifndef SOURCES_TACHOMETER_HAL_H_
#define SOURCES_TACHOMETER_HAL_H_

/* ************************************************ */
/* Method name:        tachometer_init               */
/* Method description: Initialize the tachometer    */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void tachometer_init(void);


/* ***************************************************/
/* Method name:        getSpeed                      */
/* Method description: count the number of           */
//		       interruptions and divide by 7 */
/* Input params:       n/a                           */
/* Output params:       n/a                          */
/* ***************************************************/
long int tachometer_getSpeed(char );

#endif /* SOURCES_TACHOMETER_HAL_H_ */
