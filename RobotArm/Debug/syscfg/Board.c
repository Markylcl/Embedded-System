/*
 *  ======== Board.c ========
 *  Configured TI-Drivers module definitions
 *
 *  DO NOT EDIT - This file is generated for the CC3220SF_LAUNCHXL
 *  by the SysConfig tool.
 */

#include <stddef.h>

#ifndef DeviceFamily_CC3220
#define DeviceFamily_CC3220
#endif

#include <ti/devices/DeviceFamily.h>

#include "Board.h"

/*
 *  =============================== Crypto ===============================
 */

#include <ti/drivers/crypto/CryptoCC32XX.h>

/*
 *  ======== CryptoCC32XXObjects ========
 */
#define Board_CryptoCOUNT 1

CryptoCC32XX_Object cryptoCC32XXObjects[Board_CryptoCOUNT];

/*
 *  ======== Crypto_config ========
 */
const CryptoCC32XX_Config CryptoCC32XX_config[Board_CryptoCOUNT] = {
    /* Board_Crypto0 */
    {
        .object = &cryptoCC32XXObjects[Board_Crypto0],
    },
};

const uint_least8_t CryptoCC32XX_count = Board_CryptoCOUNT;



/*
 *  =============================== DMA ===============================
 */

#include <ti/drivers/dma/UDMACC32XX.h>
#include <ti/devices/cc32xx/inc/hw_ints.h>
#include <ti/devices/cc32xx/inc/hw_types.h>
#include <ti/devices/cc32xx/driverlib/rom_map.h>
#include <ti/devices/cc32xx/driverlib/udma.h>

/* Ensure DMA control table is aligned as required by the uDMA Hardware */
static tDMAControlTable dmaControlTable[64] __attribute__ ((aligned (1024)));

/* This is the handler for the uDMA error interrupt. */
static void dmaErrorFxn(uintptr_t arg)
{
    int status = MAP_uDMAErrorStatusGet();
    MAP_uDMAErrorStatusClear();

    /* Suppress unused variable warning */
    (void)status;

    while (1);
}

UDMACC32XX_Object udmaCC3220SObject;

const UDMACC32XX_HWAttrs udmaCC3220SHWAttrs = {
    .controlBaseAddr = (void *)dmaControlTable,
    .dmaErrorFxn     = (UDMACC32XX_ErrorFxn)dmaErrorFxn,
    .intNum          = INT_UDMAERR,
    .intPriority     = (~0)
};

const UDMACC32XX_Config UDMACC32XX_config = {
    .object  = &udmaCC3220SObject,
    .hwAttrs = &udmaCC3220SHWAttrs
};


/*
 *  =============================== PWM ===============================
 */

#include <ti/drivers/PWM.h>
#include <ti/drivers/pwm/PWMTimerCC32XX.h>

#define Board_PWMCOUNT 4

/*
 *  ======== pwmTimerCC32XXObjects ========
 */
PWMTimerCC32XX_Object pwmTimerCC32XXObjects[Board_PWMCOUNT];

/*
 *  ======== pwmTimerCC32XXHWAttrs ========
 */
const PWMTimerCC32XX_HWAttrsV2 pwmTimerCC32XXHWAttrs[Board_PWMCOUNT] = {
    /* Board_PWM0 */
    /* LaunchPad LED D9 (Yellow) */
    {
        .pwmPin = PWMTimerCC32XX_PIN_01, /* 01 */
    },
    /* Board_PWM1 */
    /* LaunchPad LED D8 (Green) */
    {
        .pwmPin = PWMTimerCC32XX_PIN_02, /* 02 */
    },
    /* Board_PWM2 */
    /* LaunchPad LED D10 (Red) */
    {
        .pwmPin = PWMTimerCC32XX_PIN_64, /* 64 */
    },
    /* Board_PWM3 */
    {
        .pwmPin = PWMTimerCC32XX_PIN_21, /* 21 */
    },
};

/*
 *  ======== PWM_config ========
 */
const PWM_Config PWM_config[Board_PWMCOUNT] = {
    /* Board_PWM0 */
    /* LaunchPad LED D9 (Yellow) */
    {
        .fxnTablePtr = &PWMTimerCC32XX_fxnTable,
        .object = &pwmTimerCC32XXObjects[Board_PWM0],
        .hwAttrs = &pwmTimerCC32XXHWAttrs[Board_PWM0]
    },
    /* Board_PWM1 */
    /* LaunchPad LED D8 (Green) */
    {
        .fxnTablePtr = &PWMTimerCC32XX_fxnTable,
        .object = &pwmTimerCC32XXObjects[Board_PWM1],
        .hwAttrs = &pwmTimerCC32XXHWAttrs[Board_PWM1]
    },
    /* Board_PWM2 */
    /* LaunchPad LED D10 (Red) */
    {
        .fxnTablePtr = &PWMTimerCC32XX_fxnTable,
        .object = &pwmTimerCC32XXObjects[Board_PWM2],
        .hwAttrs = &pwmTimerCC32XXHWAttrs[Board_PWM2]
    },
    /* Board_PWM3 */
    {
        .fxnTablePtr = &PWMTimerCC32XX_fxnTable,
        .object = &pwmTimerCC32XXObjects[Board_PWM3],
        .hwAttrs = &pwmTimerCC32XXHWAttrs[Board_PWM3]
    },
};

const uint_least8_t PWM_count = Board_PWMCOUNT;




/*
 *  =============================== Power ===============================
 */
#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerCC32XX.h>
#include <ti/devices/cc32xx/driverlib/prcm.h>
#include "Board.h"

extern void PowerCC32XX_initPolicy(void);
extern void PowerCC32XX_sleepPolicy(void);
PowerCC32XX_ParkInfo parkInfo[];
/*
 *  This structure defines the configuration for the Power Manager.
 */
const PowerCC32XX_ConfigV1 PowerCC32XX_config = {
    .policyInitFxn             = PowerCC32XX_initPolicy,
    .policyFxn                 = PowerCC32XX_sleepPolicy,
    .enterLPDSHookFxn          = NULL,
    .resumeLPDSHookFxn         = NULL,
    .enablePolicy              = false,
    .enableGPIOWakeupLPDS      = true,
    .enableGPIOWakeupShutdown  = true,
    .enableNetworkWakeupLPDS   = true,
    .wakeupGPIOSourceLPDS      = PRCM_LPDS_GPIO13,
    .wakeupGPIOTypeLPDS        = PRCM_LPDS_FALL_EDGE,
    .wakeupGPIOFxnLPDS         = NULL,
    .wakeupGPIOFxnLPDSArg      = 0,
    .wakeupGPIOSourceShutdown  = PRCM_HIB_GPIO13,
    .wakeupGPIOTypeShutdown    = PRCM_HIB_RISE_EDGE,
    .ramRetentionMaskLPDS      = PRCM_SRAM_COL_1|PRCM_SRAM_COL_2|PRCM_SRAM_COL_3|PRCM_SRAM_COL_4,
    .keepDebugActiveDuringLPDS = false,
    .ioRetentionShutdown       = PRCM_IO_RET_GRP_0|PRCM_IO_RET_GRP_1|PRCM_IO_RET_GRP_2|PRCM_IO_RET_GRP_3,
    .pinParkDefs               = parkInfo,
    .numPins                   = 31
};


/*
 *  =============================== SPI ===============================
 */

#include <ti/drivers/SPI.h>
#include <ti/drivers/spi/SPICC32XXDMA.h>

#include <ti/devices/cc32xx/inc/hw_ints.h>
#include <ti/devices/cc32xx/inc/hw_memmap.h>
#include <ti/devices/cc32xx/inc/hw_types.h>
#include <ti/devices/cc32xx/driverlib/prcm.h>
#include <ti/devices/cc32xx/driverlib/spi.h>
#include <ti/devices/cc32xx/driverlib/udma.h>

#define Board_SPICOUNT 2

/*
 *  ======== spiCC32XXDMAObjects ========
 */
SPICC32XXDMA_Object spiCC32XXDMAObjects[Board_SPICOUNT];

uint32_t spiCC32XXSDMAscratchBuf[Board_SPICOUNT];

/*
 *  ======== spiCC32XXDMAHWAttrs ========
 */
const SPICC32XXDMA_HWAttrsV1 spiCC32XXDMAHWAttrs[Board_SPICOUNT] = {
    /* Board_NWP_SPI */
    /* Network Processor SPI Bus */
    {
        .baseAddr = LSPI_BASE,
        .intNum = INT_LSPI,
        .intPriority = (~0),
        .spiPRCM = PRCM_LSPI,
        .csControl = SPI_SW_CTRL_CS,
        .csPolarity = SPI_CS_ACTIVEHIGH,
        .pinMode = SPI_4PIN_MODE,
        .turboMode = SPI_TURBO_OFF,
        .scratchBufPtr = &spiCC32XXSDMAscratchBuf[0],
        .defaultTxBufValue = 0,
        .rxChannelIndex = UDMA_CH12_LSPI_RX,
        .txChannelIndex = UDMA_CH13_LSPI_TX,
        .minDmaTransferSize = 100,
        .mosiPin = SPICC32XXDMA_PIN_NO_CONFIG,
        .misoPin = SPICC32XXDMA_PIN_NO_CONFIG,
        .clkPin  = SPICC32XXDMA_PIN_NO_CONFIG,
        .csPin  = SPICC32XXDMA_PIN_NO_CONFIG
    },
    /* GSPI */
    {
        .baseAddr = GSPI_BASE,
        .intNum = INT_GSPI,
        .intPriority = (~0),
        .spiPRCM = PRCM_GSPI,
        .csControl = SPI_SW_CTRL_CS,
        .csPolarity = SPI_CS_ACTIVELOW,
        .pinMode = SPI_3PIN_MODE,
        .turboMode = SPI_TURBO_OFF,
        .scratchBufPtr = &spiCC32XXSDMAscratchBuf[1],
        .defaultTxBufValue = ~0,
        .rxChannelIndex = UDMA_CH30_GSPI_RX,
        .txChannelIndex = UDMA_CH31_GSPI_TX,
        .minDmaTransferSize = 10,
        .mosiPin = SPICC32XXDMA_PIN_07_MOSI,
        .misoPin = SPICC32XXDMA_PIN_06_MISO,
        .clkPin  = SPICC32XXDMA_PIN_05_CLK,
        .csPin  = SPICC32XXDMA_PIN_NO_CONFIG
    },
};

/*
 *  ======== SPI_config ========
 */
const SPI_Config SPI_config[Board_SPICOUNT] = {
    {
        .fxnTablePtr = &SPICC32XXDMA_fxnTable,
        .object = &spiCC32XXDMAObjects[Board_NWP_SPI],
        .hwAttrs = &spiCC32XXDMAHWAttrs[Board_NWP_SPI]
    },
    /* Board_SPI0 */
    {
        .fxnTablePtr = &SPICC32XXDMA_fxnTable,
        .object = &spiCC32XXDMAObjects[Board_SPI0],
        .hwAttrs = &spiCC32XXDMAHWAttrs[Board_SPI0]
    },
};

const uint_least8_t SPI_count = Board_SPICOUNT;


/*
 *  =============================== UART ===============================
 */

#include <ti/drivers/UART.h>
#include <ti/devices/cc32xx/inc/hw_ints.h>
#include <ti/devices/cc32xx/inc/hw_memmap.h>
#include <ti/drivers/uart/UARTCC32XX.h>

#define Board_UARTCOUNT 1

#define UART0_BASE UARTA0_BASE
#define UART1_BASE UARTA1_BASE
#define INT_UART0  INT_UARTA0
#define INT_UART1  INT_UARTA1


static unsigned char uartCC32XXRingBuffer0[32];
UARTCC32XX_Object uartCC32XXObjects0;

static const UARTCC32XX_HWAttrsV1 uartCC32XXHWAttrs0 = {
    .baseAddr           = UART0_BASE,
    .intNum             = INT_UART0,
    .intPriority        = (~0),
    .flowControl        = UARTCC32XX_FLOWCTRL_NONE,
    .ringBufPtr         = uartCC32XXRingBuffer0,
    .ringBufSize        = sizeof(uartCC32XXRingBuffer0),
    .rxPin              = UARTCC32XX_PIN_57_UART0_RX,
    .txPin              = UARTCC32XX_PIN_55_UART0_TX,
    .ctsPin             = UARTCC32XX_PIN_UNASSIGNED,
    .rtsPin             = UARTCC32XX_PIN_UNASSIGNED,
    .errorFxn           = NULL
  };

const UART_Config UART_config[Board_UARTCOUNT] = {
    {   /* Board_UART0 */
        .fxnTablePtr = &UARTCC32XX_fxnTable,
        .object      = &uartCC32XXObjects0,
        .hwAttrs     = &uartCC32XXHWAttrs0
    },
};

const uint_least8_t UART_count = Board_UARTCOUNT;


#include <ti/drivers/power/PowerCC32XX.h>

/*
 * This table defines the parking state to be set for each parkable pin
 * during LPDS. (Device resources must be parked during LPDS to achieve maximum
 * power savings.)  If the pin should be left unparked, specify the state
 * PowerCC32XX_DONT_PARK.  For example, for a UART TX pin, the device
 * will automatically park the pin in a high state during transition to LPDS,
 * so the Power Manager does not need to explictly park the pin.  So the
 * corresponding entries in this table should indicate PowerCC32XX_DONT_PARK.
 */
PowerCC32XX_ParkInfo parkInfo[] = {
/*        PIN                    PARK STATE              Pin Alias
   -----------------  ------------------------------     ---------------*/

  {PowerCC32XX_PIN01, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP10 */
  {PowerCC32XX_PIN02, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP11 */
  {PowerCC32XX_PIN03, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP12 */
  {PowerCC32XX_PIN04, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP13 */
  {PowerCC32XX_PIN05, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP14 */
  {PowerCC32XX_PIN06, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP15 */
  {PowerCC32XX_PIN07, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP16 */
  {PowerCC32XX_PIN08, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP17 */
  {PowerCC32XX_PIN13, PowerCC32XX_WEAK_PULL_DOWN_STD},
  {PowerCC32XX_PIN15, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP22 */
  {PowerCC32XX_PIN16, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* TDI */
  {PowerCC32XX_PIN17, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* TDO */
  {PowerCC32XX_PIN18, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP28 */
  {PowerCC32XX_PIN19, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* TCK */
  {PowerCC32XX_PIN20, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* TMS */
  {PowerCC32XX_PIN21, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* SOP2 */
  {PowerCC32XX_PIN29, PowerCC32XX_WEAK_PULL_DOWN_STD},
  {PowerCC32XX_PIN30, PowerCC32XX_WEAK_PULL_DOWN_STD},
  {PowerCC32XX_PIN45, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP31 */
  {PowerCC32XX_PIN50, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP00 */
  {PowerCC32XX_PIN52, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP32 */
  {PowerCC32XX_PIN53, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP30 */
  {PowerCC32XX_PIN55, PowerCC32XX_WEAK_PULL_UP_STD},   /* GP01 */
  {PowerCC32XX_PIN57, PowerCC32XX_WEAK_PULL_UP_STD},   /* GP02 */
  {PowerCC32XX_PIN58, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP03 */
  {PowerCC32XX_PIN59, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP04 */
  {PowerCC32XX_PIN60, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP05 */
  {PowerCC32XX_PIN61, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP06 */
  {PowerCC32XX_PIN62, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP07 */
  {PowerCC32XX_PIN63, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP08 */
  {PowerCC32XX_PIN64, PowerCC32XX_WEAK_PULL_DOWN_STD},   /* GP09 */
};


#include <ti/drivers/Board.h>

/*
 *  ======== Board_initHook ========
 *  Perform any board-specific initialization needed at startup.  This
 *  function is declared weak to allow applications to override it if needed.
 */
#if defined(__IAR_SYSTEMS_ICC__)
__weak void Board_initHook(void)
#elif defined(__GNUC__) && !defined(__ti__)
void __attribute__((weak)) Board_initHook(void)
#else
#pragma WEAK (Board_initHook)
void Board_initHook(void)
#endif
{
}

/*
 *  ======== Board_init ========
 *  Perform any initialization needed before using any board APIs
 */
void Board_init(void)
{
    /* ==== /ti/drivers/Power initialization ==== */
    PRCMCC3200MCUInit();
    Power_init();

    Board_initHook();
}

/*
 *  ======== Board_debugHeader ========
 *  This structure prevents the CC32XXSF bootloader from overwriting the
 *  internal FLASH; this allows us to flash a program that will not be
 *  overwritten by the bootloader with the encrypted program saved in
 *  "secure/serial flash".
 *
 *  This structure must be placed at the beginning of internal FLASH (so
 *  the bootloader is able to recognize that it should not overwrite
 *  internal FLASH).
 */
#if defined (__SF_DEBUG__) || defined(__SF_NODEBUG__)
#if defined(__TI_COMPILER_VERSION__)
#pragma DATA_SECTION(Board_debugHeader, ".dbghdr")
#pragma RETAIN(Board_debugHeader)
#elif defined(__IAR_SYSTEMS_ICC__)
#pragma location=".dbghdr"
#elif defined(__GNUC__)
__attribute__ ((section (".dbghdr")))
#endif
#if defined(__SF_DEBUG__)
const uint32_t Board_debugHeader[] = {
    0x5AA5A55A,
    0x000FF800,
    0xEFA3247D
};
#elif defined (__SF_NODEBUG__)
const uint32_t Board_debugHeader[] = {
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF
};
#endif
#endif
