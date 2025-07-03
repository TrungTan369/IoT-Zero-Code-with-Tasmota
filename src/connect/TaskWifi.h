#ifndef INC_TASKWIFI_H_
#define INC_TASKWIFI_H_

#include "globals.h"

extern String ssid;
extern String password;

void initWiFi();
bool Wifi_reconnect();
bool loadWiFiFromFS();
bool saveWiFiToFS(const String& ssid, const String& password);
void startConfigPortal();
#endif /* INC_TASKWIFI_H_ */