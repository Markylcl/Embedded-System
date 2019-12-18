#ifndef INPUT_QUEUE_H_
#define	INPUT_QUEUE_H_
#include <stdlib.h>
#include <stdbool.h>

enum Command_Type
{
    CMD_STATE,CMD_RESET,CMD_ANGLE, CMD_MOVE, CMD_RESUME, CMD_STOP, CMD_GREEN,CMD_YELLOW
};

typedef struct
{
    uint8_t type;
    uint8_t servo;
    uint8_t angle;
    uint8_t speed;
} Command;

bool InputQueue_init();
bool InputQueue_sendCmd(Command *cmd);
bool InputQueue_send(char *json);
//bool InputQueue_sendISR(char *json, size_t len);
//bool InputQueue_send(char *json,size_t len);
//bool InputQueue_send(Command* cmd);
void InputQueue_recv(Command* cmd);

#endif
