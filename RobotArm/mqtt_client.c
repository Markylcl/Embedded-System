/* Standard includes                                                         */
#include <stdlib.h>
#include <pthread.h>

#include <time.h>
#include <unistd.h>

/* MQTT Library includes                                                     */
#include <ti/net/mqtt/mqttclient.h>

/* Common interface includes                                                 */
#include "network_if.h"
#include "uart_term.h"

/* Application includes                                                      */

#include "input_queue.h"
#include "output_queue.h"

#include "mqtt_client.h"
#include "client_cbs.h"

/*Define the clientID with MacAddress*/
#define T1                        0x06
#define T2                        0xff
#define T3                        0x8a

/* Operate Lib in MQTT 3.1 mode.                                             */
#define MQTT_3_1_1               false
#define MQTT_3_1                 true

#define WILL_TOPIC               "Client"
#define WILL_MSG                 "Client Stopped"
#define WILL_QOS                 MQTT_QOS_0
#define WILL_RETAIN              false

/* Defining Broker IP address and port Number                                */
#define SERVER_ADDRESS           "192.168.4.1"
#define SERVER_IP_ADDRESS        "192.168.4.1"
#define PORT_NUMBER              1883
#define SECURED_PORT_NUMBER      8883
#define LOOPBACK_PORT            1882

/* Clean session flag                                                        */
#define CLEAN_SESSION            true

/* Retain Flag. Used in publish message.                                     */
#define RETAIN_ENABLE            0



/* Defining Subscription Topic Values                                        */
#define SUBSCRIPTION_TOPIC0      "/cc3200/RobotArmCmd"
/* Defining Publish Topic Values                                             */
#define PUBLISH_TOPIC0           "/cc3200/RobotArmState"
//#define PUBLISH_TOPIC0_DATA "Push Button SW2 has been pressed on CC32xx device T2"

/* Spawn task priority and Task and Thread Stack Size                        */
//#define TASKSTACKSIZE            2048
#define RXTASKSIZE               4096
#define MQTTTHREADSIZE           2048
//#define SPAWN_TASK_PRIORITY      9

/* secured client requires time configuration, in order to verify server     */
/* certificate validity (date).                                              */

/* Day of month (DD format) range 1-31                                       */
#define DAY                      21
/* Month (MM format) in the range of 1-12                                    */
#define MONTH                    10
/* Year (YYYY format)                                                        */
#define YEAR                     2019
/* Hours in the range of 0-23                                                */
#define HOUR                     18
/* Minutes in the range of 0-59                                              */
#define MINUTES                  57
/* Seconds in the range of 0-59                                              */
#define SEC                      21

/* Number of files used for secure connection                                */
#define CLIENT_NUM_SECURE_FILES  1

/* Expiration value for the timer that is being used to toggle the Led.      */
#define TIMER_EXPIRATION_VALUE   100 * 1000000
//*****************************************************************************
//                      LOCAL FUNCTION PROTOTYPES
//*****************************************************************************
int32_t MqttClient_start(MqttState *state);
void Mqtt_ClientStop(MqttState *state, uint8_t disconnect);

//*****************************************************************************
//                 GLOBAL VARIABLES
//*****************************************************************************

/* Connection state: (0) - connected, (negative) - disconnected              */
MQTTClient_Handle gMqttClient;
/* Client User Name and Password                                             */
//#define ClientUsername  "mqtt"
//#define ClientPassword  "mqtt"
//#define CLNT_USR_PWD 1

/* Client ID                                                                 */
/* If ClientId isn't set, the MAC address of the device will be copied into  */
/* the ClientID parameter.                                                   */
//char ClientId[13] = {'\0'};

/* Client User Name and Password                                             */



/* Publishing topics and messages                                            */
const char *publish_topic = { PUBLISH_TOPIC0 };
//const char *publish_data = { PUBLISH_TOPIC0_DATA };

/* Message Queue                                                             */
mqd_t g_PBQueue;





//*****************************************************************************
//                 Banner VARIABLES
//*****************************************************************************
#ifdef  SECURE_CLIENT

char *Mqtt_Client_secure_files[CLIENT_NUM_SECURE_FILES] =
{   "ca-cert.pem"};

/*Initialization structure to be used with sl_ExtMqtt_Init API. In order to  */
/*use secured socket method, the flag MQTTCLIENT_NETCONN_SEC, cipher,        */
/*n_files and secure_files must be configured.                               */
/*certificates also must be programmed  ("ca-cert.pem").                     */
/*The first parameter is a bit mask which configures server address type and */
/*security mode.                                                             */
/*Server address type: IPv4, IPv6 and URL must be declared with The          */
/*corresponding flag.                                                        */
/*Security mode: The flag MQTTCLIENT_NETCONN_SEC enables the security (TLS)  */
/*which includes domain name verification and certificate catalog            */
/*verification, those verifications can be disabled by adding to the bit mask*/
/*MQTTCLIENT_NETCONN_SKIP_DOMAIN_NAME_VERIFICATION and                       */
/*MQTTCLIENT_NETCONN_SKIP_CERTIFICATE_CATALOG_VERIFICATION flags             */
/*Example: MQTTCLIENT_NETCONN_IP6 | MQTTCLIENT_NETCONN_SEC |                 */
/*MQTTCLIENT_NETCONN_SKIP_CERTIFICATE_CATALOG_VERIFICATION                   */
/*For this bit mask, the IPv6 address type will be in use, the security      */
/*feature will be enable and the certificate catalog verification will be    */
/*skipped.                                                                   */
/*Note: The domain name verification requires URL Server address type        */
/*      otherwise, this verification will be disabled.                       */
MQTTClient_ConnParams Mqtt_ClientCtx =
{
    MQTTCLIENT_NETCONN_IP4 | MQTTCLIENT_NETCONN_SEC,
    SERVER_IP_ADDRESS,  //SERVER_ADDRESS,
    SECURED_PORT_NUMBER,//  PORT_NUMBER
    SLNETSOCK_SEC_METHOD_SSLv3_TLSV1_2,
    SLNETSOCK_SEC_CIPHER_FULL_LIST,
    CLIENT_NUM_SECURE_FILES,
    Mqtt_Client_secure_files
};

void setTime()
{
    SlDateTime_t dateTime =
    {   0};
    dateTime.tm_day = (uint32_t)DAY;
    dateTime.tm_mon = (uint32_t)MONTH;
    dateTime.tm_year = (uint32_t)YEAR;
    dateTime.tm_hour = (uint32_t)HOUR;
    dateTime.tm_min = (uint32_t)MINUTES;
    dateTime.tm_sec = (uint32_t)SEC;
    sl_DeviceSet(SL_DEVICE_GENERAL, SL_DEVICE_GENERAL_DATE_TIME,
            sizeof(SlDateTime_t), (uint8_t *)(&dateTime));
}

#else
MQTTClient_ConnParams Mqtt_ClientCtx = {
                                        MQTTCLIENT_NETCONN_URL,
                                         SERVER_ADDRESS,
                                         PORT_NUMBER,
                                         0, 0, 0,
                                         NULL };
#endif

/* Initialize the will_param structure to the default will parameters        */
MQTTClient_Will will_param = {WILL_TOPIC,
                               WILL_MSG,
                               WILL_QOS,
                               WILL_RETAIN };


void Mqtt_init(MqttState *state){
    state->ResetApplication = false;
    state->ApConnectionState = -1;
    state->InitState = 0;
    state->UiConnFlag = 0;
    state->ClientId[0] = '\0';
    state->topic[0] = SUBSCRIPTION_TOPIC0;
    state->qos[0] = MQTT_QOS_0;
}
int32_t Mqtt_IF_Connect()
{
    int32_t lRetVal;
    char SSID_Remote_Name[32];
    int8_t Str_Length;

    memset(SSID_Remote_Name, '\0', sizeof(SSID_Remote_Name));
    Str_Length = strlen(SSID_NAME);

    if (Str_Length)
    {
        /*Copy the Default SSID to the local variable                        */
        strncpy(SSID_Remote_Name, SSID_NAME, Str_Length);
    }

    /*Reset The state of the machine                                         */
    Network_IF_ResetMCUStateMachine();

    /*Start the driver                                                       */
    lRetVal = Network_IF_InitDriver(ROLE_STA);
    if (lRetVal < 0)
    {
        UART_PRINT("Failed to start SimpleLink Device\n\r", lRetVal);
        return (-1);
    }

    /*Initialize AP security params                                          */
    SlWlanSecParams_t SecurityParams = { 0 };
    SecurityParams.Key = (signed char *) SECURITY_KEY;
    SecurityParams.KeyLen = strlen(SECURITY_KEY);
    SecurityParams.Type = SECURITY_TYPE;

    /*Connect to the Access Point                                            */
    lRetVal = Network_IF_ConnectAP(SSID_Remote_Name, SecurityParams);
    if (lRetVal < 0)
    {
        UART_PRINT("Connection to an AP failed\n\r");
        return (-1);
    }
    return (0);
}

int32_t MQTT_SendMsgToQueue(struct msgQueue *queueElement)
{
    struct timespec abstime = { 0 };

    clock_gettime(CLOCK_REALTIME, &abstime);

    if (g_PBQueue)
    {
        /* send message to the queue                                        */
        if (mq_timedsend(g_PBQueue, (char *) queueElement,
                         sizeof(struct msgQueue), 0, &abstime) == 0)
        {
            return (0);
        }
    }
    return (-1);
}

void * MqttClientThread(void * pvParameters)
{
    struct msgQueue queueElement;
    struct msgQueue queueElemRecv;

    MQTTClient_run((MQTTClient_Handle) pvParameters);

    queueElement.event = LOCAL_CLIENT_DISCONNECTION;
    queueElement.msgPtr = NULL;

    /*write message indicating disconnect Broker message.                   */
    if (MQTT_SendMsgToQueue(&queueElement))
    {
        UART_PRINT(
                "\n\n\rQueue is full, throw first msg and send the new one\n\n\r");
        mq_receive(g_PBQueue, (char*) &queueElemRecv, sizeof(struct msgQueue),
        NULL);
        MQTT_SendMsgToQueue(&queueElement);
    }

    pthread_exit(0);

    return (NULL);
}

void * MqttClient(void *pvParameters)
{
    MqttState *state = (MqttState*) pvParameters;
    struct msgQueue queueElemRecv;
    long lRetVal = -1;
    char *tmpBuff;

    /*Initializing Client and Subscribing to the Broker.                     */
    if (state->ApConnectionState >= 0)
    {
        lRetVal = MqttClient_start((MqttState*) pvParameters);
        if (lRetVal == -1)
        {
            UART_PRINT("MQTT Client lib initialization failed\n\r");
            pthread_exit(0);
            return (NULL);
        }
    }

    /*handling the signals from various callbacks including the push button  */
    /*prompting the client to publish a msg on PUB_TOPIC OR msg received by  */
    /*the server on enrolled topic(for which the on-board client ha enrolled)*/
    /*from a local client(will be published to the remote broker by the      */
    /*client) OR msg received by the client from the remote broker (need to  */
    /*be sent to the server to see if any local client has subscribed on the */
    /*same topic).                                                           */
    for (;;)
    {
        /*waiting for signals                                                */
        mq_receive(g_PBQueue, (char*) &queueElemRecv, sizeof(struct msgQueue), NULL);

        switch (queueElemRecv.event)
        {
        case PUBLISH_PUSH_BUTTON_PRESSED:

            /*send publish message                                       */
            lRetVal = MQTTClient_publish(
                    gMqttClient,
                    (char*) publish_topic,
                    strlen((char*) publish_topic),
                    (char*) queueElemRecv.msgPtr,
                    strlen((char*) queueElemRecv.msgPtr),
                    MQTT_QOS_2 | ((RETAIN_ENABLE) ? MQTT_PUBLISH_RETAIN : 0));

            UART_PRINT("\n\r CC3200 Publishes the following message \n\r");
            UART_PRINT("Topic: %s\n\r", publish_topic);
            UART_PRINT("Data: %s\n\r", (char*) queueElemRecv.msgPtr);
            break;

            /*msg received by client from remote broker (on a topic      */
            /*subscribed by local client)                                */
        case MSG_RECV_BY_CLIENT:
            tmpBuff = (char *) ((char *) queueElemRecv.msgPtr + 12);
            if (strncmp(tmpBuff, SUBSCRIPTION_TOPIC0, queueElemRecv.topLen) == 0)
            {
                char* playload = GetPlayload(queueElemRecv.msgPtr);
                //
                InputQueue_send(playload);
            }

            free(queueElemRecv.msgPtr);
            break;

            /*On-board client disconnected from remote broker, only      */
            /*local MQTT network will work                               */
        case LOCAL_CLIENT_DISCONNECTION:
            UART_PRINT("\n\rOn-board Client Disconnected\n\r\r\n");
            state->UiConnFlag = 0;
            break;

            /*Push button for full restart check                         */
        case DISC_PUSH_BUTTON_PRESSED:
            state->ResetApplication = true;
            break;

        case THREAD_TERMINATE_REQ:
            state->UiConnFlag = 0;
            pthread_exit(0);
            return (NULL);
        case BRIDGE_DISCONNECTION:
            state->ResetApplication = true;
            break;
        default:
            sleep(1);
            break;
        }
    }
}

void *MqttSendThread(void *pvParameters)
{
    char buffer[OUTPUT_QUEUE_SIZE];
    while (1)
    {
        if(OutputQueue_recv(buffer)){
            struct msgQueue queueElement;
            queueElement.event = PUBLISH_PUSH_BUTTON_PRESSED;
            queueElement.msgPtr = buffer;

            /* write message indicating publish message                             */
            if(MQTT_SendMsgToQueue(&queueElement))
            {
                UART_PRINT("\n\n\rQueue is full\n\n\r");
            }
        }
    }
}


void Mqtt_start(MqttState *state)
{

    pthread_attr_t pAttrs;
    struct sched_param priParam;
    int32_t retc = 0;
    mq_attr attr;
    unsigned mode = 0;

    //topic[0] = SUBSCRIPTION_TOPIC0;

    /*sync object for inter thread communication                             */
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(struct msgQueue);
    g_PBQueue = mq_open("g_PBQueue", O_CREAT, mode, &attr);

    if (g_PBQueue == NULL)
    {
        UART_PRINT("MQTT Message Queue create fail\n\r");
        state->InitState &= ~MQTT_INIT_STATE;
        return;
    }
    pthread_t mqttThread = (pthread_t) NULL;
    /*Set priority and stack size attributes                                 */
    pthread_attr_init(&pAttrs);
    priParam.sched_priority = 2;
    retc = pthread_attr_setschedparam(&pAttrs, &priParam);
    retc |= pthread_attr_setstacksize(&pAttrs, MQTTTHREADSIZE);
    retc |= pthread_attr_setdetachstate(&pAttrs, PTHREAD_CREATE_DETACHED);

    if (retc != 0)
    {
        state->InitState &= ~MQTT_INIT_STATE;
        UART_PRINT("MQTT thread create fail\n\r");
        return;
    }

    retc = pthread_create(&mqttThread, &pAttrs, MqttClient,
                          (void *)state);
    if (retc != 0)
    {
        state->InitState &= ~MQTT_INIT_STATE;
        UART_PRINT("MQTT thread create fail\n\r");
        return;
    }

    /*enable interrupt for the GPIO 13 (SW3) and GPIO 22 (SW2).              */
//    GPIO_setCallback(CONFIG_GPIO_BUTTON_0, pushButtonInterruptHandler2);
//    GPIO_enableInt(CONFIG_GPIO_BUTTON_0); // SW2
//
//    GPIO_setCallback(CONFIG_GPIO_BUTTON_1, pushButtonInterruptHandler3);
//    GPIO_enableInt(CONFIG_GPIO_BUTTON_1); // SW3
    state->InitState &= ~MQTT_INIT_STATE;


    pthread_attr_init(&pAttrs);
    priParam.sched_priority = 2;
    retc = pthread_attr_setschedparam(&pAttrs, &priParam);
    retc |= pthread_attr_setstacksize(&pAttrs, 1024);
    retc |= pthread_attr_setdetachstate(&pAttrs, PTHREAD_CREATE_DETACHED);
    retc = pthread_create(&mqttThread, &pAttrs, MqttSendThread, NULL);

    return;
}

void Mqtt_Stop(MqttState *state)
{
    struct msgQueue queueElement;
    struct msgQueue queueElemRecv;

    if (state->ApConnectionState >= 0)
    {
        Mqtt_ClientStop(state, 1);
    }

    queueElement.event = THREAD_TERMINATE_REQ;
    queueElement.msgPtr = NULL;

    /*write message indicating publish message                               */
    if (MQTT_SendMsgToQueue(&queueElement))
    {
        UART_PRINT(
                "\n\n\rQueue is full, throw first msg and send the new one\n\n\r");
        mq_receive(g_PBQueue, (char*) &queueElemRecv, sizeof(struct msgQueue),
        NULL);
        MQTT_SendMsgToQueue(&queueElement);
    }

    sleep(2);

    mq_close(g_PBQueue);
    g_PBQueue = NULL;

    sl_Stop(SL_STOP_TIMEOUT);
    UART_PRINT("\n\r Client Stop completed\r\n");

    /*Disable the SW2 and SW3 interrupt */
    //GPIO_disableInt(CONFIG_GPIO_BUTTON_0); // SW2
    //GPIO_disableInt(CONFIG_GPIO_BUTTON_1); // SW3
}

int32_t MqttClient_start(MqttState *state)
{
    int32_t lRetVal = -1;
    int32_t iCount = 0;

    int32_t threadArg = 100;
    pthread_attr_t pAttrs;
    struct sched_param priParam;
    MQTTClient_Params MqttClientExmple_params;
    MqttClientExmple_params.clientId = state->ClientId;
    MqttClientExmple_params.connParams = &Mqtt_ClientCtx;
    MqttClientExmple_params.mqttMode31 = MQTT_3_1;
    MqttClientExmple_params.blockingSend = true;

    state->InitState |= CLIENT_INIT_STATE;

    /*Initialize MQTT client lib                                             */
    gMqttClient = MQTTClient_create(MqttClientCallback,
                                    &MqttClientExmple_params);
    if (gMqttClient == NULL)
    {
        /*lib initialization failed                                          */
        state->InitState &= ~CLIENT_INIT_STATE;
        return (-1);
    }

    pthread_t g_rx_task_hndl;
    /*Open Client Receive Thread start the receive task. Set priority and    */
    /*stack size attributes                                                  */
    pthread_attr_init(&pAttrs);
    priParam.sched_priority = 2;
    lRetVal = pthread_attr_setschedparam(&pAttrs, &priParam);
    lRetVal |= pthread_attr_setstacksize(&pAttrs, RXTASKSIZE);
    lRetVal |= pthread_attr_setdetachstate(&pAttrs, PTHREAD_CREATE_DETACHED);
    lRetVal |= pthread_create(&g_rx_task_hndl, &pAttrs, MqttClientThread,
                              (void *) &threadArg);
    if (lRetVal != 0)
    {
        UART_PRINT("Client Thread Create Failed failed\n\r");
        state->InitState &= ~CLIENT_INIT_STATE;
        return (-1);
    }
#ifdef SECURE_CLIENT
    setTime();
#endif

    /*setting will parameters                                                */
    MQTTClient_set(gMqttClient, MQTTClient_WILL_PARAM, &will_param,
                   sizeof(will_param));

#ifdef CLNT_USR_PWD
    /*Set user name for client connection                                    */
    MQTTClient_set(gMqttClient, MQTTClient_USER_NAME, (void *) ClientUsername,
                   strlen((char*) ClientUsername));

    /*Set password                                                           */
    MQTTClient_set(gMqttClient, MQTTClient_PASSWORD, (void *) ClientPassword,
                   strlen((char*) ClientPassword));
#endif
    /*Initiate MQTT Connect                                                  */
    if (state->ApConnectionState >= 0)
    {
#if CLEAN_SESSION == false
        bool clean = CLEAN_SESSION;
        MQTTClient_set(gMqttClient, MQTTClient_CLEAN_CONNECT, (void *)&clean,
                sizeof(bool));
#endif
        /*The return code of MQTTClient_connect is the ConnACK value that
         returns from the server */
        lRetVal = MQTTClient_connect(gMqttClient);

        /*negative lRetVal means error,
         0 means connection successful without session stored by the server,
         greater than 0 means successful connection with session stored by
         the server */
        if (0 > lRetVal)
        {
            /*lib initialization failed                                      */
            UART_PRINT("Connection to broker failed, Error code: %d\n\r",
                       lRetVal);

            state->UiConnFlag = 0;
        }
        else
        {
            state->UiConnFlag = 1;
        }
        /*Subscribe to topics when session is not stored by the server       */
        if ((state->UiConnFlag == 1) && (0 == lRetVal))
        {
            uint8_t subIndex;
            MQTTClient_SubscribeParams subscriptionInfo[SUBSCRIPTION_TOPIC_COUNT];

            for (subIndex = 0; subIndex < SUBSCRIPTION_TOPIC_COUNT; subIndex++)
            {
                subscriptionInfo[subIndex].topic = state->topic[subIndex];
                subscriptionInfo[subIndex].qos = state->qos[subIndex];
            }

            if (MQTTClient_subscribe(gMqttClient, subscriptionInfo,
            SUBSCRIPTION_TOPIC_COUNT) < 0)
            {
                UART_PRINT("\n\r Subscription Error \n\r");
                MQTTClient_disconnect(gMqttClient);
                state->UiConnFlag = 0;
            }
            else
            {
                for (iCount = 0; iCount < SUBSCRIPTION_TOPIC_COUNT; iCount++)
                {
                    UART_PRINT("Client subscribed on %s\n\r", state->topic[iCount]);
                }
            }
        }
    }

    state->InitState &= ~CLIENT_INIT_STATE;

    return (0);
}

void Mqtt_ClientStop(MqttState *state, uint8_t disconnect)
{
    uint32_t iCount;

    MQTTClient_UnsubscribeParams subscriptionInfo[SUBSCRIPTION_TOPIC_COUNT];

    for (iCount = 0; iCount < SUBSCRIPTION_TOPIC_COUNT; iCount++)
    {
        subscriptionInfo[iCount].topic = state->topic[iCount];
    }

    MQTTClient_unsubscribe(gMqttClient, subscriptionInfo,
    SUBSCRIPTION_TOPIC_COUNT);
    for (iCount = 0; iCount < SUBSCRIPTION_TOPIC_COUNT; iCount++)
    {
        UART_PRINT("Unsubscribed from the topic %s\r\n", state->topic[iCount]);
    }
    state->UiConnFlag = 0;

    /*exiting the Client library                                             */
    MQTTClient_delete(gMqttClient);
}
int32_t SetClientIdNamefromMacAddress(MqttState *state)
{
    int32_t ret = 0;
   // uint8_t Client_Mac_Name[2];
   // uint8_t Index;
    uint16_t macAddressLen = SL_MAC_ADDR_LEN;
    uint8_t macAddress[SL_MAC_ADDR_LEN];

    /*Get the device Mac address */
    ret = sl_NetCfgGet(SL_NETCFG_MAC_ADDRESS_GET, 0, &macAddressLen,
                       &macAddress[0]);

    if (macAddress[4]== T1){
        strcpy(state->ClientId, "T1");
    }
    else if (macAddress[4]== T2){
        strcpy(state->ClientId, "T2");
    }
    else if (macAddress[4]== T3){
        strcpy(state->ClientId, "T3");
    }
    else{
        strcpy(state->ClientId, "T4");
    }
//
//    /*When ClientID isn't set, use the mac address as ClientID               */
//    if (state->ClientId[0] == '\0')
//    {
//        /*6 bytes is the length of the mac address                           */
//        for (Index = 0; Index < SL_MAC_ADDR_LEN; Index++)
//        {
//            /*Each mac address byte contains two hexadecimal characters      */
//            /*Copy the 4 MSB - the most significant character                */
//            Client_Mac_Name[0] = (macAddress[Index] >> 4) & 0xf;
//            /*Copy the 4 LSB - the least significant character               */
//            Client_Mac_Name[1] = macAddress[Index] & 0xf;
//
//            if (Client_Mac_Name[0] > 9)
//            {
//                /*Converts and copies from number that is greater than 9 in  */
//                /*hexadecimal representation (a to f) into ascii character   */
//                state->ClientId[2 * Index] = Client_Mac_Name[0] + 'a' - 10;
//            }
//            else
//            {
//                /*Converts and copies from number 0 - 9 in hexadecimal       */
//                /*representation into ascii character                        */
//                state->ClientId[2 * Index] = Client_Mac_Name[0] + '0';
//            }
//            if (Client_Mac_Name[1] > 9)
//            {
//                /*Converts and copies from number that is greater than 9 in  */
//                /*hexadecimal representation (a to f) into ascii character   */
//                state->ClientId[2 * Index + 1] = Client_Mac_Name[1] + 'a' - 10;
//            }
//            else
//            {
//                /*Converts and copies from number 0 - 9 in hexadecimal       */
//                /*representation into ascii character                        */
//                state->ClientId[2 * Index + 1] = Client_Mac_Name[1] + '0';
//            }
//        }
//    }
    return (ret);
}
