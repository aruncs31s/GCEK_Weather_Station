#ifndef __WEBSITE_H_
#define __WEBSITE_H_
#include "config.h"
#include <Arduino.h>
#include <WiFi.h>
#include <cstdint>

// Used to know the listening client
class WebSite {
public:
  // Start listening for incoming connection
  void start_server();
  // Stops the website
  void stop();
  // Serve the website
  void serve(Data &new_data);

private:
  unsigned long currentTime;
  unsigned long previousTime;
  uint16_t timeoutTime = TIMEOUT;
  String header;
  WiFiClient client;
  WiFiServer server;
};
#endif // !__WEBSITE_H_
