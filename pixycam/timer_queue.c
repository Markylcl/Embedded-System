/*
 * timer_queue.c
 *
 *  Created on: Dec 3, 2019
 *      Author: b2143
 */
#include "timer_queue.h"

QueueHandle_t timerQueue;


int timerQueue_init() {
    timerQueue = xQueueCreate(20, 32);
    return 0;

}

int sendTimeMsgTotimerqueue(uint32_t timeVal) {
    BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;


    tq_type newMsg;
    newMsg.MsgType = TIMERTHREE_TYPE;
    newMsg.MsgValue = timeVal;
    if (xQueueSendFromISR(timerQueue, &newMsg, &xHigherPriorityTaskWoken ) != pdTRUE)
        //    xQueueSendToBack( SensorQueue, &data,  portMAX_DELAY)!=pdPASS)
    {

        return -1;
        // fail to push the message to queue
    }
    return 0;
}


int readMsgFrom_timer_queue(tq_type* message) {
    BaseType_t xHigherPriorityTaskWoken;
  xHigherPriorityTaskWoken = pdFALSE;

    if (xQueueIsQueueEmptyFromISR(timerQueue) != pdFALSE) {
        return -1;
    }
    else {
        if (xQueueReceive(timerQueue, message, ( TickType_t )portMAX_DELAY)!= pdPASS)
        {
            return -1;
        }
        return 0;
    }
}



