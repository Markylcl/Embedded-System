/*
 *  ======== Board.h ========
 *  Configured TI-Drivers module declarations
 *
 *  DO NOT EDIT - This file is generated for the CC3220SF_LAUNCHXL
 *  by the SysConfig tool.
 */
#ifndef Board_h
#define Board_h

#define Board_SYSCONFIG_PREVIEW

#define Board_CC3220SF_LAUNCHXL

/* Temporary define for backwards compatibility!!! */
#define __CC3220SF_LAUNCHXL_BOARD_H__

#ifndef DeviceFamily_CC3220
#define DeviceFamily_CC3220
#endif

#include <stdint.h>

/* support C++ sources */
#ifdef __cplusplus
extern "C" {
#endif


/*
 *  ======== Crypto ========
 */

#define Board_Crypto0               0

/*
 *  ======== PWM ========
 */

#define Board_PWM0                  0
#define Board_PWM1                  1
#define Board_PWM2                  2
#define Board_PWM3                  3


/*
 *  ======== SPI ========
 */

#define Board_NWP_SPI               0
#define Board_SPI0                  1


/*
 *  ======== UART ========
 */

#define Board_UART0                 0


/*
 *  ======== Board_init ========
 *  Perform all required TI-Drivers initialization
 *
 *  This function should be called once at a point before any use of
 *  TI-Drivers.
 */
extern void Board_init(void);

/*
 *  ======== Board_initGeneral ========
 *  (deprecated)
 *
 *  Board_initGeneral() is defined purely for backward compatibility.
 *
 *  All new code should use Board_init() to do any required TI-Drivers
 *  initialization _and_ use <Driver>_init() for only where specific drivers
 *  are explicitly referenced by the application.  <Driver>_init() functions
 *  are idempotent.
 */
#define Board_initGeneral Board_init

#ifdef __cplusplus
}
#endif

#endif /* include guard */
