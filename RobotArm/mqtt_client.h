#ifndef __MQTT_CLIENT__H__
#define __MQTT_CLIENT__H__
#include <mqueue.h>

#define CLIENT_INIT_STATE        (0x01)
#define MQTT_INIT_STATE          (0x04)

/* Defining Number of subscription topics                                    */
#define SUBSCRIPTION_TOPIC_COUNT 1

typedef struct{
    bool ResetApplication;
    int32_t ApConnectionState;
    uint32_t InitState;
    uint32_t UiConnFlag;
    char ClientId[13];
    char *topic[SUBSCRIPTION_TOPIC_COUNT];
    unsigned char qos[SUBSCRIPTION_TOPIC_COUNT];
}MqttState;

void Mqtt_init(MqttState *state);
int32_t Mqtt_IF_Connect();
void Mqtt_start(MqttState *state);
void Mqtt_Stop();
//int32_t MQTT_SendMsgToQueue(struct msgQueue *queueElement);
int32_t SetClientIdNamefromMacAddress(MqttState *state);
#endif
