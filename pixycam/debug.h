#ifndef DEBUG_H_
#define DEBUG_H_

#define DLOC_MAIN_BEGIN 0x10
#define DLOC_MAIN_BEFORE_RECEIVE_FROM_QUEUE 0x11
#define DLOC_MAIN_AFTER_RECEIVE_FROM_QUEUE 0x12
#define DLOC_MAIN_TIME_TYPE_MSG 0x13
#define DLOC_MAIN_SENSOR_TYPE_MSG 0x14
#define DLOC_MAIN_BEFORE_STATEMACHINE 0x15
#define DLOC_MAIN_AFTER_STATEMACHINE 0x16


#define DLOC_ENTER_SEND_QUEUE_TIME 0x21
#define DLOC_BEFORE_RECEIVE_QUEUE 0x22
#define DLOC_AFTER_SEND_QUEUE_TIME 0x23
#define DLOC_AFTER_RECEIVE_QUEUE 0x24
#define DLOC_ENTER_SEND_QUEUE_SENSOR 0x25
#define DLOC_AFTER_SEND_QUEUE_SENSOR 0x26



#define DLOC_ISR_TIMER0_ENTER 0x30
#define DLOC_ISR_TIMER1_ENTER 0x31
#define DLOC_ISR_TIMER0_EXIT 0x32
#define DLOC_ISR_TIMER1_EXIT 0x33

#define DLOC_BEFORE_SENDING_TIME_TO_QUEUE 0x40
#define DLOC_AFTER_SENDING_TIME_TO_QUEUE 0x42
#define DLOC_AFTER_RECEIVE_FROM_QUEUE 0x43
#define DLOC_BEFORE_SENDING_SENSOR_TO_QUEUE 0x44
#define DLOC_AFTER_SENDING_SENSOR_TO_QUEUE 0x45

#define ERROR_TIME_MSG 0XF0
#define ERROR_SENSOR_MSG 0XF1
#define ERROR_READING_MSG 0XF2

#define ERROR_TIMER0_INIT 0xE0
#define ERROR_TIMER0_START 0xE1
#define ERROR_TIMER0_ADD 0xE2

#define ERROR_TIMER1_INIT 0xE3
#define ERROR_TIMER1_START 0xE4
#define ERROR_TIMER1_ADD 0xE5





#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
//#include <ti/devices/cc32xx/driverlib/gpio.h>


#include <ti/devices/cc32xx/inc/hw_gpio.h>
#include <ti/devices/cc32xx/inc/hw_memmap.h>
#include <ti/devices/cc32xx/inc/hw_types.h>
#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/gpio/GPIOCC32XX.h>
#include <ti/devices/cc32xx/driverlib/gpio.h>

//#include "timerone.h"
//#include "timertwo.h"



typedef struct PinConfig {
    uint8_t pin;
    uint8_t port;
    uint16_t config;
} PinConfig;



#include <stdint.h>
#include "Board.h"

#define GPIO_PIN_0              0x00000001  // GPIO pin 0
#define GPIO_PIN_1              0x00000002  // GPIO pin 1
#define GPIO_PIN_2              0x00000004  // GPIO pin 2
#define GPIO_PIN_3              0x00000008  // GPIO pin 3
#define GPIO_PIN_4              0x00000010  // GPIO pin 4
#define GPIO_PIN_5              0x00000020  // GPIO pin 5
#define GPIO_PIN_6              0x00000040  // GPIO pin 6
#define GPIO_PIN_7              0x00000080  // GPIO pin 7

#define GPIOA0_BASE             0x40004000
#define GPIOA1_BASE             0x40005000
#define GPIOA2_BASE             0x40006000
#define GPIOA3_BASE             0x40007000
#define GPIOA4_BASE             0x40024000


UART_Handle uart;
UART_Params uartParams;
unsigned int prev;
/*
const GPIOCC32XX_Config GPIOCC32XX_config = {
    .pinConfigs = (GPIO_PinConfig *)gpioPinConfigs,
    .callbacks = NULL,
    .numberOfPinConfigs = 9,
    .numberOfCallbacks = 0,
    .intPriority = (~0)
};

*/



int uart_initialize(UART_Handle *uart, UART_Params *uartParams );





void dbgUARTVal(unsigned char outVal, UART_Handle *uart);



void dbgOutputLoc(unsigned int outLoc);

void errorFunction(unsigned int errorcode);

#endif  /* DEBUG_H_ */
