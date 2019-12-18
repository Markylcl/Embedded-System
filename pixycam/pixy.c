/*
 * pixy.c
 *
 *  Created on: Nov 20, 2019
 *      Author: b2143
 */

#include "pixy.h"
#include "client_cbs.h"
#include "uart_term.h"
#include "client.h"
#include "client_cbs.h"
#define PIXYCAM_ADDR    0x54
#define THREADSTACKSIZE   2048


void *i2cThread(void *arg0)
{
    //initialize timer
    //SensorQueue_init();
    //define variables for i2c
    uint8_t         txBuffer[6]; // request
    uint8_t         rxBuffer[48]; //receive from pixy
    I2C_Handle      i2c;
    I2C_Params      i2cParams;
    I2C_Transaction i2cTransaction;

    /* Common I2C transaction setup */
    i2cTransaction.writeBuf   = txBuffer;
    i2cTransaction.writeCount = 6;
    i2cTransaction.readBuf    = rxBuffer;
    i2cTransaction.readCount  = 48;


    //setup tx buffer
    txBuffer[0] = 0xae;
    txBuffer[1] = 0xc1;
    txBuffer[2] = 0x20;
    txBuffer[3] = 0x02;
    txBuffer[4] = 0xff;
    txBuffer[5] = 0xff;


    //GPIO_init();
    I2C_init();


    //open i2c
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_400kHz;
    i2c = I2C_open(Board_I2C_PIXY, &i2cParams);
    if(i2c == NULL)
    {
        while(1);
    }


    //get i2c transaction
    i2cTransaction.slaveAddress = PIXYCAM_ADDR;
   // int a = sendTimeMsgToQ1(250);
    msg_type msg;

    while(1){
        if (readMsgFrom_Sensor_queue( &msg) == 0){
            GPIO_toggle(Board_GPIO_LED_RED);
            if (msg.MsgType == TIME_TYPE)
        {
                //UART_PRINT("pixy readed\n\r");
                    if (!I2C_transfer(i2c, &i2cTransaction)) {
                        while(1);
                    }

                    uint8_t c1 = rxBuffer[6];
                    uint8_t c2 = rxBuffer[20];
                    uint8_t c3 = rxBuffer[33];
                    int x1_value;
                    int y1_value;
                    int c1_value;
                    int x2_value;
                    int y2_value;
                    int c2_value;
                    int x3_value;
                    int y3_value;
                    int c3_value;

                    //first block
                    if(c1 != 1 && c1 !=2 && c1!=3)
                    {
                        x1_value = -1;
                        y1_value = -1;
                        c1_value = -1;
                    }
                    else
                    {
                        uint16_t x16_1 = ((uint16_t)(rxBuffer[9]) << 8) | rxBuffer[8];
                        x1_value= (int) x16_1;
                        uint16_t y16_1 = ((uint16_t)(rxBuffer[9]) << 8) | rxBuffer[10];
                        y1_value= (int) y16_1;
                        c1_value = (int) c1;
                    }

                    //second block
                    if(c2 != 1 && c2 !=2 && c2 !=3)
                    {
                        x2_value = -1;
                        y2_value = -1;
                        c2_value = -1;
                    }
                    else
                    {
                        uint16_t x16_2 = ((uint16_t)(rxBuffer[9]) << 8) | rxBuffer[8];
                        x2_value= (int) x16_2;
                        uint16_t y16_2 = ((uint16_t)(rxBuffer[9]) << 8) | rxBuffer[10];
                        y2_value= (int) y16_2;
                        c2_value = (int) c2;
                    }

                    //third block
                    if(c3 != 1 && c3 !=2 && c3 !=3)
                    {
                        x3_value = -1;
                        y3_value = -1;
                        c3_value = -1;
                    }
                    else
                    {
                        uint16_t x16_3 = ((uint16_t)(rxBuffer[9]) << 8) | rxBuffer[8];
                        x3_value= (int) x16_3;
                        uint16_t y16_3 = ((uint16_t)(rxBuffer[9]) << 8) | rxBuffer[10];
                        y3_value= (int) y16_3;
                        c3_value = (int) c3;
                    }

                    block_type newmsg;
                    newmsg.color=c1_value;
                    newmsg.x=x1_value;
                    newmsg.y=y1_value;
                    newmsg.color2=c2_value;
                    newmsg.x2=x2_value;
                    newmsg.y2=y2_value;
                    newmsg.color3=c3_value;
                    newmsg.x3=x3_value;
                    newmsg.y3=y3_value;
                    send_pixyqueue(&newmsg);
                }
       }
    }
}

void pixy_start()
{
    pthread_t           thread0;
    pthread_attr_t      attrs;
    struct sched_param  priParam;
    int                 retc;
    int                 detachState;
    pixyqueue_init();
    SensorQueue_init();
    GPIO_init();
    I2C_init();
    Timer_init();

    GPIO_setConfig(Board_GPIO_LED_RED, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);

    /* Turn on user LED */
    GPIO_write(Board_GPIO_LED_RED, Board_GPIO_LED_ON);

    inittimertwo();


    /* Create application threads */
    pthread_attr_init(&attrs);

    detachState = PTHREAD_CREATE_DETACHED;
    /* Set priority and stack size attributes */
    retc = pthread_attr_setdetachstate(&attrs, detachState);
    if (retc != 0) {
        /* pthread_attr_setdetachstate() failed */
        while (1);
    }


    retc |= pthread_attr_setstacksize(&attrs, THREADSTACKSIZE);
    if (retc != 0) {
        /* pthread_attr_setstacksize() failed */
        while (1);
    }

    /* Create threadFxn0 thread */
    priParam.sched_priority = 1;
    pthread_attr_setschedparam(&attrs, &priParam);

    retc = pthread_create(&thread0, &attrs, i2cThread, NULL);
    if (retc != 0) {
        /* pthread_create() failed */
        while (1);
    }
}
