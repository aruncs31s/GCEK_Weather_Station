#include "wifi_config.h"
#include <cstdint>

// replace the desired ip
uint8_t desired_IP[] = {192, 168, 58, 5};
// in most case the subnet will be 24 or 22 in the case of GCEK
uint8_t subnet = 24;

void get_static_ip() {
  // Get static IP
  IPAddress local_IP(desired_IP[0], desired_IP[1], desired_IP[2],
                     desired_IP[3]);
  IPAddress gateway(desired_IP[0], desired_IP[1], desired_IP[2], 1);
  IPAddress subnet(0xFF, 0xFF, 0xFF, 0x00);
  // This is optional
  IPAddress primaryDNS(8, 8, 8, 8);
  IPAddress secondaryDNS(8, 8, 8, 8);
  // Initialize the wifi
  WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS);
}

void check_wifi() {
  // TODO: Check if the wifi connects ``
  const char *ssid = "802.11";
  const char *password = "12345678p";

  // Connect to WiFi
  WiFi.begin(ssid, password);
  // check if the WiFi is connected
  while (WiFi.status() != WL_CONNECTED) {
    // Stay in loop if not connected
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
}
void reconnect() {
  // Check if the wifi is connected
  if ((WiFi.status()) != WL_CONNECTED) {
    Serial.println("Reconnecting .");
    // if the WiFi is not connected disconnect from current WiFi and then
    // reconnect
    WiFi.disconnect();
    WiFi.reconnect();
    // TODO: Check if the delay is needed
    delay(5000);
  }
}
