#ifndef GLOBALS_H
#define GLOBALS_H

// include libraries
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <AsyncTCP.h>
#include <DHT20.h>
#include <ESPAsyncWebServer.h>
#include <PubSubClient.h>
#include <SPIFFS.h>
#include <WebServer.h>
#include <WiFi.h>
#include <Wire.h>
#include <stdint.h>
#include <LCD_I2C.h>

#include "../env.h"
#include "../src/connect/TaskMQTT.h"
#include "../src/connect/TaskWebserver.h"
#include "../src/connect/TaskWifi.h"
#include "../src/device/TaskDHT20.h"
#include "../src/device/TaskDistance.h"
#include "../src/device/TaskLCD1602.h"
#include "../src/device/TaskLed.h"
#include "../src/device/TaskLight.h"
#include "../src/device/TaskSoil.h"

#define SDA 11
#define SCL 12
#define soil_pin A0
#define light_sensor_pin A1
#define led_pin 6    // d3
#define relay_pin 8  // d5
#define fan_pin 10   // d7
#define echo 18      // D9
#define trig 21      // D10
#endif