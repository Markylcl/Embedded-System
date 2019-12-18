/*
 * timertwo.h
 *
 *  Created on: Nov 20, 2019
 *      Author: b2143
 */

#ifndef TIMERTWO_H_
#define TIMERTWO_H_


#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>
#include "Board.h"

void inittimertwo();
void timertwoCallback(Timer_Handle myHandle);




#endif /* TIMERTWO_H_ */
