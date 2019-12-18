/*
 * pixy_queue.c
 *
 *  Created on: Dec 3, 2019
 *      Author: b2143
 */

#include "pixy_queue.h"

QueueHandle_t pixyqueue;

int pixyqueue_init()
{
    pixyqueue = xQueueCreate(100, 32);
    return 0;
}

int send_pixyqueue(block_type* message) {
    BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;

    block_type newMsg;
    newMsg.color = message->color;
    newMsg.x = message->x;
    newMsg.y = message->y;
    if (xQueueSend(pixyqueue, &newMsg, ( TickType_t ) portMAX_DELAY ) != pdTRUE)
        //    xQueueSendToBack( SensorQueue, &data,  portMAX_DELAY)!=pdPASS)
    {

        return -1;
        // fail to push the message to queue
    }
    return 0;
}

int read_pixyqueue(block_type* message) {

    if (xQueueIsQueueEmptyFromISR(pixyqueue) != pdFALSE) {
        return -1;
    }
    else if (xQueueReceive(pixyqueue, message, ( TickType_t ) portMAX_DELAY )!= pdPASS)
        {
            return -1;
        }
    else
        return 0;
}
