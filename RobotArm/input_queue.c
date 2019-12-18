#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "FreeRTOS.h"
#include "queue.h"
#include "pthread.h"

#include "uart_term.h"
#include "input_queue.h"
#include "cJSON.h"
QueueHandle_t hInputQueue;

bool InputQueue_init()
{
    hInputQueue = xQueueCreate(10, sizeof(Command));
    return hInputQueue != NULL;
}

bool InputQueue_send(char *json)
{
    cJSON* root = cJSON_Parse(json);
    cJSON* itemType = cJSON_GetObjectItem(root, "cmd");
    Command cmd;
    char* type = itemType->valuestring;
    if (strcmp(type, "angle") == 0)
    {
        cmd.type = CMD_ANGLE;
        cJSON* itemServo = cJSON_GetObjectItem(root, "servo");
        cJSON* itemAngle = cJSON_GetObjectItem(root, "angle");
        cJSON* itemSpeed = cJSON_GetObjectItem(root, "speed");
        cmd.servo = itemServo->valueint;
        cmd.angle = itemAngle->valueint;
        cmd.speed = itemSpeed->valueint;
    }
    else if (strcmp(type, "state") == 0)
    {
        cmd.type = CMD_STATE;
    }
    else if (strcmp(type, "reset") == 0)
    {
        cmd.type = CMD_RESET;
    }
    else if (strcmp(type, "stop") == 0)
    {
        cmd.type = CMD_STOP;
    }
    else if (strcmp(type, "resume") == 0)
    {
        cmd.type = CMD_RESUME;
    }
    else if (strcmp(type, "move") == 0)
    {
        cmd.type = CMD_MOVE;
    }
    else if (strcmp(type, "Green") == 0)
    {
        cmd.type = CMD_GREEN;
    }
    else if (strcmp(type, "Yellow") == 0)
    {
        cmd.type = CMD_YELLOW;
    }
    else
    {
        return false;
    }
    cJSON_Delete(root);
    return InputQueue_sendCmd(&cmd);
}

bool InputQueue_sendCmd(Command *cmd)
{

    if ( xQueueSend(hInputQueue, cmd, portMAX_DELAY) == pdPASS)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool InputQueue_sendISR(char *json, size_t len)
{

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    if ( xQueueSendFromISR(hInputQueue, json,
                           &xHigherPriorityTaskWoken) == pdPASS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void InputQueue_recv(Command* cmd)
{
    xQueueReceive(hInputQueue, cmd, portMAX_DELAY);
}

//{"cmd":"angle","servo":0,"angle":100,"speed":5}
//{"cmd":"reset"}
//{"cmd":"state"} // Get current state
//{"cmd":"stop"}
//{"cmd":"resume"}

