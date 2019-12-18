/*
 * pixy_queue.h
 *
 *  Created on: Dec 3, 2019
 *      Author: b2143
 */

#ifndef PIXY_QUEUE_H_
#define PIXY_QUEUE_H_

#include <stdbool.h>
#include <FreeRTOS.h>
#include "queue.h"

typedef struct blocks {
    int color;
    int x;
    int y;
    int color2;
    int x2;
    int y2;
    int color3;
    int x3;
    int y3;
} block_type;

int pixyqueue_init();
int send_pixyqueue(block_type* message);
int read_pixyqueue(block_type* message);

#endif /* PIXY_QUEUE_H_ */
