/* ***************************************************************** */
/* File name:        timer_counter.h                                 */
/* File description: Header file containing the functions/methods    */
/*                   interfaces for handling the timer               */
/* Author name:      douglas_pedro_celso                             */
/* Creation date:    03jun2016                                       */
/* Revision date:    09jun2016                                       */
/* ***************************************************************** */

/* ************************************************** */
/* Method name: 	   timer_initTPM1AsPWM            */
/* Method description: configure Timer1 to act as PWM */
/* Input params:	   iDutycicle = duty cycle		  */
/* Output params:	   n/a 							  */
/* ************************************************** */
void timer_initTPM1AsPWM(void);


/* ************************************************** */
/* Method name: 	   timer_setDutycycle             */
/* Method description: set duty cycle                 */
/* Input params:	   iDutycicle = duty cycle		  */
/* Output params:	   n/a 							  */
/* ************************************************** */
void timer_setDutycycle(int, char );

/* ************************************************ */
/* Method name:        timer_coolerfan_init         */
/* Method description: Initialize the cooler device */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void timer_coolerfan_init(void);
/* ************************************************ */
/* Method name:        timer_changeHeaterPwm        */
/* Method description: change the cooler pwm        */
/* Input params:       pwm desired (percentage)     */
/* Output params:      n/a                          */
/* ************************************************ */
