#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "timers.h"
#include "pthread.h"
#include "Board.h"

#include "uart_term.h"
#include "output_queue.h"
#include "input_queue.h"
#include "robot_arm.h"


#define RobotArmSetRight(a,s) RobotArmSetAngle(0,a,s);

PWM_Handle pwm[4];
TimerHandle_t hTimer;

bool RobotArm_init(Servo* servo)
{
    uint16_t pwmPeriod = 20000;
    PWM_Params params;
    PWM_init();

    PWM_Params_init(&params);

    params.dutyUnits = PWM_DUTY_US;
    params.dutyValue = 0;
    params.periodUnits = PWM_PERIOD_US;
    params.periodValue = pwmPeriod;

    pwm[0] = PWM_open(Board_PWM0, &params); // P01 and 9
    pwm[1] = PWM_open(Board_PWM1, &params); // P02 and 10
    pwm[2] = PWM_open(Board_PWM2, &params); // P64 and 29
    pwm[3] = PWM_open(Board_PWM3, &params); // P21 and 13

    if (pwm[0] == NULL || pwm[1] == NULL || pwm[2] == NULL || pwm[3] == NULL)
    {
        return false;
    }
    RobotArm_reset(servo);

    int i;
    for (i = 0; i < 4; i++)
    {
        PWM_start(pwm[i]);
        servo[i].id = i;
        servo[i].pwm = pwm[i];
        servo[i].current_duty = servo->target_duty;
        servo[i].standby = true;
        if (PWM_setDuty(servo[i].pwm, servo->current_duty) == PWM_STATUS_ERROR)
        {
            // Êä³ö´íÎó
            OutputQueue_send(MSG_ERROR,"PWM_setDuty failed");
        }
    }
    return true;
}

void OnTimer(TimerHandle_t xTimer)
{
    Command cmd;
    cmd.type = CMD_MOVE;
    InputQueue_sendCmd(&cmd);
}


void * RobotArmTask(void *pvParameters)
{
    Command cmd;
    Servo servo[4];

    int state = STATE_IDLE;

    bool ret = RobotArm_init(servo);
    if (!ret)
    {
        state = STATE_ERROR;
        OutputQueue_send(MSG_ERROR, "init failed");
        pthread_exit(0);
        return (NULL);
    }
    if (!ret)
    {
        state = STATE_ERROR;
        OutputQueue_send(MSG_ERROR, "start failed");
        pthread_exit(0);
        return (NULL);
    }
    //STATE_UNKNOWN, STATE_IDLE, STATE_WORKING, STATE_ERROR, STATE_STOP
    char *stateString[] = { "unknown", "idle", "working", "error","stop" };

    RobotArm_stop();
    while (1)
    {
        InputQueue_recv(&cmd);

            if (state == STATE_ERROR) // in error state £¬Timer will stop£¬CMD_STATE will current state if there is one£¬(not CMD_MOVE)Otherwise error message output.
            {
                RobotArm_stop();
                if (cmd.type == CMD_STATE)
                {
                    OutputQueue_send(MSG_STATE, stateString[state]);
                }
                else
                {
                    if (cmd.type != CMD_MOVE)
                    {
                        OutputQueue_send(MSG_ERROR, stateString[state]);
                    }
                }
                continue;
            }
            else// Get correct command
            {
                if (cmd.type == CMD_MOVE)// make servo move
                {
                    RobotArm_move(servo);
                }
                if (servo[0].standby && servo[1].standby && servo[2].standby
                        && servo[3].standby)
                {
                    state = STATE_IDLE; // if all the servo go to target position, it will go to idle mode
                    RobotArm_stop();
                }
                else
                {
                    state = STATE_WORKING;//else go to working state
                }

                if (state == STATE_IDLE || state == STATE_WORKING)
                {
                    if (cmd.type == CMD_ANGLE)// set angle in IDLE OR WORKING state.If the previous Angle command is not executed in place, the new Angle will replace the previous one.
                    {
                        RobotArm_setAngle(&servo[cmd.servo], cmd.angle,
                                          cmd.speed);
                        RobotArm_Resume();
                    }
                }
                   if (cmd.type == CMD_STOP)//stop timer
                   {
                        RobotArm_stop();
                        state = STATE_STOP;
                    }
                if (cmd.type == CMD_STATE)//Get state from the servo
                {
                    OutputQueue_send(MSG_STATE, stateString[state]);
                }
                if (cmd.type == CMD_RESET)//reset the arm in any mode
                {
                    RobotArm_reset(servo);
                    RobotArm_Resume();
                }
                if (state == STATE_STOP && cmd.type == CMD_RESUME)//if in stop state && the command is resume
                {
                    RobotArm_Resume(); //start the timer and working
                }
            }
    }
}

bool RobotArm_start()
{
    // ms transform into tick
    hTimer = xTimerCreate("timer", pdMS_TO_TICKS(10), pdTRUE, (void *) 0,
                          OnTimer);
    if (hTimer != NULL)
    {
//        if (pdFAIL == xTimerStart(hTimer, 0))
//        {
//            return false;
//        }
    }else
    {
        return false;
    }
    pthread_t thread = (pthread_t) NULL;
    int32_t threadArg = 100;
    pthread_attr_t pAttrs;
    struct sched_param priParam;
    int32_t retc = 0;
    /*Set priority and stack size attributes                                 */
    pthread_attr_init(&pAttrs);
    priParam.sched_priority = 2;
    retc = pthread_attr_setschedparam(&pAttrs, &priParam);
    retc |= pthread_attr_setstacksize(&pAttrs, 1024);
    retc |= pthread_attr_setdetachstate(&pAttrs, PTHREAD_CREATE_DETACHED);
    if (retc != 0)
    {
        return false;
    }
    retc = pthread_create(&thread, &pAttrs, RobotArmTask, (void *) &threadArg);
    if (retc != 0)
    {
        return false;
    }
    return true;
}

void RobotArm_setAngle(Servo* servo, uint8_t angle, uint8_t speed)
{
    while(!servo->standby);
    servo->standby = false;
    servo->target_duty = angle2duty(angle);

    if(speed <=0){
        speed = 0;
    }
    servo->speed = speed;
}

void RobotArm_move(Servo* servo){
    int duty_inc;

    int i;
    for( i=0;i<4;i++)
    {
        if(servo[i].current_duty != servo[i].target_duty){
            duty_inc = abs((servo[i].target_duty - servo[i].current_duty)) / 10; // Duty ratio increase
            if (duty_inc == 0)
            {
                duty_inc = 1; //cannot be 0
            }else if (duty_inc > servo[i].speed)
            {
                duty_inc = servo[i].speed;
            }
            if (servo[i].current_duty > servo[i].target_duty)
            {
                duty_inc = -duty_inc; // Based on direction change the value
            }
            servo[i].current_duty += duty_inc;
            PWM_setDuty(servo[i].pwm, servo[i].current_duty);
        }else{
            if (!servo[i].standby)
            {
                char msg[20];
                sprintf(msg,"servo:%d standby",servo[i].id);
                OutputQueue_send(MSG_INFO, msg);
                servo[i].standby = true;
            }
        }
    }

}
void RobotArm_reset(Servo* servo)
{
    //reset the servo angle

    RobotArm_setAngle(&servo[0],95,100);
    RobotArm_setAngle(&servo[1],80,100);
    RobotArm_setAngle(&servo[2],80,100);
    RobotArm_setAngle(&servo[3],90,100);
}

void RobotArm_stop()
{
    xTimerStop(hTimer, 0);
}
void RobotArm_Resume()
{
    xTimerStart(hTimer, 0);
}


