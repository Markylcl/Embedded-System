/*This file is sensor_queue source file
 *
 *
 */
#include "Sensor_queue.h"


/* Declared globally. */


QueueHandle_t SensorQueue;


int SensorQueue_init() {
	SensorQueue = xQueueCreate(20, 8);
	return 0;

}

int sendTimeMsgToQ1(uint32_t timeVal) {
    BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    GPIO_toggle(Board_GPIO_LED_RED);

    msg_type newMsg;
    newMsg.MsgType = TIME_TYPE;
    newMsg.MsgValue = timeVal;
    int64_t data = ((int64_t)newMsg.MsgType << 32) + newMsg.MsgValue;
    if (xQueueSendFromISR (SensorQueue, &data, &xHigherPriorityTaskWoken ) != pdTRUE)
        //    xQueueSendToBack( SensorQueue, &data,  portMAX_DELAY)!=pdPASS)
    {

        return -1;
        // fail to push the message to queue
    }
    return 0;
}

int readMsgFrom_Sensor_queue(msg_type* message) {
	// BaseType_t xHigherPriorityTaskWoken;
//	xHigherPriorityTaskWoken = pdFALSE;
//    if (xQueueIsQueueEmptyFromISR(SensorQueue) != pdFALSE) {
//        return -1;
//    }
//
//	else {
        //msg_type *data;
    //GPIO_toggle(Board_GPIO_LED_RED);
    int64_t data;
    if (xQueueReceive(SensorQueue, &data, ( TickType_t )portMAX_DELAY)!= pdPASS)
    {
        return -1;
    }

    message->MsgType = data >> 32;

    uint64_t mask = 0x0000FFFF;
    message->MsgValue = data & mask;
    return 0;
//	}
}


