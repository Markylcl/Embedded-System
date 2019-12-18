#include "debug.h"



static GPIO_PinConfig gpioPinConfigs[] = {
    /* Board_GPIO_LED0 : LaunchPad LED D10 (Red) */
    GPIOCC32XX_GPIO_09 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
    /* Board_GPIO0 */
    GPIOCC32XX_GPIO_00 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
    /* Board_GPIO1 */
    GPIOCC32XX_GPIO_05 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
    /* Board_GPIO2 */
    GPIOCC32XX_GPIO_06 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
    /* Board_GPIO3 */
    GPIOCC32XX_GPIO_07 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
    /* Board_GPIO4 */
    GPIOCC32XX_GPIO_08 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
    /* Board_GPIO5 */
    GPIOCC32XX_GPIO_14 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
    /* Board_GPIO6 */
    GPIOCC32XX_GPIO_15 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
    /* Board_GPIO7 */
    GPIOCC32XX_GPIO_16 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
};

#define maskA0 0xE1
#define maskA1 0xC1
#define maskA2 0x03



int uart_initialize (UART_Handle *uart, UART_Params* uartParams)
{
    GPIO_init();
    UART_init();
    /* Create a UART with data processing off. */
    UART_Params_init(uartParams);
    uartParams->writeDataMode = UART_DATA_BINARY;
    uartParams->readDataMode = UART_DATA_BINARY;
    uartParams->readReturnMode = UART_RETURN_FULL;
    uartParams->readEcho = UART_ECHO_OFF;
    uartParams->baudRate = 115200;

    *uart = UART_open(Board_UART0, uartParams);

    if (*uart == NULL) {
        return -1;
    }
    return 1;
}


void dbgUARTVal(unsigned char outVal, UART_Handle *uart) {
    UART_write(*uart, &outVal, 1);
}

void dbgOutputLoc(unsigned int outLoc) {
    const GPIOCC32XX_Config GPIOCC32XX_config = {
        .pinConfigs = (GPIO_PinConfig *)gpioPinConfigs,
        .callbacks = NULL,
        .numberOfPinConfigs = 9,
        .numberOfCallbacks = 0,
        .intPriority = (~0)
    };


    /*!
     *  @brief     Writes the value to a GPIO pin
     *
     *  @param      index    GPIO index
     *  @param      value    must be either 0 or 1
     */

    if (outLoc > 127)
    {
        // program failed
        // start panic here

        //TODO: disable timer

        while (1) {
            const char panic[] = "failed, stop\n";
            int i = 0;
            for ( i = 0; i < 13; ++i)
            {
                dbgUARTVal(panic[i], &uart);
            }


        }

    }
  //  outLoc = 127;
// print out outLoc value with gpio
    unsigned int bits[8];
    int i =0;
    for (i = 0; i < 8; ++i)
    {
        bits[i] = 1 & (outLoc >>i );
    }
    uintptr_t  key;

    uint8_t valA0 = 0;
    uint8_t valA1 = 0;
    uint8_t valA2 = 0;

   valA0 = bits[0]+(bits[2]<<6)+(bits[3]<<7);
    //
    //valA0 = 0xff;
    valA1 = bits[4]+(bits[5]<<6)+(bits[6]<<7);

    valA2 = bits[7]+(bits[1]<<1);


    key = HwiP_disable();


        /* Clear output from pinConfig */

    for(i=0;i<=7;i++){
        GPIOCC32XX_config.pinConfigs[i] &= ~GPIO_CFG_OUT_HIGH;



        if (bits[i]) {
           // output = config->pin;

            /* Set the pinConfig output bit to high */
            GPIOCC32XX_config.pinConfigs[i] |= GPIO_CFG_OUT_HIGH;
        }
    }

    //    HWREG(GPIOA0_BASE + (GPIO_O_GPIO_DATA + (maskA0 << 2))) = valA0;
     //   HWREG(GPIOA1_BASE + (GPIO_O_GPIO_DATA + (maskA1 << 2))) = valA1;
     //   HWREG(GPIOA2_BASE + (GPIO_O_GPIO_DATA + (maskA2 << 2))) = valA2;

        HwiP_restore(key);




    if (outLoc != prev) {
       // GPIO_write(Board_GPIO7, 1);
    }
    else {
      //  GPIO_write(Board_GPIO7, 0);
    }

    prev = outLoc;

}

void errorFunction(unsigned int errorcode){
    if(errorcode<127){
        errorcode +=127;
    }
   // timer1stop();
   // timer2stop();
    dbgOutputLoc(errorcode);
    // turn off all interupt with a line of code
    //kill threads
}

