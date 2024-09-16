/*
 * All things related to wifi should live here
 */

#ifndef __WIFI_CONFIG_H_
#define __WIFI_CONFIG_H_
#include <WiFi.h>

// AP SSID of the Access Point
extern const char *ssid;
// Password of the Access Point
extern const char *password;
// Create a Web Server Named server
extern WiFiServer server;

// Used to obtain STATIC IP
void get_static_ip();
// Check Wifi Connection after initializing the connection
void check_wifi();
// Used to reconnect if the wifi is lost
void reconnect();
// Print ip_address if needed
void print_ip();
#endif // !__WIFI_CONFIG_H_
