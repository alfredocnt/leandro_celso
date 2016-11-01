/* ***************************************************************** */
/* File name:        es670_peripheral_board.h                        */
/* File description: Header file containing the peripherals mapping  */
/*                     of the peripheral board for the ES670 hardware*/
/* Author name:      dloubach                                        */
/* Creation date:    16out2015                                       */
/* Revision date:    25fev2016                                       */
/* ***************************************************************** */

#ifndef SOURCES_ES670_PERIPHERAL_BOARD_H_
#define SOURCES_ES670_PERIPHERAL_BOARD_H_

/* system includes */
#include <MKL25Z4.h>

/*                 General uC definitions                 */

/* Clock gate control */
#define  CGC_CLOCK_DISABLED         0x00U
#define  CGC_CLOCK_ENABLED          0x01U

/* GPIO input / output */
#define GPIO_INPUT                  0x00U
#define GPIO_OUTPUT                 0x01U


/*                 END OF General uC definitions         */


/*                 BUZZER Definitions                    */
#define BUZZER_PORT_BASE_PNT        PORTD                                   /* peripheral port base pointer */
#define BUZZER_GPIO_BASE_PNT        PTD                                     /* peripheral gpio base pointer */

#define BUZZER_PIN                  1U                                      /* buzzer pin */
#define BUZZER_DIR                  kGpioDigitalOutput
#define BUZZER_ALT                  0x01u
/*                 END OF BUZZER definitions             */


/*                 LED and SWITCH Definitions                    */
#define LS_PORT_BASE_PNT            PORTA                                   /* peripheral port base pointer */
#define LS_GPIO_BASE_PNT            PTA                                     /* peripheral gpio base pointer */

/* THIS PIN CONFLICTS WITH PTA1 USED AS UART0_RX IN THE OPENSDA SERIAL DEBUG PORT */
#define LS1_PIN                     1U                                      /* led/switch #1 pin */
#define LS1_ALT                     0x01u                                   /* GPIO alternative */

/* THIS PIN CONFLICTS WITH PTA2 USED AS UART0_TX IN THE OPENSDA SERIAL DEBUG PORT */
#define LS2_PIN                     2U                                      /* led/switch #2 pin */
#define LS2_DIR_OUTPUT              (GPIO_OUTPUT << LS2_PIN)
#define LS2_DIR_INPUT               (GPIO_OUTPUT << LS2_PIN)
#define LS2_ALT                     LS1_ALT

#define LS3_PIN                     4U                                      /* led/switch #3 pin */
#define LS3_DIR_OUTPUT              (GPIO_OUTPUT << LS3_PIN)
#define LS3_DIR_INPUT               (GPIO_OUTPUT << LS3_PIN)
#define LS3_ALT                     LS1_ALT

#define LS4_PIN                     5U                                      /* led/switch #4 pin */
#define LS4_DIR_OUTPUT              (GPIO_OUTPUT << LS4_PIN)
#define LS4_DIR_INPUT               (GPIO_OUTPUT << LS4_PIN)
#define LS4_ALT                     LS1_ALT

/*                 END OF LED and SWITCH definitions             */


#endif /* SOURCES_ES670_PERIPHERAL_BOARD_H_ */




/*                 LCD definitions                 */

/* LCD Register Selector
 * Used as register selector input
 * When (LCD_RS = LCD_RS_HIGH) => DATA register is selected
 * When (LCD_RS = LCD_RS_LOW)  => INSTRUCTION register is selected
*/
#define LCD_PORT_BASE_PNT           PORTC                                   /* peripheral port base pointer */
#define LCD_GPIO_BASE_PNT           PTC                                     /* peripheral gpio base pointer */

#define LCD_RS_PIN                  8U                                      /* register selector */
#define LCD_RS_DIR                  1U//kGpioDigitalOutput
#define LCD_RS_DIR_OUTPUT			(GPIO_OUTPUT << LCD_RS_PIN)
#define LCD_RS_ALT                  1U//kPortMuxAsGpio

#define LCD_ENABLE_PIN              9U                                      /* enable pin */
#define LCD_ENABLE_DIR              1U//kGpioDigitalOutput
#define LCD_ENABLE_DIR_OUTPUT		(GPIO_OUTPUT << LCD_ENABLE_PIN)
#define LCD_ENABLE_ALT              1U//kPortMuxAsGpio

#define LCD_RS_HIGH                 1U
#define LCD_RS_DATA                 LCD_RS_HIGH

#define LCD_RS_LOW                  0U
#define LCD_RS_CMD                  LCD_RS_LOW

#define LCD_ENABLED                 1U
#define LCD_DISABLED                0U

#define LCD_DATA_DIR                1U//kGpioDigitalOutput                      /* LCD data pins */
#define LCD_DATA_ALT                1U//kPortMuxAsGpio

#define LCD_DATA_DB0_PIN            0U
#define LCD_DATA_DB0_DIR_OUTPUT		(GPIO_OUTPUT << LCD_DATA_DB0_PIN )
#define LCD_DATA_DB1_PIN            1u
#define LCD_DATA_DB1_DIR_OUTPUT		(GPIO_OUTPUT << LCD_DATA_DB1_PIN )
#define LCD_DATA_DB2_PIN            2u
#define LCD_DATA_DB2_DIR_OUTPUT		(GPIO_OUTPUT << LCD_DATA_DB2_PIN )
#define LCD_DATA_DB3_PIN            3U
#define LCD_DATA_DB3_DIR_OUTPUT		(GPIO_OUTPUT << LCD_DATA_DB3_PIN )
#define LCD_DATA_DB4_PIN            4U
#define LCD_DATA_DB4_DIR_OUTPUT		(GPIO_OUTPUT << LCD_DATA_DB4_PIN )
#define LCD_DATA_DB5_PIN            5U
#define LCD_DATA_DB5_DIR_OUTPUT		(GPIO_OUTPUT << LCD_DATA_DB5_PIN )
#define LCD_DATA_DB6_PIN            6U
#define LCD_DATA_DB6_DIR_OUTPUT		(GPIO_OUTPUT << LCD_DATA_DB6_PIN )
#define LCD_DATA_DB7_PIN            7U
#define LCD_DATA_DB7_DIR_OUTPUT		(GPIO_OUTPUT << LCD_DATA_DB7_PIN )
/*                 END OF LCD definitions                 */

/*                 END OF LED and SWITCH definitions             */


/*                 COOLER Definitions                    */
#define COOLER_PORT_BASE_PNT        PORTA
#define COOLER_GPIO_BASE_PNT        PTA

#define COOLER_PIN                  13U
#define COOLER_DIR                  kGpioDigitalOutput
#define COOLER_ALT                  0x01u
/*                 END OF COOLER definitions             */


/*                 COOLER Definitions                    */
#define TACHOMETER_PORT_BASE_PNT        PORTE                                   /* peripheral port base pointer */
#define TACHOMETER_GPIO_BASE_PNT        PTE                                     /* peripheral gpio base pointer */

#define TACHOMETER_PIN                  29U                                      /* buzzer pin */
#define TACHOMETER_DIR                  kGpioDigitalOutput
#define TACHOMETER_ALT                  0x04u
/*                 END OF COOLER definitions             */


//Emissor_Largada
#define INFRARED_PORT_BASE_PNT        PORTC                                   /* peripheral port base pointer */
#define INFRARED_GPIO_BASE_PNT        PTC                                     /* peripheral gpio base pointer */
#define INFRARED_DIR                  kGpioDigitalOutput

//Emissor_1
#define INFRARED_PIN1                  6U                                      /* ----------- pin */
#define INFRARED_ALT1                  0x01u

//Emissor_2
#define INFRARED_PIN2                  5U                                      /* ----------- pin */
#define INFRARED_ALT2                  0x01u

//Emissor_3
#define INFRARED_PIN3                  4U                                      /* ----------- pin */
#define INFRARED_ALT3                  0x01u

//Emissor_4
#define INFRARED_PIN4                  3U                                      /* ----------- pin */
#define INFRARED_ALT4                  0x01u

//Emissor_5
#define INFRARED_PIN5                  0U                                      /* ----------- pin */
#define INFRARED_ALT5                  0x01u

//Emissor_6
#define INFRARED_PIN6                  7U                                      /* ----------- pin */
#define INFRARED_ALT6                  0x01u

/*                 END OF INFRARED definitions             */

/*                 Ponte H Definitions                    */
#define ENABLED_PORT_BASE_PNT        PORTB                                   /* peripheral port base pointer */
#define ENABLED_GPIO_BASE_PNT        PTB                                     /* peripheral gpio base pointer */

#define ENABLEDH_PIN                  8U                                      /* enable motor D */
#define ENABLEDH_ALT                  0x01u

#define ENABLEDAH_PIN                  9U                                      /* enable motor D */
#define ENABLEDAH_ALT                  0x01u

#define ENABLEEH_PIN                  10U                                      /* enable motor D */
#define ENABLEEH_ALT                  0x01u

#define ENABLEEAH_PIN                  11U                                      /* enable motor D */
#define ENABLEEAH_ALT                  0x01u
/*                 END OF BUZZER definitions             */

/*                 Encoders Definitions                    */
#define ENCODER_PORT_BASE_PNT            PORTA                                   /* peripheral port base pointer */
#define ENCODER_GPIO_BASE_PNT            PTA                                     /* peripheral gpio base pointer */

#define ENCODERD_PIN                     16U

#define ENCODERE_PIN                     17U
#define ENCODER_ALT                     0x01u                                   /* GPIO alternative */
/*                 END OF Encoders definitions             */

/*                 Encoders Definitions                    */
#define LED_PORT_BASE_PNT            PORTE                                   /* peripheral port base pointer */
#define LED_GPIO_BASE_PNT            PTE                                     /* peripheral gpio base pointer */

#define LED_PIN                     2U
#define LED_ALT                     0x01u                                   /* GPIO alternative */
/*                 END OF Encoders definitions             */
