#ifndef GLOBALS_H
#define GLOBALS_H

// include libraries
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <AsyncTCP.h>  // ---
#include <DHT20.h>
#include <ESPAsyncWebServer.h>  //--
#include <LCD_I2C.h>
#include <LittleFS.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <Wire.h>
#include <stdint.h>

#include "../env.h"
#include "../src/connect/TaskMQTT.h"
#include "../src/connect/TaskWebserver.h"
#include "../src/connect/TaskWifi.h"
#include "../src/device/TaskDHT20.h"
#include "../src/device/TaskDistance.h"
#include "../src/device/TaskFan.h"
#include "../src/device/TaskLCD1602.h"
#include "../src/device/TaskLed.h"
#include "../src/device/TaskLight.h"
#include "../src/device/TaskRelay.h"
#include "../src/device/TaskSoil.h"
#include "../src/task/fsm.h"

#define SDA 11
#define SCL 12
#define soil_pin 1
#define light_sensor_pin 2
#define led_pin 6    // D3
#define relay_pin 8  // D5
#define fan_pin 10   // D7
#define echo 21      // D10
#define trig 18      // D8

#endif