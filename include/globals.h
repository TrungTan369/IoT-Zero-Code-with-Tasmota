#ifndef GLOBALS_H
#define GLOBALS_H

// include libraries
#include <Arduino.h>
#include <DHT20.h>
#include <PubSubClient.h>
#include <WebServer.h>
#include <WiFi.h>
#include <Wire.h>
#include <env.h>
//#include <LiquidCrystal_I2C.h>

#include "../src/connect/TaskMQTT.h"
#include "../src/connect/TaskWebserver.h"
#include "../src/connect/TaskWifi.h"
#include "../src/device/TaskDHT20.h"

#define delay_time 10000
#define SDA 11
#define SCL 12

#endif