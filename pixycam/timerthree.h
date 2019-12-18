/*
 * timerthree.h
 *
 *  Created on: Dec 3, 2019
 *      Author: b2143
 */

#ifndef TIMERTHREE_H_
#define TIMERTHREE_H_

#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>
#include "Board.h"
#include "uart_term.h"
void inittimerthree();
void timerthreeCallback(Timer_Handle myHandle);



#endif /* TIMERTHREE_H_ */
