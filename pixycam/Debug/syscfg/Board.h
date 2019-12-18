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
 *  ======== GPIO ========
 */

#define Board_GPIO_BUTTON0          0
#define Board_GPIO_BUTTON1          1
#define Board_GPIO0                 2
#define Board_GPIO1                 3
#define Board_GPIO2                 4
#define Board_GPIO_LED_RED          5

/* LEDs are active high */
#define Board_GPIO_LED_ON  (1)
#define Board_GPIO_LED_OFF (0)

#define Board_LED_ON  (Board_GPIO_LED_ON)
#define Board_LED_OFF (Board_GPIO_LED_OFF)


/*
 *  ======== I2C ========
 */

#define Board_I2C_PIXY              0

/* ======== I2C Addresses and Speeds ======== */
#include <ti/drivers/I2C.h>

/* ---- Board_I2C_PIXY I2C bus components ---- */

/* BMA222E address and max speed */
#define Board_I2C_PIXY_BMA222E_ADDR     (0x18)
#define Board_I2C_PIXY_BMA222E_MAXSPEED (400U) /* Kbps */

/* TMP006 address and max speed */
#define Board_I2C_PIXY_TMP006_ADDR     (0x41)
#define Board_I2C_PIXY_TMP006_MAXSPEED (3400U) /* Kbps */

/* BOOSTXL_SENSORS/TMP007 address and max speed */
#define Board_I2C_PIXY_BOOSTXL_SENSORS_TMP007_ADDR     (0x40)
#define Board_I2C_PIXY_BOOSTXL_SENSORS_TMP007_MAXSPEED (2500U) /* Kbps */

/* BOOSTXL_SENSORS/BMI160_BMI150 address and max speed */
#define Board_I2C_PIXY_BOOSTXL_SENSORS_BMI160_BMI150_ADDR     (0x69)
#define Board_I2C_PIXY_BOOSTXL_SENSORS_BMI160_BMI150_MAXSPEED (1000U) /* Kbps */

/* BOOSTXL_SENSORS/BME280 address and max speed */
#define Board_I2C_PIXY_BOOSTXL_SENSORS_BME280_ADDR     (0x77)
#define Board_I2C_PIXY_BOOSTXL_SENSORS_BME280_MAXSPEED (3400U) /* Kbps */

/* BOOSTXL_SENSORS/OPT3001 address and max speed */
#define Board_I2C_PIXY_BOOSTXL_SENSORS_OPT3001_ADDR     (0x47)
#define Board_I2C_PIXY_BOOSTXL_SENSORS_OPT3001_MAXSPEED (2600U) /* Kbps */

/* Board_I2C_PIXY max speed (supported by all components) */
#define Board_I2C_PIXY_MAXSPEED   (1000U) /* Kbps */
#define Board_I2C_PIXY_MAXBITRATE ((I2C_BitRate)I2C_1000kHz)


/*
 *  ======== SPI ========
 */

#define Board_NWP_SPI               0
#define Board_SPI0                  1


/*
 *  ======== Timer ========
 */

#define Board_TIMER0                0
#define Board_TIMER1                1
#define Board_TIMER2                2
#define Board_TIMER3                3


/*
 *  ======== UART ========
 */

#define Board_UART0                 0


/*
 *  ======== Watchdog ========
 */

#define Board_WATCHDOG0             0


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
