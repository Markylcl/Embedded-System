/*
 * uart_client.c
 *
 *  Created on: 2019Äê11ÔÂ6ÈÕ
 *      Author: Administrator
 */

#include <pthread.h>
#include "uart_clinet.h"
#include "uart_term.h"
#include "input_queue.h"
#include "output_queue.h"
void * UartRevcThread(void *pvParameters)
{
    //char buffer[64];
    while (1)
    {
       // GetCmd(buffer, 64);
        //InputQueue_send(buffer);
    }
}

void *UartSendThread(void *pvParameters)
{
   // char buffer[OUTPUT_QUEUE_SIZE];
    while (1)
    {
//        if(OutputQueue_recv(buffer)){
//            Message(buffer);
//        }
    }
}

bool UartClient_start()
{
    pthread_t thread= (pthread_t) NULL;
    pthread_attr_t pAttrs;
    struct sched_param priParam;
    int32_t retc = 0;
    /*Set priority and stack size attributes                                 */
    pthread_attr_init(&pAttrs);
    priParam.sched_priority = 2;
    retc = pthread_attr_setschedparam(&pAttrs, &priParam);
    retc |= pthread_attr_setstacksize(&pAttrs, 1024);
    retc |= pthread_attr_setdetachstate(&pAttrs, PTHREAD_CREATE_DETACHED);
    retc |= pthread_create(&thread, &pAttrs, UartRevcThread, NULL);
    if (retc != 0)
    {
        return false;
    }

    pthread_attr_init(&pAttrs);
    priParam.sched_priority = 2;
    retc = pthread_attr_setschedparam(&pAttrs, &priParam);
    retc |= pthread_attr_setstacksize(&pAttrs, 1024);
    retc |= pthread_attr_setdetachstate(&pAttrs, PTHREAD_CREATE_DETACHED);
    retc |= pthread_create(&thread, &pAttrs, UartSendThread, NULL);
    if (retc != 0)
    {
        return false;
    }
    return true;
}

