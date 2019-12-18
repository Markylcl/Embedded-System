/*
 * timertwo.c
 *
 *  Created on: Nov 20, 2019
 *      Author: b2143
 */

#include "FreeRTOS.h"
#include <queue.h>
#include "timertwo.h"
#include "task.h"
#include "croutine.h"
#include "Sensor_queue.h"
#include <board.h>
/* Driver Header files */
#include <stddef.h>
#include "client.h"
#include "uart_term.h"

//#include "Sensor_queue.h"
 Timer_Handle timer1;

void inittimertwo()
{
    Timer_Params params1;

    Timer_Params_init(&params1);
    params1.period = 500000;
    params1.periodUnits = Timer_PERIOD_US;
    params1.timerMode = Timer_CONTINUOUS_CALLBACK;
    params1.timerCallback = timertwoCallback;
    timer1 = Timer_open(Board_TIMER3, &params1);
    if (timer1 == NULL) {
        /* Failed to initialized timer */
        //errorFunction(ERROR_TIMER0_INIT);
        int i = 1;
    }


    if (Timer_start(timer1) == Timer_STATUS_ERROR) {
        /* Failed to start timer */
        //errorFunction(ERROR_TIMER0_START);
        int i = 1;

    }

}


void timertwoCallback(Timer_Handle myHandle)
{
    uint32_t time = 250;



//    if (sendTimeMsgToQ1(time) != 0)
//    {
//        UART_PRINT("\n\n\rone second *******************\n\n\r");
//    }



}


