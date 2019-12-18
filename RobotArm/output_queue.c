#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "pthread.h"

#include "uart_term.h"
#include "output_queue.h"
#include "cJSON.h"


QueueHandle_t hOutputQueue;

QueueHandle_t OutputQueue_init()
{
    hOutputQueue = xQueueCreate(20, OUTPUT_QUEUE_SIZE);
    return hOutputQueue;
}

void OutputQueue_send(uint8_t type, char* msg) {

    cJSON*  root = cJSON_CreateObject();
    if(type== MSG_ERROR ){
        cJSON_AddStringToObject(root, "type", "error");
    }else if(type== MSG_INFO ){
        cJSON_AddStringToObject(root, "type", "info");
    }else if(type== MSG_STATE ){
        cJSON_AddStringToObject(root, "type", "state");
    }

    cJSON_AddStringToObject(root, "msg", msg);
    char* json = cJSON_PrintUnformatted(root);

    char buffer[OUTPUT_QUEUE_SIZE];
    int len = strlen(json);
    memcpy(buffer,json, len);
    buffer[len] = '\0';
    xQueueSend(hOutputQueue, buffer, ( TickType_t ) portMAX_DELAY );
    cJSON_Delete(root);
    free(json);
}

bool OutputQueue_recv(char * msg) {
    return xQueueReceive(hOutputQueue, msg, portMAX_DELAY)== pdPASS;
}
