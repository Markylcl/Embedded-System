#ifndef ROBOT_ARM_H_
#define ROBOT_ARM_H_

#include <stdbool.h>
#include <ti/drivers/PWM.h>



#define angle2duty(a) (500+(2000*a)/180)
#define duty2angle(d) ((d-500)*180/2000)
#define RIGHT 0
#define CLIP 1
#define LEFT 2
#define BASE 3

typedef struct
{
    uint8_t id;
    PWM_Handle pwm;
    uint16_t current_duty;
    uint16_t target_duty;
    uint8_t speed;
    bool standby;
} Servo;
enum RobotArmState
{
   STATE_UNKNOWN, STATE_IDLE, STATE_WORKING, STATE_ERROR, STATE_STOP
};

//
//bool RobotArm_init(Servo* servo);
bool RobotArm_start();
void RobotArm_reset(Servo* servo);
void RobotArm_setAngle(Servo* servo, uint8_t angle, uint8_t speed);
void RobotArm_stop();
void RobotArm_Resume();
void RobotArm_move(Servo* servo);
#endif
