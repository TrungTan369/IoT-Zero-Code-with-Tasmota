#ifndef INC_TASKMQTT_H_
#define INC_TASKMQTT_H_

#include "globals.h"

extern PubSubClient client;
void initMQTT();
void reconnectMQTT();
void publishData(String feed, String data);

#endif /* INC_TASKMQTT_H_ */