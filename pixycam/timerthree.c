/*
 * timerthree.c
 *
 *  Created on: Dec 3, 2019
 *      Author: b2143
 */
#include "FreeRTOS.h"
#include <queue.h>
#include "task.h"
#include "croutine.h"
#include "timer_queue.h"
#include <board.h>
/* Driver Header files */
#include <stddef.h>
#include "client.h"
#include "timerthree.h"

 Timer_Handle timer3;
void inittimerthree()
{
    Timer_Params params3;

    Timer_Params_init(&params3);
    params3.period = 500000;
    params3.periodUnits = Timer_PERIOD_US;
    params3.timerMode = Timer_CONTINUOUS_CALLBACK;
    params3.timerCallback = timerthreeCallback;
    timer3 = Timer_open(Board_TIMER0, &params3);
    if (timer3 == NULL) {
        /* Failed to initialized timer */
        //errorFunction(ERROR_TIMER0_INIT);
    }


    if (Timer_start(timer3) == Timer_STATUS_ERROR) {
        /* Failed to start timer */
        //errorFunction(ERROR_TIMER0_START);
        int i = 1;

    }

}


void timerthreeCallback(Timer_Handle myHandle)
{
    //sendflag=1;
    uint32_t time = 500;

    if (sendTimeMsgTotimerqueue(time) != 0)
    {
        int i =1;
    }
    /*
    if(MQTT_SendMsgToQueue(&queueElem))
    {
        UART_PRINT("\n\n\rQueue is full\n\n\r");
    }
    */


}

