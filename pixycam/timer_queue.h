/*
 * timer_queue.h
 *
 *  Created on: Dec 3, 2019
 *      Author: b2143
 */

#ifndef TIMER_QUEUE_H_
#define TIMER_QUEUE_H_

#include "FreeRTOS.h"
#include <queue.h>
#include "task.h"
#include "croutine.h"
#include "debug.h"




// 8-bytes Message From the sensor,
// which includes two components:
// message type（time or sensor message） and
// data being sent (time value or sensor value)

#define TIMERTHREE_TYPE 0

typedef struct timerq_type {
    uint32_t MsgType;// time or sens
    uint32_t MsgValue;// time value or sensor value
} tq_type;



int timerQueue_init();
int sendTimeMsgTotimerqueue(uint32_t timeVal);
int readMsgFrom_timer_queue(tq_type* message);



#endif /* TIMER_QUEUE_H_ */
