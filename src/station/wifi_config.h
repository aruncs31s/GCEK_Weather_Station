#ifndef __WIFI_CONFIG_H_
#define __WIFI_CONFIG_H_
#include <Arduino.h>
#include <WiFi.h>
// this connects to the WiFi
// @param ssid , and password
void connect();
// this reconnects to the WiFi if lost connection due to signal loss
void reconnect();

// Gets static ip
void get_static_ip();
// N
// void print_ip();

void check_wifi();
#endif // !__WIFI_CONFIG_H_
