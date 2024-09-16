#include "wifi_config.h"
#include <Arduino.h>

const char *ssid = "802.11";
const char *password = "12345678p";

WiFiServer server(80);

void get_static_ip() {
  // Get static IP
  IPAddress local_IP(192, 168, 13, 5);
  IPAddress gateway(192, 168, 13, 1);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress primaryDNS(8, 8, 8, 8);
  IPAddress secondaryDNS(8, 8, 8, 8);
  // Initialize the wifi
  WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS);
}
void check_wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
}

void reconnect() {
  if ((WiFi.status()) != WL_CONNECTED) {
    Serial.println("Reconnecting .");
    WiFi.disconnect();
    WiFi.reconnect();
    delay(5000);
  }
}
void print_ip() {
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
