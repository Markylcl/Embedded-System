/*
This is the header file for sensor_queue.c


*/



#ifndef SENSOR_QUEUE_H_
#define	SENSOR_QUEUE_H_


#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "croutine.h"
#include "debug.h"



// 8-bytes Message From the sensor,
// which includes two components:
// message type（time or sensor message） and
// data being sent (time value or sensor value)

#define TIME_TYPE 0

typedef struct Message_type {
	uint32_t MsgType;// time or sens
	uint32_t MsgValue;// time value or sensor value
} msg_type;



int SensorQueue_init();
int sendTimeMsgToQ1(uint32_t timeVal);
int readMsgFrom_Sensor_queue(msg_type* message);



#endif	/* SENSOR_QUEUE_H_ */

