/* Standard includes                                                         */
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/* TI-Driver includes                                                        */
#include <ti/drivers/SPI.h>

/* Simplelink includes                                                       */
#include <ti/drivers/net/wifi/simplelink.h>

/* SlNetSock includes                                                        */
#include <ti/drivers/net/wifi/slnetifwifi.h>

/* Common interface includes                                                 */
#include "network_if.h"
#include "uart_term.h"

/* Application includes                                                      */
#include "Board.h"
#include "network_if.h"
#include "input_queue.h"
#include "output_queue.h"
#include "robot_arm.h"
#include "mqtt_client.h"
#include "uart_clinet.h"
#define APPLICATION_VERSION      "1.1.1"
#define APPLICATION_NAME         "MQTT client"

#define SLNET_IF_WIFI_PRIO       (5)
/* Spawn task priority and Task and Thread Stack Size                        */
#define TASKSTACKSIZE            2048
//#define RXTASKSIZE               4096
//#define MQTTTHREADSIZE           2048
#define SPAWN_TASK_PRIORITY      9

/* Printing new line                                                         */
char lineBreak[] = "\n\r";

void printBorder(char ch, int n)
{
    int i = 0;

    for (i = 0; i < n; i++)
    {
        putch(ch);
    }
}

int32_t DisplayAppBanner(char* appName, char* appVersion)
{
    int32_t ret = 0;
    uint8_t macAddress[SL_MAC_ADDR_LEN];
    uint16_t macAddressLen = SL_MAC_ADDR_LEN;
    uint16_t ConfigSize = 0;
    uint8_t ConfigOpt = SL_DEVICE_GENERAL_VERSION;
    SlDeviceVersion_t ver = { 0 };

    ConfigSize = sizeof(SlDeviceVersion_t);

    /*Print device version info. */
    ret = sl_DeviceGet(SL_DEVICE_GENERAL, &ConfigOpt, &ConfigSize,
                       (uint8_t*) (&ver));

    /*Print device Mac address */
    ret |= (int32_t) sl_NetCfgGet(SL_NETCFG_MAC_ADDRESS_GET, 0, &macAddressLen,
                                  &macAddress[0]);

    UART_PRINT(lineBreak);
    UART_PRINT("\t");
    printBorder('=', 44);
    UART_PRINT(lineBreak);
    UART_PRINT("\t   %s Example Ver: %s", appName, appVersion);
    UART_PRINT(lineBreak);
    UART_PRINT("\t");
    printBorder('=', 44);
    UART_PRINT(lineBreak);
    UART_PRINT(lineBreak);
    UART_PRINT("\t CHIP: 0x%x", ver.ChipId);
    UART_PRINT(lineBreak);
    UART_PRINT("\t MAC:  %d.%d.%d.%d", ver.FwVersion[0], ver.FwVersion[1],
               ver.FwVersion[2], ver.FwVersion[3]);
    UART_PRINT(lineBreak);
    UART_PRINT("\t PHY:  %d.%d.%d.%d", ver.PhyVersion[0], ver.PhyVersion[1],
               ver.PhyVersion[2], ver.PhyVersion[3]);
    UART_PRINT(lineBreak);
    UART_PRINT("\t NWP:  %d.%d.%d.%d", ver.NwpVersion[0], ver.NwpVersion[1],
               ver.NwpVersion[2], ver.NwpVersion[3]);
    UART_PRINT(lineBreak);
    UART_PRINT("\t ROM:  %d", ver.RomVersion);
    UART_PRINT(lineBreak);
    UART_PRINT("\t HOST: %s", SL_DRIVER_VERSION);
    UART_PRINT(lineBreak);
    UART_PRINT("\t MAC address: %02x:%02x:%02x:%02x:%02x:%02x", macAddress[0],
               macAddress[1], macAddress[2], macAddress[3], macAddress[4],
               macAddress[5]);
    UART_PRINT(lineBreak);
    UART_PRINT(lineBreak);
    UART_PRINT("\t");
    printBorder('=', 44);
    UART_PRINT(lineBreak);
    UART_PRINT(lineBreak);

    return (ret);
}

void *mainThread(void *arg0)
{
    uint32_t count = 0;
    pthread_t spawn_thread = (pthread_t) NULL;
    pthread_attr_t pAttrs_spawn;
    struct sched_param priParam;
    int32_t retc = 0;
    UART_Handle tUartHndl;

   // uint32_t memPtrCounterfree = 0;
   // bool resetApplication = false;

    /*Initialize SlNetSock layer with CC31xx/CC32xx interface */
    retc =SlNetIf_init(0);
    retc = SlNetIf_add(SLNETIF_ID_1, "CC32xx",
                (const SlNetIf_Config_t *) &SlNetIfConfigWifi,
                SLNET_IF_WIFI_PRIO);

    retc =SlNetSock_init(0);
    retc = SlNetUtil_init(0);

    SPI_init();

    /*Configure the UART                                                     */
    tUartHndl = InitTerm();
    /*remove uart receive from LPDS dependency                               */
    UART_control(tUartHndl, UART_CMD_RXDISABLE, NULL);

    InputQueue_init();
    OutputQueue_init();
    //UartClient_start();
    RobotArm_start();

    /*Create the sl_Task                                                     */
    pthread_attr_init(&pAttrs_spawn);
    priParam.sched_priority = SPAWN_TASK_PRIORITY;
    retc = pthread_attr_setschedparam(&pAttrs_spawn, &priParam);
    retc |= pthread_attr_setstacksize(&pAttrs_spawn, TASKSTACKSIZE);
    retc |= pthread_attr_setdetachstate(&pAttrs_spawn, PTHREAD_CREATE_DETACHED);
    retc = pthread_create(&spawn_thread, &pAttrs_spawn, sl_Task, NULL);

    if (retc != 0)
    {
        UART_PRINT("could not create simplelink task\n\r");
        while (1);
    }
    retc = sl_Start(0, 0, 0);
    if (retc < 0)
    {
        /*Handle Error */
        UART_PRINT("\n sl_Start failed\n");
        while (1);
    }

    MqttState state;
    Mqtt_init(&state);
    retc = DisplayAppBanner(APPLICATION_NAME, APPLICATION_VERSION);
    /*Set the ClientId with its own mac address */
    retc |= SetClientIdNamefromMacAddress(&state);
    retc = sl_Stop(SL_STOP_TIMEOUT);
    if (retc < 0)
    {
        /*Handle Error */
        UART_PRINT("\n sl_Stop failed\n");
        while (1);
    }
    if (retc < 0)
    {
        /*Handle Error */
        UART_PRINT("mqtt_client - Unable to retrieve device information \n");
        while (1);
    }

    while (1)
    {
        state.ResetApplication = false;
        state.InitState = 0;
        /*Connect to AP                                                      */
        state.ApConnectionState = Mqtt_IF_Connect();
        state.InitState |= MQTT_INIT_STATE;
        /*Run MQTT Main Thread (it will open the Client and Server)          */
        Mqtt_start(&state);
        /*Wait for init to be completed!!!                                   */
        while(state.InitState != 0)
        {
            UART_PRINT(".");
            sleep(1);
        }
        while(state.ResetApplication == false);
        UART_PRINT("TO Complete - Closing all threads and resources\r\n");
        /*Stop the MQTT Process                                              */
        Mqtt_Stop();
        UART_PRINT("reopen MQTT # %d  \r\n", ++count);
    }
}
