#ifndef OUTPUT_QUEUE_H_
#define OUTPUT_QUEUE_H_
#include <stdbool.h>
#include <FreeRTOS.h>
#include "queue.h"
enum Message_Type
{
    MSG_INFO, MSG_STATE, MSG_ERROR
};

#define OUTPUT_QUEUE_SIZE 64
//typedef struct
//{
//    uint8_t type;
//    char msg[32];
//} Msg;

QueueHandle_t OutputQueue_init();
void OutputQueue_send(uint8_t type, char* msg);
bool OutputQueue_recv(char *msg);

#endif

//{"type":info,msg:"ok"}
//{"type":error,msg:"xxxxx"}
